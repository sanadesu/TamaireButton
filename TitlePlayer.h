#pragma once
#include "Engine/GameObject.h"
#include "Engine/Frame.h"
#include "Json.h"

static const int EASE_MAX = 1;//イージングの最大値

class TitlePlayer : public GameObject
{
    enum PlayerID
    {
        PLAYER_RED,
        PLAYER_WHITE
    };

    int hModel_;    //モデル番号

    int redStop;
    float rotateZ;
    float posX;
    float easePlayer;
    float BoundRed;
    float BoundWhite;
    float playerPosRed;
    float playerPosWhite;
    float playerRotateZ;
    Frame* nowFrame = (Frame*)FindObject("Frame");
    nlohmann::json data;
public:
    int T_PlayerID;
    
    //コンストラクタ
    TitlePlayer(GameObject* parent);

    //デストラクタ
    ~TitlePlayer();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

};