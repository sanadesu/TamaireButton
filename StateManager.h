#pragma once
#include "StateWalk.h"
#include "StateBase.h"

class StateManager
{
	StateBase* pStateBase;
public:
	//‰Šúó‘Ô‚ğA•à‚­‚©‚çn‚ß‚é
	StateManager() : pStateBase(new StateWalk) {}

	void Action();

	void NextState();
};

