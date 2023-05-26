#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Time : public GameObject
{
    enum Pict
    {
        PICT_FRONT,
        PICT_BACK,
        PICT_PLACE_ONE,
        PICT_PLACE_TEN,
        PICT_PLACE_HUNDRED,
        PICT_READY,
        PICT_START,
        PICT_MAX
    };
    const float FONT_SPACE = 0.06f;

    float ease = 0.9f;
    int hSound_;
    int hPict_[Pict::PICT_MAX];

    int textAlpha;
    float textScale;
    float fontScale;
    int time;
    int startTime;

    Transform transTime;
    Transform transLeft;
    Transform transText;
public:
    //コンストラクタ
    Time(GameObject* parent);

    //デストラクタ
    ~Time();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //残り時間セット
    void SetTime(float time_);

    int GetTime();

    int GetStartTime();

    void BGMStop();

    void SetStart();
};