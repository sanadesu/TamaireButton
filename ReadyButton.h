#pragma once
#include "Engine/GameObject.h" 
#include "Engine/ScreenSplit.h"
#include "Player.h"

//■■シーンを管理するクラス
class ReadyButton : public GameObject
{
	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	enum Button
	{
		BUTTON_ASSIST_T,//◎
		BUTTON_ASSIST_F,
		BUTTON_READY,
		BUTTON_MAX
	};

	enum Screen
	{
		SCREEN_ALL,
		SCREEN_LEFT,
		SCREEN_RIGHT,
		SCREEN_LEFT_UP,
		SCREEN_RIGHT_UP,
		SCREEN_LEFT_DOWN,
		SCREEN_RIGHT_DOWN
	};

	int hPict_;    //画像番号
	int hSound_[Sound::SOUND_MAX];    //サウンド番号
	int min;
	int playerNum; //画面
	int button;
	int posX;
	int posY;
	float scaleY;
	bool isAssist;
	bool isStickMove;
	bool isReady;
	Transform buttonTrans;
	Player* pPlayer[4];

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ReadyButton(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetSplit(int split_) { playerNum = split_; }

	bool GetReady();
};
