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
        // 1�ԏ�ɓ��B������A��ԉ��ɂ���
        if (cursor < 0)
        {
            cursor = 3;
        }
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_A) || key_input->GetKeyState(KEY_INPUT_DOWN) == eInputState::Pressed)
    {
        cursor++;
        // 1�ԉ��ɓ��B������A��ԏ�ɂ���
        if (cursor > 3)
        {
            cursor = 0;
        }
    }

    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Released)
    {
        //�J�[�\������(���肵����ʂɑJ�ڂ���)
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

    // ���݂̃V�[���^�C�v��Ԃ�
    return GetNowScene();
}

void TitleScene::Draw() const
{
    /* �������牺�̏����͉��@�\ */
    int y = 24;

    //�^�[�Q�b�g�J�[�\��
    DrawFormatString(10, 10, GetColor(255, 255, 255), "%d",cursor,TRUE);

    //�J�[�\��
    DrawCircle((SCREEN_WIDTH / 2) - 80, (SCREEN_HEIGHT / 1.9) + cursor * 20, 5, GetColor(255, 255, 255), TRUE);

    //�^�񒆂�����ɕ`��
    DrawFormatString((SCREEN_WIDTH / 2 ) - 90 , (SCREEN_HEIGHT / 3), GetColor(255, 255, 255), "�^�C�g����ʂł�");

    //���j���[
    DrawFormatString((SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2.1) + y, GetColor(255, 255, 255), "�X�^�[�g");
    DrawFormatString((SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2.1) + y * 2, GetColor(255, 255, 255), "���U���g");
    DrawFormatString((SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2.1) + y * 3, GetColor(255, 255, 255), "�N���W�b�g");
    DrawFormatString((SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2.1) + y * 4, GetColor(255, 255, 255), "�G���h");
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType();
}
