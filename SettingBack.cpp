#include "SettingBack.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"

//�R���X�g���N�^
SettingBack::SettingBack(GameObject* parent)
	: GameObject(parent, "SettingBack"), hPict_(-1)
{
}

//������
void SettingBack::Initialize()
{
	//���[�h
	hPict_ = Image::Load("SelectBack.png");
	assert(hPict_ >= 0);
}

//�X�V
void SettingBack::Update()
{

}

//�`��
void SettingBack::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void SettingBack::Release()
{
}
