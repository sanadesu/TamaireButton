#include "Player.h"
#include"Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/Image.h"
#include "Engine/Global.h"
#include "Engine/CsvReader.h"
#include "Engine/ScreenSplit.h"
#include "Engine/Audio.h"

#define _USE_MATH_DEFINES
#include<math.h>

#define THIRD_VIEW 1 //三人称視点か一人称視点 一人称はわかりづらいからなし

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),
    hModel_(-1),  pLine(nullptr), pText(nullptr), hSound_Charge(-1), hSound_Throw(-1),
    IsAssist(true)
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
    hSound_Charge = Audio::Load("Star.wav", false, 0.8f, 1);//あとで
    assert(hSound_Charge >= 0);
    hSound_Throw = Audio::Load("Throw.wav", false, 0.8f, 1);
    assert(hSound_Throw >= 0);

    transform_.position_ = XMFLOAT3(START_POS_X, 1.5f, START_POS_Z);
    //transform_.position_.x = (float)(rand() % 180 / 10);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, -0.2f,0), HIT_SIZE);
    AddCollider(collision);

    nowState = WALK_STATE;
    playerID = 0;
    key = 0;
    button = 0;
    processID = 0;
    rightHand = -1;
    leftHand = -1;
    dropTime = 0;
    powerY = 0.0f;
    powerZ = 0.0f;
    trajectoryY = 0.0f;
    trajectoryZ = 0.0f;
    
#if THIRD_VIEW
    viewY = 8.0f; //Y座標
    cameraZ = 15.0f;
#else
    viewY = 3.0f; //Y座標
    cameraZ = 0.1f;
#endif
    stateText = "Player";

    moveLimit = 0.0f;
    goalLength = 0.0f;
    IsFirst = true;
    damage = false;
    chargePower = false;
    IsDrop = false;
    IsEnd = false;
    //IsAssist = true;
    prevPos = transform_;

    pLine = std::make_unique<PoryLine>();
    pLine->Load("tex1.png");
    //pLineW = new PoryLine;
    //pLineW->Load("tex2.jpg");
    //pLineX = new PoryLine;
    //pLineX->Load("tex2.jpg");

    trans = transform_;
    //pCsv->CsvReader("a.csv");
    pText = new Text;
    pText->Initialize();

    pParticle_ = Instantiate<Particle>(this);

    hModel_ = Model::Load("Goma.fbx");
    assert(hModel_ >= 0);
   /* if (playerID % 2 == 0)
    {
        hModel_ = Model::Load("Goma.fbx");
        assert(hModel_ >= 0);
    }
    else
    {
        hModel_ = Model::Load("fryPlayer.fbx");
        assert(hModel_ >= 0);
    }*/
}

