#pragma once
#include "Engine/GameObject.h"
#include "TitlePlayer.h"

//�����V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	static const int MAX_PLAYER = 2;//�^�C�g���ɓo�ꂳ����v���C���[�̐�
	static const int BALL_DROP_INTERVAL = 10;//�{�[���𗎂Ƃ��Ԋu
	static const int DROP_START_FRAME = 120;//�{�[���𗎂Ƃ��n�߂�t���[����

	int hPict_;    //�摜�ԍ�
	int hPict_Back;
	int hSound_;    //�T�E���h�ԍ�
	int hSound_Button;    
	int hSound_Move;
	int hModel_; //���f��

	bool isSkip;
	TitlePlayer* pT_Player[MAX_PLAYER];
	
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
