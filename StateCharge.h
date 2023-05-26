#pragma once
#include "StateBase.h"
#include "StateThrow.h"

class StateCharge :
    public StateBase
{
    void Action() override;

    StateBase* NextState() override;
};

