#pragma once
#include <list>
#include "Direct3D.h"
#include "Texture.h"
#include <DirectXMath.h>
#include <string>
using namespace DirectX;
using namespace std;

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMFLOAT4	color;
};

//���_���
struct VERTEX
{
	XMFLOAT3 position;
	XMFLOAT3 uv;
};

class PoryLine
{
	const float WIDTH_;		//����
	const int LENGTH_;		//����

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;	//�摜


	list<XMFLOAT3> positions_;	//�ߋ�length_�񕪂̈ʒu

public:
	//�R���X�g���N�^
	PoryLine();

	//���݂̈ʒu���L��������
	//�����Fpos	���݂̈ʒu
	void AddPosition(XMFLOAT3 pos);

	void AddPositionW(XMFLOAT3 pos);

	void AddPositionX(XMFLOAT3 pos);

	//���[�h
	//�����FfileName	�摜�t�@�C����
	//�ߒl�F����/���s
	HRESULT Load(std::string fileName);

	//�`��
	void Draw();

	//�`��F�w��o�[�W����
	void Draw(XMFLOAT4 color);

	//���
	void Release();

};

