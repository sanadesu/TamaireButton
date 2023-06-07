#include "Result.h"
#include "ResultText.h"
#include "ResultButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/Input.h"

//�萔
namespace
{
	static const int BUTTON_COUNT = 2;
	static const int SCREEN_ID = 5;
}

//�R���X�g���N�^
Result::Result(GameObject* parent)
	: GameObject(parent, "Result")
{
}

//������
void Result::Initialize()
{
	Instantiate<ResultText>(this);
	pTime = (Time*)FindObject("Time");
	isFirst = true;
}

//�X�V
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

//�`��
void Result::Draw()
{
	
}

//�J��
void Result::Release()
{
}
