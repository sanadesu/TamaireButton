#pragma once
#include "Engine/GameObject.h"
#include "PoryLine.h"
#include "StateWalk.h"
#include "Ground.h"
#include"Ball.h"
#include "Engine/Text.h"
#include "StateManager.h"
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

    const int CIRCLE_RANGE = 360;//�ۂ͈̔́H�H�H�H
    const int PORY_LENGTH = 42;//�O����ۑ����钷��?-1
    const int NOT_HAVE = -1;
    const int DROP_TIME = 120;//�ʂ𓖂Ă�ꂽ�Ƃ��ɏE���Ȃ�����
    const int CIRCLE_RADIUS = 21;//�S�[������[�܂ł̒���
    const int COM_ROTATE = 137;//�R���s���[�^�[���[�܂ōs�������̉�]��
    const int RANDOM_VALUE = 3000;//�{�[���𓊂��郉���_���l
    const float ROTATE_SPEED = 1.5f;//��]�̑���
    const float DECIMAL_CHANGE = 1000.0f;//�����ɂ���
    const float THROW_POWER_Y = 0.5f;
    const float POWER_ADJUSTMENT = 0.22f;
    const float PLAYER_INTERVAL = 3.0f;//�����v���C���[�Ԋu
    const float GOAL_ROTATE = 180.0f;//����������ɉ�]����
    const float POWER = 0.01;//�P�t���[�����Ƃɂ��߂��
    const float GRADATION_VALUE = 0.02f;//�G�t�F�N�g�̃O���f�[�V�����ω���
    const float NOTTHROW_RANGE = 50.0f;//�������Ȃ��͈�
    const float START_POS_X = 0.0f;
    const float START_POS_Z = -6.0f;
    const float HIT_SIZE = 1.7f;//�����蔻��
    const float PLAYER_MOVE = 0.1f;//�ړ�����
    const float GRAVITY = 0.05f;//�d��
    const float RESISTANCE = 0.97f;//��R

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
    StateManager sManager;
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
     StateWalk* pStateWalk;
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