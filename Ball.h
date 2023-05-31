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
    const int CIRCLE_RANGE = 360;//地面範囲
    const int NEAR_GOAL = 15;//ゴールの近く
    const int CIRCLE_OUTSIDE = 450;//ボールの生存範囲

    const float BALLSIZE = 0.18f;//ボール半径
    const float GRAVITY = 0.05f;//重力
    const float RESISTANCE = 0.97f;//抵抗
    const float BOUND = 0.6f;//バウンドの大きさ
    const float END_MOVE = 0.001f;//ボールが止まる値

    float radiusPower;         //円の半径の2乗
    float powerZ;       //投げる距離
    float powerY;       //投げる高さ

    bool isThrowBall;     //ボールを投げている間
    bool isThrow;//投げてる状態かどうか
    bool isHave;//持っている状態かどうか

    Ground* pGround;
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

    //投げる強さをセット
    void SetPower(float powerY, float powerZ, float rotatePlayer);

    //どのボールか判別
    int GetBallNum();

    //投げてる状態かどうか取得
    bool GetIsThrow();

    //場所セット
    void SetBallPos(XMFLOAT3 ballPos);

    //持っているかどうかセット
    void SetIsHave(bool isHave_);

    //持っているかどうか取得
    bool GetIsHave();
};