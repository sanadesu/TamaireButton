#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//���������Ǘ�����N���X
class UI : public GameObject
{
    int hPict_;//�摜�ԍ�
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