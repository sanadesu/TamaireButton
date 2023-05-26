#pragma once
#include "Engine/GameObject.h" 
#include "Frame.h"

//�����V�[�����Ǘ�����N���X
class SettingText : public GameObject
{
	enum Pict
	{
		PICT_SELECT,
		PICT_LOAD,
		PICT_MAX
	};

	int hPict_[Pict::PICT_MAX];    //�摜�ԍ�

	float easeX;
	Frame* nowFrame = (Frame*)FindObject("Frame");
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SettingText(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
