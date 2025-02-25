#pragma once
#include"DxLib.h"
#include"Vector2D.h"

//マクロ定義
#define EFFECT_H
#define EFFECT_MAX 100  //エフェクトの最大数

//マクロ定義 (エフェクトの種類)
#define EFF_EXPLODE 1   //爆発エフェクト
#define EFF_CIRCLE 2

class Effect
{
public://エフェクト画像系
    int imgExplosion;  // 爆発画像

    //1つの画像だけど、総分割数60、横に10分割、縦に6分割
    int imgHanabi;

    int eff_num;  // 現在のエフェクトの数

public:

    Effect();  // コンストラクタ
    void Initialize();     //初期化処理
    void Draw() const;  //描画処理
    void Update();  //更新処理

    /// <summary>
    /// エフェクトをセット
    /// </summary>
    /// <param name="x">X座標</param>
    /// <param name="y">Y座標</param>
    /// <param name="pattern">エフェクトパターン</param>
    void Set(int x, int y, int pattern); 

private://エフェクトの情報
    struct OBJECT {
        int x;
        int y;
        int vx;
        int vy;
        int state;    // エフェクトの状態（アクティブかどうか）
        int pattern;  // エフェクトのパターン（種類）
        int image;
        int wid;
        int hei;
        int shield;    //これは要らないけど一応
        int timer;    // エフェクトの時間
    };

    // エフェクトの配列
    OBJECT effects[EFFECT_MAX]; 

    /// <summary>
    /// 爆発エフェクトの描画
    /// </summary>
    /// <param name="effect"></param>
    void DrawExplosion(const OBJECT& effect) const;

    void DrawCircleEffect(const OBJECT& effect) const;
};
