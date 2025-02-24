#include "InGameScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"

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
	EnemyString = read_csv("EnemyQ.csv");
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
	//後々いじりますわ
}

/// <summary>
/// 恒常処理
/// </summary>
/// <param></param>
/// <returns>現在のシーンを返却</returns>
eSceneType InGameScene::Update()
{	

#if _DEBUG
	KeyInput* key_input = KeyInput::Get();

	if (PadInput::GetButton(DX_INPUT_PAD1, PAD_INPUT_B)|| key_input->GetKeyState(KEY_INPUT_UP) == eInputState::Pressed)
	{
		/*↓これを利用すると、リザルト画面に偏移する。*/
		return eSceneType::E_RESULT; 
	}
#endif // _DEBUG

	/*	Enemy関連(2つとも記載済みのため、関数呼び出しのみ)	*/
	{
		//Enemyから問いかけを貰う

		//Enemyから答えを受け取る

	}
	/*player関連^-_-^おそらくループ*/
	{
		//入力に応じた処理
		PlayerAnser();
		//全員入力する または 指定時間過ぎる(要勉強)

	}

	//Enemyから受け取った答えとplayerらが言ってる答えを比較する
	if (0/*?*/)
	{
		//正解の場合
		//scoreを正答したプレイヤーに加算

	}
	else//不正解の場合
	{
		//今回は誤答ペナルティが存在しないので、特筆すべき処理は無し

	}
	
	//指定ポイント分配しきったら
	/*----
	↓これを利用して、リザルト画面に偏移する。
	//return eSceneType::E_RESULT;
	----*/
	
	return eSceneType::E_INGAME;
}


/// <summary>
/// 現在のシーン情報を返却
/// </summary>
/// <param></param>
/// <returns>現在のシーン情報</returns>
eSceneType InGameScene::GetNowScene() const
{
	return eSceneType::E_INGAME;
}

int InGameScene::PlayerAnser()
{
	for (int i = 0; i < 4; i++)
	{
		//playerの押したボタンに応じて回答を当てはめる
		switch (PadInput::GetButton(i, PAD_INPUT_B))//←仮置き)
		{
		default:
			break;
		}
	}
	return 0;
}

///--		*	*	*	*	*	Enemy関連	*	*	*	*	*	--///

/// <summary>
/// Enemyの答え決め
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::EnemyAnser()
{
	switch (GetRand(4) + 1)
	{
	case 1:
		FatalAnser = agreement::positive;
		break;
	case 2:
		FatalAnser = agreement::negation;
		break;
	case 3:
		FatalAnser = agreement::question;
		break;
	case 4:
		FatalAnser = agreement::excitement;
		break;
	}
}


/// <summary>
/// Enemyの質問決定
/// </summary>
void InGameScene::EnemyAsk()
{
	string Question = EnemyString[(int)FatalAnser][GetRand(5)];
}

/// <summary>
/// CSVファイルを読み取る
/// </summary>
/// <param name ="filename">開くファイルの名前</param>
/// <returns>vectorの中のvectorの中にあるstring</returns>
vector<vector<string>> InGameScene::read_csv(const string& filename)
{
	vector<vector<string>> data;
	ifstream file(filename);
	if (!file) {
		cerr << "Error: ファイルを開けませんでした。" << endl;
		return data;
	}

	string line;
	while (getline(file, line)) { // 1行ずつ読み込む
		vector<string> row;
		stringstream ss(line);
		string cell;

		while (getline(ss, cell, ',')) { // カンマ区切りで分割
			row.push_back(cell);
		}
		data.push_back(row);
	}
	return data;
}
