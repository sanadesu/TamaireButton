#include "StopButton.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Easing.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
#include "UI.h"

//�R���X�g���N�^
StopButton::StopButton(GameObject* parent)
	: GameObject(parent, "StopButton"), hPict_(-1)
{
}

//������
void StopButton::Initialize()
{
	//���[�h
	hPict_ = Image::Load("StopButton.png");
	assert(hPict_ >= 0);
	
	//�g�p����T�E���h�t�@�C����
	const char* soundFileName[] = { "Button.wav", "Move.wav" };

	//���[�h
	for (int i = 0; i < Sound::SOUND_MAX; i++)
	{
		hSound_[i] = Audio::Load(soundFileName[i], false, 0.8f, 10);
		assert(hSound_[i] >= 0);
	}
}

//�X�V
void StopButton::Update()
{
	if (pStop->GetIsStopPause())
	{
		if (Input::IsKeyDown(DIK_RIGHT))
		{
			transform_.position_.x = 0.63f;
			Audio::Play(hSound_[Sound::SOUND_MOVE]);
		}
		else if (Input::IsKeyDown(DIK_LEFT))
		{
			transform_.position_.x = 0;
			Audio::Play(hSound_[Sound::SOUND_MOVE]);
		}
		else if (Input::IsKeyDown(DIK_SPACE))
		{
			if (transform_.position_.x > 0.5f)
			{
				//�^�C�g����
				UI* pUI = (UI*)FindObject("UI");
				pUI->LoadSet();
				//���~�߂遝
				//Audio::Release();
				Time* pTime = (Time*)FindObject("Time");
				pTime->BGMStop();
				Audio::Play(hSound_[Sound::SOUND_BUTTON]);
				SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
				pSceneManager->ChangeScene(SCENE_ID_TITLE);
			}
			else
			{
				//������
				pStop->SetIsStopPause(false);
				Audio::Play(hSound_[Sound::SOUND_BUTTON]);
				Time* pTime = (Time*)FindObject("Time");
				pTime->SetStart();
				pStop->SetIsStart(true);
			}
		}
	}
}

//�`��
void StopButton::Draw()
{
	if (pStop->GetIsStopPause() && Direct3D::lr == 0)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//�J��
void StopButton::Release()
{
}