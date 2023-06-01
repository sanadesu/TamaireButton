#include "SettingScene.h"
//#include"Engine/Camera.h"
//#include "Engine/SceneManager.h"
#include "Engine/Input.h"
//#include "Engine/Image.h"
#include "Engine/Camera.h"
//#include "Engine/ScreenSplit.h"
#include "Engine/Audio.h"
#include "Engine/ButtonManager.h"
#include "Frame.h"
#include "SettingText.h"
#include "SettingBack.h"
#include "SettingArrowButton.h"
#include "SettingStartButton.h"
#include "Number.h"

static const float NUM_X = 0.435f;

//�R���X�g���N�^
SettingScene::SettingScene(GameObject* parent)
	: GameObject(parent, "SettingScene")
{
}

//������
void SettingScene::Initialize()
{/*
	hSound_Button = Audio::Load("Button.wav",10);
	assert(hSound_Button >= 0);
	hSound_Move = Audio::Load("Move.wav", 10);
	assert(hSound_Move >= 0);*/
	
	
	//playerNum = 1;
	//comNum = 3;
	//frameNum = 0;
	//pText->Initialize();
	////�摜�f�[�^�̃��[�h
	//hPict_ = Image::Load("Select.png");
	//assert(hPict_ >= 0);

	//hPict_Back = Image::Load("SelectBack.png");
	//assert(hPict_Back >= 0);
	Instantiate<Frame>(this);
	Instantiate<SettingBack>(this);
	//Instantiate<SettingButton>(this);
	Instantiate<SettingText>(this);
	Number* pNumber[2];
	const char* numberName[2] = { "Number1","Number2" };
	XMFLOAT3 numPos[2] = { XMFLOAT3(0.435f,0.36f,0),XMFLOAT3(0.435f,-0.23f,0) };
	for (int i = 0; i < 2; i++)
	{
		pNumber[i] = InstantiateID<Number>(this,numPos[i],i);
		pNumber[i]->SetObjectName(numberName[i]);
		//pNumber[i]->SetPosition(numPos[i]);
	}


	for (int i = 0; i < 4; i++)
	{
		//ButtonManager::CreateButton(this, XMFLOAT3(0,0,0), 1);

		ButtonManager::CreateButton<SettingArrowButton>(this, transform_.position_, i);
		//transform_.position_.x += 0.5f;
	}
	SettingStartButton* pStartButton = Instantiate<SettingStartButton>(this);
	pStartButton->SetObjectName("SettingStartButton");
	//Instantiate<SettingArrowButton>(this);
	
	//hPict_Frame = Image::Load("SelectTriangle.png");
	//assert(hPict_Frame >= 0);

	//hPict_Number = Image::Load("Number.png");
	//assert(hPict_Number >= 0);

	/*transPlayerNum = transform_;
	transPlayerNum.position_.x = 0.435;
	transPlayerNum.position_.y = 0.36;

	transComNum = transform_;
	transComNum.position_.x = 0.435;
	transComNum.position_.y = -0.23;*/

	//transFrame = transform_;
	/*framePos[0] = {0.085, 0.38};
	framePos[1] = { 0.78, 0.38 };
	framePos[2] = { 0.085, -0.205 };
	framePos[3] = { 0.78, -0.21 };*/
	player = 1;
	//stickMove = true;
}

