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

	switch (Data::player_num)
	{
	case 4:
		PlayerImage[3] = LoadGraph("Rescurce/Image/Player4.png");
	case 3:
		PlayerImage[2] = LoadGraph("Rescurce/Image/Player3.png");
	case 2:
		PlayerImage[1] = LoadGraph("Rescurce/Image/Player2.png");
	case 1:
		PlayerImage[0] = LoadGraph("Rescurce/Image/Player1.png");
		break;
	}

	EnemyAnser();

	EnemyString = {
		{"ポジティブな質問1", "ポジティブな質問2", "ポジティブな質問3", "ポジティブな質問4", "ポジティブな質問5"},
		{"ネガティブな質問1", "ネガティブな質問2", "ネガティブな質問3", "ネガティブな質問4", "ネガティブな質問5"},
		{"疑問系の質問1", "疑問系の質問2", "疑問系の質問3", "疑問系の質問4", "疑問系の質問5"},
		{"盛り上げる質問1", "盛り上げる質問2", "盛り上げる質問3", "盛り上げる質問4", "盛り上げる質問5"}
	};

	PString = { "そうだね！","そんなことないよ！","そうなの？","それから？" };

	Question = EnemyString[FatalAnserNum][GetRand(4)];

	Background_image = LoadGraph("Rescurce/Image/background.png");

	 PlayerTextImage = LoadGraph("Rescurce/Image/MessageFrame_1.png");
	 EnemyImage		 = LoadGraph("Rescurce/Image/MessageFrame_2.png");
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
	//背景画像
	DrawGraph(0, 0, Background_image, false);

	//エネミー関係
	DrawGraph(800, 100, EnemyImage, true);
	DrawFormatString(800, 200, 0xFFFFFF, "%s", Question.c_str());

	//人数に合わせて描画
	switch (Data::player_num)
	{
	case 4:
		DrawGraph(50, 500, PlayerImage[3], true);
		if (Collect[3] == false)
		{
		DrawFormatString(180, 600, 0x000000, "<メッセージが削除されました>");
		}else {
		DrawReverseGraph(80, 500, PlayerTextImage, true, 1);
		DrawFormatString(180,600, 0x000000, "%s", PString[Pagree[3]].c_str());
		}
	case 3:
		if (Collect[2] == false)
		{
		DrawFormatString(180, 450, 0x000000, "<メッセージが削除されました>");
		}else {
		DrawGraph(50, 350, PlayerImage[2], true);
		DrawReverseGraph(80, 350, PlayerTextImage, true, 1);
		DrawFormatString(180,450, 0x000000, "%s", PString[Pagree[2]].c_str());

		}
	case 2:
		if (Collect[1] == false)
		{
		DrawFormatString(180, 300, 0x000000, "<メッセージが削除されました>");
		}else {
		DrawGraph(50, 200, PlayerImage[1], true);
		DrawReverseGraph(80, 200, PlayerTextImage, true, 1);
		DrawFormatString(180,300, 0x000000, "%s", PString[Pagree[1]].c_str());

		}

	case 1:
		if (Collect[0] == false)
		{
		DrawFormatString(180, 150, 0x000000, "<メッセージが削除されました>");
		}else{
		DrawGraph(50, 50, PlayerImage[0], true);
		DrawReverseGraph(80, 50, PlayerTextImage, true, 1);
		DrawFormatString(180, 150, 0x000000, "%s", PString[Pagree[0]].c_str());
		}
	}

	DrawFormatString(900, 0, 0x000000, "TimeCount:%d", Timer);
#if _DEBUG
	switch (Data::player_num)
	{
	case 4:
		DrawFormatString(50, 600, 0x000000, "%d", PD4.score);
	case 3:
		DrawFormatString(50, 450, 0x000000, "%d", PD3.score);
	case 2:
		DrawFormatString(50, 300, 0x000000, "%d", PD2.score);
	case 1:
		DrawFormatString(50, 150, 0x000000, "%d", PD1.score);
	}

	DrawString(10, 10, "InGame", 0x000000);

#endif
}

/// <summary>
/// 恒常処理
/// </summary>
/// <param></param>
/// <returns>現在のシーンを返却</returns>
eSceneType InGameScene::Update()
{
	__super::Update();
#if _DEBUG
	KeyInput* key_input = KeyInput::Get();
#endif // _DEBUG

	/*	Enemy関連(2つとも記載済みのため、関数呼び出しのみ)	*/
	if (Timer == 2)
	{
		Collect[0] = true;
		Collect[1] = true;
		Collect[2] = true;
		Collect[3] = true;
	}
	while (Timer > 4)
	{
		//Enemyから受け取った答えとplayerらが言ってる答えを比較する
		CheckAnser();
		//Enemyから問いかけを貰う
		EnemyAsk();
		Timer = 0;
	}
	/*player関連^-_-^おそらくループ*/

	TimerCount();
	//入力に応じた処理
	PlayerAnser();
	//全員入力する または 指定時間過ぎる(要勉強)


	//指定ポイント分配しきったら
	if (TotalScore <= 0)
	{
		return eSceneType::E_RESULT;
	}

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
	int j = 1;
	for (int i = 0; i < Data::player_num; i++)
	{
		//playerの押したボタンに応じて回答を当てはめる
		if(PadInput::GetButtonDown(j, XINPUT_BUTTON_B))//←仮置き
		{
			Player_Anser[i] = agreement::positive;
			Pagree[i] = 0;
		}
		else if (PadInput::GetButtonDown(j, XINPUT_BUTTON_A))
		{
			Player_Anser[i] = agreement::negation;
			Pagree[i] = 1;

		}
		else if (PadInput::GetButtonDown(j, XINPUT_BUTTON_X))
		{
			Player_Anser[i] = agreement::question;
			Pagree[i] = 2;

		}
		else if (PadInput::GetButtonDown(j, XINPUT_BUTTON_Y))
		{
			Player_Anser[i] = agreement::excitement;
			Pagree[i] = 3;

		}
		j++;
	}

	return 0;
}

void InGameScene::CheckAnser()
{
	Collect[0] = false;
	Collect[1] = false;
	Collect[2] = false;
	Collect[3] = false;

	for (int i = 0; i < Data::player_num; i++)
	{
		if (Player_Anser[i] == FatalAnser)
		{
			//正解の場合
			//scoreを正答したプレイヤーに加算
			switch (i)
			{
			case 0:
				PD1.score += 50;
				TotalScore -= 50;
				Collect[0] = true;
				break;
			case 1:
				PD2.score += 50;
				TotalScore -= 50;
				Collect[1] = true;

				break;
			case 2:
				PD3.score += 50;
				TotalScore -= 50;
				Collect[2] = true;
				break;
			case 3:
				PD4.score += 50;
				TotalScore -= 50;
				Collect[3] = true;
				break;
			}
		}
	}
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
		FatalAnserNum = 0;
		break;
	case 2:
		FatalAnser = agreement::negation;
		FatalAnserNum = 1;
		break;
	case 3:
		FatalAnser = agreement::question;
		FatalAnserNum = 2;
		break;
	case 4:
		FatalAnser = agreement::excitement;
		FatalAnserNum = 3;
		break;
	}
}


/// <summary>
/// Enemyの質問決定
/// </summary>
void InGameScene::EnemyAsk()
{
	EnemyAnser();

	Question = EnemyString[FatalAnserNum][GetRand(4)];
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

void InGameScene::TimerCount()
{
	TimeCountUp += 1.0f;

	if (TimeCountUp > 60.0f)
	{
		TimeCountUp = 0.0f;
		Timer ++;
	}
}
