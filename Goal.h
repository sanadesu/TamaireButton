#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Goal : public GameObject
{
    int hModel_[1];    //���f���ԍ�

public:
    //�R���X�g���N�^
    Goal(GameObject* parent);

    //�f�X�g���N�^
    ~Goal();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;



};