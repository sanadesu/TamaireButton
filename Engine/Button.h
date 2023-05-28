#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "GameObject.h"
#include "Sprite.h"
#include "Transform.h"


class Button :public GameObject
{
private:
	//bool isSelect;
	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	int hPict_;								//画像番号
	int hSound_[Sound::SOUND_MAX];    //サウンド番号
	int alpha;
	int screenID;
	bool isStickMove;
	bool isNextSelect;
	bool isNowSelect;
	Button* firstButton;

	XMFLOAT3 nowButtonPos;
	//std::pair<float, float> framePos[5];
	
protected:

	//ボタンが押されたときにする処理
	virtual void Event();

	//選択ボタンの動き　
	virtual void SelectMove(int screenID);

	//選択された瞬間
	virtual void IsSelect();

	//選択解除された瞬間
	virtual void IsSelectReleas();

	//サブアップデート
	virtual void SubUpdate();

	//サブ初期化
	virtual void SubInitialize();

	//画像セット
	void SetImage(const std::string& path ,Transform trans);
	
	//選択中ボタン
	//void SetNowButton(XMFLOAT3 selectButton);

	//次の選択ボタンセット
	void SetIsNextSelect(bool state_);

	//次の選択ボタン取得
	bool GetIsNextSelect();

	//選択ボタンセット
	void SetIsNowSelect(bool state_);
	
	//選択ボタン取得
	bool GetIsNowSelect();

	void ButtonSwith();

	void SetIsFirst(Button* first);

	Button* GetIsFirst();

	void SetAlpha(int alpha_);

	void SetScreenID(int screenID);



public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Button(GameObject* parent, const std::string& name);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	virtual int GetScreenID();
};