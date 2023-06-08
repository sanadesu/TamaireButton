#include "PlayStop.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "Engine/ButtonManager.h"
#include "StopBack.h"
#include "PauseButton.h"


//定数
namespace
{
	static const int SOUND_COUNT = 10;
	static const int BUTTON_COUNT = 2;
	static const int SCREEN_ID = 5;
	static const float VOLUME = 0.8f;
}

//コンストラクタ
PlayStop::PlayStop(GameObject* parent)
	: GameObject(parent, "PlayStop")
{
}

//初期化
void PlayStop::Initialize()
{
	Instantiate<StopBack>(this);
	hSound_ = Audio::Load("Move.wav", false, VOLUME, SOUND_COUNT);
	assert(hSound_ >= 0);

	for(int i = 0;i < Stop::STOP_MAX;i++)
		isStop[i] = true;

	isStop[Stop::STOP_PAUSE] = false;
	isRetry = false;
	pTime = (Time*)FindObject("Time");
}

//更新
void PlayStop::Update()
{
	pUI = (UI*)FindObject("UI");
	//ポーズ
	if ((Input::IsKeyDown(DIK_LCONTROL) || Input::IsKeyDown(DIK_RCONTROL) || Input::IsPadButtonDown(XINPUT_GAMEPAD_START))
		&& pUI->GetIsEnd() == false)
	{
		const char* buttonName[] = { "PlayButton" ,"TitleButton" };
		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			ButtonManager::CreateButtonScreen<PauseButton>(this, buttonName[i], i, SCREEN_ID);
		}//再開
		if (isStop[Stop::STOP_PAUSE])
		{
			isStop[Stop::STOP_PAUSE] = false;
			Audio::Play(hSound_);

			pTime->SetStart();
			isStop[Stop::STOP_START] = true;
			isRetry = true;
			ButtonManager::ButtonRelease();
		}//止める
		else
		{
			isStop[Stop::STOP_PAUSE] = true;
			Audio::Play(hSound_);
			isRetry = false;
		}
	}

	if (pTime->GetStartTime() <= 0)
		isStop[Stop::STOP_START] = false;

	for (int i = 0; i < ScreenSplit::GetAllPerson(); i++)
	{
		if (isReady[i] == false)
		{
			break;
		}
		
		if (i == ScreenSplit::GetAllPerson() - 1)
		{
			isStop[Stop::STOP_READY] = false;
		}
	}
}

//描画
void PlayStop::Draw()
{
}

//開放
void PlayStop::Release()
{
}

void PlayStop::SetIsStopPause(bool isStop_)
{
	isStop[Stop::STOP_PAUSE] = isStop_;
}

bool PlayStop::GetIsStopPause()
{
	return isStop[Stop::STOP_PAUSE];
}

void PlayStop::SetIsReady(bool isReady_, int ID)
{
	isReady[ID] = isReady_;
}

bool PlayStop::GetIsStopReady()
{
	return isStop[Stop::STOP_READY];
}

bool PlayStop::GetIsStop()
{
	for (int i = 0; i < Stop::STOP_MAX; i++)
	{
		if (isStop[i] == true)
			return true;
	}
	return false;
}

void PlayStop::GameStart()
{
	isStop[Stop::STOP_READY] = false;
}

void PlayStop::SetIsStart(bool IsStart_)
{
	isStop[Stop::STOP_START] = IsStart_;
}

void PlayStop::SetIsRetry(bool isRetry_)
{
	isRetry = isRetry_;
}

bool PlayStop::GetIsRetry()
{
	return isRetry;
}