#include "ReadyOKButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "AssistReady.h"
#include "PlayStop.h"
#include "ReadyArrowButton.h"
#include "Engine/ScreenSplit.h"
//�R���X�g���N�^
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
	playerNum = 0;
	if (ScreenSplit::GetPlayerPerson() == 2)
	{
		scaleY = 0.5f;
	}
	else
	{
		scaleY = 1;
	}
	isFirst = true;
	transform_.position_.y = -0.3f;
	transform_.scale_.y = scaleY;

	SetIsNextSelect(true);
	IsSelect();
	SetIsFirst(this);
}

void ReadyOKButton::SubUpdate()
{
	if (isFirst)
	{
		isFirst = false;
		ButtonManager::AddButton((Button*)this, screenID);
		this->SetScreenID(screenID);
	}
	ButtonSwith();
}

void ReadyOKButton::Draw()
{
	//�`��
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	if (playerNum == Direct3D::lr && pStop->GetIsStopReady())
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//�{�^���������ꂽ�Ƃ��ɂ��鏈��
void ReadyOKButton::Event()
{
	AssistReady* pAssistReady = (AssistReady*)FindObject("AssistReady");
	isReady = true;
	//����
	pAssistReady->ReadyKill(screenID);
}

//�I�����ꂽ�u��
void ReadyOKButton::IsSelect()
{
	//�I�𒆂ɂ���
	ButtonManager::SetNowButton(this);
	//�摜�ς���
	hPict_ = Image::Load("ReadySelect.png");
}

//�I���������ꂽ�u��
void ReadyOKButton::IsSelectReleas()
{
	//�摜�߂�
	hPict_ = Image::Load("ReadyButton.png");
}

bool ReadyOKButton::GetReady()
{
	return isReady;
}

