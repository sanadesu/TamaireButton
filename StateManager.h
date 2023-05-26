#pragma once
#include "StateWalk.h"
#include "StateBase.h"

class StateManager
{
	StateBase* pStateBase;
public:
	//初期状態を、歩くから始める
	StateManager() : pStateBase(new StateWalk) {}

	void Action();

	void NextState();
};

