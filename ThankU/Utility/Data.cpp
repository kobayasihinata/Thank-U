#include "Data.h"
#include "DxLib.h"

int Data::player_num = 0;				//音量 0=全体 1=BGM 2=SE
PlayerData Data::player_data[4] = { 0 };	//キー割り当て情報格納
int Data::frame_image[6] = { 0 };			//吹き出し枠

void Data::Initialize()
{
	LoadDivGraph("Rescurce/Image/MessageFrame_3.png", 6, 3, 2, 100, 120, frame_image);
}

void Data::DrawSpeechBubble(Vector2D _loc, int _size_x, bool _color)
{
	int f = GetFontSize();
	Vector2D shift = { _loc.x - 100,_loc.y - 60 + (f / 2) };	//文字を吹き出しの中に収めるための移動
	//吹き出し左端
	DrawGraphF(shift.x,
		shift.y,
		frame_image[0 + (((int)_color) * 3)],
		true);
	int n = 0;	//何回描画したか計測
	//吹き出し中央
	for (int j = 0; j < _size_x; j += 100)
	{
		DrawGraphF(shift.x + 100 + j,
			shift.y,
			frame_image[1 + (((int)_color) * 3)],
			true);
		n++;
	}
	//吹き出し右端
	DrawGraphF(shift.x + n * 100 + 100,
		shift.y,
		frame_image[2 + (((int)_color) * 3)],
		true);
}