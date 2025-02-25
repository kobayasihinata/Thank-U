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
    for (int i = 0; i < effect_num; i++)
    {
        EffectSpawnData kari={ 0 };
        int ka[100] = { 0 };
        //画像を分割して読み込む
        LoadDivGraph(effect_image_path[i].image_path,
            effect_image_path[i].all_num,
            effect_image_path[i].x_num,
            effect_image_path[i].y_num,
            effect_image_path[i].x_size,
            effect_image_path[i].y_size,
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

/// <summary>
/// エフェクトをセット
/// </summary>
/// <param name="x">X座標</param>
/// <param name="y">Y座標</param>
/// <param name="pattern">エフェクトパターン</param>
//void EffectManager::Set(int x, int y, int pattern)
//{
//
//}

//描画
void EffectManager::Draw() const
{

}

//更新処理
void EffectManager::Update()
{
    ////エフェクトの状態を更新
    //for (int i = 0; i < EFFECT_MAX; ++i)
    //{
    //    if (effects[i].state == 0) {
    //        continue;  // 非アクティブなエフェクトは更新しない
    //    }

    //    // タイマーを更新し、エフェクトの状態を管理
    //    effects[i].timer++;
    //    if (effects[i].timer == 7) {  // 7回更新したらエフェクト終了
    //        effects[i].state = 0;
    //    }
    //}
    //int x = effect_image_path[0].all_num;

    //フレーム計測
    frame++;
    ////生成されているオブジェクトを管理
    //for (auto effect : effect_spawn)
    //{
    //    //指定の間隔毎にアニメーションを次に進める
    //    if (frame % effect.anim_span == 0)
    //    {
    //        //加算後、画像数を越したら削除
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

//爆発エフェクトを呼び出す
//void EffectManager::DrawExplosion(const OBJECT& effect) const
//{
//    int ix = effect.timer * 128;  // 画像の切り出し位置
//   // DrawRectGraph(effect.x - 64, effect.y - 64, ix, 0, 128, 128, imgExplosion, TRUE, FALSE);  // 爆発画像の描画
//}

//void Effect::DrawCircleEffect(const OBJECT& effect) const
//{
//   if (effect[i].timer < 30)
//   {
//       // 加算による描画の重ね合わせ
//       SetDrawBlendMode(DX_BLENDMODE_ADD, effect[i].timer * 8);
//   }
//   else
//       SetDrawBlendMode(DX_BLENDMODE_ADD, (60 - effect[i].timer) * 8);
//   for (int i = 3; i < 8; i++) {
//       DrawCircle(effect.x, effect.y, (effect.x + effect.y) / i, 0x2040c0, TRUE);
//       SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードを解除
//       effect[i].timer++;
//       if (effect[i].timer == 60) effect[i].state = 0;
//   }
//}
