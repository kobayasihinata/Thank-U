#include"EffectManager.h"

EffectManager* EffectManager::Get()
{

    static EffectManager instance;
    //�������g�̃|�C���^��ԋp����
    return &instance;
}

//������
void EffectManager::Initialize()
{
    frame = 0;
    for (int i = 0; i < effect_num; i++)
    {
        EffectSpawnData kari={ 0 };
        int ka[100] = { 0 };
        //�摜�𕪊����ēǂݍ���
        LoadDivGraph(effect_image_path[i].image_path,
            effect_image_path[i].all_num,
            effect_image_path[i].x_num,
            effect_image_path[i].y_num,
            effect_image_path[i].x_size,
            effect_image_path[i].y_size,
            ka);
        //�ǂݍ��񂾉摜��std�Ɋi�[
        for (int j = 0; ka[j] != NULL; j++)
        {
            kari.image.push_back(ka[j]);
        }
        //�A�j���[�V�����X�V�p�x���i�[
        kari.anim_span = effect_image_path[i].anim_span;

        //�i�[�����l��effect_image�ɓZ�߂�
        effect_image.push_back(kari);
    }
}

void EffectManager::Finalize()
{

}

/// <summary>
/// �G�t�F�N�g���Z�b�g
/// </summary>
/// <param name="x">X���W</param>
/// <param name="y">Y���W</param>
/// <param name="pattern">�G�t�F�N�g�p�^�[��</param>
//void EffectManager::Set(int x, int y, int pattern)
//{
//
//}

//�`��
void EffectManager::Draw() const
{

}

//�X�V����
void EffectManager::Update()
{
    ////�G�t�F�N�g�̏�Ԃ��X�V
    //for (int i = 0; i < EFFECT_MAX; ++i)
    //{
    //    if (effects[i].state == 0) {
    //        continue;  // ��A�N�e�B�u�ȃG�t�F�N�g�͍X�V���Ȃ�
    //    }

    //    // �^�C�}�[���X�V���A�G�t�F�N�g�̏�Ԃ��Ǘ�
    //    effects[i].timer++;
    //    if (effects[i].timer == 7) {  // 7��X�V������G�t�F�N�g�I��
    //        effects[i].state = 0;
    //    }
    //}
    //int x = effect_image_path[0].all_num;

    //�t���[���v��
    frame++;
    ////��������Ă���I�u�W�F�N�g���Ǘ�
    //for (auto effect : effect_spawn)
    //{
    //    //�w��̊Ԋu���ɃA�j���[�V���������ɐi�߂�
    //    if (frame % effect.anim_span == 0)
    //    {
    //        //���Z��A�摜�����z������폜
    //        effect.now_image++;
    //        if (effect.now_image > effect.image.size())
    //        {
    //            for (auto it2 = effect_spawn.begin(); it2 != effect_spawn.end();)
    //            {
    //                if (*it2 == effect)
    //                {
    //                    it2 = effect_spawn.erase(it2);
    //                    break;
    //                }
    //                else
    //                {
    //                    ++it2;
    //                }
    //            }
    //        }
    //    }
    //}
}

//�����G�t�F�N�g���Ăяo��
//void EffectManager::DrawExplosion(const OBJECT& effect) const
//{
//    int ix = effect.timer * 128;  // �摜�̐؂�o���ʒu
//   // DrawRectGraph(effect.x - 64, effect.y - 64, ix, 0, 128, 128, imgExplosion, TRUE, FALSE);  // �����摜�̕`��
//}

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
