#include "SettingStartButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Number.h"
#include "Engine/Easing.h"

//�萔
namespace
{
	const float EASE_VAL = 0.04f;
	const float START_EASE = 1.4f;
}

//�R���X�g���N�^
SettingStartButton::SettingStartButton(GameObject* parent)
	: Button(parent, "SettingButton")
{
}

//������
void SettingStartButton::SubInitialize()
{
	easeSave = 1;
	easeX = 0;
	Number* pNumber1 = (Number*)FindObject("Number1");
	Number* pNumber2 = (Number*)FindObject("Number2");
	playerNum = 1;
	comNum = 3;
	pNumber1->SetNum(playerNum, 0.06f);
	pNumber2->SetNum(comNum, 0.06f);

	transform_.position_.y = -0.7f;
	SetImage("NormalCircle.png", transform_);

	ButtonManager::AddButton((Button*)this,0);
}

void SettingStartButton::SubUpdate()
{
	ButtonSwith();
	//�����I�������
	if (easeSave != 0)
	{
		//�X���C�h���ēo�ꂳ����
		easeSave = START_EASE - easeX;
		easeSave = std::min<float>(std::max<float>(easeSave, 0), 1);
		transform_.position_.x = -Easing::EaseInQuart(easeSave) * 2;
		easeX += EASE_VAL;
	}
}

//�{�^���������ꂽ�Ƃ��ɂ��鏈��
void SettingStartButton::Event()
{
	//��ŐF�I���Ƃ��`�[�������Ƃ��ǉ��A���͂Ƒΐ킪�ł���悤��
			//�X�^�[�g
	//�i���o�[�N���X���玝���Ă���
	ScreenSplit::SetScreenSplit(playerNum);
	ScreenSplit::SetPlayPerson(playerNum);
	ScreenSplit::SetAllPerson(playerNum + comNum);

	transform_.position_ = XMFLOAT3(0, 0, 0);
	SetImage("Load.png", transform_);

	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_PLAY);
}

//�I�����ꂽ�u��
void SettingStartButton::IsSelect()
{
	//�I�𒆂ɂ���
	ButtonManager::SetNowButton(this);
	//�摜�ς���
	SetImage("SelectCircle.png", transform_);
}

//�I���������ꂽ�u��
void SettingStartButton::IsSelectReleas()
{
	//�摜�߂�
	SetImage("NormalCircle.png", transform_);
}

void SettingStartButton::SetPlayerNum(int playerNum_)
{
	playerNum = playerNum_;
}

int SettingStartButton::GetPlayerNum()
{
	return playerNum;
}

void SettingStartButton::SetComNum(int comNum_)
{
	comNum = comNum_;
}

int SettingStartButton::GetComNum()
{
	return comNum;
}
