#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "Player.h"
#include "Time.h"
#include "UI.h"
#include "Engine/ScreenSplit.h"

//�����V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
	int hPict_Back;    //�摜
	int hPict_;    //�摜�ԍ�
	int hSound_;

	const int ALL_BALL = 60;
	const int END_TIME = 7200;
	float time;
	int startTime;
	int playerNumber;
	int groundBall;
	bool isEnd;
	Ball* pBall[80];
	Text* pText;
	UI* pUI;
	//Player* pPlayer[ScreenSplit::GetScreenSplit()];
	Player* pPlayer[4];
	Player* p1;
	Player* p2;
	Ground* pGround;
	Time* pTime;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//������
	bool IsDelete();
};