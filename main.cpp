#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

// 4. The Window Procedure (The Brains of the Window)
// Every time you click, move, or resize the window, Windows calls this function.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0); // Tell the message loop to exit when the 'X' is clicked
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // We would draw here, but Vulkan will handle this later.
        // For now, we just fill it with a basic system color.
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
        return 0;
    }
    }
    // Let Windows handle any events we didn't explicitly catch
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// 1. The Entry Point (Replaces int main)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    // 2. Register the Window Class
    // This tells Windows what our window will look like and how it behaves.
    const wchar_t CLASS_NAME[] = L"MyCustomGUILibraryClass";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc; // Attach our event callback function
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // 3. Create the Window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"C++ GUI",        // Window text (Title bar)
        WS_OVERLAPPEDWINDOW,            // Window style (standard window with borders/buttons)

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // 5. The Message Loop (The Heartbeat)
    // This loop runs forever, pulling events from the OS and sending them to our WindowProc
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}