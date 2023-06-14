#pragma once
#include "Engine/GameObject.h"

class StartSignal : public GameObject
{
    enum Pict
    {
        PICT_READY,
        PICT_START,
        PICT_MAX
    };

    int hSound_;//音
    int hPict_[Pict::PICT_MAX];//画像
    int startTime;//開始のカウント
    int textAlpha;//よーいどんの透明度
    float textScale;//よーいどんのサイズ
    //PlayStop* pPlayStop;
    Transform transText;//よーいどんトランスフォーム
public:
    //コンストラクタ
    StartSignal(GameObject* parent);

    //デストラクタ
    ~StartSignal();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //開始前時間取得
    int GetStartTime();

    //よーいどんを表示する
    void SetStart();
};