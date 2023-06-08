#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Fbx.h"
#include "Basket.h"
#include "Engine/PoryLine.h"
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