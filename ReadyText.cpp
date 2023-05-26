#include "ReadyText.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "PlayStop.h"

//コンストラクタ
ReadyText::ReadyText(GameObject* parent)
	: GameObject(parent, "ReadyText"), hPict_(-1)
{
}

//初期化
void ReadyText::Initialize()
{
	//ロード
	hPict_ = Image::Load("ReadyText.png");
	assert(hPict_ >= 0);
	if (ScreenSplit::GetPlayerPerson() == 2)
	{
		transform_.scale_.y *= 0.5f;
		//transform_.position_.y += 0.05f;
	}
}

//更新
void ReadyText::Update()
{

}

//描画
void ReadyText::Draw()
{
	if (playerNum == Direct3D::lr)
	{
		PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
		if (pStop->GetIsStopReady())
		{
			Image::SetTransform(hPict_, transform_);
			Image::Draw(hPict_);
		}
	}
}

//開放
void ReadyText::Release()
{
}