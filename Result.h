#pragma once
#include "Engine/GameObject.h"
#include "Time.h"
//�����V�[�����Ǘ�����N���X
class Result : public GameObject
{

	Time* pTime;
	bool isFirst;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Result(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};
