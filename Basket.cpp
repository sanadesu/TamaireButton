#include "Basket.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
Basket::Basket(GameObject* parent)
    :GameObject(parent, "Basket"),hModel_(-1)
{

}

//デストラクタ
Basket::~Basket()
{

}

//初期化
void Basket::Initialize()
{
    hModel_ = Model::Load("GoalB.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
    
    transform_.position_ = XMFLOAT3(0, 0, 0);

    //当たり判定
    SphereCollider* collision = new SphereCollider(BASKET_POS, HIT_SIZE);
    AddCollider(collision);

}

//更新
void Basket::Update()
{
}

//描画
void Basket::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Basket::Release()
{
}

//何かに当たった
void Basket::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
}

