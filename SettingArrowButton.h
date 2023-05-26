#pragma once
#include "Engine/Button.h"

//using namespace Button;

//�����V�[�����Ǘ�����N���X
class SettingArrowButton : public Button
{
	enum Pict
	{
		PICT_BUTTON,
		PICT_NUMBER,
		PICT_MAX
	};

	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	//int hPict_;    //�摜�ԍ�
	//int hSound_;    //�T�E���h�ԍ�


	const int REVERSE = 180;//�{�^�����]

	const float EASE_VAL = 0.04f;//�C�[�W���O�̕ω���(�X���C�h)
	//�{�^���̈ʒu
	const float LEFT_POS = 0.085f;
	const float RIGHT_POS = 0.78f;
	const float UP_POS = 0.38f;
	const float DOWN_POS = -0.21f;

	int arrowID;
	
	float easeX;
	float easeSave;
	float startEase;
	float arrowPosX;

	bool isStickMove;
	bool isLoad;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SettingArrowButton(GameObject* parent, int arrowID);

	//������
	void SubInitialize() override;

	//�X�V
	void SubUpdate() override;

	////�`��
	//void Draw() override;

	////�J��
	//void Release() override;

	//bool IsLoad();


//�{�^���������ꂽ�Ƃ��ɂ��鏈��
	void Event() override;

	//�I�����ꂽ�u��
	void IsSelect() override;

	//�I���������ꂽ�u��
	void IsSelectReleas() override;
};
