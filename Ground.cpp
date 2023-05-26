#include "Ground.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"

//コンストラクタ
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground"), hModel_(-1)
{

}

//デストラクタ
Ground::~Ground()
{
}

//初期化
void Ground::Initialize()
{
    hModel_ = Model::Load("Field.fbx");
    assert(hModel_ >= 0);

    groundBall = 60;//csv
    transform_.position_ = XMFLOAT3(0, GROUND_HEIGHT, 0);
    
}

//更新
void Ground::Update()
{
    int a = groundBall;
}

//描画
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void Ground::Release()
{
}


void Ground::SetGroundBall(int groundBall_)
{
    groundBall = groundBall + groundBall_;
}

int Ground::GetGroundBall()
{
    return groundBall;
}

