#include <Windows.h>
using namespace std;
struct point
{
    int x, y;
    point() {
        x = 0; y = 0;
    }

    point(int x, int y) {
        this->x = x; this->y = y;
    }
};
int Round(double x)
{
    return (int)(x + 0.5);
}

void DrawHermiteCurve(HDC hdc, point p1, point T1, point p2, point T2, COLORREF color)
{

    double alpha0 = p1.x,
            alpha1 = T1.x,
            alpha2 = -3 * p1.x - 2 * T1.x + 3 * p2.x - T2.x,
            alpha3 = 2 * p1.x + T1.x - 2 * p2.x + T2.x;
    double beta0 = p1.y,
            beta1 = T1.y,
            beta2 = -3 * p1.y - 2 * T1.y + 3 * p2.y - T2.y,
            beta3 = 2 * p1.y + T1.y - 2 * p2.y + T2.y;
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t,
                t3 = t2 * t;
        double x = alpha0 + alpha1 * t + alpha2 * t2 + alpha3 * t3;
        double y = beta0 + beta1 * t + beta2 * t2 + beta3 * t3;

        SetPixel(hdc, Round(x), Round(y), color);
    }
}
void DrawBezierCurve(HDC hdc, point P0, point P1, point P2, point P3, COLORREF color)
{
    point T0;
    T0.x = (3 * (P1.x - P0.x));
    T0.y = 3 * (P1.y - P0.y);
    point T1;
    T1.x = (3 * (P3.x - P2.x));
    T1.y = 3 * (P3.y - P2.y);
    DrawHermiteCurve(hdc, P0, T0, P3, T1, color);
}

LRESULT WINAPI MyWndProc(HWND hWnd, UINT mcode, WPARAM wp, LPARAM lp)
{
    HDC hdc;

    static point points[4];
    static int idx = 0;
    switch (mcode)
    {
        case WM_LBUTTONDOWN:
            if (idx < 4)
            {
                point p;
                p = point(LOWORD(lp),HIWORD(lp));
                points[idx++] = p;

                if (idx == 4)
                {
                    hdc = GetDC(hWnd);
                    DrawBezierCurve( hdc, points[0],points[1],  points[2], points[3], RGB(255,0,0));
                    idx = 0;
                }
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default: return DefWindowProc(hWnd, mcode, wp, lp);
    }
    return 0;
}
int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh)
{
    WNDCLASS wc;
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hinst;
    wc.lpfnWndProc = MyWndProc;
    wc.lpszClassName = reinterpret_cast<LPCSTR>(L"MyClass");
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow(reinterpret_cast<LPCSTR>(L"MyClass"), reinterpret_cast<LPCSTR>(L"My First Window"), WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hinst, 0);
    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}