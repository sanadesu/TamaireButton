#include "Ground.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"

//�R���X�g���N�^
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground"), hModel_(-1)
{

}

//�f�X�g���N�^
Ground::~Ground()
{
}

//������
void Ground::Initialize()
{
    hModel_ = Model::Load("Field.fbx");
    assert(hModel_ >= 0);

    groundBall = 60;//csv
    transform_.position_ = XMFLOAT3(0, GROUND_HEIGHT, 0);
    
}

//�X�V
void Ground::Update()
{
    int a = groundBall;
}

//�`��
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
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

