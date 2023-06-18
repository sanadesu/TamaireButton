#include "TitleButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "SettingStartButton.h"
#include "Engine/Number.h"
#include "Engine/Easing.h"
#include "Rule.h"
#include "Engine/Input.h"

//�萔
namespace
{
	static const int COLOR = 255;								//��������Ȃ�
	static const int ADD_COLOR = 5;								//���X�ɕs�����ɂ��Ă���
	static const int BUTTON_ALPHA = 120;						//�{�^����������悤�ɂ���J�n�t���[����
	static const float RULE_BUTTON_POS = 0.87f;					//���[���{�^���̏ꏊ
	static const float POS_X = 0;								//�؂���J�n�ʒu(X)
	static const float POS_Y = 780.0f;							//�؂���J�n�ʒu(Y)
	static const float WIDTH = 1920.0f;							//�؂���͈�(��)
	static const float HEIGHT = 300.0f;							//�؂���͈�(�c)
	static const XMFLOAT2 START_POS = XMFLOAT2(0.43f, -0.67f);	//�{�^���̏ꏊ
}

//�R���X�g���N�^
TitleButton::TitleButton(GameObject* pParent, const std::string name, int buttonID_, int screenID_)
	: Button(pParent, "TitleButton")
{
	buttonID = buttonID_;
}

//������
void TitleButton::SubInitialize()
{
	if (buttonID == START_BUTTON)
	{
		transform_.position_ = XMFLOAT3(-START_POS.x, START_POS.y, 0);
		SetImage("StartButton.png", transform_);
		//�I�𒆂ɂ���
		SetIsNextSelect(true);
		IsSelect();
		SetIsFirst(this);
	}
	else
	{
		transform_.position_ = XMFLOAT3(START_POS.x, START_POS.y, 0);
		SetImage("RuleButton.png", transform_);
	}
	
	//�{�^���ǉ�
	ButtonManager::AddButton((Button*)this,0);

	alpha = 0;
	SetAlpha(alpha);//�����ɂ���
	titleState = 0;
	isPush = false;
	pTitle = (TitleScene*)FindObject("TitleScene");
	nowFrame = (Frame*)FindObject("Frame");
	isFirstTime = true;
}

//�X�V
void TitleButton::SubUpdate()
{
	//�ŏ�������肽������
	if (isFirstTime)
	{
		pRuleButton = (TitleButton*)FindObject("TitleRuleButton");
		isFirstTime = false;
	}
	
	//�I���{�^���ύX
	if(pRuleButton->GetTitleState() == TITLE)
		ButtonSwith();
	
	//���X�Ɍ�����悤�ɂ���
	if (nowFrame->GetFrame() >= BUTTON_ALPHA || pTitle->GetIsSkip())
	{
		if (alpha < COLOR)
			alpha += ADD_COLOR;
		SetAlpha(alpha);
	}

	//�{�^�����s�����ɂȂ�����{�^����������
	if (alpha >= COLOR)
		isPush = true;

	//�^�C�g���̓������X�L�b�v������
	if (pTitle->GetIsSkip() && (Input::IsKeyDown(DIK_SPACE) || Input::IsPadButtonDown(XINPUT_GAMEPAD_A)) && alpha < COLOR)
	{
		alpha = COLOR;
		isPush = false;
	}
}

//�{�^���������ꂽ�Ƃ��ɂ��鏈��
void TitleButton::Event()
{
	//�����Ȃ�(���[���J���Ă���)
	if (isPush == false)
		return;

	if (buttonID == START_BUTTON)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SET);
	}
	else
	{
		titleState++;
		titleState = titleState % TitleState::MAX;

		Rule* pRule = (Rule*)FindObject("Rule");

		switch (titleState)
		{
		case TitleState::TITLE:
			pRule->SetRuleImage("NO");
			break;
		case TitleState::RULE:
			pRule->SetRuleImage("Rule.png");
			break;
		case TitleState::OPERATE:
			pRule->SetRuleImage("Operate.png");
			break;
		default:
			break;
		}
	}
}

//�I�����ꂽ�u��
void TitleButton::IsSelect()
{
	if (buttonID == START_BUTTON)
	{
		//�I�𒆂ɂ���
		ButtonManager::SetNowButton(this);
		//�摜�ς���
		SetImage("StartSelect.png", transform_);
	}
	else
	{
		//�I�𒆂ɂ���
		ButtonManager::SetNowButton(this);
		//�摜�ς���
		SetImage("RuleSelect.png", transform_);
	}
}

//�I���������ꂽ�u��
void TitleButton::IsSelectReleas()
{
	//�摜�߂�
	if (buttonID == START_BUTTON)
		SetImage("StartButton.png", transform_);
	else
		SetImage("RuleButton.png", transform_);
}

//��Ԏ擾
int TitleButton::GetTitleState()
{
	return titleState;
}