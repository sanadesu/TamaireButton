#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/Image.h"
#include "Engine/Global.h"
#include "Engine/CsvReader.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Audio.h"
#include "Engine/Direct3D.h"

#define _USE_MATH_DEFINES
#include<math.h>

#define THIRD_VIEW 1 //三人称視点か一人称視点 一人称はわかりづらいからなし

//定数
namespace
{
    static const int CIRCLE_RANGE = 360;//丸の範囲
    static const int PORY_LENGTH = 42;//軌道を保存する長さ
    static const int NOT_HAVE = -1;//ボールを持っていない
    static const int DROP_TIME = 120;//玉を当てられたときに拾えない時間
    static const int CIRCLE_RADIUS = 21;//ゴールから端までの長さ
    static const int COM_ROTATE = 137;//コンピューターが端まで行った時の回転量
    static const int RANDOM_VALUE = 3000;//ボールを投げるランダム値
    static const float ROTATE_SPEED = 1.5f;//回転の速さ
    static const float DECIMAL_CHANGE = 1000.0f;//小数にする
    static const float THROW_POWER_Y = 0.5f;
    static const float POWER_ADJUSTMENT = 0.22f;
    static const float PLAYER_INTERVAL = 3.0f;//初期プレイヤー間隔
    static const float GOAL_ROTATE = 180.0f;//投げる方向に回転する
    static const float POWER = 0.01;//１フレームごとにためる力
    static const float GRADATION_VALUE = 0.02f;//エフェクトのグラデーション変化量
    static const float NOTTHROW_RANGE = 50.0f;//投げられない範囲
    static const float HIT_SIZE = 1.7f;//当たり判定
    static const float PLAYER_MOVE = 0.1f;//移動距離
    static const float GRAVITY = 0.05f;//重力
    static const float RESISTANCE = 0.97f;//抵抗
    static const float SOUND_VOLUME = 0.8f;//音量
    static const float SOUND_COUNT = 3;//同時に鳴らせる回数

    static const float COLLISION_POS = -0.2f;//当たり判定の場所
    static const XMFLOAT3 START_POS = XMFLOAT3(0, 1.5f, -6);//プレイヤー位置
}

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),
    hModel_(-1),  pLine(nullptr), pText(nullptr), hSound_Throw(-1),
    isAssist(true)
{

}

//デストラクタ
Player::~Player()
{
   // SAFE_DELETE(pLine);
}

//初期化
void Player::Initialize()
{
    //サウンドデータのロード
    hSound_Throw = Audio::Load("Throw.wav", false, SOUND_VOLUME, SOUND_COUNT);
    assert(hSound_Throw >= 0);

    transform_.position_ = START_POS;

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, COLLISION_POS,0), HIT_SIZE);
    AddCollider(collision);

    nowState = WALK_STATE;
    playerID = 0;
    rightHand = -1;
    leftHand = -1;
    dropTime = 0;
    pGround = (Ground*)FindObject("Ground");
    powerY = 0;
    powerZ = 0;
    trajectoryY = 0;
    trajectoryZ = 0;
    
#if THIRD_VIEW
    viewY = 8.0f; //Y座標
    cameraZ = 15.0f;
#else
    viewY = 3.0f; //Y座標
    cameraZ = 0.1f;
#endif
    effectCollar = 0;
    stateText = "Player";

    moveLimit = 0.0f;
    goalLength = 0.0f;
    IsFirst = true;
    isDamage = false;
    isChargePower = false;
    isDrop = false;
    camPos = XMFLOAT3(0, 0, 0);
    prevPos = transform_;

    pLine = std::make_unique<PoryLine>();
    pLine->Load("tex1.png");

    poryTrans = transform_;
    pBall = (Ball*)FindObject("Ball");
    pBallRight = nullptr;
    pBallLeft = nullptr;
    pBallThrow = nullptr;
    //pCsv->CsvReader("a.csv");
    pText = new Text;
    pText->Initialize();
    pParticle_ = Instantiate<Particle>(this);

    hModel_ = Model::Load("WhitePlayer.fbx");
    assert(hModel_ >= 0);
}

