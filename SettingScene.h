#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//�����V�[�����Ǘ�����N���X
class SettingScene : public GameObject
{
	enum Arrow
	{
		LEFT_UP,
		RIGHT_UP,
		LEFT_DOWN,
		RIGHT_DOWN,
		ARROW_MAX
	};


	
	//int hPict_;    //�摜�ԍ�
	//int hPict_Back;
	/*
	int hPict_Frame;
	int hPict_Number;*/

	//int hSound_Button;    //�T�E���h�ԍ�
	//int hSound_Move;

	int player;
	//int playerNum;
	//int comNum;
	//int frameNum;
	////bool stickMove;
	////std::pair<float, float> framePos[5];
	//Transform transPlayerNum;
	//Transform transComNum;
	/*Transform transFrame;*/
public:
	static int mode;
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SettingScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;


};

