#pragma once
#include"DxLib.h"
#include"../SceneBase.h"

enum agreement :int
{
    positive = 1,
    negation,
    question,
    excitement
};

class InGameScene  : public SceneBase
{
public:
    agreement FatalAnser;
    agreement PlayerAnser[4];
public:
    InGameScene();								                                            //インストラクタ
    ~InGameScene();								                                            //デストラクタ

    virtual void Initialize()	            override;		                                //イニシャライズ
    virtual void Finalize()		            override;		                                //ファイナライズ
    virtual eSceneType Update()	            override;		                                //恒常処理
    virtual void Draw() const	            override;		                                //描画処理

    virtual eSceneType GetNowScene() const override;                                        //現在のシーン情報

    void EnemyAnser();
private:

};