#include <QCoreApplication>
#include <QSettings>

#include <iostream>
#include <windows.h>
#include <mmsystem.h>

/*
 * delimetr = VK_DIVIDE
 * mul = VK_MULTIPLY
 * minus = VK_SUBTRACT
 * plus = VK_ADD
 * dot = VK_DECIMAL
 * 0 = VK_NUMPAD0
 * 1 = VK_NUMPAD1
 * 2 = VK_NUMPAD2
 * 3 = VK_NUMPAD3
 * 4 = VK_NUMPAD4
 * 5 = VK_NUMPAD5
 * 6 = VK_NUMPAD6
 * 7 = VK_NUMPAD7
 * 8 = VK_NUMPAD8
 * 9 = VK_NUMPAD9
 */


// Функция обратного вызова для глобального хука клавиатуры
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {

    QSettings set("Settings.ini", QSettings::IniFormat);

    QString divide = set.value("Audio/Slash").toString();
    QString multiply = set.value("Audio/Zvezd").toString();
    QString subtract = set.value("Audio/Minus").toString();
    QString add = set.value("Audio/Plus").toString();
    QString decimal = set.value("Audio/Dot").toString();
    QString num0 = set.value("Audio/num0").toString();
    QString num1 = set.value("Audio/num1").toString();
    QString num2 = set.value("Audio/num2").toString();
    QString num3 = set.value("Audio/num3").toString();
    QString num4 = set.value("Audio/num4").toString();
    QString num5 = set.value("Audio/num5").toString();
    QString num6 = set.value("Audio/num6").toString();
    QString num7 = set.value("Audio/num7").toString();
    QString num8 = set.value("Audio/num8").toString();
    QString num9 = set.value("Audio/num9").toString();

    std::wstring res;

    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

        switch(p->vkCode) {
            case VK_DIVIDE:
                res = (divide.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
            break;

            case VK_MULTIPLY:
                res = (multiply.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
            break;

            case VK_SUBTRACT:
                res = (subtract.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
            break;

            case VK_ADD:
                res = (add.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_DECIMAL:
                res = (decimal.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD0:
                res = (num0.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD1:
                res = (num1.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD2:
                res = (num2.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD3:
                res = (num3.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD4:
                res = (num4.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD5:
                res = (num5.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD6:
                res = (num6.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD7:
                res = (num7.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD8:
                res = (num8.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case VK_NUMPAD9:
                res = (num9.toStdWString());
                PlaySound(res.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                break;
        }

    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Установка глобального хука
    HHOOK hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    if (!hKeyboardHook) {
        std::cerr << "Не удалось установить хук клавиатуры." << std::endl;
        return -1;
    }

    // Цикл обработки сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Отключение хука перед выходом
    UnhookWindowsHookEx(hKeyboardHook);

    return a.exec();
}
