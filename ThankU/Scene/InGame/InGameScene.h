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
    //プレイヤ―の吹き出し
    int PlayerTextImage;
    //背景の画像
    int Background_image;                       //背景
    //下のライン
    int Border_Line;
    int false_Message;
    int InGameHelp;
    //SE類
    int SE_Correct;
    int SE_Talk;
    int SE_MessageDelete;
    //-Enemy関連-//
    vector<vector<string>> EnemyString;         //csvファイルを読み込んで保存する領域
    agreement FatalAnser;                       //正解
    int FatalAnserNum;                          //正解の添え字
    string Question;                            //質問文

    vector<int> PlaySeter;
    vector<string> PString;
    int Pagree[4];
    agreement Player_Anser[4];                  //プレイヤー入力保存領域
    int PlayerScore[4];                         //仮置き
    int TotalScore;                      //全体に配分する合計スコアポイント
    int ScoreValue[4];

    bool QSet;
    bool Anserd[4];
    bool Collect[4];

    float TimeCountUp;
    int Timer;

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

    void SetPoint();

    void CheckAnser();

    //ーー以下は全て記述済みーー//

    //エネミーの回答を設定
    void EnemyAnser();
    //質問文のセット
    void EnemyAsk();
    //csvの読み取り
    vector<vector<string>>read_csv(const string& filename);

    void TimerCount();

};