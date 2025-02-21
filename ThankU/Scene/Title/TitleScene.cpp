#include "TitleScene.h"

TitleScene::TitleScene()
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
    // カーソル決定(決定した画面に遷移する)
  /*  if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
    {
        PlaySoundMem(sound, TRUE);

        switch (menu_cursor)
        {
        case 0:
            return eSceneType::E_INGAME;
        case 1:
            return eSceneType::E_RESULT;
        case 2:
            return eSceneType::E_HELP;
        default:
            return eSceneType::E_END;
        }
    }*/

    // 現在のシーンタイプを返す
    return GetNowScene();
}

void TitleScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "タイトル画面です");
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType();
}
