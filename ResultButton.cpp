#include "ResultButton.h"
#include "Engine/ButtonManager.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Result.h"
#include "UI.h"
#include "Engine/Audio.h"
//コンストラクタ
ResultButton::ResultButton(GameObject* pParent,std::string name, int buttonID_ ,int screenID_)
	: Button(pParent, "ResultButton"),hPict_(-1)
{
	buttonID = buttonID_;
}

//初期化
void ResultButton::SubInitialize()
{
	if (buttonID == 0)
	{
		transform_.position_ = XMFLOAT3(-0.4f, RESULT_POX_Y, 0);
		hPict_ = Image::Load("ResultRetrySelect.png");
		assert(hPict_ >= 0); 
		SetIsNextSelect(true);
		IsSelect();
		SetIsFirst(this);
	}
	else
	{
		transform_.position_ = XMFLOAT3(0.4f, RESULT_POX_Y, 0);

		hPict_ = Image::Load("ResultTitleButton.png");
		assert(hPict_ >= 0); 
		//SetImage("ResultTitleButton.png", transform_);
	}
	ButtonManager::AddButton((Button*)this, 0);
}

//更新
void ResultButton::SubUpdate()
{
	ButtonSwith();

}

void ResultButton::Draw()
{
	if (Direct3D::lr == 0)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//ボタンが押されたときにする処理
void ResultButton::Event()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	Result* pResult = (Result*)FindObject("Result");
	UI* pUI = (UI*)FindObject("UI");
	//ロード
	pUI->LoadSet();
	Audio::Release();
	int hSound_ = Audio::Load("Button.wav", false, 0.8f, 1);
	Audio::Play(hSound_);
	if (buttonID == 0)
	{
		pSceneManager->SameScene();
	}
	else
	{
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
	pResult->KillMe();
}

//選択された瞬間
void ResultButton::IsSelect()
{
	//選択中にする
	ButtonManager::SetNowButton(this);
	if (buttonID == 0)
	{
		//画像変える
		hPict_ = Image::Load("ResultRetrySelect.png");
		//SetImage("ResultRetrySelect.png", transform_);
	}
	else
	{
		//画像変える
		hPict_ = Image::Load("ResultTitleSelect.png");
		//SetImage("ResultTitleSelect.png", transform_);
	}
}

void ResultButton::IsSelectReleas()
{
	//画像戻す
	if (buttonID == 0)
		hPict_ = Image::Load("ResultRetryButton.png");
	else
		hPict_ = Image::Load("ResultTitleButton.png");
}
