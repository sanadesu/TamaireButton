#include "SettingStartButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Number.h"
#include "Engine/Easing.h"
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
	startEase = 1.4f;
	Number* pNumber1 = (Number*)FindObject("Number1");
	Number* pNumber2 = (Number*)FindObject("Number2");
	playerNum = 1;
	comNum = 3;
	pNumber1->SetNum(playerNum, 0.06f);
	pNumber2->SetNum(comNum, 0.06f);

	transform_.position_.y = -0.7f;

	//hPict_ = Image::Load("SelectTriangle");
	//transform_.scale_ = XMFLOAT3(30, 30, 30);
	SetImage("NormalCircle.png", transform_);

	ButtonManager::AddButton((Button*)this,0);
}

void SettingStartButton::SubUpdate()
{
	ButtonSwith();
	//動き終わったか
	if (easeSave != 0)
	{
		//スライドして登場させる
		easeSave = startEase - easeX;

		easeSave = std::min<float>(std::max<float>(easeSave, 0), 1);
		/*if (easeSave < 0)
			easeSave = 0;
		else if (easeSave > 1)
			easeSave = 1;*/
		transform_.position_.x = -Easing::EaseInQuart(easeSave) * 2;
		easeX += EASE_VAL;
	}
}

//ボタンが押されたときにする処理
void SettingStartButton::Event()
{
	//後で色選択とかチーム分けとか追加、協力と対戦ができるように
			//スタート
	//ナンバークラスから持ってくる
	ScreenSplit::SetScreenSplit(playerNum);
	ScreenSplit::SetPlayPerson(playerNum);
	ScreenSplit::SetAllPerson(playerNum + comNum);

	transform_.position_ = XMFLOAT3(0, 0, 0);
	SetImage("Load.png", transform_);

	//ロード画像に変更したい？
	//isLoad = true;
	//別クラス？
	//hPict_[Pict::PICT_BUTTON] = Image::Load("Load.png");
	//assert(hPict_[Pict::PICT_BUTTON] >= 0);

	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_PLAY);
	//クラス増やす
	//矢印なら左右
	//矢印関数作る
	//決定なら個別の処理
	//これはシーン切り替え
	//スタートボタンクラスに移動
	//ScreenSplit::SetScreenSplit(playerNum);
	//ScreenSplit::SetPlayPerson(playerNum);
	//ScreenSplit::SetAllPerson(playerNum + comNum);

	////ロードクラス作るどっかに
	////ロード画像に変更したい？
	//isLoad = true;
	////別クラス？
	////hPict_[Pict::PICT_BUTTON] = Image::Load("Load.png");
	////assert(hPict_[Pict::PICT_BUTTON] >= 0);
	//SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//pSceneManager->ChangeScene(SCENE_ID_PLAY);

	//矢印
	//rotate.z == 0 なら減らす関数　左スクロール
	//rotate.z == 180なら増やす関数　右スクロール
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
