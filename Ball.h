#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Fbx.h"
#include "Basket.h"
#include "PoryLine.h"
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

    const int DIAMETER = 3800;//�n�ʂɃ����_���Ƀ{�[���z�u
    const int HALF = 2;
    const int CHANGE_DECIMAL = 100;//�����ɕω�
    const int CIRCLE_RANGE = 360;//�n�ʔ͈�
    const int NEAR_GOAL = 15;//�S�[���̋߂�
    const int CIRCLE_OUTSIDE = 450;//�{�[���̐����͈�

    const float BALLSIZE = 0.18f;//�{�[�����a
    const float GRAVITY = 0.05f;//�d��
    const float RESISTANCE = 0.97f;//��R
    const float BOUND = 0.6f;//�o�E���h�̑傫��
    const float END_MOVE = 0.001f;//�{�[�����~�܂�l

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