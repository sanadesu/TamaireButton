#include "State.h"
#include <iostream>



void State::NextState(StateBase* state_)
{
}

void State::Walk()
{

}



//
//enum SwitchState
//{
//	On = 0,
//	Off
//};
//class Switch
//{
//public:
//	Switch() = delete;
//	Switch(SwitchState s)
//	{
//		state = s;
//	}
//	void Put()
//	{
//		switch (state)
//		{
//		case SwitchState::On:
//			std::cout << "���݂̃X�e�C�g��On" << std::endl;
//			break;
//		case SwitchState::Off:
//			std::cout << "���݂̃X�e�C�g��Off" << std::endl;
//			break;
//		default:
//			break;
//		}
//	}
//	void Change()
//	{
//		switch (state)
//		{
//		case SwitchState::On:
//			state = SwitchState::Off;
//			break;
//		case SwitchState::Off:
//			state = SwitchState::On;
//			break;
//		default:
//			break;
//		}
//	}
//private:
//	SwitchState state;
//};