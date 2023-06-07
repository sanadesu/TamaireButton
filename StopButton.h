#pragma once
#include "Engine/GameObject.h" 
#include "PlayStop.h"

class StopButton : public GameObject
{
	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	int hPict_;    //画像番号
	int hSound_[Sound::SOUND_MAX];
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StopButton(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
