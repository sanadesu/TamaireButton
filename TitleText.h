#pragma once
#include "Engine/GameObject.h"
#include "Frame.h"
#include "TitleScene.h"

class TitleText : public GameObject
{
	int hPict_;    //画像番号
	float easeX;//スライドして出てくるイージング
	float easeScaleRed;//赤プレイヤーの大きさイージング
	float easeScaleWhite;//白プレイヤーの大きさイージング
	Frame* nowFrame;//今のフレームを取得する
	TitleScene* pTitle;//タイトル
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleText(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
