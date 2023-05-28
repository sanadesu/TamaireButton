#include "UI.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/ScreenSplit.h"
#include "Player.h"
#include "Engine/ScreenSplit.h"

//�R���X�g���N�^
UI::UI(GameObject* parent)
    :GameObject(parent, "UI"),
    hPict_{ -1,-1,-1 },
    pText(nullptr)
{
}

//�f�X�g���N�^
UI::~UI()
{
}

//������
void UI::Initialize()
{
    //�摜�t�@�C�����[�h
    {
        //�g�p����摜�t�@�C����
        const char* fileName[] = { "Frame.png", "WhiteBar.png", "RedBar.png" };

        //���[�h
        for (int i = 0; i < PICT_MAX; i++)
        {
            hPict_[i] = Image::Load(fileName[i]);
            assert(hPict_[i] >= 0);
        }
    }

    nowBar = 50;      
    maxBar = 100;  
    //stopRatio = ((float)redSum + 1) / ((float)whiteSum + 1);
    moveRatio = stopRatio;

    pText = new Text;
    pText->Initialize();

    
    IsEnd = false;

    transBarWhite = transform_;
    transBarWhite.position_.y = 0.8f;
    transBarRed = transBarWhite;
    transBarRed.position_.x = BAR_X;
}

//�X�V
void UI::Update()
{
   // //�ő�HP�ɑ΂���A����HP�̊���
   // stopRatio = ((float)redSum + 1.0f ) / ((float)whiteSum + 1 + redSum + 1.0f) + 0.5;
   ///* if (stopRatio > 1.25f)
   // {
   //     stopRatio = 1.25f;
   // }
   // else if (stopRatio < 0.75f)
   // {
   //     stopRatio = 0.75f;
   // }*/

   // //�o�[�𓮂���
   // if (moveRatio < stopRatio) 
   //     moveRatio += SPEED;
   // else if (moveRatio > stopRatio) 
   //     moveRatio -= SPEED;

   // //HP�ω��Ȃ�
   // if (abs(moveRatio - stopRatio) < SPEED)
   // {
   //     //�΃Q�[�W
   //     transBarRed = transBarWhite;
   //     transBarRed.scale_.x *= stopRatio;
   //     transBarRed.position_.x = BAR_X;

   // }
   // //�񕜒�
   // else if (moveRatio < stopRatio)
   // {
   //     ////���΃Q�[�W
   //     //gaugeTrans = transform_;
   //     //gaugeTrans.scale_.x *= stopRatio_;
   //     //Image::SetTransform(hPict_[PICT_RED], gaugeTrans);
   //     //Image::Draw(hPict_[PICT_RED]);

   //     //�΃Q�[�W
   //     transBarRed = transBarWhite;
   //     transBarRed.scale_.x *= moveRatio;
   //     transBarRed.position_.x = BAR_X;
   // }

   // //�_���[�W��
   // else
   // {
   //     //�ԃQ�[�W
   //     transBarRed = transBarWhite;
   //     transBarRed.scale_.x *= moveRatio;
   //     transBarRed.position_.x = BAR_X;

   //     ////�΃Q�[�W
   //     //gaugeTrans = transform_;
   //     //gaugeTrans.scale_.x *= stopRatio_;
   //     //Image::SetTransform(hPict_[PICT_RED], gaugeTrans);
   //     //Image::Draw(hPict_[PICT_RED]);
   // }
}

