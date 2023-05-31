#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//◆◆◆を管理するクラス
class UI : public GameObject
{
    static const int PLAYER_MAX = 4;
    const int TEXT_SIZE = 30;
    const int OPERATION_X = 1630;
    const int OPERATION_Y = 450;
    const int STATE_X = 1730;
    const int STATE_Y = 120;
    const int OPERATION_MAX = 7;
    //画像番号
    int hPict_;
    bool IsEnd;       //終了してるか
    Text* pText;
public:
    //コンストラクタ
    UI(GameObject* parent);

    //デストラクタ
    ~UI();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //ロード画面に切り替え
    void LoadSet();

    //終了してるか取得
    bool GetIsEnd();
};