#pragma once
#include "Engine/GameObject.h"
#include "Engine/Number.h"

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

    int hSound_;//��
    int hPict_[Pict::PICT_MAX];//�摜
    int time;//1/60�b�^�C��
    int startTime;//�J�n�̃J�E���g
    int textAlpha;//��[���ǂ�̓����x
    float textScale;//��[���ǂ�̃T�C�Y

    Number* pNumber;//�c�莞�Ԑ����\��
    Transform transTime;//�c�莞�Ԏ��v
    Transform transLeft;//�c�莞�Ԏ��v
    Transform transText;//��[���ǂ�g�����X�t�H�[��
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

    //�c�莞�Ԏ擾
    int GetTime();

    //�J�n�O���Ԏ擾
    int GetStartTime();

    //��[���ǂ��\������
    void SetStart();
};