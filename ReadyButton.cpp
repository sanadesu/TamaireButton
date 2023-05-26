#include "ReadyButton.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "PlayStop.h"
#include "AssistReady.h"

//�R���X�g���N�^
ReadyButton::ReadyButton(GameObject* parent)
	: GameObject(parent, "ReadyButton"), hPict_(-1)
{
}

//������
void ReadyButton::Initialize()
{
	//�g�p����T�E���h�t�@�C����
	const char* soundFileName[] = { "Button.wav", "Move.wav" };

	//���[�h
	for (int i = 0; i < Sound::SOUND_MAX; i++)
	{
		hSound_[i] = Audio::Load(soundFileName[i], false, 0.8f, 10);
		assert(hSound_[i] >= 0);
	}

	if (ScreenSplit::GetPlayerPerson() == 2)
	{
		scaleY = 0.5f;
		posY = 500;
		posX = 10;
	}
	else
	{
		scaleY = 1;
		posY = 465;
		posX = 0;
	}
	
	playerNum = 0;
	//button = BUTTON_READY;
	
		//���[�h
	hPict_ = Image::Load("ReadyButton.png");
	assert(hPict_ >= 0);

	button = Button::BUTTON_READY;
	buttonTrans = transform_;
	buttonTrans.scale_ = XMFLOAT3(1, scaleY, 1);
	//if (ScreenSplit::GetPlayerPerson() > playerNum + 3)
	isAssist = true;
	//else
		//isAssist = false;
	isStickMove = true;
	isReady = false;
	if (ScreenSplit::GetPlayerPerson() != 3)
	{
		min = ScreenSplit::GetPlayerPerson() - 1;
	}
	else
	{
		min = 3;
	}

	const char* PlayerName[] = { "Player", "Player2", "Player3", "Player4"};

	for (int i = 0; i < ScreenSplit::GetPlayerPerson(); i++)
	{
		pPlayer[i] = (Player*)FindObject(PlayerName[i]);
	}

	
}

