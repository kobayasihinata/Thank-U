#pragma once
#include"DxLib.h"
#include"../SceneBase.h"

class ResultScene : public SceneBase
{
public://�v���p�e�B(�f�[�^�Q)
	int result_image;	//�^�C�g���摜�i�[
public:	//���\�b�h(�����Q)
	ResultScene();													//�C���X�g���N�^�[
	~ResultScene();													//�f�X�g���N�^�[

	virtual void Initialize()	override;							//�N��������
	virtual void Finalize()		override;							//�I��������
	virtual eSceneType Update()	override;							//�P�폈��
	virtual void Draw() const	override;							//�`�揈��


	//���݂̃V�[�������擾
	virtual eSceneType GetNowScene() const override;
private:

};