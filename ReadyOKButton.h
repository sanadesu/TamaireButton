#pragma once
#include "Engine/Button.h"

class ReadyOKButton : public Button
{
	int screenID;
	int hPict_;
	int playerNum;
	float scaleY;
	bool isReady;
	bool isFirst;
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

	//準備完了したか
	bool GetReady();

	void SetSplit(int split_) { playerNum = split_; }
};
