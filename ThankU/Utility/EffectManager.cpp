#include"Effect.h"

//�R���X�g���N�^
Effect::Effect() : eff_num(0), imgExplosion(0), effects()
{
}

//������
void Effect::Initialize()
{
    //�G�t�F�N�g��������
    for (int i = 0; i < EFFECT_MAX; ++i) {
        effects[i].state = 0;
    }

    // �����摜�̓ǂݍ���(��)
    imgExplosion = LoadGraph("Rescurce/Image/explosion.png");
    imgHanabi = LoadGraph("Rescurce/Image/E_PuffAndStar.png");    //�ԉ�
}

/// <summary>
/// �G�t�F�N�g���Z�b�g
/// </summary>
/// <param name="x">X���W</param>
/// <param name="y">Y���W</param>
/// <param name="pattern">�G�t�F�N�g�p�^�[��</param>
void Effect::Set(int x, int y, int pattern)
{
    //�`�悵�������W�ɃZ�b�g
    effects[eff_num].x = x;
    effects[eff_num].y = y;

    // �A�N�e�B�u��Ԃɐݒ�
    effects[eff_num].state = 1;
    effects[eff_num].pattern = pattern;

    // �^�C�}�[������
    effects[eff_num].timer = 0;

    // �ő吔�𒴂��Ȃ��悤�ɂ���
    eff_num = (eff_num + 1) % EFFECT_MAX;
}

//�`��
void Effect::Draw() const
{
    for (int i = 0; i < EFFECT_MAX; ++i)
    {
        if (effects[i].state == 0) {
            continue;  // ��A�N�e�B�u�ȃG�t�F�N�g�͕`�悵�Ȃ�
        }

        //�����Ŏ�ނ𑝂₵���肷�遃--�G�t�F�N�g�̃p�^�[��
        switch (effects[i].pattern)
        {
        case EFF_EXPLODE:
            DrawExplosion(effects[i]);  //����
            break;
        //case:EFF_CIRCLE;

        }
    }
}

//�X�V����
void Effect::Update()
{
    //�G�t�F�N�g�̏�Ԃ��X�V
    for (int i = 0; i < EFFECT_MAX; ++i)
    {
        if (effects[i].state == 0) {
            continue;  // ��A�N�e�B�u�ȃG�t�F�N�g�͍X�V���Ȃ�
        }

        // �^�C�}�[���X�V���A�G�t�F�N�g�̏�Ԃ��Ǘ�
        effects[i].timer++;
        if (effects[i].timer == 7) {  // 7��X�V������G�t�F�N�g�I��
            effects[i].state = 0;
        }
    }
}

//�����G�t�F�N�g���Ăяo��
void Effect::DrawExplosion(const OBJECT& effect) const
{
    int ix = effect.timer * 128;  // �摜�̐؂�o���ʒu
    DrawRectGraph(effect.x - 64, effect.y - 64, ix, 0, 128, 128, imgExplosion, TRUE, FALSE);  // �����摜�̕`��
}

//void Effect::DrawCircleEffect(const OBJECT& effect) const
//{
//   if (effect[i].timer < 30)
//   {
//       // ���Z�ɂ��`��̏d�ˍ��킹
//       SetDrawBlendMode(DX_BLENDMODE_ADD, effect[i].timer * 8);
//   }
//   else
//       SetDrawBlendMode(DX_BLENDMODE_ADD, (60 - effect[i].timer) * 8);
//   for (int i = 3; i < 8; i++) {
//       DrawCircle(effect.x, effect.y, (effect.x + effect.y) / i, 0x2040c0, TRUE);
//       SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �u�����h���[�h������
//       effect[i].timer++;
//       if (effect[i].timer == 60) effect[i].state = 0;
//   }
//}
