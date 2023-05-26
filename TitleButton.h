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

	const int COLOR = 255;//透明じゃない
	const int ADD_COLOR = 5;//徐々に不透明にしていく
	const float RULE_BUTTON_POS = 0.87f;//ルールボタンの場所
	const float POS_X = 0;//切り取り開始位置(X)
	const float POS_Y = 780.0f;//切り取り開始位置(Y)
	const float WIDTH = 1920.0f;//切り取り範囲(横)
	const float HEIGHT = 300.0f;//切り取り範囲(縦)
	const float START_POX_X = 0.43f;
	const float START_POX_Y = -0.67f;


	int buttonID;
	int alpha;
	int titleState;
	bool isPush;

	TitleScene* pTitle;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleButton(GameObject* parent, int arrowID);

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
