#pragma once

//�V�[�����
enum eSceneType
{
	E_TITLE,	//�^�C�g�����
	E_INGAME,	//�C���Q�[�����
	E_RESULT,	//���U���g���
	E_CREDIT,	//�N���W�b�g���
	E_END		//�G���h
};

//���V�[���N���X
class SceneBase
{
public:
	SceneBase() {}	//�R���X�g���N�^
	virtual ~SceneBase() {}	//�f�X�g���N�^

public:
	//����������
	virtual void Initialize() {}

	//�X�V����
	virtual eSceneType Update(){ return GetNowScene();}

	//�`�揈��
	virtual void Draw() const {}

	//�I��������
	virtual void Finalize() {}

	//���݂̃V�[�������擾
	virtual eSceneType GetNowScene() const = 0;
};