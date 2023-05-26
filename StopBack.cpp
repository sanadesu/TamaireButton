#include "StopBack.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "PlayStop.h"

//�R���X�g���N�^
StopBack::StopBack(GameObject* parent)
	: GameObject(parent, "StopBack"), hPict_(-1)
{
}

//������
void StopBack::Initialize()
{
	//���[�h
	hPict_ = Image::Load("StopBack.png");
	assert(hPict_ >= 0);
}

//�X�V
void StopBack::Update()
{
	
}

//�`��
void StopBack::Draw()
{
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	if (pStop->GetIsStopPause() && Direct3D::lr == 0)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//�J��
void StopBack::Release()
{
}