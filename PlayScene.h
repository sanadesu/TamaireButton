#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "Player.h"
#include "Time.h"
#include "UI.h"
#include "Engine/ScreenSplit.h"

//■■シーンを管理するクラス
class PlayScene : public GameObject
{
	int hPict_Back;    //画像
	int hPict_;    //画像番号
	int hSound_;

	const int ALL_BALL = 60;
	const int END_TIME = 7200;
	float time;
	int startTime;
	int playerNumber;
	int groundBall;
	bool isEnd;
	Ball* pBall[80];
	Text* pText;
	UI* pUI;
	//Player* pPlayer[ScreenSplit::GetScreenSplit()];
	Player* pPlayer[4];
	Player* p1;
	Player* p2;
	Ground* pGround;
	Time* pTime;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//消すか
	bool IsDelete();
};