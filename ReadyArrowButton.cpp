#include "ReadyArrowButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/SceneManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "AssistReady.h"
#include "PlayStop.h"
//コンストラクタ
ReadyArrowButton::ReadyArrowButton(GameObject* parent, const string name, int buttonID_, int screenID_)
	: Button(parent, "ReadyArrowButton")
{
	arrowID = buttonID_;
	screenID = screenID_;
	SetScreenID(screenID_);
}

ReadyArrowButton::ReadyArrowButton(GameObject* parent, int buttonID_)
	: Button(parent, "ReadyArrowButton")
{
}

void ReadyArrowButton::SubInitialize()
{
	hPict_ = Image::Load("Triangle.png");
	//ロードされたか確認
	assert(hPict_ >= 0);

	if (arrowID % 2 == 1)
	{
		transform_.rotate_.z = 180;
		arrowPos = 1475;
	}
	else
	{
		arrowPos = 1000;
		SetIsNextSelect(true);
		IsSelect();
		SetIsFirst(this);
	}

	


	const char* PlayerName[] = { "Player", "Player2", "Player3", "Player4" };
	pPlayer = (Player*)FindObject(PlayerName[arrowID]);

	if (ScreenSplit::GetPlayerPerson() != 3)
	{
		min = ScreenSplit::GetPlayerPerson() - 1;
	}
	else
	{
		min = 3;
	}

	if (ScreenSplit::GetPlayerPerson() == 2)
	{
		scaleY = 0.5f;
		posY = 500;
		posX = 10;
	}
	else
	{
		scaleY = 1;
		posY = 465;
		posX = 0;
	}


	transform_.position_ = Image::PixelPos(hPict_, arrowPos + posX, posY);
	transform_.scale_ = XMFLOAT3(0.5f,scaleY * 0.5f,0.5f);

	isAssist = true;
}

void ReadyArrowButton::SubUpdate()
{
	ButtonSwith();
	if (a == 0)
	{
		a = 1;
		ButtonManager::AddButton((Button*)this, playerNum - min);
		this->SetScreenID(playerNum - min);
	}
}

void ReadyArrowButton::Draw()
{
	//描画
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	if (playerNum == Direct3D::lr && pStop->GetIsStopReady())
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//ボタンが押されたときにする処理
void ReadyArrowButton::Event()
{
	AssistReady* pAssistReady = (AssistReady*)FindObject("AssistReady");
	if (playerNum == min || (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, playerNum - min)))
	{
		switch (arrowID)
		{
			case 0:
				pPlayer->SetIsAssist(false);
				pAssistReady->SetAssistText(playerNum - min, 256);
				break;
			case 1:
				pPlayer->SetIsAssist(true);
				pAssistReady->SetAssistText(playerNum - min, 0);
				break;
			default:
				break;
		}
	}


	
}

//選択された瞬間
void ReadyArrowButton::IsSelect()
{
	//選択中にする
	ButtonManager::SetNowButton(this);
	//画像変える
	hPict_ = Image::Load("SelectTriangle.png");
	//SetImage("SelectTriangle.png", transform_);
}

//選択解除された瞬間
void ReadyArrowButton::IsSelectReleas()
{
	//画像戻す
	hPict_ = Image::Load("Triangle.png");
	//SetImage("Triangle.png", transform_);
}

int ReadyArrowButton::GetScreenID()
{
	return playerNum - min;
}

int ReadyArrowButton::GetPlayerNum()
{
	return playerNum;
}
