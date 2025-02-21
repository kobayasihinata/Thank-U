#pragma once
#include"DxLib.h"
#include"../SceneBase.h"

class InGameScene  : public SceneBase
{
public://�v���p�e�B(�f�[�^�Q)
	class Player* Player[4];					

public:	//���\�b�h(�����Q)
	InGameScene();								//�C���X�g���N�^�[
	~InGameScene();								//�f�X�g���N�^�[

	virtual void Initialize()	override;		//�N��������
	virtual void Finalize()		override;		//�I��������
	virtual eSceneType Update()	override;		//�P�폈��
	virtual void Draw() const	override;		//�`�揈��
	class Player* Player[4];																//player
	class Enemy* Enemy;																		//Enemy


public:	//���\�b�h(�����Q)
	InGameScene();																			//�C���X�g���N�^�[
	~InGameScene();																			//�f�X�g���N�^�[

	virtual void Initialize()		override;												//�N��������
	virtual void Finalize()			override;													//�P�폈��
	virtual void Draw() const		override;											//�I��������
	virtual eSceneType Update()		override;												//�`�揈��


	//���݂̃V�[�������擾
	virtual eSceneType GetNowScene() const override;
private:

};