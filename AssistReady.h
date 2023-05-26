#pragma once
#include "Engine/GameObject.h" 
#include "Engine/ScreenSplit.h"

//�����V�[�����Ǘ�����N���X
class AssistReady : public GameObject
{
	//static const int a = ScreenSplit::GetPlayerPerson();
	//bool isReady[ScreenSplit::GetPlayerPerson()];
	//std::vector<bool> isReaady;//(ScreenSplit::GetPlayerPerson(),false);
	

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	AssistReady(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetIsReady();

	bool AllReady();

	void ReadyKill(int ScreenNum);

	void SetAssistText(int ScreenNum, int x);
};
