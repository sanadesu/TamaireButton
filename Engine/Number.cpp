#include "Number.h"
#include "Image.h"
#include "Model.h"
#include "Easing.h"

//定数
namespace
{
    static const int MAX_DIGITS = 3;//最大桁数
    static const int CHANGE_DIGITS = 60;//桁を変える
    static const int NUM_INTERVAL = 150;//数字の画像の間隔
    static const int WIDTH = 150;//数字1つの横幅
    static const int HEIGHT = 256;//数字1つの縦幅
}

//コンストラクタ
Number::Number(GameObject* parent,int ID)
    : GameObject(parent, "Number"), hPict_{ -1, -1, -1 }
{

}

//初期化
void Number::Initialize()
{
	num = 0;
    dividedTime = 0;
    saveTime = 0;
    space = 0;
    for (int i = 0; i < MAX_DIGITS; i++)
    {
        hPict_[i] = Image::Load("Number.png");
        assert(hPict_[i] >= 0);
    }
}

//更新
void Number::Update()
{
	
}

//描画
void Number::Draw()
{
    if (Direct3D::lr == 0)
    {
        transform_.position_.x -= space;
        for (int i = 0; i < MAX_DIGITS; i++)
        {
            if (hPict_[i] != -1)
            {
                Image::SetTransform(hPict_[i], transform_);
                Image::Draw(hPict_[i]);
            }
            transform_.position_.x += space;
        }
        transform_.position_.x -= space * 2;
    }
}
	

//開放
void Number::Release()
{
}

void Number::SetNum(int num_, float space_, float posX_)
{
    space = space_;
	num = num_ * CHANGE_DIGITS;
    dividedTime = 0;
    int repeat = 0;
    if (num >= CHANGE_DIGITS * 100)
    {
        //3桁
        dividedTime = CHANGE_DIGITS * 100;
        repeat = 3;
    }
    else if (num < CHANGE_DIGITS * 100 && num >= CHANGE_DIGITS * 10)
    {
        //2桁
        dividedTime = CHANGE_DIGITS * 10;
        repeat = 2;
        transform_.position_.x = posX_ + space_ / 2;
    }
    else
    {
        //1桁
        dividedTime = CHANGE_DIGITS;
        repeat = 1;
        transform_.position_.x = posX_ + space_;
    }

    saveTime = num;
    for (int i = 0; i <= MAX_DIGITS; i++)
    {
        if (i < repeat)
        {
            Image::SetRect(hPict_[i], int(saveTime / dividedTime) * NUM_INTERVAL, 0, WIDTH, HEIGHT);
            saveTime = saveTime % dividedTime;
            dividedTime /= 10;
        }
        else
        {
            hPict_[i] = -1;
        }
    }
}
