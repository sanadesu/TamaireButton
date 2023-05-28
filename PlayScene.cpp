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
//#include "Engine/Camera.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), hPict_Back(-1), hPict_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	hSound_ = Audio::Load("PlayBGM.wav", true, 0.8f, 1);
	assert(hSound_ >= 0);
	isEnd = false;

	//ScreenSplit::SetScreenSplit(2);//後でプレイヤーの数に変更　これを★に
	//Camera::Initialize();
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

	groundBall = ALL_BALL;
	for (int i = 0; i < ScreenSplit::GetAllPerson(); i++)
	{
		pPlayer[i] = Instantiate<Player>(this);
		pPlayer[i]->playerID = i;
		//pPlayer[i]->SetObjectName("Player" + (char)i); 
	}
	if(pPlayer[1] != nullptr)
	{
		pPlayer[1]->SetObjectName("Player2");
	}
	if (pPlayer[2] != nullptr)
	{
		pPlayer[2]->SetObjectName("Player3");
	}
	if (pPlayer[3] != nullptr)
	{
		pPlayer[3]->SetObjectName("Player4");
	}

	Instantiate<Basket>(this);
	
	pText = new Text;
	pText->Initialize();
	time = END_TIME;
	playerNumber = 0;
	startTime = 180;
	Instantiate<Time>(this);
	Instantiate<PlayStop>(this);
	Instantiate<AssistReady>(this);
	Instantiate<UI>(this);
	Instantiate<Result>(this);
	pGround = (Ground*)FindObject("Ground");
	pUI = (UI*)FindObject("UI");
	pTime = (Time*)FindObject("Time");

	hPict_Back = Image::Load("TimeBack.png");
	assert(hPict_Back >= 0);

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