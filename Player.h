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

//◆◆◆を管理するクラス
class Player : public GameObject
{
    //なし　数字でおっけー
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

    int hModel_;    //モデル番号
    int hSound_Charge;    //サウンド番号
    int hSound_Throw;

    const int CIRCLE_RANGE = 360;//丸の範囲？？？？
    const int PORY_LENGTH = 42;//軌道を保存する長さ?-1
    const int DROP_TIME = 120;//玉を当てられたときに拾えない時間
    const float POWER = 0.01;//１フレームごとにためる力
    const float START_POS_X = 0.0f;
    const float START_POS_Z = -6.0f;
    const float HIT_SIZE = 1.7f;
    const float PLAYER_MOVE = 0.1f;//移動距離
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
    float viewY;               //Y座標
    float moveLimit;        //移動範囲
    float goalLength;
    float cameraZ; //Z座標

    float effectCollar = 0;

    bool IsFirst;
    bool damage;            //攻撃を受けたか
    bool chargePower;
    bool IsDrop;            //玉を拾えない
    bool IsEnd;            //動けるか
    bool IsAssist;          //アシストありか


    XMFLOAT3 camPos = XMFLOAT3(0, 0, 0);
    XMFLOAT3 cameraPos[MAX_PLAYER] = { XMFLOAT3(0,0,0) };
    XMFLOAT3 cameraTarget[MAX_PLAYER] = { XMFLOAT3(0,0,0) };
    StateManager sManager;

    Particle* pParticle_;
    string stateText;

    Transform prevPos; //1フレーム前の場所
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

    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

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

    //角度取得
    float GetAngle();

    ////ボールを持つ
    //void SetHand(bool rightHand_, bool leftHand_);

    ////ボールを持っているか
    //std::pair<bool, bool> GetHand();

    //攻撃を受ける
    void SetDamage(bool damage_);

    //攻撃治る
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