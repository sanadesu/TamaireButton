#pragma once
#include "Engine/GameObject.h"
#include "Time.h"
#include "UI.h"
#include "Engine/Text.h"

//���������Ǘ�����N���X
class ResultText : public GameObject
{ 
    //�g�p����摜�̎��
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

    //�摜�ԍ�
    int hPict_[Pict::PICT_MAX];
    int hSound_[Sound::SOUND_MAX];
    int whiteSum;   //���ʂ̓��_
    int redSum;     //�ԋʂ̓��_ 
    int ResultTextCount;//���U���g�\���̃J�E���g

    Text* pText;
    Time* pTime;
    UI* pUI;
    bool isEnd;
public:
    //�R���X�g���N�^
    ResultText(GameObject* parent);

    //�f�X�g���N�^
    ~ResultText();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void WhiteCount() { whiteSum++; }

    void RedCount() { redSum++; }

    bool GetIsEnd();
};