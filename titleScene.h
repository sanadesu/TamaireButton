#pragma once
#include "Engine/GameObject.h"
#include "TitlePlayer.h"

//■■シーンを管理するクラス
class TitleScene : public GameObject
{
	static const int MAX_PLAYER = 2;//タイトルに登場させるプレイヤーの数
	static const int BALL_DROP_INTERVAL = 10;//ボールを落とす間隔
	static const int DROP_START_FRAME = 120;//ボールを落とし始めるフレーム数

	int hPict_;    //画像番号
	int hPict_Back;
	int hSound_;    //サウンド番号
	int hSound_Button;    
	int hSound_Move;
	int hModel_; //モデル

	bool isSkip;
	TitlePlayer* pT_Player[MAX_PLAYER];
	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//スキップ
	bool GetIsSkip();
};
