#pragma once
#include "Engine/GameObject.h" 

//�����V�[�����Ǘ�����N���X
class TitleBall : public GameObject
{
	int hModel_;    //���f���ԍ�

	const int DOWN_LIMIT = -40;//�{�[������������
	const int RANGE_X = 600;//�{�[���𗎂Ƃ��͈�(��)
	const int RANGE_Z = 100;//�{�[���𗎂Ƃ��͈�(��)
	const int SIZE = 4;//�{�[���̑傫��

	const float DOWN_SPEAD = 0.005f;//�{�[���������鑬��

	float easeY;
	//std::vector<int> ballDrop;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleBall(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
