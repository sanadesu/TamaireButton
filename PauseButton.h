#pragma once
#include "Engine/Button.h"
#include "PlayStop.h"
#include "StartSignal.h"
class PauseButton :
    public Button
{
	int hPict_;//画像
	int buttonID;//ボタン識別番号
	PlayStop* pPlayStop;
	StartSignal* pStartSignal;
public:
	//コンストラクタ
	PauseButton(GameObject* pParent, std::string name, int buttonID_, int screenID_);

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

