#include "TitleScene.h"

//Utility
#include"../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/Vector2D.h"
#include "../../Utility/Data.h"

//コンストラクタ   --＞生成時呼び出されるのでここで初期化しますね
TitleScene::TitleScene() : 
cursor(0),scale(0), alpha(0), fadein_timer(0), 
obj_location(0), message_x(0),
title_image(NULL),title_logo(NULL), scaling_up(true), 
object_image(),player_icon_x(),player_join(),join_flag(0)
{
}

//デストラクタ(破棄する時) --＞シーン管理機能クラスがあるから中身は無くても大丈夫。多分
TitleScene::~TitleScene()
{
}

//初期化処理
void TitleScene::Initialize()
{
    //背景画像
    title_image = LoadGraph("Rescurce/Image/Title/TitleImages/background.png");
    title_logo = LoadGraph("Rescurce/Image/Title/TitleImages/TitleLogo.png");

    //各オブジェクトの画像
    object_image[0] = LoadGraph("Rescurce/Image/Title/TitleImages/MessageFrame.png");
    object_image[1] = LoadGraph("Rescurce/Image/Title/TitleImages/Menu.png");
    object_image[2] = LoadGraph("Rescurce/Image/Title/TitleImages/Cursor.png");
    object_image[3] = LoadGraph("Rescurce/Image/Title/TitleImages/Line_Message.png");
    object_image[4] = LoadGraph("Rescurce/Image/Title/TitleImages/Menu.png");
    //エネミー用
    object_image[5] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage.png");
    object_image[6] = LoadGraph("Rescurce/Image/Title/TitleImages/Icon.png");
   //参加者
   object_image[7] = LoadGraph("Rescurce/Image/Title/TitleImages/Player1.png");
   object_image[8] = LoadGraph("Rescurce/Image/Title/TitleImages/Player2.png");
   object_image[9] = LoadGraph("Rescurce/Image/Title/TitleImages/Player3.png");
   object_image[10] = LoadGraph("Rescurce/Image/Title/TitleImages/Player4.png");
   object_image[11] = LoadGraph("Rescurce/Image/Title/TitleImages/Button.png");

   //オブジェクトの基準となる位置
    obj_location.x = SCREEN_WIDTH;  //1920
    obj_location.y = SCREEN_HEIGHT; //1080  
    message_x = SCREEN_WIDTH / 1.2f; // メッセージアイコンの初期位置を画面右側に設定

    //参加者の初期化
    for (int i = 0; i < 4; i++) {
        player_icon_x[i] = SCREEN_WIDTH; // 初期位置を画面右側に設定
        player_join[i] = false; // 参加フラグを初期化
    }
}

//終了時処理
void TitleScene::Finalize()
{
}

