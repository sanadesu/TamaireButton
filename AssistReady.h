#pragma once
#include "Engine/GameObject.h" 
#include "Engine/ScreenSplit.h"
#include "Engine/Text.h"

//■■シーンを管理するクラス
class AssistReady : public GameObject
{
	int split;//画面分割数
	Text* pText;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	AssistReady(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//void SetIsReady();

	bool AllReady();

	void ReadyKill(int ScreenNum);

	void SetAssistText(int ScreenNum, int x);
};
