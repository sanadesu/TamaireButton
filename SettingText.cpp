#include "SettingText.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Easing.h"

//�R���X�g���N�^
SettingText::SettingText(GameObject* parent)
	: GameObject(parent, "SettingText"), hPict_{-1,-1}
{
}

//������
void SettingText::Initialize()
{
	//�g�p����摜�t�@�C����
	const char* pictFileName[] = { "Select.png", "Load.png" };

	//���[�h
	for (int i = 0; i < Pict::PICT_MAX; i++)
	{
		hPict_[i] = Image::Load(pictFileName[i]);
		assert(hPict_[i] >= 0);
	}

	easeX = 0;
}

//�X�V
void SettingText::Update()
{
	
}

//�`��
void SettingText::Draw()
{
	Transform transText = transform_;
	float x, y, width, height;

	float screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//�X�N���[���̕�
	float screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//�X�N���[���̍���

	const float EASE_VAL = 0.04f;
	float easeSave = 0;

	x = 0;
	y = 0;
	width = 1920.0f;
	height = 500.0f;
	//��
	Image::SetRect(hPict_[Pict::PICT_SELECT], x, y, width, height);
	//transText.scale_ = XMFLOAT3(Easing::EaseOutBack(easeScaleRed), Easing::EaseOutBack(easeScaleRed), 0);
	transText.position_ = XMFLOAT3(((float)width / screenWidth + x / (screenWidth / 2)) - 1, 1 - ((float)height / screenHeight + y / (screenHeight / 2)), 0);
	easeSave = 1.0f - easeX;
	if (easeSave < 0)
		easeSave = 0;
	else if (easeSave > 1)
		easeSave = 1;
	transText.position_.x -= Easing::EaseInQuart(easeSave) * 2;
	
	Image::SetTransform(hPict_[Pict::PICT_SELECT], transText);
	Image::Draw(hPict_[Pict::PICT_SELECT]);

	//�s�N�Z���̒l��transform_.position_�ɕϊ���������H�ł���
	//XMFLOAT3(((float)width / screenWidth + x / (screenWidth / 2)) - 1, 1 - ((float)height / screenHeight + y / (screenHeight / 2)), 0);


	y = 500;
	height = 300.0f;
	//��
	Image::SetRect(hPict_[Pict::PICT_SELECT], x, y, width, height);
	//transText.scale_ = XMFLOAT3(Easing::EaseOutBack(easeScaleRed), Easing::EaseOutBack(easeScaleRed), 0);
	transText.position_ = XMFLOAT3(((float)width / screenWidth + x / (screenWidth / 2)) - 1, 1 - ((float)height / screenHeight + y / (screenHeight / 2)), 0);
	easeSave = 1.2f - easeX;
	if (easeSave < 0)
		easeSave = 0;
	else if (easeSave > 1)
		easeSave = 1;
	transText.position_.x -= Easing::EaseInQuart(easeSave) * 2;
	
	Image::SetTransform(hPict_[Pict::PICT_SELECT], transText);
	Image::Draw(hPict_[Pict::PICT_SELECT]);

	y = 800;
	height = 1080.0f;
	//��
	//Image::SetRect(hPict_[Pict::PICT_SELECT], x, y, width, height);
	////transText.scale_ = XMFLOAT3(Easing::EaseOutBack(easeScaleRed), Easing::EaseOutBack(easeScaleRed), 0);
	//transText.position_ = XMFLOAT3(((float)width / screenWidth + x / (screenWidth / 2)) - 1, 1 - ((float)height / screenHeight + y / (screenHeight / 2)), 0);
	//easeSave = 1.4f - easeX;
	//if (easeSave < 0)
	//	easeSave = 0;
	//else if (easeSave > 1)
	//	easeSave = 1;
	//transText.position_.x -= Easing::EaseInQuart(easeSave) * 2;
	//
	//	
	//Image::SetTransform(hPict_[Pict::PICT_SELECT], transText);
	//Image::Draw(hPict_[Pict::PICT_SELECT]);


	easeX += EASE_VAL;

	//�ނ��������������Œ���
	//SettingButton* pSet = (SettingButton*)FindObject("SettingButton");
	/*if (pSet->IsLoad())
	{
		Image::SetTransform(hPict_[Pict::PICT_LOAD], transform_);
		Image::Draw(hPict_[Pict::PICT_LOAD]);
	}*/
	
}

//�J��
void SettingText::Release()
{
}
