#pragma once
#include "Engine/GameObject.h"
#include "Time.h"
#include "UI.h"
#include "Engine/Text.h"

//◆◆◆を管理するクラス
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
        //PICT_BUTTON_TITLE,
        //PICT_BUTTON_PLAY,
        //PICT_BUTTON_BACE,
        PICT_MAX
    };

    enum Sound
    {
        SOUND_END,
        SOUND_DRUM,
        SOUND_RESULT,
        SOUND_MAX
    };

    //画像番号
    int hPict_[Pict::PICT_MAX];
    int hSound_[Sound::SOUND_MAX];
    int whiteSum;   //白玉の得点
    int redSum;     //赤玉の得点 
    int ResultTextCount;//リザルト表示のカウント

    Text* pText;
    Time* pTime;
    UI* pUI;
    bool isEnd;
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

    void WhiteCount() { whiteSum++; }

    void RedCount() { redSum++; }

    bool GetIsEnd();
};