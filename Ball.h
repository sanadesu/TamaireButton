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
    const int CIRCLE_RANGE = 360;
    const int NEAR_GOAL = 15;
    const int CIRCLE_OUTSIDE = 450;
    const int DROP_TIME = 600;
    const float BALLSIZE = 0.18f;
    const float POWER = 0.01f;
    const float GRAVITY = 0.05f;
    const float RESISTANCE = 0.97f;
    const float BOUND = 0.6f;
    const float RIGHT_HAND_LENGTH = 1.0f;
    const float LEFT_HAND_LENGTH = -1.0f;
    const float HAND_HEIGHT = 2.5f;
    const float END_MOVE = 0.001f;

    int key;
    int ballDrop;
    int assistKey;
    int playerModel = 0;
    int groundBall;
    float radius;         //�~�̔��a��2��
    float height;       //�o�E���h�̍���
    float powerZ;       //�����鋗��
    float powerY;       //�����鍂��
    float playerRotateY;
    bool throwBall;     //�{�[���𓊂��Ă����
    bool rightHaving;   //�E��
    bool leftHaving;    //����
    bool chargePower;   //�͂����߂Ă��邩
    bool assist;
    bool isThrow;
    bool isHave;
    //XMFLOAT direction;

   
    //Player* pPlayer = (Player*)FindObject("Player");
    //* pBasket = (Basket*)FindObject("Basket");
    GameObject* pBall = FindObject("Ball");
    PoryLine* pLine;
    Transform trans;
    Ground* pGround = (Ground*)FindObject("Ground");
    int a = 0;
    //PlayScene* pPlayScene;
    //Fbx* pFbx;
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


    //�v���C���[���{�[��������
    //�����F�R���g���[���[�̔ԍ� , �E��Ɏ���
    void HandPos(int playerID_, bool rightHand_);

    void PlayerBone(XMFLOAT3 bone);

    void SetPower(float powerY, float powerZ, float rotatePlayer);

    void SetPlayerModel(int model_, int ballID_);

    int GetBallNum();

    bool GetIsThrow();

    void SetBallPos(XMFLOAT3 ballPos);

    void SetIsHave(bool isHave_);

    bool GetIsHave();
};