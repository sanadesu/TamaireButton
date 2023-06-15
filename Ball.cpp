#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "ResultText.h"
#include "PlayScene.h"
#include "PlayStop.h"

//定数
namespace
{
    static const int DIAMETER = 3800;//地面にランダムにボール配置
    static const int HALF = 2;
    static const int CHANGE_DECIMAL = 100;//小数に変化
    static const int CIRCLE_RANGE = 360;//地面範囲
    static const int NEAR_GOAL = 15;//ゴールの近く
    static const int CIRCLE_OUTSIDE = 450;//ボールの生存範囲
    static const float BALL_SIZE = 1.3f;//ボールの大きさ
    static const float BALL_COL_SIZE = 0.23f;//ボールの当たり判定
    static const float GRAVITY = 0.05f;//重力
    static const float RESISTANCE = 0.97f;//抵抗
    static const float BOUND = 0.6f;//バウンドの大きさ
    static const float END_MOVE = 0.001f;//ボールが止まる値
    static const float CENTER_MOVE = 0.5f;//ゴールした時中央に寄る値、大きいほど中央に行く
}

//コンストラクタ
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball")
{
    for (int i : hModel_)
    {

        hModel_[i] = -1;
    }
    ballID = 0;
}

//デストラクタ
Ball::~Ball()
{
}

//初期化
void Ball::Initialize()
{
    radiusPower = 0;
    powerZ = 0;
    powerY = 0;
    isThrowBall = false;
    isThrow = false;

    std::string fileName[] = { "WhiteBall.fbx","RedBall.fbx" };
    //モデルデータのロード
    for (int i = 0; i < 2; i++)
    {
        std::string fn = fileName[i];
        hModel_[i] = Model::Load(fn);
        assert(hModel_[i] >= 0);
        Model::SetShederType(hModel_[i], Direct3D::SHADER_TOON);
    }

    transform_.scale_ = XMFLOAT3(BALL_SIZE, BALL_SIZE, BALL_SIZE);
    transform_.position_.y = 0.2f;
    do
    {
        transform_.position_.x = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;
        transform_.position_.z = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;

        radiusPower = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    } while (radiusPower >= CIRCLE_RANGE || radiusPower < NEAR_GOAL);

    pGround = (Ground*)FindObject("Ground");

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), BALL_COL_SIZE);
    AddCollider(collision);
}

//更新
void Ball::Update()
{
    PlayStop* pPlayStop = (PlayStop*)FindObject("PlayStop");
    if (pPlayStop->GetIsStop() == false)
    {
        //後でキーを変えられるようにしてfor文

        //投げるときのボールの動き
        if (isThrowBall == true)
        {
            //加速度の演算
            powerY += GRAVITY;

            // スピードの演算
            XMFLOAT3 move = { 0,-powerY,powerZ }; //移動量
            XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            XMStoreFloat3(&transform_.position_, vPos);

            powerZ *= RESISTANCE;//抵抗

            // バウンドの判定
            if (transform_.position_.y <= 0.0f)
            {  // ボールが下に当たったら
                isThrow = false;
                transform_.position_.y = 0.0;
                powerY = -powerY * BOUND;  // y軸のスピードを反転して玉入れっぽくあまり
                powerZ *= RESISTANCE;//抵抗

                //当たり判定終わりにする　あとで
            }

            //移動が終わる
            if (powerZ <= END_MOVE)
            {
                powerZ = 0;
                powerY = 0;
                isThrowBall = false;
                isHave = false;
            }
        }
        //デバッグ用
        if (Input::IsKey(DIK_B))
        {
            int a = 0;
        }

        ////円の範囲外なら消える
        radiusPower = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
        if (radiusPower > CIRCLE_OUTSIDE)
        {
            pGround->SetGroundBall(-1);
            KillMe();
        }

    }
}

//描画
void Ball::Draw()
{
    
        if (ballID % 2 == 0)
        {
            Model::SetTransform(hModel_[0], transform_);
            Model::Draw(hModel_[0]);
        }
        else
        {
            Model::SetTransform(hModel_[1], transform_);
            Model::Draw(hModel_[1]);
        }
    
   
}

//開放
void Ball::Release()
{

}

//当たり判定
void Ball::OnCollision(GameObject* pTarget)
{
    //ゴールに当たったとき
    if (pTarget->GetObjectName() == "Basket" && isThrowBall)
    {
        ResultText* pResultText = (ResultText*)FindObject("ResultText");
        hModel_[0];
        this->hModel_;

        if (ballID % 2 == 0)
        {
            //ゴールに入ったら得点
            pResultText->WhiteCount();
            pGround->SetGroundBall(-1);
            
        }
        else
        {
            pResultText->RedCount();
            pGround->SetGroundBall(-1);
        }

        isThrowBall = false;

        //中心の計算
        Basket* pBasket = (Basket*)FindObject("Basket");
        XMFLOAT3 basketPos = pBasket->GetBasketPos();
        XMVECTOR vBasket = XMLoadFloat3(&basketPos);
        XMVECTOR vBall = XMLoadFloat3(&transform_.position_);
        XMVECTOR vCenter = vBasket - vBall;//中心の向き
        vCenter = XMVector3Normalize(vCenter);
        vCenter *= CENTER_MOVE;
        XMFLOAT3 centerRotate;
        XMStoreFloat3(&centerRotate, vCenter);
        //中心方向に移動
        transform_.position_.x += centerRotate.x;
        transform_.position_.y += centerRotate.y;
        transform_.position_.z += centerRotate.z;
    }
}

void Ball::SetPower(float powerY_, float powerZ_, float playerRotateY_)
{
    powerY = powerY_;
    powerZ = powerZ_;
    transform_.rotate_.y = playerRotateY_;
    isThrowBall = true;
    isThrow = true;
}

int Ball::GetBallNum()
{
    //return ballID;//??
    return 1;
}

bool Ball::GetIsThrow()
{
    return isThrow;
}

void Ball::SetBallPos(XMFLOAT3 ballPos)
{
    transform_.position_ = ballPos;
}

void Ball::SetIsHave(bool isHave_)
{
    isHave = isHave_;
}

bool Ball::GetIsHave()
{
    return isHave;
}


