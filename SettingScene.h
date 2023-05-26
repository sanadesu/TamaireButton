#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//■■シーンを管理するクラス
class SettingScene : public GameObject
{
	enum Arrow
	{
		LEFT_UP,
		RIGHT_UP,
		LEFT_DOWN,
		RIGHT_DOWN,
		ARROW_MAX
	};


	
	//int hPict_;    //画像番号
	//int hPict_Back;
	/*
	int hPict_Frame;
	int hPict_Number;*/

	//int hSound_Button;    //サウンド番号
	//int hSound_Move;

	int player;
	//int playerNum;
	//int comNum;
	//int frameNum;
	////bool stickMove;
	////std::pair<float, float> framePos[5];
	//Transform transPlayerNum;
	//Transform transComNum;
	/*Transform transFrame;*/
public:
	static int mode;
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SettingScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;


};

