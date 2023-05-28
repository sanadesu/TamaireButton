#include "Result.h"
#include "ResultText.h"
#include "ResultButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/Input.h"

//コンストラクタ
Result::Result(GameObject* parent)
	: GameObject(parent, "Result")
{
}

//初期化
void Result::Initialize()
{
	Instantiate<ResultText>(this);
	//Instantiate<ResultText>(this);
	////Instantiate<ResultButton>(this);
	//for (int i = 0; i < 2; i++)
	//{
	//	ButtonManager::CreateButton<ResultButton>(this, transform_.position_, i);
	//}
	pTime = (Time*)FindObject("Time");
	isFirst = true;
}

//更新
void Result::Update()
{
	if (pTime->GetTime() <= 0 && isFirst)
	{
		isFirst = false;
		//Instantiate<ResultButton>(this);
		for (int i = 0; i < 2; i++)
		{
			ButtonManager::CreateButtonScreen<ResultButton>(this, "ResultButton", i,5);
		}
	}
	
	/*if (Input::IsKeyDown(DIK_F))
	{
		KillMe();
	}*/
}

//描画
void Result::Draw()
{
	
}

//開放
void Result::Release()
{
}
