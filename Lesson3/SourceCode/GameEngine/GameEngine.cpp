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
#include "InputHandler.h"
#include "UpdatableVector.h"
#include "ControllableCube.h"
#include "JumpingCube.h"
#include "MovingCube.h"

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
    InputHandler* inputHandler = new InputHandler();
    UpdatableVector uvec = UpdatableVector();
    srand(time(0));

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            GameObject* cube;
            switch (rand() % 3)
            {
            case 0:
                cube = new JumpingCube(-20.0f);
                break;
            case 1:
                cube = new ControllableCube(inputHandler);
                break;
            case 2:
                cube = new MovingCube();
                break;

            default:
                cube = new CubeGameObject();
                break;
            }

            cube->SetPosition(-15.0f + 3.0f * i, -20.0f, 3.0f * j);
            renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());
            uvec.push_back(cube);
        }
    }

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float newPositionX = 0.0f;

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
            inputHandler->Update();
            timer.Tick();

            uvec.update(timer.DeltaTime());

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