//更新
void Player::Update()
{
    
    //bool a = pPlayStop->GetIsStop();
    //動けるかどうか
    
        //最初の一回だけやりたい処理
    if (IsFirst)
    {
        pPlayStop = (PlayStop*)FindObject("PlayStop");
        pResultText = (ResultText*)FindObject("ResultText");
        if (playerID % 2 == 0)
        {
            //白チーム
            hModel_ = Model::Load("WhitePlayer.fbx");
            assert(hModel_ >= 0);
            transform_.position_.x = playerID * -3 - 3;
        }
        else
        {
            //赤チーム
            hModel_ = Model::Load("FryDamage.fbx");
            hModel_ = Model::Load("RedPlayer.fbx");
            assert(hModel_ >= 0);
            transform_.position_.x = playerID * 3;
        }

        //AI
        if (playerID >= ScreenSplit::GetPlayerPerson())
        {
            pPlayStop->SetIsReady(true, playerID);
        }

        IsFirst = false;
    }

    ////準備完了
    //if (Input::IsKeyDown(DIK_R))
    //{
    //    pPlayStop->SetIsReady(true, playerID);
    //}

    if (!(pResultText->GetIsEnd() || pPlayStop->GetIsStop()))
    {
        /*if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X, playerID))
        {
            if (IsAssist)
            {
                IsAssist = false;
            }
            else
            {
                IsAssist = true;
            }
        }*/


        //プレイヤーが色選択できるように後で変える
        //              プレイ人数
        if (playerID >= ScreenSplit::GetPlayerPerson())
        {
            //ステートベースAI
            sManager.Action();//今の状態のアクション
            sManager.NextState();//状態遷移

            //ステートベースAI
            switch (nowState)
            {
            case WALK_STATE://ボールを拾うまで歩く
            {
                //投げる強さの色を戻しておく
                effectCollar = 0;
                //状態表示用、デバッグのみ
                stateText = "Walk";

                //方向転換、後でちゃんとボールを探索で見つけたい(未)
                if (moveLimit > CIRCLE_RANGE)
                    transform_.rotate_.y += 137;
                //移動
                transform_ = FrontDirection(0, 0, PLAYER_MOVE, transform_.rotate_.y, transform_);
                
                //ボールを2個持ってる&ゴールから一定距離離れているか
                if (pBallLeft != nullptr && moveLimit > 50)
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
                        effectCollar += 0.02f;
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
                        transform_.rotate_.y = (float)(atan2(goalRotate.x, goalRotate.z) * 180.0 / M_PI);
                    }
                    else
                    {
                        //ゴールと反対を向く
                        goalLength = 21 - goalLength;
                        transform_.rotate_.y = (float)(atan2(-goalRotate.x, -goalRotate.z) * 180.0 / M_PI);
                    }
                    //力ためる
                    powerY -= POWER;
                    powerZ += POWER;


                    ////アシスト機能オンなら(未)
                    //if (IsAssist)
                    //{
                    //    //ボールの軌道
                    //    trajectoryY = powerY;
                    //    trajectoryZ = powerZ;
                    //    //右手の位置
                    //    trans.position_ = Model::GetBonePosition(hModel_, "joint1");

                    //    for (int j = 0; j < PORY_LENGTH; j++)
                    //    {
                    //        //3フレームおきの場所を入れる
                    //        if (j % 3 == 0)
                    //        {
                    //            pLine->AddPosition(trans.position_);
                    //            //pLineW->AddPositionW(trans.position_);
                    //            //pLineX->AddPositionX(trans.position_);
                    //        }

                    //        // 加速度の演算
                    //        trajectoryY += GRAVITY;
                    //        trans.rotate_ = transform_.rotate_;
                    //        trans = FrontDirection(0, -trajectoryY, trajectoryZ, transform_.rotate_.y, trans);
                    //        trajectoryZ *= RESISTANCE;//抵抗

                    //    }
                    //    //軌道を表示する
                    //    chargePower = true;

                    //}
                    
                    //投げるか
                    //あとでAIかどうか判別                                                
                    if (powerZ > powf(goalLength - ((rand() % 3000) / 1000.0f), 0.5f) * 0.22f )
                    {
                        //if(effectCollar > 2)//エフェクト試す用
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
                chargePower = false;//↑足す？
                powerY = 0;
                powerZ = 0;
                rightHand = leftHand;
                leftHand = -1;
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
            //trans.position_ = Model::GetBonePosition(hModel_, "joint1");
            //pBallRight->PlayerBone(Model::GetBonePosition(hModel_, "joint1"));

        }//左手ボール持ってたら
        if (pBallLeft != nullptr)
        {
            //左手にボール持つ
            pBallLeft->SetBallPos(Model::GetBonePosition(hModel_, "joint2"));
            //pBallLeft->PlayerBone(Model::GetBonePosition(hModel_, "joint2"));
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

           

            if (IsAssist)
            {
                trajectoryY = powerY;
                trajectoryZ = powerZ;
                //右手の位置 予測のやつ
                trans.position_ = Model::GetBonePosition(hModel_, "joint1");

                for (int i = 0; i < PORY_LENGTH; i++)
                {
                    if (i % 3 == 0)
                    {
                        pLine->AddPosition(trans.position_);
                        //pLineW->AddPositionW(trans.position_);
                        //pLineX->AddPositionX(trans.position_);
                    }
                    // 加速度の演算
                    trajectoryY += GRAVITY;

                    trans.rotate_ = transform_.rotate_;
                    trans = FrontDirection(0, -trajectoryY, trajectoryZ, transform_.rotate_.y, trans);

                    trajectoryZ *= RESISTANCE;//抵抗
                }
                chargePower = true;
            }
        }
        if ((((Input::IsKeyUp(DIK_SPACE) && playerID == 0) ||  //キーボード操作
            (Input::IsPadButtonUp(XINPUT_GAMEPAD_A, playerID) || Input::IsPadButtonUp(XINPUT_GAMEPAD_B, playerID) || Input::IsPadButtonUp(XINPUT_GAMEPAD_X, playerID) || Input::IsPadButtonUp(XINPUT_GAMEPAD_Y, playerID))) &&
            rightHand >= 0) )
        {
            effectCollar = 0;
            Audio::Play(hSound_Throw);
            pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
            chargePower = false;
            powerY = 0;
            powerZ = 0;
            rightHand = leftHand;
            leftHand = -1;
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
        //transform_.position_.x += LeftStick.x;
        //transform_.position_.z += LeftStick.y;

        transform_ = FrontDirection(LeftStick.x, 0, LeftStick.y, transform_.rotate_.y, transform_);

        XMFLOAT3 RightStick = Input::GetPadStickR(playerID);
        //RightSrick.x /= 2;
        if (Input::IsKey(DIK_LEFT) && playerID == 0)
        {
            RightStick.x = -1;
        }
        if (Input::IsKey(DIK_RIGHT) && playerID == 0)
        {
            RightStick.x = 1;
        }

#if THIRD_VIEW

        RightStick.x *= 1.5;
#else 

        RightStick.x /= 300;
#endif

        transform_.rotate_.y += RightStick.x;
        //viewY += RightStick.y;//上下回転
        // 
        //hdri
        //ポリヘブン

        if (IsDrop)
        {
            if (dropTime <= DROP_TIME)
            {
                //攻撃された動き
                if (dropTime % 10 == 0)
                {
                    if (playerID % 2 == 0)
                    {
                    }
                    else
                    {
                        hModel_ = Model::Load("FryDamage.fbx");
                        assert(hModel_ >= 0);
                    }
                }
                if (dropTime % 20 == 0)
                {
                    if (playerID % 2 == 0)
                    {
                    }
                    else
                    {
                        hModel_ = Model::Load("Fry2.fbx");
                        assert(hModel_ >= 0);
                    }
                }
                dropTime++;

            }
            else
            {
                if (playerID % 2 == 0)
                {

                }
                else
                {
                    hModel_ = Model::Load("Fry2.fbx");
                    assert(hModel_ >= 0);
                }
                dropTime = 0;
                IsDrop = false;
            }
        }

        //カメラ
        //if (playerID == 0)
        {
#if THIRD_VIEW
            //XMVECTOR vCam = XMVectorSet(0.0f, viewY, -cameraZ, 0.0f);
            //XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

            //vCam = XMVector3TransformCoord(vCam, mRotate);
            //XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
            //XMFLOAT3 camPos;
            //XMStoreFloat3(&camPos, vPos + vCam);//カメラの座標

            //Camera::SetPosition(XMFLOAT3(camPos.x, camPos.y-3, camPos.z ));
            //Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y+5, transform_.position_.z));
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
        }

        //デバッグ用
#ifdef _DEBUG
        if (Input::IsKeyDown(DIK_B))
        {
            int a = 0;
            //Audio::Play(hSound_);
        }
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

    //変数にposとtarget入れるメインで使う
    //Camera::SetPosition(XMFLOAT3(camPos.x, camPos.y - 3, camPos.z));
    //Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y + 5, transform_.position_.z));
    //XMFLOAT3 cameraPos[MAX_PLAYER] = {XMFLOAT3(0,0,0)};
   // XMFLOAT3 cameraTarget[MAX_PLAYER] = { XMFLOAT3(0,0,0) };
                      
    //GetCameraPos(i);
   // GetCameraTarget(i);

    //cameraPos[playerID] = XMFLOAT3(camPos.x, camPos.y - 3, camPos.z);
    //cameraTarget[playerID] = XMFLOAT3(transform_.position_.x, transform_.position_.y + 5, transform_.position_.z);

    Direct3D::SetShader(Direct3D::SHADER_TOON);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    if (IsAssist == false)
        return;

    if (chargePower == true)
    {
        //ポリラインを描画
       pLine->Draw();
        //pLineW->Draw();
        //pLineX->Draw();
    }

}

//開放
void Player::Release()
{
    //ポリライン解放
    pLine->Release();
    //pLineW->Release();
    //pLineX->Release();
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    //ボールにあたる＆どのプレイヤーか＆ボール持ってないか
    if (pTarget->GetObjectName() == "Ball" && IsDrop == false)
    {
        //落ちてるボールか投げてるボールか転がってるボールか
        //↑ボールの状態取得して判別
        pBallThrow = (Ball*)pTarget;
        //投げてるボールだったら
        if (pBallThrow->GetIsThrow())
        {
            rightHand = -1;
            leftHand = -1;
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
            IsDrop = true;
            //振動させたい
            //Input::SetPadVibration(50, 50, playerID);


            //透明にさせる
            
            //値を戻す
            nowState = WALK_STATE;
            chargePower = false;
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

        //投げてるボール
        //持ってるボールを消す
        //一定時間拾えない
        //点滅
    }
}

//角度取得
float Player::GetAngle()
{
    return 0;
}

void Player::SetDamage(bool damage_)
{
    damage = damage_;
}

bool Player::GetDamage()
{
    return damage;
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

int Player::GetState()
{
    return nowState;
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

XMFLOAT3 Player::GetCameraPos(int player_)
{
    cameraPos[player_] = XMFLOAT3(camPos.x, camPos.y - 3, camPos.z);
    return cameraPos[player_];
}

XMFLOAT3 Player::GetCameraTarget(int player_)
{
    cameraTarget[player_] = cameraTarget[player_] = XMFLOAT3(transform_.position_.x, transform_.position_.y + 3, transform_.position_.z);
    return cameraTarget[player_];
}

string Player::GetStateText()
{
    return stateText;
}

void Player::SetIsEnd(bool End_)
{
    IsEnd = End_;
}

void Player::SetIsAssist(bool assist_)
{
    IsAssist = assist_;
}

bool Player::GetIsAssist()
{
    return IsAssist;
}

