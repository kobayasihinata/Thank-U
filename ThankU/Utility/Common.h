#pragma once

#define FULLSCREEN 0

//よく使うor共有すべきマクロはここ
#ifdef FULLSCREEN
#define SCREEN_WIDTH 1920		//画面幅
#define SCREEN_HEIGHT 1080		//画面高さ
#else
#define WINDOW_MODE 1
#define SCREEN_WIDTH 1280		//画面幅
#define SCREEN_HEIGHT 720		//画面高さ
#endif 