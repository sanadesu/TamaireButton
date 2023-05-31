#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <vector>
#include <string>
#include "Transform.h"
#include "Texture.h"
#include "Direct3D.h"

class FbxParts;

//���C�L���X�g�p�\����
struct RayCastData
{
	XMFLOAT3	start = XMFLOAT3(0,0,0);	//���C���ˈʒu
	XMFLOAT3	dir = XMFLOAT3(0, 0, 0);	//���C�̌����x�N�g��
	float       dist = 0.0f;	//�Փ˓_�܂ł̋���
	BOOL        hit = false;	//���C������������
	XMFLOAT3 normal = XMFLOAT3(0, 0, 0);	//�@��

	RayCastData() { dist = 99999.0f; }
};

//-----------------------------------------------------------
//�@FBX�t�@�C���������N���X
//�@�قƂ�ǂ̏����͊e�p�[�c���Ƃ�FbxParts�N���X�ōs��
//-----------------------------------------------------------
class Fbx
{
	//FbxPart�N���X���t�����h�N���X�ɂ���
	//FbxPart��private�Ȋ֐��ɂ��A�N�Z�X��
	friend class FbxParts;



	//���f���̊e�p�[�c�i�������邩���j
	std::vector<FbxParts*>	parts_;

	//FBX�t�@�C���������@�\�̖{��
	FbxManager* pFbxManager_;

	//FBX�t�@�C���̃V�[���iMaya�ō�������ׂĂ̕��́j������
	FbxScene*	pFbxScene_;


	// �A�j���[�V�����̃t���[�����[�g
	FbxTime::EMode	_frameRate;

	//�A�j���[�V�������x
	float			_animSpeed;

	//�A�j���[�V�����̍ŏ��ƍŌ�̃t���[��
	int _startFrame, _endFrame;

	//�m�[�h�̒��g�𒲂ׂ�
	//�����FpNode		���ׂ�m�[�h
	//�����FpPartsList	�p�[�c�̃��X�g
	void CheckNode(FbxNode* pNode, std::vector<FbxParts*> *pPartsList);




public:
	Fbx();
	~Fbx();

	//���[�h
	//�����FfileName	�t�@�C����
	//�ߒl�F�����������ǂ���
	virtual HRESULT Load(std::string fileName);

	//�`��
	//�����FWorld	���[���h�s��
	void    Draw(Transform& transform, int frame, Direct3D::SHADER_TYPE shaderType);

	//���
	void    Release();

	//�C�ӂ̃{�[���̈ʒu���擾
	//�����FboneName	�擾�������{�[���̈ʒu
	//�ߒl�F�{�[���̈ʒu
	XMFLOAT3 GetBonePosition(std::string boneName);

	//���C�L���X�g�i���C���΂��ē����蔻��j
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void RayCast(RayCastData *data);

};

