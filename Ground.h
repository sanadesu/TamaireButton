#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Ground : public GameObject
{
    int hModel_;    //���f���ԍ�
    int groundBall;//�t�B�[���h���̃{�[���̐�

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

    //�{�[�����Z�b�g
    void SetGroundBall(int groundBall_);

    //�{�[�����擾
    int GetGroundBall();

};