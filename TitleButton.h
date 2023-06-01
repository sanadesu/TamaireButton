#pragma once
#include "Engine/Button.h"
#include "TitleScene.h"

//using namespace Button;

//■■シーンを管理するクラス
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
