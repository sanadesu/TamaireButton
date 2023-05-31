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
    int hSound_Throw;

    const int CIRCLE_RANGE = 360;//丸の範囲？？？？
    const int PORY_LENGTH = 42;//軌道を保存する長さ?-1
    const int NOT_HAVE = -1;
    const int DROP_TIME = 120;//玉を当てられたときに拾えない時間
    const int CIRCLE_RADIUS = 21;//ゴールから端までの長さ
    const int COM_ROTATE = 137;//コンピューターが端まで行った時の回転量
    const int RANDOM_VALUE = 3000;//ボールを投げるランダム値
    const float ROTATE_SPEED = 1.5f;//回転の速さ
    const float DECIMAL_CHANGE = 1000.0f;//小数にする
    const float THROW_POWER_Y = 0.5f;
    const float POWER_ADJUSTMENT = 0.22f;
    const float PLAYER_INTERVAL = 3.0f;//初期プレイヤー間隔
    const float GOAL_ROTATE = 180.0f;//投げる方向に回転する
    const float POWER = 0.01;//１フレームごとにためる力
    const float GRADATION_VALUE = 0.02f;//エフェクトのグラデーション変化量
    const float NOTTHROW_RANGE = 50.0f;//投げられない範囲
    const float START_POS_X = 0.0f;
    const float START_POS_Z = -6.0f;
    const float HIT_SIZE = 1.7f;//当たり判定
    const float PLAYER_MOVE = 0.1f;//移動距離
    const float GRAVITY = 0.05f;//重力
    const float RESISTANCE = 0.97f;//抵抗

    int dropTime;//ボールを拾えない時間
    int nowState;//現在の状態
    int rightHand;//ボールをもっているか
    int leftHand;//ボールをもっているか
    float powerY;//投げる強さ
    float powerZ;//投げる強さ
    float trajectoryY;//ボールの軌道計算
    float trajectoryZ;//ボールの軌道計算
    float viewY;//カメラY座標
    float moveLimit;//移動範囲
    float goalLength;//ゴールまでの長さ
    float cameraZ; //カメラZ座標
    float effectCollar;//エフェクトグラデーション用

    bool IsFirst;//最初だけやりたい処理
    bool isDamage;            //攻撃を受けたか
    bool isChargePower; //パワーチャージ中か
    bool isDrop;            //玉を拾えないか
    bool isAssist;          //アシストありか


    XMFLOAT3 camPos;//カメラの場所
    StateManager sManager;
    Particle* pParticle_;
    string stateText;

    Transform prevPos; //1フレーム前の場所
    Transform poryTrans;//ボールの軌道の場所
    std::unique_ptr<PoryLine> pLine;//ボールの軌道を描く
    Ball* pBall;
    Ball* pBallRight;//右手で持ってるボール
    Ball* pBallLeft;//左手で持ってるボール
    Ball* pBallThrow;//投げられているボール
    Ground* pGround;//ボールの管理に使う
     StateWalk* pStateWalk;
    ResultText* pResultText;
    PlayStop* pPlayStop;
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

    //攻撃を受ける
    void SetDamage(bool damage_);

    //攻撃治る
    bool GetDamage();

    //プレイヤーの場所取得
    Transform GetPlayerPosition(bool right_);

    Transform FrontDirection(float x_, float y_, float z_, float direction_, Transform trans_);

    //カメラの場所取得
    XMFLOAT3 GetCameraPos();

    //カメラのターゲット取得
    XMFLOAT3 GetCameraTarget();

    //プレイヤーの状態取得
    string GetStateText();

    //アシストセット
    void SetIsAssist(bool assist_);

    //アシスト取得
    bool GetIsAssist();
};