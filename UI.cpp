#include "UI.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/ScreenSplit.h"
#include "Player.h"
#include "Engine/ScreenSplit.h"

//コンストラクタ
UI::UI(GameObject* parent)
    :GameObject(parent, "UI"),
    hPict_(-1),
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
    hPict_ = Image::Load("Frame.png");
    assert(hPict_ >= 0);

    pText = new Text;
    pText->Initialize();
    IsEnd = false;
}

//更新
void UI::Update()
{
 
}

//描画
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
        //デバッグ用
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

//開放
void UI::Release()
{
}

//ロード画面に切り替え
void UI::LoadSet()
{
    hPict_ = Image::Load("Load.png");
}

//終了してるか取得
bool UI::GetIsEnd()
{
    return IsEnd;
}
