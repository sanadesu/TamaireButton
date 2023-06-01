#pragma once
#include "Engine/Button.h"

//using namespace Button;

//■■シーンを管理するクラス
class SettingArrowButton : public Button
{
	enum PlayerNum
	{

	};

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

	int arrowID;//矢印ボタンID
	
	float easeX;//スライドして登場するときのイージング値
	float easeSave;//イージングの値保存
	float startEase;//スライド開始位置
	float arrowPosX;//矢印ボタンの場所
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SettingArrowButton(GameObject* parent, int arrowID);

	//初期化
	void SubInitialize() override;

	//更新
	void SubUpdate() override;

	//ボタンが押されたときにする処理
	void Event() override;

	//選択された瞬間
	void IsSelect() override;

	//選択解除された瞬間
	void IsSelectReleas() override;
};
