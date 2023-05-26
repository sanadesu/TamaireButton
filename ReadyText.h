#pragma once
#include "Engine/GameObject.h" 

//�����V�[�����Ǘ�����N���X
class ReadyText : public GameObject
{
	int hPict_;    //�摜�ԍ�
	int playerNum; //���
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ReadyText(GameObject* parent);

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
