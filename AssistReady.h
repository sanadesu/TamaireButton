#pragma once
#include "Engine/GameObject.h" 
#include "Engine/ScreenSplit.h"

//■■シーンを管理するクラス
class AssistReady : public GameObject
{
	//static const int a = ScreenSplit::GetPlayerPerson();
	//bool isReady[ScreenSplit::GetPlayerPerson()];
	//std::vector<bool> isReaady;//(ScreenSplit::GetPlayerPerson(),false);
	

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

	void SetIsReady();

	bool AllReady();

	void ReadyKill(int ScreenNum);

	void SetAssistText(int ScreenNum, int x);
};
