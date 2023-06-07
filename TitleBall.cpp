#include "TitleBall.h"
#include "Engine/Image.h"
#include "Engine/Model.h"
#include "Engine/Easing.h"

//定数
namespace
{
	static const int DOWN_LIMIT = -40;//ボールを消す高さ
	static const int RANGE_X = 600;//ボールを落とす範囲(横)
	static const int RANGE_Z = 100;//ボールを落とす範囲(奥)
	static const int BALL_FRONT = 30;//ボールを前に出す
	static const int START_DOWN = 9;//ボールのスタート位置
	static const int BALL_SIZE = 4;//ボールの大きさ
	static const float DOWN_SPEAD = 0.005f;//ボールが落ちる速さ
	static const float DECIMAL_CHANGE = 10.0f;//ボールが落ちる速さ
	static const float EASE_START = 0.01f;//ボールが落ちる速さ
}

//コンストラクタ
TitleBall::TitleBall(GameObject* parent)
	: GameObject(parent, "TitleBall"),hModel_(-1)
{
}

//初期化
void TitleBall::Initialize()
{
	//赤白ボールランダムで降らす
	if (rand() % 2 == 0)
		hModel_ = Model::Load("RedBall.fbx");
	else
		hModel_ = Model::Load("WhiteBall.fbx");
	assert(hModel_ >= 0);

	//場所もランダム
	transform_.position_.x = (float)(rand() % RANGE_X - (RANGE_X / 2)) / DECIMAL_CHANGE;
	transform_.position_.z = (float)(rand() % RANGE_Z) / DECIMAL_CHANGE + BALL_FRONT;//前に出す
	transform_.position_.y = START_DOWN;

	//サイズ変更
	transform_.scale_ = XMFLOAT3(BALL_SIZE, BALL_SIZE, BALL_SIZE);
	easeY = EASE_START;
}

//更新
void TitleBall::Update()
{
	//ボールの落ちるスピード
	easeY += DOWN_SPEAD;
	if (easeY > 1)
		easeY = 1;
	transform_.position_.y -= Easing::EaseInQuad(easeY);

	//下に行ったら消す
	if (transform_.position_.y < DOWN_LIMIT)
		KillMe();
}

//描画
void TitleBall::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void TitleBall::Release()
{
}
