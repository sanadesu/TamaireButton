#pragma once
#include "Engine/GameObject.h" 
#include "Engine/ScreenSplit.h"
#include "Player.h"

//�����V�[�����Ǘ�����N���X
class ReadyButton : public GameObject
{
	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	enum Button
	{
		BUTTON_ASSIST_T,//��
		BUTTON_ASSIST_F,
		BUTTON_READY,
		BUTTON_MAX
	};

	enum Screen
	{
		SCREEN_ALL,
		SCREEN_LEFT,
		SCREEN_RIGHT,
		SCREEN_LEFT_UP,
		SCREEN_RIGHT_UP,
		SCREEN_LEFT_DOWN,
		SCREEN_RIGHT_DOWN
	};

	int hPict_;    //�摜�ԍ�
	int hSound_[Sound::SOUND_MAX];    //�T�E���h�ԍ�
	int min;
	int playerNum; //���
	int button;
	int posX;
	int posY;
	float scaleY;
	bool isAssist;
	bool isStickMove;
	bool isReady;
	Transform buttonTrans;
	Player* pPlayer[4];

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ReadyButton(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetSplit(int split_) { playerNum = split_; }

	bool GetReady();
};
