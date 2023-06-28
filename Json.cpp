#include "Json.h"
#include <Windows.h>

nlohmann::json Json::Load(std::string fileName)
{
    //JSON�f�[�^��ǂݍ��ނ��߂̃t�@�C���X�g���[�����쐬
    std::ifstream file(fileName);

    // �t�@�C��������ɃI�[�v�����ꂽ�����m�F
    if (!file.is_open()) {
        MessageBox(NULL, "JSON�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B", "FAIL", MB_OK);
    }

    // JSON�f�[�^���i�[���邽�߂̕ϐ�
    nlohmann::json data;

    // JSON�t�@�C�����p�[�X���ăf�[�^���擾
    file >> data;

    // �t�@�C�����N���[�Y
    file.close();
    return data;
}
