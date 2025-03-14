#pragma once
#include"DxLib.h"
#include"Vector2D.h"
#include <vector>


struct EffectData
{                                                     //作者
    char image_path[256];            //ファイルパス      小
    int all_num;                    //分割数             林
    int x_num;                      //X分割数            陽
    int y_num;                      //Y分割数            向

    //ここまではLoadDivGraphの引数と同じ(画像幅、高さは勝手に計算するので入れなくていい)
    int anim_span;                  //アニメーション切り替え速度
};

//エフェクトを生成するときに必要なデータ
struct EffectSpawnData
{
    Vector2D location;              //座標(左上)
    int now_image;                  //現在表示している画像
    int anim_span;                  //アニメーション切り替え速度
    std::vector<int> image;         //格納先

    //↓アニメーションが移動する場合は使用する
    Vector2D velocity;              //移動量

    //↓アニメーションに生存時間があるなら使用する
    int life_time;                  //生存時間

    //等価演算子のオーバーロード
    bool operator==(const EffectSpawnData& other) const {
        return (now_image == other.now_image) && (anim_span == other.anim_span) && (image == other.image);
    }
};

/******************************************************************************
*   ↓新しいエフェクト入れるときとアニメーション速度変える時にいじるゾーン↓  *
******************************************************************************/
enum eEffectList
{
    eExplosion = 0,
    ePuffAndStar,
    eAnima,
    eBighit,
    eBloodImpact,
    eImpact,
    eStarRed,
    eStarOrange,
    eStarYellow,
    eStarGreen,
    eStarLightBlue,
    eStarBlue,
    eStarPurple,
    eStarPink,
    eStarWhite,
    eStarBlack,

    eEnd    //常に最後の要素になるようにする
};
int const effect_num = eEnd + 1;     //enumの最後の要素を格納しておく

//EffectListの順にパスを並べる(パス、画像総数、X軸画像数、Y軸画像数、アニメーション切り替えスパンの順)
static EffectData effect_image_path[effect_num] =
{
    {"Rescurce/Image/Effect/explosion.png",     7,7,1,5},
    {"Rescurce/Image/Effect/E_PuffAndStar.png", 60,10,8,1},
    {"Rescurce/Image/Effect/E_Anima.png",       63,9,7,1},
    {"Rescurce/Image/Effect/E_BigHit_2.png",    27,9,3,1},
    {"Rescurce/Image/Effect/E_BloodImpact.png", 63,9,7,1},
    {"Rescurce/Image/Effect/E_Impact_1.png",    27,9,3,1},
    {"Rescurce/Image/Effect/star_red.png",      20,5,4,1},
    {"Rescurce/Image/Effect/star_orange.png",   20,5,4,1},
    {"Rescurce/Image/Effect/star_yellow.png",   20,5,4,1},
    {"Rescurce/Image/Effect/star_green.png",    20,5,4,1},
    {"Rescurce/Image/Effect/star_lightBlue.png",20,5,4,1},
    {"Rescurce/Image/Effect/star_blue.png",     20,5,4,1},
    {"Rescurce/Image/Effect/star_purple.png",   20,5,4,1},
    {"Rescurce/Image/Effect/star_pink.png",     20,5,4,1},
    {"Rescurce/Image/Effect/star_white.png",    20,5,4,1},
    {"Rescurce/Image/Effect/star_black.png",    20,5,4,1},

    {"この文字が常に配列の最後に来るようにする",0,0,0,0},
};
/********************************************************************************
*   ↑新しいエフェクト入れるときとアニメーション速度変える時にいじるゾーン↑    *
*********************************************************************************/
class EffectManager
{
private://エフェクト画像系
    int frame;                                  //測定用
    std::vector<EffectSpawnData> effect_image; //アニメーションに必要な情報格納
    std::vector<EffectSpawnData> effect_list;  //実際に生成されているエフェクトを管理
    std::vector<EffectSpawnData> delete_list;  //削除するべきエフェクトを管理

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

    void Initialize();   //初期化処理
    void Finalize();     //終了時処理
    void Draw() const;   //描画処理
    void Update();       //更新処理

    /// <summary>
    /// エフェクト生成
    /// </summary>
    /// <param name="_loc">座標</param>
    /// <param name="type">生成するエフェクトの種類</param>
    /// <param name="_velocity">移動量（移動するなら）</param>
    /// <param name="_life_time">生存時間</param>
    void SpawnEffect(Vector2D _loc, eEffectList _type,Vector2D _velocity = 0, int _life_time = 0);

};
