#include "Result.h"
#include "ResultText.h"
#include "ResultButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/Input.h"

//定数
namespace
{
	static const int BUTTON_COUNT = 2;
	static const int SCREEN_ID = 5;
}

//コンストラクタ
Result::Result(GameObject* parent)
	: GameObject(parent, "Result")
{
}

//初期化
void Result::Initialize()
{
	Instantiate<ResultText>(this);
	pTime = (Time*)FindObject("Time");
	isFirst = true;
}

//更新
void Result::Update()
{
	if (pTime->GetTime() <= 0 && isFirst)
	{
		isFirst = false;
		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			ButtonManager::CreateButtonScreen<ResultButton>(this, "ResultButton", i, SCREEN_ID);
		}
	}
}

//描画
void Result::Draw()
{
	
}

//開放
void Result::Release()
{
}
