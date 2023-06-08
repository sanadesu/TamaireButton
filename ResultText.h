#pragma once
#include "Engine/GameObject.h"
#include "Time.h"
#include "UI.h"
#include "Engine/Text.h"
#include "Engine/Number.h"

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
        PICT_MAX
    };

    enum Sound
    {
        SOUND_END,
        SOUND_DRUM,
        SOUND_RESULT,
        SOUND_MAX
    };
   
    int hPict_[Pict::PICT_MAX]; //�摜�ԍ�
    int hSound_[Sound::SOUND_MAX];//��
    int whiteSum;   //���ʂ̓��_
    int redSum;     //�ԋʂ̓��_ 
    int ResultTextCount;//���U���g�\���̃J�E���g

    Number* pRedNumber;//�ԓ��_�\��
    Number* pWhiteNumber;//�����_�\��
    Text* pText;//�f�o�b�O������
    Time* pTime;//�Q�[���c�莞��
    bool isEnd;//�Q�[�����I��������ǂ���
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

    //���{�[���̓��_
    void WhiteCount() { whiteSum++; }

    //�ԃ{�[���̓��_
    void RedCount() { redSum++; }

    //�I�������
    bool GetIsEnd();
};