#include "TitleBall.h"
#include "Engine/Image.h"
#include "Engine/Model.h"
#include "Engine/Easing.h"

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
	transform_.position_.x = (float)(rand() % RANGE_X - (RANGE_X / 2)) / 10.0f;
	transform_.position_.z = (float)(rand() % RANGE_Z) / 10.0f + 30;//�O�ɏo��
	transform_.position_.y = 9;

	transform_.scale_ = XMFLOAT3(SIZE, SIZE, SIZE);
	easeY = 0.1f;
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
