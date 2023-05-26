#pragma once
#include "Engine/GameObject.h" 

//■■シーンを管理するクラス
class AssistText : public GameObject
{

	int playerNum; //画面

	int hPict_;    //画像番号
	int posY;
	bool isReady[4];
public:
	int text;
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	AssistText(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetSplit(int split_) { playerNum = split_; }
};