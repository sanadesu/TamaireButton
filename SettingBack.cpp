#include "SettingBack.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"

//コンストラクタ
SettingBack::SettingBack(GameObject* parent)
	: GameObject(parent, "SettingBack"), hPict_(-1)
{
}

//初期化
void SettingBack::Initialize()
{
	//ロード
	hPict_ = Image::Load("SelectBack.png");
	assert(hPict_ >= 0);
}

//更新
void SettingBack::Update()
{

}

//描画
void SettingBack::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void SettingBack::Release()
{
}
