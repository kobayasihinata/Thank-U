#include "ResultScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/Common.h"
#include "../../Utility/Data.h"

ResultScene::ResultScene():frame(0)
{
	
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	animation_image = LoadGraph("Rescurce/Image/background.png");
	bar_image = LoadGraph("Rescurce/Image/Line_Message.png");
}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::Update()
{
	__super::Update();

	//�t���[������
	frame++;

	KeyInput* key_input = KeyInput::Get();

	//�f�o�b�O������
#if _DEBUG

	//B�{�^�����X�y�[�X�L�[�Ń^�C�g����
	if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return E_TITLE;
	}
#endif //  DEBUG
	//���݂̃V�[����Ԃ�
	return GetNowScene();
}

void ResultScene::Draw() const
{
	//�w�i�摜
	DrawGraph(0, 0, animation_image, false);

	//�X�R�A�\��
	for (int i = 0; i < Data::player_num; i++)
	{
		DrawFormatString(100, 100 + (i * 50), 0x000000,
			"Player%d  Score:%d Great:%d Bad:%d",
			i,
			Data::player_data[i].score,
			Data::player_data[i].great,
			Data::player_data[i].bad);
	}
	//���̃o�[�`��
	DrawGraph(0, 0, bar_image, true);
#if _DEBUG
	DrawString(0, 0, "Result", 0x000000);
	DrawString(0, 20, "Pad B  or  Space�Ń^�C�g��", 0x000000);
#endif
}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}