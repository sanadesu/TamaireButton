#include "ReadyBack.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "PlayStop.h"

//�R���X�g���N�^
ReadyBack::ReadyBack(GameObject* parent)
	: GameObject(parent, "ReadyBack"), hPict_(-1)
{
}

//������
void ReadyBack::Initialize()
{
	//���[�h
	hPict_ = Image::Load("StopBack.png");
	assert(hPict_ >= 0);

}

//�X�V
void ReadyBack::Update()
{

}

//�`��
void ReadyBack::Draw()
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
void ReadyBack::Release()
{
}

void ReadyBack::BlackBack()
{
	hPict_ = Image::Load("BlackBack.png");
	assert(hPict_ >= 0);
}
