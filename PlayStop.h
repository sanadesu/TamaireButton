#pragma once
#include "Engine/GameObject.h" 
#include "Engine/ScreenSplit.h"
#include "Time.h"
#include "UI.h"

//■■シーンを管理するクラス
class PlayStop : public GameObject
{
	enum Stop
	{
		STOP_READY,
		STOP_START,
		STOP_PAUSE,
		//STOP_RESULT,
		STOP_MAX
	};
	int hSound_;
	bool isStop[Stop::STOP_MAX];
	//bool isReady[ScreenSplit::GetAllPerson()];
	bool isReady[4];

	Time* pTime = (Time*)FindObject("Time");
	UI* pUI;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayStop(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//一時停止
	void SetIsStopPause(bool isStop_);
	bool GetIsStopPause();

	void SetIsReady(bool isReady_,int ID);
	bool GetIsStopReady();

	bool GetIsStop();

	void GameStart();

	void SetIsStart(bool IsStart_);
};
