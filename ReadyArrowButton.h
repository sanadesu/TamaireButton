#pragma once
#include "Engine/Button.h"
#include "TitleScene.h"
#include "Player.h"

class ReadyArrowButton : public Button
{
	int a = 0;
	int hPict_;
	int arrowID;
	int screenID;
	int min;
	int posX;
	int posY;
	int playerNum;
	int arrowPos;
	float scaleY;
	Player* pPlayer;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ReadyArrowButton(GameObject* parent,const string name, int buttonID_,int screenID);

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ReadyArrowButton(GameObject* parent, int buttonID_);

	//������
	void SubInitialize() override;

	//�X�V
	void SubUpdate() override;

	//�`��
	void Draw() override;

	//�{�^���������ꂽ�Ƃ��ɂ��鏈��
	void Event() override;

	//�I�����ꂽ�u��
	void IsSelect() override;

	//�I���������ꂽ�u��
	void IsSelectReleas() override;


	void SetSplit(int split_) { playerNum = split_; }

	int GetScreenID() override;

	int GetPlayerNum();
};
