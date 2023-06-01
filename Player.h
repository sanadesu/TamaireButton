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