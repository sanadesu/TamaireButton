#include "UI.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/ScreenSplit.h"
#include "Player.h"
#include "Engine/ScreenSplit.h"

//コンストラクタ
UI::UI(GameObject* parent)
    :GameObject(parent, "UI"),
    hPict_{ -1,-1,-1 },
    pText(nullptr)
{
}

//デストラクタ
UI::~UI()
{
}

//初期化
void UI::Initialize()
{
    //画像ファイルロード
    {
        //使用する画像ファイル名
        const char* fileName[] = { "Frame.png", "WhiteBar.png", "RedBar.png" };

        //ロード
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

//更新
void UI::Update()
{
   // //最大HPに対する、現在HPの割合
   // stopRatio = ((float)redSum + 1.0f ) / ((float)whiteSum + 1 + redSum + 1.0f) + 0.5;
   ///* if (stopRatio > 1.25f)
   // {
   //     stopRatio = 1.25f;
   // }
   // else if (stopRatio < 0.75f)
   // {
   //     stopRatio = 0.75f;
   // }*/

   // //バーを動かす
   // if (moveRatio < stopRatio) 
   //     moveRatio += SPEED;
   // else if (moveRatio > stopRatio) 
   //     moveRatio -= SPEED;

   // //HP変化なし
   // if (abs(moveRatio - stopRatio) < SPEED)
   // {
   //     //緑ゲージ
   //     transBarRed = transBarWhite;
   //     transBarRed.scale_.x *= stopRatio;
   //     transBarRed.position_.x = BAR_X;

   // }
   // //回復中
   // else if (moveRatio < stopRatio)
   // {
   //     ////黄緑ゲージ
   //     //gaugeTrans = transform_;
   //     //gaugeTrans.scale_.x *= stopRatio_;
   //     //Image::SetTransform(hPict_[PICT_RED], gaugeTrans);
   //     //Image::Draw(hPict_[PICT_RED]);

   //     //緑ゲージ
   //     transBarRed = transBarWhite;
   //     transBarRed.scale_.x *= moveRatio;
   //     transBarRed.position_.x = BAR_X;
   // }

   // //ダメージ中
   // else
   // {
   //     //赤ゲージ
   //     transBarRed = transBarWhite;
   //     transBarRed.scale_.x *= moveRatio;
   //     transBarRed.position_.x = BAR_X;

   //     ////緑ゲージ
   //     //gaugeTrans = transform_;
   //     //gaugeTrans.scale_.x *= stopRatio_;
   //     //Image::SetTransform(hPict_[PICT_RED], gaugeTrans);
   //     //Image::Draw(hPict_[PICT_RED]);
   // }
}

//描画
void UI::Draw()
{
    Player* pPlayer[4];
    pPlayer[0] = (Player*)FindObject("Player");
    pPlayer[1] = (Player*)FindObject("Player2");
    pPlayer[2] = (Player*)FindObject("Player3");
    pPlayer[3] = (Player*)FindObject("Player4");

    if (Direct3D::lr == 0)
    {
        //デバッグ用
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
        ////結果表示
        //if (IsEnd)
        //{
        //    int divided = 10;
        //    Transform numTrans = transform_;
        //    numTrans.position_.x = -0.6f;
        //    int whiteScore = whiteSum;
        //    int redScore = redSum;

        //    //白得点
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
        //    //赤得点
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
        //    //白勝ち
        //    if (redSum < whiteSum)
        //    {
        //        Image::SetTransform(hPict_[PICT_WIN], whiteTrans);
        //        Image::Draw(hPict_[PICT_WIN]);
        //       /* Image::SetTransform(hPict_[PICT_LOSE], redTrans);
        //        Image::Draw(hPict_[PICT_LOSE]);*/
        //   /*     pText->Draw(450, 450, "WIN");
        //        pText->Draw(1450, 450, "LOSE");*/
        //    }//赤勝ち
        //    else if (whiteSum < redSum)
        //    {
        //       /* Image::SetTransform(hPict_[PICT_WIN], redTrans);
        //        Image::Draw(hPict_[PICT_WIN]);*/
        //        Image::SetTransform(hPict_[PICT_LOSE], whiteTrans);
        //        Image::Draw(hPict_[PICT_LOSE]);
        //       /* pText->Draw(450, 450, "LOSE");
        //        pText->Draw(1450, 450, "WIN");*/
        //    }//引き分け
        //    else
        //    {
        //        Transform transDraw = transform_;
        //        transDraw.position_.y = -0.2f;
        //        Image::SetTransform(hPict_[PICT_DRAW], transDraw);
        //        Image::Draw(hPict_[PICT_DRAW]);
        //        //pText->Draw(930, 450, "DRAW");
        //    }
        //}

        ////途中までにする
        //Image::SetTransform(hPict_[PICT_WHITE_BAR], transBarWhite);
        //Image::Draw(hPict_[PICT_WHITE_BAR]);
        //Image::SetTransform(hPict_[PICT_RED_BAR], transBarRed);
        //Image::Draw(hPict_[PICT_RED_BAR]);
    }
    Image::SetTransform(hPict_[PICT_FRAME], transform_);
    Image::Draw(hPict_[PICT_FRAME]);
}

//開放
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
