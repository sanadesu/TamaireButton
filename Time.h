#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
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
    //�R���X�g���N�^
    Time(GameObject* parent);

    //�f�X�g���N�^
    ~Time();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�c�莞�ԃZ�b�g
    void SetTime(float time_);

    int GetTime();

    int GetStartTime();

    void BGMStop();

    void SetStart();
};