#include"Effect.h"

//コンストラクタ
Effect::Effect() : eff_num(0), imgExplosion(0), effects()
{
}

//初期化
void Effect::Initialize()
{
    //エフェクトを初期化
    for (int i = 0; i < EFFECT_MAX; ++i) {
        effects[i].state = 0;
    }

    // 爆発画像の読み込み(仮)
    imgExplosion = LoadGraph("Rescurce/Image/explosion.png");
    imgHanabi = LoadGraph("Rescurce/Image/E_PuffAndStar.png");    //花火
}

/// <summary>
/// エフェクトをセット
/// </summary>
/// <param name="x">X座標</param>
/// <param name="y">Y座標</param>
/// <param name="pattern">エフェクトパターン</param>
void Effect::Set(int x, int y, int pattern)
{
    //描画したい座標にセット
    effects[eff_num].x = x;
    effects[eff_num].y = y;

    // アクティブ状態に設定
    effects[eff_num].state = 1;
    effects[eff_num].pattern = pattern;

    // タイマー初期化
    effects[eff_num].timer = 0;

    // 最大数を超えないようにする
    eff_num = (eff_num + 1) % EFFECT_MAX;
}

//描画
void Effect::Draw() const
{
    for (int i = 0; i < EFFECT_MAX; ++i)
    {
        if (effects[i].state == 0) {
            continue;  // 非アクティブなエフェクトは描画しない
        }

        //ここで種類を増やしたりする＜--エフェクトのパターン
        switch (effects[i].pattern)
        {
        case EFF_EXPLODE:
            DrawExplosion(effects[i]);  //爆発
            break;
        //case:EFF_CIRCLE;

        }
    }
}

//更新処理
void Effect::Update()
{
    //エフェクトの状態を更新
    for (int i = 0; i < EFFECT_MAX; ++i)
    {
        if (effects[i].state == 0) {
            continue;  // 非アクティブなエフェクトは更新しない
        }

        // タイマーを更新し、エフェクトの状態を管理
        effects[i].timer++;
        if (effects[i].timer == 7) {  // 7回更新したらエフェクト終了
            effects[i].state = 0;
        }
    }
}

//爆発エフェクトを呼び出す
void Effect::DrawExplosion(const OBJECT& effect) const
{
    int ix = effect.timer * 128;  // 画像の切り出し位置
    DrawRectGraph(effect.x - 64, effect.y - 64, ix, 0, 128, 128, imgExplosion, TRUE, FALSE);  // 爆発画像の描画
}

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
