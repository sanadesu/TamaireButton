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
    static const int DRUM_START = 50;//ドラム鳴らすタイミング
    static const int WHITE_SCORE = 100;//白ボール個数表示
    static const int RED_SCORE = 150;//赤ボール個数表示
    static const int RESULT_TEXT = 200;//結果表示
    static const int SOUND_COUNT = 10;//音を同時に鳴らせる回数
    static const float SOUND_VOLUME = 1.0f;//音量
    static const float FONT_SPACE = 0.15f;//数字の間隔
    static const float POS_X = 0.5f;//場所X
    static const float POS_Y = 0.4;//場所Y
}

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
            hSound_[i] = Audio::Load(soundFileName[i], false, SOUND_VOLUME, SOUND_COUNT);
            assert(hSound_[i] >= 0);
        }
        hSound_[Sound::SOUND_DRUM] = Audio::Load(soundFileName[Sound::SOUND_DRUM], true, SOUND_VOLUME, SOUND_COUNT);
        assert(hSound_[Sound::SOUND_DRUM] >= 0);
    }

    
    whiteSum = 0;
    redSum = 0;
    ResultTextCount = 0;
    pText = new Text;
    pText->Initialize();
	pTime = (Time*)FindObject("Time");
	isEnd = false;
}

//更新
void ResultText::Update()
{
	//制限時間
	if (pTime->GetTime() <= 0)
	{
        switch (ResultTextCount)
        {
        case 0:
            Audio::Play(hSound_[Sound::SOUND_END]);
            break;
        case DRUM_START:
            Audio::Play(hSound_[Sound::SOUND_DRUM]);
            break;
        case RESULT_TEXT:
            Audio::Stop(hSound_[Sound::SOUND_DRUM]);
            Audio::Play(hSound_[Sound::SOUND_RESULT]);
            break;
        case WHITE_SCORE:
            pWhiteNumber = InstantiateID<Number>(this, XMFLOAT3(0, 0, 0), 0);
            pWhiteNumber->SetNum(whiteSum, FONT_SPACE, -POS_X);
            break;
        case RED_SCORE:
            pRedNumber = InstantiateID<Number>(this, XMFLOAT3(0, 0, 0), 0);
            pRedNumber->SetNum(redSum, FONT_SPACE, POS_X);
            break;
        default:
            break;
        }

        ResultTextCount++;

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
            Transform redTrans = transform_;
            Transform whiteTrans = transform_;
            redTrans.position_.x = POS_X;
            redTrans.position_.y = POS_Y;
            whiteTrans.position_.x = -POS_X;
            whiteTrans.position_.y = POS_Y;
            Image::SetTransform(hPict_[PICT_WHITE_TEXT], whiteTrans);
            Image::Draw(hPict_[PICT_WHITE_TEXT]);
            Image::SetTransform(hPict_[PICT_RED_TEXT], redTrans);
            Image::Draw(hPict_[PICT_RED_TEXT]);

            if (ResultTextCount > RESULT_TEXT)
            {
                //白勝ち
                if (redSum < whiteSum)
                {
                    Image::SetTransform(hPict_[PICT_WIN], transform_);
                    Image::Draw(hPict_[PICT_WIN]);
                }//赤勝ち
                else if (whiteSum < redSum)
                {
                    Image::SetTransform(hPict_[PICT_LOSE], transform_);
                    Image::Draw(hPict_[PICT_LOSE]);
                }//引き分け
                else
                {
                    Image::SetTransform(hPict_[PICT_DRAW], transform_);
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
