#pragma once
#include "Engine/Button.h"

//using namespace Button;

//■■シーンを管理するクラス
class ReadyOKButton : public Button
{
	int a = 0;
	int hPict_;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ReadyOKButton(GameObject* parent, const std::string name, int buttonID_, int screenID_);

	//初期化
	void SubInitialize() override;

	//更新
	void SubUpdate() override;

	//描画
	void Draw() override;

	//ボタンが押されたときにする処理
	void Event() override;

	//選択された瞬間
	void IsSelect() override;

	//選択解除された瞬間
	void IsSelectReleas() override;
};
