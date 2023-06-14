#pragma once
#include "Engine/GameObject.h"
#include "Engine/Number.h"
#include "StartSignal.h"
#include "PlayStop.h"

class Time : public GameObject
{
    enum Pict
    {
        PICT_FRONT,
        PICT_BACK,
        PICT_READY,
        PICT_START,
        PICT_MAX
    };

    int hSound_;//音
    int hPict_[Pict::PICT_MAX];//画像
    int time;//1/60秒タイム

    bool isFirst;//1フレーム目にやりたい処理

    StartSignal* pStartSignal;
    PlayStop* pPlayStop;
    Number* pNumber;//残り時間数字表示
    Transform transTime;//残り時間時計
    Transform transLeft;//残り時間時計
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

    //残り時間取得
    int GetTime();

};