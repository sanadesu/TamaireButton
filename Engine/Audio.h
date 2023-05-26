#pragma once
#include <string>

//-----------------------------------------------------------
//サウンドを管理する（XAudio使用）
//-----------------------------------------------------------
namespace Audio
{
	//初期化
	void Initialize();

	//サウンドファイル(.wav）をロード
	//すでに同じ名前のファイルをロード済みの場合は、既存のデータの番号を返す
	//引数：fileName	ファイル名
	//引数：svNum　		同時に鳴らす最大数（省略可）
	//戻値：そのデータに割り当てられた番号
	int Load(std::string fileName, bool loopFlg, float volume, int svNum);

	//再生
	//引数：ID	鳴らしたいサウンドの番号
	void Play(int ID);

	//止める
	//引数：ID	止めたいサウンドの番号
	void Stop(int ID);

	//すべて開放
	void Release();
	void AllRelease();
};

