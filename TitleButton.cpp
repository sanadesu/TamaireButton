#include "TitleButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "SettingStartButton.h"
#include "Engine/Number.h"
#include "Engine/Easing.h"
#include "Frame.h"
#include "Rule.h"
#include "Engine/Input.h"

//定数
namespace
{
	static const int COLOR = 255;//透明じゃない
	static const int ADD_COLOR = 5;//徐々に不透明にしていく
	static const int BUTTON_ALPHA = 120;//ボタンを見えるようにする開始フレーム数
	static const float RULE_BUTTON_POS = 0.87f;//ルールボタンの場所
	static const float POS_X = 0;//切り取り開始位置(X)
	static const float POS_Y = 780.0f;//切り取り開始位置(Y)
	static const float WIDTH = 1920.0f;//切り取り範囲(横)
	static const float HEIGHT = 300.0f;//切り取り範囲(縦)
	static const float START_POX_X = 0.43f;
	static const float START_POX_Y = -0.67f;
}

//コンストラクタ
TitleButton::TitleButton(GameObject* pParent, const std::string name, int buttonID_, int screenID_)
	: Button(pParent, "TitleButton")
{
	buttonID = buttonID_;
}

void TitleButton::SubInitialize()
{
	if (buttonID == 0)
	{
		transform_.position_ = XMFLOAT3(-START_POX_X, START_POX_Y, 0);
		SetImage("StartButton.png", transform_);
		SetIsNextSelect(true);
		IsSelect();
		SetIsFirst(this);
	}
	else
	{
		transform_.position_ = XMFLOAT3(START_POX_X, START_POX_Y, 0);
		SetImage("RuleButton.png", transform_);
	}
	
	ButtonManager::AddButton((Button*)this,0);

	alpha = 0;
	SetAlpha(alpha);
	titleState = 0;
	isPush = false;
	pTitle = (TitleScene*)FindObject("TitleScene");
	isFirstTime = true;
}

void TitleButton::SubUpdate()
{
	//最初だけやりたい処理
	if (isFirstTime)
	{
		pRuleButton = (TitleButton*)FindObject("TitleRuleButton");
		isFirstTime = false;
	}
	
	if(pRuleButton->GetTitleState() == TITLE)
		ButtonSwith();
	
	Frame* nowFrame = (Frame*)FindObject("Frame");
	//徐々に見えるようにする
	if (nowFrame->GetFrame() >= BUTTON_ALPHA || pTitle->GetIsSkip())
	{
		if (alpha < COLOR)
			alpha += ADD_COLOR;
		SetAlpha(alpha);
	}

	if (alpha >= COLOR)
		isPush = true;
	if (pTitle->GetIsSkip() && (Input::IsKeyDown(DIK_SPACE) || Input::IsPadButtonDown(XINPUT_GAMEPAD_A)) && alpha < COLOR)
	{
		alpha = COLOR;
		isPush = false;
	}
	
}

//ボタンが押されたときにする処理
void TitleButton::Event()
{

	if (isPush )
	{
		if (buttonID == 0)
		{
			if (alpha >= COLOR)
			{
				SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
				pSceneManager->ChangeScene(SCENE_ID_SET);
			}
		}
		else
		{
			titleState++;
			titleState = titleState % TitleState::MAX;

			Rule* pRule;
			pRule = (Rule*)FindObject("Rule");

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
}

//選択された瞬間
void TitleButton::IsSelect()
{
	if (buttonID == 0)
	{
		//選択中にする
		ButtonManager::SetNowButton(this);
		//画像変える
		SetImage("StartSelect.png", transform_);
	}
	else
	{
		//選択中にする
		ButtonManager::SetNowButton(this);
		//画像変える
		SetImage("RuleSelect.png", transform_);
	}
	
}

//選択解除された瞬間
void TitleButton::IsSelectReleas()
{
	//画像戻す
	if (buttonID == 0)
		SetImage("StartButton.png", transform_);
	else
		SetImage("RuleButton.png", transform_);

}

int TitleButton::GetTitleState()
{
	return titleState;
}