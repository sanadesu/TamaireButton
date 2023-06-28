#pragma once
#include "Engine/GameObject.h"
#include "Engine/Frame.h"
#include "Json.h"

static const int EASE_MAX = 1;//�C�[�W���O�̍ő�l

class TitlePlayer : public GameObject
{
    enum PlayerID
    {
        PLAYER_RED,
        PLAYER_WHITE
    };

    int hModel_;    //���f���ԍ�

    int redStop;
    float rotateZ;
    float posX;
    float easePlayer;
    float BoundRed;
    float BoundWhite;
    float playerPosRed;
    float playerPosWhite;
    float playerRotateZ;
    Frame* nowFrame = (Frame*)FindObject("Frame");
    nlohmann::json data;
public:
    int T_PlayerID;
    
    //�R���X�g���N�^
    TitlePlayer(GameObject* parent);

    //�f�X�g���N�^
    ~TitlePlayer();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};