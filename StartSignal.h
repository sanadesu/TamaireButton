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

    int hSound_;//��
    int hPict_[Pict::PICT_MAX];//�摜
    int startTime;//�J�n�̃J�E���g
    int textAlpha;//��[���ǂ�̓����x
    float textScale;//��[���ǂ�̃T�C�Y
    //PlayStop* pPlayStop;
    Transform transText;//��[���ǂ�g�����X�t�H�[��
public:
    //�R���X�g���N�^
    StartSignal(GameObject* parent);

    //�f�X�g���N�^
    ~StartSignal();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�J�n�O���Ԏ擾
    int GetStartTime();

    //��[���ǂ��\������
    void SetStart();
};