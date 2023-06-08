#include "ButtonManager.h"
#include "Button.h"
#include "Input.h"
#include <list>

namespace ButtonManager
{
	static const int ALL_SCREEN_ID = 5;//
	bool isStickMove = true;//スティックを動かしたか
	std::list<Button*> buttonList[4];
	Button* Selecting_[4] = { nullptr,nullptr,nullptr,nullptr };
	Button* nextSelect = nullptr;
	bool selectChange = false;

	//ボタン追加
	void ButtonManager::AddButton(Button* button,int screenID)
	{
		buttonList[screenID].push_back(button);
	}

	//ボタン開放
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

	//選択中ボタン
	void ButtonManager::SetNowButton(Button* sel)
	{
		Selecting_[sel->GetScreenID()] = sel;
	}

	Button* ButtonManager::GetNowButton(int screenID_)
	{
		return Selecting_[screenID_];
	}

	//選択中ボタンの位置
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

	//選択ボタンの動き　
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
			//今いる場所 nowPos;
			Button* nearButton = ButtonManager::GetNowButton(screenID_move);

			for (auto i : GetButtonList(screenID_move))
			{
				//上のやつベクターに入れる
				//ソートする
				//上のやつ正解
				if (i->GetPosition().y > selectingPosY &&//選択中ボタンより上にある＆
					(nearButton->GetPosition().y == selectingPosY ||//選択中ボタンとY軸が同じ||
						(nearButton->GetPosition().y >= i->GetPosition().y &&//上&
							((i->GetPosition().y == nearButton->GetPosition().y &&//Y軸が同じ時選択中ボタンXが近いほうにする||
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
			//選択中ボタンの位置
			float selectingPosY = ButtonManager::GetSelectButtonPos(screenID_move).y;
			//移動先ボタン
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
			//選択中ボタン変更（全部）
			ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
			nearButton->SetIsNextSelect(true);

			isStickMove = false;
			ButtonManager::SetSelectChange(true);
		}
		if (IsPushRIGHT(screenID_move))
		{
			//自分とスクリーン一緒？？
			float selectingPosX = ButtonManager::GetSelectButtonPos(screenID_move).x;
			//移動先ボタン
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
			//選択中ボタンの位置
			float selectingPosX = ButtonManager::GetSelectButtonPos(screenID_move).x;
			//移動先ボタン
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
			//選択中ボタン変更（全部）
			ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
			nearButton->SetIsNextSelect(true);
			isStickMove = false;
			ButtonManager::SetSelectChange(true);
		}
	}

	//上を押したか
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