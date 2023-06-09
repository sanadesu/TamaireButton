#include "SettingText.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Easing.h"

//�萔
namespace
{
	static const int ROU_COUNT = 2;
	static const float TOP_TEXT_HEIGHT = 500.0f;//1�s�ڂ̕\���͈�(�c)
	static const float BOTTOM_TEXT_Y = 500.0f;//2�s�ڂ̏�[�̒l
	static const float BOTTOM_TEXT_HEIGHT = 300.0f;//2�s�ڂ̕\���͈�(�c)
	static const float TEXT_WIDTH = 1920.0f;//�\���͈�(��)
	static const float EASE_START_TOP = 1.0f;//1�s�ڂ̃C�[�W���O
	static const float EASE_START_BOTTOM = 1.2f;//2�s�ڂ̃C�[�W���O
	static const float EASE_VAL = 0.04f;//�C�[�W���O�̕ω���

}

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

	easeSave = 0;
	easeX = 0;
	float y[] = { 0,BOTTOM_TEXT_Y };
	float heigght[] = {TOP_TEXT_HEIGHT ,BOTTOM_TEXT_HEIGHT};
	float start[] = { EASE_START_TOP ,EASE_START_BOTTOM };
	for (int i = 0; i < ROU_COUNT; i++)
	{
		textY[i] = y[i];
		textHeight[i] = heigght[i]; 
		easeStart[i] = start[i];
	}
}

//�X�V
void SettingText::Update()
{
	
}

//�`��
void SettingText::Draw()
{
	for (int i = 0; i < ROU_COUNT; i++)
	{
		transform_.position_ = Image::SetRectPos(hPict_[Pict::PICT_SELECT], 0, textY[i], TEXT_WIDTH, textHeight[i]);

		easeSave = easeStart[i] - easeX;
		if (easeSave < 0)
			easeSave = 0;
		else if (easeSave > 1)
			easeSave = 1;

		transform_.position_.x -= Easing::EaseInQuart(easeSave) * 2;

		Image::SetTransform(hPict_[Pict::PICT_SELECT], transform_);
		Image::Draw(hPict_[Pict::PICT_SELECT]);
	}

	easeX += EASE_VAL;
}

//�J��
void SettingText::Release()
{
}