//更新処理(現在シーン)
eSceneType TitleScene::Update()
{
    //オブジェクトの演出処理
    ObjectMove();

    //キーボードのインスタンス取得(Singleton)
    KeyInput* key_input = KeyInput::Get();

    /* --- カーソルの操作 --- */
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_Y) || 
        key_input->GetKeyState(KEY_INPUT_UP) == eInputState::Pressed)
    {
        cursor--;
        // 1番上に到達したら、一番下にする
        if (cursor < 0)  cursor = 2;
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_A) || 
        key_input->GetKeyState(KEY_INPUT_DOWN) == eInputState::Pressed)
    {
        cursor++;
        // 1番下に到達したら、一番上にする
        if (cursor > 2) cursor = 0;
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Released)
    {
        //カーソル決定(決定した画面に遷移する)
        switch (cursor)
        {
        case 0:
            return eSceneType::E_INGAME;
        case 1:
            return eSceneType::E_CREDIT;
        default:
            return eSceneType::E_END;
        }
    }

    // 各参加者の入力があれば＜-- X ボタンで参加  ※複数コントローラー必要
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_X) && !player_join[0]) {
        player_join[0] = true; // プレイヤー1が参加
        Data::player_num++;
        Data::player_data[0].use_controller = DX_INPUT_PAD1;
        Data::player_data[0].number = 0;
        join_flag++;
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD2, XINPUT_BUTTON_X) && !player_join[1]) {
        player_join[1] = true; // プレイヤー2が参加
        Data::player_num++;
        Data::player_data[1].use_controller = DX_INPUT_PAD2;
        Data::player_data[1].number = 1;
        join_flag++;
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD3, XINPUT_BUTTON_X) && !player_join[2]) {
        player_join[2] = true; // プレイヤー3が参加
        join_flag++;
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD4, XINPUT_BUTTON_X) && !player_join[3]) {
        player_join[3] = true; // プレイヤー4が参加
        join_flag++;
    }
    for (int i = 1; i <= 4; i++)
    {
        if (CheckUseController(i) && PadInput::GetButtonDown(i, XINPUT_BUTTON_X))
        {
            Data::player_data[Data::player_num].use_controller = i;
            Data::player_data[Data::player_num].number = Data::player_num;
            Data::player_num++;
        }
    }
    //デバッグ用＜--　Aキー で参加 ※ひとり用
    if (key_input->GetKeyState(KEY_INPUT_A) == eInputState::Pressed)
    {
        for (int i = 0; i < 4; i++) {
            if (!player_join[i]) {
                player_join[i] = true; // 参加フラグを設定
                join_flag++;
                break;
            }
        }
    }

    // 現在のシーンタイプを返す
    return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
    DrawGraph(0, 0, title_image, true);         //背景画像の描画
    DrawGraph(0.0f, 0.0f, title_logo, true);    //タイトルロゴ
    DrawGraph(0, 0, object_image[3], true);     //メッセージバー(下の枠みたいなやつ)
    DrawGraph(10, 500, object_image[11], true); //操作説明

    //敵側のメッセージ
    DrawRotaGraph(500, 400, scale, 0.0f, object_image[5], true); //メッセージ(ちょっと話聞いてほしくて)
    DrawRotaGraph(75, 340, 1.0f, 0.0f, object_image[6], true);   //アイコン

    //メッセージアイコン(メニュー枠)
    DrawRotaGraph(message_x, obj_location.y / 1.65f, (scale - 0.2), 0.0f, object_image[0], true);

    //フェードインして描画 ----エフェクト開始
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

    //メニュー(文字)
    DrawRotaGraph(message_x, obj_location.y / 1.65f, (scale - 0.2), 0.0f, object_image[1], true);
    //カーソル(送信ボタン)
    DrawRotaGraph(SCREEN_WIDTH / 1.45f, (obj_location.y / 2.2) + cursor * 155.0f, 1.8f, 0.0, object_image[2], true);

    //ブレンドモードを解除 ----エフェクト終了
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // 参加者アイコンを描画
    for (int i = 0; i < 4; i++) {
        if (player_join[i]) {
            DrawGraph(player_icon_x[i] + i * 130, obj_location.y / 4.2f, object_image[7 + i], true);
        }
    }

    SetFontSize(50); //フォントサイズを設定
    DrawFormatString(SCREEN_WIDTH / 1.8, obj_location.y / 1.25f, GetColor(0, 0, 0), "既読", true);    //UI

    //デバッグ用
    DrawFormatString(SCREEN_WIDTH / 5, obj_location.y / 1.3f, GetColor(0, 0, 0), "-- A キーで参加 --", true);

    // 既読状態の描画  ＜--バグあり
    DrawFormatString(SCREEN_WIDTH / 1.8 + 105, obj_location.y / 1.25f, GetColor(0, 0, 0), "%d", join_flag, false);

 }

//現在シーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType();
}

//オブジェクトの演出処理
void TitleScene::ObjectMove()
{
    //徐々に大きくなる的なやつ
    if (scaling_up){
       scale += 0.05f;
        if (scale >= 1.0f){
            scale = 1.0f;
            scaling_up = false;
        }
    }
    // フェードインの処理
    if (fadein_timer < 60) {  alpha = fadein_timer * 5; // アルファ値を増加
                              fadein_timer++;   }
    else {   alpha = 255; }    

    // 参加者アイコンのスライド処理
    for (int i = 0; i < 4; i++) {
        if (player_join[i] && player_icon_x[i] > SCREEN_WIDTH / 1.5f) {
            player_icon_x[i] -= 10; // スライド速度を調整
        }
    }
}

bool TitleScene::CheckUseController(int _pad)
{
    //Playerの数だけ
    for (int i = 0; i < 4; i++)
    {
        //確認するコントローラーが既に割り当てられているなら真
        if (Data::player_data[i].use_controller == _pad)
        {
            return true;
        }
    }
    //どこにも割り当てられてないなら偽
    return false;
}
