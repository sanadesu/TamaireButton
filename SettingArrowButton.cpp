#include "SettingArrowButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "SettingStartButton.h"
#include "Engine/Number.h"
#include "Engine/Easing.h"

//�萔
namespace
{
	static const int REVERSE = 180;//�{�^�����]
	static const float EASE_VAL = 0.04f;//�C�[�W���O�̕ω���(�X���C�h)
	static const float START_EASE_UP = 1.0f;//�X���C�h�J�n�C�[�W���O��
	static const float START_EASE_DOWN = 1.2f;//�X���C�h�J�n�C�[�W���O��
	//�{�^���̈ʒu
	static const float LEFT_POS = 0.085f;
	static const float RIGHT_POS = 0.78f;
	static const float UP_POS = 0.38f;
	static const float DOWN_POS = -0.21f;
	static const float NUM_POS = 0.435f;//�����̈ʒu
}

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
			startEase = START_EASE_UP;
		else
			startEase = START_EASE_DOWN;


		//�X���C�h���ēo�ꂳ����
		easeSave = startEase - easeX;
		if (easeSave < 0)
			easeSave = 0;
		else if (easeSave > 1)
			easeSave = 1;
		transform_.position_.x = -Easing::EaseInQuart(easeSave) * 2 + arrowPosX;
		
		if (arrowID == 0)
			pNumber1->SetPosition(XMFLOAT3(-Easing::EaseInQuart(easeSave) * 2 + NUM_POS, pNumber1->GetPosition().y, pNumber1->GetPosition().z));
		else if(arrowID == 2)
			pNumber2->SetPosition(XMFLOAT3(-Easing::EaseInQuart(easeSave) * 2 + NUM_POS, pNumber2->GetPosition().y, pNumber2->GetPosition().z));
		//0.435f = SettingScene��x�̈ʒu�w�肵�Ă�

		easeX += EASE_VAL;
	}
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
		if (playerNum > ONE_PERSON)
			playerNum--;
		if (playerNum > TWO_PERSON)
		{
			comNum = FOUR_PERSON - playerNum;
		}
		else if (playerNum == TWO_PERSON && comNum % 2 == 1)
		{
			comNum = TWO_PERSON;
		}
		else if (playerNum == ONE_PERSON && comNum % 2 == 0)
		{
			comNum = TREE_PERSON;
		}
		break;
	case 1://�l�����₷
		if (playerNum < FOUR_PERSON)
			playerNum++;
		if (playerNum > TWO_PERSON)
		{
			comNum = FOUR_PERSON - playerNum;
		}
		else if (playerNum == TWO_PERSON && comNum % 2 == 1)
		{
			comNum = TWO_PERSON;
		}
		break;
	case 2://CPU���₷
		if (playerNum <= TWO_PERSON && comNum >= TWO_PERSON)
		{
			if (comNum > ONE_PERSON)
				comNum -= TWO_PERSON;
		}
		break;
	case 3://CPU���炷
		if (playerNum <= TWO_PERSON && comNum <= ONE_PERSON)
		{
			if (comNum < TREE_PERSON)
				comNum += TWO_PERSON;
		}
		break;
	default:
		break;
	}

	pStartButton->SetComNum(comNum);
	pStartButton->SetPlayerNum(playerNum);

	pNumber1->SetNum(pStartButton->GetPlayerNum(),0, NUM_POS);
	pNumber2->SetNum(pStartButton->GetComNum(), 0, NUM_POS);
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
