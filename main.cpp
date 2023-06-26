#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#undef main
#pragma execution_character_set("utf-8")

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 300;
const std::string before[] = {"代号", "Project"};

void quit(SDL_Window *window);

int main() {
    std::string before_str, after_str;
    SDL_Surface *nameStrSurface;

    SDL_Window *window = NULL;

    SDL_Surface *screenSurface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL无法初始化！SDL_错误：" << SDL_GetError() << std::endl;
    } else {
        //创建窗口
        window = SDL_CreateWindow("手游名称生成器", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cout << "无法创建窗口！SDL_错误：" << SDL_GetError() << std::endl;
        } else {
            //获取窗口表面
            screenSurface = SDL_GetWindowSurface(window);

            //把表面涂成白色
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            //向屏幕中打印文字：“按下随机按钮生成手游名称：”
            TTF_Init();
            TTF_Font *font = TTF_OpenFont("Alibaba-PuHuiTi-Regular.otf", 24);
            SDL_Color textColor = {0, 0, 0};
            SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, "按下随机按钮生成手游名称：", textColor);
            SDL_Rect textLocation = {50, 30, 0, 24};
            SDL_BlitSurface(textSurface, NULL, screenSurface, &textLocation);

            //创建随机按钮
            SDL_Rect buttonLocation = {400, 200, 100, 50};
            SDL_Surface *buttonSurface = SDL_CreateRGBSurface(0, 100, 50, 32, 0, 0, 0, 0);
            SDL_FillRect(buttonSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 255, 255));
            SDL_BlitSurface(buttonSurface, NULL, screenSurface, &buttonLocation);
            SDL_Surface *buttonTextSurface = TTF_RenderUTF8_Solid(font, "随机", textColor);
            SDL_Rect buttonTextLocation = {400, 200, 100, 50};
            SDL_BlitSurface(buttonTextSurface, NULL, screenSurface, &buttonTextLocation);

            //更新曲面
            SDL_UpdateWindowSurface(window);

            //按钮点击事件
            SDL_Event event;
            bool quit = false;
            while (!quit) {
                while (SDL_PollEvent(&event) != 0) {
                    if (event.type == SDL_QUIT) {
                        quit = true;
                    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        if (x > 400 && x < 500 && y > 200 && y < 250) {
                            //生成随机字符串，格式为：代号或Project：+ 2~5为随机大写字母或数字
                            before_str = before[rand() % 2];
                            after_str = "";
                            for (int i = 0; i < rand() % 4 + 2; i++) {
                                after_str += rand() % 2 == 0 ? (char) (rand() % 26 + 65) : (char) (rand() % 10 + 48);
                            }
                            std::string str = before_str + "：" + after_str;

                            //向屏幕中打印随机字符串
                            if (nameStrSurface != NULL) {
                                //清空原来打印出来的字符串
                                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
                                SDL_BlitSurface(textSurface, NULL, screenSurface, &textLocation);
                                SDL_BlitSurface(buttonSurface, NULL, screenSurface, &buttonLocation);
                                SDL_BlitSurface(buttonTextSurface, NULL, screenSurface, &buttonTextLocation);
                            }
                            nameStrSurface = TTF_RenderUTF8_Solid(font, str.c_str(), textColor);
                            SDL_Rect nameStrLocation = {50, 125, 0, 24};
                            SDL_BlitSurface(nameStrSurface, NULL, screenSurface, &nameStrLocation);

                            //更新曲面
                            SDL_UpdateWindowSurface(window);
                        }
                    }
                }
            }
        }
    }

    quit(window);

    return 0;
}

void quit(SDL_Window *window) {
    //破坏窗口
    SDL_DestroyWindow(window);

    //退出SDL子系统
    SDL_Quit();
}