#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Ground : public GameObject
{
    int hModel_;    //���f���ԍ�

    const float GROUND_HEIGHT = -0.27;
    int groundBall;

public:
    //�R���X�g���N�^
    Ground(GameObject* parent);

    //�f�X�g���N�^
    ~Ground();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetGroundBall(int groundBall_);

    int GetGroundBall();

};