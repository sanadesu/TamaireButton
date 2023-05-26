#pragma once
#include "Engine/GameObject.h"
#include "Frame.h"

static const int EASE_MAX = 1;//�C�[�W���O�̍ő�l

class TitlePlayer : public GameObject
{
    enum PlayerID
    {
        PLAYER_RED,
        PLAYER_WHITE
    };

    int hModel_;    //���f���ԍ�
    static const int POS_X = -15;
    static const int MOVE_RANGE = 50;
    const int BOUND_WIDTH = 15;//�o�ꂷ�鎞�̉���
    const int PLAYER_POS_Y = -2;//�v���C���[�̍���
    const int RED_ANGLE = 170;//�ԃL�����̊p�x
    const int WHITE_ANGLE = 190;//���L�����̊p�x
    const int WHITE_START = 30;//�ԃL��������x��ēo�ꂷ��t���[����
    const int SWING_WIDTH = 30;//�h��镝

    const float SIZE = 2.0f;//�v���C���[�̑傫��
    const float SWING_ROTATE = 0.01f;//���E�ɎC��鎞��1�t���[���ɉ�]����l
    const float SWING_POS = 0.05f;//���E�ɗh���Ƃ���1�t���[���ɓ����l
    const float BOUND_EASE_START = 0.5f;//�C�[�W���O���ǂ�����n�߂邩
    const float PLAYER_ROTATE = 3.6f;//�o�Ă���Ƃ���1�t���[���̉�]��
    const float BOUND_DOWN = 0.01f;//�C�[�W���O�̕ω���
    const float SWING_SLOPE = 60.0f;//�����̌X���
    const float SWING_MOVE = 5.0f;//�����̍��E�ړ��
    const float SWING_POS_RED = 17.5f;//�����̍��E�ړ��
    const float SWING_POS_WHITE = 12.5f;//�����̍��E�ړ��
   

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