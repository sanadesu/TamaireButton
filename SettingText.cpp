#include "SettingText.h"
#include "Engine/Image.h"
#include "Engine/Easing.h"
#include "Engine/Easing.h"

//定数
namespace
{
	static const int ROU_COUNT = 2;
	static const float TOP_TEXT_HEIGHT = 500.0f;//1行目の表示範囲(縦)
	static const float BOTTOM_TEXT_Y = 500.0f;//2行目の上端の値
	static const float BOTTOM_TEXT_HEIGHT = 300.0f;//2行目の表示範囲(縦)
	static const float TEXT_WIDTH = 1920.0f;//表示範囲(横)
	static const float EASE_START_TOP = 1.0f;//1行目のイージング
	static const float EASE_START_BOTTOM = 1.2f;//2行目のイージング
	static const float EASE_VAL = 0.04f;//イージングの変化量

}

//コンストラクタ
SettingText::SettingText(GameObject* parent)
	: GameObject(parent, "SettingText"), hPict_{-1,-1}
{
}

//初期化
void SettingText::Initialize()
{
	//使用する画像ファイル名
	const char* pictFileName[] = { "Select.png", "Load.png" };

	//ロード
	for (int i = 0; i < Pict::PICT_MAX; i++)
	{
		hPict_[i] = Image::Load(pictFileName[i]);
		assert(hPict_[i] >= 0);
	}

	easeSave = 0;
	easeX = 0;
	float y[] = { 0,BOTTOM_TEXT_Y };
	float heigght[] = {TOP_TEXT_HEIGHT ,BOTTOM_TEXT_HEIGHT};
	float start[] = { EASE_START_TOP ,EASE_START_BOTTOM };
	for (int i = 0; i < ROU_COUNT; i++)
	{
		textY[i] = y[i];
		textHeight[i] = heigght[i]; 
		easeStart[i] = start[i];
	}
}

//更新
void SettingText::Update()
{
	
}

//描画
void SettingText::Draw()
{
	for (int i = 0; i < ROU_COUNT; i++)
	{
		transform_.position_ = Image::SetRectPos(hPict_[Pict::PICT_SELECT], 0, textY[i], TEXT_WIDTH, textHeight[i]);

		easeSave = easeStart[i] - easeX;
		if (easeSave < 0)
			easeSave = 0;
		else if (easeSave > 1)
			easeSave = 1;

		transform_.position_.x -= Easing::EaseInQuart(easeSave) * 2;

		Image::SetTransform(hPict_[Pict::PICT_SELECT], transform_);
		Image::Draw(hPict_[Pict::PICT_SELECT]);
	}

	easeX += EASE_VAL;
}

//開放
void SettingText::Release()
{
}
