#include "StartSignal.h"
#include "Time.h"
#include "PlayStop.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Easing.h"
#include "Engine/Audio.h"

//大きさと線

//定数
namespace
{
    static const int MAX_ALPHA = 255;//完全に見える
    static const int MAX_PLAY_TIME = 7200;//プレイ時間
    static const int MAX_START_TIME = 120;//スタート時間
    static const int REVERSE = 180;//画像反転
    static const int START_TEXT_COUNT = 20;//どんの文字出すタイミング
    static const int ROTATE_SIZE = MAX_PLAY_TIME / 360;//時間に合わせて回る
    static const int ALPHS_DECREASE = 10;//少しずつ透明になる時の値
    static const int CHANGE_SECONDS = 60;//秒単位に直す
    static const float FONT_SPACE = 0.06f;//数字の間隔
    static const float NUM_SIZE = 0.5f;//数字の大きさ
    static const float START_TEXT_SIZE = 0.1f;//よーいどん最初の大きさ
    static const float TIME_POS_Y = 0.75f;//残り時間表示位置(Y)
    static const float SOUND_VOLUME = 1.0f;//音の大きさ
    static const float SOUND_MAX_NUM = 1.0f;//同時に鳴らせる音の数
    static const float TEXT_SCALE_UP = 1.5f;//イージングの値大きく
    static const float EASE_READY_TEXT_SCALE = 0.05f;//イージングの変化量
    static const float EASE_START_TEXT_SCALE = 0.015f;//どんのイージングの変化量
}

//コンストラクタ
StartSignal::StartSignal(GameObject* parent)
    :GameObject(parent, "StartSignal"), hSound_(-1), hPict_{ -1,-1 }
{
}

//デストラクタ
StartSignal::~StartSignal()
{
}

//初期化
void StartSignal::Initialize()
{
    hSound_ = Audio::Load("Ready.wav", false, SOUND_VOLUME, SOUND_MAX_NUM);
    assert(hSound_ >= 0);

    //使用するファイル名
    const char* pictFileName[] = { "Ready.png" ,"Start.png" };

    //ロード
    for (int i = 0; i < Pict::PICT_MAX; i++)
    {
        hPict_[i] = Image::Load(pictFileName[i]);
        assert(hPict_[i] >= 0);
    }
    hPict_[Pict::PICT_START] = -1;
    hPict_[Pict::PICT_READY] = -1;

    textAlpha = MAX_ALPHA;
    textScale = START_TEXT_SIZE;
    startTime = MAX_START_TIME;

    transText = transform_;
    transText.scale_ = XMFLOAT3(Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale));

    if (ScreenSplit::GetPlayerPerson() < 3)
        transform_.position_.y = TIME_POS_Y;

  
}

//更新
void StartSignal::Update()
{
    PlayStop* pPlayStop = (PlayStop*)FindObject("PlayStop");
    if (pPlayStop->GetIsStopReady() == false)
    {
        if (startTime == MAX_START_TIME)
        {
            hPict_[Pict::PICT_READY] = Image::Load("Ready.png");

            hSound_ = Audio::Load("Ready.wav", false, SOUND_VOLUME, SOUND_MAX_NUM);
            assert(hSound_ >= 0);
            Audio::Play(hSound_);
        }
        else if (startTime > START_TEXT_COUNT)
        {
            transText.scale_ = XMFLOAT3(Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale));
            if (textScale < 1)
                textScale += EASE_START_TEXT_SCALE;
            else
                textAlpha -= ALPHS_DECREASE;
        }
        else if (startTime == START_TEXT_COUNT)
        {
            hPict_[Pict::PICT_READY] = -1;
            hPict_[Pict::PICT_START] = Image::Load("Start.png");
            textScale = 0;
            transText.scale_ = XMFLOAT3(Easing::EaseOutCirc(textScale * TEXT_SCALE_UP), Easing::EaseOutCirc(textScale * TEXT_SCALE_UP), Easing::EaseOutCirc(textScale * TEXT_SCALE_UP));

            hSound_ = Audio::Load("Go.wav", false, SOUND_VOLUME, SOUND_MAX_NUM);
            assert(hSound_ >= 0);
            Audio::Play(hSound_);

            hSound_ = Audio::Load("PlayBGM.wav", true, SOUND_VOLUME, SOUND_MAX_NUM);
            assert(hSound_ >= 0);
            Audio::Play(hSound_);
        }
        else if (startTime > 0)
        {
            textScale += EASE_READY_TEXT_SCALE;
            transText.scale_ = XMFLOAT3(Easing::EaseOutCirc(textScale * TEXT_SCALE_UP), Easing::EaseOutCirc(textScale * TEXT_SCALE_UP), Easing::EaseOutCirc(textScale * TEXT_SCALE_UP));
        }
        else if (startTime <= 0)
        {
            hPict_[Pict::PICT_START] = -1;
        }
        startTime--;
    }
}

//描画
void StartSignal::Draw()
{
    if (Direct3D::lr == 0)
    {
        for (int i = Pict::PICT_READY; i < Pict::PICT_MAX; i++)
        {
            if (hPict_[i] >= 0)
            {
                Image::SetAlpha(hPict_[Pict::PICT_READY], textAlpha);
                Image::SetTransform(hPict_[i], transText);
                Image::Draw(hPict_[i]);
            }
        }
    }
}

//開放
void StartSignal::Release()
{
}

int StartSignal::GetStartTime()
{
    return startTime;
}

void StartSignal::SetStart()
{
    startTime = MAX_START_TIME;
}