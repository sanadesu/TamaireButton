#pragma once
#include "Engine/GameObject.h" 

//■■シーンを管理するクラス
class TitleBall : public GameObject
{
	int hModel_;    //モデル番号

	const int DOWN_LIMIT = -40;//ボールを消す高さ
	const int RANGE_X = 600;//ボールを落とす範囲(横)
	const int RANGE_Z = 100;//ボールを落とす範囲(奥)
	const int SIZE = 4;//ボールの大きさ

	const float DOWN_SPEAD = 0.005f;//ボールが落ちる速さ

	float easeY;
	//std::vector<int> ballDrop;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleBall(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
