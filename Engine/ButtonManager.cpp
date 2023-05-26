#include "ButtonManager.h"
#include "Button.h"
#include <list>

namespace ButtonManager
{
	std::list<Button*> buttonList[4];
	Button* Selecting_[4] = { nullptr,nullptr,nullptr,nullptr };
	Button* nextSelect = nullptr;
	bool selectChange = false;

	//?????
	void ButtonManager::AddButton(Button* button,int screenID)
	{
		buttonList[screenID].push_back(button);
	}

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
	
}