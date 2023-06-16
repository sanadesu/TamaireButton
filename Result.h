#pragma once
#include "Engine/GameObject.h"
#include "Time.h"
#include "ResultText.h"

class Result : public GameObject
{
	int hPict_;		//画像番号
	Time* pTime;	//ゲームが終わっているかどうか確認する
	bool isFirst;	//最初の一回だけやりたい処理
	ResultText* pResultText;
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
