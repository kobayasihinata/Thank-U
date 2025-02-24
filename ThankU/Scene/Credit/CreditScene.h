#pragma once
#include"DxLib.h"
#include"../SceneBase.h"
#include   "../../Utility/Common.h"

class CreditScene : public SceneBase
{
public://�v���p�e�B(�f�[�^�Q)
	int count = 3600;	//��莞�Ԍo�߂ŏI��
	int scrollY = SCREEN_HEIGHT; // Starting Y position

private:
	int background_image;
	int object_image[5];

public:	//���\�b�h(�����Q)
	CreditScene();													//�C���X�g���N�^�[
	~CreditScene();													//�f�X�g���N�^�[

	virtual void Initialize()	override;							//�N��������
	virtual void Finalize()		override;							//�I��������
	virtual eSceneType Update()	override;							//�P�폈��
	virtual void Draw() const	override;							//�`�揈��


	//���݂̃V�[�������擾
	virtual eSceneType GetNowScene() const override;
private:

};