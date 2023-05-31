#include "UI.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/ScreenSplit.h"
#include "Player.h"
#include "Engine/ScreenSplit.h"

//�R���X�g���N�^
UI::UI(GameObject* parent)
    :GameObject(parent, "UI"),
    hPict_(-1),
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
    hPict_ = Image::Load("Frame.png");
    assert(hPict_ >= 0);

    pText = new Text;
    pText->Initialize();
    IsEnd = false;
}

//�X�V
void UI::Update()
{
 
}

//�`��
void UI::Draw()
{
    const char* objectName[] = { "Player","Player2" ,"Player3" ,"Player4" };
    
    Player* pPlayer[PLAYER_MAX];
    for (int i = 0; i < PLAYER_MAX; i++)
    {
        pPlayer[i] = (Player*)FindObject(objectName[i]);
    }

    if (Direct3D::lr == 0)
    {
        //�f�o�b�O�p
#ifdef _DEBUG
        for (int i = 0; i < ScreenSplit::GetAllPerson(); i++)
        {
            pText->Draw(STATE_X, STATE_Y + (i * TEXT_SIZE), i + 1);
            pText->Draw(STATE_X + TEXT_SIZE, STATE_Y + (i * TEXT_SIZE), pPlayer[i]->GetStateText().c_str());
        }

        const char* operation[] = {"OPERATION","0     ->TIME FAST","WASD  ->MOVE","<-.-> ->ROTATE","SPASE ->THROW","ESC   ->END","CLRL  ->PAUSE"};
        for (int i = 0;i < OPERATION_MAX;i++)
        {
            pText->Draw(OPERATION_X, OPERATION_Y + (i * TEXT_SIZE), operation[i]);
        }
#endif
    }
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

//�J��
void UI::Release()
{
}

//���[�h��ʂɐ؂�ւ�
void UI::LoadSet()
{
    hPict_ = Image::Load("Load.png");
}

//�I�����Ă邩�擾
bool UI::GetIsEnd()
{
    return IsEnd;
}
