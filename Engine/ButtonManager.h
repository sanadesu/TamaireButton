#pragma once
#include "GameObject.h"

class Button;
namespace ButtonManager
{
	//�{�^���ǉ�
	void AddButton(Button* button,int screenID);

	//�{�^���N���A
	void ButtonRelease();

	//�{�^�����X�g�擾
	std::list<Button*> GetButtonList(int screenID);

	//�I�𒆃{�^���Z�b�g
	void SetNowButton(Button* sel);

	//�I�𒆃{�^���擾
	Button* GetNowButton(int screenID);

	//�I�𒆃{�^���̈ʒu
	XMFLOAT3 GetSelectButtonPos(int screenID_);

	//���ɑI������{�^���Z�b�g
	void SetNextSelectButton(Button* next);

	//���ɑI������{�^���擾
	Button* GetNextButton();

	//�I��ύX�Z�b�g
	void SetSelectChange(bool isChange);

	//�I��ύX�擾
	bool GetSelectChange();

	//�I���{�^���̓����@
	void SelectMove(int screenID);
	
	//�Q�[�����[�h�I���{�^������
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

	//�����������
	bool IsPushUP(int screenID_);

	//�����������
	bool IsPushDOWN(int screenID_);

	//�����������
	bool IsPushRIGHT(int screenID_);

	//�����������
	bool IsPushLEFT(int screenID_);

	//���ɑI������{�^��
	void NextSelectButton(int screenID_, bool isPlus_, bool isHorizontal);
}