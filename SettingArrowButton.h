#pragma once
#include "Engine/Button.h"

//using namespace Button;

//�����V�[�����Ǘ�����N���X
class SettingArrowButton : public Button
{
	enum PlayerNum
	{

	};

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

	int arrowID;//���{�^��ID
	
	float easeX;//�X���C�h���ēo�ꂷ��Ƃ��̃C�[�W���O�l
	float easeSave;//�C�[�W���O�̒l�ۑ�
	float startEase;//�X���C�h�J�n�ʒu
	float arrowPosX;//���{�^���̏ꏊ
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SettingArrowButton(GameObject* parent, int arrowID);

	//������
	void SubInitialize() override;

	//�X�V
	void SubUpdate() override;

	//�{�^���������ꂽ�Ƃ��ɂ��鏈��
	void Event() override;

	//�I�����ꂽ�u��
	void IsSelect() override;

	//�I���������ꂽ�u��
	void IsSelectReleas() override;
};
