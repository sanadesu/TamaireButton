#pragma once
#include "GameObject.h"

//�����V�[�����Ǘ�����N���X
class Frame : public GameObject
{
	int frame;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Frame(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�t���[����
	int GetFrame();
};
