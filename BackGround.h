#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class BackGround : public GameObject
{
    int hModel_;    //���f���ԍ�
    int hModel_Sky;
    Transform transSky;
    
public:
    //�R���X�g���N�^
    BackGround(GameObject* parent);

    //�f�X�g���N�^
    ~BackGround();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};