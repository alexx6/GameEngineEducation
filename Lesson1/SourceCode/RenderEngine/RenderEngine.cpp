#include <bx/math.h>

#include "RenderEngine.h"

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

CRenderEngine::CRenderEngine(HINSTANCE hInstance)
{
	assert(!m_hwnd);
	m_hwnd = InitMainWindow(hInstance);
	assert(m_hwnd);

	bgfx::renderFrame();

	bgfx::Init bgfxInit;
	bgfxInit.type = bgfx::RendererType::Direct3D11;
	bgfxInit.resolution.width = m_Width;
	bgfxInit.resolution.height = m_Height;
	bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
	bgfxInit.platformData.nwh = m_hwnd;
	if (!bgfx::init(bgfxInit))
		assert(0);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xffaa88bb, 1.0f, 0);
	bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

	m_defaultCube = new Cube();
	m_myShape = new MyShape();
	timePoint = std::chrono::high_resolution_clock::now();
	elapsedTime = 0.0f;
}

CRenderEngine::~CRenderEngine()
{
	bgfx::shutdown();
	DestroyWindow(m_hwnd);
}

HWND CRenderEngine::InitMainWindow(HINSTANCE hInstance)
{
	std::wstring wstrWindowName = L"MainWnd";
	std::wstring wstrWindowCaption = L"GameEngine";

	HWND hwnd = nullptr;

	WNDCLASSEXW wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = wstrWindowName.c_str();
	wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return hwnd;
	}

	DWORD borderlessStyle = WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
	DWORD defaultStyle = WS_OVERLAPPEDWINDOW;

	RECT R = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&R, defaultStyle, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	hwnd = CreateWindow(wstrWindowName.c_str(), wstrWindowCaption.c_str(),
		defaultStyle, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);
	if (!hwnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return hwnd;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return hwnd;
}

void CRenderEngine::Update()
{
	const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
	const bx::Vec3 eye = { 0.0f, 10.0f, -5.0f };
	float view[16];
	bx::mtxLookAt(view, eye, at);
	float proj[16];
	bx::mtxProj(proj, 60.0f, float(m_Width) / float(m_Height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform(0, view, proj);


	std::chrono::steady_clock::time_point curTime = std::chrono::high_resolution_clock::now();

	float tm[16];
	bx::mtxTranslate(tm, 0.0f, 5.0f * bx::sin(elapsedTime), 0.0f);

	float rm[16];
	bx::mtxRotateXY(rm, 1.0f * elapsedTime, bx::cos(elapsedTime));

	
	float resm[16];
	bx::mtxMul(resm, tm, rm);

	elapsedTime += std::chrono::duration_cast<std::chrono::milliseconds>(curTime - timePoint).count() / 1000.0f;
	timePoint = curTime;
	bgfx::setVertexBuffer(0, m_myShape->GetVertexBuffer());
	bgfx::setIndexBuffer(m_myShape->GetIndexBuffer());
	bgfx::setTransform(resm);

	bgfx::submit(0, m_myShape->GetProgramHandle());

	bgfx::touch(0);

	bgfx::frame();
}