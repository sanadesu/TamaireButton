#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class BackGround : public GameObject
{
    int hModel_;    //モデル
    int hModel_Sky;
    Transform transSky;//空のトランスフォーム
    
public:
    //コンストラクタ
    BackGround(GameObject* parent);

    //デストラクタ
    ~BackGround();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

};