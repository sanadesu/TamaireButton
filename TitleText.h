#pragma once
#include "Engine/GameObject.h"
#include "TitlePlayer.h"
#include "Frame.h"
#include "TitleScene.h"

class TitleText : public GameObject
{
	const int RED_TEXT_EASE_START = 10;//[�g]�g��X�^�[�g
	const int WHITE_TEXT_EASE_START = 40;//[��]�g��X�^�[�g	
	const int SLIDE_TEXT_EASE_START = 80;//�X���C�h�X�^�[�g
	const float EASE_SCALE = 0.025f;//[�g��]�̊g���
	const float EASE_MOVE = 0.01f;//�X���C�h�̈ړ���

	int hPict_;    //�摜�ԍ�

	float easeX;
	float easeScaleRed;
	float easeScaleWhite;
	Frame* nowFrame = (Frame*)FindObject("Frame");
	TitleScene* pTitle = (TitleScene*)FindObject("TitleScene");
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleText(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
