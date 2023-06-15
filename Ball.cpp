#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "ResultText.h"
#include "PlayScene.h"
#include "PlayStop.h"

//�萔
namespace
{
    static const int DIAMETER = 3800;//�n�ʂɃ����_���Ƀ{�[���z�u
    static const int HALF = 2;
    static const int CHANGE_DECIMAL = 100;//�����ɕω�
    static const int CIRCLE_RANGE = 360;//�n�ʔ͈�
    static const int NEAR_GOAL = 15;//�S�[���̋߂�
    static const int CIRCLE_OUTSIDE = 450;//�{�[���̐����͈�
    static const float BALL_SIZE = 1.3f;//�{�[���̑傫��
    static const float BALL_COL_SIZE = 0.23f;//�{�[���̓����蔻��
    static const float GRAVITY = 0.05f;//�d��
    static const float RESISTANCE = 0.97f;//��R
    static const float BOUND = 0.6f;//�o�E���h�̑傫��
    static const float END_MOVE = 0.001f;//�{�[�����~�܂�l
    static const float CENTER_MOVE = 0.5f;//�S�[�������������Ɋ��l�A�傫���قǒ����ɍs��
}

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
    radiusPower = 0;
    powerZ = 0;
    powerY = 0;
    isThrowBall = false;
    isThrow = false;

    std::string fileName[] = { "WhiteBall.fbx","RedBall.fbx" };
    //���f���f�[�^�̃��[�h
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

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), BALL_COL_SIZE);
    AddCollider(collision);
}

//�X�V
void Ball::Update()
{
    PlayStop* pPlayStop = (PlayStop*)FindObject("PlayStop");
    if (pPlayStop->GetIsStop() == false)
    {
        //��ŃL�[��ς�����悤�ɂ���for��

        //������Ƃ��̃{�[���̓���
        if (isThrowBall == true)
        {
            //�����x�̉��Z
            powerY += GRAVITY;

            // �X�s�[�h�̉��Z
            XMFLOAT3 move = { 0,-powerY,powerZ }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);

            powerZ *= RESISTANCE;//��R

            // �o�E���h�̔���
            if (transform_.position_.y <= 0.0f)
            {  // �{�[�������ɓ���������
                isThrow = false;
                transform_.position_.y = 0.0;
                powerY = -powerY * BOUND;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂�
                powerZ *= RESISTANCE;//��R

                //�����蔻��I���ɂ���@���Ƃ�
            }

            //�ړ����I���
            if (powerZ <= END_MOVE)
            {
                powerZ = 0;
                powerY = 0;
                isThrowBall = false;
                isHave = false;
            }
        }
        //�f�o�b�O�p
        if (Input::IsKey(DIK_B))
        {
            int a = 0;
        }

        ////�~�͈̔͊O�Ȃ������
        radiusPower = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
        if (radiusPower > CIRCLE_OUTSIDE)
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
    if (pTarget->GetObjectName() == "Basket" && isThrowBall)
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

        isThrowBall = false;

        //���S�̌v�Z
        Basket* pBasket = (Basket*)FindObject("Basket");
        XMFLOAT3 basketPos = pBasket->GetBasketPos();
        XMVECTOR vBasket = XMLoadFloat3(&basketPos);
        XMVECTOR vBall = XMLoadFloat3(&transform_.position_);
        XMVECTOR vCenter = vBasket - vBall;//���S�̌���
        vCenter = XMVector3Normalize(vCenter);
        vCenter *= CENTER_MOVE;
        XMFLOAT3 centerRotate;
        XMStoreFloat3(&centerRotate, vCenter);
        //���S�����Ɉړ�
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


