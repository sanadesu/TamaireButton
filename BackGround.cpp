#include "BackGround.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"
#include"Ball.h"

//�萔
namespace
{
    static const float BACK_GROUND_SCALE = 2;
    static const float SKY_SCALE = BACK_GROUND_SCALE + 0.1f;
    static const float POS_Y = 7;
    static const float ROTATE_SPEED = 0.01f;
}

//�R���X�g���N�^
BackGround::BackGround(GameObject* parent)
    :GameObject(parent, "BackGround"), hModel_(-1),hModel_Sky(-1)
{

}

//�f�X�g���N�^
BackGround::~BackGround()
{
}

//������
void BackGround::Initialize()
{
    hModel_ = Model::Load("BackGround1.fbx");
    assert(hModel_ >= 0);
    hModel_Sky = Model::Load("BackSky.fbx");
    assert(hModel_Sky >= 0);
   
    transform_.scale_ = XMFLOAT3(BACK_GROUND_SCALE, BACK_GROUND_SCALE, BACK_GROUND_SCALE);
    transSky = transform_;
    transform_.position_.y = POS_Y;
    transSky.scale_ = XMFLOAT3(SKY_SCALE, SKY_SCALE, SKY_SCALE);
}

//�X�V
void BackGround::Update()
{
    transSky.rotate_.y += ROTATE_SPEED;
}

//�`��
void BackGround::Draw()
{
    Model::SetTransform(hModel_Sky, transSky);
    Model::Draw(hModel_Sky);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void BackGround::Release()
{
}

