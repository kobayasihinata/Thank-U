#pragma once
#include"DxLib.h"
#include"../SceneBase.h"

class InGameScene  : public SceneBase
{
public://�v���p�e�B(�f�[�^�Q)
	class Player* Player[4];										//player
public:	//���\�b�h(�����Q)
	InGameScene();													//�C���X�g���N�^�[
	~InGameScene();													//�f�X�g���N�^�[

	void Initialize();												//�N��������
	void Finalize();												//�I��������
	void Update();													//�P�폈��
	void Draw();													//�`�揈��


private:

};