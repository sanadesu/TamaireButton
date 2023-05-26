#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"

//���������Ǘ�����N���X
class Field : public GameObject
{
    int hModel_[2];    //���f���ԍ�
    struct
    {
        int type;
        int height;

    }table[15][15];
public:
    //�R���X�g���N�^
    Field(GameObject* parent);

    //�f�X�g���N�^
    ~Field();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

};