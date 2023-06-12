#pragma once
#include "GameObject.h"

//■■シーンを管理するクラス
class Frame : public GameObject
{
	int frame;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Frame(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//フレーム数
	int GetFrame();
};
