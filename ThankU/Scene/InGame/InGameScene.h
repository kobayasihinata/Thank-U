#pragma once
#include"DxLib.h"
#include"../SceneBase.h"

class InGameScene  : public SceneBase
{
public://�v���p�e�B(�f�[�^�Q)
    class Player* Player[4];					

public:	//���\�b�h(�����Q)
    InGameScene();								//
    ~InGameScene();								//

    virtual void Initialize()	override;		//
    virtual void Finalize()		override;		//
    virtual eSceneType Update()	override;		//
    virtual void Draw() const	override;		//
    class Player* Player[4];																//player
    class Enemy* Enemy;																		//Enemy
    //���݂̃V�[�������擾
    virtual eSceneType GetNowScene() const override;
private:

};