//更新
void Player::Update()
{
        //最初の一回だけやりたい処理
    if (IsFirst)
    {
        pResultText = (ResultText*)FindObject("ResultText");
        pPlayStop = (PlayStop*)FindObject("PlayStop");
        if (playerID % 2 == 0)
        {
            //白チーム
            hModel_ = Model::Load("WhitePlayerD0.fbx");
            hModel_ = Model::Load("WhitePlayer.fbx");
            assert(hModel_ >= 0);
            Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
            transform_.position_.x = playerID * -PLAYER_INTERVAL - PLAYER_INTERVAL;
        }
        else
        {
            //赤チーム
            hModel_ = Model::Load("RedPlayerD0.fbx");
            hModel_ = Model::Load("RedPlayer.fbx");
            assert(hModel_ >= 0);
            Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
            transform_.position_.x = playerID * PLAYER_INTERVAL;
        }

        //AI
        if (playerID >= ScreenSplit::GetPlayerPerson())
        {
            pPlayStop->SetIsReady(true, playerID);
        }

        IsFirst = false;
    }

    //ゲームが進行中なら
    if (!(pResultText->GetIsEnd() || pPlayStop->GetIsStop()))
    {
        //AIなら
        if (playerID >= ScreenSplit::GetPlayerPerson())
        {

            //ステートベースAI
            switch (nowState)
            {
            case WALK_STATE://ボールを拾うまで歩く
            {
                //投げる強さの色を戻しておく
                effectCollar = 0;
                //状態表示用、デバッグのみ
                stateText = "Walk";

                if (moveLimit > CIRCLE_RANGE)
                    transform_.rotate_.y += COM_ROTATE;
                //移動
                transform_ = FrontDirection(0, 0, PLAYER_MOVE, transform_.rotate_.y, transform_);
                
                //ボールを2個持ってる&ゴールから一定距離離れているか
                if (pBallLeft != nullptr && moveLimit > NOTTHROW_RANGE)
                {
                    //ボールの投げる強さを決める状態へ
                    nowState = CHARGE_STATE;
                }
                break;
            }
            case CHARGE_STATE://投げる強さを決める
                //状態表示用、デバッグのみにする(未)
                stateText = "Charge";

                //ボールを持ってる
                if (pBallRight != nullptr)
                {
                    {
                        //投げる強さ表示エフェクト
                        EmitterData data;
                        data.textureFileName = "Cloud.png";
                        data.position = Model::GetBonePosition(hModel_, "joint1");//表示位置は手
                        data.position.y -= 0.5f;
                        data.delay = 0;
                        data.number = 50;
                        data.lifeTime = 2;
                        data.dir = XMFLOAT3(0, 1, 0);
                        data.dirErr = XMFLOAT3(90, 90, 90);
                        data.speed = 0.3f;
                        data.speedErr = 0.8f;
                        data.accel = 0.5f;
                        data.size = XMFLOAT2(0.7f, 0.7f);
                        data.sizeErr = XMFLOAT2(0.1, 0.1);
                        data.scale = XMFLOAT2(1.05, 1.05);
                        //エフェクトグラデーション
                        if (effectCollar < 1)
                        {
                            data.color = XMFLOAT4(0, effectCollar, 1 - effectCollar, 1);
                        }
                        else if (effectCollar < 2)
                        {

                            data.color = XMFLOAT4(effectCollar -1, 2 - effectCollar , 0, 1);
                        }
                        else
                        {
                            data.color = XMFLOAT4(effectCollar - 1, 0, 0, 1);
                        }
                        //data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
                        pParticle_->Start(data);
                        
                        //グラデーション用
                        effectCollar += GRADATION_VALUE;
                    }

                    //ゴールを向く
                    XMFLOAT3 origine = XMFLOAT3(0, 0, 0);
                    XMVECTOR vOrigin = XMLoadFloat3(&origine);
                    XMFLOAT3 HandPos = Model::GetBonePosition(hModel_, "joint1");
                    XMVECTOR vPlayerPos = XMLoadFloat3(&HandPos);
                    XMVECTOR vGoal = vOrigin - vPlayerPos; //ゴールへの向き

                    //ゴールまでの長さ
                    XMVECTOR vGoalLength = XMVector3Length(vGoal);
                    goalLength = XMVectorGetX(vGoalLength);
                    //ゴールの方向
                    XMFLOAT3 goalRotate;
                    XMStoreFloat3(&goalRotate, vGoal);
                    //持ってるボールが自分のか
                    if (playerID % 2 == pBallRight->ballID % 2)
                    {
                        //ゴール向く
                        transform_.rotate_.y = (float)(atan2(goalRotate.x, goalRotate.z) * GOAL_ROTATE / M_PI);
                    }
                    else
                    {
                        //ゴールと反対を向く
                        goalLength = CIRCLE_RADIUS - goalLength;
                        transform_.rotate_.y = (float)(atan2(-goalRotate.x, -goalRotate.z) * GOAL_ROTATE / M_PI);
                    }
                    //力ためる
                    powerY -= POWER;
                    powerZ += POWER;

                    //投げるか
                    //あとでAIかどうか判別                                                
                    if (powerZ > powf(goalLength - ((rand() % RANDOM_VALUE) / DECIMAL_CHANGE), THROW_POWER_Y) * POWER_ADJUSTMENT)
                    {
                        nowState = THROW_STATE;//ボールを投げる状態へ
                    }
                }
                break;
            case THROW_STATE://ボール投げる
                //投げる強さの色を戻しておく
                effectCollar = 0;
                //状態表示用、デバッグのみにする(未)
                stateText = "Throw";


                pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
                isChargePower = false;//↑足す？
                powerY = 0;
                powerZ = 0;
                rightHand = leftHand;
                leftHand = NOT_HAVE;
                pBallRight = pBallLeft;
                pBallLeft = nullptr;//ここまで？
                //あとでAIかどうか判別 
                //ボール持ってなかったら
                if (pBallRight == nullptr)
                {
                    //ボール探す
                    nowState = WALK_STATE;
                }
                else//持ってたら
                {
                    //投げる
                    nowState = CHARGE_STATE;
                }
                
                break;
            default:
                nowState = WALK_STATE;
                break;
            }
        }

        //右手ボール持ってたら
        if (pBallRight != nullptr)
        {
            //右手にボール持つ
            pBallRight->SetBallPos(Model::GetBonePosition(hModel_, "joint1"));

        }//左手ボール持ってたら
        if (pBallLeft != nullptr)
        {
            //左手にボール持つ
            pBallLeft->SetBallPos(Model::GetBonePosition(hModel_, "joint2"));
        }

        //いる場所、二乗
        moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);

        if (moveLimit > CIRCLE_RANGE)
        {
            //後で変える
            if (transform_.position_.x < 0)
            {
                transform_.position_.x = prevPos.position_.x;
            }
            else if (transform_.position_.x > 0)
            {
                transform_.position_.x = prevPos.position_.x;
            }

            if (transform_.position_.z < 0)
            {
                transform_.position_.z = prevPos.position_.z;
            }
            else if (transform_.position_.z > 0)
            {
                transform_.position_.z = prevPos.position_.z;
            }
        }

        prevPos = transform_;

        //XMFLOAT3
        //なげる
        if (((Input::IsKey(DIK_SPACE) && playerID == 0) || //キーボード操作
            (Input::IsPadButton(XINPUT_GAMEPAD_A, playerID) || 
             Input::IsPadButton(XINPUT_GAMEPAD_B, playerID) || 
             Input::IsPadButton(XINPUT_GAMEPAD_X, playerID) || 
             Input::IsPadButton(XINPUT_GAMEPAD_Y, playerID))) &&
            rightHand >= 0)
        {
            if (effectCollar < 2)
            {
                //力ためるやつ
                powerY -= POWER;
                powerZ += POWER;
                //グラデーション用
                effectCollar += 0.02f;
            }
            

            //投げる強さ表示エフェクト
            EmitterData data;
            data.textureFileName = "Cloud.png";
            data.position = Model::GetBonePosition(hModel_, "joint1");//表示位置は手
            data.position.y -= 0.5f;
            data.delay = 0;
            data.number = 50;
            data.lifeTime = 2;
            data.dir = XMFLOAT3(0, 1, 0);
            data.dirErr = XMFLOAT3(90, 90, 90);
            data.speed = 0.3f;
            data.speedErr = 0.8f;
            data.accel = 0.5f;
            data.size = XMFLOAT2(0.7f, 0.7f);
            data.sizeErr = XMFLOAT2(0.1, 0.1);
            data.scale = XMFLOAT2(1.05, 1.05);
            //エフェクトグラデーション
            if (effectCollar < 1)
            {
                data.color = XMFLOAT4(0, effectCollar, 1 - effectCollar, 1);
            }
            else if (effectCollar < 2)
            {

                data.color = XMFLOAT4(effectCollar - 1, 2 - effectCollar, 0, 1);
            }
            else
            {
                data.color = XMFLOAT4(effectCollar - 1, 0, 0, 1);
            }
            //data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
            pParticle_->Start(data);

           

            if (isAssist)
            {
                trajectoryY = powerY;
                trajectoryZ = powerZ;
                //右手の位置 予測のやつ
                poryTrans.position_ = Model::GetBonePosition(hModel_, "joint1");

                for (int i = 0; i < PORY_LENGTH; i++)
                {
                    if (i % 3 == 0)
                        pLine->AddPosition(poryTrans.position_);

                    // 加速度の演算
                    trajectoryY += GRAVITY;

                    poryTrans.rotate_ = transform_.rotate_;
                    poryTrans = FrontDirection(0, -trajectoryY, trajectoryZ, transform_.rotate_.y, poryTrans);

                    trajectoryZ *= RESISTANCE;//抵抗
                }
                isChargePower = true;
            }
        }
        if ((((Input::IsKeyUp(DIK_SPACE) && playerID == 0) ||  //キーボード操作
            (Input::IsPadButtonUp(XINPUT_GAMEPAD_A, playerID) || Input::IsPadButtonUp(XINPUT_GAMEPAD_B, playerID) || Input::IsPadButtonUp(XINPUT_GAMEPAD_X, playerID) || Input::IsPadButtonUp(XINPUT_GAMEPAD_Y, playerID))) &&
            rightHand >= 0) )
        {
            effectCollar = 0;
            Audio::Play(hSound_Throw);
            pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
            isChargePower = false;
            powerY = 0;
            powerZ = 0;
            rightHand = leftHand;
            leftHand = NOT_HAVE;
            pBallRight = pBallLeft;
            pBallLeft = nullptr;
        }

        //移動
        XMFLOAT3 LeftStick = Input::GetPadStickL(playerID);
        if (Input::IsKey(DIK_W) && playerID == 0)
        {
            LeftStick.y = 1;
        }
        if (Input::IsKey(DIK_A) && playerID == 0)
        {
            LeftStick.x = -1;
        }
        if (Input::IsKey(DIK_S) && playerID == 0)
        {
            LeftStick.y = -1;
        }
        if (Input::IsKey(DIK_D) && playerID == 0)
        {
            LeftStick.x = 1;
        }
        //自動回転
        transform_.rotate_.y += LeftStick.x / 2;
        LeftStick.x /= 10;
        LeftStick.y /= 10;

        transform_ = FrontDirection(LeftStick.x, 0, LeftStick.y, transform_.rotate_.y, transform_);

        XMFLOAT3 RightStick = Input::GetPadStickR(playerID);
        if (Input::IsKey(DIK_LEFT) && playerID == 0)
        {
            RightStick.x = -1;
        }
        if (Input::IsKey(DIK_RIGHT) && playerID == 0)
        {
            RightStick.x = 1;
        }

#if THIRD_VIEW

        RightStick.x *= ROTATE_SPEED;
#else 

        RightStick.x /= 300;
#endif
        transform_.rotate_.y += RightStick.x;
        
        if (isDrop)
        {
            if (dropTime <= DROP_TIME)
            {
                //攻撃された動き
                if (dropTime % 10 == 0)
                {
                    if (playerID % 2 == 0)
                    {
                        hModel_ = Model::Load("WhitePlayerD0.fbx");
                        assert(hModel_ >= 0);
                        Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
                    }
                    else
                    {
                        hModel_ = Model::Load("RedPlayerD0.fbx");
                        assert(hModel_ >= 0);
                        Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
                    }
                }
                if (dropTime % 20 == 0)
                {
                    if (playerID % 2 == 0)
                    {
                        hModel_ = Model::Load("WhitePlayer.fbx");
                        assert(hModel_ >= 0);
                        Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
                    }
                    else
                    {
                        hModel_ = Model::Load("RedPlayer.fbx");
                        assert(hModel_ >= 0);
                        Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
                    }
                }
                dropTime++;
            }
            else
            {
                if (playerID % 2 == 0)
                {
                    hModel_ = Model::Load("WhitePlayer.fbx");
                    assert(hModel_ >= 0);
                    Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
                }
                else
                {
                    hModel_ = Model::Load("RedPlayer.fbx");
                    assert(hModel_ >= 0);
                    Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
                }
                dropTime = 0;
                isDrop = false;
            }
        }

        //カメラ
#if THIRD_VIEW
            //
#else 
            XMVECTOR vCam = XMVectorSet(0.0f, viewY, cameraZ, 0.0f);
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

            vCam = XMVector3TransformCoord(vCam, mRotate);
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
            XMFLOAT3 camPos;
            XMStoreFloat3(&camPos, vPos + vCam);//カメラの座標

            XMFLOAT3 cameraPos = transform_.position_;
            cameraPos.y += 3;
            Camera::SetPosition(cameraPos);

            Camera::SetTarget(camPos);
#endif

        //デバッグ用
#ifdef _DEBUG
        if (Input::IsKeyDown(DIK_1))
        {
            ScreenSplit::SetScreenSplit(1);
        }
        if (Input::IsKeyDown(DIK_2))
        {
            ScreenSplit::SetScreenSplit(2);
        }
        if (Input::IsKeyDown(DIK_4))
        {
            ScreenSplit::SetScreenSplit(4);
        }//振動試し
        if (Input::IsPadButton(XINPUT_GAMEPAD_X))
        {
            Input::SetPadVibration(50, 50, playerID);//☆
        }
#endif
    }
}

