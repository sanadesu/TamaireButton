#include "StateManager.h"
#include "State.h"
#include "StateCharge.h"
#include "StateThrow.h"

void StateManager::Action()
{
	//現在の状態のactionを行え！と命令
	pStateBase->Action();
}

void StateManager::NextState()
{
	//現在の状態オブジェクトを削除して、
	//次の状態に状態遷移
	StateBase* del = this->pStateBase;
	pStateBase = pStateBase->NextState();
	//本当はデストラクタをvirtualにして書いておかないとだめよ
	delete del;
}



//
//int main()
//{
//	//ステートマシンを初期化
//	State* state = new StateThrow();
//
//	//状態を出力
//	state->Put();
//
//	//スイッチを切り替える（Off→On）
//	state = state->Switch();
//	//状態を出力
//	state->Put();
//	delete state;
//}