#pragma once
#include "Engine/GameObject.h" 
#include "Engine/ScreenSplit.h"
#include "StartSignal.h"
#include "UI.h"

//■■シーンを管理するクラス
class PlayStop : public GameObject
{
	enum Stop
	{
		STOP_READY,
		STOP_START,
		STOP_PAUSE,
		STOP_MAX
	};
	int hSound_;//音
	bool isStop[Stop::STOP_MAX];//止めるかどうか
	bool isReady[4];//準備が完了したか
	bool isStart;//スタートしたか
	bool isRetry;//再開

	StartSignal* pStartSignal;//スタートさせる
	UI* pUI;//ゲーム中かどうか

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

	//一時停止セット
	void SetIsStopPause(bool isStop_);

	//一時停止取得
	bool GetIsStopPause();

	//準備中セット
	void SetIsReady(bool isReady_,int ID);

	//準備中取得
	bool GetIsStopReady();

	//止まっているか取得
	bool GetIsStop();

	//動けるようになる
	void GameStart();

	//再開セット
	void SetIsStart(bool IsStart_);

	void SetIsRetry(bool isRetry_);

	//再開したか取得
	bool GetIsRetry();
};
