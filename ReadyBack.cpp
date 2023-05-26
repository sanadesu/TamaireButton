#include "ReadyBack.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "PlayStop.h"

//コンストラクタ
ReadyBack::ReadyBack(GameObject* parent)
	: GameObject(parent, "ReadyBack"), hPict_(-1)
{
}

//初期化
void ReadyBack::Initialize()
{
	//ロード
	hPict_ = Image::Load("StopBack.png");
	assert(hPict_ >= 0);

}

//更新
void ReadyBack::Update()
{

}

//描画
void ReadyBack::Draw()
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
void ReadyBack::Release()
{
}

void ReadyBack::BlackBack()
{
	hPict_ = Image::Load("BlackBack.png");
	assert(hPict_ >= 0);
}
