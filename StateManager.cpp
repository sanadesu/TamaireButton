#include "StateManager.h"
#include "State.h"
#include "StateCharge.h"
#include "StateThrow.h"

void StateManager::Action()
{
	//���݂̏�Ԃ�action���s���I�Ɩ���
	pStateBase->Action();
}

void StateManager::NextState()
{
	//���݂̏�ԃI�u�W�F�N�g���폜���āA
	//���̏�Ԃɏ�ԑJ��
	StateBase* del = this->pStateBase;
	pStateBase = pStateBase->NextState();
	//�{���̓f�X�g���N�^��virtual�ɂ��ď����Ă����Ȃ��Ƃ��߂�
	delete del;
}



//
//int main()
//{
//	//�X�e�[�g�}�V����������
//	State* state = new StateThrow();
//
//	//��Ԃ��o��
//	state->Put();
//
//	//�X�C�b�`��؂�ւ���iOff��On�j
//	state = state->Switch();
//	//��Ԃ��o��
//	state->Put();
//	delete state;
//}