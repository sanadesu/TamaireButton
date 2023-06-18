#pragma once
#include "Engine/GameObject.h" 

class TitleBall : public GameObject
{
	int hModel_;    //モデル番号
	float easeY;	//イージングの値
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
