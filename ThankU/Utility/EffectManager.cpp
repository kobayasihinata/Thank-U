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
    for (int i = 0; i < effect_num-1; i++)
    {
        EffectSpawnData kari={ 0 };
        int ka[100] = { 0 };
        int im, w, h;

        //���ǂݍ���ŁA�����ƕ����擾����
        im = LoadGraph(effect_image_path[i].image_path);
        GetGraphSize(im,&w, &h);

        //����������ɁA�ꕪ��������̕��A���������߂�
        w /= effect_image_path[i].x_num;
        h /= effect_image_path[i].y_num;

        //�摜�𕪊����ēǂݍ���
        LoadDivGraph(effect_image_path[i].image_path,
            effect_image_path[i].all_num,
            effect_image_path[i].x_num,
            effect_image_path[i].y_num,
            w,
            h,
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

//�`��
void EffectManager::Draw() const
{
    //��������Ă���I�u�W�F�N�g���Ǘ�
    for (const auto& effect : effect_list)
    {
        DrawGraph(effect.location.x, effect.location.y, effect.image[effect.now_image], TRUE);
    }
}

//�X�V����
void EffectManager::Update()
{
    //�t���[���v��
    frame++;

    //��������Ă���I�u�W�F�N�g���Ǘ�
    for (auto& effect : effect_list)
    {
        //�w��̊Ԋu���ɃA�j���[�V���������ɐi�߂�
        if (frame % effect.anim_span == 0)
        {
            //���Z
            effect.now_image++;
            //�摜��\������������폜�Ώۃ��X�g�ɒǉ�
            if (effect.now_image >= effect.image.size())
            {
                delete_list.push_back(effect);
            }
        }
    }

    //�I�u�W�F�N�g�z�񂩂�폜���鏈��
    for (const auto& delete_object : delete_list)
    {
        for (auto it = effect_list.begin(); it != effect_list.end();)
        {
            if (*it == delete_object)
            {

                it = effect_list.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }
    }
    //�폜�����I�u�W�F�N�g�͏���
    delete_list.clear();
}

void EffectManager::SpawnEffect(Vector2D _loc, eEffectList _type)
{
    EffectSpawnData kari;
    //�K�v�����i�[
    kari = effect_image[_type];
    //���W���i�[
    kari.location = _loc;
    //����
    effect_list.push_back(kari);
}