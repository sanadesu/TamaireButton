#include "ReadyOKButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "AssistReady.h"
#include "PlayStop.h"
#include "ReadyArrowButton.h"
//�R���X�g���N�^
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
	//�`��
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	ReadyArrowButton* pArrowButton = (ReadyArrowButton*)FindObject("ReadyArrowButton");
	if (pArrowButton->GetPlayerNum() == Direct3D::lr && pStop->GetIsStopReady())
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//�{�^���������ꂽ�Ƃ��ɂ��鏈��
void ReadyOKButton::Event()
{

}

//�I�����ꂽ�u��
void ReadyOKButton::IsSelect()
{
	//�I�𒆂ɂ���
	ButtonManager::SetNowButton(this);
	//�摜�ς���
	SetImage("ReadyButton.png", transform_);
}

//�I���������ꂽ�u��
void ReadyOKButton::IsSelectReleas()
{
	//�摜�߂�
	SetImage("ReadyButton.png", transform_);
}
