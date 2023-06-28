#include "Json.h"
#include <Windows.h>

nlohmann::json Json::Load(std::string fileName)
{
    //JSONデータを読み込むためのファイルストリームを作成
    std::ifstream file(fileName);

    // ファイルが正常にオープンされたかを確認
    if (!file.is_open()) {
        MessageBox(NULL, "JSONファイルの読み込みに失敗しました。", "FAIL", MB_OK);
    }

    // JSONデータを格納するための変数
    nlohmann::json data;

    // JSONファイルをパースしてデータを取得
    file >> data;

    // ファイルをクローズ
    file.close();
    return data;
}
