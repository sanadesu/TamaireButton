#pragma once
#include "Engine/GameObject.h" 

//�����V�[�����Ǘ�����N���X
class AssistText : public GameObject
{

	int playerNum; //���

	int hPict_;    //�摜�ԍ�
	int posY;
	bool isReady[4];
public:
	int text;
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	AssistText(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetSplit(int split_) { playerNum = split_; }
};