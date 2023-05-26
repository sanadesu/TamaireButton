#include "StopBack.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Direct3D.h"
#include "PlayStop.h"

//コンストラクタ
StopBack::StopBack(GameObject* parent)
	: GameObject(parent, "StopBack"), hPict_(-1)
{
}

//初期化
void StopBack::Initialize()
{
	//ロード
	hPict_ = Image::Load("StopBack.png");
	assert(hPict_ >= 0);
}

//更新
void StopBack::Update()
{
	
}

//描画
void StopBack::Draw()
{
	PlayStop* pStop = (PlayStop*)FindObject("PlayStop");
	if (pStop->GetIsStopPause() && Direct3D::lr == 0)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//開放
void StopBack::Release()
{
}