//�`��
void UI::Draw()
{
    Player* pPlayer[4];
    pPlayer[0] = (Player*)FindObject("Player");
    pPlayer[1] = (Player*)FindObject("Player2");
    pPlayer[2] = (Player*)FindObject("Player3");
    pPlayer[3] = (Player*)FindObject("Player4");

    if (Direct3D::lr == 0)
    {
        //�f�o�b�O�p
#ifdef _DEBUG
        //pPlayer->GetState();

        for (int i = 0; i < ScreenSplit::GetAllPerson(); i++)
        {
            pText->Draw(1730, 120 + (i * 30), i + 1);
            pText->Draw(1760, 120 + (i * 30), pPlayer[i]->GetStateText().c_str());

        }

        const char* operation[] = {"OPERATION","0     ->TIME FAST","WASD  ->MOVE","<-.-> ->ROTATE","SPASE ->THROW","ESC   ->END","CLRL  ->PAUSE"};
        for (int i = 0;i < 7;i++)
        {
            pText->Draw(1630, 450 + (i * 30), operation[i]);
        }
       

        if (ScreenSplit::GetPlayerPerson() >= 3)
        {
            //Direct3D::SetShader(Direct3D::SHADER_CIRCLE)
            //Direct3D::SetShader(Direct3D::SHADER_2D);
        }

#endif
        ////���ʕ\��
        //if (IsEnd)
        //{
        //    int divided = 10;
        //    Transform numTrans = transform_;
        //    numTrans.position_.x = -0.6f;
        //    int whiteScore = whiteSum;
        //    int redScore = redSum;

        //    //�����_
        //    for (int i = PICT_SECOND_NUMBER; i >= PICT_FIRST_NUMBER; i--)
        //    {
        //        //numTrans.position_.x = -0.1f;
        //        Image::SetRect(hPict_[i], int(whiteScore / divided) * 150, 0, 150, 256);
        //        Image::SetTransform(hPict_[i], numTrans);
        //        Image::Draw(hPict_[i]);
        //        whiteScore = whiteScore % divided;
        //        divided /= 10;
        //        numTrans.position_.x += 0.15f;
        //    }

        //    /*pText->Draw(510, 420, whiteSum);
        //    pText->Draw(420, 420, "White");*/

        //    divided = 10;
        //    numTrans.position_.x = 0.45f;
        //    //�ԓ��_
        //    for (int i = PICT_SECOND_NUMBER; i >= PICT_FIRST_NUMBER; i--)
        //    {
        //        //numTrans.position_.x = -0.1f;
        //        Image::SetRect(hPict_[i], int(redScore / divided) * 150, 0, 150, 256);
        //        Image::SetTransform(hPict_[i], numTrans);
        //        Image::Draw(hPict_[i]);
        //        redScore = redScore % divided;
        //        divided /= 10;
        //        numTrans.position_.x += 0.15f;
        //    }

        //   /* pText->Draw(1510, 420, redSum);
        //    pText->Draw(1420, 420, "Red");
        //    */


        //    Transform redTrans = transform_;
        //    Transform whiteTrans = transform_;
        //    redTrans.position_.x = 0.5f;
        //    redTrans.position_.y = 0.4f;
        //    whiteTrans.position_.x = -0.5f;
        //    whiteTrans.position_.y = 0.4f;
        //    Image::SetTransform(hPict_[PICT_WHITE_TEXT], whiteTrans);
        //    Image::Draw(hPict_[PICT_WHITE_TEXT]);
        //    Image::SetTransform(hPict_[PICT_RED_TEXT], redTrans);
        //    Image::Draw(hPict_[PICT_RED_TEXT]);

        //    redTrans.position_.y = -0.5f;
        //    whiteTrans.position_.y = 0;
        //    whiteTrans.position_.x = 0;
        //    //whiteTrans.position_.x = -0.55f;
        //    //������
        //    if (redSum < whiteSum)
        //    {
        //        Image::SetTransform(hPict_[PICT_WIN], whiteTrans);
        //        Image::Draw(hPict_[PICT_WIN]);
        //       /* Image::SetTransform(hPict_[PICT_LOSE], redTrans);
        //        Image::Draw(hPict_[PICT_LOSE]);*/
        //   /*     pText->Draw(450, 450, "WIN");
        //        pText->Draw(1450, 450, "LOSE");*/
        //    }//�ԏ���
        //    else if (whiteSum < redSum)
        //    {
        //       /* Image::SetTransform(hPict_[PICT_WIN], redTrans);
        //        Image::Draw(hPict_[PICT_WIN]);*/
        //        Image::SetTransform(hPict_[PICT_LOSE], whiteTrans);
        //        Image::Draw(hPict_[PICT_LOSE]);
        //       /* pText->Draw(450, 450, "LOSE");
        //        pText->Draw(1450, 450, "WIN");*/
        //    }//��������
        //    else
        //    {
        //        Transform transDraw = transform_;
        //        transDraw.position_.y = -0.2f;
        //        Image::SetTransform(hPict_[PICT_DRAW], transDraw);
        //        Image::Draw(hPict_[PICT_DRAW]);
        //        //pText->Draw(930, 450, "DRAW");
        //    }
        //}

        ////�r���܂łɂ���
        //Image::SetTransform(hPict_[PICT_WHITE_BAR], transBarWhite);
        //Image::Draw(hPict_[PICT_WHITE_BAR]);
        //Image::SetTransform(hPict_[PICT_RED_BAR], transBarRed);
        //Image::Draw(hPict_[PICT_RED_BAR]);
    }
    Image::SetTransform(hPict_[PICT_FRAME], transform_);
    Image::Draw(hPict_[PICT_FRAME]);
}

//�J��
void UI::Release()
{
}


void UI::SetIsEnd(bool move_)
{
    IsEnd = move_;
}

void UI::LoadSet()
{
    hPict_[PICT_FRAME] = Image::Load("Load.png");
}

bool UI::GetIsEnd()
{
    return IsEnd;
}
