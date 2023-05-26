#include "Rule.h"
#include "Engine/Image.h"

//�R���X�g���N�^
Rule::Rule(GameObject* parent)
	: GameObject(parent, "Rule"), hPict_(-1)
{
}

//������
void Rule::Initialize()
{
	
}

//�X�V
void Rule::Update()
{
	
}

//�`��
void Rule::Draw()
{
	if (hPict_ != -1)
	{
		Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

//�J��
void Rule::Release()
{
}

void Rule::SetRuleImage(const std::string& path)
{
	if (path != "NO")
	{
		//�摜�f�[�^�̃��[�h
		hPict_ = Image::Load(path);

		//���[�h���ꂽ���m�F
		assert(hPict_ >= 0);
	}
	else
	{
		hPict_ = -1;
	}
}
