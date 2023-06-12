#pragma once
#include "GameObject.h"

class Button;
namespace ButtonManager
{
	//ボタン追加
	void AddButton(Button* button,int screenID);

	//ボタンクリア
	void ButtonRelease();

	//ボタンリスト取得
	std::list<Button*> GetButtonList(int screenID);

	//選択中ボタンセット
	void SetNowButton(Button* sel);

	//選択中ボタン取得
	Button* GetNowButton(int screenID);

	//選択中ボタンの位置
	XMFLOAT3 GetSelectButtonPos(int screenID_);

	//次に選択するボタンセット
	void SetNextSelectButton(Button* next);

	//次に選択するボタン取得
	Button* GetNextButton();

	//選択変更セット
	void SetSelectChange(bool isChange);

	//選択変更取得
	bool GetSelectChange();

	//選択ボタンの動き　
	void SelectMove(int screenID);
	
	//ゲームモード選択ボタン生成
	template<class T>
	T* CreateButton(GameObject* pParent, const XMFLOAT3& position, int ID)
	{
		T* pNewObject = new T(pParent,ID);

		if (pParent != nullptr)
		{
			pParent->PushBackChild(pNewObject);
		}

		pNewObject->SetPosition(position);
		pNewObject->Initialize();

		return pNewObject;
	}

	template<class T>
	T* CreateButtonScreen(GameObject* pParent, const std::string name, int buttonID_, int screenID_)
	{
		T* pNewObject = new T(pParent, name, buttonID_, screenID_);

		if (pParent != nullptr)
		{
			pParent->PushBackChild(pNewObject);
		}

		//pNewObject->SetPosition(position);
		pNewObject->Initialize();

		return pNewObject;
	}

	//上を押したか
	bool IsPushUP(int screenID_);

	//上を押したか
	bool IsPushDOWN(int screenID_);

	//上を押したか
	bool IsPushRIGHT(int screenID_);

	//上を押したか
	bool IsPushLEFT(int screenID_);

	//次に選択するボタン
	void NextSelectButton(int screenID_, bool isPlus_, bool isHorizontal);
}