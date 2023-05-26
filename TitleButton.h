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

	const int COLOR = 255;//��������Ȃ�
	const int ADD_COLOR = 5;//���X�ɕs�����ɂ��Ă���
	const float RULE_BUTTON_POS = 0.87f;//���[���{�^���̏ꏊ
	const float POS_X = 0;//�؂���J�n�ʒu(X)
	const float POS_Y = 780.0f;//�؂���J�n�ʒu(Y)
	const float WIDTH = 1920.0f;//�؂���͈�(��)
	const float HEIGHT = 300.0f;//�؂���͈�(�c)
	const float START_POX_X = 0.43f;
	const float START_POX_Y = -0.67f;


	int buttonID;
	int alpha;
	int titleState;
	bool isPush;

	TitleScene* pTitle;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleButton(GameObject* parent, int arrowID);

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
