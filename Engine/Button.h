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
	enum Sound
	{
		SOUND_BUTTON,
		SOUND_MOVE,
		SOUND_MAX
	};

	int hPict_;								//画像番号
	int hSound_[Sound::SOUND_MAX];    //サウンド番号
	int alpha;//透明度
	int screenID;//スクリーン番号
	bool isStickMove;//スティックを動かしたか
	bool isNextSelect;//次に選択にするボタンか
	bool isNowSelect;//選択中のボタンか
	Button* firstButton;//初めに選択するボタン
	
	bool IsPushUP(int screenID_);
protected:

	//ボタンが押されたときにする処理
	virtual void Event();

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
	

	//次の選択ボタン取得
	bool GetIsNextSelect();

	//選択ボタンセット
	void SetIsNowSelect(bool state_);
	
	//選択ボタン取得
	bool GetIsNowSelect();

	//ボタンの切り替え
	void ButtonSwith();

	//初めに選択されるボタンセット
	void SetIsFirst(Button* first);

	/// <summary>
	/// アルファ値セット
	/// </summary>
	/// <param name="alpha_">透明度,1～255まで</param>
	void SetAlpha(int alpha_);

	//スクリーンIDのセット
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

	//次の選択ボタンセット
	void SetIsNextSelect(bool state_);

	//シーンID取得
	virtual int GetScreenID();
};