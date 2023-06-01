#pragma once
#include "Engine/GameObject.h"
#include "TitlePlayer.h"

//�����V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	int hPict_;    //�摜�ԍ�
	int hPict_Back;
	int hSound_;    //�T�E���h�ԍ�
	
	bool isSkip;
	TitlePlayer* pT_Player[2];
	
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�X�L�b�v
	bool GetIsSkip();
};
