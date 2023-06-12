#include "TitleScene.h"
#include"Engine/Camera.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Audio.h"
#include "Engine/Model.h"
#include "Engine/Easing.h"
#include"TitlePlayer.h"
#include"TitleText.h"
#include"TitleBall.h"
#include "Engine/Frame.h"
#include "TitleButton.h"
#include "Engine/ButtonManager.h"
#include "Rule.h"

//�萔
namespace
{
	static const int MAX_PLAYER = 2;//�^�C�g���ɓo�ꂳ����v���C���[�̐�
	static const int BALL_DROP_INTERVAL = 10;//�{�[���𗎂Ƃ��Ԋu
	static const int DROP_START_FRAME = 120;//�{�[���𗎂Ƃ��n�߂�t���[����
	static const int BUTTON_NUM = 2;//�{�^����
}

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1), hPict_Back(-1), hSound_(-1)
{
}

//������
void TitleScene::Initialize()
{ 
	isSkip = false;
	//�T�E���h�f�[�^�̃��[�h
	hSound_ = Audio::Load("Star.wav", false, 0.7f, 1);
	assert(hSound_ >= 0);
	
	Audio::Play(hSound_);

	ScreenSplit::SetScreenSplit(1);
	Camera::Initialize();
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Title.png");
	assert(hPict_ >= 0);
	hPict_Back = Image::Load("Back.jpg");
	assert(hPict_Back >= 0);

	Instantiate<Frame>(this);
	Instantiate<TitleText>(this);

	TitleButton* pTitleButton[BUTTON_NUM];
	const std::string ButtonName[BUTTON_NUM] = { "TitleStartButton","TitleRuleButton" };
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		pTitleButton[i] = ButtonManager::CreateButtonScreen<TitleButton>(this, ButtonName[i], i,0);
		pTitleButton[i]->SetObjectName(ButtonName[i]);
	}

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		pT_Player[i] = InstantiateFront<TitlePlayer>(this);
		pT_Player[i]->T_PlayerID = i;
	}
	Instantiate<Rule>(this);
}

//�X�V
void TitleScene::Update()
{
	Frame* nowFrame = (Frame*)FindObject("Frame");
	if (nowFrame->GetFrame() % BALL_DROP_INTERVAL == 0 && nowFrame->GetFrame() >= DROP_START_FRAME)
	{
		InstantiateFront<TitleBall>(this);
	}
	
	//�{�^�������ꂽ��X�L�b�v
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		isSkip = true;
	}
}

//�`��
void TitleScene::Draw()
{
	Transform transBack = transform_;
	transBack.position_ = XMFLOAT3(0, 0, 0);
	Image::SetTransform(hPict_Back, transBack);
	Image::Draw(hPict_Back);
}

//�J��
void TitleScene::Release()
{
}

//�X�L�b�v
bool TitleScene::GetIsSkip()
{
	return isSkip;
}
