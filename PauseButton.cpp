#include "PauseButton.h"
#include "Engine/Image.h"
#include "Engine/ButtonManager.h"
#include "Engine/SceneManager.h"
#include "Engine/Direct3D.h"
#include "Engine/Audio.h"
#include "UI.h"

//�萔
namespace
{

	static const float BUTTON_POS_X = 0.3f;
	static const float BUTTON_POX_Y = -0.25f;

}

//�R���X�g���N�^
PauseButton::PauseButton(GameObject* pParent, std::string name, int buttonID_, int screenID_)
	: Button(pParent, "PauseButton"), hPict_(-1)
{
	buttonID = buttonID_;
}

//������
void PauseButton::SubInitialize()
{
	if (buttonID == 0)
	{
		transform_.position_ = XMFLOAT3(-BUTTON_POS_X, BUTTON_POX_Y, 0);
		hPict_ = Image::Load("PauseRetrySelect.png");
		assert(hPict_ >= 0);
		SetIsNextSelect(true);
		IsSelect();
		SetIsFirst(this);
	}
	else
	{
		transform_.position_ = XMFLOAT3(BUTTON_POS_X, BUTTON_POX_Y, 0);

		hPict_ = Image::Load("PauseButtonTitle.png");
		assert(hPict_ >= 0);
	}
	ButtonManager::AddButton((Button*)this, 0);
	pTime = (Time*)FindObject("Time");
	pPlayStop = (PlayStop*)FindObject("PlayStop");
}

//�X�V
void PauseButton::SubUpdate()
{
	ButtonSwith();
	if (pPlayStop->GetIsRetry())
	{
		KillMe();
	}
}

//�`��
void PauseButton::Draw()
{
	if (Direct3D::lr == 0)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//�{�^���������ꂽ�Ƃ��ɂ��鏈��
void PauseButton::Event()
{
	
	if (buttonID == 0)
	{
		pPlayStop = (PlayStop*)FindObject("PlayStop");
		//������
		pPlayStop->SetIsStopPause(false);
		pTime->SetStart();
		pPlayStop->SetIsStart(true);
		pPlayStop->SetIsRetry(true);
	}
	else
	{
		UI* pUI = (UI*)FindObject("UI");
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		//���[�h
		pUI->LoadSet();
		Audio::Release();
		//�^�C�g���ֈړ�
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//�I�����ꂽ�u��
void PauseButton::IsSelect()
{
	//�I�𒆂ɂ���
	ButtonManager::SetNowButton(this);

	//�摜�ς���
	if (buttonID == 0)
		hPict_ = Image::Load("PauseRetrySelect.png");
	else
		hPict_ = Image::Load("PauseTitleSelect.png");
}

void PauseButton::IsSelectReleas()
{
	//�摜�߂�
	if (buttonID == 0)
		hPict_ = Image::Load("PauseButtonRetry.png");
	else
		hPict_ = Image::Load("PauseButtonTitle.png");
}
