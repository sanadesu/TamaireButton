#pragma once
#include "Engine/Button.h"
#include "TitleScene.h"

//using namespace Button;

//�����V�[�����Ǘ�����N���X
class TitleButton : public Button
{
	enum TitleState
	{
		TITLE,
		RULE,
		OPERATE,
		MAX
	};




	int buttonID;
	int alpha;
	int titleState;
	bool isPush;
	bool isFirstTime;

	TitleScene* pTitle;
	TitleButton* pRuleButton;
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
