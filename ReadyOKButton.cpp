#include "ReadyOKButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "AssistReady.h"
#include "PlayStop.h"
#include "ReadyArrowButton.h"
#include "Engine/ScreenSplit.h"
//コンストラクタ
ReadyOKButton::ReadyOKButton(GameObject* parent, const string name, int buttonID_, int screenID_)
	: Button(parent, "ReadyOKButton"),hPict_(-1)
{
	screenID = screenID_;
	SetScreenID(screenID_);
}

void ReadyOKButton::SubInitialize()
{
	hPict_ = Image::Load("ReadyButton.png");
	assert(hPict_ >= 0);
	first = 0;
	playerNum = 0;
	if (ScreenSplit::GetPlayerPerson() == 2)
	{
		scaleY = 0.5f;
	}
	else
	{
		scaleY = 1;
	}
	transform_.position_.y = -0.3f;
	transform_.scale_.y = scaleY;
	/*SetIsNextSelect(true);
	IsSelect();
	SetIsFirst(this);*/
}

void ReadyOKButton::SubUpdate()
{
	ButtonSwith();
	if (first == 0)
	{
		ButtonManager::AddButton((Button*)this, screenID);
		this->SetScreenID(screenID);
		first = 1;
	}
}

void ReadyOKButton::Draw()
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
void ReadyOKButton::Event()
{
	AssistReady* pAssistReady = (AssistReady*)FindObject("AssistReady");
	isReady = true;
	//消す
	pAssistReady->ReadyKill(screenID);
	//KillMe();
}

//選択された瞬間
void ReadyOKButton::IsSelect()
{
	//選択中にする
	ButtonManager::SetNowButton(this);
	//transform_.position_.x = 0.5f;
	//画像変える
	hPict_ = Image::Load("ReadySelect.png");
	//SetImage("ReadySelect.png", transform_);
}

//選択解除された瞬間
void ReadyOKButton::IsSelectReleas()
{
	//画像戻す
	hPict_ = Image::Load("ReadyButton.png");
	//SetImage("ReadyButton.png", transform_);
}

bool ReadyOKButton::GetReady()
{
	return isReady;
}

