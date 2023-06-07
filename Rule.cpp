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
	//���g������Ε`�悷��
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

//�摜�Z�b�g
void Rule::SetRuleImage(const std::string& path)
{
	//�摜��\�����邩�ǂ���
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
