#pragma once
#include "Engine/GameObject.h"
#include "Time.h"
//■■シーンを管理するクラス
class Result : public GameObject
{

	Time* pTime;
	bool isFirst;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Result(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};
