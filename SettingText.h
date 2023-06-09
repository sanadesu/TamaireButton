#pragma once
#include "Engine/GameObject.h" 
#include "Frame.h"

//■■シーンを管理するクラス
class SettingText : public GameObject
{
	enum Pict
	{
		PICT_SELECT,
		PICT_LOAD,
		PICT_MAX
	};

	int hPict_[Pict::PICT_MAX];    //画像番号

	float easeSave;//イージングの数値保存
	float easeX;//イージングのX軸
	float textY[2];
	float textHeight[2];
	float easeStart[2];

	Frame* nowFrame = (Frame*)FindObject("Frame");
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SettingText(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
