#include "sceneManager.h"

#include "../TitleScene.h"
#include "../PlayScene.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "../SettingScene.h"
#include "Input.h"
#include "ButtonManager.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);//�^�C�g������X�^�[�g�ɂȂ���
	IsChange = false;
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_ || IsChange)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		//Audio::Release();
		Model::AllRelease();
		Image::AllRelease();
		ButtonManager::ButtonRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_SET: Instantiate<SettingScene>(this); break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;

		IsChange = false;
	}
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}

void SceneManager::SameScene()
{
	IsChange = true;
}
