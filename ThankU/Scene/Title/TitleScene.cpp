#include "TitleScene.h"
#include"../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/Vector2D.h"

TitleScene::TitleScene() : cursor(0)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::Update()
{
    KeyInput* key_input = KeyInput::Get();

    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_Y) || key_input->GetKeyState(KEY_INPUT_UP) == eInputState::Pressed)
    {
        cursor--;
        // 1番上に到達したら、一番下にする
        if (cursor < 0)
        {
            cursor = 3;
        }
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_A) || key_input->GetKeyState(KEY_INPUT_DOWN) == eInputState::Pressed)
    {
        cursor++;
        // 1番下に到達したら、一番上にする
        if (cursor > 3)
        {
            cursor = 0;
        }
    }

    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Released)
    {
        //カーソル決定(決定した画面に遷移する)
        switch (cursor)
        {
        case 0:
            return eSceneType::E_INGAME;
        case 1:
            return eSceneType::E_RESULT;
        case 2:
            return eSceneType::E_CREDIT;
        default:
            return eSceneType::E_END;
        }
    }

    // 現在のシーンタイプを返す
    return GetNowScene();
}

void TitleScene::Draw() const
{
    /* ここから下の処理は仮機能 */
    int y = 24;

    //ターゲットカーソル
    DrawFormatString(10, 10, GetColor(255, 255, 255), "%d",cursor,TRUE);

    //カーソル
    DrawCircle((SCREEN_WIDTH / 2) - 80, (SCREEN_HEIGHT / 1.9) + cursor * 20, 5, GetColor(255, 255, 255), TRUE);

    //真ん中あたりに描画
    DrawFormatString((SCREEN_WIDTH / 2 ) - 90 , (SCREEN_HEIGHT / 3), GetColor(255, 255, 255), "タイトル画面です");

    //メニュー
    DrawFormatString((SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2.1) + y, GetColor(255, 255, 255), "スタート");
    DrawFormatString((SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2.1) + y * 2, GetColor(255, 255, 255), "リザルト");
    DrawFormatString((SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2.1) + y * 3, GetColor(255, 255, 255), "クレジット");
    DrawFormatString((SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2.1) + y * 4, GetColor(255, 255, 255), "エンド");
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType();
}
