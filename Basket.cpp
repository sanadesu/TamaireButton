#include "Basket.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"

//�萔
namespace
{
    const float HIT_HEIGHT = 5.0f;
    const float BASKET_SIZE = 1.0f;
    const XMFLOAT3 BASKET_POS = XMFLOAT3(0, 5.0f, 0);
}

//�R���X�g���N�^
Basket::Basket(GameObject* parent)
    :GameObject(parent, "Basket"),hModel_(-1)
{

}

//�f�X�g���N�^
Basket::~Basket()
{

}

//������
void Basket::Initialize()
{
    hModel_ = Model::Load("Goal.fbx");
    assert(hModel_ >= 0);
    Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
    transform_.scale_ = XMFLOAT3(BASKET_SIZE, BASKET_SIZE, BASKET_SIZE);
    
    transform_.position_ = XMFLOAT3(0, 0, 0);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(BASKET_POS, BASKET_SIZE);
    AddCollider(collision);

}

//�X�V
void Basket::Update()
{
}

//�`��
void Basket::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Basket::Release()
{
}

//�����ɓ�������
void Basket::OnCollision(GameObject* pTarget)
{
    //���������Ƃ��̏���
}

XMFLOAT3 Basket::GetBasketPos()
{
    return BASKET_POS;
}

