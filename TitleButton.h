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
	int alpha;			//ボタンの透明度、だんだん不透明になる
	int titleState;		//なんの画面か
	bool isPush;		//押せるか
	bool isFirstTime;	//1フレーム目か

	TitleScene* pTitle;
	TitleButton* pRuleButton;
	Frame* nowFrame;
public:

	//コンストラクタ
	TitleButton(GameObject* pParent, const std::string name, int buttonID_, int screenID_);

	//初期化
	void SubInitialize() override;

	//更新
	void SubUpdate() override;


//ボタンが押されたときにする処理
	void Event() override;

	//選択された瞬間
	void IsSelect() override;

	//選択解除された瞬間
	void IsSelectReleas() override;

	//状態取得
	int GetTitleState();
};
