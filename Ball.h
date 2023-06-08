#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Fbx.h"
#include "Basket.h"
#include "Engine/PoryLine.h"
#include "Ground.h"

//#include "PlayScene.h"
//���������Ǘ�����N���X
class Ball : public GameObject
{
    int hModel_[2];    //���f���ԍ�

    enum Player
    {
        First,
        Second,
        Max
    };

   
    float radiusPower;         //�~�̔��a��2��
    float powerZ;       //�����鋗��
    float powerY;       //�����鍂��

    bool isThrowBall;     //�{�[���𓊂��Ă����
    bool isThrow;//�����Ă��Ԃ��ǂ���
    bool isHave;//�����Ă����Ԃ��ǂ���

    Ground* pGround;
public:
    int ballID;
    //�R���X�g���N�^
    Ball(GameObject* parent);

    //�f�X�g���N�^
    ~Ball();

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

    //�����鋭�����Z�b�g
    void SetPower(float powerY, float powerZ, float rotatePlayer);

    //�ǂ̃{�[��������
    int GetBallNum();

    //�����Ă��Ԃ��ǂ����擾
    bool GetIsThrow();

    //�ꏊ�Z�b�g
    void SetBallPos(XMFLOAT3 ballPos);

    //�����Ă��邩�ǂ����Z�b�g
    void SetIsHave(bool isHave_);

    //�����Ă��邩�ǂ����擾
    bool GetIsHave();
};