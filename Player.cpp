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

#define THIRD_VIEW 1 //�O�l�̎��_����l�̎��_ ��l�̂͂킩��Â炢����Ȃ�

//�萔
namespace
{
    static const int CIRCLE_RANGE = 360;//�ۂ͈̔�
    static const int PORY_LENGTH = 42;//�O����ۑ����钷��
    static const int NOT_HAVE = -1;//�{�[���������Ă��Ȃ�
    static const int DROP_TIME = 120;//�ʂ𓖂Ă�ꂽ�Ƃ��ɏE���Ȃ�����
    static const int CIRCLE_RADIUS = 21;//�S�[������[�܂ł̒���
    static const int COM_ROTATE = 137;//�R���s���[�^�[���[�܂ōs�������̉�]��
    static const int RANDOM_VALUE = 3000;//�{�[���𓊂��郉���_���l
    static const int SOUND_COUNT = 3;//�����ɖ点���
    static const int COLOR_MAX = 2;//�G�t�F�N�g�F�̍ő�l

    static const float ROTATE_SPEED = 1.5f;//��]�̑���
    static const float DECIMAL_CHANGE = 1000.0f;//�����ɂ���
    static const float THROW_POWER_Y = 0.5f;
    static const float POWER_ADJUSTMENT = 0.22f;
    static const float PLAYER_INTERVAL = 3.0f;//�����v���C���[�Ԋu
    static const float GOAL_ROTATE = 180.0f;//����������ɉ�]����
    static const float POWER = 0.01;//�P�t���[�����Ƃɂ��߂��
    static const float GRADATION_VALUE = 0.02f;//�G�t�F�N�g�̃O���f�[�V�����ω���
    static const float NOTTHROW_RANGE = 50.0f;//�������Ȃ��͈�
    static const float HIT_SIZE = 1.7f;//�����蔻��
    static const float PLAYER_MOVE = 0.1f;//�ړ�����
    static const float GRAVITY = 0.05f;//�d��
    static const float RESISTANCE = 0.97f;//��R
    static const float SOUND_VOLUME = 0.8f;//����
    static const float ROTATE_X = 1;//��]��
    static const float MOVE_DISTANCE = 1;//�ړ���
    static const float AUTOMATIC_ROTAT = 10;//������]��

    static const float COLLISION_POS = -0.2f;//�����蔻��̏ꏊ
    static const XMFLOAT3 START_POS = XMFLOAT3(0, 1.5f, -6);//�v���C���[�ʒu
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),
    hModel_(-1),  pLine(nullptr), pText(nullptr), hSound_Throw(-1),
    isAssist(true)
{

}

//�f�X�g���N�^
Player::~Player()
{

}

