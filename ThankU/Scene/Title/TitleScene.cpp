#include "TitleScene.h"
#include"../../Utility/PadInput.h"

TitleScene::TitleScene():key(0)
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
    
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_SPACE))
    {
        return eSceneType::E_INGAME;
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_A))
    {
        return eSceneType::E_CREDIT;
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_S))
    {
        return eSceneType::E_RESULT;
    }
        ////�J�[�\������(���肵����ʂɑJ�ڂ���)
        //switch (key)
        //{
        //case 0:
        //    return eSceneType::E_INGAME;
        //case 1:
        //    return eSceneType::E_RESULT;
        //case 2:
        //    return eSceneType::E_CREDIT;
        //default:
        //    return eSceneType::E_END;
        //}

    // ���݂̃V�[���^�C�v��Ԃ�
    //return GetNowScene();
}

void TitleScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "�^�C�g����ʂł�");
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType();
}
