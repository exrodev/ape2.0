#define OBF_BEGIN try { obf::next_step __crv = obf::next_step::ns_done; std::shared_ptr<obf::base_rvholder> __rvlocal;

#include <Windows.h>
#include <tchar.h>
#include <math.h> 
#include <time.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "resource.h"
#include "o.h"
#include <random>

#pragma comment(lib, "winmm.lib")

int cpsMin = 9;
int cpsMax = 12;
int jitter = 0;
int toggleAC = 45;
int toggleWindow = 46;
int toggleSounds = 35;
int toggleJitter = 123;
int selected = 1;
bool toggled = false;
bool toggledSounds = false;
bool toggledJitter = false;

using namespace std;

const char* keys[256] = {
    "",
    "",
    "",
    "",
    "",
    "MOUSE4",
    "MOUSE5",
    "",
    "",
    "TAB",
    "",
    "",
    "CLEAR",
    "ENTER",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "SPACE",
    "PGUP",
    "PGDOWN",
    "END",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "INSERT",
    "DELETE",
    "",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "",
    "",
    "",
    "",
    "",
    "NUM0",
    "NUM1",
    "NUM2",
    "NUM3",
    "NUM4",
    "NUM5",
    "NUM6",
    "NUM7",
    "NUM8",
    "NUM9",
    "MULTIPLY",
    "ADD",
    "SEPARATOR",
    "SUBTRACT",
    "DECIMAL",
    "DIVIDE",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "LSHIFT",
    "RSHIFT",
    "LCONTROL",
    "",
    "LMENU",
    "RMENU",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "COMMA",
    "MINUS",
    "PERIOD",
    "SLASH",
    "TILDA",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "[",
    "|",
    "]",
    "QUOTE",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

void remove_scrollbar()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(handle, new_size);
}

void colors() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 255; i++) {
        SetConsoleTextAttribute(hConsole, i);
        cout << i << endl;
    }

    system("pause");
}

