#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

/////////////////////
// GLOBALS
//
/// Define a structure to hold all
/// of the global variables of this app.
struct Globals
{
    HINSTANCE hInstance;    // window app instance

    HWND hwnd;      // handle for the window

    HDC   hdc;      // handle to device context

    HGLRC hglrc;    // handle to OpenGL rendering context
    
    int width, height;      // the desired width and
    // height of the CLIENT AREA
    // (DRAWABLE REGION in Window)
};


///////////////////////////
// GLOBALS
// declare one struct Globals called g;
Globals g;
//
///////////////////////////


// Function prototypes.
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow );
void draw();            // drawing function containing OpenGL function calls

////////////////////////////
// In a C++ Windows app, the starting point is WinMain().
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow )
{
    //Store hinstance
    g.hInstance = hInstance;

    // Create the WNDCLASS
    WNDCLASS wc;
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );         
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );     
    wc.hInstance = hInstance;         
    wc.lpfnWndProc = WndProc;         
    wc.lpszClassName = TEXT("GameEngine");
    wc.lpszMenuName = 0; 
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

    // Register that class with the Windows O/S..
	RegisterClass(&wc);
    
    //create the RECT for our window as follows:
    RECT rect;
    SetRect( &rect, 50,  // left
                    50,  // top
                    850, // right
                    650 ); // bottom
    
    // Save width and height
    g.width = rect.right - rect.left;
    g.height = rect.bottom - rect.top;
    
    // Adjust it.
    AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );

    ///////////////////
    // NOW we call CreateWindow, using
    // that adjusted RECT structure to
    // specify the width and height of the window.
    g.hwnd = CreateWindow(TEXT("Game Engine"),
                          TEXT("Game Engine"),
                          WS_OVERLAPPEDWINDOW,
                          rect.left, rect.top,  // adjusted x, y positions
                          rect.right - rect.left, rect.bottom - rect.top,  // adjusted width and height
                          NULL, NULL,
                          hInstance, NULL);

    // check to see that the window
    // was created successfully!
    if( g.hwnd == NULL )
    {
        FatalAppExit( NULL, TEXT("CreateWindow() failed!") );
    }

    // and show.
    ShowWindow( g.hwnd, iCmdShow );

    //GET DC OF WINDOW
    g.hdc = GetDC( g.hwnd );

    // A PIXEL FORMAT just describes the
    // "qualities" that each pixel in the 
    // window will have.  Do you want your
    // OpenGL app to use 24 bit color
    // ("true color" -- really high
    // quality!)?  Or 16 bit color (can look
    // a bit washed out)?

    //Create descriptor
    PIXELFORMATDESCRIPTOR pfd = { 0 };  // create the pfd,
	
    //set only the fields of the pfd we care about:
    pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );    // just its size
    pfd.nVersion = 1;   // always 1

    pfd.dwFlags = PFD_SUPPORT_OPENGL |  // OpenGL support - not DirectDraw
                  PFD_DOUBLEBUFFER   |  // double buffering support
                  PFD_DRAW_TO_WINDOW;   // draw to the app window, not to a bitmap image

    pfd.iPixelType = PFD_TYPE_RGBA ;    // red, green, blue, alpha for each pixel
    pfd.cColorBits = 24;                // 24 bit == 8 bits for red, 8 for green, 8 for blue.
                                        // This count of color bits EXCLUDES alpha.

    pfd.cDepthBits = 32;                // 32 bits to measure pixel depth

    int chosenPixelFormat = ChoosePixelFormat( g.hdc, &pfd );
	//Check for error with chosen pixel format
    if( chosenPixelFormat == 0 )
    {
        FatalAppExit( NULL, TEXT("ChoosePixelFormat() failed!") );
    }
    
    //Set the pixel format
    int result = SetPixelFormat( g.hdc, chosenPixelFormat, &pfd );

    if (result == NULL)
    {
        FatalAppExit( NULL, TEXT("SetPixelFormat() failed!") );
    }

	//Create the drawing context
    g.hglrc = wglCreateContext( g.hdc );

	//Connect Render context with Draw context
    wglMakeCurrent( g.hdc, g.hglrc );

	//Begin the message loop
    MSG msg;

    while( 1 )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            if( msg.message == WM_QUIT )
            {
                break;
            }
            
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            //Call the draw method
            draw();
        }
    }
  
    // Remove the render context
    wglMakeCurrent( NULL, NULL );

    // Delete the rendering context, we no longer need it.
    wglDeleteContext( g.hglrc );

    // release your window's DC
    ReleaseDC( g.hwnd, g.hdc );

    return msg.wParam;
}

////////////////////////
// DRAWING FUNCTION
void draw() 
{
   
}





////////////////////////
// WNDPROC
// Notice that WndProc is very very neglected.
// We hardly do anything with it!  That's because
// we do all of our processing in the draw()
// function.
LRESULT CALLBACK WndProc(   HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam ) 
{
    switch( message )
    {
    case WM_CREATE:
        Beep( 50, 10 );
        return 0;
        break;

    case WM_PAINT:
        {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint( hwnd, &ps );
                // don't draw here.  would be waaay too slow.
                // draw in the draw() function instead.
            EndPaint( hwnd, &ps );
        }
        return 0;
        break;

    case WM_KEYDOWN:
        switch( wparam )
        {
        case VK_ESCAPE:
            PostQuitMessage( 0 );
            break;
        default:
            break;
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage( 0 ) ;
        return 0;
        break;
    }
 
    return DefWindowProc( hwnd, message, wparam, lparam );
}


