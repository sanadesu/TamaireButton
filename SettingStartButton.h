#pragma once
#include "Engine/Button.h"

//using namespace Button;

//■■シーンを管理するクラス
class SettingStartButton : public Button
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

	const float EASE_VAL = 0.04f;
	//int hPict_;    //画像番号
//	int hSound_;    //サウンド番号

	int playerNum;
	int comNum;

	float easeX;
	float easeSave;
	float startEase;
	//float arrowPosX;
	bool isStickMove;
	bool isLoad;
	std::pair<float, float> framePos[5];

	Transform transButton;
	Transform transPlayerNum;
	Transform transComNum;
public:
	int arrowID;

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SettingStartButton(GameObject* parent);

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

	//プレイヤーの人数取得
	void SetPlayerNum(int playerNum_);
	
	//プレイヤーの人数取得
	int GetPlayerNum();

	//コンピュータの数取得
	void SetComNum(int comNum_);

	//コンピュータの数取得
	int GetComNum();

};
