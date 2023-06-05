#pragma once
#include "Engine/Button.h"

class SettingStartButton : public Button
{
	int playerNum;//プレイヤー人数
	int comNum;//COM人数

	float easeX;//スライドして登場するときのイージング値
	float easeSave;//イージングの値保存
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SettingStartButton(GameObject* parent);

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

	//プレイヤーの人数取得
	void SetPlayerNum(int playerNum_);
	
	//プレイヤーの人数取得
	int GetPlayerNum();

	//コンピュータの数取得
	void SetComNum(int comNum_);

	//コンピュータの数取得
	int GetComNum();

};
