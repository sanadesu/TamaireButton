#pragma once
#include "StateBase.h"
#include "StateWalk.h"

class StateThrow : 
	public StateBase
{
	void Action() override;

	StateBase* NextState() override;
};

