#include "ScreenSplit.h"
#include "Direct3D.h"

namespace ScreenSplit
{
	int screenDivision = 1;//��ʕ�����
	int playPerson = 1;//�v���C���[�l��(AI����Ȃ�)
	int allPerson = 4;//���v�l��(AI��)

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

