#include "Frame.h"
#include "Image.h"
#include "Easing.h"

//�R���X�g���N�^
Frame::Frame(GameObject* parent)
	: GameObject(parent, "Frame")
{
	
}

//������
void Frame::Initialize()
{
	frame = 0;
}

//�X�V
void Frame::Update()
{
	frame++;
}

//�`��
void Frame::Draw()
{


}

//�J��
void Frame::Release()
{
}

int Frame::GetFrame()
{
	return frame;
}
