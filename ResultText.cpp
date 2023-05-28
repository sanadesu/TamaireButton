#include "ResultText.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"

//コンストラクタ
ResultText::ResultText(GameObject* parent)
    :GameObject(parent, "ResultText"),
    hPict_{-1, -1, -1, -1, -1, -1, -1},
    hSound_{-1,-1,-1},
    pText(nullptr)
{

}

//デストラクタ
ResultText::~ResultText()
{

}

//初期化
void ResultText::Initialize()
{
    //画像ファイルロード
    {
        //使用する画像ファイル名
        const char* fileName[] = { "WhiteResult.png", "RedResult.png","WhiteWin.png", "RedWin.png", "Draw.png", "Number.png", "Number.png" };

        //ロード
        for (int i = 0; i < PICT_MAX; i++)
        {
            hPict_[i] = Image::Load(fileName[i]);
            assert(hPict_[i] >= 0);
        }
        
        //使用するサウンドファイル名
        const char* soundFileName[] = { "End.wav", "Drum.wav","Result.wav" };

        //ロード
        for (int i = 0; i < Sound::SOUND_MAX; i++)
        {
            hSound_[i] = Audio::Load(soundFileName[i], false, 1.5f, 10);
            assert(hSound_[i] >= 0);
        }
        hSound_[Sound::SOUND_DRUM] = Audio::Load(soundFileName[Sound::SOUND_DRUM], true, 1.5f, 10);
        assert(hSound_[Sound::SOUND_DRUM] >= 0);
    }

    whiteSum = 0;
    redSum = 0;
    ResultTextCount = 0;

    pText = new Text;
    pText->Initialize();
	pTime = (Time*)FindObject("Time");
	pUI = (UI*)FindObject("UI");
	isEnd = false;
}

//更新
void ResultText::Update()
{
	//制限時間
	if (pTime->GetTime() <= 0)
	{
        ResultTextCount++;
        if(ResultTextCount == 1)
        {
            Audio::Play(hSound_[Sound::SOUND_END]);
        }
        if (ResultTextCount == 50)
        {
            Audio::Play(hSound_[Sound::SOUND_DRUM]);
            //Audio::Play(Sound::SOUND_ResultText);
        }
        if (ResultTextCount == 150)
        {
            //Audio::Play(hSound_[Sound::SOUND_ResultText]);
        }
        if (ResultTextCount == 200)
        {
            Audio::Stop(hSound_[Sound::SOUND_DRUM]);
            Audio::Play(hSound_[Sound::SOUND_RESULT]);
        }

        // 文字出すイージング
        // 
        // swittiにする？
        // {
        // if(ResultTextCount > 60 終了後)
        // {
        // 白表示
        // }
        // else if()
        // {
        // 赤表示
        // }
        // else if()結果
        // 最後ボタン
        // 
        // }
		//動けない
		//for (int i = 0; i < ScreenSplit::GetAllPerson(); i++)
		{
			//pPlayer[i]->SetIsEnd(TRUE);
			isEnd = true;
		}
		
		//if (isEnd && 時間)
		{
			//結果表示 後で移動
			//pUI->SetIsEnd(TRUE);




           




			//もう一回
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, 0) || Input::IsKeyDown(DIK_A))
			{
				////ロード
				//pUI->LoadSet();
				//SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
				//pSceneManager->SameScene();
			}
		}
	}

}

