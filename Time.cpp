#include "Time.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Easing.h"
#include "Engine/Audio.h"
#include "PlayStop.h"

//コンストラクタ
Time::Time(GameObject* parent)
    :GameObject(parent, "Time"), hSound_(-1),hPict_{-1,-1,-1,-1,-1,-1,-1}
{
}

//デストラクタ
Time::~Time()
{
}

//初期化
void Time::Initialize()
{
    hSound_ = Audio::Load("Ready.wav", false, 1, 1);
    assert(hSound_ >= 0);

    //使用するファイル名
    const char* pictFileName[] = { "TimerFront.png", "TimerBack.png" ,"Number.png" ,"Number.png" ,"Number.png" ,"Ready.png" ,"Start.png" };

    //ロード
    for (int i = 0; i < Pict::PICT_MAX; i++)
    {
        hPict_[i] = Image::Load(pictFileName[i]);
        assert(hPict_[i] >= 0);
    }
    hPict_[Pict::PICT_START] = -1;
    hPict_[Pict::PICT_READY] = -1;

    textAlpha = 255;
    textScale = 0.1f;
    fontScale = 0.5f;
    time = 7200;
    startTime = 120;

    transText = transform_;
    transText.scale_ = XMFLOAT3(Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale));

    if (ScreenSplit::GetPlayerPerson() < 3)
        transform_.position_.y += 0.75f;
    if(ScreenSplit::GetPlayerPerson() == 1)
        transform_.position_.x -= 0.85f;

    transTime = transform_;
    transLeft = transform_;
    transLeft.rotate_.z = 180;
}

//更新
void Time::Update()
{
    PlayStop* pPlayStop = (PlayStop*)FindObject("PlayStop");
    if (pPlayStop->GetIsStopReady() == false)
    {
        //transform_.position_.x -= 0.0000736f;
        //スタートしたら
        if (startTime < 0 && pPlayStop->GetIsStopPause() == false)
        {
            //制限時間
            if (time > 0)
                time--;

            if (time == 3600)
            {
                hSound_ = Audio::Load("Half.wav", false, 1, 1);
                assert(hSound_ >= 0);
                Audio::Play(hSound_);
            }
        }
        else//スタートカウントダウン
        {
            if (startTime == 120)
            {
                hPict_[Pict::PICT_READY] = Image::Load("Ready.png");

                hSound_ = Audio::Load("Ready.wav", false, 1, 1);
                assert(hSound_ >= 0);
                Audio::Play(hSound_);
            }
            else if (startTime > 20)
            {
                transText.scale_ = XMFLOAT3(Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale));
                if (textScale < 1)
                    textScale += 0.015f;
                else
                    textAlpha -= 10;
                
            }
            else if (startTime == 20)
            {
                hPict_[Pict::PICT_READY] = -1;
                hPict_[Pict::PICT_START] = Image::Load("Start.png");
                textScale = 0;
                transText.scale_ = XMFLOAT3(Easing::EaseOutCirc(textScale * 1.5f), Easing::EaseOutCirc(textScale * 1.5f), Easing::EaseOutCirc(textScale * 1.5f));

                hSound_ = Audio::Load("Go.wav", false, 1, 1);
                assert(hSound_ >= 0);
                Audio::Play(hSound_);

                hSound_ = Audio::Load("PlayBGM.wav", true, 0.8f, 1);
                assert(hSound_ >= 0);
                Audio::Play(hSound_);
            }
            else if (startTime > 0)
            {
                textScale += 0.05f;
                transText.scale_ = XMFLOAT3(Easing::EaseOutCirc(textScale * 1.5f), Easing::EaseOutCirc(textScale * 1.5f), Easing::EaseOutCirc(textScale * 1.5f));
            }
            else if (startTime <= 0)
            {
                hPict_[Pict::PICT_START] = -1;
            }
            startTime--;
        }

        transTime.rotate_.z = (float)-(7200 - time) / 20;

#ifdef _DEBUG

        //デバッグのみ
        if (Input::IsKeyDown(DIK_0))
        {
            time -= 1800;
        }

#endif // DEBUG
    }
    
}

//描画
void Time::Draw()
{
    if (Direct3D::lr == 0)
    {
        //transTime.rotate_.z -= 0.05;

        Image::SetTransform(hPict_[Pict::PICT_BACK], transLeft);
        Image::Draw(hPict_[Pict::PICT_BACK]);

        if (time < 3600)
        {
            Image::SetTransform(hPict_[Pict::PICT_FRONT], transTime);
            Image::Draw(hPict_[Pict::PICT_FRONT]);
        }
        else
        {
            Image::SetTransform(hPict_[Pict::PICT_FRONT], transLeft);
            Image::Draw(hPict_[Pict::PICT_FRONT]);
        }

        Image::SetTransform(hPict_[Pict::PICT_BACK], transform_);
        Image::Draw(hPict_[Pict::PICT_BACK]);

        if (time > 3600)
        {
            Image::SetTransform(hPict_[Pict::PICT_FRONT], transTime);
            Image::Draw(hPict_[Pict::PICT_FRONT]);
        }


        //文字表示
        int dividedTime = 6000;
        int saveTime = time;
        Transform numTrans = transform_;

        numTrans.scale_ = XMFLOAT3(fontScale, fontScale, fontScale);
        numTrans.position_.x -= FONT_SPACE;
        for (int i = Pict::PICT_PLACE_ONE; i <= Pict::PICT_PLACE_HUNDRED; i++)
        {
            Image::SetRect(hPict_[i], int(saveTime / dividedTime) * 150, 0, 150, 256);
            Image::SetTransform(hPict_[i], numTrans);
            Image::Draw(hPict_[i]);
            saveTime = saveTime % dividedTime;
            dividedTime /= 10;
            numTrans.position_.x += FONT_SPACE;
        }

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
void Time::Release()
{
}

void Time::SetTime(float time_)
{
    //transform_.position_.x = (time_ * 0.000075) - 1.273f;
  
}

int Time::GetTime()
{
    return time;
}

int Time::GetStartTime()
{
    return startTime;
}

void Time::BGMStop()
{
    Audio::Stop(hSound_);
}

void Time::SetStart()
{
    startTime = 120;
}
