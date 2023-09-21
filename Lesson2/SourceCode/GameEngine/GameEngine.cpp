// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include <INIReader.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();

    GameObject* cube = new CubeGameObject();
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();
    float speed = 10.0f;

    std::map<std::string, char> keysConfig;
    INIReader reader("keys.ini");

    if (reader.ParseError() < 0)
    {
        keysConfig["GoUp"] = 'w';
        keysConfig["GoDown"] = 's';
        keysConfig["GoLeft"] = 'a';
        keysConfig["GoRight"] = 'd';
    }
    else
    {
        keysConfig["GoUp"] = reader.Get("Keyboard", "GoUp", "w")[0];
        keysConfig["GoDown"] = reader.Get("Keyboard", "GoDown", "s")[0];
        keysConfig["GoLeft"] = reader.Get("Keyboard", "GoLeft", "a")[0];
        keysConfig["GoRight"] = reader.Get("Keyboard", "GoRight", "d")[0];
    }

    cube->SetPosition(0.0f, 0.0f, 0.0f);

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            timer.Tick();

            if (GetAsyncKeyState(VkKeyScanEx(keysConfig["GoUp"], GetKeyboardLayout(GetCurrentThreadId()))) & 0x8000)
            {
                cube->ShiftPosition(0.0f, speed * timer.DeltaTime(), 0.0f);
            }

            if (GetAsyncKeyState(VkKeyScanEx(keysConfig["GoDown"], GetKeyboardLayout(GetCurrentThreadId()))) & 0x8000)
            {
                cube->ShiftPosition(0.0f, -speed * timer.DeltaTime(), 0.0f);
            }

            if (GetAsyncKeyState(VkKeyScanEx(keysConfig["GoLeft"], GetKeyboardLayout(GetCurrentThreadId()))) & 0x8000)
            {
                cube->ShiftPosition(-speed * timer.DeltaTime(), 0.0f, 0.0f);
            }

            if (GetAsyncKeyState(VkKeyScanEx(keysConfig["GoRight"], GetKeyboardLayout(GetCurrentThreadId()))) & 0x8000)
            {
                cube->ShiftPosition(speed * timer.DeltaTime(), 0.0f, 0.0f);
            }

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
