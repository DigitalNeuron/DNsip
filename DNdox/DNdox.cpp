#include "DNdox.h"



NS_IMPL_ISUPPORTS1(DNdox, IDNdox)
void CreateImage(HWND hwnd);

DNdox::DNdox()
{
	/* member initializers and constructor code */
}

DNdox::~DNdox()
{
	/* destructor code */
}

/* long Add (in long a, in long b); */
NS_IMETHODIMP DNdox::Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM)
{
	HWND hContent = 0;
	HWND hFF = ::FindWindowEx(0, 0, LPWSTR("MozillaUIWindowClass"), 0);

	if (hFF) {
		// next we step down through a fixed structure
		HWND hTemp;
		hTemp = ::FindWindowEx(hFF, 0, LPWSTR("MozillaWindowClass"), 0);
		hTemp = ::FindWindowEx(hTemp, 0, LPWSTR("MozillaWindowClass"), 0);

		// assume only 1 window at this level has children
		// and the 1 with children is the one we want
		HWND hChild = ::GetWindow(hTemp, GW_CHILD);
		while (hTemp && !hChild) {
			hTemp = ::GetWindow(hTemp, GW_HWNDNEXT);
			hChild = ::GetWindow(hTemp, GW_CHILD);
		}

		// did we find a window with children?
		// that child is hopefully the content window
		if (hTemp) {
			hTemp = ::GetWindow(hTemp, GW_CHILD);
			hContent = ::FindWindowEx(hTemp, 0, LPWSTR("MozillaContentWindowClass"), 0);
		}
	}
	//CreateImage(hContent,"c:\\test.bmp");
CaptureAnImage(hContent);
	*_retval = a + b;
	return NS_OK;
}

int DNdox::CaptureAnImage(HWND hWnd)
{
	
    HDC hdcScreen;
    HDC hdcWindow;
    HDC hdcMemDC = NULL;
    HBITMAP hbmScreen = NULL;
    BITMAP bmpScreen;

    // Retrieve the handle to a display device context for the client 
    // area of the window. 
    hdcScreen = GetDC(NULL);
    hdcWindow = GetDC(hWnd);

    // Create a compatible DC which is used in a BitBlt from the window DC
    hdcMemDC = CreateCompatibleDC(hdcWindow); 

    if(!hdcMemDC)
    {
        MessageBox(hWnd, L"CreateCompatibleDC has failed",L"Failed", MB_OK);
        goto done;
    }

    // Get the client area for size calculation
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
/*
    //This is the best stretch mode
    SetStretchBltMode(hdcWindow,HALFTONE);

    //The source DC is the entire screen and the destination DC is the current window (HWND)
    if(!StretchBlt(hdcWindow, 
               0,0, 
               rcClient.right, rcClient.bottom, 
               hdcScreen, 
               0,0,
               GetSystemMetrics (SM_CXSCREEN),
               GetSystemMetrics (SM_CYSCREEN),
               SRCCOPY))
    {
        MessageBox(hWnd, L"StretchBlt has failed",L"Failed", MB_OK);
        goto done;
    }
 */   
    // Create a compatible bitmap from the Window DC
    //hbmScreen = CreateCompatibleBitmap(hdcWindow, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top);
	int maxY=GetSystemMetrics (SM_CYSCREEN);
	int maxX=GetSystemMetrics (SM_CXSCREEN);
     hbmScreen = CreateCompatibleBitmap(hdcWindow, maxX, maxY);
    if(!hbmScreen)
    {
        MessageBox(hWnd, L"CreateCompatibleBitmap Failed",L"Failed", MB_OK);
        goto done;
    }

    // Select the compatible bitmap into the compatible memory DC.
    SelectObject(hdcMemDC,hbmScreen);
    
    // Bit block transfer into our compatible memory DC.
    if(!BitBlt(hdcMemDC, 
               0,0, 
               maxX, maxY, 
               hdcWindow, 
               0,0,
               SRCCOPY))
    {
        MessageBox(hWnd, L"BitBlt has failed", L"Failed", MB_OK);
        goto done;
    }

    // Get the BITMAP from the HBITMAP
    GetObject(hbmScreen,sizeof(BITMAP),&bmpScreen);
     
    BITMAPFILEHEADER   bmfHeader;    
    BITMAPINFOHEADER   bi;
     
    bi.biSize = sizeof(BITMAPINFOHEADER);    
    bi.biWidth = bmpScreen.bmWidth;    
    bi.biHeight = bmpScreen.bmHeight;  
    bi.biPlanes = 1;    
    bi.biBitCount = 32;    
    bi.biCompression = BI_RGB;    
    bi.biSizeImage = 0;  
    bi.biXPelsPerMeter = 0;    
    bi.biYPelsPerMeter = 0;    
    bi.biClrUsed = 0;    
    bi.biClrImportant = 0;

    DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

    // Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
    // call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
    // have greater overhead than HeapAlloc.
    HANDLE hDIB = GlobalAlloc(GHND,dwBmpSize); 
    char *lpbitmap = (char *)GlobalLock(hDIB);    

    // Gets the "bits" from the bitmap and copies them into a buffer 
    // which is pointed to by lpbitmap.
    GetDIBits(hdcWindow, hbmScreen, 0,
        (UINT)bmpScreen.bmHeight,
        lpbitmap,
        (BITMAPINFO *)&bi, DIB_RGB_COLORS);

    // A file is created, this is where we will save the screen capture.
    HANDLE hFile = CreateFile(L"captureqwsx.bmp",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);   
    
    // Add the size of the headers to the size of the bitmap to get the total file size
    DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
 
    //Offset to where the actual bitmap bits start.
    bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER); 
    
    //Size of the file
    bmfHeader.bfSize = dwSizeofDIB; 
    
    //bfType must always be BM for Bitmaps
    bmfHeader.bfType = 0x4D42; //BM   
 
    DWORD dwBytesWritten = 0;
    WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);
    
    //Unlock and Free the DIB from the heap
    GlobalUnlock(hDIB);    
    GlobalFree(hDIB);

    //Close the handle for the file that was created
    CloseHandle(hFile);
       
    //Clean up
