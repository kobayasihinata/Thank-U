#include "InGameScene.h"

/// <summary>
///　インストラクタ
/// </summary>
/// <param></param>
/// <returns></returns>
InGameScene::InGameScene()
{
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param></param>
/// <returns></returns>
InGameScene::~InGameScene()
{
}

/// <summary>
/// 開始時処理
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Initialize()
{
}

/// <summary>
/// 終了時処理
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Finalize()
{
}

/// <summary>
/// ゲーム画面の描画をする
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Draw() const
{
	
}

/// <summary>
/// 恒常処理
/// </summary>
/// <param></param>
/// <returns>現在のシーンを返却</returns>
eSceneType InGameScene::Update()
{
	/*↓	Enemy関連	↓*/
	//Enemyから問いかけを貰う

	//Enemyから答えを受け取る


	/*↑	Enemy関連	↑*/
	//Enemyから受け取った答えとplayerらが言ってる答えを比較する
	if (0)
	{
		//正解の場合

	}
	else
	{
		//不正解の場合
	}
	/*↓これを利用すると、リザルト画面に偏移する。*/
	//return eSceneType::E_RESULT; 
	
	
	return eSceneType::E_INGAME;
}


/// <summary>
/// 現在のシーン情報の返却
/// </summary>
/// <param></param>
/// <returns>現在のシーン名を返却</returns>
eSceneType InGameScene::GetNowScene() const
{
	return eSceneType::E_INGAME;
}


void InGameScene::EnemyAnser()
{
	switch (GetRand(4) + 1)
	{
	case 0:
		FatalAnser = agreement::positive;
		break;
	case 1:
		FatalAnser = agreement::negation;
		break;
	case 2:
		FatalAnser = agreement::question;
		break;
	case 3:
		FatalAnser = agreement::excitement;
		break;
	}
}
