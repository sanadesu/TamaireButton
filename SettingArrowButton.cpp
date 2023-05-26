#include "SettingArrowButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "SettingStartButton.h"
#include "Number.h"
#include "Engine/Easing.h"

//コンストラクタ
SettingArrowButton::SettingArrowButton(GameObject* parent,int ID)
	: Button(parent, "SettingButton")
{
	arrowID = ID;
}

void SettingArrowButton::SubInitialize()
{
	easeSave = 1;
	easeX = 0;
	startEase = 0;
	switch (arrowID)
	{
	case 0:
		arrowPosX = LEFT_POS;
		transform_.position_.y = UP_POS;
		break;
	case 1:
		arrowPosX = RIGHT_POS;
		transform_.position_.y = UP_POS;
		transform_.rotate_.z = REVERSE;
		break;
	case 2:
		arrowPosX = LEFT_POS;
		transform_.position_.y = DOWN_POS;
		break;
	case 3:
		arrowPosX = RIGHT_POS;
		transform_.position_.y = DOWN_POS;
		transform_.rotate_.z = REVERSE;
		break;
	default:
		break;
	}
	transform_.position_.x = arrowPosX;

	//hPict_ = Image::Load("SelectTriangle");
	//transform_.scale_ = XMFLOAT3(30, 30, 30);
	SetImage("Triangle.png", transform_);
	if (arrowID == 0)
	{
		SetIsNextSelect(true);
		IsSelect();
		SetIsFirst(this);
	}
	ButtonManager::AddButton((Button*)this,0);
}

////初期化
//void SettingArrowButton::Initialize()
//{
//	
//}

void SettingArrowButton::SubUpdate()
{
	ButtonSwith();
	//動き終わったか
	if (easeSave != 0)
	{
		Number* pNumber1 = (Number*)FindObject("Number1");
		Number* pNumber2 = (Number*)FindObject("Number2");
		//上段下段分ける
		if (arrowID < 2 )
			startEase = 1.0f;
		else
			startEase = 1.2f;

		//スライドして登場させる
		easeSave = startEase - easeX;
		if (easeSave < 0)
			easeSave = 0;
		else if (easeSave > 1)
			easeSave = 1;
		transform_.position_.x = -Easing::EaseInQuart(easeSave) * 2 + arrowPosX;
		
		if (arrowID == 0)
			pNumber1->SetPosition(XMFLOAT3(-Easing::EaseInQuart(easeSave) * 2 + 0.435f, pNumber1->GetPosition().y, pNumber1->GetPosition().z));
		else if(arrowID == 2)
			pNumber2->SetPosition(XMFLOAT3(-Easing::EaseInQuart(easeSave) * 2 + 0.435f, pNumber2->GetPosition().y, pNumber2->GetPosition().z));
		//0.435f = SettingSceneでxの位置指定してる
		

		easeX += EASE_VAL;
	}
	
	/*if (GetIsNextSelect() != GetIsNowSelect())
	{
		SetIsNowSelect(GetIsNextSelect());
		if (GetIsNowSelect())
		{
			IsSelect();
			ButtonManager::SetNowButton(this);
		}
		else
			IsSelectReleas();
	}*/
}

//ボタンが押されたときにする処理
void SettingArrowButton::Event()
{
	SettingStartButton* pStartButton = (SettingStartButton*)FindObject("SettingStartButton");
	Number* pNumber1 = (Number*)FindObject("Number1");
	Number* pNumber2 = (Number*)FindObject("Number2");
	int playerNum = pStartButton->GetPlayerNum();
	int comNum = pStartButton->GetComNum();
	//ナンバークラスから持ってくる
	//ナンバークラスは２つのセッターゲッターと数字の切り替え
	switch (arrowID)
	{
	case 0://人数減らす
		if (playerNum > 1)
			playerNum--;
		if (playerNum > 2)
		{
			comNum = 4 - playerNum;
		}
		else if (playerNum == 2 && comNum % 2 == 1)
		{
			comNum = 2;
		}
		else if (playerNum == 1 && comNum % 2 == 0)
		{
			comNum = 3;
		}
		break;
	case 1://人数増やす
		if (playerNum < 4)
			playerNum++;
		if (playerNum > 2)
		{
			comNum = 4 - playerNum;
		}
		else if (playerNum == 2 && comNum % 2 == 1)
		{
			comNum = 2;
		}
		break;
	case 2://CPU増やす
		if (playerNum <= 2 && comNum >= 2)
		{
			if (comNum > 1)
				comNum -= 2;
		}
		break;
	case 3://CPU減らす
		if (playerNum <= 2 && comNum <= 1)
		{
			if (comNum < 3)
				comNum += 2;
		}
		break;
	default:
		break;
	}

	pStartButton->SetComNum(comNum);
	pStartButton->SetPlayerNum(playerNum);

	pNumber1->SetNum(pStartButton->GetPlayerNum(),0);
	pNumber2->SetNum(pStartButton->GetComNum(), 0);

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
void SettingArrowButton::IsSelect()
{
	//選択中にする
	ButtonManager::SetNowButton(this);
	//画像変える
	SetImage("SelectTriangle.png", transform_);
}

//選択解除された瞬間
void SettingArrowButton::IsSelectReleas()
{
	//画像戻す
	SetImage("Triangle.png", transform_);
}
