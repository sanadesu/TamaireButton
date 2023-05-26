#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//���������Ǘ�����N���X
class UI : public GameObject
{
    //�g�p����摜�̎��
    enum
    {
        PICT_FRAME,
        PICT_WHITE_BAR,
        PICT_RED_BAR,
        PICT_MAX
    };

    //�摜�ԍ�
    int hPict_[PICT_MAX];

    int nowBar; 
    int maxBar; 

    float stopRatio;       //�ő�ɑ΂���Œ肳�ꂽ�Q�[�W�̊���
    float moveRatio;       //�ő�ɑ΂���ω����Ă�Q�[�W�̊���
    const float BAR_X = -128.0f / (GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini")/2);
    const float SPEED = 0.005f;      //�o�[�̑��x

    bool IsEnd;            //�����邩
    Text* pText;
    Transform transBarRed;
    Transform transBarWhite;
public:
    //�R���X�g���N�^
    UI(GameObject* parent);

    //�f�X�g���N�^
    ~UI();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetIsEnd(bool move_);

    void LoadSet();

    bool GetIsEnd();
};