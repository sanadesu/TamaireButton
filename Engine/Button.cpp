#include "Button.h"
#include "Global.h"
#include "Button.h"
#include "Input.h"
#include "Audio.h"
#include "Image.h"
#include "ButtonManager.h"


//コンストラクタ
Button::Button(GameObject* parent, const std::string& name)
	:GameObject(parent,"SettingButton"),hSound_{-1,-1}
{
}
//
////コンストラクタ
//Button::Button(GameObject* pParent, const std::string name, int buttonID_, int screenID_)
//	:GameObject(parent, "SettingButton")
//{
//}

//初期化
void Button::Initialize()
{
	isStickMove = true;
	isNextSelect = false;
	isNowSelect = false;
	screenID = 0;
	alpha = 255;
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
	if (ButtonManager::GetSelectChange() == false || GetIsFirst() == this)
	{

		//次のボタン
		//if (ButtonManager::GetNowButton() != ButtonManager::GetNextButton() && ButtonManager::GetNextButton() != nullptr)
		//{
		//	ButtonManager::GetNowButton()->IsSelectReleas();//
		//	//ボタンマネージャー呼ぶ
		//	ButtonManager::GetNextButton()->IsSelect();
		//}

		//選択移動したとき
		if (ButtonManager::GetNowButton(this->GetScreenID()) == this)
		{
			SelectMove(screenID);
		}
		ButtonManager::SetSelectChange(false);
	}
	

	//SelectMove();
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

//選択ボタンの動き　
void Button::SelectMove(int screenID_move)
{
	if(screenID_move == 5)
		screenID_move = 0;
	if (Input::GetPadStickL(screenID_move).y == 0 && Input::GetPadStickL(screenID_move).x == 0)
	{
		isStickMove = true;
	}

	if (((Input::IsKeyDown(DIK_UP) && screenID_move == 0)||
		Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP, screenID_move) ||
		(Input::GetPadStickL(screenID_move).y > 0 && isStickMove))  /* && screenID_move == this->GetScreenID()*/)
	{
		float selectingPosY = ButtonManager::GetSelectButtonPos(screenID_move).y;
		//今いる場所 nowPos;
		//float minPos = ButtonManager::GetNowButton()->GetPosition().y;
		Button* nearButton = ButtonManager::GetNowButton(screenID_move);
		
		for (auto i : ButtonManager::GetButtonList(screenID_move))
		{
			/*if (selectingPosY < i->GetPosition().y &&
				i->GetPosition().y != ButtonManager::GetSelectButtonPos().y &&
				nearButton->GetPosition().y <= i->GetPosition().y)
			{
				if (i->GetPosition().y == nearButton->GetPosition().y)
				{
					if (abs(ButtonManager::GetSelectButtonPos().x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos().x - nearButton->GetPosition().x))
						nearButton = i;
				}
				else
					nearButton = i;
			}*/

			if (i->GetPosition().y > selectingPosY &&
				(nearButton->GetPosition().y == selectingPosY ||
				(nearButton->GetPosition().y >= i->GetPosition().y &&//
				((i->GetPosition().y == nearButton->GetPosition().y &&//
				abs(ButtonManager::GetSelectButtonPos(screenID_move).x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos(screenID_move).x - nearButton->GetPosition().x)) ||
				i->GetPosition().y != nearButton->GetPosition().y))))
			{
				nearButton = i;
			}
		}
		//ButtonManager::SetNextSelectButton(nearButton);
		//SetIsNextSelect(nearButton);
		ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
		nearButton->SetIsNextSelect(true);
		
		isStickMove = false;
		ButtonManager::SetSelectChange(true);
	}
	if (((((Input::IsKeyDown(DIK_DOWN) && screenID_move == 0)|| 
		Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN, screenID_move) || (
			Input::GetPadStickL(screenID_move).y < 0 && isStickMove)))&& 
		ButtonManager::GetSelectChange() == false)/* && screenID_move == this->GetScreenID()*/)
	{
		//選択中ボタンの位置
		float selectingPosY = ButtonManager::GetSelectButtonPos(screenID_move).y;
		//float minPos = ButtonManager::GetSelectButtonPos().y;
		//移動先ボタン
		//auto nearButton = ButtonManager::GetButtonList().end();
		Button* nearButton = ButtonManager::GetNowButton(screenID_move);
		//--nearButton;
		for (auto* i : ButtonManager::GetButtonList(screenID_move))
		{
				if (i->GetPosition().y < selectingPosY &&
				(nearButton->GetPosition().y == selectingPosY ||
				(nearButton->GetPosition().y <= i->GetPosition().y &&
				((i->GetPosition().y == nearButton->GetPosition().y &&
				abs(ButtonManager::GetSelectButtonPos(screenID_move).x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos(screenID_move).x - nearButton->GetPosition().x)) ||
				i->GetPosition().y != nearButton->GetPosition().y))))
				{
					
					nearButton = i;
					
					/*else if (nearButton->GetPosition().y <= i->GetPosition().y &&
						((i->GetPosition().y == nearButton->GetPosition().y &&
							abs(ButtonManager::GetSelectButtonPos().x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos().x - nearButton->GetPosition().x)) ||
							i->GetPosition().y != nearButton->GetPosition().y))*/
					{
						/*if ((i->GetPosition().y == nearButton->GetPosition().y && 
							abs(ButtonManager::GetSelectButtonPos().x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos().x - nearButton->GetPosition().x)) ||
							i->GetPosition().y != nearButton->GetPosition().y)
					*/	{
							//if (abs(ButtonManager::GetSelectButtonPos().x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos().x - nearButton->GetPosition().x))
								//nearButton = i;
						}
						/*else if(i->GetPosition().y != nearButton->GetPosition().y)
							nearButton = i;*/



						/*if (i->GetPosition().y == nearButton->GetPosition().y)
						{
							if (abs(ButtonManager::GetSelectButtonPos().x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos().x - nearButton->GetPosition().x))
								nearButton = i;
						}
						else
							nearButton = i;*/
					}
				}
			
		
			
			
			
			
			
			/*
			if (selectingPosY > i->GetPosition().y &&
				(i->GetPosition().y != ButtonManager::GetSelectButtonPos().y &&
				nearButton->GetPosition().y >= i->GetPosition().y))*/

			/*if(nearButton->GetPosition().y == selectingPosY ||
				(i->GetPosition().y >= nearButton->GetPosition().y &&
					selectingPosY > i->GetPosition().y))*/
			//if(i->GetPosition().y < selectingPosY)
			{
				//if (nearButton->GetPosition().y > i->GetPosition().y &&
					//nearButton->GetPosition().y < selectingPosY)
				{
					/*if (i->GetPosition().y == nearButton->GetPosition().y)
					{
						if (abs(ButtonManager::GetSelectButtonPos().x - i->GetPosition().x) < abs(ButtonManager::GetSelectButtonPos().x - nearButton->GetPosition().x))
							nearButton = i;
					}*/
					//else
						//nearButton = i;
				}
				/*else
				{
					nearButton = i;
				}
				*/
			}
		}
		//選択中ボタン変更（全部）
		//ButtonManager::GetNowButton()->IsSelectReleas();
		//nearButton->IsSelect();
		ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
		nearButton->SetIsNextSelect(true);
		//ButtonManager::SetNextSelectButton(nearButton);
		isStickMove = false;
		ButtonManager::SetSelectChange(true);
	}
	if (((Input::IsKeyDown(DIK_RIGHT) && screenID_move == 0)|| 
		Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT, screenID_move) ||
		(Input::GetPadStickL(screenID_move).x > 0 && isStickMove))/* && screenID_move == this->GetScreenID()*/)
	{
		//自分とスクリーン一緒？？
 		float selectingPosX = ButtonManager::GetSelectButtonPos(screenID_move).x;
		//float minPos = ButtonManager::GetSelectButtonPos().y;
		//移動先ボタン
		Button* nearButton = ButtonManager::GetNowButton(screenID_move);
		for (auto i : ButtonManager::GetButtonList(screenID_move))
		{
			if (i->GetPosition().y == ButtonManager::GetSelectButtonPos(screenID_move).y &&
				(i->GetPosition().x > selectingPosX &&
				(nearButton->GetPosition().x == selectingPosX ||
					(nearButton->GetPosition().x >= i->GetPosition().x &&//
						(i->GetPosition().x == nearButton->GetPosition().x &&//
							//abs(ButtonManager::GetSelectButtonPos().y - i->GetPosition().y) < abs(ButtonManager::GetSelectButtonPos().y - nearButton->GetPosition().y)) ||
							i->GetPosition().x != nearButton->GetPosition().x)))))
			{
				nearButton = i;
			}
		}
		ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
		nearButton->SetIsNextSelect(true);

		isStickMove = false;
		ButtonManager::SetSelectChange(true);
	}
	if (((Input::IsKeyDown(DIK_LEFT) && screenID_move == 0)|| 
		Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT, screenID_move) || 
		(Input::GetPadStickL(screenID_move).x < 0 && isStickMove)) /*&& screenID_move == this->GetScreenID()*/)
	{
		//選択中ボタンの位置
		float selectingPosX = ButtonManager::GetSelectButtonPos(screenID_move).x;
		//移動先ボタン
		Button* nearButton = ButtonManager::GetNowButton(screenID_move);
		for (auto* i : ButtonManager::GetButtonList(screenID_move))
		{
			if (i->GetPosition().y == ButtonManager::GetSelectButtonPos(screenID_move).y &&
				(i->GetPosition().x < selectingPosX &&
				(nearButton->GetPosition().x == selectingPosX ||
					(nearButton->GetPosition().x <= i->GetPosition().x &&
						(i->GetPosition().x == nearButton->GetPosition().x &&
							i->GetPosition().x != nearButton->GetPosition().x)))))
			{
				nearButton = i;
			}
		}
		//選択中ボタン変更（全部）
		ButtonManager::GetNowButton(screenID_move)->SetIsNextSelect(false);
		nearButton->SetIsNextSelect(true);
		isStickMove = false;
		ButtonManager::SetSelectChange(true);
	}
}

//選択された瞬間
void Button::IsSelect()
{
}

//選択解除された瞬間
void Button::IsSelectReleas()
{
}

void Button::SubUpdate()
{
}

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

void Button::SetIsFirst(Button* first)
{
	firstButton = first;
}

Button* Button::GetIsFirst()
{
	return firstButton;
}

void Button::SetAlpha(int alpha_)
{
	alpha = alpha_;
}

void Button::SetScreenID(int screenID_)
{
	screenID = screenID_;
}

int Button::GetScreenID()
{
	return screenID;
}
