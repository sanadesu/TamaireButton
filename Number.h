#pragma once
#include "Engine/GameObject.h" 

//■■シーンを管理するクラス
class Number : public GameObject
{
	const int MAX_DIGITS = 3;
	const int CHANGE_DIGITS = 60;
	const int NUM_INTERVAL = 150;
	const int WIDTH = 150;
	const int HEIGHT = 256;
	int hPict_[3];    //モデル番号
	int num;
	int numID;
	int dividedTime;
	int saveTime;
	//float easeY;
	//std::vector<int> ballDrop;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Number(GameObject* parent,int ID);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//数字セット
	void SetNum(int num_, float space_);

	
};
