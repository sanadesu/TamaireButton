#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Basket : public GameObject
{
    int hModel_;    //���f���ԍ�

    const float HIT_HEIGHT = 5.0f;
    const float HIT_SIZE = 1.0f;
    const XMFLOAT3 BASKET_POS = XMFLOAT3(0, 5.0f, 0);
public:
    //�R���X�g���N�^
    Basket(GameObject* parent);

    //�f�X�g���N�^
    ~Basket();

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

    //��
    XMFLOAT3 GetBasketPos() { return BASKET_POS; }
};