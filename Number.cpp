#include "Number.h"
#include "Engine/Image.h"
#include "Engine/Model.h"
#include "Engine/Easing.h"

//�R���X�g���N�^
Number::Number(GameObject* parent,int ID)
    : GameObject(parent, "Number"), hPict_{ -1, -1, -1 }
{
	numID = ID;
}

//������
void Number::Initialize()
{
	num = 0;
    dividedTime = 0;
    saveTime = 0;
    for (int i = 0; i < 3; i++)
    {
        hPict_[i] = Image::Load("Number.png");
        assert(hPict_[i] >= 0);
    }
}

//�X�V
void Number::Update()
{
	
}

//�`��
void Number::Draw()
{
    for (int i = 0; i < 3; i++)
    {
        if (hPict_[i] != -1)
        {
            //Image::SetRect(hPict_[i], int(saveTime / dividedTime) * 150, 0, 150, 256);
            Image::SetTransform(hPict_[i], transform_);
            Image::Draw(hPict_[i]);
        }
    }
}
	

//�J��
void Number::Release()
{
}

void Number::SetNum(int num_, float space_)
{
	num = num_ * 60;
    dividedTime = 0;
    int repeat = 0;
    if (num >= 6000)
    {
        //3��
        dividedTime = 6000;
        repeat = 3;
    }
    else if (num < 6000 && num >= 600)
    {
        //2��
        dividedTime = 600;
        repeat = 2;
    }
    else
    {
        //1��
        dividedTime = 60;
        repeat = 1;
    }
    //int dividedTime = 6000;
    saveTime = num;
    //Transform numTrans = transform_;

    //numTrans.scale_ = XMFLOAT3(fontScale, fontScale, fontScale);
    transform_.position_.x -= space_;
    for (int i = 0; i <= 3; i++)
    {
        if (i < repeat)
        {
            Image::SetRect(hPict_[i], int(saveTime / dividedTime) * 150, 0, 150, 256);
            //Image::SetTransform(hPict_[i], transform_);
            //Image::Draw(hPict_[i]);
            saveTime = saveTime % dividedTime;
            dividedTime /= 10;
            transform_.position_.x += space_;
        }
        else
        {
            hPict_[i] = -1;
        }
    }
}
