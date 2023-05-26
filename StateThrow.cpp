#include "StateThrow.h"
#include "StateCharge.h"
#include "State.h"
#include<iostream>
class StateWalk;

void StateThrow::Action()
{
    //stateText = "Throw";
    //if (rightHand == pBallRight->GetBallNum())
    //{
    //    pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
    //    chargePower = false;
    //    powerY = 0;
    //    powerZ = 0;
    //    rightHand = leftHand;
    //    leftHand = -1;
    //    pBallRight = pBallLeft;
    //    pBallLeft = nullptr;
    //    //あとでAIかどうか判別
    //    if (playerID == 1 && pBallRight == nullptr)
    //    {
    //        nowState = WALK_STATE;
    //    }
    //    else
    //    {
    //        nowState = CHARGE_STATE;
    //    }//nextState
    //}
}

StateBase* StateThrow::NextState()
{
	return(new StateWalk);//nextState
}




//
////On状態のクラス
//class StateThrow :public State
//{
//public:
//    void Put()
//    {
//        std::cout << "現在のステイトはOn" << std::endl;
//    }
//    State* Switch();
//};
//State* StateThrow::Switch()
//{
//    StateCharge* ret = new StateCharge();
//    delete this;
//    return ret;
//}