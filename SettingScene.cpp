#include "SettingScene.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Audio.h"
#include "Engine/ButtonManager.h"
#include "Frame.h"
#include "SettingText.h"
#include "SettingBack.h"
#include "SettingArrowButton.h"
#include "SettingStartButton.h"
#include "Number.h"

//定数
namespace
{
	static const int NUMERIC_COUNT = 2;
	static const float NUM_X = 0.435f;
	static const float NUM_UP_Y = 0.36f;
	static const float NUM_DOWN_Y = -0.23f;

}

//コンストラクタ
SettingScene::SettingScene(GameObject* parent)
	: GameObject(parent, "SettingScene")
{
}

//初期化
void SettingScene::Initialize()
{
	Instantiate<Frame>(this);
	Instantiate<SettingBack>(this);
	Instantiate<SettingText>(this);

	Number* pNumber[NUMERIC_COUNT];
	const char* numberName[NUMERIC_COUNT] = { "Number1","Number2" };
	XMFLOAT3 numPos[NUMERIC_COUNT] = { XMFLOAT3(NUM_X,NUM_UP_Y,0),XMFLOAT3(NUM_X,NUM_DOWN_Y,0) };

	for (int i = 0; i < NUMERIC_COUNT; i++)
	{
		pNumber[i] = InstantiateID<Number>(this,numPos[i],i);
		pNumber[i]->SetObjectName(numberName[i]);
	}

	for (int i = 0; i < ARROW_MAX; i++)
	{
		ButtonManager::CreateButton<SettingArrowButton>(this, transform_.position_, i);
	}

	SettingStartButton* pStartButton = Instantiate<SettingStartButton>(this);
	pStartButton->SetObjectName("SettingStartButton");
	player = 1;
}

//更新
void SettingScene::Update()
{

}

//描画
void SettingScene::Draw()
{
	
}

//開放
void SettingScene::Release()
{
}