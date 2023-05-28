#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "GameObject.h"
#include "Sprite.h"
#include "Transform.h"


class Button :public GameObject
{
private:
	//bool isSelect;
	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	int hPict_;								//�摜�ԍ�
	int hSound_[Sound::SOUND_MAX];    //�T�E���h�ԍ�
	int alpha;
	int screenID;
	bool isStickMove;
	bool isNextSelect;
	bool isNowSelect;
	Button* firstButton;

	XMFLOAT3 nowButtonPos;
	//std::pair<float, float> framePos[5];
	
protected:

	//�{�^���������ꂽ�Ƃ��ɂ��鏈��
	virtual void Event();

	//�I���{�^���̓����@
	virtual void SelectMove(int screenID);

	//�I�����ꂽ�u��
	virtual void IsSelect();

	//�I���������ꂽ�u��
	virtual void IsSelectReleas();

	//�T�u�A�b�v�f�[�g
	virtual void SubUpdate();

	//�T�u������
	virtual void SubInitialize();

	//�摜�Z�b�g
	void SetImage(const std::string& path ,Transform trans);
	
	//�I�𒆃{�^��
	//void SetNowButton(XMFLOAT3 selectButton);

	//���̑I���{�^���Z�b�g
	void SetIsNextSelect(bool state_);

	//���̑I���{�^���擾
	bool GetIsNextSelect();

	//�I���{�^���Z�b�g
	void SetIsNowSelect(bool state_);
	
	//�I���{�^���擾
	bool GetIsNowSelect();

	void ButtonSwith();

	void SetIsFirst(Button* first);

	Button* GetIsFirst();

	void SetAlpha(int alpha_);

	void SetScreenID(int screenID);



public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Button(GameObject* parent, const std::string& name);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	virtual int GetScreenID();
};