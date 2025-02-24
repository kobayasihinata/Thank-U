#pragma once
#include"DxLib.h"
#include"../SceneBase.h"
#include "../../Utility/Vector2D.h"

class ResultScene : public SceneBase
{
public://�v���p�e�B(�f�[�^�Q)
	int frame;		//�t���[�����ԑ���

	//�摜�p�ϐ�
	int bar_image;			//���̃o�[
	Vector2D score_location[4];	//�X�R�A�\���̍��W	
	Vector2D winner_draw;		//���҂̕`��ʒu

public:	//���\�b�h(�����Q)
	ResultScene();													//�C���X�g���N�^�[
	~ResultScene();													//�f�X�g���N�^�[

	virtual void Initialize()	override;							//�N��������
	virtual void Finalize()		override;							//�I��������
	virtual eSceneType Update()	override;							//�P�폈��
	virtual void Draw() const	override;							//�`�揈��


	//���݂̃V�[�������擾
	virtual eSceneType GetNowScene() const override;
};