#pragma once
#include "Engine/Button.h"
#include "TitleScene.h"
#include "Player.h"

class ReadyArrowButton : public Button
{
	int a = 0;
	int hPict_;
	int arrowID;
	int screenID;
	int min;
	int posX;
	int posY;
	int playerNum;
	int arrowPos;
	float scaleY;
	Player* pPlayer;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ReadyArrowButton(GameObject* parent,const string name, int buttonID_,int screenID);

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ReadyArrowButton(GameObject* parent, int buttonID_);

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


	void SetSplit(int split_) { playerNum = split_; }

	int GetScreenID() override;

	int GetPlayerNum();
};
