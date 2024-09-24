#include <iostream>
#include <windows.h>
#include <dbt.h>

// Window procedure to handle device notifications
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DEVICECHANGE) {
        if (wParam == DBT_DEVICEARRIVAL) {
            std::cout << "USB drive detected! Welcome!\n";
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Create a hidden window to listen for device notifications
HWND createHiddenWindow() {
    WNDCLASSW wc = {};  // Use WNDCLASSW for wide character support
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"USBDetectionWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassW(&wc)) {  // Use RegisterClassW
        std::cerr << "Failed to register window class.\n";
        return NULL;
    }

    HWND hWnd = CreateWindowExW(
        0,
        L"USBDetectionWindow",
        L"USB Detection",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, wc.hInstance, NULL
    );

    if (!hWnd) {
        std::cerr << "Failed to create window.\n";
        return NULL;
    }

    return hWnd;
}

int main() {
    HWND hWnd = createHiddenWindow();
    if (!hWnd) return 1;

    // Set up device notification
    DEV_BROADCAST_HDR dbh = {};
    dbh.dbch_size = sizeof(DEV_BROADCAST_HDR);
    dbh.dbch_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    dbh.dbch_reserved = 0;

    HDEVNOTIFY hDevNotify = RegisterDeviceNotification(hWnd, &dbh, DEVICE_NOTIFY_WINDOW_HANDLE);
    if (!hDevNotify) {
        std::cerr << "Failed to register device notification.\n";
        return 1;
    }

    std::cout << "Please insert your flash drive...\n";

    // Message loop to keep the application running
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up
    UnregisterDeviceNotification(hDevNotify);
    return 0;
}
