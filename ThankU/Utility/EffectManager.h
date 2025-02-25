#pragma once
#include"DxLib.h"
#include"Vector2D.h"
#include <vector>


struct EffectData
{
    char image_path[256];    //ファイルパス
    int all_num;                    //分割数
    int x_num;                      //X分割数
    int y_num;                      //Y分割数
    int x_size;                     //X大きさ
    int y_size;                     //Y大きさ
    //ここまではLoadDivGraphの引数と同じ
    int anim_span;                  //アニメーション切り替え速度
};

//エフェクトを生成するときに必要なデータ
struct EffectSpawnData
{
    int now_image;                  //現在表示している画像
    int anim_span;                  //アニメーション切り替え速度
    std::vector<int> image;         //格納先
};

enum eEffectList
{
    eExplosion = 0,
    ePuffAndStar,

    eEnd    //常に最後の要素になるようにする
};
int const effect_num = eEnd + 1;     //enumの最後の要素を格納しておく

//EffectListの順にパスを並べる(パス、画像総数、X軸画像数、Y軸画像数、画像幅、画像高さ、アニメーション切り替えスパンの順)
static EffectData effect_image_path[effect_num] =
{
    {"Rescurce/Image/Effect/explosion.png",7,7,1,128,128,10},
    {"Rescurce/Image/Effect/E_PuffAndStar.png",60,10,6,108,116,10},

    {"この文字が常に配列の最後に来るようにする",0,0,0,0,0},
};

class EffectManager
{
private://エフェクト画像系
    int frame;                                  //測定用
    std::vector<EffectSpawnData> effect_image; //アニメーションに必要な情報格納
    std::vector<EffectSpawnData> effect_spawn;  //実際に生成されているエフェクトを管理
private:
    //コンストラクタをprivateにすることで、
//自クラスのメンバ関数でインスタンスを生成できないようにする
    EffectManager() = default;

    //コピーガード
    //クラス外でインスタンスを生成して渡すことができないようにする
    EffectManager(EffectManager& v) = default;
    EffectManager& operator = (const EffectManager& v) = delete;
    ~EffectManager() = default;
public:
    //インスタンスを取得する処理
    static EffectManager* Get();

    void Initialize();     //初期化処理
    void Finalize();       //終了時処理
    void Draw() const;  //描画処理
    void Update();  //更新処理


    /// <summary>
    /// エフェクトをセット
    /// </summary>
    /// <param name="x">X座標</param>
    /// <param name="y">Y座標</param>
    /// <param name="pattern">エフェクトパターン</param>
    //void Set(int x, int y, int pattern); 

private://エフェクトの情報
    //struct OBJECT {
    //    int x;
    //    int y;
    //    int vx;
    //    int vy;
    //    int state;    // エフェクトの状態（アクティブかどうか）
    //    int pattern;  // エフェクトのパターン（種類）
    //    int image;
    //    int wid;
    //    int hei;
    //    int shield;    //これは要らないけど一応
    //    int timer;    // エフェクトの時間
    //};


    /// <summary>
    /// 爆発エフェクトの描画
    /// </summary>
    /// <param name="effect"></param>
    //void DrawExplosion(const OBJECT& effect) const;

    //void DrawCircleEffect(const OBJECT& effect) const;
};
