#include "TitleText.h"
#include"Engine/Camera.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Audio.h"
#include "Engine/Model.h"
#include "Engine/Easing.h"
#include "TitlePlayer.h"
#include <iostream>
#include <vector>
#include <chrono>

//�萔
namespace
{
	static const int RED_TEXT_EASE_START = 10;//[�g]�g��X�^�[�g
	static const int WHITE_TEXT_EASE_START = 40;//[��]�g��X�^�[�g	
	static const int SLIDE_TEXT_EASE_START = 80;//�X���C�h�X�^�[�g
	static const float EASE_SCALE = 0.025f;//[�g��]�̊g���
	static const float EASE_MOVE = 0.01f;//�X���C�h�̈ړ���
}

//�R���X�g���N�^
TitleText::TitleText(GameObject* parent)
	: GameObject(parent, "TitleText"), hPict_(-1)
{
}

//������
void TitleText::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Title.png");
	assert(hPict_ >= 0);
	easeX = 0;
	easeScaleRed = 0;
	easeScaleWhite = 0;
	nowFrame = (Frame*)FindObject("Frame");
	pTitle = (TitleScene*)FindObject("TitleScene");
}

//�X�V
void TitleText::Update()
{
	if (pTitle->GetIsSkip())
	{
		easeScaleRed = EASE_MAX;
		easeScaleWhite = EASE_MAX;
		easeX = EASE_MAX;
	}
	else
	{
		if (nowFrame->GetFrame() > RED_TEXT_EASE_START)
		{
			easeScaleRed += EASE_SCALE;
			if (easeScaleRed > EASE_MAX)
			{
				easeScaleRed = EASE_MAX;
			}
		}
		if (nowFrame->GetFrame() > WHITE_TEXT_EASE_START)
		{
			easeScaleWhite += EASE_SCALE;
			if (easeScaleWhite > EASE_MAX)
			{
				easeScaleWhite = EASE_MAX;
			}
		}
		if (nowFrame->GetFrame() > SLIDE_TEXT_EASE_START)
		{
			easeX += 0.01f;
			if (easeX > EASE_MAX)
			{
				easeX = EASE_MAX;
			}
		}
	}
}

//�`��
void TitleText::Draw()
{
	Transform transText = transform_;
	transText.position_ = XMFLOAT3(0, 0, 0);
	float x,y,width,height;
	
	x = 600.0f;
	y = 0;
	width = 400.0f;
	height = 450.0f;
	transText.position_ = Image::SetRectPos(hPict_, x, y, width, height);
	transText.scale_ = XMFLOAT3(Easing::EaseOutBack(easeScaleRed), Easing::EaseOutBack(easeScaleRed), 0);
	Image::SetTransform(hPict_, transText);
	Image::Draw(hPict_);

	x = 1000.0f;
	transText.position_ = Image::SetRectPos(hPict_, x, y, width, height);
	transText.scale_ = XMFLOAT3(Easing::EaseOutBack(easeScaleWhite), Easing::EaseOutBack(easeScaleWhite), 0);
	Image::SetTransform(hPict_, transText);
	Image::Draw(hPict_);

	x = 300.0f;
	y = 450.0f;
	width = 1300.0f;
	height = 300.0f;
	
	transText.position_ = Image::SetRectPos(hPict_, x, y, width, height);
	transText.position_.x = -Easing::EaseOutElastic(easeX) * 1.7f + 1.7f;
	Image::SetTransform(hPict_, transText);
	Image::Draw(hPict_);
}

//�J��
void TitleText::Release()
{
}
