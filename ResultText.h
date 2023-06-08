#pragma once
#include "Engine/GameObject.h"
#include "Time.h"
#include "UI.h"
#include "Engine/Text.h"
#include "Engine/Number.h"

class ResultText : public GameObject
{ 
    //使用する画像の種類
    enum Pict
    {
        PICT_WHITE_TEXT,
        PICT_RED_TEXT,
        PICT_WIN,
        PICT_LOSE,
        PICT_DRAW,
        PICT_FIRST_NUMBER,
        PICT_SECOND_NUMBER,
        PICT_MAX
    };

    enum Sound
    {
        SOUND_END,
        SOUND_DRUM,
        SOUND_RESULT,
        SOUND_MAX
    };
   
    int hPict_[Pict::PICT_MAX]; //画像番号
    int hSound_[Sound::SOUND_MAX];//音
    int whiteSum;   //白玉の得点
    int redSum;     //赤玉の得点 
    int ResultTextCount;//リザルト表示のカウント

    Number* pRedNumber;//赤得点表示
    Number* pWhiteNumber;//白得点表示
    Text* pText;//デバッグ時文字
    Time* pTime;//ゲーム残り時間
    bool isEnd;//ゲームが終わったかどうか
public:
    //コンストラクタ
    ResultText(GameObject* parent);

    //デストラクタ
    ~ResultText();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //白ボールの得点
    void WhiteCount() { whiteSum++; }

    //赤ボールの得点
    void RedCount() { redSum++; }

    //終わったか
    bool GetIsEnd();
};