//�X�V
void SettingScene::Update()
{
	////��
	//if (Input::IsKeyDown(DIK_SPACE) || Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	//{
	//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//	switch (frameNum)
	//	{
	//	case 0:
	//		if (playerNum > 1)
	//			playerNum--;
	//		if (playerNum > 2)
	//		{
	//			comNum = 4 - playerNum;
	//		}
	//		else if (playerNum == 2 && comNum % 2 == 1)
	//		{
	//			comNum = 2;
	//		}
	//		else if (playerNum == 1 && comNum % 2 == 0)
	//		{
	//			comNum = 3;
	//		}
	//		break;
	//	case 1:
	//		if (playerNum < 4)
	//			playerNum++;
	//		if (playerNum > 2)
	//		{
	//			comNum = 4 - playerNum;
	//		}
	//		else if (playerNum == 2 && comNum % 2 == 1)
	//		{
	//			comNum = 2;
	//		}

	//		break;
	//	case 2:
	//		if (playerNum <= 2 && comNum >= 2)
	//		{
	//			if (comNum > 1)
	//				comNum -= 2;
	//		}
	//		break;
	//	case 3:
	//		if (playerNum <= 2 && comNum <= 1)
	//		{
	//			if (comNum < 3)
	//				comNum += 2;
	//		}
	//		break;
	//	case 4:
	//		//��ŐF�I���Ƃ��`�[�������Ƃ��ǉ��A���͂Ƒΐ킪�ł���悤��
	//		//�X�^�[�g
	//		ScreenSplit::SetScreenSplit(playerNum);
	//		ScreenSplit::SetPlayPerson(playerNum);
	//		ScreenSplit::SetAllPerson(playerNum + comNum);

	//		hPict_ = Image::Load("Load.png");
	//		assert(hPict_ >= 0);

	//		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	//		break;
	//	default:
	//		break;
	//	}
	//	Audio::Play(hSound_Button);
	//}

	/*if (Input::GetPadStickL(0).y == 0 && Input::GetPadStickL(0).x == 0)
	{
		stickMove = true;
	}

	if ((Input::IsKeyDown(DIK_UP) || Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP, 0) || (Input::GetPadStickL(0).y > 0 && stickMove)) && frameNum > 1)
	{
		frameNum -= 2;
		stickMove = false;
		Audio::Play(hSound_Move);
	}
	if ((Input::IsKeyDown(DIK_DOWN) || Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN,0) || (Input::GetPadStickL(0).y < 0 && stickMove)) && frameNum < 4 )
	{
		frameNum += 2;
		if (frameNum > 4)
			frameNum = 4;
		stickMove = false;
		Audio::Play(hSound_Move);
	}
	if ((Input::IsKeyDown(DIK_RIGHT) || Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT, 0) || (Input::GetPadStickL(0).x > 0 && stickMove)) && frameNum < 4 && frameNum % 2 == 0)
	{
		frameNum++;
		stickMove = false;
		Audio::Play(hSound_Move);
	}
	if ((Input::IsKeyDown(DIK_LEFT) || Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT, 0) || (Input::GetPadStickL(0).x < 0 && stickMove)) && frameNum > 0 && frameNum % 2 == 1)
	{
		frameNum--;
		stickMove = false;
		Audio::Play(hSound_Move);
	}*/

	/*Transform transNum = transform_;
	transNum.position_.x = 1000;*/
	//Image::SetTransform(hPict_PlayerNumber,transNum);

	//if (Input::IsKeyDown(DIK_1))
	//{
	//	ScreenSplit::SetScreenSplit(1);
	//	//���[�h�摜�ɂ���A�P���
	//	hPict_ = Image::Load("Load.png");
	//	assert(hPict_ >= 0);
	//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//	pSceneManager->ChangeScene(SCENE_ID_PLAY);
	//}
	//if (Input::IsKeyDown(DIK_2))
	//{
	//	ScreenSplit::SetScreenSplit(2);
	//	//���[�h�摜�ɂ���A�P���
	//	hPict_ = Image::Load("Load.png");
	//	assert(hPict_ >= 0);
	//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//	pSceneManager->ChangeScene(SCENE_ID_PLAY);
	//}
	//if (Input::IsKeyDown(DIK_4))
	//{
	//	ScreenSplit::SetScreenSplit(4);
	//	//���[�h�摜�ɂ���A�P���
	//	hPict_ = Image::Load("Load.png");
	//	assert(hPict_ >= 0);
	//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//	pSceneManager->ChangeScene(SCENE_ID_PLAY);
	//}

	/*if (Input::IsKeyDown(DIK_UP)&&player < 4)
	{
		player++;
		ScreenSplit::SetPlayPerson(player);
	}
	if (Input::IsKeyDown(DIK_DOWN) && player > 1)
	{
		player--;
		ScreenSplit::SetPlayPerson(player);
	}*/
}

//�`��
void SettingScene::Draw()
{
	//�w�i
	/*Image::SetTransform(hPict_Back, transform_);
	Image::Draw(hPict_Back);*/
	////�g,�I���̂��
	////���������180�x��]������
	//if (frameNum % 2 == 1)
	//{
	//	transFrame.rotate_.z = 180;
	//}
	//else
	//{
	//	transFrame.rotate_.z = 0;
	//}
	//if (frameNum == 4)
	//{
	//	hPict_Frame = Image::Load("SelectCircle.png");
	//}
	//else
	//{
	//	hPict_Frame = Image::Load("SelectTriangle.png");
	//}

	//transFrame.position_.x = framePos[frameNum].first;
	//transFrame.position_.y = framePos[frameNum].second;
	//Image::SetTransform(hPict_Frame, transFrame);
	//Image::Draw(hPict_Frame);
	////�v���C���[�̐l���\��
	//Image::SetRect(hPict_Number, playerNum * 150, 0, 150, 256);
	//Image::SetTransform(hPict_Number, transPlayerNum);
	//Image::Draw(hPict_Number);
	////COM�̐l���\��
	//Image::SetRect(hPict_Number, comNum * 150, 0, 150, 256);
	//Image::SetTransform(hPict_Number, transComNum);
	//Image::Draw(hPict_Number);

	//���ȊO�A�����Ƃ�
	/*Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);*/
	
}

//�J��
void SettingScene::Release()
{
}