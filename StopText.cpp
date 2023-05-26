#include "StopText.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "PlayStop.h"

//コンストラクタ
StopText::StopText(GameObject* parent)
	: GameObject(parent, "StopText"), hPict_(-1)
{
}

//初期化
void StopText::Initialize()
{
	//ロード
	hPict_ = Image::Load("StopText.png");
	assert(hPict_ >= 0);
}

//更新
void StopText::Update()
{

}

//描画
void StopText::Draw()
{
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	if (pStop->GetIsStopPause() && Direct3D::lr == 0)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//開放
void StopText::Release()
{
}