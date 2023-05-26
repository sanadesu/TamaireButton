#include "Goal.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Goal::Goal(GameObject* parent)
    :GameObject(parent, "Goal")
{

}

//�f�X�g���N�^
Goal::~Goal()
{
}

//������
void Goal::Initialize()
{
    std::string fileName[] = { "Goal" };
    //���f���f�[�^�̃��[�h
    //for (int i = 0; i < /*sizeof(fileName)*/2; i++)
    //{
    std::string fn = "Assets/" + fileName[0] + ".fbx";
    hModel_[0] = Model::Load(fn);
    assert(hModel_[0] >= 0);
    //}
}

//�X�V
void Goal::Update()
{

}

//�`��
void Goal::Draw()
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
void Goal::Release()
{
}

