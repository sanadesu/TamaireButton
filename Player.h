#pragma once
#include "Engine/GameObject.h"
#include "Engine/PoryLine.h"
#include "Ground.h"
#include"Ball.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"
#include "ResultText.h"
#include "PlayStop.h"

#include<memory>

class Player : public GameObject
{
    //�Ȃ��@�����ł������[
    enum PlayerNumber
    {
        FIRST,
        SECOND,
        THIRD,
        FOURTH,
        MAX_PLAYER
    };

    enum State
    {
        WALK_STATE = 0,
        CHARGE_STATE,
        THROW_STATE,
        MAX_STATE
    };

    int hModel_;    //���f���ԍ�
    int hSound_Throw;//�����鉹

    int dropTime;//�{�[�����E���Ȃ�����
    int nowState;//���݂̏��
    int rightHand;//�{�[���������Ă��邩
    int leftHand;//�{�[���������Ă��邩
    float powerY;//�����鋭��
    float powerZ;//�����鋭��
    float trajectoryY;//�{�[���̋O���v�Z
    float trajectoryZ;//�{�[���̋O���v�Z
    float viewY;//�J����Y���W
    float moveLimit;//�ړ��͈�
    float goalLength;//�S�[���܂ł̒���
    float cameraZ; //�J����Z���W
    float effectCollar;//�G�t�F�N�g�O���f�[�V�����p
    float throwPower;//�������

    bool IsFirst;//�ŏ�������肽������
    bool isDamage;            //�U�����󂯂���
    bool isChargePower; //�p���[�`���[�W����
    bool isDrop;            //�ʂ��E���Ȃ���
    bool isAssist;          //�A�V�X�g���肩


    XMFLOAT3 camPos;//�J�����̏ꏊ
    XMFLOAT3 LeftStick;//�ړ��ʂ�����
    XMFLOAT3 RightStick;//��]�ʂ�����
    XMFLOAT3 move;//�v���C���[�ړ���
    XMVECTOR vMove;//���x�N�^�[
    //�J����
    XMVECTOR vCam;
    XMVECTOR vPos;
    XMMATRIX mRotate;

    Particle* pParticle_;//�p���[���߂�G�t�F�N�g
    string stateText;//��ԕ\��

    Transform prevPos; //1�t���[���O�̏ꏊ
    Transform poryTrans;//�{�[���̋O���̏ꏊ
    std::unique_ptr<PoryLine> pLine;//�{�[���̋O����`��
    Ball* pBall;
    Ball* pBallRight;//�E��Ŏ����Ă�{�[��
    Ball* pBallLeft;//����Ŏ����Ă�{�[��
    Ball* pBallThrow;//�������Ă���{�[��
    Ground* pGround;//�{�[���̊Ǘ��Ɏg��
    ResultText* pResultText;
    PlayStop* pPlayStop;//�����邩
    Text* pText;

public:
    int playerID;

    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

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

    //�p�x�擾
    float GetAngle();

    //�U�����ꂽ���Z�b�g
    void SetDamage(bool damage_);

    //�U�����ꂽ���擾
    bool GetDamage();

    //�v���C���[�̏ꏊ�擾
    Transform GetPlayerPosition(bool right_);

    //�v���C���[�J����
    Transform FrontDirection(float x_, float y_, float z_, float direction_, Transform trans_);

    //�J�����̏ꏊ�擾
    XMFLOAT3 GetCameraPos();

    //�J�����̃^�[�Q�b�g�擾
    XMFLOAT3 GetCameraTarget();

    //�v���C���[�̏�Ԏ擾
    string GetStateText();

    //�A�V�X�g�Z�b�g
    void SetIsAssist(bool assist_);

    //�_���[�W��
    void Damage();

    //�U�����ꂽ
    void Attacked();

    //�����鋭���̃G�t�F�N�g�F
    void EffectGradationColor();

    //����
    void WalkMotion();

    //�p���[���߂�
    void ChargeMotion();

    //������
    void ThrowMotion();

    //������{�^���������Ă邩
    bool IsPowerPush();

    //������{�^���𗣂�����
    bool IsThrowPull();

    //�{�[���̋O���\��
    void AssistTrajectory();

    //�ŏ��ɂ�邱�Ƃ��Z�b�g
    void FirstSet();

    //�͂����߂�
    void ChargePower();

    //������
    void Throw();

    //�L�[�{�[�h�ړ�����
    void KeyboardOperation();

    //�f�o�b�O���̂ݍs������
    void Debug();
};