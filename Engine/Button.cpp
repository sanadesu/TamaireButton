#include "Button.h"
#include "Global.h"
#include "Button.h"
#include "Input.h"
#include "Audio.h"
#include "Image.h"
#include "ButtonManager.h"

//�萔
namespace
{
	static const int ALL_CREEN_ID = 5;
	static const int ALPHA_MAX = 255;

}

//�R���X�g���N�^
Button::Button(GameObject* parent, const std::string& name)
	:GameObject(parent,"SettingButton"),hSound_{-1,-1}
{
}

//������
void Button::Initialize()
{
	isStickMove = true;
	isNextSelect = false;
	isNowSelect = false;
	screenID = 0;
	alpha = ALPHA_MAX;
	//�g�p����T�E���h�t�@�C����
	const char* soundFileName[] = { "Button.wav", "Move.wav" };

	//���[�h
	for (int i = 0; i < Sound::SOUND_MAX; i++)
	{
		hSound_[i] = Audio::Load(soundFileName[i], false, 0.8f, 10);
		assert(hSound_[i] >= 0);
	}

	SubInitialize();
}

//�X�V
void Button::Update()
{
	if (ButtonManager::GetSelectChange() == false || firstButton == this)
	{
		//�I���ړ������Ƃ�
		if (ButtonManager::GetNowButton(this->GetScreenID()) == this)
		{
			ButtonManager::SelectMove(screenID);
		}
		ButtonManager::SetSelectChange(false);
	}
	
	SubUpdate();

	//���肵���Ƃ�
	if ((Input::IsKeyDown(DIK_SPACE) || Input::IsPadButtonDown(XINPUT_GAMEPAD_A, screenID)) && this == ButtonManager::GetNowButton(screenID))
	{
		Audio::Play(hSound_[SOUND_BUTTON]);
		Event();
	}
}

//�`��
void Button::Draw()
{
	Image::SetAlpha(hPict_, alpha);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void Button::Release()
{
}



//�{�^���������ꂽ�Ƃ��ɂ��鏈��
void Button::Event()
{
}
//�I�����ꂽ�u��
void Button::IsSelect()
{
}

//�I���������ꂽ�u��
void Button::IsSelectReleas()
{
}

//�T�u�A�b�v�f�[�g
void Button::SubUpdate()
{
}

//�T�u������
void Button::SubInitialize()
{
}

//�摜��ݒ�
void Button::SetImage(const std::string& path,Transform trans)
{
	Image::SetTransform(hPict_, trans);
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load(path);

	//���[�h���ꂽ���m�F
	assert(hPict_ >= 0);
}


//���̑I���{�^���Z�b�g
void Button::SetIsNextSelect(bool state_)
{
	isNextSelect = state_;
}

//���̑I���{�^���擾
bool Button::GetIsNextSelect()
{
	return isNextSelect;
}

//�I���{�^���Z�b�g
void Button::SetIsNowSelect(bool state_)
{
	isNowSelect = state_;
}

//�I���{�^���擾
bool Button::GetIsNowSelect()
{
	return isNowSelect;
}

//�{�^���̐؂�ւ�
void Button::ButtonSwith()
{
	if (GetIsNextSelect() != GetIsNowSelect())
	{
		Audio::Play(hSound_[SOUND_MOVE]);
		SetIsNowSelect(GetIsNextSelect());
		if (GetIsNowSelect())
		{
			IsSelect();
			ButtonManager::SetNowButton(this);
		}
		else
			IsSelectReleas();
	}
}

//���߂ɑI�������{�^���Z�b�g
void Button::SetIsFirst(Button* first)
{
	firstButton = first;
}

// �A���t�@�l�Z�b�g
void Button::SetAlpha(int alpha_)
{
	alpha = alpha_;
}

//�X�N���[��ID�̃Z�b�g
void Button::SetScreenID(int screenID_)
{
	screenID = screenID_;
}

//�V�[��ID�擾
int Button::GetScreenID()
{
	return screenID;
}
