#include "TitleBall.h"
#include "Engine/Image.h"
#include "Engine/Model.h"
#include "Engine/Easing.h"

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
	transform_.position_.x = (float)(rand() % RANGE_X - (RANGE_X / 2)) / 10.0f;
	transform_.position_.z = (float)(rand() % RANGE_Z) / 10.0f + 30;//前に出す
	transform_.position_.y = 9;

	transform_.scale_ = XMFLOAT3(SIZE, SIZE, SIZE);
	easeY = 0.1f;
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
