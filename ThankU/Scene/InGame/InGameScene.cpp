#include "InGameScene.h"

/// <summary>
///�@�C���X�g���N�^
/// </summary>
/// <param></param>
/// <returns></returns>
InGameScene::InGameScene()
{
	//�v���C���[�̏��̏�����
	Player[0] = nullptr;
	Player[1] = nullptr;
	Player[2] = nullptr;
	Player[3] = nullptr;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <param></param>
/// <returns></returns>
InGameScene::~InGameScene()
{
}

/// <summary>
/// �J�n������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Initialize()
{
}

/// <summary>
/// �I��������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Finalize()
{
}

/// <summary>
/// �Q�[����ʂ̕`�������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Draw() const
{
	
}

/// <summary>
/// �P�폈��
/// </summary>
/// <param></param>
/// <returns>���݂̃V�[����ԋp</returns>
eSceneType InGameScene::Update()
{
	/*��	Enemy�֘A	��*/
	//Enemy����₢������Ⴄ

	//Enemy���瓚�����󂯎��


	/*��	Enemy�֘A	��*/
	//Enemy����󂯎����������player�炪�����Ă铚�����r����
	if (0)
	{
		//�����̏ꍇ

	}
	else
	{
		//�s�����̏ꍇ
	}
	/*������𗘗p����ƁA���U���g��ʂɕΈڂ���B*/
	//return eSceneType::E_RESULT; 
	
	
	return eSceneType::E_INGAME;
}


/// <summary>
/// ���݂̃V�[�����̕ԋp
/// </summary>
/// <param></param>
/// <returns>���݂̃V�[������ԋp</returns>
eSceneType InGameScene::GetNowScene() const
{
	return eSceneType::E_INGAME;
}
