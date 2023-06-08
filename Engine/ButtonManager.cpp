#include "ButtonManager.h"
#include "Button.h"
#include "Input.h"
#include <list>

namespace ButtonManager
{
	static const int ALL_SCREEN_ID = 5;//
	bool isStickMove = true;//�X�e�B�b�N�𓮂�������
	std::list<Button*> buttonList[4];
	Button* Selecting_[4] = { nullptr,nullptr,nullptr,nullptr };
	Button* nextSelect = nullptr;
	bool selectChange = false;

	//�{�^���ǉ�
	void ButtonManager::AddButton(Button* button,int screenID)
	{
		buttonList[screenID].push_back(button);
	}

	//�{�^���J��
	void ButtonRelease()
	{
		for (int i = 0; i < 4; i++)
		{
			buttonList[i].clear();
		}
	}

	std::list<Button*> ButtonManager::GetButtonList(int screenID)
	{
		return buttonList[screenID];
	}

	//�I�𒆃{�^��
	void ButtonManager::SetNowButton(Button* sel)
	{
		Selecting_[sel->GetScreenID()] = sel;
	}

	Button* ButtonManager::GetNowButton(int screenID_)
	{
		return Selecting_[screenID_];
	}

	//�I�𒆃{�^���̈ʒu
	XMFLOAT3 ButtonManager::GetSelectButtonPos(int screenID_)
	{
		if(Selecting_[screenID_] != nullptr)
			return Selecting_[screenID_]->GetPosition();
		return XMFLOAT3(0, 0, 0);
	}

	void ButtonManager::SetNextSelectButton(Button* next)
	{
		nextSelect = next;
	}

	Button* ButtonManager::GetNextButton()
	{
		return nextSelect;
	}

	void ButtonManager::SetSelectChange(bool isChange)
	{
		selectChange = isChange;
	}

	bool ButtonManager::GetSelectChange()
	{
		return selectChange;
	}

