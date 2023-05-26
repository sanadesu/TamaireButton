#include "TitleScene.h"
#include"Engine/Camera.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Audio.h"
#include "Engine/Model.h"
#include "Engine/Easing.h"
#include"TitlePlayer.h"
#include"TitleText.h"
#include"TitleBall.h"
#include "Frame.h"
#include "TitleButton.h"
#include "Engine/ButtonManager.h"
#include "Rule.h"
//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1), hPict_Back(-1), hSound_(-1), hSound_Button(-1), hSound_Move(-1), hModel_(-1)
{
}

//初期化
void TitleScene::Initialize()
{ 
	isSkip = false;
	//サウンドデータのロード
	hSound_ = Audio::Load("Star.wav", false, 0.8f, 1);
	assert(hSound_ >= 0);
	hSound_Button = Audio::Load("Button.wav", false, 0.8f, 10);
	assert(hSound_Button >= 0);
	hSound_Move = Audio::Load("Move.wav", false, 0.8f, 10);
	assert(hSound_Move >= 0);

	Audio::Play(hSound_);

	ScreenSplit::SetScreenSplit(1);
	Camera::Initialize();
	//画像データのロード
	hPict_ = Image::Load("Title.png");
	assert(hPict_ >= 0);
	hPict_Back = Image::Load("Back.jpg");
	assert(hPict_Back >= 0);
	hModel_ = Model::Load("BackSky.fbx");
	assert(hModel_ >= 0);


	Instantiate<Frame>(this);
	
	Instantiate<TitleText>(this);
	//Instantiate<TitleButton>(this);
	TitleButton* pTitleButton[2];
	const char* ButtonName[2] = { "TitleStartButton","TitleRuleButton" };
	for (int i = 0; i < 2; i++)
	{
		pTitleButton[i] = ButtonManager::CreateButton<TitleButton>(this, transform_.position_, i);
		pTitleButton[i]->SetObjectName(ButtonName[i]);
	}

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		pT_Player[i] = InstantiateFront<TitlePlayer>(this);
		pT_Player[i]->T_PlayerID = i;
	}
	Instantiate<Rule>(this);
}

//更新
void TitleScene::Update()
{
	Frame* nowFrame = (Frame*)FindObject("Frame");
	if (nowFrame->GetFrame() % BALL_DROP_INTERVAL == 0 && nowFrame->GetFrame() >= DROP_START_FRAME)
	{
		//☆
		/*SceneManager* pSceneMnager = (SceneManager*)FindObject("SceneManager");
		Instantiate<TitleBack>(pSceneMnager);*/
		InstantiateFront<TitleBall>(this);
	}
	
	//ボタン押されたらスキップ
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		isSkip = true;
	}
}

//描画
void TitleScene::Draw()
{
	/*Model::SetTransform(hModel_, transSky);
	Model::Draw(hModel_);*/
	Transform transBack = transform_;
	transBack.position_ = XMFLOAT3(0, 0, 0);
	Image::SetTransform(hPict_Back, transBack);
	Image::Draw(hPict_Back);
	//Image::SetTransform(hPict_Select, transButton);
	//Image::Draw(hPict_Select);

	//
	/*8, 5;
	960; 225;
	1920; 1080;
	Image::SetRect(hPict_, 600, 0, 400, 450);
	transBack.position_ = XMFLOAT3(((float)400/1920 + 600.0f/ 960.0f) - 1, 1 - (float)450/1080, 0);
	Image::SetTransform(hPict_, transBack);
	Image::Draw(hPict_);*/

	//Image::ResetRect(hPict_);
	//Image::SetTransform(hPict_, transform_);
	//Image::Draw(hPict_);
}

//開放
void TitleScene::Release()
{
}

bool TitleScene::GetIsSkip()
{
	return isSkip;
}
