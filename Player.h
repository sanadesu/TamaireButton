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
    int hSound_Throw;//投げる音

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
    float throwPower;//投げる力

    bool IsFirst;//最初だけやりたい処理
    bool isDamage;            //攻撃を受けたか
    bool isChargePower; //パワーチャージ中か
    bool isDrop;            //玉を拾えないか
    bool isAssist;          //アシストありか


    XMFLOAT3 camPos;//カメラの場所
    XMFLOAT3 LeftStick;//移動量を入れる
    XMFLOAT3 RightStick;//回転量を入れる
    XMFLOAT3 move;//プレイヤー移動量
    XMVECTOR vMove;//↑ベクター
    //カメラ
    XMVECTOR vCam;
    XMVECTOR vPos;
    XMMATRIX mRotate;

    Particle* pParticle_;//パワー溜めるエフェクト
    string stateText;//状態表示

    Transform prevPos; //1フレーム前の場所
    Transform poryTrans;//ボールの軌道の場所
    std::unique_ptr<PoryLine> pLine;//ボールの軌道を描く
    Ball* pBall;
    Ball* pBallRight;//右手で持ってるボール
    Ball* pBallLeft;//左手で持ってるボール
    Ball* pBallThrow;//投げられているボール
    Ground* pGround;//ボールの管理に使う
    ResultText* pResultText;
    PlayStop* pPlayStop;//動けるか
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

    //攻撃されたかセット
    void SetDamage(bool damage_);

    //攻撃されたか取得
    bool GetDamage();

    //プレイヤーの場所取得
    Transform GetPlayerPosition(bool right_);

    //プレイヤーカメラ
    Transform FrontDirection(float x_, float y_, float z_, float direction_, Transform trans_);

    //カメラの場所取得
    XMFLOAT3 GetCameraPos();

    //カメラのターゲット取得
    XMFLOAT3 GetCameraTarget();

    //プレイヤーの状態取得
    string GetStateText();

    //アシストセット
    void SetIsAssist(bool assist_);

    //ダメージ中
    void Damage();

    //攻撃された
    void Attacked();

    //投げる強さのエフェクト色
    void EffectGradationColor();

    //歩く
    void WalkMotion();

    //パワー溜める
    void ChargeMotion();

    //投げる
    void ThrowMotion();

    //投げるボタンを押してるか
    bool IsPowerPush();

    //投げるボタンを離したか
    bool IsThrowPull();

    //ボールの軌道予測
    void AssistTrajectory();

    //最初にやることをセット
    void FirstSet();

    //力をためる
    void ChargePower();

    //投げる
    void Throw();

    //キーボード移動操作
    void KeyboardOperation();

    //デバッグ時のみ行う処理
    void Debug();
};