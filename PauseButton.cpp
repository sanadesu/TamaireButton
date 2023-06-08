#include "PauseButton.h"
#include "Engine/Image.h"
#include "Engine/ButtonManager.h"
#include "Engine/SceneManager.h"
#include "Engine/Direct3D.h"
#include "Engine/Audio.h"
#include "UI.h"

//定数
namespace
{

	static const float BUTTON_POS_X = 0.3f;
	static const float BUTTON_POX_Y = -0.25f;

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
		hPict_ = Image::Load("PauseRetrySelect.png");
		assert(hPict_ >= 0);
		SetIsNextSelect(true);
		IsSelect();
		SetIsFirst(this);
	}
	else
	{
		transform_.position_ = XMFLOAT3(BUTTON_POS_X, BUTTON_POX_Y, 0);

		hPict_ = Image::Load("PauseButtonTitle.png");
		assert(hPict_ >= 0);
	}
	ButtonManager::AddButton((Button*)this, 0);
	pTime = (Time*)FindObject("Time");
	pPlayStop = (PlayStop*)FindObject("PlayStop");
}

//更新
void PauseButton::SubUpdate()
{
	ButtonSwith();
	if (pPlayStop->GetIsRetry())
	{
		KillMe();
	}
}

//描画
void PauseButton::Draw()
{
	if (Direct3D::lr == 0)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//ボタンが押されたときにする処理
void PauseButton::Event()
{
	
	if (buttonID == 0)
	{
		pPlayStop = (PlayStop*)FindObject("PlayStop");
		//続ける
		pPlayStop->SetIsStopPause(false);
		pTime->SetStart();
		pPlayStop->SetIsStart(true);
		pPlayStop->SetIsRetry(true);
	}
	else
	{
		UI* pUI = (UI*)FindObject("UI");
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		//ロード
		pUI->LoadSet();
		Audio::Release();
		//タイトルへ移動
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//選択された瞬間
void PauseButton::IsSelect()
{
	//選択中にする
	ButtonManager::SetNowButton(this);

	//画像変える
	if (buttonID == 0)
		hPict_ = Image::Load("PauseRetrySelect.png");
	else
		hPict_ = Image::Load("PauseTitleSelect.png");
}

void PauseButton::IsSelectReleas()
{
	//画像戻す
	if (buttonID == 0)
		hPict_ = Image::Load("PauseButtonRetry.png");
	else
		hPict_ = Image::Load("PauseButtonTitle.png");
}
