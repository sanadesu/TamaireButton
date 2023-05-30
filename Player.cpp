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

#define THIRD_VIEW 1 //�O�l�̎��_����l�̎��_ ��l�̂͂킩��Â炢����Ȃ�

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),
    hModel_(-1),  pLine(nullptr), pText(nullptr), hSound_Charge(-1), hSound_Throw(-1),
    IsAssist(true)
{

}

//�f�X�g���N�^
Player::~Player()
{
   // SAFE_DELETE(pLine);
}

//������
void Player::Initialize()
{
    //�T�E���h�f�[�^�̃��[�h
    hSound_Charge = Audio::Load("Star.wav", false, 0.8f, 1);//���Ƃ�
    assert(hSound_Charge >= 0);
    hSound_Throw = Audio::Load("Throw.wav", false, 0.8f, 1);
    assert(hSound_Throw >= 0);

    transform_.position_ = XMFLOAT3(START_POS_X, 1.5f, START_POS_Z);
    //transform_.position_.x = (float)(rand() % 180 / 10);

    //�����蔻��
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
    viewY = 8.0f; //Y���W
    cameraZ = 15.0f;
#else
    viewY = 3.0f; //Y���W
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

//�X�V
void Player::Update()
{
    
    //bool a = pPlayStop->GetIsStop();
    //�����邩�ǂ���
    
        //�ŏ��̈�񂾂���肽������
    if (IsFirst)
    {
        pPlayStop = (PlayStop*)FindObject("PlayStop");
        pResultText = (ResultText*)FindObject("ResultText");
        if (playerID % 2 == 0)
        {
            //���`�[��
            hModel_ = Model::Load("WhitePlayer.fbx");
            assert(hModel_ >= 0);
            transform_.position_.x = playerID * -3 - 3;
        }
        else
        {
            //�ԃ`�[��
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

    ////��������
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


        //�v���C���[���F�I���ł���悤�Ɍ�ŕς���
        //              �v���C�l��
        if (playerID >= ScreenSplit::GetPlayerPerson())
        {
            //�X�e�[�g�x�[�XAI
            sManager.Action();//���̏�Ԃ̃A�N�V����
            sManager.NextState();//��ԑJ��

            //�X�e�[�g�x�[�XAI
            switch (nowState)
            {
            case WALK_STATE://�{�[�����E���܂ŕ���
            {
                //�����鋭���̐F��߂��Ă���
                effectCollar = 0;
                //��ԕ\���p�A�f�o�b�O�̂�
                stateText = "Walk";

                //�����]���A��ł����ƃ{�[����T���Ō�������(��)
                if (moveLimit > CIRCLE_RANGE)
                    transform_.rotate_.y += 137;
                //�ړ�
                transform_ = FrontDirection(0, 0, PLAYER_MOVE, transform_.rotate_.y, transform_);
                
                //�{�[����2�����Ă�&�S�[�������苗������Ă��邩
                if (pBallLeft != nullptr && moveLimit > 50)
                {
                    //�{�[���̓����鋭�������߂��Ԃ�
                    nowState = CHARGE_STATE;
                }
                break;
            }
            case CHARGE_STATE://�����鋭�������߂�
                //��ԕ\���p�A�f�o�b�O�݂̂ɂ���(��)
                stateText = "Charge";

                //�{�[���������Ă�
                if (pBallRight != nullptr)
                {
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
                        
                        //�O���f�[�V�����p
                        effectCollar += 0.02f;
                    }

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
                        transform_.rotate_.y = (float)(atan2(goalRotate.x, goalRotate.z) * 180.0 / M_PI);
                    }
                    else
                    {
                        //�S�[���Ɣ��΂�����
                        goalLength = 21 - goalLength;
                        transform_.rotate_.y = (float)(atan2(-goalRotate.x, -goalRotate.z) * 180.0 / M_PI);
                    }
                    //�͂��߂�
                    powerY -= POWER;
                    powerZ += POWER;


                    ////�A�V�X�g�@�\�I���Ȃ�(��)
                    //if (IsAssist)
                    //{
                    //    //�{�[���̋O��
                    //    trajectoryY = powerY;
                    //    trajectoryZ = powerZ;
                    //    //�E��̈ʒu
                    //    trans.position_ = Model::GetBonePosition(hModel_, "joint1");

                    //    for (int j = 0; j < PORY_LENGTH; j++)
                    //    {
                    //        //3�t���[�������̏ꏊ������
                    //        if (j % 3 == 0)
                    //        {
                    //            pLine->AddPosition(trans.position_);
                    //            //pLineW->AddPositionW(trans.position_);
                    //            //pLineX->AddPositionX(trans.position_);
                    //        }

                    //        // �����x�̉��Z
                    //        trajectoryY += GRAVITY;
                    //        trans.rotate_ = transform_.rotate_;
                    //        trans = FrontDirection(0, -trajectoryY, trajectoryZ, transform_.rotate_.y, trans);
                    //        trajectoryZ *= RESISTANCE;//��R

                    //    }
                    //    //�O����\������
                    //    chargePower = true;

                    //}
                    
                    //�����邩
                    //���Ƃ�AI���ǂ�������                                                
                    if (powerZ > powf(goalLength - ((rand() % 3000) / 1000.0f), 0.5f) * 0.22f )
                    {
                        //if(effectCollar > 2)//�G�t�F�N�g�����p
                        nowState = THROW_STATE;//�{�[���𓊂����Ԃ�
                    }
                }
                break;
            case THROW_STATE://�{�[��������
                //�����鋭���̐F��߂��Ă���
                effectCollar = 0;
                //��ԕ\���p�A�f�o�b�O�݂̂ɂ���(��)
                stateText = "Throw";


                pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
                chargePower = false;//�������H
                powerY = 0;
                powerZ = 0;
                rightHand = leftHand;
                leftHand = -1;
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
            //trans.position_ = Model::GetBonePosition(hModel_, "joint1");
            //pBallRight->PlayerBone(Model::GetBonePosition(hModel_, "joint1"));

        }//����{�[�������Ă���
        if (pBallLeft != nullptr)
        {
            //����Ƀ{�[������
            pBallLeft->SetBallPos(Model::GetBonePosition(hModel_, "joint2"));
            //pBallLeft->PlayerBone(Model::GetBonePosition(hModel_, "joint2"));
        }

        //����ꏊ�A���
        moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);

        if (moveLimit > CIRCLE_RANGE)
        {
            //��ŕς���
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
        //�Ȃ���
        if (((Input::IsKey(DIK_SPACE) && playerID == 0) || //�L�[�{�[�h����
            (Input::IsPadButton(XINPUT_GAMEPAD_A, playerID) || 
             Input::IsPadButton(XINPUT_GAMEPAD_B, playerID) || 
             Input::IsPadButton(XINPUT_GAMEPAD_X, playerID) || 
             Input::IsPadButton(XINPUT_GAMEPAD_Y, playerID))) &&
            rightHand >= 0)
        {
            if (effectCollar < 2)
            {
                //�͂��߂���
                powerY -= POWER;
                powerZ += POWER;
                //�O���f�[�V�����p
                effectCollar += 0.02f;
            }
            

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
                //�E��̈ʒu �\���̂��
                trans.position_ = Model::GetBonePosition(hModel_, "joint1");

                for (int i = 0; i < PORY_LENGTH; i++)
                {
                    if (i % 3 == 0)
                    {
                        pLine->AddPosition(trans.position_);
                        //pLineW->AddPositionW(trans.position_);
                        //pLineX->AddPositionX(trans.position_);
                    }
                    // �����x�̉��Z
                    trajectoryY += GRAVITY;

                    trans.rotate_ = transform_.rotate_;
                    trans = FrontDirection(0, -trajectoryY, trajectoryZ, transform_.rotate_.y, trans);

                    trajectoryZ *= RESISTANCE;//��R
                }
                chargePower = true;
            }
        }
        if ((((Input::IsKeyUp(DIK_SPACE) && playerID == 0) ||  //�L�[�{�[�h����
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

        //�ړ�
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
        //������]
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
        //viewY += RightStick.y;//�㉺��]
        // 
        //hdri
        //�|���w�u��

        if (IsDrop)
        {
            if (dropTime <= DROP_TIME)
            {
                //�U�����ꂽ����
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

        //�J����
        //if (playerID == 0)
        {
#if THIRD_VIEW
            //XMVECTOR vCam = XMVectorSet(0.0f, viewY, -cameraZ, 0.0f);
            //XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

            //vCam = XMVector3TransformCoord(vCam, mRotate);
            //XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
            //XMFLOAT3 camPos;
            //XMStoreFloat3(&camPos, vPos + vCam);//�J�����̍��W

            //Camera::SetPosition(XMFLOAT3(camPos.x, camPos.y-3, camPos.z ));
            //Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y+5, transform_.position_.z));
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
        }

        //�f�o�b�O�p
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
        }//�U������
        if (Input::IsPadButton(XINPUT_GAMEPAD_X))
        {
            Input::SetPadVibration(50, 50, playerID);//��
        }
#endif
    }
}

//�`��
void Player::Draw()   
{                     
    XMVECTOR vCam = XMVectorSet(0.0f, viewY, -cameraZ, 0.0f);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMStoreFloat3(&camPos, vPos + vCam);//�J�����̍��W

    //�ϐ���pos��target����郁�C���Ŏg��
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
        //�|�����C����`��
       pLine->Draw();
        //pLineW->Draw();
        //pLineX->Draw();
    }

}

//�J��
void Player::Release()
{
    //�|�����C�����
    pLine->Release();
    //pLineW->Release();
    //pLineX->Release();
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    //�{�[���ɂ����違�ǂ̃v���C���[�����{�[�������ĂȂ���
    if (pTarget->GetObjectName() == "Ball" && IsDrop == false)
    {
        //�����Ă�{�[���������Ă�{�[�����]�����Ă�{�[����
        //���{�[���̏�Ԏ擾���Ĕ���
        pBallThrow = (Ball*)pTarget;
        //�����Ă�{�[����������
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
            //�U����������
            //Input::SetPadVibration(50, 50, playerID);


            //�����ɂ�����
            
            //�l��߂�
            nowState = WALK_STATE;
            chargePower = false;
            powerY = 0;
            powerZ = 0;
        } //�����Ă�{�[��
        else if (pBallThrow->GetIsHave())
        {
            //
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

        //�����Ă�{�[��
        //�����Ă�{�[��������
        //��莞�ԏE���Ȃ�
        //�_��
    }
}

//�p�x�擾
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
    XMFLOAT3 move = { x_,y_,z_ }; //�ړ���
    XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(direction_));   //Y���ł�����]������s��

    vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
    XMVECTOR vPos = XMLoadFloat3(&trans_.position_); //���ݒn���x�N�g���ɕϊ�

    vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

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

