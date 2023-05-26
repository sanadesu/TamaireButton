#include "TitlePlayer.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"
#include "Engine/Easing.h"
#include "TitleScene.h"
#include "TitleButton.h"
//コンストラクタ
TitlePlayer::TitlePlayer(GameObject* parent)
    :GameObject(parent, "TitlePlayer"), hModel_(-1)
{

}

//デストラクタ
TitlePlayer::~TitlePlayer()
{
}

//初期化
void TitlePlayer::Initialize()
{
    T_PlayerID = 0;
    redStop = 0;
    rotateZ = SWING_ROTATE;
    posX = SWING_POS;
    easePlayer = BOUND_EASE_START;
    BoundRed = EASE_MAX;
    BoundWhite = EASE_MAX;
    playerPosRed = POS_X + MOVE_RANGE;
    playerPosWhite = POS_X + MOVE_RANGE;
    playerRotateZ = 0;
    hModel_ = Model::Load("Fry.fbx");
    assert(hModel_ >= 0);
    transform_.position_.z += 30;
    transform_.scale_.x *= SIZE;
    transform_.scale_.y *= SIZE;
    transform_.scale_.z *= SIZE;
}

//更新
void TitlePlayer::Update()
{
    TitleScene* pTitle = (TitleScene*)FindObject("TitleScene");

    if (T_PlayerID == PLAYER_RED && BoundRed != 0)
    {
        if (pTitle->GetIsSkip())
        {
            BoundRed = 0;

            playerPosRed = POS_X;
            playerRotateZ = 0;
        }

        transform_.position_.y = Easing::EaseInBounce(BoundRed) * BOUND_WIDTH + PLAYER_POS_Y;
        transform_.position_.x = playerPosRed;
        transform_.rotate_.z = -playerRotateZ;
        transform_.rotate_.y = RED_ANGLE;

        if (playerPosRed > POS_X)
        {
            playerPosRed -= MOVE_RANGE / (EASE_MAX / BOUND_DOWN);
            playerRotateZ += PLAYER_ROTATE;
            if (playerPosRed < POS_X)
                playerPosRed = POS_X;

        }

        if (BoundRed > 0)
        {
            BoundRed -= BOUND_DOWN;
            if (BoundRed <= 0)
            {
                BoundRed = 0;
                transform_.rotate_.z = 0;
                redStop = nowFrame->GetFrame();
            }
        }
    }
    else if(T_PlayerID == PLAYER_WHITE)
    {
        //☆
        hModel_ = Model::Load("GomaPlayer.fbx");
        assert(hModel_ >= 0);

        if ((nowFrame->GetFrame() > WHITE_START && BoundWhite != 0) || pTitle->GetIsSkip())
        {
            if (pTitle->GetIsSkip())
            {
                BoundWhite = 0;

                playerPosWhite = POS_X;
                playerRotateZ = 0;
            }
            transform_.position_.x = -playerPosWhite;
            transform_.position_.y = Easing::EaseInBounce(BoundWhite) * BOUND_WIDTH + PLAYER_POS_Y;
            //transform_.rotate_.z = playerRotateZ;
            transform_.rotate_.y = WHITE_ANGLE;
            if (playerPosWhite > POS_X)
            {
                playerPosWhite -= MOVE_RANGE / (EASE_MAX / BOUND_DOWN);
                playerRotateZ += PLAYER_ROTATE;
                if (playerPosWhite < POS_X)
                    playerPosWhite = POS_X;

            }
            if (BoundWhite > 0)
            {
                transform_.rotate_.z = playerRotateZ;
                BoundWhite -= BOUND_DOWN;
                if (BoundWhite <= 0)
                {
                    BoundWhite = 0;
                    transform_.rotate_.z = 0;
                }
            }
        }
    }
    
    if (BoundWhite == 0 || BoundRed == 0)
    {
        if(nowFrame->GetFrame() > redStop + WHITE_START || T_PlayerID == PLAYER_WHITE || pTitle->GetIsSkip())
        {
            //transform_.rotate_.z += rotateZ;
            easePlayer += rotateZ;
            if (easePlayer > EASE_MAX)
            {
                easePlayer = EASE_MAX;
            }
            else if(easePlayer < 0)
            {
                easePlayer = 0;
            }

            //ゆらゆらさせる
            if (T_PlayerID == PLAYER_RED)
            {
                transform_.rotate_.z = -((Easing::EaseInOutCubic(easePlayer) * SWING_SLOPE) - (SWING_SLOPE / 2));
                transform_.position_.x = (Easing::EaseInOutCubic(1 - easePlayer) * SWING_MOVE) - SWING_POS_RED;
            }
            else if (T_PlayerID == PLAYER_WHITE)
            {
                transform_.rotate_.z = (Easing::EaseInOutCubic(easePlayer) * SWING_SLOPE) - (SWING_SLOPE / 2);
                transform_.position_.x = (Easing::EaseInOutCubic(easePlayer) * SWING_MOVE) + SWING_POS_WHITE;
            }
                
        }

        //揺れを反対方向にする
        if (abs(transform_.rotate_.z) >= SWING_WIDTH)
        {
            rotateZ *= -1;
            posX *= -1;
        }
    }
}

//描画
void TitlePlayer::Draw()
{
    TitleButton* pTitleButton = (TitleButton*)FindObject("TitleRuleButton");
    if (pTitleButton->GetTitleState() == 0)
    {
        TitleScene* pTitle = (TitleScene*)FindObject("TitleScene");
        Direct3D::SetShader(Direct3D::SHADER_TOON);//☆
        if (T_PlayerID == PLAYER_RED)
        {
            Model::SetTransform(hModel_, transform_);
            Model::Draw(hModel_);
        }
        else if ((nowFrame->GetFrame() > WHITE_START + 1 && T_PlayerID == PLAYER_WHITE) || pTitle->GetIsSkip())
        {
            Model::SetTransform(hModel_, transform_);
            Model::Draw(hModel_);
        }
       
        Direct3D::SetShader(Direct3D::SHADER_TOON);
    }
}

//開放
void TitlePlayer::Release()
{
}