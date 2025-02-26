#include "TitleScene.h"

//Utility
#include"../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/Vector2D.h"
#include "../../Utility/Data.h"
#include "../../Utility/DebugInformation.h"
#include "../../Utility/EffectManager.h"

//コンストラクタ   --＞生成時呼び出されるのでここで初期化しますね
TitleScene::TitleScene() : 
    frame(0), cursor(0), player_button_flg{ false },game_start_flg(false),
    game_start_timer(0) , cursor_size(2.3f), scale(0), alpha(0), fadein_timer(0),
obj_location(0), message_x(0),
title_image(NULL),title_logo(NULL), scaling_up(true), SE_Cursor(NULL),SE_Decision(NULL),
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
    //タイトルBGM再生
    PlaySoundFile("Rescurce/BGM/TitleBGM.wav", DX_PLAYTYPE_LOOP);

    //SEファイル読み込み
    SE_Cursor = LoadSoundMem("Rescurce/SE/CursorMove.mp3");
    SE_Decision = LoadSoundMem("Rescurce/SE/Decision.mp3");

    //エフェクト管理クラス取得
    e_manager = EffectManager::Get();

    //背景画像
    title_image = LoadGraph("Rescurce/Image/background.png");
    title_logo = LoadGraph("Rescurce/Image/TitleLogo.png");

    //各オブジェクトの画像
    object_image[0] = LoadGraph("Rescurce/Image/MessageFrame.png");
    object_image[1] = LoadGraph("Rescurce/Image/Menu.png");
    object_image[2] = LoadGraph("Rescurce/Image/Cursor.png");
    object_image[3] = LoadGraph("Rescurce/Image/Line_Message.png");
    object_image[4] = LoadGraph("Rescurce/Image/Menu.png");

    //エネミー用
    object_image[5] = LoadGraph("Rescurce/Image/EnemyMessage.png");
    object_image[6] = LoadGraph("Rescurce/Image/Icon.png");
    
    message_image[0] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_1.png");
    message_image[1] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_2.png");
    message_image[2] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_3.png");
    message_image[3] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_4.png");
    message_image[4] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_5.png");
    message_image[5] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_6.png");
    message_image[6] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_7.png");
    message_image[7] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_8.png");
    message_image[8] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_9.png");

   //参加者
   object_image[7] = LoadGraph("Rescurce/Image/Player1.png");
   object_image[8] = LoadGraph("Rescurce/Image/Player2.png");
   object_image[9] = LoadGraph("Rescurce/Image/Player3.png");
   object_image[10] = LoadGraph("Rescurce/Image/Player4.png");
   object_image[11] = LoadGraph("Rescurce/Image/Button.png");

   //オブジェクトの基準となる位置
    obj_location.x = SCREEN_WIDTH;  //1920
    obj_location.y = SCREEN_HEIGHT; //1080  
    message_x = SCREEN_WIDTH / 1.2f; // メッセージアイコンの初期位置を画面右側に設定

    //参加者の初期化
    for (int i = 0; i < 4; i++) {
        player_icon_x[i] = SCREEN_WIDTH; // 初期位置を画面右側に設定
        player_join[i] = false; // 参加フラグを初期化
        Data::player_data[i] = { 0 };   //プレイヤーデータ初期化
    }
    Data::player_num = 0;               //人数もリセット
  
    //コントローラー1は強制的にプレイヤー1
    if (Data::player_data[0].use_controller == 0)
    {
        Data::player_data[0].use_controller = DX_INPUT_PAD1;
        Data::player_num++;
        player_join[0] = true;
        join_flag++;    //参加しました。
    }

    random_image_timer = 0; // タイマー変数の初期化
    current_image_index = rand() % 9; // ランダムな画像の初期選択
}

//終了時処理
void TitleScene::Finalize()
{
    //BGMを止める
    StopSoundFile();
}

