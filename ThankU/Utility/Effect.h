#pragma once
#include"DxLib.h"
#include"Vector2D.h"

//�}�N����`
#define EFFECT_H
#define EFFECT_MAX 100  //�G�t�F�N�g�̍ő吔

//�}�N����` (�G�t�F�N�g�̎��)
#define EFF_EXPLODE 1   //�����G�t�F�N�g
#define EFF_CIRCLE 2

class Effect
{
public://�G�t�F�N�g�摜�n
    int imgExplosion;  // �����摜

    //1�̉摜�����ǁA��������60�A����10�����A�c��6����
    int imgHanabi;

    int eff_num;  // ���݂̃G�t�F�N�g�̐�

public:

    Effect();  // �R���X�g���N�^
    void Initialize();     //����������
    void Draw() const;  //�`�揈��
    void Update();  //�X�V����

    /// <summary>
    /// �G�t�F�N�g���Z�b�g
    /// </summary>
    /// <param name="x">X���W</param>
    /// <param name="y">Y���W</param>
    /// <param name="pattern">�G�t�F�N�g�p�^�[��</param>
    void Set(int x, int y, int pattern); 

private://�G�t�F�N�g�̏��
    struct OBJECT {
        int x;
        int y;
        int vx;
        int vy;
        int state;    // �G�t�F�N�g�̏�ԁi�A�N�e�B�u���ǂ����j
        int pattern;  // �G�t�F�N�g�̃p�^�[���i��ށj
        int image;
        int wid;
        int hei;
        int shield;    //����͗v��Ȃ����ǈꉞ
        int timer;    // �G�t�F�N�g�̎���
    };

    // �G�t�F�N�g�̔z��
    OBJECT effects[EFFECT_MAX]; 

    /// <summary>
    /// �����G�t�F�N�g�̕`��
    /// </summary>
    /// <param name="effect"></param>
    void DrawExplosion(const OBJECT& effect) const;

    void DrawCircleEffect(const OBJECT& effect) const;
};
