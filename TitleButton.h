#pragma once
#include "Engine/Button.h"
#include "TitleScene.h"
#include "Engine/Frame.h"

class TitleButton : public Button
{
	enum TitleState
	{
		TITLE,
		RULE,
		OPERATE,
		MAX
	};

	enum ButtonID
	{
		START_BUTTON,
		RULE_BUTTON
	};
	int buttonID;
	int alpha;			//�{�^���̓����x�A���񂾂�s�����ɂȂ�
	int titleState;		//�Ȃ�̉�ʂ�
	bool isPush;		//�����邩
	bool isFirstTime;	//1�t���[���ڂ�

	TitleScene* pTitle;
	TitleButton* pRuleButton;
	Frame* nowFrame;
public:

	//�R���X�g���N�^
	TitleButton(GameObject* pParent, const std::string name, int buttonID_, int screenID_);

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

	//��Ԏ擾
	int GetTitleState();
};
