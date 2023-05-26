#include "SettingArrowButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "SettingStartButton.h"
#include "Number.h"
#include "Engine/Easing.h"

//�R���X�g���N�^
SettingArrowButton::SettingArrowButton(GameObject* parent,int ID)
	: Button(parent, "SettingButton")
{
	arrowID = ID;
}

void SettingArrowButton::SubInitialize()
{
	easeSave = 1;
	easeX = 0;
	startEase = 0;
	switch (arrowID)
	{
	case 0:
		arrowPosX = LEFT_POS;
		transform_.position_.y = UP_POS;
		break;
	case 1:
		arrowPosX = RIGHT_POS;
		transform_.position_.y = UP_POS;
		transform_.rotate_.z = REVERSE;
		break;
	case 2:
		arrowPosX = LEFT_POS;
		transform_.position_.y = DOWN_POS;
		break;
	case 3:
		arrowPosX = RIGHT_POS;
		transform_.position_.y = DOWN_POS;
		transform_.rotate_.z = REVERSE;
		break;
	default:
		break;
	}
	transform_.position_.x = arrowPosX;

	//hPict_ = Image::Load("SelectTriangle");
	//transform_.scale_ = XMFLOAT3(30, 30, 30);
	SetImage("Triangle.png", transform_);
	if (arrowID == 0)
	{
		SetIsNextSelect(true);
		IsSelect();
		SetIsFirst(this);
	}
	ButtonManager::AddButton((Button*)this,0);
}

////������
//void SettingArrowButton::Initialize()
//{
//	
//}

void SettingArrowButton::SubUpdate()
{
	ButtonSwith();
	//�����I�������
	if (easeSave != 0)
	{
		Number* pNumber1 = (Number*)FindObject("Number1");
		Number* pNumber2 = (Number*)FindObject("Number2");
		//��i���i������
		if (arrowID < 2 )
			startEase = 1.0f;
		else
			startEase = 1.2f;

		//�X���C�h���ēo�ꂳ����
		easeSave = startEase - easeX;
		if (easeSave < 0)
			easeSave = 0;
		else if (easeSave > 1)
			easeSave = 1;
		transform_.position_.x = -Easing::EaseInQuart(easeSave) * 2 + arrowPosX;
		
		if (arrowID == 0)
			pNumber1->SetPosition(XMFLOAT3(-Easing::EaseInQuart(easeSave) * 2 + 0.435f, pNumber1->GetPosition().y, pNumber1->GetPosition().z));
		else if(arrowID == 2)
			pNumber2->SetPosition(XMFLOAT3(-Easing::EaseInQuart(easeSave) * 2 + 0.435f, pNumber2->GetPosition().y, pNumber2->GetPosition().z));
		//0.435f = SettingScene��x�̈ʒu�w�肵�Ă�
		

		easeX += EASE_VAL;
	}
	
	/*if (GetIsNextSelect() != GetIsNowSelect())
	{
		SetIsNowSelect(GetIsNextSelect());
		if (GetIsNowSelect())
		{
			IsSelect();
			ButtonManager::SetNowButton(this);
		}
		else
			IsSelectReleas();
	}*/
}

//�{�^���������ꂽ�Ƃ��ɂ��鏈��
void SettingArrowButton::Event()
{
	SettingStartButton* pStartButton = (SettingStartButton*)FindObject("SettingStartButton");
	Number* pNumber1 = (Number*)FindObject("Number1");
	Number* pNumber2 = (Number*)FindObject("Number2");
	int playerNum = pStartButton->GetPlayerNum();
	int comNum = pStartButton->GetComNum();
	//�i���o�[�N���X���玝���Ă���
	//�i���o�[�N���X�͂Q�̃Z�b�^�[�Q�b�^�[�Ɛ����̐؂�ւ�
	switch (arrowID)
	{
	case 0://�l�����炷
		if (playerNum > 1)
			playerNum--;
		if (playerNum > 2)
		{
			comNum = 4 - playerNum;
		}
		else if (playerNum == 2 && comNum % 2 == 1)
		{
			comNum = 2;
		}
		else if (playerNum == 1 && comNum % 2 == 0)
		{
			comNum = 3;
		}
		break;
	case 1://�l�����₷
		if (playerNum < 4)
			playerNum++;
		if (playerNum > 2)
		{
			comNum = 4 - playerNum;
		}
		else if (playerNum == 2 && comNum % 2 == 1)
		{
			comNum = 2;
		}
		break;
	case 2://CPU���₷
		if (playerNum <= 2 && comNum >= 2)
		{
			if (comNum > 1)
				comNum -= 2;
		}
		break;
	case 3://CPU���炷
		if (playerNum <= 2 && comNum <= 1)
		{
			if (comNum < 3)
				comNum += 2;
		}
		break;
	default:
		break;
	}

	pStartButton->SetComNum(comNum);
	pStartButton->SetPlayerNum(playerNum);

	pNumber1->SetNum(pStartButton->GetPlayerNum(),0);
	pNumber2->SetNum(pStartButton->GetComNum(), 0);

	//�N���X���₷
	//���Ȃ獶�E
	//���֐����
	//����Ȃ�ʂ̏���
	//����̓V�[���؂�ւ�
	//�X�^�[�g�{�^���N���X�Ɉړ�
	//ScreenSplit::SetScreenSplit(playerNum);
	//ScreenSplit::SetPlayPerson(playerNum);
	//ScreenSplit::SetAllPerson(playerNum + comNum);

	////���[�h�N���X���ǂ�����
	////���[�h�摜�ɕύX�������H
	//isLoad = true;
	////�ʃN���X�H
	////hPict_[Pict::PICT_BUTTON] = Image::Load("Load.png");
	////assert(hPict_[Pict::PICT_BUTTON] >= 0);
	//SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//pSceneManager->ChangeScene(SCENE_ID_PLAY);

	//���
	//rotate.z == 0 �Ȃ猸�炷�֐��@���X�N���[��
	//rotate.z == 180�Ȃ瑝�₷�֐��@�E�X�N���[��
}

//�I�����ꂽ�u��
void SettingArrowButton::IsSelect()
{
	//�I�𒆂ɂ���
	ButtonManager::SetNowButton(this);
	//�摜�ς���
	SetImage("SelectTriangle.png", transform_);
}

//�I���������ꂽ�u��
void SettingArrowButton::IsSelectReleas()
{
	//�摜�߂�
	SetImage("Triangle.png", transform_);
}
