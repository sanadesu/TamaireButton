#pragma once
#include "Engine/Direct3D.h"
#include "Engine/Transform.h"

class StateBase
{
public:
	//static StandingState standing;
	//virtual ~StateBase() {};
	//virtual void Update() {};
	//------------------------����------------------------
	//�G�������Ă��ă{�[����1�����Ă��灨�߂��{�[���܂�
	//������玩���̃{�[���܂�
	// 
	//stateText = "Walk";
	//if (moveLimit > CIRCLE_RANGE)
	//	transform_.rotate_.y += 137;

	//transform_ = FrontDirection(0, 0, PLAYER_MOVE, transform_.rotate_.y, transform_);

	/*Transform transform_;
	Transform GetTransform() { return transform_; }
	StateBase(Transform t_) :transform_(t_) {}*/

	virtual void Action() = 0;

	virtual StateBase* NextState() = 0;

	XMFLOAT3 pos;
	//------------------------�E��------------------------
	//�����Ă�G��1�{�[�������ĂȂ���������������{�[���E���ɍs������s���Ȃ�������

	//-----------------------������-----------------------
	//�����Ă�G��1�{�[�������Ă違�����悤�Ƃ��ĂȂ����G�Ɍ������ē�����
	//�Ⴄ�� 
	//�����{�[���̎����S�[����
	//�G�{�[�������������H�O�ɏo���H
};

