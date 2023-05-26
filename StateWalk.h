#pragma once
#include "StateBase.h"
#include "StateCharge.h"
#include "Engine/Transform.h"

class StateWalk : 
	public StateBase
{
	//StateWalk(Transform t_) :StateBase(t_) {}
	void Action() override;

	StateBase* NextState() override;
};

