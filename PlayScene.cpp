#include "PlayScene.h"
#include"Player.h"
#include"Ground.h"
#include "Basket.h"
#include "Ball.h"
#include "UI.h"
#include "BackGround.h"
#include "PlayStop.h"
#include "AssistReady.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Camera.h"
#include "Engine/Audio.h"
#include "Result.h"

//定数
namespace
{
	static const int ALL_BALL = 60;//ボールの数
	static const int END_TIME = 7200;//ゲーム時間
	static const float VOLUME = 0.7f;//音量
}

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), hPict_(-1), hSound_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	hSound_ = Audio::Load("PlayBGM.wav", true, VOLUME, 1);
	assert(hSound_ >= 0);

	Instantiate<BackGround>(this);
	Instantiate<Ground>(this);
	for (int i = 0; i < ALL_BALL; i++)
	{
		if (pBall[i] == nullptr)
		{
			pBall[i] = Instantiate<Ball>(this);
			pBall[i]->ballID = i;
		}
	}

	const char* objectName[] = { "Player","Player2" ,"Player3" ,"Player4" };
	for (int i = 0; i < ScreenSplit::GetAllPerson(); i++)
	{
		pPlayer[i] = Instantiate<Player>(this);
		pPlayer[i]->playerID = i;
		pPlayer[i]->SetObjectName(objectName[i]);
	}

	Instantiate<Basket>(this);
	Instantiate<Time>(this);
	Instantiate<PlayStop>(this);
	Instantiate<AssistReady>(this);
	Instantiate<UI>(this);
	Instantiate<Result>(this);
	pGround = (Ground*)FindObject("Ground");

	Camera::SetScreen(ScreenSplit::GetScreenSplit());
}

//更新
void PlayScene::Update()
{
	if (pGround->GetGroundBall() < ALL_BALL / 2)
	{
		for (int i = 0; i < ALL_BALL / 2; i++)
		{
			pBall[i] = InstantiateFront<Ball>(this);
			pBall[i]->ballID = i;
		}
		pGround->SetGroundBall(ALL_BALL / 2);
	}

#ifdef _DEBUG

	//デバッグのみ
	if (Input::IsKeyDown(DIK_T))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
		Audio::Release();
	}

#endif // DEBUG
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}