#pragma once
#include"DxLib.h"
#include"../SceneBase.h"

class TitleScene : public SceneBase
{
private:
	int key;	//�f�o�b�O�p(�V�[���؂�ւ�)

public://�v���p�e�B(�f�[�^�Q)

public:	//���\�b�h(�����Q)
	TitleScene();													//�C���X�g���N�^�[
	~TitleScene();													//�f�X�g���N�^�[

	virtual void Initialize()	override;												//�N��������
	virtual void Finalize()		override;												//�I��������
	virtual eSceneType Update()	override;												//�P�폈��
	virtual void Draw() const	override;												//�`�揈��


	//���݂̃V�[�������擾
	virtual eSceneType GetNowScene() const override;
private:

};