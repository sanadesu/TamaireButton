#include "SettingStartButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Number.h"
#include "Engine/Easing.h"

//定数
namespace
{
	static const float EASE_VAL = 0.04f;//イージングの変化量(スライド)
	static const float START_EASE = 1.4f;//スライド開始,イージング
	static const float START_BUTTON_Y = -0.7f;//スタートボタンの位置(Y)
	static const float NUM_X = 0.435f;//数字の位置(X)
}

//コンストラクタ
SettingStartButton::SettingStartButton(GameObject* parent)
	: Button(parent, "SettingButton")
{
}

//初期化
void SettingStartButton::SubInitialize()
{
	easeSave = 1;
	easeX = 0;
	Number* pNumber1 = (Number*)FindObject("Number1");
	Number* pNumber2 = (Number*)FindObject("Number2");
	playerNum = 1;
	comNum = 3;
	pNumber1->SetNum(playerNum, 0, NUM_X);
	pNumber2->SetNum(comNum, 0, NUM_X);

	transform_.position_.y = START_BUTTON_Y;
	SetImage("NormalCircle.png", transform_);

	//ボタン追加
	ButtonManager::AddButton((Button*)this,0);
}

void SettingStartButton::SubUpdate()
{
	ButtonSwith();
	//動き終わったか
	if (easeSave != 0)
	{
		//スライドして登場させる
		easeSave = START_EASE - easeX;
		easeSave = std::min<float>(std::max<float>(easeSave, 0), 1);
		transform_.position_.x = -Easing::EaseInQuart(easeSave) * 2;
		easeX += EASE_VAL;
	}
}

//ボタンが押されたときにする処理
void SettingStartButton::Event()
{
	ScreenSplit::SetScreenSplit(playerNum);
	ScreenSplit::SetPlayPerson(playerNum);
	ScreenSplit::SetAllPerson(playerNum + comNum);

	transform_.position_ = XMFLOAT3(0, 0, 0);
	SetImage("Load.png", transform_);

	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_PLAY);
}

//選択された瞬間
void SettingStartButton::IsSelect()
{
	//選択中にする
	ButtonManager::SetNowButton(this);
	//画像変える
	SetImage("SelectCircle.png", transform_);
}

//選択解除された瞬間
void SettingStartButton::IsSelectReleas()
{
	//画像戻す
	SetImage("NormalCircle.png", transform_);
}

void SettingStartButton::SetPlayerNum(int playerNum_)
{
	playerNum = playerNum_;
}

int SettingStartButton::GetPlayerNum()
{
	return playerNum;
}

void SettingStartButton::SetComNum(int comNum_)
{
	comNum = comNum_;
}

int SettingStartButton::GetComNum()
{
	return comNum;
}
