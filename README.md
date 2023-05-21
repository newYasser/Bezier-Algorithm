# Bezier Curve Drawing

This program demonstrates drawing a Bezier curve using the Windows API.

## Prerequisites

- Windows operating system
- C++ compiler
- Windows SDK

## Getting Started

1. Include the necessary header files:
```cpp
#include <Windows.h>
using namespace std;
```

2. Define a `point` structure to represent a point with x and y coordinates:
```cpp
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
```

3. Define a helper function `Round` to round a floating-point number to the nearest integer:
```cpp
int Round(double x)
{
    return (int)(x + 0.5);
}
```

4. Implement the `DrawHermiteCurve` function to draw a Hermite curve given four control points:
```cpp
void DrawHermiteCurve(HDC hdc, point p1, point T1, point p2, point T2, COLORREF color)
{
    // Calculate alpha and beta values for the Hermite curve
    // ...

    // Iterate over t from 0 to 1 and calculate x and y coordinates
    // ...

    // Use SetPixel to draw each point of the curve
    // ...
}
```

5. Implement the `DrawBezierCurve` function to draw a Bezier curve by converting it to a Hermite curve:
```cpp
void DrawBezierCurve(HDC hdc, point P0, point P1, point P2, point P3, COLORREF color)
{
    // Calculate the tangent vectors T0 and T1
    // ...

    // Use DrawHermiteCurve to draw the Bezier curve
    // ...
}
```

6. Implement the `MyWndProc` function as the window procedure to handle mouse events and drawing the Bezier curve:
```cpp
LRESULT WINAPI MyWndProc(HWND hWnd, UINT mcode, WPARAM wp, LPARAM lp)
{
    HDC hdc;

    static point points[4];
    static int idx = 0;
    switch (mcode)
    {
        case WM_LBUTTONDOWN:
            // Handle left mouse button click
            // ...

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
```

7. Implement the `WinMain` function as the entry point of the program:
```cpp
int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh)
{
    // Register the window class
    // ...

    // Create the window
    // ...

    // Enter the main message loop
    // ...

    return 0;
}
```

## Compilation and Execution

- Compile the source code using a C++ compiler with the Windows SDK.
- Run the compiled executable file.
- A window will appear, and you can click the left mouse button to draw Bezier curves by specifying four control points.

