#include "Result.h"
#include "ResultText.h"
#include "ResultButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Result::Result(GameObject* parent)
	: GameObject(parent, "Result")
{
}

//������
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

//�X�V
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

//�`��
void Result::Draw()
{
	
}

//�J��
void Result::Release()
{
}
