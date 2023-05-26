#include "ReadyText.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "PlayStop.h"

//�R���X�g���N�^
ReadyText::ReadyText(GameObject* parent)
	: GameObject(parent, "ReadyText"), hPict_(-1)
{
}

//������
void ReadyText::Initialize()
{
	//���[�h
	hPict_ = Image::Load("ReadyText.png");
	assert(hPict_ >= 0);
	if (ScreenSplit::GetPlayerPerson() == 2)
	{
		transform_.scale_.y *= 0.5f;
		//transform_.position_.y += 0.05f;
	}
}

//�X�V
void ReadyText::Update()
{

}

//�`��
void ReadyText::Draw()
{
	if (playerNum == Direct3D::lr)
	{
		PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
		if (pStop->GetIsStopReady())
		{
			Image::SetTransform(hPict_, transform_);
			Image::Draw(hPict_);
		}
	}
}

//�J��
void ReadyText::Release()
{
}