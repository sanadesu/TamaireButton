#include "ResultText.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/ScreenSplit.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"

//�R���X�g���N�^
ResultText::ResultText(GameObject* parent)
    :GameObject(parent, "ResultText"),
    hPict_{-1, -1, -1, -1, -1, -1, -1},
    hSound_{-1,-1,-1},
    pText(nullptr)
{

}

//�f�X�g���N�^
ResultText::~ResultText()
{

}

//������
void ResultText::Initialize()
{
    //�摜�t�@�C�����[�h
    {
        //�g�p����摜�t�@�C����
        const char* fileName[] = { "WhiteResult.png", "RedResult.png","WhiteWin.png", "RedWin.png", "Draw.png", "Number.png", "Number.png" };

        //���[�h
        for (int i = 0; i < PICT_MAX; i++)
        {
            hPict_[i] = Image::Load(fileName[i]);
            assert(hPict_[i] >= 0);
        }
        
        //�g�p����T�E���h�t�@�C����
        const char* soundFileName[] = { "End.wav", "Drum.wav","Result.wav" };

        //���[�h
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

//�X�V
void ResultText::Update()
{
	//��������
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

        // �����o���C�[�W���O
        // 
        // switti�ɂ���H
        // {
        // if(ResultTextCount > 60 �I����)
        // {
        // ���\��
        // }
        // else if()
        // {
        // �ԕ\��
        // }
        // else if()����
        // �Ō�{�^��
        // 
        // }
		//�����Ȃ�
		//for (int i = 0; i < ScreenSplit::GetAllPerson(); i++)
		{
			//pPlayer[i]->SetIsEnd(TRUE);
			isEnd = true;
		}
		
		//if (isEnd && ����)
		{
			//���ʕ\�� ��ňړ�
			//pUI->SetIsEnd(TRUE);




           




			//�������
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, 0) || Input::IsKeyDown(DIK_A))
			{
				////���[�h
				//pUI->LoadSet();
				//SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
				//pSceneManager->SameScene();
			}
		}
	}

}

//�`��
void ResultText::Draw()
{
    if (Direct3D::lr == 0)
    {
        if (pTime->GetTime() <= 0)
        {
            //���ʕ\��
            if (/*IsEnd ���ԁH*/"")
            {
                int divided = 10;
                Transform numTrans = transform_;
                numTrans.position_.x = -0.6f;

                int whiteScore = whiteSum;//�����Ă���H�������ŃJ�E���g����
                int redScore = redSum;

                if (ResultTextCount > 100)
                {
                    //�����_
                    for (int i = PICT_SECOND_NUMBER; i >= PICT_FIRST_NUMBER; i--)
                    {
                        //numTrans.position_.x = -0.1f;
                        //number�֐�
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
                    //�ԓ��_
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
                    //������
                    if (redSum < whiteSum)
                    {
                        Image::SetTransform(hPict_[PICT_WIN], whiteTrans);
                        Image::Draw(hPict_[PICT_WIN]);
                        /* Image::SetTransform(hPict_[PICT_LOSE], redTrans);
                         Image::Draw(hPict_[PICT_LOSE]);*/
                         /*     pText->Draw(450, 450, "WIN");
                              pText->Draw(1450, 450, "LOSE");*/
                    }//�ԏ���
                    else if (whiteSum < redSum)
                    {
                        /* Image::SetTransform(hPict_[PICT_WIN], redTrans);
                         Image::Draw(hPict_[PICT_WIN]);*/
                        Image::SetTransform(hPict_[PICT_LOSE], whiteTrans);
                        Image::Draw(hPict_[PICT_LOSE]);
                        /* pText->Draw(450, 450, "LOSE");
                         pText->Draw(1450, 450, "WIN");*/
                    }//��������
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
        //�f�o�b�O
#ifdef _DEBUG
        //���_�\��
        pText->Draw(1730, 30, "White");
        pText->Draw(1850, 30, (whiteSum));
        pText->Draw(1730, 60, "Red");
        pText->Draw(1850, 60, (redSum));
#endif
    }
}

//�J��
void ResultText::Release()
{
}

bool ResultText::GetIsEnd()
{
	return isEnd;
}
