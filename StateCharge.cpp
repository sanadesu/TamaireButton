#include "StateCharge.h"
#include "StateThrow.h"
#include "State.h"
#include<iostream>
class StateThrow;

void StateCharge::Action()
{
    //stateText = "Charge";
    //XMFLOAT3 origine = XMFLOAT3(0, 0, 0);
    //XMVECTOR vOrigin = XMLoadFloat3(&origine);
    //XMFLOAT3 HandPos = Model::GetBonePosition(hModel_, "joint1");
    //XMVECTOR vPlayerPos = XMLoadFloat3(&HandPos);
    //XMVECTOR vGoal = vOrigin - vPlayerPos; //ゴールへの向き

    //XMVECTOR vGoalLength = XMVector3Length(vGoal);
    //goalLength = XMVectorGetX(vGoalLength);

    //XMFLOAT3 vGoalRotate;

    //XMStoreFloat3(&vGoalRotate, vGoal);

    //transform_.rotate_.y = (float)(atan2(vGoalRotate.x, vGoalRotate.z) * 180.0 / 3.14);

    ////力ためるやつ
    //powerY -= POWER;
    //powerZ += POWER;
    //trajectoryY = powerY;
    //trajectoryZ = powerZ;
    ////右手の位置
    //trans.position_ = Model::GetBonePosition(hModel_, "joint1");

    //for (int j = 0; j < PORY_LENGTH; j++)
    //{
    //    if (j % 3 == 0)
    //    {
    //        pLine->AddPosition(trans.position_);
    //    }

    //    // 加速度の演算
    //    trajectoryY += GRAVITY;

    //    trans.rotate_ = transform_.rotate_;

    //    trans = FrontDirection(0, -trajectoryY, trajectoryZ, transform_.rotate_.y, trans);

    //    trajectoryZ *= RESISTANCE;//抵抗

    //}
    //chargePower = true;

    ////あとでAIかどうか判別
    //if (powerZ > powf(goalLength - (rand() % 3000 / 1000), 0.5f) * 0.22f && playerID == 1)
    //{
    //    nowState = THROW_STATE;
    //}
}

StateBase* StateCharge::NextState()
{
	return(new StateThrow);
}

//
//class DuckingState : public HeroineState
//{
//public:
//	DuckingState()
//		:chargeTime_(0)
//	{}
//
//	virtual void handleInput(Heroine& heroine, Input input)
//	{
//		if (input == RELEASE_DOWN)
//		{
//			heroine.setGraphics(IMAGE_STAND);
//		}
//	}
//
//	virtual void update(Heroine& heroine)
//	{
//		chargeTime_++;
//		if (chargeTime_ > MAX_CHARGE)
//		{
//			heroine.superBomb();
//		}
//	}
//
//private:
//	int chargeTime_;
//};



//
////Off状態のクラス
//class StateCharge :public State
//{
//public:
//    void Put()
//    {
//        std::cout << "現在のステイトはOff" << std::endl;
//    }
//    State* Switch();
//
//};
//
//State* StateCharge::Switch()
//{
//    StateThrow* ret = new StateThrow();
//    delete this;
//    return ret;
//}