#pragma once
#include "Engine/Button.h"

//using namespace Button;

//■■シーンを管理するクラス
class SettingArrowButton : public Button
{
	enum Pict
	{
		PICT_BUTTON,
		PICT_NUMBER,
		PICT_MAX
	};

	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	//int hPict_;    //画像番号
	//int hSound_;    //サウンド番号


	const int REVERSE = 180;//ボタン反転

	const float EASE_VAL = 0.04f;//イージングの変化量(スライド)
	//ボタンの位置
	const float LEFT_POS = 0.085f;
	const float RIGHT_POS = 0.78f;
	const float UP_POS = 0.38f;
	const float DOWN_POS = -0.21f;

	int arrowID;
	
	float easeX;
	float easeSave;
	float startEase;
	float arrowPosX;

	bool isStickMove;
	bool isLoad;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SettingArrowButton(GameObject* parent, int arrowID);

	//初期化
	void SubInitialize() override;

	//更新
	void SubUpdate() override;

	////描画
	//void Draw() override;

	////開放
	//void Release() override;

	//bool IsLoad();


//ボタンが押されたときにする処理
	void Event() override;

	//選択された瞬間
	void IsSelect() override;

	//選択解除された瞬間
	void IsSelectReleas() override;
};
