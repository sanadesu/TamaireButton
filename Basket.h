#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Basket : public GameObject
{
    int hModel_;    //モデル番号

    const float HIT_HEIGHT = 5.0f;
    const float HIT_SIZE = 1.0f;
    const XMFLOAT3 BASKET_POS = XMFLOAT3(0, 5.0f, 0);
public:
    //コンストラクタ
    Basket(GameObject* parent);

    //デストラクタ
    ~Basket();

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

    //☆
    XMFLOAT3 GetBasketPos() { return BASKET_POS; }
};