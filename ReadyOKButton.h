#pragma once
#include "Engine/Button.h"

//using namespace Button;

//�����V�[�����Ǘ�����N���X
class ReadyOKButton : public Button
{
	int a = 0;
	int hPict_;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ReadyOKButton(GameObject* parent, const std::string name, int buttonID_, int screenID_);

	//������
	void SubInitialize() override;

	//�X�V
	void SubUpdate() override;

	//�`��
	void Draw() override;

	//�{�^���������ꂽ�Ƃ��ɂ��鏈��
	void Event() override;

	//�I�����ꂽ�u��
	void IsSelect() override;

	//�I���������ꂽ�u��
	void IsSelectReleas() override;
};
