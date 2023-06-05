#pragma once
#include "Engine/Button.h"

class SettingStartButton : public Button
{
	int playerNum;//�v���C���[�l��
	int comNum;//COM�l��

	float easeX;//�X���C�h���ēo�ꂷ��Ƃ��̃C�[�W���O�l
	float easeSave;//�C�[�W���O�̒l�ۑ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SettingStartButton(GameObject* parent);

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

	//�v���C���[�̐l���擾
	void SetPlayerNum(int playerNum_);
	
	//�v���C���[�̐l���擾
	int GetPlayerNum();

	//�R���s���[�^�̐��擾
	void SetComNum(int comNum_);

	//�R���s���[�^�̐��擾
	int GetComNum();

};
