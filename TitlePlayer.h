#pragma once
#include "Engine/GameObject.h"
#include "Frame.h"

static const int EASE_MAX = 1;//イージングの最大値

class TitlePlayer : public GameObject
{
    enum PlayerID
    {
        PLAYER_RED,
        PLAYER_WHITE
    };

    int hModel_;    //モデル番号
    static const int POS_X = -15;
    static const int MOVE_RANGE = 50;
    const int BOUND_WIDTH = 15;//登場する時の横幅
    const int PLAYER_POS_Y = -2;//プレイヤーの高さ
    const int RED_ANGLE = 170;//赤キャラの角度
    const int WHITE_ANGLE = 190;//白キャラの角度
    const int WHITE_START = 30;//赤キャラから遅れて登場するフレーム数
    const int SWING_WIDTH = 30;//揺れる幅

    const float SIZE = 2.0f;//プレイヤーの大きさ
    const float SWING_ROTATE = 0.01f;//左右に擦れる時の1フレームに回転する値
    const float SWING_POS = 0.05f;//左右に揺れるときの1フレームに動く値
    const float BOUND_EASE_START = 0.5f;//イージングをどこから始めるか
    const float PLAYER_ROTATE = 3.6f;//出てくるときの1フレームの回転量
    const float BOUND_DOWN = 0.01f;//イージングの変化量
    const float SWING_SLOPE = 60.0f;//ゆらゆらの傾き具合
    const float SWING_MOVE = 5.0f;//ゆらゆらの左右移動具合
    const float SWING_POS_RED = 17.5f;//ゆらゆらの左右移動具合
    const float SWING_POS_WHITE = 12.5f;//ゆらゆらの左右移動具合
   

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