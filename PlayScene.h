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
	int hPict_;    //�摜�ԍ�
	int hSound_;//��

	const int ALL_BALL = 60;//�{�[���̐�
	const int END_TIME = 7200;//�Q�[������
	const float VOLUME = 0.7f;//����
	Ball* pBall[80];
	Player* pPlayer[4];
	Ground* pGround;
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
};