//描画
void Player::Draw()   
{                     
    XMVECTOR vCam = XMVectorSet(0.0f, viewY, -cameraZ, 0.0f);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMStoreFloat3(&camPos, vPos + vCam);//カメラの座標

    Direct3D::SetShader(Direct3D::SHADER_TOON);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    if (isAssist == false)
        return;

    //ポリラインを描画
    if (isChargePower)
       pLine->Draw();

}

//開放
void Player::Release()
{
    //ポリライン解放
    pLine->Release();
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    //ボールにあたる＆どのプレイヤーか＆ボール持ってないか
    if (pTarget->GetObjectName() == "Ball" && isDrop == false)
    {
        //落ちてるボールか投げてるボールか転がってるボールか
        //↑ボールの状態取得して判別
        pBallThrow = (Ball*)pTarget;
        //投げてるボールだったら
        if (pBallThrow->GetIsThrow())
        {
            rightHand = NOT_HAVE;
            leftHand = NOT_HAVE;
            if (pBallRight != nullptr)
            {
                pGround->SetGroundBall(-1);
                pBallRight->KillMe();
                pBallRight = nullptr;
            }
            if (pBallLeft != nullptr)
            {
                pGround->SetGroundBall(-1);
                pBallLeft->KillMe();
                pBallLeft = nullptr;
            }
            isDrop = true;
            //値を戻す
            nowState = WALK_STATE;
            isChargePower = false;
            powerY = 0;
            powerZ = 0;
        } //持ってるボール
        else if (pBallThrow->GetIsHave())
        {
            //
        }//右手があいてる
        else if (rightHand < 0)
        {
            //右手にボールもつ
            pBallRight = (Ball*)pTarget;
            pBallThrow->SetIsHave(true);
            //当たったボールの番号
            rightHand = pBallRight->GetBallNum();
        }//左手があいてる
        else if (leftHand < 0)
        {
            //左手にボールもつ
            pBallLeft = (Ball*)pTarget;
            pBallThrow->SetIsHave(true);
            //当たったボールの番号
            leftHand = pBallLeft->GetBallNum();
        }
    }
}

