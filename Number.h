#pragma once
#include "Engine/GameObject.h" 

//�����V�[�����Ǘ�����N���X
class Number : public GameObject
{
	int hPict_[3];    //���f���ԍ�
	int num;
	int dividedTime;
	int saveTime;
	float space;
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
	void SetNum(int num_, float space_, float posX_);

	
};
