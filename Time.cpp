#include "Time.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Easing.h"
#include "Engine/Audio.h"
#include "PlayStop.h"

//�傫���Ɛ�

//�萔
namespace
{
    static const int MAX_ALPHA = 255;//���S�Ɍ�����
    static const int MAX_PLAY_TIME = 7200;//�v���C����
    static const int MAX_START_TIME = 120;//�X�^�[�g����
    static const int REVERSE = 180;//�摜���]
    static const int START_TEXT_COUNT = 20;//�ǂ�̕����o���^�C�~���O
    static const int ROTATE_SIZE = MAX_PLAY_TIME / 360;//���Ԃɍ��킹�ĉ��
    static const int ALPHS_DECREASE = 10;//�����������ɂȂ鎞�̒l
    static const int CHANGE_SECONDS = 60;//�b�P�ʂɒ���
    static const float FONT_SPACE = 0.06f;//�����̊Ԋu
    static const float NUM_SIZE = 0.5f;//�����̑傫��
    static const float START_TEXT_SIZE = 0.1f;//��[���ǂ�ŏ��̑傫��
    static const float TIME_POS_Y = 0.75f;//�c�莞�ԕ\���ʒu(Y)
    static const float SOUND_VOLUME = 1.0f;//���̑傫��
    static const float SOUND_MAX_NUM = 1.0f;//�����ɖ点�鉹�̐�
    static const float TEXT_SCALE_UP = 1.5f;//�C�[�W���O�̒l�傫��
    static const float EASE_READY_TEXT_SCALE = 0.05f;//�C�[�W���O�̕ω���
    static const float EASE_START_TEXT_SCALE = 0.015f;//�ǂ�̃C�[�W���O�̕ω���
}

//�R���X�g���N�^
Time::Time(GameObject* parent)
    :GameObject(parent, "Time"), hSound_(-1),hPict_{-1,-1,-1,-1}
{
}

//�f�X�g���N�^
Time::~Time()
{
}

//������
void Time::Initialize()
{
    hSound_ = Audio::Load("Ready.wav", false, SOUND_VOLUME, SOUND_MAX_NUM);
    assert(hSound_ >= 0);

    //�g�p����t�@�C����
    const char* pictFileName[] = { "TimerFront.png", "TimerBack.png" ,"Number.png" ,"Number.png" ,"Number.png" ,"Ready.png" ,"Start.png" };

    //���[�h
    for (int i = 0; i < Pict::PICT_MAX; i++)
    {
        hPict_[i] = Image::Load(pictFileName[i]);
        assert(hPict_[i] >= 0);
    }
    hPict_[Pict::PICT_START] = -1;
    hPict_[Pict::PICT_READY] = -1;

    textAlpha = MAX_ALPHA;
    textScale = START_TEXT_SIZE;
    time = MAX_PLAY_TIME;
    startTime = MAX_START_TIME;

    transText = transform_;
    transText.scale_ = XMFLOAT3(Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale), Easing::EaseOutBack(textScale));

    if (ScreenSplit::GetPlayerPerson() < 3)
        transform_.position_.y = TIME_POS_Y;

    transTime = transform_;
    transLeft = transform_;
    transLeft.rotate_.z = REVERSE;
    pNumber = InstantiateID<Number>(this, XMFLOAT3(0,0,0), 0);
    pNumber->SetNum(MAX_PLAY_TIME / CHANGE_SECONDS, FONT_SPACE,0);
    pNumber->SetScale(XMFLOAT3(NUM_SIZE, NUM_SIZE, NUM_SIZE));
    if(ScreenSplit::GetPlayerPerson() < 3)
        pNumber->SetPosition(0, TIME_POS_Y, 0);
    else
        pNumber->SetPosition(0, 0, 0);
}

//�X�V
void Time::Update()
{
    PlayStop* pPlayStop = (PlayStop*)FindObject("PlayStop");
    if (pPlayStop->GetIsStopReady() == false)
    {
        //�X�^�[�g������
        if (startTime < 0 && pPlayStop->GetIsStopPause() == false)
        {
            pNumber->SetNum(time / CHANGE_SECONDS, FONT_SPACE,0);
            //��������
            if (time > 0)
                time--;

            if (time == MAX_PLAY_TIME / 2)
            {
                hSound_ = Audio::Load("Half.wav", false, SOUND_VOLUME, SOUND_MAX_NUM);
                assert(hSound_ >= 0);
                Audio::Play(hSound_);
            }
        }
        else//�X�^�[�g�J�E���g�_�E��
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

        transTime.rotate_.z = (float)-(MAX_PLAY_TIME - time) / ROTATE_SIZE;

#ifdef _DEBUG

        

#endif // DEBUG
        //�f�o�b�O�̂�
        if (Input::IsKeyDown(DIK_0))
        {
            time -= 1800;
        }
    }
    
}

//�`��
void Time::Draw()
{
    if (Direct3D::lr == 0)
    {
        Image::SetTransform(hPict_[Pict::PICT_BACK], transLeft);
        Image::Draw(hPict_[Pict::PICT_BACK]);

        if (time < MAX_PLAY_TIME / 2)
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

        if (time > MAX_PLAY_TIME / 2)
        {
            Image::SetTransform(hPict_[Pict::PICT_FRONT], transTime);
            Image::Draw(hPict_[Pict::PICT_FRONT]);
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

//�J��
void Time::Release()
{
}


int Time::GetTime()
{
    return time;
}

int Time::GetStartTime()
{
    return startTime;
}

void Time::SetStart()
{
    startTime = MAX_START_TIME;
}