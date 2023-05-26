#include "StateWalk.h"
class StateCharge;

void StateWalk::Action()
{
    /*stateText = "Walk";
    if (moveLimit > CIRCLE_RANGE)
        transform_.rotate_.y += 137;

    transform_ = FrontDirection(0, 0, PLAYER_MOVE, transform_.rotate_.y, transform_);*/
}

StateBase* StateWalk::NextState()
{
    return(new StateCharge);
}
