#include "pch.h"
#include "framework.h"
#include "Client.h"

#include "SoundManager.h"
#include "GameProcess.h"

#define MAX_LOADSTRING 100
#define WINSIZEX 1920
#define WINSIZEY 1080

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
HWND	  g_hWnd;								// 메인 윈도우 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

MONITORINFOEX monitorInfo;
WINDOWPLACEMENT g_wpPrev;
bool zoomMonitor;

int g_screenWidth;
int g_screenHeight;
// 전체 화면 모드로 전환

void ChangeScreenResolution(int width, int height)
{
	DEVMODE devMode;
	devMode.dmSize = sizeof(DEVMODE);
	devMode.dmDriverExtra = 0;
	EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &devMode);

	devMode.dmPelsWidth = width;
	devMode.dmPelsHeight = height;


	LONG result = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	if (result != DISP_CHANGE_SUCCESSFUL)
	{
		// 모니터 해상도 변경 실패 처리
	}
}
// SAL 주석 : _In_, _In_opt_ ...
int APIENTRY wWinMain(_In_ HINSTANCE hInstance  // HINSTANCE는 프로세스가 시작되는 메모리 주소, 실행 된 프로세스의 시작 주소
	, _In_opt_ HINSTANCE hPrevInstance // 이전 메모리 주소, 가상 메모리 시스템이 들어오기 이전에 해당됨
	, _In_ LPWSTR lpCmdLine     // 추가적인 인자로 문자열을 넣어줌. 사용 안함
	, _In_ int nCmdShow)
{
	// 메모리 릭(누수) 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(36647);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	
	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);


	g_screenWidth = GetSystemMetrics(SM_CXSCREEN);
	g_screenHeight = GetSystemMetrics(SM_CYSCREEN);
	// 윈도우 정보 등록
	MyRegisterClass(hInstance);

	// 윈도우 생성
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Core 초기화 
	/// 이제 싱글톤 안쓴당
	/// 정창도
// 	if (FAILED(GameProcess::GetInst()->Initialize(g_hWnd, POINT{ 1920, 1080 })))
// 	{
// 		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
// 
// 		return FALSE;
// 	}

	// 단축키 테이블 정보 로딩
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;


	// GetMessage
	// 메시지 큐에서 메시지 확인될 때까지 대기
	// msg.message == WM_QUIT 인 경우 false를 반환 -> 프로그램 종료

	// PeekMessage
	// 메세지 유무와 관계없이 반환
	//


	GameProcess* gameProcess = new GameProcess;
	
	assert(gameProcess);

	if (FAILED(gameProcess->Initialize(g_hWnd, POINT{ 1920, 1080 })))
	{
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

		return FALSE;
	}

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		// 메세지가 발생하지 않는 대부분의 시간
		else
		{
			// Game 코드 수행
			// 디자인 패턴(설계 유형)
			// 싱글톤 패턴
			gameProcess->Progress();
		}
	}

	delete gameProcess;


	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_CLIENT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_hWnd = CreateWindowW(szWindowClass, L"Visible", WS_POPUP,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_F11)
		{
			// F11 키를 누르면 전체 화면 모드로 전환 또는 복원
			MONITORINFO monitorInfo;
			monitorInfo.cbSize = sizeof(MONITORINFO);
			GetMonitorInfo(MonitorFromWindow(g_hWnd, MONITOR_DEFAULTTONEAREST), &monitorInfo);

			if (monitorInfo.dwFlags & MONITORINFOF_PRIMARY)
			{
				if (zoomMonitor)
					ChangeScreenResolution(g_screenWidth, g_screenHeight);
				else
				{
					// 현재 윈도우 위치와 크기 저장
// 					g_wpPrev.length = sizeof(WINDOWPLACEMENT);
// 					GetWindowPlacement(g_hWnd, &g_wpPrev);
// 
// 					SetFullscreen();
					ChangeScreenResolution(1920, 1080);
					zoomMonitor = true;
				}
			}
		}
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:	// 무효화 영역(Invalidate)이 발생한 경우
	{
		PAINTSTRUCT ps;

		// Device Context 만들어서 ID를 반환
		HDC hdc = BeginPaint(hWnd, &ps);	// Device Context (그리기)

		//Rectangle(hdc, 1180, 668, 1280, 768);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_MOUSEMOVE:

		break;

	case WM_LBUTTONUP:

		break;

	case WM_DESTROY:
		ChangeScreenResolution(g_screenWidth, g_screenHeight);
		SoundManager::GetInst()->EndSound();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
