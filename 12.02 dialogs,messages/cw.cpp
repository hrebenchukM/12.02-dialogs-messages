//#include <windows.h>
//#include <tchar.h>
//#include "resource.h"
//
//


//BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
//
//HWND hStatic1, hStatic2;
//TCHAR szCoordinates[20];
//HINSTANCE hInst;
//const int LEFT = 15, TOP = 110, WIDTH = 380, HEIGHT = 50;
//
//int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
//{
//	hInst = hInstance;
//	// создаём главное окно приложения на основе модального диалога
//	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
//}
//
//BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_CLOSE:
//		EndDialog(hWnd, 0); // закрываем модальный диалог
//		return TRUE;
//		// WM_INITDIALOG - данное сообщение приходит после создания диалогового окна, но перед его отображением на экран
//	case WM_INITDIALOG:
//		hStatic1 = GetDlgItem(hWnd, IDC_STATIC1); // получаем дескриптор статика, размещенного на форме диалога
//		//создаём статик с помощью CreateWindowEx
//		hStatic2 = CreateWindowEx(0, TEXT("STATIC"), 0,
//			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
//			LEFT, TOP, WIDTH, HEIGHT, hWnd, 0, hInst, 0);
//		return TRUE;
//	case WM_MOUSEMOVE:
//		wsprintf(szCoordinates, TEXT("X=%d  Y=%d"), LOWORD(lParam), HIWORD(lParam)); // текущие координаты курсора мыши
//		SetWindowText(hStatic1, szCoordinates);	// строка выводится на статик
//		return TRUE;
//	case WM_LBUTTONDOWN:
//		SetWindowText(hStatic2, TEXT("Нажата левая кнопка мыши"));
//		return TRUE;
//	case WM_RBUTTONDOWN:
//		SetWindowText(hStatic2, TEXT("Нажата правая кнопка мыши"));
//		return TRUE;
//	}
//	return FALSE;
//}

/*BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	// создаём главное окно приложения на основе модального диалога
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL,(DLGPROC) DlgProc);//явное преобразование последнего параметра
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0); // закрываем модальный диалог
		return TRUE;
	}
	return FALSE;
}*/