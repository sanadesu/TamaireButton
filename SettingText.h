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

	float easeSave;//�C�[�W���O�̐��l�ۑ�
	float easeX;//�C�[�W���O��X��
	float textY[2];
	float textHeight[2];
	float easeStart[2];

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
