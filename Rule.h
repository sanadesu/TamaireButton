#pragma once
#include "Engine/GameObject.h"

class Rule : public GameObject
{
	int hPict_;    //�摜�ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Rule(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�摜�Z�b�g
	void SetRuleImage(const std::string& path);
};
