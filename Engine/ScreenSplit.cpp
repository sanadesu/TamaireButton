#include "ScreenSplit.h"
#include "Direct3D.h"

namespace ScreenSplit
{
	int screenDivision = 1;//画面分割数
	int playPerson = 1;//プレイヤー人数(AIじゃない)
	int allPerson = 4;//合計人数(AI込)

	void ScreenSplit::SetScreenSplit(int i)
	{
		screenDivision = i;
	}

	int ScreenSplit::GetScreenSplit()
	{
		return screenDivision;
	}

	void ScreenSplit::SetPlayPerson(int player_)
	{
		playPerson = player_;
	}

	int ScreenSplit::GetPlayerPerson()
	{
		return playPerson;
	}


	void SetAllPerson(int num)
	{
		allPerson = num;
	}

	int GetAllPerson()
	{
		return allPerson;
	}
}

