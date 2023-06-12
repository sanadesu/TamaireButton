#include "ButtonManager.h"
#include "Button.h"
#include "Input.h"
#include <list>
#include<algorithm>

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
			isStickMove = true;

		if (IsPushUP(screenID_move))
			NextSelectButton(screenID_move, true, false);
		if (IsPushDOWN(screenID_move))
			NextSelectButton(screenID_move, false, false);
		if (IsPushRIGHT(screenID_move))
			NextSelectButton(screenID_move, true, true);
		if (IsPushLEFT(screenID_move))
			NextSelectButton(screenID_move, false, true);
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

	//������������
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

	//�E����������
	bool IsPushRIGHT(int screenID_)
	{
		if ((Input::IsKeyDown(DIK_RIGHT) && screenID_ == 0) ||
			Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT, screenID_) ||
			(Input::GetPadStickL(screenID_).x > 0 && isStickMove))
			return true;
		else
			return false;
	}

	//������������
	bool IsPushLEFT(int screenID_)
	{
		if ((Input::IsKeyDown(DIK_LEFT) && screenID_ == 0) ||
			Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT, screenID_) ||
			(Input::GetPadStickL(screenID_).x < 0 && isStickMove))
			return true;
		else
			return false;
	}

	//���ɑI������{�^��
	void NextSelectButton(int screenID_, bool isPlus_, bool isHorizontal)
	{
		//�ړ���{�^��
		Button* nearButton = ButtonManager::GetNowButton(screenID_);
		std::vector<std::pair<float, Button*>> vNearButton;

		//�S�{�^��
		for (auto* i : ButtonManager::GetButtonList(screenID_))
		{
			//�Y���{�^�����x�N�^�[�ɓ����
			if (isPlus_)
			{
				if (isHorizontal)
				{
					if (i->GetPosition().x > ButtonManager::GetSelectButtonPos(screenID_).x && i->GetPosition().y == GetSelectButtonPos(screenID_).y)
						vNearButton.push_back({ i->GetPosition().x,i });
				}
				else
				{
					if (i->GetPosition().y > ButtonManager::GetSelectButtonPos(screenID_).y)
						vNearButton.push_back({ i->GetPosition().y,i });
				}
			}
			else
			{
				if (isHorizontal)
				{
					if (i->GetPosition().x < ButtonManager::GetSelectButtonPos(screenID_).x && i->GetPosition().y == GetSelectButtonPos(screenID_).y)
						vNearButton.push_back({ i->GetPosition().x,i });
				}
				else
				{
					if (i->GetPosition().y < ButtonManager::GetSelectButtonPos(screenID_).y)
						vNearButton.push_back({ i->GetPosition().y,i });
				}
			}
		}

		if (vNearButton.size() == 1)
		{
			nearButton = vNearButton[0].second;
		}
		else if (vNearButton.size() > 0)
		{
			//�\�[�g����
			if (isPlus_)
				sort(vNearButton.begin(), vNearButton.end());
			else
				sort(vNearButton.rbegin(), vNearButton.rend());

			if (isHorizontal == false)
			{
				//��ԋ߂��{�^�������߂�
				if (vNearButton[0].first == vNearButton[1].first &&
					abs(vNearButton[0].second->GetPosition().x - GetSelectButtonPos(screenID_).x) > abs(vNearButton[1].second->GetPosition().x - GetSelectButtonPos(screenID_).x))
				{
					vNearButton[0] = vNearButton[1];
				}
			}

			nearButton = vNearButton[0].second;
		}

		//�I�𒆃{�^���ύX�i�S���j
		ButtonManager::GetNowButton(screenID_)->SetIsNextSelect(false);
		nearButton->SetIsNextSelect(true);

		isStickMove = false;
		ButtonManager::SetSelectChange(true);
	}
}