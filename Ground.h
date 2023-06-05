#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Ground : public GameObject
{
    int hModel_;    //モデル番号
    int groundBall;//フィールド内のボールの数

public:
    //コンストラクタ
    Ground(GameObject* parent);

    //デストラクタ
    ~Ground();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //ボール数セット
    void SetGroundBall(int groundBall_);

    //ボール数取得
    int GetGroundBall();

};