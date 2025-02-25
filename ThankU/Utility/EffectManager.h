#pragma once
#include"DxLib.h"
#include"Vector2D.h"
#include <vector>


struct EffectData
{
    char image_path[256];    //�t�@�C���p�X
    int all_num;                    //������
    int x_num;                      //X������
    int y_num;                      //Y������
    int x_size;                     //X�傫��
    int y_size;                     //Y�傫��
    //�����܂ł�LoadDivGraph�̈����Ɠ���
    int anim_span;                  //�A�j���[�V�����؂�ւ����x
};

//�G�t�F�N�g�𐶐�����Ƃ��ɕK�v�ȃf�[�^
struct EffectSpawnData
{
    int now_image;                  //���ݕ\�����Ă���摜
    int anim_span;                  //�A�j���[�V�����؂�ւ����x
    std::vector<int> image;         //�i�[��
};

enum eEffectList
{
    eExplosion = 0,
    ePuffAndStar,

    eEnd    //��ɍŌ�̗v�f�ɂȂ�悤�ɂ���
};
int const effect_num = eEnd + 1;     //enum�̍Ō�̗v�f���i�[���Ă���

//EffectList�̏��Ƀp�X����ׂ�(�p�X�A�摜�����AX���摜���AY���摜���A�摜���A�摜�����A�A�j���[�V�����؂�ւ��X�p���̏�)
static EffectData effect_image_path[effect_num] =
{
    {"Rescurce/Image/Effect/explosion.png",7,7,1,128,128,10},
    {"Rescurce/Image/Effect/E_PuffAndStar.png",60,10,6,108,116,10},

    {"���̕�������ɔz��̍Ō�ɗ���悤�ɂ���",0,0,0,0,0},
};

class EffectManager
{
private://�G�t�F�N�g�摜�n
    int frame;                                  //����p
    std::vector<EffectSpawnData> effect_image; //�A�j���[�V�����ɕK�v�ȏ��i�[
    std::vector<EffectSpawnData> effect_spawn;  //���ۂɐ�������Ă���G�t�F�N�g���Ǘ�
private:
    //�R���X�g���N�^��private�ɂ��邱�ƂŁA
//���N���X�̃����o�֐��ŃC���X�^���X�𐶐��ł��Ȃ��悤�ɂ���
    EffectManager() = default;

    //�R�s�[�K�[�h
    //�N���X�O�ŃC���X�^���X�𐶐����ēn�����Ƃ��ł��Ȃ��悤�ɂ���
    EffectManager(EffectManager& v) = default;
    EffectManager& operator = (const EffectManager& v) = delete;
    ~EffectManager() = default;
public:
    //�C���X�^���X���擾���鏈��
    static EffectManager* Get();

    void Initialize();     //����������
    void Finalize();       //�I��������
    void Draw() const;  //�`�揈��
    void Update();  //�X�V����


    /// <summary>
    /// �G�t�F�N�g���Z�b�g
    /// </summary>
    /// <param name="x">X���W</param>
    /// <param name="y">Y���W</param>
    /// <param name="pattern">�G�t�F�N�g�p�^�[��</param>
    //void Set(int x, int y, int pattern); 

private://�G�t�F�N�g�̏��
    //struct OBJECT {
    //    int x;
    //    int y;
    //    int vx;
    //    int vy;
    //    int state;    // �G�t�F�N�g�̏�ԁi�A�N�e�B�u���ǂ����j
    //    int pattern;  // �G�t�F�N�g�̃p�^�[���i��ށj
    //    int image;
    //    int wid;
    //    int hei;
    //    int shield;    //����͗v��Ȃ����ǈꉞ
    //    int timer;    // �G�t�F�N�g�̎���
    //};


    /// <summary>
    /// �����G�t�F�N�g�̕`��
    /// </summary>
    /// <param name="effect"></param>
    //void DrawExplosion(const OBJECT& effect) const;

    //void DrawCircleEffect(const OBJECT& effect) const;
};