//更新処理(現在シーン)
eSceneType TitleScene::Update()
{
    //オブジェクトの演出処理
    ObjectMove();

    //フレーム計測
    if (frame++ > 6000)frame = 0;

    //キーボードのインスタンス取得(Singleton)
    KeyInput* key_input = KeyInput::Get();

    if (!game_start_flg)
    {
        /* --- カーソルの操作 --- */
        if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_Y) || 
            key_input->GetKeyState(KEY_INPUT_UP) == eInputState::Pressed)
    {
        cursor--;
        PlaySoundMem(SE_Cursor, DX_PLAYTYPE_BACK);
        // 1番上に到達したら、一番下にする
        if (cursor < 0)  cursor = 2;
        
    }
        if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_A) || 
            key_input->GetKeyState(KEY_INPUT_DOWN) == eInputState::Pressed)
    {
        cursor++;
        PlaySoundMem(SE_Cursor, DX_PLAYTYPE_BACK);
        // 1番下に到達したら、一番上にする
        if (cursor > 2) cursor = 0;
    }
        if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
        {
            //ゲーム開始演出
            PlaySoundMem(SE_Decision, DX_PLAYTYPE_NORMAL);
            game_start_flg = true;
            game_start_timer = 0;
        }
    }

    //開始演出処理
    if (game_start_flg)
    {
        //一定時間経過で遷移
        if (++game_start_timer > 60)
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
    }
    //コントローラーが1～4なのでforも合わす
    for (int i = 1; i <= 4; i++)
    {
        //ボタンが押された時に参加
        if (PadInput::GetButtonDown(i, XINPUT_BUTTON_X))
        {
            //参加
            if (CheckUseController(i) == -1)
            {
                Data::player_data[Data::player_num].use_controller = i;
                Data::player_data[Data::player_num].number = Data::player_num;
                Data::player_num++;
            }
        }
    }

    //待機中の演出
    for (int i = 0; i < Data::player_num; i++)
    {
        int use = Data::player_data[i].use_controller;
        if (PadInput::GetButtonDown(use, XINPUT_BUTTON_A) ||
            PadInput::GetButtonDown(use, XINPUT_BUTTON_B) ||
            PadInput::GetButtonDown(use, XINPUT_BUTTON_X) ||
            PadInput::GetButtonDown(use, XINPUT_BUTTON_Y))
        {
            player_button_flg[i] = true;
            //StarBurst({ player_icon_x[i] + i * 130, obj_location.y / 4.2f,});
            //e_manager->SpawnEffect({ player_icon_x[i] + i * 130, obj_location.y / 4.2f, }, eEffectList::eExplosion);
        }
        else
        {
            player_button_flg[i] = false;
        }
    }
    //↑キーでも反応(デバッグ)
    if (key_input->GetKeyState(KEY_INPUT_UP) == eInputState::Pressed)
    {
        player_button_flg[0] = true;
    }
    else
    {
        player_button_flg[0] = false;
    }

    //Dataを参照してアイコンの演出
    for (int i = 0; i < 4; i++)
    {
        //コントローラーが割り当てられている＝プレイヤーが居ると判断
        if (Data::player_data[i].use_controller != 0 && !player_join[i])
        {
            //演出の開始
            player_join[i] = true;
            join_flag++;
        }
    }

    // タイマーをインクリメント
    random_image_timer++;

    // 一定間隔 (例えば60フレーム = 1秒) ごとにランダムな画像を選択
    if (random_image_timer >= 60 * 3)   //＜--60×3なのでだいたい3秒
    {
        random_image_timer = 0; // タイマーをリセット
        current_image_index = rand() % 9; // ランダムな画像を選択
    }

    //カーソルを大きくしたり小さくしたりする
    if (frame % 60 > 30)
    {
        cursor_size += 0.01f;
    }
    else
    {
        cursor_size -= 0.01f;
    }
#ifdef _DEBUG
    //デバッグ用(リザルト画面)
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_START) ||key_input->GetKeyState(KEY_INPUT_R) == eInputState::Pressed)
    {
        return eSceneType::E_RESULT;
    }
    //デバッグ用＜--　Aキー で参加 ※ひとり用
    if (key_input->GetKeyState(KEY_INPUT_A) == eInputState::Pressed)
    {
        //コントローラーが1～４なのでforも
        for (int i = 1; i <= 4; i++)
        {
            //参加
            if (CheckUseController(i) == -1)
            {
                Data::player_data[Data::player_num].use_controller = i;
                Data::player_data[Data::player_num].number = Data::player_num;
                Data::player_num++;
                break;
            }
        }
    }
    //エフェクトテスト(爆発)
    if (key_input->GetKeyState(KEY_INPUT_1) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::eExplosion);
    }
    //エフェクトテスト(細かい爆発)
    if (key_input->GetKeyState(KEY_INPUT_2) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::ePuffAndStar);
    }
    //エフェクトテスト(Anima)
    if (key_input->GetKeyState(KEY_INPUT_3) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::eAnima);
    }
    //エフェクトテスト(BigHit)
    if (key_input->GetKeyState(KEY_INPUT_4) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::eBighit);
    }
    //エフェクトテスト(BigHit)
    if (key_input->GetKeyState(KEY_INPUT_5) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::eBloodImpact);
    }
    //エフェクトテスト(星)
    if (key_input->GetKeyState(KEY_INPUT_6) == eInputState::Pressed)
    {
        StarBurst({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) });
    }

    DebugInfomation::Add("cont1", PadInput::GetButton(DX_INPUT_PAD1, XINPUT_BUTTON_A));
    DebugInfomation::Add("cont2", PadInput::GetButton(DX_INPUT_PAD2, XINPUT_BUTTON_A));
    DebugInfomation::Add("cont3", PadInput::GetButton(DX_INPUT_PAD3, XINPUT_BUTTON_A));
    DebugInfomation::Add("cont4", PadInput::GetButton(DX_INPUT_PAD4, XINPUT_BUTTON_A));
