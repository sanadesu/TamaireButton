#pragma once
#include "Engine/GameObject.h"
#include "PoryLine.h"
#include "Ground.h"
#include"Ball.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"
#include "ResultText.h"
#include "PlayStop.h"

#include<memory>

//���������Ǘ�����N���X
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
    int hSound_Throw;

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

    bool IsFirst;//�ŏ�������肽������
    bool isDamage;            //�U�����󂯂���
    bool isChargePower; //�p���[�`���[�W����
    bool isDrop;            //�ʂ��E���Ȃ���
    bool isAssist;          //�A�V�X�g���肩


    XMFLOAT3 camPos;//�J�����̏ꏊ
    Particle* pParticle_;
    string stateText;

    Transform prevPos; //1�t���[���O�̏ꏊ
    Transform poryTrans;//�{�[���̋O���̏ꏊ
    std::unique_ptr<PoryLine> pLine;//�{�[���̋O����`��
    Ball* pBall;
    Ball* pBallRight;//�E��Ŏ����Ă�{�[��
    Ball* pBallLeft;//����Ŏ����Ă�{�[��
    Ball* pBallThrow;//�������Ă���{�[��
    Ground* pGround;//�{�[���̊Ǘ��Ɏg��
    ResultText* pResultText;
    PlayStop* pPlayStop;
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

    //�U�����󂯂�
    void SetDamage(bool damage_);

    //�U������
    bool GetDamage();

    //�v���C���[�̏ꏊ�擾
    Transform GetPlayerPosition(bool right_);

    Transform FrontDirection(float x_, float y_, float z_, float direction_, Transform trans_);

    //�J�����̏ꏊ�擾
    XMFLOAT3 GetCameraPos();

    //�J�����̃^�[�Q�b�g�擾
    XMFLOAT3 GetCameraTarget();

    //�v���C���[�̏�Ԏ擾
    string GetStateText();

    //�A�V�X�g�Z�b�g
    void SetIsAssist(bool assist_);

    //�A�V�X�g�擾
    bool GetIsAssist();
};