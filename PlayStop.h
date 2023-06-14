#pragma once
#include "Engine/GameObject.h" 
#include "Engine/ScreenSplit.h"
#include "StartSignal.h"
#include "UI.h"

//�����V�[�����Ǘ�����N���X
class PlayStop : public GameObject
{
	enum Stop
	{
		STOP_READY,
		STOP_START,
		STOP_PAUSE,
		STOP_MAX
	};
	int hSound_;//��
	bool isStop[Stop::STOP_MAX];//�~�߂邩�ǂ���
	bool isReady[4];//����������������
	bool isStart;//�X�^�[�g������
	bool isRetry;//�ĊJ

	StartSignal* pStartSignal;//�X�^�[�g������
	UI* pUI;//�Q�[�������ǂ���

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

	//�ꎞ��~�Z�b�g
	void SetIsStopPause(bool isStop_);

	//�ꎞ��~�擾
	bool GetIsStopPause();

	//�������Z�b�g
	void SetIsReady(bool isReady_,int ID);

	//�������擾
	bool GetIsStopReady();

	//�~�܂��Ă��邩�擾
	bool GetIsStop();

	//������悤�ɂȂ�
	void GameStart();

	//�ĊJ�Z�b�g
	void SetIsStart(bool IsStart_);

	void SetIsRetry(bool isRetry_);

	//�ĊJ�������擾
	bool GetIsRetry();
};
