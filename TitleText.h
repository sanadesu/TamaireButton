#pragma once
#include "Engine/GameObject.h"
#include "Frame.h"
#include "TitleScene.h"

class TitleText : public GameObject
{
	int hPict_;    //�摜�ԍ�
	float easeX;//�X���C�h���ďo�Ă���C�[�W���O
	float easeScaleRed;//�ԃv���C���[�̑傫���C�[�W���O
	float easeScaleWhite;//���v���C���[�̑傫���C�[�W���O
	Frame* nowFrame;//���̃t���[�����擾����
	TitleScene* pTitle;//�^�C�g��
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleText(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
