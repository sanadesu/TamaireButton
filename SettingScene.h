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

	int player;

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

