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

//コンストラクタ
AssistReady::AssistReady(GameObject* parent)
	: GameObject(parent, "AssistReady")
{
}

struct ReadyUI
{
	ReadyBack* pReadyBack;
	//ReadyButton* pReadyButton;
	ReadyText* pReadyText;
	AssistText* pAssistText;
	ReadyArrowButton* pReadyArrowButton[2];
	ReadyOKButton* pReadyOKButton;
}; ReadyUI playerUI[5];

//初期化
void AssistReady::Initialize()
{
	const char* buttonName[] = { "ReadyArrowButton1", "ReadyArrowButton2"};
	if (ScreenSplit::GetPlayerPerson() != 3)
	{
		for (int i = 0; i < ScreenSplit::GetPlayerPerson(); i++)
		{
			playerUI[i].pReadyBack = Instantiate<ReadyBack>(this);
			playerUI[i].pReadyBack->SetSplit(i + ScreenSplit::GetPlayerPerson() - 1);
			for (int j = 0; j < 2; j++)
			{
				playerUI[i].pReadyArrowButton[j] = ButtonManager::CreateButtonScreen<ReadyArrowButton>(this, buttonName[j], j, i);
				playerUI[i].pReadyArrowButton[j]->SetSplit(i + ScreenSplit::GetPlayerPerson() - 1);
				
			}
			playerUI[i].pReadyOKButton = ButtonManager::CreateButtonScreen<ReadyOKButton>(this, "ReadyOKButton", 0, i);
			playerUI[i].pReadyOKButton->SetSplit(i + ScreenSplit::GetPlayerPerson() - 1);
			//playerUI[i].pReadyButton = Instantiate<ReadyButton>(this);
			//playerUI[i].pReadyButton->SetSplit(i + ScreenSplit::GetPlayerPerson() - 1);
			playerUI[i].pReadyText = Instantiate<ReadyText>(this);
			playerUI[i].pReadyText->SetSplit(i + ScreenSplit::GetPlayerPerson() - 1);
			playerUI[i].pAssistText = Instantiate<AssistText>(this);
			playerUI[i].pAssistText->SetSplit(i + ScreenSplit::GetPlayerPerson() - 1);
		}
	}
	else
	{
		for (int i = 0; i < ScreenSplit::GetPlayerPerson(); i++)
		{
			playerUI[i].pReadyBack = Instantiate<ReadyBack>(this);
			playerUI[i].pReadyBack->SetSplit(i + ScreenSplit::GetPlayerPerson());
			for (int j = 0; j < 2; j++)
			{
				playerUI[i].pReadyArrowButton[j] = ButtonManager::CreateButtonScreen<ReadyArrowButton>(this, buttonName[j], j,i);
				playerUI[i].pReadyArrowButton[j]->SetSplit(i + ScreenSplit::GetPlayerPerson());
			}
			playerUI[i].pReadyOKButton = ButtonManager::CreateButtonScreen<ReadyOKButton>(this, "ReadyOKButton", 0, i);
			playerUI[i].pReadyOKButton->SetSplit(i + ScreenSplit::GetPlayerPerson());
			//playerUI[i].pReadyButton = Instantiate<ReadyButton>(this);
			//playerUI[i].pReadyButton->SetSplit(i + ScreenSplit::GetPlayerPerson());
			playerUI[i].pReadyText = Instantiate<ReadyText>(this);
			playerUI[i].pReadyText->SetSplit(i + ScreenSplit::GetPlayerPerson());
			playerUI[i].pAssistText = Instantiate<AssistText>(this);
			playerUI[i].pAssistText->SetSplit(i + ScreenSplit::GetPlayerPerson());
		}
	}

	isFirstTime = true;
	pText = new Text;
	pText->Initialize();
	//switch (ScreenSplit::GetPlayerPerson())
	//{
	//case 1:
	//	Instantiate<ReadyBack>(this)->SetSplit(0);
	//	Instantiate<ReadyButton>(this)->SetSplit(0);
	//	Instantiate<ReadyText>(this)->SetSplit(0);
	//	Instantiate<AssistText>(this)->SetSplit(0);
	//	break;
	//case 2:
	//	Instantiate<ReadyBack>(this)->SetSplit(1);
	//	Instantiate<ReadyBack>(this)->SetSplit(2);
	//	Instantiate<ReadyButton>(this)->SetSplit(1);
	//	Instantiate<ReadyButton>(this)->SetSplit(2);
	//	Instantiate<ReadyText>(this)->SetSplit(1);
	//	Instantiate<ReadyText>(this)->SetSplit(2);
	//	Instantiate<AssistText>(this)->SetSplit(1);
	//	Instantiate<AssistText>(this)->SetSplit(2);
	//	break;
	//case 3:
	//	Instantiate<ReadyBack>(this)->SetSplit(3);
	//	Instantiate<ReadyBack>(this)->SetSplit(4);
	//	Instantiate<ReadyBack>(this)->SetSplit(5);
	//	Instantiate<ReadyButton>(this)->SetSplit(3);
	//	Instantiate<ReadyButton>(this)->SetSplit(4);
	//	Instantiate<ReadyButton>(this)->SetSplit(5);
	//	Instantiate<ReadyText>(this)->SetSplit(3);
	//	Instantiate<ReadyText>(this)->SetSplit(4);
	//	Instantiate<ReadyText>(this)->SetSplit(5);
	//	Instantiate<AssistText>(this)->SetSplit(3);
	//	Instantiate<AssistText>(this)->SetSplit(4);
	//	Instantiate<AssistText>(this)->SetSplit(5);
	//	break;
	//case 4:
	//	Instantiate<ReadyBack>(this)->SetSplit(3);
	//	Instantiate<ReadyBack>(this)->SetSplit(4);
	//	Instantiate<ReadyBack>(this)->SetSplit(5);
	//	Instantiate<ReadyBack>(this)->SetSplit(6);
	//	Instantiate<ReadyButton>(this)->SetSplit(3);
	//	Instantiate<ReadyButton>(this)->SetSplit(4);
	//	Instantiate<ReadyButton>(this)->SetSplit(5);
	//	Instantiate<ReadyButton>(this)->SetSplit(6);
	//	Instantiate<ReadyText>(this)->SetSplit(3);
	//	Instantiate<ReadyText>(this)->SetSplit(4);
	//	Instantiate<ReadyText>(this)->SetSplit(5);
	//	Instantiate<ReadyText>(this)->SetSplit(6);
	//	Instantiate<AssistText>(this)->SetSplit(3);
	//	Instantiate<AssistText>(this)->SetSplit(4);
	//	Instantiate<AssistText>(this)->SetSplit(5);
	//	Instantiate<AssistText>(this)->SetSplit(6);
	//	break;
	//default:
	//	break;
	//}
}

//更新
void AssistReady::Update()
{
	if (/*isFirstTime &&*/ AllReady())
	{
		isFirstTime = false;
		PlayStop* pPlayStop = (PlayStop*)FindObject("PlayStop");
		//スタート
		pPlayStop->GameStart();//一回だけにする
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
		//if (playerUI[i].pReadyButton->GetReady() == false)
		if(playerUI[i].pReadyOKButton->IsDead() == false)
			return false;
	}
	return true;
}

void AssistReady::ReadyKill(int ScreenNum)
{
	playerUI[ScreenNum].pReadyBack->BlackBack();
	//playerUI[ScreenNum].pReadyButton->KillMe();
	//playerUI[ScreenNum].pReadyArrowButton->KillMe();
	for (int i = 0; i < 2; i++)
		playerUI[ScreenNum].pReadyArrowButton[i]->KillMe();

	playerUI[ScreenNum].pReadyOKButton->KillMe();
	playerUI[ScreenNum].pReadyText->KillMe();
	playerUI[ScreenNum].pAssistText->KillMe(); 
}

void AssistReady::SetAssistText(int ScreenNum, int x)
{
	playerUI[ScreenNum].pAssistText->text = x;
}
