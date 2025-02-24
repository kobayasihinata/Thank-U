#pragma once
#include"DxLib.h"
#include"../SceneBase.h"
#include "../../Utility/Vector2D.h"

#define WINNER_DRAW_TIME 150

class ResultScene : public SceneBase
{
public://�v���p�e�B(�f�[�^�Q)
	int frame;					//�t���[�����ԑ���
	Vector2D score_location[4];	//�X�R�A�\���̍��W	
	Vector2D winner_draw;		//���҂̕`��ʒu
	int result_num;				//���l���`�撆��
	bool result_draw_flg;		//�X�R�A�����ׂĕ\���o���������f
	int winner_draw_time;		//���ʔ��\�܂ł̒���
	int winner_num;				//������ʂ̐l��
	
	//�摜�p�ϐ�
	int bar_image;			//���̃o�[

	//�����p�ϐ�
	int talk_se;			//�������o���Ƃ���SE
	int drum_se;			//�h�������[��SE
	int winner_se;			//���҂�SE
	int result_bgm;			//BGM

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
	int CheckWinnerNum()const;		//��ԑ傫���X�R�A�����m

	void DrawWinner()const;			//���҂�`��
};