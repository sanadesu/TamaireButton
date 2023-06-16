#include "Basket.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"

//定数
namespace
{
    const float HIT_HEIGHT = 5.0f;
    const float BASKET_SIZE = 1.5f;
    const float BASKET_COL_SIZE = 1.8f;
    const XMFLOAT3 BASKET_POS = XMFLOAT3(0, 5.5f, 0);
}

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
    hModel_ = Model::Load("GoalMini.fbx");
    assert(hModel_ >= 0);
    Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
    transform_.scale_ = XMFLOAT3(BASKET_SIZE, BASKET_SIZE, BASKET_SIZE);
    
    transform_.position_ = XMFLOAT3(0, 0, 0);

    //当たり判定
    SphereCollider* collision = new SphereCollider(BASKET_POS, BASKET_COL_SIZE);
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

XMFLOAT3 Basket::GetBasketPos()
{
    return BASKET_POS;
}

float Basket::GetRadius()
{
    return BASKET_COL_SIZE;
}

