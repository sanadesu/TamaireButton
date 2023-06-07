#include "Rule.h"
#include "Engine/Image.h"

//コンストラクタ
Rule::Rule(GameObject* parent)
	: GameObject(parent, "Rule"), hPict_(-1)
{
}

//初期化
void Rule::Initialize()
{
	
}

//更新
void Rule::Update()
{
	
}

//描画
void Rule::Draw()
{
	//中身があれば描画する
	if (hPict_ != -1)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//開放
void Rule::Release()
{
}

//画像セット
void Rule::SetRuleImage(const std::string& path)
{
	//画像を表示するかどうか
	if (path != "NO")
	{
		//画像データのロード
		hPict_ = Image::Load(path);

		//ロードされたか確認
		assert(hPict_ >= 0);
	}
	else
	{
		hPict_ = -1;
	}
}