done:
    DeleteObject(hbmScreen);
    DeleteObject(hdcMemDC);
    ReleaseDC(NULL,hdcScreen);
    ReleaseDC(hWnd,hdcWindow);

    return 0;
}
/*
void DNdox::CreateImage(HWND window, const char* filename)
{
	MessageBox(window,LPCWSTR(window),LPCWSTR(window),MB_OK);
	
	// get screen rectangle 
	RECT windowRect; 
		int n;
	GetWindowRect(window, &windowRect); 
	// bitmap dimensions 
	int bitmap_dx = windowRect.right - windowRect.left; 
	int bitmap_dy = windowRect.bottom - windowRect.top; 
	// create file 
	//ofstream file(filename, ios::binary); 
	HANDLE out = CreateFile ( LPWSTR(filename), FILE_WRITE_DATA, 0, NULL,
    CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	//if(!file) return; 
	// save bitmap file headers 
	BITMAPFILEHEADER fileHeader; 
	BITMAPINFOHEADER infoHeader; 
	fileHeader.bfType      = 0x4d42; 
	fileHeader.bfSize      = 0; 
	fileHeader.bfReserved1 = 0; 
	fileHeader.bfReserved2 = 0; 
	fileHeader.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); infoHeader.biSize          = sizeof(infoHeader); 
	infoHeader.biWidth         = bitmap_dx; 
	infoHeader.biHeight        = bitmap_dy; 
	infoHeader.biPlanes        = 1; 
	infoHeader.biBitCount      = 24; 
	infoHeader.biCompression   = BI_RGB; 
	infoHeader.biSizeImage     = 0; 
	infoHeader.biXPelsPerMeter = 0; 
	infoHeader.biYPelsPerMeter = 0; 
	infoHeader.biClrUsed       = 0; 
	infoHeader.biClrImportant  = 0; 
//	file.write((char*)&fileHeader, sizeof(fileHeader)); 
//	file.write((char*)&infoHeader, sizeof(infoHeader));
	WriteFile ( out, (char*)&fileHeader, sizeof fileHeader, LPDWORD(&n), NULL );
	WriteFile ( out, (char*)&infoHeader, sizeof infoHeader, LPDWORD(&n), NULL );
	// dibsection information 
	BITMAPINFO info; info.bmiHeader = infoHeader;  
	// ------------------ // THE IMPORTANT CODE // ------------------ // create a dibsection and blit the window contents to the bitmap 
	HDC winDC = GetWindowDC(window); 
	HDC memDC = CreateCompatibleDC(winDC); 
	BYTE* memory = 0; 
	HBITMAP bitmap = CreateDIBSection(winDC, &info, DIB_RGB_COLORS, (void**)&memory, 0, 0); 
	SelectObject(memDC, bitmap); 
	BitBlt(memDC, 0, 0, bitmap_dx, bitmap_dy, winDC, 0, 0, SRCCOPY); 
	DeleteDC(memDC); 
	ReleaseDC(window, winDC); // save dibsection data 
	int bytes = (((24*bitmap_dx + 31) & (~31))/8)*bitmap_dy; 
	//file.write(memory, bytes); // HA HA, forgot paste in the DeleteObject lol, happy now ;)? 
	MessageBox(window,LPCWSTR(bytes),LPCWSTR(bytes),MB_OK);
	WriteFile ( out, LPCVOID(bytes), sizeof bytes, LPDWORD(&n), NULL );
  CloseHandle ( out );
	DeleteObject(bitmap);

}*/