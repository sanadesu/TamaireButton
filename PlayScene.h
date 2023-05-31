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
	int hPict_;    //画像番号
	int hSound_;//音

	const int ALL_BALL = 60;//ボールの数
	const int END_TIME = 7200;//ゲーム時間
	const float VOLUME = 0.7f;//音量
	Ball* pBall[80];
	Player* pPlayer[4];
	Ground* pGround;
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
};