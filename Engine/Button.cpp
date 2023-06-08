#include "Button.h"
#include "Global.h"
#include "Button.h"
#include "Input.h"
#include "Audio.h"
#include "Image.h"
#include "ButtonManager.h"

//定数
namespace
{
	static const int ALL_CREEN_ID = 5;
	static const int ALPHA_MAX = 255;

}

//コンストラクタ
Button::Button(GameObject* parent, const std::string& name)
	:GameObject(parent,"SettingButton"),hSound_{-1,-1}
{
}

//初期化
void Button::Initialize()
{
	isStickMove = true;
	isNextSelect = false;
	isNowSelect = false;
	screenID = 0;
	alpha = ALPHA_MAX;
	//使用するサウンドファイル名
	const char* soundFileName[] = { "Button.wav", "Move.wav" };

	//ロード
	for (int i = 0; i < Sound::SOUND_MAX; i++)
	{
		hSound_[i] = Audio::Load(soundFileName[i], false, 0.8f, 10);
		assert(hSound_[i] >= 0);
	}

	SubInitialize();
}

//更新
void Button::Update()
{
	if (ButtonManager::GetSelectChange() == false || firstButton == this)
	{
		//選択移動したとき
		if (ButtonManager::GetNowButton(this->GetScreenID()) == this)
		{
			ButtonManager::SelectMove(screenID);
		}
		ButtonManager::SetSelectChange(false);
	}
	
	SubUpdate();

	//決定したとき
	if ((Input::IsKeyDown(DIK_SPACE) || Input::IsPadButtonDown(XINPUT_GAMEPAD_A, screenID)) && this == ButtonManager::GetNowButton(screenID))
	{
		Audio::Play(hSound_[SOUND_BUTTON]);
		Event();
	}
}

//描画
void Button::Draw()
{
	Image::SetAlpha(hPict_, alpha);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void Button::Release()
{
}



//ボタンが押されたときにする処理
void Button::Event()
{
}
//選択された瞬間
void Button::IsSelect()
{
}

//選択解除された瞬間
void Button::IsSelectReleas()
{
}

//サブアップデート
void Button::SubUpdate()
{
}

//サブ初期化
void Button::SubInitialize()
{
}

//画像を設定
void Button::SetImage(const std::string& path,Transform trans)
{
	Image::SetTransform(hPict_, trans);
	//画像データのロード
	hPict_ = Image::Load(path);

	//ロードされたか確認
	assert(hPict_ >= 0);
}


//次の選択ボタンセット
void Button::SetIsNextSelect(bool state_)
{
	isNextSelect = state_;
}

//次の選択ボタン取得
bool Button::GetIsNextSelect()
{
	return isNextSelect;
}

//選択ボタンセット
void Button::SetIsNowSelect(bool state_)
{
	isNowSelect = state_;
}

//選択ボタン取得
bool Button::GetIsNowSelect()
{
	return isNowSelect;
}

//ボタンの切り替え
void Button::ButtonSwith()
{
	if (GetIsNextSelect() != GetIsNowSelect())
	{
		Audio::Play(hSound_[SOUND_MOVE]);
		SetIsNowSelect(GetIsNextSelect());
		if (GetIsNowSelect())
		{
			IsSelect();
			ButtonManager::SetNowButton(this);
		}
		else
			IsSelectReleas();
	}
}

//初めに選択されるボタンセット
void Button::SetIsFirst(Button* first)
{
	firstButton = first;
}

// アルファ値セット
void Button::SetAlpha(int alpha_)
{
	alpha = alpha_;
}

//スクリーンIDのセット
void Button::SetScreenID(int screenID_)
{
	screenID = screenID_;
}

//シーンID取得
int Button::GetScreenID()
{
	return screenID;
}
