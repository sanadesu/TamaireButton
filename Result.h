#pragma once
#include "Engine/GameObject.h"
#include "Time.h"
#include "ResultText.h"

class Result : public GameObject
{
	int hPict_;		//�摜�ԍ�
	Time* pTime;	//�Q�[�����I����Ă��邩�ǂ����m�F����
	bool isFirst;	//�ŏ��̈�񂾂���肽������
	ResultText* pResultText;
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
