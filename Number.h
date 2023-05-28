#pragma once
#include "Engine/GameObject.h" 

//�����V�[�����Ǘ�����N���X
class Number : public GameObject
{
	const int MAX_DIGITS = 3;
	const int CHANGE_DIGITS = 60;
	const int NUM_INTERVAL = 150;
	const int WIDTH = 150;
	const int HEIGHT = 256;
	int hPict_[3];    //���f���ԍ�
	int num;
	int numID;
	int dividedTime;
	int saveTime;
	//float easeY;
	//std::vector<int> ballDrop;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Number(GameObject* parent,int ID);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�����Z�b�g
	void SetNum(int num_, float space_);

	
};
