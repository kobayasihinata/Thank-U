#pragma once

/*******************���їz��*************
* ���O����
* 
* SceneManager��Update�Ȃǂ́A��ɍX�V����Ă��鏊��DebugInfomation��Update���ǉ�
* ������Draw�����̕`�悪����Ă��鏊�ɒǉ��i�S�`��̌�ɕ`�悷��j
* 
* 
* �g����
* 
* DebugInfomation.h���C���N���[�h
* 		��
* Add�֐��Ɂu�\������������ , �ϐ��v��n���ČĂяo��
*		��
* ���s����X�L�[�ŕ\��
*/
#include "Vector2D.h"										
#include "Dxlib.h"											
#include "PadInput.h"										
															
#include <unordered_map>									

#define DEBUG_X 10
#define DEBUG_Y 100

class DebugInfomation
{
private:
	static std::unordered_map<const char*, float>draw_list;	//�`�悷��f�o�b�O�\���̈ꗗ
	static bool draw_flg;							//�f�o�b�O�\����`�悷�邩�ǂ���
	static bool hit_once;							//�L�[���͂Ɉ�񂾂���������
public:
	//�X�V
	static void Update();
	//�f�o�b�O�\���̕`��
	static void Draw();
	//�f�o�b�O�\����ǉ�����
	static void Add(const char* _c, float _num);
	static void Add(const char* _c, int _num);
	static void Add(const char* _c, bool _num);
};



