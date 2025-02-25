#pragma once
#include"DxLib.h"
#include   "../../Utility/Common.h"
#include   "../../Utility/Vector2D.h"
#include"../SceneBase.h"

//�^�C�g���V�[���N���X
class TitleScene : public SceneBase
{
private:
	//�e�摜
	int cursor;				//���j���[�J�[�\��
	int title_image;		//�^�C�g���w�i
	int title_logo;			//�^�C�g�����S
	int object_image[13];	//�I�u�W�F�N�g
	int message_image[10];	//���b�Z�[�W�摜

	int random_image_timer = 0; // �^�C�}�[�ϐ��̏�����
	int current_image_index = rand() % 9; // �����_���ȉ摜�̏����I��

private:
	//�I�u�W�F�N�g�Ǘ��p�ϐ�
	float message_x;		//���b�Z�[�W�A�C�R���� X �ʒu
	float scale;			//�傫��
	bool scaling_up;		//�X�P�[����傫�����邩���������邩�̃t���O ��-- �����g��Ȃ�
	Vector2D obj_location;	//�I�u�W�F�N�g�̍��W

private: //��--�Q���l���������Ō��߂�̂���΃p�u���b�N�̕���������������Ȃ�

	float player_icon_x[4]; //�Q���҃A�C�R���� X �ʒu
	bool player_join[4];	//�Q���t���O
	int join_flag;	//�`��p�t���O

private:
	//�G�t�F�N�g�p	��--�G�t�F�N�g���l�A�p�[�e�B�N���̃N���X��������������K�v�ɂȂ邩��

	int alpha;				// �t�F�[�h�C���p�̃A���t�@�l
	int fadein_timer;		// �t�F�[�h�C���̃^�C�}�[

public:	//���\�b�h(�����Q)
	TitleScene();													//�C���X�g���N�^�[
	~TitleScene();													//�f�X�g���N�^�[

	virtual void Initialize()	override;	//����������
	virtual void Finalize()		override;	//�I��������
	virtual eSceneType Update()	override;	//�X�V����
	virtual void Draw() const	override;	//�`�揈��

	//���݂̃V�[�������擾
	virtual eSceneType GetNowScene() const override;

private:
	//�I�u�W�F�N�g�̉��o����
	void ObjectMove();

	//���̃R���g���[���[�����ɃQ�[���ɎQ�����Ă��邩�擾 
	//_pad=�m�F����R���g���[���[ �߂�l �g���Ă���v���C���[(-1�͒N���g���Ă��Ȃ�)
	int CheckUseController(int _pad);

};