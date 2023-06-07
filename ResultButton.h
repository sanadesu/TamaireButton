#pragma once
#include "Engine/Button.h"

//�����V�[�����Ǘ�����N���X
class ResultButton : public Button
{
	int hPict_;//�摜
	int buttonID;//�{�^�����ʔԍ�
public:
	//�R���X�g���N�^
	ResultButton(GameObject* pParent, std::string name, int buttonID_, int screenID_);

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