//角度取得
float Player::GetAngle()
{
    return 0;
}

void Player::SetDamage(bool damage_)
{
    isDamage = damage_;
}

bool Player::GetDamage()
{
    return isDamage;
}

Transform Player::GetPlayerPosition(bool right)
{
    Transform trans_ = transform_;

    if (right == true)
    {
        trans_.position_ = Model::GetBonePosition(hModel_, "joint1");
    }
    else
    {
        trans_.position_ = Model::GetBonePosition(hModel_, "joint2");
    }

    return trans_;
}


Transform Player::FrontDirection(float x_, float y_, float z_, float direction_, Transform trans_)
{
    XMFLOAT3 move = { x_,y_,z_ }; //移動量
    XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(direction_));   //Y軸でｙ°回転させる行列

    vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
    XMVECTOR vPos = XMLoadFloat3(&trans_.position_); //現在地をベクトルに変換

    vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

    XMStoreFloat3(&trans_.position_, vPos);
    return trans_;
}

XMFLOAT3 Player::GetCameraPos()
{
    return XMFLOAT3(camPos.x, camPos.y - 3, camPos.z);
}

XMFLOAT3 Player::GetCameraTarget()
{
    return XMFLOAT3(transform_.position_.x, transform_.position_.y + 3, transform_.position_.z);;
}

string Player::GetStateText()
{
    return stateText;
}

void Player::SetIsAssist(bool assist_)
{
    isAssist = assist_;
}

bool Player::GetIsAssist()
{
    return isAssist;
}