	//�I���{�^���̓����@
	void ButtonManager::SelectMove(int screenID_move)
	{
		if (screenID_move == ALL_SCREEN_ID)
			screenID_move = 0;
		if (Input::GetPadStickL(screenID_move).y == 0 && Input::GetPadStickL(screenID_move).x == 0)
		{
			isStickMove = true;
		}

		if (IsPushUP(screenID_move))
		{
			float selectingPosY = ButtonManager::GetSelectButtonPos(screenID_move).y;
			//������ꏊ nowPos;
			Button* nearButton = ButtonManager::GetNowButton(screenID_move);

			for (auto i : GetButtonList(screenID_move))
			{
				//��̂�x�N�^�[�ɓ����
				//�\�[�g����
				//��̂����
				if (i->GetPosition().y > selectingPosY &&//�I�𒆃{�^������ɂ��違
					(nearButton->GetPosition().y == selectingPosY ||//�I�𒆃{�^����Y��������||
						(nearButton->GetPosition().y >= i->GetPosition().y &&//��&
							((i->GetPosition().y == nearButton->GetPosition().y &&//Y�����������I�𒆃{�^��X���߂��ق��ɂ���||
								abs(ButtonManager::GetSelectButtonPos(screenID_move).x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos(screenID_move).x - nearButton->GetPosition().x)) ||
								i->GetPosition().y != nearButton->GetPosition().y))))//
				{
					nearButton = i;
				}
			}
			ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
			nearButton->SetIsNextSelect(true);

			isStickMove = false;
			ButtonManager::SetSelectChange(true);
		}
		if (IsPushDOWN(screenID_move))
		{
			//�I�𒆃{�^���̈ʒu
			float selectingPosY = ButtonManager::GetSelectButtonPos(screenID_move).y;
			//�ړ���{�^��
			Button* nearButton = ButtonManager::GetNowButton(screenID_move);
			for (auto* i : ButtonManager::GetButtonList(screenID_move))
			{
				if (i->GetPosition().y < selectingPosY &&
					(nearButton->GetPosition().y == selectingPosY ||
						(nearButton->GetPosition().y <= i->GetPosition().y &&
							((i->GetPosition().y == nearButton->GetPosition().y &&
								abs(ButtonManager::GetSelectButtonPos(screenID_move).x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos(screenID_move).x - nearButton->GetPosition().x)) ||
								i->GetPosition().y != nearButton->GetPosition().y))))
				{
					nearButton = i;
				}
			}
			//�I�𒆃{�^���ύX�i�S���j
			ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
			nearButton->SetIsNextSelect(true);

			isStickMove = false;
			ButtonManager::SetSelectChange(true);
		}
		if (IsPushRIGHT(screenID_move))
		{
			//�����ƃX�N���[���ꏏ�H�H
			float selectingPosX = ButtonManager::GetSelectButtonPos(screenID_move).x;
			//�ړ���{�^��
			Button* nearButton = ButtonManager::GetNowButton(screenID_move);
			for (auto i : ButtonManager::GetButtonList(screenID_move))
			{
				if (i->GetPosition().y == ButtonManager::GetSelectButtonPos(screenID_move).y &&
					(i->GetPosition().x > selectingPosX &&
						(nearButton->GetPosition().x == selectingPosX ||
							(nearButton->GetPosition().x >= i->GetPosition().x &&//
								(i->GetPosition().x == nearButton->GetPosition().x &&//
									i->GetPosition().x != nearButton->GetPosition().x)))))
				{
					nearButton = i;
				}
			}
			ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
			nearButton->SetIsNextSelect(true);

			isStickMove = false;
			ButtonManager::SetSelectChange(true);
		}
		if (IsPushLEFT(screenID_move))
		{
			//�I�𒆃{�^���̈ʒu
			float selectingPosX = ButtonManager::GetSelectButtonPos(screenID_move).x;
			//�ړ���{�^��
			Button* nearButton = ButtonManager::GetNowButton(screenID_move);
			for (auto* i : ButtonManager::GetButtonList(screenID_move))
			{
				if (i->GetPosition().y == ButtonManager::GetSelectButtonPos(screenID_move).y &&
					(i->GetPosition().x < selectingPosX &&
						(nearButton->GetPosition().x == selectingPosX ||
							(nearButton->GetPosition().x <= i->GetPosition().x &&
								(i->GetPosition().x == nearButton->GetPosition().x &&
									i->GetPosition().x != nearButton->GetPosition().x)))))
				{
					nearButton = i;
				}
			}
			//�I�𒆃{�^���ύX�i�S���j
			ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
			nearButton->SetIsNextSelect(true);
			isStickMove = false;
			ButtonManager::SetSelectChange(true);
		}
	}

	//�����������
	bool ButtonManager::IsPushUP(int screenID_)
	{
		if ((Input::IsKeyDown(DIK_UP) && screenID_ == 0) ||
			Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP, screenID_) ||
			(Input::GetPadStickL(screenID_).y > 0 && isStickMove))
			return true;
		else
			return false;
	}
	bool IsPushDOWN(int screenID_)
	{
		if(((Input::IsKeyDown(DIK_DOWN) && screenID_ == 0) ||
			Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN, screenID_) || (
				Input::GetPadStickL(screenID_).y < 0 && isStickMove)) &&
			ButtonManager::GetSelectChange() == false)
			return true;
		else
			return false;
	}
	bool IsPushRIGHT(int screenID_)
	{
		if ((Input::IsKeyDown(DIK_RIGHT) && screenID_ == 0) ||
			Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT, screenID_) ||
			(Input::GetPadStickL(screenID_).x > 0 && isStickMove))
			return true;
		else
			return false;
	}
	bool IsPushLEFT(int screenID_)
	{
		if ((Input::IsKeyDown(DIK_LEFT) && screenID_ == 0) ||
			Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT, screenID_) ||
			(Input::GetPadStickL(screenID_).x < 0 && isStickMove))
			return true;
		else
			return false;
	}
}