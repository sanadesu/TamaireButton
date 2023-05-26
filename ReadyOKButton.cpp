#include "ReadyOKButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "AssistReady.h"
#include "PlayStop.h"
#include "ReadyArrowButton.h"
//コンストラクタ
ReadyOKButton::ReadyOKButton(GameObject* parent, const string name, int buttonID_, int screenID_)
	: Button(parent, "ReadyOKButton"),hPict_(-1)
{
	SetScreenID(screenID_);
}

void ReadyOKButton::SubInitialize()
{
	hPict_ = Image::Load("ReadyButton.png");
	assert(hPict_ >= 0);


	
	
}

void ReadyOKButton::SubUpdate()
{
	ButtonSwith();
	if (a == 0)
	{
		ReadyArrowButton* pReadyArrowButton = (ReadyArrowButton*)FindObject("ReadyArrowButton");
		ButtonManager::AddButton((Button*)this, pReadyArrowButton->GetScreenID()); 
		this->SetScreenID(pReadyArrowButton->GetScreenID());
	}
}

void ReadyOKButton::Draw()
{
	//描画
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	ReadyArrowButton* pArrowButton = (ReadyArrowButton*)FindObject("ReadyArrowButton");
	if (pArrowButton->GetPlayerNum() == Direct3D::lr && pStop->GetIsStopReady())
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//ボタンが押されたときにする処理
void ReadyOKButton::Event()
{

}

//選択された瞬間
void ReadyOKButton::IsSelect()
{
	//選択中にする
	ButtonManager::SetNowButton(this);
	//画像変える
	SetImage("ReadyButton.png", transform_);
}

//選択解除された瞬間
void ReadyOKButton::IsSelectReleas()
{
	//画像戻す
	SetImage("ReadyButton.png", transform_);
}
