#pragma once
#include"DxLib.h"
#include"../SceneBase.h"
#include "../../Utility/Common.h"
#include "../../Utility/Effect.h"

class CreditScene : public SceneBase
{
private://�G�t�F�N�g�֘A
	//�����ɃG�t�F�N�g�̃����_���v�Z�Ƃ��J�E���g�Ɏg���ϐ��Ƃ���錾

public://�v���p�e�B(�f�[�^�Q)

	int count;	//��莞�Ԍo�߂ŏI��
	int scrollY; //�X�N���[�������ʒu

public:
	//�G�t�F�N�g���g�p����ەK�v
	Effect effect;

private:
	int background_image;	//�w�i
	int credit_logo;		//���S
	int object_image[5];	//�e�I�u�W�F�N�g

public:	//���\�b�h(�����Q)
	CreditScene();			//�C���X�g���N�^�[
	~CreditScene();			//�f�X�g���N�^�[

	virtual void Initialize()	override;	//�N��������
	virtual void Finalize()		override;	//�I��������
	virtual eSceneType Update()	override;	//�P�폈��
	virtual void Draw() const	override;	//�`�揈��


	//���݂̃V�[�������擾
	virtual eSceneType GetNowScene() const override;
private:

};