//�X�V
void ReadyButton::Update()
{
	if (ScreenSplit::GetPlayerPerson() >= 2)
	{
		
	}
	else
	{

	}

	for (int i = 0; i < ScreenSplit::GetPlayerPerson(); i++)
	{
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, i))
		{

		}
	}

	//if (((Input::IsKeyDown(DIK_RIGHT) && playerNum == min) 
	//	|| (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT, playerNum - min) 
	//	|| Input::GetPadStickL(playerNum - min).x > 0))
	//	&& isStickMove && button != BUTTON_READY
	//	/*&& playerNum == Direct3D::lr*/)
	//{
	//	isStickMove = false;
	//	button = BUTTON_ASSIST_T;
	//	buttonTrans.rotate_.z = 180;
	//	Audio::Play(hSound_[Sound::SOUND_MOVE]);
	//}
	///*if (((Input::IsKeyDown(DIK_LEFT)  && playerNum == min)
	//	|| (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT, playerNum - min) 
	//	|| Input::GetPadStickL(0).x < 0)) 
	//	&& isStickMove && button != BUTTON_READY
	//	&&Direct3D::lr == playerNum )  
	//{
	//	isStickMove = false; 
	//	button = BUTTON_ASSIST_F;
	//	buttonTrans.rotate_.z = 0;
	//	Audio::Play(hSound_[Sound::SOUND_MOVE]);
	//}*/
	//if (((Input::IsKeyDown(DIK_DOWN) && playerNum == min) 
	//	|| (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN, playerNum - min) 
	//	|| Input::GetPadStickL(playerNum - min).y < 0))
	//	&& isStickMove&& button != BUTTON_READY
	//	/*&&playerNum == Direct3D::lr*/)
	//{
	//	isStickMove = false;
	//	button = BUTTON_READY;
	//	hPict_ = Image::Load("ReadyButton.png");
	//	assert(hPict_ >= 0);
	//	buttonTrans.position_ = XMFLOAT3(0, 0, 0);
	//	buttonTrans.scale_ = XMFLOAT3(1, 1, 1);
	//	buttonTrans.rotate_.z = 0;
	//	Audio::Play(hSound_[Sound::SOUND_MOVE]);
	//}
	//if (((Input::IsKeyDown(DIK_UP) && playerNum == min) 
	//	|| (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP, playerNum - min) 
	//	|| Input::GetPadStickL(playerNum - min).y > 0))
	//	&& isStickMove&& button == BUTTON_READY
	//	/*&& playerNum == Direct3D::lr*/)
	//{
	//	isStickMove = false;
	//	button = BUTTON_ASSIST_F;
	//	hPict_ = Image::Load("SelectTriangle.png");
	//	assert(hPict_ >= 0);
	//	buttonTrans.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
	//	Audio::Play(hSound_[Sound::SOUND_MOVE]);
	//}
	//if ((Input::IsKeyDown(DIK_SPACE) && playerNum == min) 
	//	|| (Input::IsPadButton(XINPUT_GAMEPAD_A, playerNum - min)))
	//{
	//	AssistText* pAssistText = (AssistText*)FindObject("AssistText");
	//	//�A�V�X�g�I���I�t
	//	//��������
	//	switch (button)
	//	{
	//	case BUTTON_ASSIST_F://�A�V�X�g�I�t
	//		break;
	//	case BUTTON_ASSIST_T://�A�V�X�g�I��
	//		break;
	//	case BUTTON_READY://��������
	//		pAssistText->SetIsReady(true, 0);

	//		break;
	//	default:
	//		button = BUTTON_ASSIST_F;
	//		break;
	//	}
	//	Audio::Play(hSound_[Sound::SOUND_BUTTON]);
	//}

	if (Input::GetPadStickL(0).y == 0 && Input::GetPadStickL(0).x == 0)
	{
		isStickMove = true;
	}
	//for (int i = 0; i < 4; i++)
	//{
	//	if (button[i] != Button::BUTTON_READY)
	//		break;
	//	if (i == 3)
	//	{
	//		//�S������OK
	//	}
	//}
	// 
	// 
	//switch (button)
	//{
	//case BUTTON_ASSIST_F://�A�V�X�g�I�t
	//	break;
	//case BUTTON_ASSIST_T://�A�V�X�g�I��
	//	break;
	//case BUTTON_READY://��������
	//	break;
	//default:
	//	button = BUTTON_ASSIST_F;
	//	break;
	//}
}

