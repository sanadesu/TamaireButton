#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "ResultText.h"
#include "PlayScene.h"
#include "PlayStop.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball")
{
    for (int i : hModel_)
    {

        hModel_[i] = -1;
    }
    ballID = 0;
}

//�f�X�g���N�^
Ball::~Ball()
{
}

//������
void Ball::Initialize()
{
    //const int WhiteConstParam::DIAMETER = 3800;


    key = 0;
    radius = 0;


    height = 1;
    powerZ = 0;
    powerY = 0;
    ballDrop = 0;
    throwBall = false;
    rightHaving = false;
    leftHaving = false;
    chargePower = false;
    assist = false;
    isThrow = false;

    //���f���f�[�^�̃��[�h
    /*hModel_ = Model::Load("WhiteBall.fbx");
    assert(hModel_ >= 0);*/


    std::string fileName[] = { "WhiteBall.fbx","RedBall.fbx" };
    //���f���f�[�^�̃��[�h
    for (int i = 0; i < 2; i++)
    {
        std::string fn = fileName[i];
        hModel_[i] = Model::Load(fn);
        assert(hModel_[i] >= 0);
    }

    do
    {
        transform_.position_.x = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;
        transform_.position_.z = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;

        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    } while (radius >= CIRCLE_RANGE || radius < NEAR_GOAL);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), BALLSIZE);
    AddCollider(collision);

    trans.position_ = XMFLOAT3(0, 0, 0);
}

//�X�V
void Ball::Update()
{
    PlayStop* pPlayStop = (PlayStop*)FindObject("PlayStop");
    if (pPlayStop->GetIsStop() == false)
    {
        //��ŃL�[��ς�����悤�ɂ���for��

        //������Ƃ��̃{�[���̓���
        if (throwBall == true)
        {
            //�����x�̉��Z
            powerY += GRAVITY;

            // �X�s�[�h�̉��Z

            transform_.rotate_.y = playerRotateY;

            XMFLOAT3 move = { 0,-powerY,powerZ }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);


            /*transform_.position_.z += powerZ[i];
            transform_.position_.y -= powerY[i];*/
            powerZ *= RESISTANCE;//��R

            // �o�E���h�̔���
            if (transform_.position_.y <= 0.0f)
            {  // �{�[�������ɓ���������
                isThrow = false;
                transform_.position_.y = 0.0;
                powerY = -powerY * BOUND;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂蒵�˂Ȃ�����
                height = powerY; //�����ۑ�
                powerZ *= RESISTANCE;//��R

                //�����蔻��I���ɂ���@���Ƃ�
            }

            //�ړ����I���
            if (powerZ <= END_MOVE)
            {
                powerZ = 0;
                powerY = 0;
                throwBall = false;
                isHave = false;
            }
        }

        ////�p���[�n��
        //if (Input::IsPadButtonUp(XINPUT_GAMEPAD_A) && throwBall == false)
        //{
        //    throwBall = true;
        //    /* powerY = -0.5;
        //     powerZ = 0.5;*/
        //}


        for (int i = 0; i < Max; i++)
        {
            if (i == First)
            {
                key = DIK_SPACE;
                assistKey = DIK_F1;
            }
            else if (i == Second)
            {
                key = DIK_RETURN;
                assistKey = DIK_F2;
            }
            else
            {
                key = 0;
            }
        }

        //�f�o�b�O�p
        if (Input::IsKey(DIK_B))
        {
            int a = 0;
        }

        ////�~�͈̔͊O�Ȃ������
        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
        if (radius > CIRCLE_OUTSIDE)
        {
            pGround->SetGroundBall(-1);
            KillMe();
        }

    }
}

//�`��
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

//�J��
void Ball::Release()
{

}

//�����蔻��
void Ball::OnCollision(GameObject* pTarget)
{
    //�S�[���ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Basket" && throwBall)
    {
        ResultText* pResultText = (ResultText*)FindObject("ResultText");
        hModel_[0];
        this->hModel_;

        if (ballID % 2 == 0)
        {
            //�S�[���ɓ������瓾�_
            pResultText->WhiteCount();
            pGround->SetGroundBall(-1);
            
        }
        else
        {
            pResultText->RedCount();
            pGround->SetGroundBall(-1);
        }

        throwBall = false;
        //���S�Ɍ������Ĉړ�
        Basket* pBasket = (Basket*)FindObject("Basket");
        XMFLOAT3 basketPos = pBasket->GetBasketPos();
        XMVECTOR vBasket = XMLoadFloat3(&basketPos);
        XMVECTOR vBall = XMLoadFloat3(&transform_.position_);
        XMVECTOR vCenter = vBasket - vBall;//���S�̌���

        vCenter = XMVector3Normalize(vCenter);
        vCenter *= 0.2;

        XMFLOAT3 centerRotate;
        XMStoreFloat3(&centerRotate, vCenter);
        
        transform_.position_.x += centerRotate.x;
        transform_.position_.y += centerRotate.y;
        transform_.position_.z += centerRotate.z;

        //ClearCollider();
    }
}


void Ball::HandPos(int playerID_, bool rightHand_)
{
    //transform_.position_ = bonePos;
    //a = true;
    //�����Ă邠�����̕ϐ�true
}

void Ball::PlayerBone(XMFLOAT3 bone)
{
    //transform_.position_ = bone;
}

void Ball::SetPower(float powerY_, float powerZ_, float playerRotateY_)
{
    powerY = powerY_;
    powerZ = powerZ_;
    playerRotateY = playerRotateY_;
    throwBall = true;
    isThrow = true;
}

void Ball::SetPlayerModel(int model_, int ballID_)
{
    //�ł��Ȃ�
    /*playerModel = model_;
    transform_.position_ = Model::GetBonePosition(playerModel, "joint1");*/

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


