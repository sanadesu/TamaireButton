#pragma once
#include "Engine/GameObject.h" 
#include "PlayStop.h"

class StopButton : public GameObject
{
	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	int hPict_;    //�摜�ԍ�
	int hSound_[Sound::SOUND_MAX];
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StopButton(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