//描画
void ResultText::Draw()
{
    if (Direct3D::lr == 0)
    {
        if (pTime->GetTime() <= 0)
        {
            //結果表示
            if (/*IsEnd 時間？*/"")
            {
                int divided = 10;
                Transform numTrans = transform_;
                numTrans.position_.x = -0.6f;

                int whiteScore = whiteSum;//もってくる？こっちでカウントする
                int redScore = redSum;

                if (ResultTextCount > 100)
                {
                    //白得点
                    for (int i = PICT_SECOND_NUMBER; i >= PICT_FIRST_NUMBER; i--)
                    {
                        //numTrans.position_.x = -0.1f;
                        //number関数
                        Image::SetRect(hPict_[i], int(whiteScore / divided) * 150, 0, 150, 256);
                        Image::SetTransform(hPict_[i], numTrans);
                        Image::Draw(hPict_[i]);
                        whiteScore = whiteScore % divided;
                        divided /= 10;
                        numTrans.position_.x += 0.15f;
                    }
                }
                

                /*pText->Draw(510, 420, whiteSum);
                pText->Draw(420, 420, "White");*/

                divided = 10;
                numTrans.position_.x = 0.45f;
                if (ResultTextCount > 150)
                {
                    //赤得点
                    for (int i = PICT_SECOND_NUMBER; i >= PICT_FIRST_NUMBER; i--)
                    {
                        //numTrans.position_.x = -0.1f;
                        Image::SetRect(hPict_[i], int(redScore / divided) * 150, 0, 150, 256);
                        Image::SetTransform(hPict_[i], numTrans);
                        Image::Draw(hPict_[i]);
                        redScore = redScore % divided;
                        divided /= 10;
                        numTrans.position_.x += 0.15f;
                    }
                }
                

                /* pText->Draw(1510, 420, redSum);
                 pText->Draw(1420, 420, "Red");
                 */


                Transform redTrans = transform_;
                Transform whiteTrans = transform_;
                redTrans.position_.x = 0.5f;
                redTrans.position_.y = 0.4f;
                whiteTrans.position_.x = -0.5f;
                whiteTrans.position_.y = 0.4f;
                Image::SetTransform(hPict_[PICT_WHITE_TEXT], whiteTrans);
                Image::Draw(hPict_[PICT_WHITE_TEXT]);
                Image::SetTransform(hPict_[PICT_RED_TEXT], redTrans);
                Image::Draw(hPict_[PICT_RED_TEXT]);

                redTrans.position_.y = -0.5f;
                whiteTrans.position_.y = 0;
                whiteTrans.position_.x = 0;
                //whiteTrans.position_.x = -0.55f;
                if (ResultTextCount > 200)
                {
                    //白勝ち
                    if (redSum < whiteSum)
                    {
                        Image::SetTransform(hPict_[PICT_WIN], whiteTrans);
                        Image::Draw(hPict_[PICT_WIN]);
                        /* Image::SetTransform(hPict_[PICT_LOSE], redTrans);
                         Image::Draw(hPict_[PICT_LOSE]);*/
                         /*     pText->Draw(450, 450, "WIN");
                              pText->Draw(1450, 450, "LOSE");*/
                    }//赤勝ち
                    else if (whiteSum < redSum)
                    {
                        /* Image::SetTransform(hPict_[PICT_WIN], redTrans);
                         Image::Draw(hPict_[PICT_WIN]);*/
                        Image::SetTransform(hPict_[PICT_LOSE], whiteTrans);
                        Image::Draw(hPict_[PICT_LOSE]);
                        /* pText->Draw(450, 450, "LOSE");
                         pText->Draw(1450, 450, "WIN");*/
                    }//引き分け
                    else
                    {
                        Transform transDraw = transform_;

                        Image::SetTransform(hPict_[PICT_DRAW], whiteTrans);
                        Image::Draw(hPict_[PICT_DRAW]);
                        //pText->Draw(930, 450, "DRAW");
                    }
                }
                
            }
        }
        //デバッグ
#ifdef _DEBUG
        //得点表示
        pText->Draw(1730, 30, "White");
        pText->Draw(1850, 30, (whiteSum));
        pText->Draw(1730, 60, "Red");
        pText->Draw(1850, 60, (redSum));
#endif
    }
}

//開放
void ResultText::Release()
{
}

bool ResultText::GetIsEnd()
{
	return isEnd;
}