#endif // _DEBUG
    // 現在のシーンタイプを返す
    return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
    DrawGraph(0, 0, title_image, true);         //背景画像の描画
    DrawGraph(0, 0, object_image[3], true);     //メッセージバー(下の枠みたいなやつ)
    DrawGraph(10, 500, object_image[11], true); //操作説明

    DrawGraph(0.0f,  game_start_timer *(-4), title_logo, true);    //タイトルロゴ

    //敵側のメッセージ
    DrawRotaGraph(75 - game_start_timer * 14, 340, 1.0f, 0.0f, object_image[6], true);   //アイコン

    // ランダム画像を描画
    DrawRotaGraph(500 - game_start_timer * 14, 400, scale, 0.0f, message_image[current_image_index], true);

    //メッセージアイコン(メニュー枠)
    DrawRotaGraph(message_x + game_start_timer * 14, obj_location.y / 1.65f, (scale - 0.2), 0.0f, object_image[0], true);

    //フェードインして描画 ----エフェクト開始
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    //メニュー(文字)
    DrawRotaGraph(message_x + game_start_timer * 14, obj_location.y / 1.65f, (scale - 0.2), 0.0f, object_image[1], true);
    //カーソル(送信ボタン)
    DrawRotaGraph(SCREEN_WIDTH / 1.45f + game_start_timer * 14, (obj_location.y / 2.2) + cursor * 157.0f, cursor_size, 0.0, object_image[2], true);
    //ブレンドモードを解除 ----エフェクト終了
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // 参加者アイコンを描画
    for (int i = 0; i < 4; i++) {
        //自分のコントローラーを押したら反応する
        //コントローラーが割り当てられているかで判断
        if (Data::player_data[i].use_controller > 0)
        {
            if (player_button_flg[i])
            {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
                //強調描画
                for (int j = 0; j < 5; j++)
                {
                    DrawCircleAA(player_icon_x[i] + i * 130 +(game_start_timer * 14), obj_location.y / 3.4f, 60 + (j * 5), 20, 0xffffff, true);
                }
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
                //ちょっと大きいアイコン描画
                DrawRotaGraphF(player_icon_x[i] + i * 130 + (game_start_timer * 14), obj_location.y / 3.4f, 1.1f, 0.f, object_image[7 + i], true);
            }
            else
            {
                //通常のアイコン描画
                DrawRotaGraphF(player_icon_x[i] + i * 130 + (game_start_timer * 14), obj_location.y / 3.4f,1.0f,0.f, object_image[7 + i], true);
            }
        }
    }

    SetFontSize(50); //フォントサイズを設定
    DrawFormatString(SCREEN_WIDTH / 1.8 + (game_start_timer * 14), obj_location.y / 1.25f, GetColor(0, 0, 0), "既読", true);    //UI

    // 既読状態の描画
    DrawFormatString(SCREEN_WIDTH / 1.8 + 105 + (game_start_timer * 14), obj_location.y / 1.25f, GetColor(0, 0, 0), "%d", join_flag, false);
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

int TitleScene::CheckUseController(int _pad)
{
    //Playerの数だけ
    for (int i = 0; i < 4; i++)
    {
        //コントローラーが既に割り当てられているなら使っているプレイヤーの位置を取得
        if (Data::player_data[i].use_controller == _pad)
        {
            return i;
        }
    }
    //どこにも割り当てられてないなら-1
    return -1;
}

void TitleScene::StarBurst(Vector2D _loc)const
{
    for (int i = 0; i < 5; i++)
    {
        e_manager->SpawnEffect(_loc,
            (eEffectList)(GetRand(9) + 6),
            { (float)(GetRand(20) - 10),(float)(GetRand(20) - 10) }, 
            10);
    }
}