#pragma once
#include "Engine/GameObject.h" 
#include "Engine/ScreenSplit.h"
#include "Time.h"
#include "UI.h"

//�����V�[�����Ǘ�����N���X
class PlayStop : public GameObject
{
	enum Stop
	{
		STOP_READY,
		STOP_START,
		STOP_PAUSE,
		//STOP_RESULT,
		STOP_MAX
	};
	int hSound_;
	bool isStop[Stop::STOP_MAX];
	//bool isReady[ScreenSplit::GetAllPerson()];
	bool isReady[4];

	Time* pTime = (Time*)FindObject("Time");
	UI* pUI;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayStop(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�ꎞ��~
	void SetIsStopPause(bool isStop_);
	bool GetIsStopPause();

	void SetIsReady(bool isReady_,int ID);
	bool GetIsStopReady();

	bool GetIsStop();

	void GameStart();

	void SetIsStart(bool IsStart_);
};
