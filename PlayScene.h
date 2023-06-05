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
	
	Ball* pBall[80];//ボールの個数
	Player* pPlayer[4];//プレイヤー
	Ground* pGround;//フィールド
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