#pragma once
#include "Engine/Button.h"
#include "PlayStop.h"
#include "Time.h"
class PauseButton :
    public Button
{
	int hPict_;//�摜
	int buttonID;//�{�^�����ʔԍ�
	PlayStop* pPlayStop;
	Time* pTime;
public:
	//�R���X�g���N�^
	PauseButton(GameObject* pParent, std::string name, int buttonID_, int screenID_);

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

