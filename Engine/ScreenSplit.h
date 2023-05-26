#pragma once

namespace ScreenSplit
{
    //カメラ分割数(セッター)
    void SetScreenSplit(int i);

    //カメラ分割数(ゲッター)
    int GetScreenSplit();

    //プレイ人数(セッター)
    void SetPlayPerson(int player_);

    //プレイ人数(ゲッター)
    int GetPlayerPerson();

    //全員
    void SetAllPerson(int num);

    int GetAllPerson();
}