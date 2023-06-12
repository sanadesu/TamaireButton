#include "Frame.h"
#include "Image.h"
#include "Easing.h"

//コンストラクタ
Frame::Frame(GameObject* parent)
	: GameObject(parent, "Frame")
{
	
}

//初期化
void Frame::Initialize()
{
	frame = 0;
}

//更新
void Frame::Update()
{
	frame++;
}

//描画
void Frame::Draw()
{


}

//開放
void Frame::Release()
{
}

int Frame::GetFrame()
{
	return frame;
}
