#pragma once
#include"DxLib.h"
#include "../../Utility/Data.h"
#include"../SceneBase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>



enum agreement :int
{
    none = 0,           //未回答
    positive = 1,       //肯定
    negation = 2,       //否定
    question = 3,       //疑問
    excitement = 4    //盛り上げ
};

//stdの記入を省略(詳細省略)
using namespace std;

class InGameScene  : public SceneBase
{
public://データ
    //--画像類--//
    //敵の吹き出し
    int EnemyImage;
    //敵の吹き出し
    int EnemyTextImage;
    //プレイヤ―の吹き出し
    int PlayerImage[4];

    //プレイヤ―の文字吹き出し
    int PlayerTextImage;
    //背景の画像
    int Background_image;
    //下のライン画像
    int Border_Line;
    //失敗時の画像
    int false_Message;
    //操作方法の画像
    int InGameHelp;
    //正解時の演出画像(1)
    int Collect1st_Image;
    //正解時の演出画像(2)
    int Collect2nd_Image;
    //不正解時の演出画像
    int Bad_Image;
    //SE類
    //SE＿正解
    int SE_Correct;
    //SE＿不正解
    int SE_MessageDelete;
    //SE＿メッセージ表示
    int SE_Talk;
//    //-Enemy関連-//
    //csvファイルを読み込んで保存する領域
    vector<vector<string>> EnemyString;   
    //正解
    agreement FatalAnser;
    //正解の添え字
    int FatalAnserNum;                          
    //質問文
    string Question;                            

    //プレイヤーの回答順(正誤問わず)
    vector<int> PlaySeter;

    //プレイヤーのセリフ
    vector<string> PString;

    //プレイヤーの回答
    int Pagree[4];

    //プレイヤー入力保存領域
    agreement Player_Anser[4];

    //全体に配分する合計スコアポイント
    int TotalScore;             

    //スコアの倍率
    int ScoreValue[4];

    //ループ時の１度だけ通すための変数
    bool QSet;

    //回答したかどうか
    bool Anserd[4];

    //正解したかどうか(falseならそもそも表示されない)
    bool Collect[4];

    //未回答含む正誤どちらか(回答状況が不明で、Anserdを組み合わせた凡長なif文になるのを嫌った)
    int right[4];

    //フレーム単位の時間
    float TimeCountUp;

    //実際に経過した時間
    int Timer;

 //追加された点数と表示位置
    int addscore[2][4];    
public:
    //インストラクタ
    InGameScene();
    //デストラクタ
    ~InGameScene();

    //イニシャライズ
    virtual void Initialize()	            override;
    //ファイナライズ
    virtual void Finalize()		            override;
    //恒常処理
    virtual eSceneType Update()	            override;
    //描画処理
    virtual void Draw() const	            override;
    //現在のシーン情報
    virtual eSceneType GetNowScene() const override;                                       


    
    //プレイヤーの回答を探索
    int PlayerAnser();
    //プレイヤーのスコア倍率をセット
    void SetPoint();
    //正誤確認
    void CheckAnser();

    //ーー以下は全て記述済みーー//

    //エネミーの回答を設定
    void EnemyAnser();
    //質問文のセット
    void EnemyAsk();
    //csvの読み取り
    vector<vector<string>>read_csv(const string& filename);
    //時間の経過
    void TimerCount();

};