#include "AssistReady.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "Engine/ScreenSplit.h"
#include "Engine/ButtonManager.h"
#include "Engine/Input.h"
#include "AssistText.h"
#include "ReadyBack.h"
#include "ReadyButton.h"
#include "ReadyText.h"
#include "PlayStop.h"
#include "ReadyArrowButton.h"
#include "ReadyOKButton.h"

//定数
namespace 
{
	static const int UI_READY_COUNT = 5;
	static const int ARROW_NUM = 2;
}

struct ReadyUI
{
	ReadyBack* pReadyBack;
	ReadyText* pReadyText;
	AssistText* pAssistText;
	ReadyArrowButton* pReadyArrowButton[ARROW_NUM];
	ReadyOKButton* pReadyOKButton;
}; ReadyUI playerUI[UI_READY_COUNT];

//コンストラクタ
AssistReady::AssistReady(GameObject* parent)
	: GameObject(parent, "AssistReady")
{
}

//初期化
void AssistReady::Initialize()
{
	const char* buttonName[] = { "ReadyArrowButton1", "ReadyArrowButton2"};
	if (ScreenSplit::GetPlayerPerson() != 3)
		split = ScreenSplit::GetPlayerPerson() - 1;
	else
		split = ScreenSplit::GetPlayerPerson();

	for (int i = 0; i < ScreenSplit::GetPlayerPerson(); i++)
	{
		playerUI[i].pReadyBack = Instantiate<ReadyBack>(this);
		playerUI[i].pReadyBack->SetSplit(i + split);
		for (int j = 0; j < 2; j++)
		{
			playerUI[i].pReadyArrowButton[j] = ButtonManager::CreateButtonScreen<ReadyArrowButton>(this, buttonName[j], j, i);
			playerUI[i].pReadyArrowButton[j]->SetSplit(i + split);

		}
		playerUI[i].pReadyOKButton = ButtonManager::CreateButtonScreen<ReadyOKButton>(this, "ReadyOKButton", 0, i);
		playerUI[i].pReadyOKButton->SetSplit(i + split);
		playerUI[i].pReadyText = Instantiate<ReadyText>(this);
		playerUI[i].pReadyText->SetSplit(i + split);
		playerUI[i].pAssistText = Instantiate<AssistText>(this);
		playerUI[i].pAssistText->SetSplit(i + split);
	}

	pText = new Text;
	pText->Initialize();
}

//更新
void AssistReady::Update()
{
	if (AllReady())
	{
		PlayStop* pPlayStop = (PlayStop*)FindObject("PlayStop");
		//スタート
		pPlayStop->GameStart();
		ButtonManager::ButtonRelease();
		KillMe();
	}

#ifdef _DEBUG
	//準備完了
	if (Input::IsKeyDown(DIK_R))
	{
		for (int i = 0; i < ScreenSplit::GetPlayerPerson(); i++)
		{
			ReadyKill(i);
		}
	}
#endif // DEBUG

}

//描画
void AssistReady::Draw()
{
#ifdef _DEBUG
	if (Direct3D::lr == 0)
	{
		pText->Draw(30, 30, "DEBUG");
		pText->Draw(30, 60, "R->START!");
	}
#endif // DEBUG
}

//開放
void AssistReady::Release()
{
}

bool AssistReady::AllReady()
{
	for (int i = 0; i < ScreenSplit::GetPlayerPerson(); i++)
	{
		if(playerUI[i].pReadyOKButton->IsDead() == false)
			return false;
	}
	return true;
}

void AssistReady::ReadyKill(int ScreenNum)
{
	playerUI[ScreenNum].pReadyBack->BlackBack();
	for (int i = 0; i < ARROW_NUM; i++)
		playerUI[ScreenNum].pReadyArrowButton[i]->KillMe();

	playerUI[ScreenNum].pReadyOKButton->KillMe();
	playerUI[ScreenNum].pReadyText->KillMe();
	playerUI[ScreenNum].pAssistText->KillMe(); 
}

void AssistReady::SetAssistText(int ScreenNum, int x)
{
	playerUI[ScreenNum].pAssistText->text = x;
}
