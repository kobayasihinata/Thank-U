#include"EffectManager.h"

EffectManager* EffectManager::Get()
{

    static EffectManager instance;
    //自分自身のポインタを返却する
    return &instance;
}

//初期化
void EffectManager::Initialize()
{
    frame = 0;
    for (int i = 0; i < effect_num-1; i++)
    {
        EffectSpawnData kari={ 0 };
        int ka[100] = { 0 };
        int im, w, h;

        //一回読み込んで、高さと幅を取得する
        im = LoadGraph(effect_image_path[i].image_path);
        GetGraphSize(im,&w, &h);

        //分割数を基に、一分割当たりの幅、高さを求める
        w /= effect_image_path[i].x_num;
        h /= effect_image_path[i].y_num;

        //画像を分割して読み込む
        LoadDivGraph(effect_image_path[i].image_path,
            effect_image_path[i].all_num,
            effect_image_path[i].x_num,
            effect_image_path[i].y_num,
            w,
            h,
            ka);

        //読み込んだ画像をstdに格納
        for (int j = 0; ka[j] != NULL; j++)
        {
            kari.image.push_back(ka[j]);
        }

        //アニメーション更新頻度を格納
        kari.anim_span = effect_image_path[i].anim_span;

        //格納した値をeffect_imageに纏める
        effect_image.push_back(kari);
    }
}

void EffectManager::Finalize()
{

}

//描画
void EffectManager::Draw() const
{
    //生成されているオブジェクトを管理
    for (const auto& effect : effect_list)
    {
        DrawGraph(effect.location.x, effect.location.y, effect.image[effect.now_image], TRUE);
    }
}

//更新処理
void EffectManager::Update()
{
    //フレーム計測
    frame++;

    //生成されているオブジェクトを管理
    for (auto& effect : effect_list)
    {
        //指定の間隔毎にアニメーションを次に進める
        if (frame % effect.anim_span == 0)
        {
            //加算
            effect.now_image++;
            //画像を表示しきったら削除対象リストに追加
            if (effect.now_image >= effect.image.size())
            {
                delete_list.push_back(effect);
            }
        }
    }

    //オブジェクト配列から削除する処理
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
    //削除したオブジェクトは消去
    delete_list.clear();
}

void EffectManager::SpawnEffect(Vector2D _loc, eEffectList _type)
{
    EffectSpawnData kari;
    //必要情報を格納
    kari = effect_image[_type];
    //座標を格納
    kari.location = _loc;
    //生成
    effect_list.push_back(kari);
}