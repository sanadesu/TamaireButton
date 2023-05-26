#pragma once
#include "StateWalk.h"
#include "StateBase.h"

class StateManager
{
	StateBase* pStateBase;
public:
	//������Ԃ��A��������n�߂�
	StateManager() : pStateBase(new StateWalk) {}

	void Action();

	void NextState();
};

