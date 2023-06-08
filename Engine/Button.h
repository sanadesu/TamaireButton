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
	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	int hPict_;								//�摜�ԍ�
	int hSound_[Sound::SOUND_MAX];    //�T�E���h�ԍ�
	int alpha;//�����x
	int screenID;//�X�N���[���ԍ�
	bool isStickMove;//�X�e�B�b�N�𓮂�������
	bool isNextSelect;//���ɑI���ɂ���{�^����
	bool isNowSelect;//�I�𒆂̃{�^����
	Button* firstButton;//���߂ɑI������{�^��
	
	bool IsPushUP(int screenID_);
protected:

	//�{�^���������ꂽ�Ƃ��ɂ��鏈��
	virtual void Event();

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
	

	//���̑I���{�^���擾
	bool GetIsNextSelect();

	//�I���{�^���Z�b�g
	void SetIsNowSelect(bool state_);
	
	//�I���{�^���擾
	bool GetIsNowSelect();

	//�{�^���̐؂�ւ�
	void ButtonSwith();

	//���߂ɑI�������{�^���Z�b�g
	void SetIsFirst(Button* first);

	/// <summary>
	/// �A���t�@�l�Z�b�g
	/// </summary>
	/// <param name="alpha_">�����x,1�`255�܂�</param>
	void SetAlpha(int alpha_);

	//�X�N���[��ID�̃Z�b�g
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

	//���̑I���{�^���Z�b�g
	void SetIsNextSelect(bool state_);

	//�V�[��ID�擾
	virtual int GetScreenID();
};