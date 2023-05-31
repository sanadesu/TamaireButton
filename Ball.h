#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Fbx.h"
#include "Basket.h"
#include "PoryLine.h"
#include "Ground.h"

//#include "PlayScene.h"
//◆◆◆を管理するクラス
class Ball : public GameObject
{
    int hModel_[2];    //モデル番号

    enum Player
    {
        First,
        Second,
        Max
    };

    const int DIAMETER = 3800;//地面にランダムにボール配置
    const int HALF = 2;
    const int CHANGE_DECIMAL = 100;//小数に変化
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
    float radius;         //円の半径の2乗
    float height;       //バウンドの高さ
    float powerZ;       //投げる距離
    float powerY;       //投げる高さ
    float playerRotateY;
    bool throwBall;     //ボールを投げている間
    bool rightHaving;   //右手
    bool leftHaving;    //左手
    bool chargePower;   //力をためているか
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
    //コンストラクタ
    Ball(GameObject* parent);

    //デストラクタ
    ~Ball();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;


    //プレイヤーがボールをもつ
    //引数：コントローラーの番号 , 右手に持つか
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