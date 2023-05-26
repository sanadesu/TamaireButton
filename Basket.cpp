#include "Basket.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"

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
    hModel_ = Model::Load("GoalB.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
    
    transform_.position_ = XMFLOAT3(0, 0, 0);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(BASKET_POS, HIT_SIZE);
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

