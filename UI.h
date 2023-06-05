#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//◆◆◆を管理するクラス
class UI : public GameObject
{
    int hPict_;//画像番号
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