#include "Result.h"
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
	pResultText = Instantiate<ResultText>(this);
	pTime = (Time*)FindObject("Time");
	isFirst = true;
}

//�X�V
void Result::Update()
{
	if (pTime->GetTime() <= 0 && isFirst)
	{
		hPict_ = Image::Load("BlackBack.png");
		assert(hPict_ >= 0);
		isFirst = false;
	}

	if (pResultText->GetResultCount() == 250)
	{
		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			ButtonManager::CreateButtonScreen<ResultButton>(this, "ResultButton", i, SCREEN_ID);
		}
	}
}

//�`��
void Result::Draw()
{
	if (pTime->GetTime() <= 0)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//�J��
void Result::Release()
{
}
