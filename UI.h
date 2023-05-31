#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//���������Ǘ�����N���X
class UI : public GameObject
{
    static const int PLAYER_MAX = 4;
    const int TEXT_SIZE = 30;
    const int OPERATION_X = 1630;
    const int OPERATION_Y = 450;
    const int STATE_X = 1730;
    const int STATE_Y = 120;
    const int OPERATION_MAX = 7;
    //�摜�ԍ�
    int hPict_;
    bool IsEnd;       //�I�����Ă邩
    Text* pText;
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

    //���[�h��ʂɐ؂�ւ�
    void LoadSet();

    //�I�����Ă邩�擾
    bool GetIsEnd();
};