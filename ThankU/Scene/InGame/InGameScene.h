#pragma once
#include"DxLib.h"
#include"../SceneBase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../../Utility/Data.h"

//stdの記入を省略(詳細省略)
using namespace std;

enum agreement :int
{
    none         = 0,   //未回答
    positive     = 1,   //肯定
    negation     = 2,   //否定
    question     = 3,   //疑問
    excitement   = 4    //盛り上げ
};

class InGameScene  : public SceneBase
{
public://データ
    vector<vector<string>> EnemyString;         //csvファイルを読み込んで保存する領域
    agreement FatalAnser;                       //正解
    int FatalAnserNum;
    int EnemyImage;
    int PlayerImage;
    int Background_image;                       //背景
    agreement Player_Anser[4];                  //プレイヤー入力保存領域
    string Question;                            //質問文
    int PlayerScore[4];                         //仮置き
    int TotalScore;                             //全体に配分する合計スコアポイント
    PlayerData PD1{};
    PlayerData PD2{};
    PlayerData PD3{};
    PlayerData PD4{};


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

    //ーー以下は記述必須ーー//
    
    //プレイヤーの回答を探索
    int PlayerAnser();

    //ーー以下は全て記述済みーー//

    //エネミーの回答を設定
    void EnemyAnser();
    //質問文のセット
    void EnemyAsk();
    //csvの読み取り
    vector<vector<string>>read_csv(const string& filename);

};