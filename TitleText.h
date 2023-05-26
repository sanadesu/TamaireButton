#pragma once
#include "Engine/GameObject.h"
#include "TitlePlayer.h"
#include "Frame.h"
#include "TitleScene.h"

class TitleText : public GameObject
{
	const int RED_TEXT_EASE_START = 10;//[紅]拡大スタート
	const int WHITE_TEXT_EASE_START = 40;//[白]拡大スタート	
	const int SLIDE_TEXT_EASE_START = 80;//スライドスタート
	const float EASE_SCALE = 0.025f;//[紅白]の拡大量
	const float EASE_MOVE = 0.01f;//スライドの移動量

	int hPict_;    //画像番号

	float easeX;
	float easeScaleRed;
	float easeScaleWhite;
	Frame* nowFrame = (Frame*)FindObject("Frame");
	TitleScene* pTitle = (TitleScene*)FindObject("TitleScene");
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