//�`��
void ReadyButton::Draw()
{
	if (((Input::IsKeyDown(DIK_RIGHT) && playerNum == min)
		|| (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT, playerNum - min)
			|| Input::GetPadStickL(playerNum - min).x > 0))
		&& isStickMove && button != BUTTON_READY)
	{
		isStickMove = false;
		button = BUTTON_ASSIST_F;
		buttonTrans.rotate_.z = 180;

		buttonTrans.position_ = Image::PixelPos(hPict_,1475 + posX,posY);
		Audio::Play(hSound_[Sound::SOUND_MOVE]);
	}
	if (((Input::IsKeyDown(DIK_LEFT)  && playerNum == min)
		|| (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT, playerNum - min)
		|| Input::GetPadStickL(playerNum - min).x < 0))
		&& isStickMove && button != BUTTON_READY)
	{
		isStickMove = false;
		button = BUTTON_ASSIST_T;
		buttonTrans.rotate_.z = 0;
		buttonTrans.position_ = Image::PixelPos(hPict_, 1000 - posX, posY);
		Audio::Play(hSound_[Sound::SOUND_MOVE]);
	}
	if (((Input::IsKeyDown(DIK_DOWN) && playerNum == min)
		|| (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN, playerNum - min)
			|| Input::GetPadStickL(playerNum - min).y < 0))
		&& isStickMove && button != BUTTON_READY)
	{
		isStickMove = false;
		button = BUTTON_READY;
		hPict_ = Image::Load("ReadyButton.png");
		assert(hPict_ >= 0);
		buttonTrans.position_ = XMFLOAT3(0, 0, 0);
		buttonTrans.scale_ = XMFLOAT3(1, scaleY, 1);
		buttonTrans.rotate_.z = 0;
		Audio::Play(hSound_[Sound::SOUND_MOVE]);
	}
	if (((Input::IsKeyDown(DIK_UP) && playerNum == min)
		|| (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP, playerNum - min)
			|| Input::GetPadStickL(playerNum - min).y > 0))
		&& isStickMove && button == BUTTON_READY)
	{
		isStickMove = false;
		button = BUTTON_ASSIST_T;
		hPict_ = Image::Load("SelectTriangle.png");
		assert(hPict_ >= 0);
		buttonTrans.scale_ = XMFLOAT3(0.5f, (scaleY * 0.5f), 0.5f);
		buttonTrans.position_ = Image::PixelPos(hPict_, 1000 - posX, posY);
		Audio::Play(hSound_[Sound::SOUND_MOVE]);
	}
	if ((Input::IsKeyDown(DIK_SPACE) && playerNum == min)
		|| (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, playerNum - min)))
	{
		AssistReady* pAssistReady = (AssistReady*)FindObject("AssistReady");
		//�A�V�X�g�I���I�t
		//��������
		switch (button)
		{
		case BUTTON_ASSIST_F://�A�V�X�g�I�t
			pPlayer[playerNum - min]->SetIsAssist(false);
			pAssistReady->SetAssistText(playerNum - min, 256);
			break;
		case BUTTON_ASSIST_T://�A�V�X�g�I��
			pPlayer[playerNum - min]->SetIsAssist(true);
			pAssistReady->SetAssistText(playerNum - min, 0);
			break;
		case BUTTON_READY://��������
			isReady = true;
			//����
			pAssistReady->ReadyKill(playerNum - min);
			break;
		default:
			button = BUTTON_ASSIST_F;
			break;
		}
		Audio::Play(hSound_[Sound::SOUND_BUTTON]);
	}


	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
  	if (playerNum == Direct3D::lr && pStop->GetIsStopReady())
	{
		Image::SetTransform(hPict_, buttonTrans);
		Image::Draw(hPict_);
	}


	//PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	//if (pStop->GetIsStopReady())
	//{
	//	if (ScreenSplit::GetPlayerPerson() != 1 && Direct3D::lr != Screen::SCREEN_ALL)
	//	{
	//		if (Direct3D::lr == Screen::SCREEN_LEFT_UP)
	//		{
	//			Image::SetTransform(hPict_[0], buttonTrans[0]);
	//			Image::Draw(hPict_[0]);
	//		}
	//		else if(Direct3D::lr == Screen::SCREEN_RIGHT_UP)
	//		{
	//			Image::SetTransform(hPict_[1], transform_);
	//			Image::Draw(hPict_[1]);
	//		}
	//		else if (Direct3D::lr == Screen::SCREEN_LEFT_DOWN)
	//		{
	//			Image::SetTransform(hPict_[2], transform_);
	//			Image::Draw(hPict_[2]);
	//		}
	//		else if (Direct3D::lr == Screen::SCREEN_RIGHT_DOWN)
	//		{
	//			Image::SetTransform(hPict_[3], transform_);
	//			Image::Draw(hPict_[3]);
	//		}
	//		else if (Direct3D::lr == Screen::SCREEN_LEFT)
	//		{
	//			Image::SetTransform(hPict_[1], transform_);
	//			Image::Draw(hPict_[1]);
	//		}
	//		else if (Direct3D::lr == Screen::SCREEN_RIGHT)
	//		{
	//			Image::SetTransform(hPict_[2], transform_);
	//			Image::Draw(hPict_[2]);
	//		}
	//	}
	//	else if(ScreenSplit::GetPlayerPerson() == 1)
	//	{
	//		Image::SetTransform(hPict_[0], transform_);
	//		Image::Draw(hPict_[0]);
	//	}
	//}
}

//�J��
void ReadyButton::Release()
{
}

bool ReadyButton::GetReady()
{
	return isReady;
}
