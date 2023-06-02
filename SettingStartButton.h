#pragma once
#include "Engine/Button.h"

//using namespace Button;

//�����V�[�����Ǘ�����N���X
class SettingStartButton : public Button
{
	int playerNum;
	int comNum;

	float easeX;
	float easeSave;
	bool isStickMove;
	bool isLoad;
	std::pair<float, float> framePos[5];

	Transform transButton;
	Transform transPlayerNum;
	Transform transComNum;
public:
	int arrowID;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SettingStartButton(GameObject* parent);

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

	//�v���C���[�̐l���擾
	void SetPlayerNum(int playerNum_);
	
	//�v���C���[�̐l���擾
	int GetPlayerNum();

	//�R���s���[�^�̐��擾
	void SetComNum(int comNum_);

	//�R���s���[�^�̐��擾
	int GetComNum();

};
