#include "TitlePlayer.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"
#include "Engine/Easing.h"
#include "TitleScene.h"
#include "TitleButton.h"

//�萔
namespace
{
    static const int POS_X = -15;
    static const int MOVE_RANGE = 50;
    static const int BOUND_WIDTH = 15;//�o�ꂷ�鎞�̉���
    static const int PLAYER_POS_Y = -2;//�v���C���[�̍���
    static const int RED_ANGLE = 170;//�ԃL�����̊p�x
    static const int WHITE_ANGLE = 190;//���L�����̊p�x
    static const int WHITE_START = 30;//�ԃL��������x��ēo�ꂷ��t���[����
    static const int SWING_WIDTH = 30;//�h��镝
    static const float PLAYER_SIZE = 2.0f;//�v���C���[�̑傫��
    static const float SWING_ROTATE = 0.01f;//���E�ɎC��鎞��1�t���[���ɉ�]����l
    static const float SWING_POS = 0.05f;//���E�ɗh���Ƃ���1�t���[���ɓ����l
    static const float BOUND_EASE_START = 0.5f;//�C�[�W���O���ǂ�����n�߂邩
    static const float PLAYER_ROTATE = 3.6f;//�o�Ă���Ƃ���1�t���[���̉�]��
    static const float BOUND_DOWN = 0.01f;//�C�[�W���O�̕ω���
    static const float SWING_SLOPE = 60.0f;//�����̌X���
    static const float SWING_MOVE = 5.0f;//�����̍��E�ړ��
    static const float SWING_POS_RED = 17.5f;//�����̍��E�ړ��
    static const float SWING_POS_WHITE = 12.5f;//�����̍��E�ړ��
}
//�R���X�g���N�^
TitlePlayer::TitlePlayer(GameObject* parent)
    :GameObject(parent, "TitlePlayer"), hModel_(-1)
{

}

//�f�X�g���N�^
TitlePlayer::~TitlePlayer()
{
}

//������
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
    hModel_ = Model::Load("RedPlayer.fbx");
    assert(hModel_ >= 0);
    transform_.position_.z += 30;
    transform_.scale_.x *= PLAYER_SIZE;
    transform_.scale_.y *= PLAYER_SIZE;
    transform_.scale_.z *= PLAYER_SIZE;
}

//�X�V
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
        //��
        hModel_ = Model::Load("WhitePlayer.fbx");
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

            //����炳����
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

        //�h��𔽑Ε����ɂ���
        if (abs(transform_.rotate_.z) >= SWING_WIDTH)
        {
            rotateZ *= -1;
            posX *= -1;
        }
    }
}

//�`��
void TitlePlayer::Draw()
{
    TitleButton* pTitleButton = (TitleButton*)FindObject("TitleRuleButton");
    if (pTitleButton->GetTitleState() == 0)
    {
        TitleScene* pTitle = (TitleScene*)FindObject("TitleScene");
        Direct3D::SetShader(Direct3D::SHADER_TOON);//��
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

//�J��
void TitlePlayer::Release()
{
}