//������
void Player::Initialize()
{
    //�T�E���h�f�[�^�̃��[�h
    hSound_Throw = Audio::Load("Throw.wav", false, SOUND_VOLUME, SOUND_COUNT);
    assert(hSound_Throw >= 0);

    transform_.position_ = START_POS;

    //�����蔻��
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
    viewY = 8.0f; //Y���W
    cameraZ = 15.0f;
#else
    viewY = 3.0f; //Y���W
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
    LeftStick = XMFLOAT3(0, 0, 0);
    RightStick = XMFLOAT3(0, 0, 0);

    pText = new Text;
    pText->Initialize();
    pParticle_ = Instantiate<Particle>(this);

    hModel_ = Model::Load("WhitePlayer.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Player::Update()
{
    //�ŏ��̈�񂾂���肽������
    FirstSet();

    //�Q�[�����i�s���Ȃ�
    if (!(pResultText->GetIsEnd() || pPlayStop->GetIsStop()))
    {
        //AI�Ȃ�
        if (playerID >= ScreenSplit::GetPlayerPerson())
        {
            //�X�e�[�g�x�[�XAI
            switch (nowState)
            {
            case WALK_STATE://�{�[�����E���܂ŕ���
                WalkMotion();
                break;
            case CHARGE_STATE://�����鋭�������߂�
                ChargeMotion();
                break;
            case THROW_STATE://�{�[��������
                ThrowMotion();
                break;
            default:
                nowState = WALK_STATE;
                break;
            }
        }

        //�E��{�[�������Ă���
        if (pBallRight != nullptr)
        {
            //�E��Ƀ{�[������
            pBallRight->SetBallPos(Model::GetBonePosition(hModel_, "joint1"));

        }//����{�[�������Ă���
        if (pBallLeft != nullptr)
        {
            //����Ƀ{�[������
            pBallLeft->SetBallPos(Model::GetBonePosition(hModel_, "joint2"));
        }

        //����ꏊ�A���
        moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);

        //�͈͊O��
        if (moveLimit > CIRCLE_RANGE)
        {
            transform_.position_.x = prevPos.position_.x;
            transform_.position_.z = prevPos.position_.z;
        }

        //������ꏊ
        prevPos = transform_;

        //�Ȃ���p���[���߂�
        if (IsPowerPush())
        {
            ChargePower();
        }
        //������
        if (IsThrowPull())
        {
            Throw();
        }

        //�R���g���[���[����
        LeftStick = Input::GetPadStickL(playerID);
        RightStick = Input::GetPadStickR(playerID);

        //�L�[�{�[�h����
        KeyboardOperation();
        
        //������]
        transform_.rotate_.y += LeftStick.x / 2;
        LeftStick.x /= AUTOMATIC_ROTAT;
        LeftStick.y /= AUTOMATIC_ROTAT;

        //�ړ�
        transform_ = FrontDirection(LeftStick.x, 0, LeftStick.y, transform_.rotate_.y, transform_);

#if THIRD_VIEW

        RightStick.x *= ROTATE_SPEED;
#else 

        RightStick.x /= 300;
#endif
        transform_.rotate_.y += RightStick.x;
        
        //�E���Ȃ���
        if (isDrop)
        {
            //�_�ł���
            Damage();
        }

    //�J����
#if THIRD_VIEW
            //
#else 
            XMVECTOR vCam = XMVectorSet(0.0f, viewY, cameraZ, 0.0f);
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

            vCam = XMVector3TransformCoord(vCam, mRotate);
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
            XMFLOAT3 camPos;
            XMStoreFloat3(&camPos, vPos + vCam);//�J�����̍��W

            XMFLOAT3 cameraPos = transform_.position_;
            cameraPos.y += 3;
            Camera::SetPosition(cameraPos);

            Camera::SetTarget(camPos);
#endif

        //�f�o�b�O�p
#ifdef _DEBUG
            Debug();
#endif
    }
}

//�`��
void Player::Draw()   
{
    Direct3D::SetShader(Direct3D::SHADER_TOON);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //�A�V�X�g�Ȃ��Ȃ珈���I���
    if (isAssist == false)
        return;

    //�|�����C����`��
    if (isChargePower)
       pLine->Draw();

}

//�J��
void Player::Release()
{
    //�|�����C�����
    pLine->Release();
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    //�{�[���ɂ����違�ǂ̃v���C���[�����{�[�������ĂȂ���
    if (pTarget->GetObjectName() == "Ball" && isDrop == false)
    {
        //�����Ă�{�[���������Ă�{�[�����]�����Ă�{�[����
        //���{�[���̏�Ԏ擾���Ĕ���
        pBallThrow = (Ball*)pTarget;
        //�����Ă�{�[����������
        if (pBallThrow->GetIsThrow())
        {
            Attacked();
        } //�����Ă�{�[��
        else if (pBallThrow->GetIsHave())
        {
            //�������Ȃ�
        }//�E�肪�����Ă�
        else if (rightHand < 0)
        {
            //�E��Ƀ{�[������
            pBallRight = (Ball*)pTarget;
            pBallThrow->SetIsHave(true);
            //���������{�[���̔ԍ�
            rightHand = pBallRight->GetBallNum();
        }//���肪�����Ă�
        else if (leftHand < 0)
        {
            //����Ƀ{�[������
            pBallLeft = (Ball*)pTarget;
            pBallThrow->SetIsHave(true);
            //���������{�[���̔ԍ�
            leftHand = pBallLeft->GetBallNum();
        }
    }
}

//�p�x�擾
float Player::GetAngle()
{
    return 0;
}

//�U�����ꂽ���Z�b�g
void Player::SetDamage(bool damage_)
{
    isDamage = damage_;
}

//�U�����ꂽ���擾
bool Player::GetDamage()
{
    return isDamage;
}

//�v���C���[�̏ꏊ�擾
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

//�v���C���[�J����
Transform Player::FrontDirection(float x_, float y_, float z_, float direction_, Transform trans_)
{
    move = { x_,y_,z_ }; //�ړ���
    vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
    mRotate = XMMatrixRotationY(XMConvertToRadians(direction_));   //Y���ł�����]������s��

    vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
    vPos = XMLoadFloat3(&trans_.position_); //���ݒn���x�N�g���ɕϊ�

    vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

    XMStoreFloat3(&trans_.position_, vPos);

    //�J����
    vCam = XMVectorSet(0.0f, viewY, -cameraZ, 0.0f);
    mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    vCam = XMVector3TransformCoord(vCam, mRotate);
    //vPos = XMLoadFloat3(&transform_.position_);
    XMStoreFloat3(&camPos, vPos + vCam);//�J�����̍��W
    return trans_;
}

//�J�����̏ꏊ�擾
XMFLOAT3 Player::GetCameraPos()
{
    return XMFLOAT3(camPos.x, camPos.y - 3, camPos.z);
}

//�J�����̃^�[�Q�b�g�擾
XMFLOAT3 Player::GetCameraTarget()
{
    return XMFLOAT3(transform_.position_.x, transform_.position_.y + 3, transform_.position_.z);;
}

//�v���C���[�̏�Ԏ擾
string Player::GetStateText()
{
    return stateText;
}

//�A�V�X�g�Z�b�g
void Player::SetIsAssist(bool assist_)
{
    isAssist = assist_;
}

//�A�V�X�g�擾
bool Player::GetIsAssist()
{
    return isAssist;
}

//�_���[�W��
void Player::Damage()
{
    if (dropTime <= DROP_TIME)
    {
        //�U�����ꂽ����
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

//�U�����ꂽ
void Player::Attacked()
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
    //�l��߂�
    nowState = WALK_STATE;
    isChargePower = false;
    powerY = 0;
    powerZ = 0;
    //�����鋭���̐F��߂��Ă���
    effectCollar = 0;
}

//�����鋭���̃G�t�F�N�g�F
void Player::EffectGradationColor()
{
    //�����鋭���\���G�t�F�N�g
    EmitterData data;
    data.textureFileName = "Cloud.png";
    data.position = Model::GetBonePosition(hModel_, "joint1");//�\���ʒu�͎�
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

    //�G�t�F�N�g�O���f�[�V����
    if (effectCollar < 1)
        data.color = XMFLOAT4(0, effectCollar, 1 - effectCollar, 1);
    else if (effectCollar < 2)
        data.color = XMFLOAT4(effectCollar - 1, 2 - effectCollar, 0, 1);
    else
        data.color = XMFLOAT4(1, 0, 0, 1);

    pParticle_->Start(data);
}

//����
void Player::WalkMotion()
{
    //��ԕ\���p�A�f�o�b�O�̂�
    stateText = "Walk";

    if (moveLimit > CIRCLE_RANGE)
        transform_.rotate_.y += COM_ROTATE;
    //�ړ�
    transform_ = FrontDirection(0, 0, PLAYER_MOVE, transform_.rotate_.y, transform_);

    //�{�[����2�����Ă�&�S�[�������苗������Ă��邩
    if (pBallLeft != nullptr && moveLimit > NOTTHROW_RANGE)
    {
        //�{�[���̓����鋭�������߂��Ԃ�
        nowState = CHARGE_STATE;
    }
}

//�p���[���߂�
void Player::ChargeMotion()
{
    //��ԕ\���p�A�f�o�b�O�݂̂ɂ���
    stateText = "Charge";

    //�{�[���������Ă�
    if (pBallRight != nullptr)
    {
        EffectGradationColor();

        //�O���f�[�V�����p
        effectCollar += GRADATION_VALUE;

        //�S�[��������
        XMFLOAT3 origine = XMFLOAT3(0, 0, 0);
        XMVECTOR vOrigin = XMLoadFloat3(&origine);
        XMFLOAT3 HandPos = Model::GetBonePosition(hModel_, "joint1");
        XMVECTOR vPlayerPos = XMLoadFloat3(&HandPos);
        XMVECTOR vGoal = vOrigin - vPlayerPos; //�S�[���ւ̌���

        //�S�[���܂ł̒���
        XMVECTOR vGoalLength = XMVector3Length(vGoal);
        goalLength = XMVectorGetX(vGoalLength);
        //�S�[���̕���
        XMFLOAT3 goalRotate;
        XMStoreFloat3(&goalRotate, vGoal);
        //�����Ă�{�[���������̂�
        if (playerID % 2 == pBallRight->ballID % 2)
        {
            //�S�[������
            transform_.rotate_.y = (float)(atan2(goalRotate.x, goalRotate.z) * GOAL_ROTATE / M_PI);
        }
        else
        {
            //�S�[���Ɣ��΂�����
            goalLength = CIRCLE_RADIUS - goalLength;
            transform_.rotate_.y = (float)(atan2(-goalRotate.x, -goalRotate.z) * GOAL_ROTATE / M_PI);
        }

        //�͂��߂�
        powerY -= POWER;
        powerZ += POWER;

        //�����邩                                           
        if (powerZ > powf(goalLength - ((rand() % RANDOM_VALUE) / DECIMAL_CHANGE), THROW_POWER_Y) * POWER_ADJUSTMENT)
        {
            nowState = THROW_STATE;//�{�[���𓊂����Ԃ�
        }
    }
    else
        nowState = WALK_STATE;
}

//������
void Player::ThrowMotion()
{
    //�����鋭���̐F��߂��Ă���
    effectCollar = 0;
    //��ԕ\���p�A�f�o�b�O�݂̂ɂ���(��)
    stateText = "Throw";


    pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
    isChargePower = false;//�������H
    powerY = 0;
    powerZ = 0;
    rightHand = leftHand;
    leftHand = NOT_HAVE;
    pBallRight = pBallLeft;
    pBallLeft = nullptr;//�����܂ŁH
    //���Ƃ�AI���ǂ������� 
    //�{�[�������ĂȂ�������
    if (pBallRight == nullptr)
    {
        //�{�[���T��
        nowState = WALK_STATE;
    }
    else//�����Ă���
    {
        //������
        nowState = CHARGE_STATE;
    }
}

//������{�^���������Ă邩
bool Player::IsPowerPush()
{
    if (((Input::IsKey(DIK_SPACE) && playerID == 0) || //�L�[�{�[�h����
        (Input::IsPadButton(XINPUT_GAMEPAD_A, playerID) ||
            Input::IsPadButton(XINPUT_GAMEPAD_B, playerID) ||
            Input::IsPadButton(XINPUT_GAMEPAD_X, playerID) ||
            Input::IsPadButton(XINPUT_GAMEPAD_Y, playerID))) &&
        rightHand >= 0)
        return true;
    else
        return false;
}

//������{�^���𗣂�����
bool Player::IsThrowPull()
{
    if (((Input::IsKeyUp(DIK_SPACE) && playerID == 0) ||  //�L�[�{�[�h����
        (Input::IsPadButtonUp(XINPUT_GAMEPAD_A, playerID) || Input::IsPadButtonUp(XINPUT_GAMEPAD_B, playerID) || Input::IsPadButtonUp(XINPUT_GAMEPAD_X, playerID) || Input::IsPadButtonUp(XINPUT_GAMEPAD_Y, playerID))) &&
        rightHand >= 0)
        return true;
    else
        return false;
}

//�{�[���̋O���\��
void Player::AssistTrajectory()
{
    trajectoryY = powerY;
    trajectoryZ = powerZ;
    //�E��̈ʒu �\���̂��
    poryTrans.position_ = Model::GetBonePosition(hModel_, "joint1");

    for (int i = 0; i < PORY_LENGTH; i++)
    {
        if (i % 3 == 0)
            pLine->AddPosition(poryTrans.position_);

        // �����x�̉��Z
        trajectoryY += GRAVITY;

        poryTrans.rotate_ = transform_.rotate_;
        poryTrans = FrontDirection(0, -trajectoryY, trajectoryZ, transform_.rotate_.y, poryTrans);

        trajectoryZ *= RESISTANCE;//��R
    }
    isChargePower = true;
}

void Player::FirstSet()
{
    if (IsFirst)
    {
        pResultText = (ResultText*)FindObject("ResultText");
        pPlayStop = (PlayStop*)FindObject("PlayStop");
        if (playerID % 2 == 0)
        {
            //���`�[��
            hModel_ = Model::Load("WhitePlayerD0.fbx");
            hModel_ = Model::Load("WhitePlayer.fbx");
            assert(hModel_ >= 0);
            Model::SetShederType(hModel_, Direct3D::SHADER_TOON);
            transform_.position_.x = playerID * -PLAYER_INTERVAL - PLAYER_INTERVAL;
        }
        else
        {
            //�ԃ`�[��
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

        vCam = XMVectorSet(0.0f, viewY, -cameraZ, 0.0f);
        mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

        vCam = XMVector3TransformCoord(vCam, mRotate);
        vPos = XMLoadFloat3(&transform_.position_);
        XMStoreFloat3(&camPos, vPos + vCam);//�J�����̍��W

        IsFirst = false;
    }
}

//�͂����߂�
void Player::ChargePower()
{
    //�p���[���ő傶��Ȃ�������
    if (effectCollar < COLOR_MAX)
    {
        //�͂��߂�
        powerY -= POWER;
        powerZ += POWER;
        //�O���f�[�V�����p
        effectCollar += GRADATION_VALUE;
    }

    //�G�t�F�N�g�\��
    EffectGradationColor();

    //�A�V�X�g����Ȃ�
    if (isAssist)
    {
        //�{�[���̋O���\��
        AssistTrajectory();
    }
}

//������
void Player::Throw()
{
    //������
    pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
    //���߂Ă��͂����ɖ߂�
    effectCollar = 0;
    powerY = 0;
    powerZ = 0;
    isChargePower = false;
    //�{�[���������ς���
    rightHand = leftHand;
    leftHand = NOT_HAVE;
    pBallRight = pBallLeft;
    pBallLeft = nullptr;
}

//�L�[�{�[�h�ړ�����
void Player::KeyboardOperation()
{
    if (playerID == 0)
    {
        //�ړ�
        if (Input::IsKey(DIK_W))
            LeftStick.y = MOVE_DISTANCE;
        if (Input::IsKey(DIK_A))
            LeftStick.x = -MOVE_DISTANCE;
        if (Input::IsKey(DIK_S))
            LeftStick.y = -MOVE_DISTANCE;
        if (Input::IsKey(DIK_D))
            LeftStick.x = MOVE_DISTANCE;

        //��]
        if (Input::IsKey(DIK_LEFT))
            RightStick.x = -ROTATE_X;
        if (Input::IsKey(DIK_RIGHT))
            RightStick.x = ROTATE_X;
    }
}

//�f�o�b�O���̂ݍs������
void Player::Debug()
{
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
    }
    //�U������
    if (Input::IsPadButton(XINPUT_GAMEPAD_X))
    {
        Input::SetPadVibration(50, 50, playerID);//��
    }
}
