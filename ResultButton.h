#pragma once
#include "Engine/Button.h"

//■■シーンを管理するクラス
class ResultButton : public Button
{
	const float RESULT_POX_X = 0.43f;
	const float RESULT_POX_Y = -0.75f;
	int hPict_;
	int buttonID;
public:
	//コンストラクタ
	ResultButton(GameObject* pParent, std::string name, int buttonID_, int screenID_);

	//初期化
	void SubInitialize() override;

	//更新
	void SubUpdate() override;

	void Draw() override;

	//ボタンが押されたときにする処理
	void Event() override;

	//選択された瞬間
	void IsSelect() override;

	//選択解除された瞬間
	void IsSelectReleas() override;

};
