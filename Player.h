#pragma once
#include "Engine/GameObject.h"
#include "PoryLine.h"
#include "Ball.h"
#include "Basket.h"
#include "StateWalk.h"
#include "Ground.h"
#include"Engine/CsvReader.h"
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
    int hSound_Charge;    //�T�E���h�ԍ�
    int hSound_Throw;

    const int CIRCLE_RANGE = 360;//�ۂ͈̔́H�H�H�H
    const int PORY_LENGTH = 42;//�O����ۑ����钷��?-1
    const int DROP_TIME = 120;//�ʂ𓖂Ă�ꂽ�Ƃ��ɏE���Ȃ�����
    const float POWER = 0.01;//�P�t���[�����Ƃɂ��߂��
    const float START_POS_X = 0.0f;
    const float START_POS_Z = -6.0f;
    const float HIT_SIZE = 1.7f;
    const float PLAYER_MOVE = 0.1f;//�ړ�����
    const float HAND_HEIGHT = 2.5f;
    const float GRAVITY = 0.05f;//
    const float RESISTANCE = 0.97f;

    int dropTime;
    int nowState;
    int key;
    int button;
    int processID;
    int rightHand;
    int leftHand;
    float powerY;
    float powerZ;
    float trajectoryY;
    float trajectoryZ;
    float viewY;               //Y���W
    float moveLimit;        //�ړ��͈�
    float goalLength;
    float cameraZ; //Z���W

    float effectCollar = 0;

    bool IsFirst;
    bool damage;            //�U�����󂯂���
    bool chargePower;
    bool IsDrop;            //�ʂ��E���Ȃ�
    bool IsEnd;            //�����邩
    bool IsAssist;          //�A�V�X�g���肩


    XMFLOAT3 camPos = XMFLOAT3(0, 0, 0);
    XMFLOAT3 cameraPos[MAX_PLAYER] = { XMFLOAT3(0,0,0) };
    XMFLOAT3 cameraTarget[MAX_PLAYER] = { XMFLOAT3(0,0,0) };
    StateManager sManager;

    Particle* pParticle_;
    string stateText;

    Transform prevPos; //1�t���[���O�̏ꏊ
    Transform trans;
    std::unique_ptr<PoryLine> pLine;
    PoryLine* pLineW;
    PoryLine* pLineX;
    Ball* pBall = (Ball*)FindObject("Ball");
    Ball* pBallRight = nullptr;
    Ball* pBallLeft = nullptr;
    Ball* pBallThrow = nullptr;
    Basket* pBasket = (Basket*)FindObject("Basket");
    Ground* pGround = (Ground*)FindObject("Ground");
    StateWalk* pStateWalk = (StateWalk*)FindObject("StateWalk");
    ResultText* pResultText;
    PlayStop* pPlayStop;
    CsvReader* pCsv;
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

    ////�{�[��������
    //void SetHand(bool rightHand_, bool leftHand_);

    ////�{�[���������Ă��邩
    //std::pair<bool, bool> GetHand();

    //�U�����󂯂�
    void SetDamage(bool damage_);

    //�U������
    bool GetDamage();

    Transform GetPlayerPosition(bool right_);

    int GetState();

    Transform FrontDirection(float x_, float y_, float z_, float direction_, Transform trans_);

    XMFLOAT3 GetCameraPos(int player_);

    XMFLOAT3 GetCameraTarget(int player_);

    string GetStateText();

    void SetIsEnd(bool End_);

    void SetIsAssist(bool assist_);

    bool GetIsAssist();
};