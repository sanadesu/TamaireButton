#include "BackGround.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"
#include"Ball.h"

//コンストラクタ
BackGround::BackGround(GameObject* parent)
    :GameObject(parent, "BackGround"), hModel_(-1),hModel_Sky(-1)
{

}

//デストラクタ
BackGround::~BackGround()
{
}

//初期化
void BackGround::Initialize()
{
    hModel_ = Model::Load("BackGround1.fbx");
    assert(hModel_ >= 0);
    hModel_Sky = Model::Load("BackSky.fbx");
    assert(hModel_Sky >= 0);
   
    transform_.scale_ = XMFLOAT3(2, 2, 2);
    transSky = transform_;
    transform_.position_.y = 7;
    transSky.scale_ = XMFLOAT3(2.1f,2.1f,2.1f);
    //transform_.scale_ = XMFLOAT3(35.1f, 35.1f, 35.1f);
}

//更新
void BackGround::Update()
{
    transSky.rotate_.y += 0.01f;
}

//描画
void BackGround::Draw()
{
    //Direct3D::SetShader(Direct3D::SHADER_NORMAL);//
    Model::SetTransform(hModel_Sky, transSky);
    Model::Draw(hModel_Sky);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
  
    //Direct3D::SetShader(Direct3D::SHADER_TOON);

}

//開放
void BackGround::Release()
{
}

