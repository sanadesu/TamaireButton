#include "TitleBall.h"
#include "Engine/Image.h"
#include "Engine/Model.h"
#include "Engine/Easing.h"

//�萔
namespace
{
	static const int DOWN_LIMIT = -40;//�{�[������������
	static const int RANGE_X = 600;//�{�[���𗎂Ƃ��͈�(��)
	static const int RANGE_Z = 100;//�{�[���𗎂Ƃ��͈�(��)
	static const int BALL_FRONT = 30;//�{�[����O�ɏo��
	static const int START_DOWN = 9;//�{�[���̃X�^�[�g�ʒu
	static const int BALL_SIZE = 4;//�{�[���̑傫��
	static const float DOWN_SPEAD = 0.005f;//�{�[���������鑬��
	static const float DECIMAL_CHANGE = 10.0f;//�{�[���������鑬��
	static const float EASE_START = 0.01f;//�{�[���������鑬��
}

//�R���X�g���N�^
TitleBall::TitleBall(GameObject* parent)
	: GameObject(parent, "TitleBall"),hModel_(-1)
{
}

//������
void TitleBall::Initialize()
{
	//�Ԕ��{�[�������_���ō~�炷
	if (rand() % 2 == 0)
		hModel_ = Model::Load("RedBall.fbx");
	else
		hModel_ = Model::Load("WhiteBall.fbx");
	assert(hModel_ >= 0);

	//�ꏊ�������_��
	transform_.position_.x = (float)(rand() % RANGE_X - (RANGE_X / 2)) / DECIMAL_CHANGE;
	transform_.position_.z = (float)(rand() % RANGE_Z) / DECIMAL_CHANGE + BALL_FRONT;//�O�ɏo��
	transform_.position_.y = START_DOWN;

	//�T�C�Y�ύX
	transform_.scale_ = XMFLOAT3(BALL_SIZE, BALL_SIZE, BALL_SIZE);
	easeY = EASE_START;
}

//�X�V
void TitleBall::Update()
{
	//�{�[���̗�����X�s�[�h
	easeY += DOWN_SPEAD;
	if (easeY > 1)
		easeY = 1;
	transform_.position_.y -= Easing::EaseInQuad(easeY);

	//���ɍs���������
	if (transform_.position_.y < DOWN_LIMIT)
		KillMe();
}

//�`��
void TitleBall::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void TitleBall::Release()
{
}
