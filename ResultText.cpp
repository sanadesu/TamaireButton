#include "ResultText.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"

//定数
namespace
{
    static const int END_TEXT = 1;//ゲーム終了
    static const int DRUM_START = 50;//ドラム鳴らすタイミング
    static const int WHITE_SCORE = 100;//白ボール個数表示
    static const int RED_SCORE = 150;//赤ボール個数表示
    static const int RESULTTEXT = 200;//結果表示
    static const int SOUND_COUNT = 10;//音を同時に鳴らせる回数
    static const float SOUND_VOLUME = 1.0f;//音量

}

//コンストラクタ
ResultText::ResultText(GameObject* parent)
    :GameObject(parent, "ResultText"),
    hPict_{-1, -1, -1, -1, -1, -1, -1},
    hSound_{-1,-1,-1}
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
            hSound_[i] = Audio::Load(soundFileName[i], false, SOUND_VOLUME, SOUND_COUNT);
            assert(hSound_[i] >= 0);
        }
        hSound_[Sound::SOUND_DRUM] = Audio::Load(soundFileName[Sound::SOUND_DRUM], true, SOUND_VOLUME, SOUND_COUNT);
        assert(hSound_[Sound::SOUND_DRUM] >= 0);
    }

    whiteSum = 0;
    redSum = 0;
    ResultTextCount = 0;

	pTime = (Time*)FindObject("Time");
	isEnd = false;
}

//更新
void ResultText::Update()
{
	//制限時間
	if (pTime->GetTime() <= 0)
	{
        ResultTextCount++;
        if(ResultTextCount == END_TEXT)
        {
            Audio::Play(hSound_[Sound::SOUND_END]);
        }
        if (ResultTextCount == DRUM_START)
        {
            Audio::Play(hSound_[Sound::SOUND_DRUM]);
        }
        if (ResultTextCount == RESULTTEXT)
        {
            Audio::Stop(hSound_[Sound::SOUND_DRUM]);
            Audio::Play(hSound_[Sound::SOUND_RESULT]);
        }

		isEnd = true;
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
            int divided = 10;
            Transform numTrans = transform_;
            numTrans.position_.x = -0.6f;

            int whiteScore = whiteSum;
            int redScore = redSum;

            if (ResultTextCount > WHITE_SCORE)
            {
                //白得点
                for (int i = PICT_SECOND_NUMBER; i >= PICT_FIRST_NUMBER; i--)
                {
                    Image::SetRect(hPict_[i], int(whiteScore / divided) * 150, 0, 150, 256);
                    Image::SetTransform(hPict_[i], numTrans);
                    Image::Draw(hPict_[i]);
                    whiteScore = whiteScore % divided;
                    divided /= 10;
                    numTrans.position_.x += 0.15f;
                }
            }

            divided = 10;
            numTrans.position_.x = 0.45f;
            if (ResultTextCount > RED_SCORE)
            {
                //赤得点
                for (int i = PICT_SECOND_NUMBER; i >= PICT_FIRST_NUMBER; i--)
                {
                    Image::SetRect(hPict_[i], int(redScore / divided) * 150, 0, 150, 256);
                    Image::SetTransform(hPict_[i], numTrans);
                    Image::Draw(hPict_[i]);
                    redScore = redScore % divided;
                    divided /= 10;
                    numTrans.position_.x += 0.15f;
                }
            }

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
            if (ResultTextCount > RESULTTEXT)
            {
                //白勝ち
                if (redSum < whiteSum)
                {
                    Image::SetTransform(hPict_[PICT_WIN], whiteTrans);
                    Image::Draw(hPict_[PICT_WIN]);
                }//赤勝ち
                else if (whiteSum < redSum)
                {
                    Image::SetTransform(hPict_[PICT_LOSE], whiteTrans);
                    Image::Draw(hPict_[PICT_LOSE]);
                }//引き分け
                else
                {
                    Image::SetTransform(hPict_[PICT_DRAW], whiteTrans);
                    Image::Draw(hPict_[PICT_DRAW]);
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