void menu() {
    system("cls");
    cout << endl << AY_OBFUSCATE("              _|_|_|  _|_|_|      _|_|") << endl;
    cout << AY_OBFUSCATE("            _|    _|  _|    _|  _|_|_|_|") << endl;
    cout << AY_OBFUSCATE("            _|    _|  _|    _|  _|") << endl;
    cout << AY_OBFUSCATE("              _|_|_|  _|_|_|      _|_|_|") << endl;
    cout << AY_OBFUSCATE("                      _|     2.2 beta") << endl;
    cout << AY_OBFUSCATE("                      _|") << endl << endl;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    if (selected == 1) cout << AY_OBFUSCATE("              ----> MIN: ") << cpsMin << AY_OBFUSCATE(" CPS <----") << endl;
    else cout << AY_OBFUSCATE("                    MIN: ") << cpsMin << AY_OBFUSCATE(" CPS") << endl;
    cout << "    [";
    for (int i = cpsMin - 6; i > 0; --i) {
        SetConsoleTextAttribute(hConsole, 170);
        cout << "     ";
    }
    for (int i = cpsMin - 6; i < 8; i++) {
        SetConsoleTextAttribute(hConsole, 68);
        cout << "     ";
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << "]" << endl;

    if (selected == 2) cout << AY_OBFUSCATE("              ----> MAX: ") << cpsMax << AY_OBFUSCATE(" CPS <----") << endl;
    else cout << AY_OBFUSCATE("                    MAX: ") << cpsMax << AY_OBFUSCATE(" CPS") << endl;
    cout << "    [";
    for (int i = cpsMax - 6; i > 0; --i) {
        SetConsoleTextAttribute(hConsole, 170);
        cout << "     ";
    }
    for (int i = cpsMax - 6; i < 8; i++) {
        SetConsoleTextAttribute(hConsole, 68);
        cout << "     ";
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << "]" << endl;

    if (selected == 3) cout << AY_OBFUSCATE("           ----> JITTER: ") << jitter << AY_OBFUSCATE(" STRENGTH <----") << endl;
    else cout << AY_OBFUSCATE("                 JITTER: ") << jitter << AY_OBFUSCATE(" STRENGTH") << endl;
    cout << "    [";
    for (int i = jitter; i > 0; --i) {
        SetConsoleTextAttribute(hConsole, 170);
        cout << "    ";
    }
    for (int i = jitter; i < 10; i++) {
        SetConsoleTextAttribute(hConsole, 68);
        cout << "    ";
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << "]" << endl << endl << endl;

    if (toggled) SetConsoleTextAttribute(hConsole, 10);
    else SetConsoleTextAttribute(hConsole, 12);
    cout << "              [" << keys[toggleAC] << "]";
    SetConsoleTextAttribute(hConsole, 15);
    cout << AY_OBFUSCATE(" Toggle Autoclicker") << endl;
    if (toggledSounds) SetConsoleTextAttribute(hConsole, 10);
    else SetConsoleTextAttribute(hConsole, 12);
    cout << "              [" << keys[toggleSounds] << "]";
    SetConsoleTextAttribute(hConsole, 15);
    cout << AY_OBFUSCATE(" Toggle Sounds") << endl;
    if (toggledJitter) SetConsoleTextAttribute(hConsole, 10);
    else SetConsoleTextAttribute(hConsole, 12);
    cout << "              [" << keys[toggleJitter] << "]";
    SetConsoleTextAttribute(hConsole, 15);
    cout << AY_OBFUSCATE(" Toggle Jitter") << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "              [" << keys[toggleWindow] << AY_OBFUSCATE("] Toggle Window") << endl;
    cout << AY_OBFUSCATE("              [HOME] Change Binds") << endl;
    cout << AY_OBFUSCATE("              [RCONTROL+BACKSPACE] Destruct") << endl;
}

int randomInt(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
    return dist6(rng);
}

static auto generate_random_float = [](float min, float max) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
};

void clickSound() {
    PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
}

int main() {

    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    POINT pt;

    toggled = false;
    remove_scrollbar();
    Sleep(10);

    SetConsoleTitle(_T(""));
    HWND hWnd = FindWindow(_T("LWJGL"), NULL);
    if (hWnd == NULL) {
        cout << AY_OBFUSCATE("                                                  Couldn't find game... ") << endl;
        Sleep(1000);
        exit(1);
    }


    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 420, 407, TRUE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    remove_scrollbar();
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~(WS_SIZEBOX | WS_MAXIMIZEBOX));

    
    menu();

    while (true) {

        if (GetAsyncKeyState(VK_RCONTROL) && GetAsyncKeyState(VK_BACK)) {
            system("cls");
            cout << AY_OBFUSCATE("Destructing...") << endl;
            system(AY_OBFUSCATE("del /q c0gnito.dll >nul"));
            system(AY_OBFUSCATE("ipconfig /flushdns >nul"));
            exit(2);
        }

        Sleep(1);

        if (!IsWindow(hWnd)) {
            Sleep(1000);
            hWnd = FindWindow(_T("LWJGL"), NULL);
            if (hWnd == NULL) {
                exit(1);
            }
        }

        HWND hWndCur = GetForegroundWindow();

        if (hWndCur == console) {

            if (GetAsyncKeyState(VK_LEFT)) {
                switch (selected) {
                case 1:
                    if (cpsMin >= 7) {
                        cpsMin--;
                        menu();
                        Sleep(100);
                    }
                    break;
                case 2:
                    if (cpsMax >= 7) {
                        if (cpsMax > cpsMin) {
                            cpsMax--;
                            menu();
                            Sleep(100);
                        }
                    }
                    break;
                case 3:
                    if (jitter >= 1) {
                        jitter--;
                        menu();
                        Sleep(100);
                    }
                    break;
                }
            }


            if (GetAsyncKeyState(VK_RIGHT)) {
                switch (selected) {
                case 1:
                    if (cpsMin <= 13) {
                        if (cpsMin < cpsMax) {
                            cpsMin++;
                            menu();
                            Sleep(100);
                        }
                    }
                    break;
                case 2:
                    if (cpsMax <= 13) {
                        cpsMax++;
                        menu();
                        Sleep(100);
                    }
                    break;
                case 3:
                    if (jitter <= 9) {
                        jitter++;
                        menu();
                        Sleep(100);
                    }
                    break;
                }
            }


            if (GetAsyncKeyState(VK_UP)) {
                switch (selected) {
                case 2:
                    selected = 1;
                    menu();
                    Sleep(100);
                    break;
                case 3:
                    selected = 2;
                    menu();
                    Sleep(100);
                    break;
                default:
                    break;
                }
            }


            if (GetAsyncKeyState(VK_DOWN)) {
                switch (selected) {
                case 1:
                    selected = 2;
                    menu();
                    Sleep(100);
                    break;
                case 2:
                    selected = 3;
                    menu();
                    Sleep(100);
                    break;
                default:
                    break;
                }
            }
        }

        if (GetAsyncKeyState(toggleAC)) {
            if (toggled) {
                toggled = false;
                menu();
                Sleep(250);
            }
            else {
                toggled = true;
                menu();
                Sleep(250);
            }
        }

        if (GetAsyncKeyState(toggleSounds)) {
            if (toggledSounds) {
                toggledSounds = false;
                menu();
                Sleep(250);
            }
            else {
                toggledSounds = true;
                menu();
                Sleep(250);
            }
        }

        if (GetAsyncKeyState(toggleJitter)) {
            if (toggledJitter) {
                toggledJitter = false;
                menu();
                Sleep(250);
            }
            else {
                toggledJitter = true;
                menu();
                Sleep(250);
            }
        }


        if (GetAsyncKeyState(toggleWindow)) {
            if (::IsWindowVisible(::GetConsoleWindow()) == TRUE)
            {
                ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
                Sleep(250);
            }
            else if (::IsWindowVisible(::GetConsoleWindow()) == FALSE)
            {
                ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
                Sleep(250);
            }
        }


        if (GetAsyncKeyState(VK_HOME)) {
            if (hWndCur == console) {
                cout << endl;
                cout << AY_OBFUSCATE(" Toggle Autoclicker: ");
                Sleep(750);

                int a = 0;
                while (a == 0) {
                    for (int i = 3; i < 256; i++)
                    {
                        if (GetAsyncKeyState((i)))
                        {
                            if (i < 256) {
                                if (!(*keys[i] == 0)) {
                                    a = 1;
                                    cout << keys[i];
                                    toggleAC = i;
                                    Sleep(500);
                                    continue;
                                }
                            }
                        }
                    }
                    Sleep(1);
                }

                cout << endl << AY_OBFUSCATE(" Toggle Sounds: ");
                Sleep(750);

                int b = 0;
                while (b == 0) {
                    for (int i = 3; i < 256; i++)
                    {
                        if (GetAsyncKeyState((i)))
                        {
                            if (i < 256) {
                                if (!(*keys[i] == 0)) {
                                    if (!(i == toggleAC)) {
                                        b = 1;
                                        cout << keys[i];
                                        toggleSounds = i;
                                        Sleep(50);
                                    }
                                }
                            }

                        }
                    }
                    Sleep(1);
                }

                cout << endl << AY_OBFUSCATE(" Toggle Jitter: ");
                Sleep(750);

                b = 0;
                while (b == 0) {
                    for (int i = 3; i < 256; i++)
                    {
                        if (GetAsyncKeyState((i)))
                        {
                            if (i < 256) {
                                if (!(*keys[i] == 0)) {
                                    if (!(i == toggleAC)) {
                                        if (!(i == toggleSounds)) {
                                            b = 1;
                                            cout << keys[i];
                                            toggleJitter = i;
                                            Sleep(50);
                                        }
                                    }
                                }
                            }

                        }
                    }
                    Sleep(1);
                }

                cout << endl << AY_OBFUSCATE(" Toggle Window: ");
                Sleep(750);

                b = 0;
                while (b == 0) {
                    for (int i = 3; i < 256; i++)
                    {
                        if (GetAsyncKeyState((i)))
                        {
                            if (i < 256) {
                                if (!(*keys[i] == 0)) {
                                    if (!(i == toggleAC)) {
                                        if (!(i == toggleSounds)) {
                                            if (!(i == toggleJitter)) {
                                                b = 1;
                                                cout << keys[i];
                                                toggleWindow = i;
                                                Sleep(50);
                                            }
                                        }
                                    }
                                }
                            }

                        }
                    }
                    Sleep(1);
                }

                menu();
            }
        }


        if (toggled) {
            if (hWndCur == hWnd) {

                bool first = true;

                while (GetAsyncKeyState(VK_LBUTTON)) {
                    if (first) {
                        first = false;
                        if (toggledSounds) {
                            auto r_thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)clickSound, nullptr, 0, nullptr);
                            CloseHandle(r_thread);
                        }
                        if (randomInt(1, 10) == 2) Sleep((int)(generate_random_float(1000. / cpsMin, 1000. / cpsMax)) - (randomInt(9, 32)));
                        else Sleep((int)(generate_random_float(1000. / cpsMin, 1000. / cpsMax)) >> 1);
                        continue;
                    }

                    if (randomInt(1, 9) == 2) continue;

                    GetCursorPos(&pt);
                    SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));
                    if (toggledSounds) {
                        auto r_thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)clickSound, nullptr, 0, nullptr);
                        CloseHandle(r_thread);
                    }
                    if (jitter > 0) {
                        if (toggledJitter) {
                            SetCursorPos(pt.x - (generate_random_float(-jitter, jitter)), pt.y - (generate_random_float(-jitter, jitter)));
                        }
                    }
                    if (randomInt(1, 10) == 2) Sleep((int)(generate_random_float(1000. / cpsMin, 1000. / cpsMax)) - (randomInt(9, 32)));
                    else Sleep((int)(generate_random_float(1000. / cpsMin, 1000. / cpsMax)) >> 1);
                    SendMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
                    if (randomInt(1, 10) == 2) Sleep((int)(generate_random_float(1000. / cpsMin, 1000. / cpsMax)) - (randomInt(9, 32)));
                    else Sleep((int)(generate_random_float(1000. / cpsMin, 1000. / cpsMax)) >> 1);
                }
            }
        }
    }
}

#define OBF_END } catch(std::shared_ptr<obf::base_rvholder>& r) { return *r; } catch (...) {throw;}