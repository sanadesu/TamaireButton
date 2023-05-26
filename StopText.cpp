#include "StopText.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "PlayStop.h"

//�R���X�g���N�^
StopText::StopText(GameObject* parent)
	: GameObject(parent, "StopText"), hPict_(-1)
{
}

//������
void StopText::Initialize()
{
	//���[�h
	hPict_ = Image::Load("StopText.png");
	assert(hPict_ >= 0);
}

//�X�V
void StopText::Update()
{

}

//�`��
void StopText::Draw()
{
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	if (pStop->GetIsStopPause() && Direct3D::lr == 0)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//�J��
void StopText::Release()
{
}