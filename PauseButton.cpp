#include "PauseButton.h"
#include "Engine/Image.h"
#include "Engine/ButtonManager.h"
#include "Engine/SceneManager.h"
#include "Engine/Direct3D.h"
#include "Engine/Audio.h"
#include "UI.h"
#include "PlayStop.h"

//定数
namespace
{

	static const float BUTTON_POS_X = 0.4f;
	static const float BUTTON_POX_Y = -0.75f;

}

//コンストラクタ
PauseButton::PauseButton(GameObject* pParent, std::string name, int buttonID_, int screenID_)
	: Button(pParent, "PauseButton"), hPict_(-1)
{
	buttonID = buttonID_;
}

//初期化
void PauseButton::SubInitialize()
{
	if (buttonID == 0)
	{
		transform_.position_ = XMFLOAT3(-BUTTON_POS_X, BUTTON_POX_Y, 0);
		hPict_ = Image::Load("ResultRetrySelect.png");
		assert(hPict_ >= 0);
		SetIsNextSelect(true);
		IsSelect();
		SetIsFirst(this);
	}
	else
	{
		transform_.position_ = XMFLOAT3(BUTTON_POS_X, BUTTON_POX_Y, 0);

		hPict_ = Image::Load("ResultTitleButton.png");
		assert(hPict_ >= 0);
	}
	ButtonManager::AddButton((Button*)this, 0);
}

//更新
void PauseButton::SubUpdate()
{
	ButtonSwith();
}

//描画
void PauseButton::Draw()
{
	PlayStop* pPlayStop = (PlayStop*)FindObject("PlayStop");
	if (Direct3D::lr == 0 && pPlayStop->GetIsStart() == false)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//ボタンが押されたときにする処理
void PauseButton::Event()
{
	UI* pUI = (UI*)FindObject("UI");
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//ロード
	//pUI->LoadSet();
	//Audio::Release();

	if (buttonID == 0)
	{
		//pSceneManager->SameScene();
	}
	else
	{
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
	const char* buttonName[] = { "PlayButton" ,"TitleButton" };

	/*for (int i = 0; i < 2; i++)
	{
		PauseButton* pPauseButton = (PauseButton*)FindObject(buttonName[i]);
		pPauseButton->KillMe();
	}*/
	//KillMe();
}

//選択された瞬間
void PauseButton::IsSelect()
{
	//選択中にする
	ButtonManager::SetNowButton(this);

	//画像変える
	if (buttonID == 0)
		hPict_ = Image::Load("ResultRetrySelect.png");
	else
		hPict_ = Image::Load("ResultTitleSelect.png");
}

void PauseButton::IsSelectReleas()
{
	//画像戻す
	if (buttonID == 0)
		hPict_ = Image::Load("ResultRetryButton.png");
	else
		hPict_ = Image::Load("ResultTitleButton.png");
}
