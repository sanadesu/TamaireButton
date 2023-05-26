#include "Field.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Field::Field(GameObject* parent)
    :GameObject(parent, "Field")
{

}

//�f�X�g���N�^
Field::~Field()
{
}

//������
void Field::Initialize()
{
    std::string fileName[] = { "Field","BoxBrick" };
    //���f���f�[�^�̃��[�h
    for (int i = 0; i < /*sizeof(fileName)*/2; i++)
    {
        std::string fn = "Assets/" + fileName[i] + ".fbx";
        hModel_[i] = Model::Load(fn);
        assert(hModel_[i] >= 0);
    }

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.2f);
    AddCollider(collision);
}

//�X�V
void Field::Update()
{

}

//�`��
void Field::Draw()
{
   

    //for (int i = 0; i < 15; i++)
    //{
    //    for (int j = 0; j < 15; j++)
    //    {
    //        for (int k = 0; k < table[i][j].height + 1; k++)
    //        {
    //            //RayCastData data;

    //            //int type = table[i][j].type;
    //            Transform trans;
    //            trans.position_.x = i;
    //            trans.position_.z = j;
                Model::SetTransform(hModel_[0], transform_);
                Model::Draw(hModel_[0]);
    /*        }
        }
    }*/
}

//�J��
void Field::Release()
{
}

//�����ɓ�������
void Field::OnCollision(GameObject* pTarget)
{
    //���������Ƃ��̏���
}