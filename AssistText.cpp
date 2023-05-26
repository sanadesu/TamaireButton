#include "AssistText.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "PlayStop.h"
#include "ReadyButton.h"

//コンストラクタ
AssistText::AssistText(GameObject* parent)
	: GameObject(parent, "AssistText"), hPict_(-1)
{
}

//初期化
void AssistText::Initialize()
{
	//ロード
	hPict_ = Image::Load("AssistText.png");
	assert(hPict_ >= 0);
	playerNum = 0;
	for (int i = 0; i < 4; i++)
	{
		isReady[i] = false;
	}
	text = 0;
	if (ScreenSplit::GetPlayerPerson() == 2)
	{
		transform_.scale_.y *= 0.5f;
		posY = 500;
	}
	else
		posY = 465;
}

//更新
void AssistText::Update()
{

}

//描画
void AssistText::Draw()
{
	if (playerNum == Direct3D::lr)
	{
		PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
		if (pStop->GetIsStopReady())
		{
			Image::SetRect(hPict_, text, 0, 256, 128);
			transform_.position_ = Image::PixelPos(hPict_, 1250, posY);
			
			Image::SetTransform(hPict_, transform_);
			Image::Draw(hPict_);
		}
	}


	//for (int i = 0; i < ScreenSplit::GetPlayerPerson(); i++)
	//{
	//	if (ScreenSplit::GetPlayerPerson() >= 3 && isReady[i] == false && Direct3D::lr == i + 3)
	//	{
	//		PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	//		if (pStop->GetIsStopReady() && Direct3D::lr == i + 3)
	//		{
	//			float x, y, width, height;

	//			float screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//スクリーンの幅
	//			float screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//スクリーンの高さ

	//			x = 1130;
	//			y = 400;
	//			width = 256;
	//			height = 128;

	//			Image::SetRect(hPict_, 0, 0, 256, 128);
	//			transform_.position_ = XMFLOAT3(((float)width / screenWidth + x / (screenWidth / 2)) - 1, 1 - ((float)height / screenHeight + y / (screenHeight / 2)), 0);

	//			Image::SetTransform(hPict_, transform_);
	//			Image::Draw(hPict_);
	//		}
	//	}
	//	else if (ScreenSplit::GetPlayerPerson() == 2 && isReady[i] == false && Direct3D::lr == i + 1)
	//	{

	//	}
	//	else if (ScreenSplit::GetPlayerPerson() == 1 && isReady[i] == false && Direct3D::lr == i)
	//	{

	//	}
	//}
	
	
}

//開放
void AssistText::Release()
{
}

