#pragma once
#include "StateBase.h"
#include "Ball.h"
#include"Engine/GameObject.h"

class State :
	public StateBase, GameObject
{
	Ball* pBall = (Ball*)FindObject("Ball");
public:
	virtual void Action();
	void NextState(StateBase* state_);
	void Walk();

};

