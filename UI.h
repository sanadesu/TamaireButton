#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//◆◆◆を管理するクラス
class UI : public GameObject
{
    //使用する画像の種類
    enum
    {
        PICT_FRAME,
        PICT_WHITE_BAR,
        PICT_RED_BAR,
        PICT_MAX
    };

    //画像番号
    int hPict_[PICT_MAX];

    int nowBar; 
    int maxBar; 

    float stopRatio;       //最大に対する固定されたゲージの割合
    float moveRatio;       //最大に対する変化してるゲージの割合
    const float BAR_X = -128.0f / (GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini")/2);
    const float SPEED = 0.005f;      //バーの速度

    bool IsEnd;            //動けるか
    Text* pText;
    Transform transBarRed;
    Transform transBarWhite;
public:
    //コンストラクタ
    UI(GameObject* parent);

    //デストラクタ
    ~UI();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetIsEnd(bool move_);

    void LoadSet();

    bool GetIsEnd();
};