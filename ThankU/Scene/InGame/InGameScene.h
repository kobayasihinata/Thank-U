#pragma once
#include"DxLib.h"
#include"../SceneBase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

enum agreement :int
{
    positive     = 1,
    negation     = 2,
    question     = 3,
    excitement   = 4
};

class InGameScene  : public SceneBase
{
public:
    vector<vector<string>> EnemyString;

    agreement FatalAnser;
    agreement Player_Anser[4];
    string Question;
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

    int PlayerAnser();

    //ーー以下は全て記述済みーー//

    void EnemyAnser();
    void EnemyAsk();
    //csvの読み取り
    vector<vector<string>>read_csv(const string& filename);
private:

};