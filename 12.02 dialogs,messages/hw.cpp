#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

TCHAR str1[20];
HWND mystatic;
HINSTANCE hInst1;
int staticCount = 0; // ���������� ������ ��������(�� ����������)
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst1 = hInst;
	MSG msg;
	// ������ ������� ���� ���������� �� ������ ������������ �������
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
	// ���������� ����
	ShowWindow(hDialog, nCmdShow);
	//��������� ���� ��������� ���������
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

int x, y;
BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	switch (mes)
	{
	case WM_CLOSE:
		// ��������� ����������� ������
		DestroyWindow(hWnd); // ��������� ����
		PostQuitMessage(0); // ������������� ���� ��������� ���������
		return TRUE;
	case WM_MOUSEMOVE:
		wsprintf(str1, TEXT("X=%d  Y=%d"), LOWORD(lp), HIWORD(lp)); // ������� ���������� ������� ����
		SetWindowText(hWnd, str1);
		break;
	case WM_LBUTTONDOWN:
	{
		x = LOWORD(lp);
		y = HIWORD(lp);

	}
	break;
	case WM_LBUTTONUP:
	{
		int width = LOWORD(lp) - x;
		int height = HIWORD(lp) - y;
		// ���������, ��� ������� ������� �� ������ 10�10

		//2)����������� ������ �������� ���������� 10�10, � ��� ������� �������� �������� ���������� ������� ��������
		//  ������������ ������ ������� ��������������� ��������������.
		if (width < 10 || height < 10)
		{
			MessageBox(hWnd, TEXT("������� ������� ������ ���� �� ������ 10�10!"), TEXT("�������������� ��� ����,������� �� ��� ������������!!!"), MB_OK | MB_ICONWARNING);
			break;
		}
		
		mystatic = CreateWindowEx(0, TEXT("STATIC"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
			x, y, width, height, hWnd, 0, hInst1, 0);
		staticCount++;
		TCHAR staticInfo[100];
		wsprintf(staticInfo, TEXT("������ �%d: ������=%d, ������=%d, X=%d, Y=%d"), staticCount, width, height, x, y);
		SetWindowText(hWnd, staticInfo);
	}

	return FALSE;
}





//
//
//1)������������ �������� ����� ������� ���� �� ����� ������� �, �� �������� ������, ���� �� ��� �����, � � ������ ���������� ������ �� ���������� ����������� ��������������(��� ��������, ���� ����� �� ��������� ���������� ��� �������� ��������������) �������� �������, ������� �������� ���� ���������� �����(������� � ���� ������� ��������� �������� �� �����).
//3)��� ������ ������ ������� ���� ��� ������������ �������� � ��������� ���� ������ ��������� ���������� � �������(���������� ����� ��������, ������ � ������, � ����� ���������� �������� ������������ ������������� ����).� ������ ���� � ����� ������ ��������� ��������� ���������, TO ������������ �������� �������� ���������� ���������� �������.C
//
//4)��� ������� ������ ����� ������ ���� ��� ������������ << ������� �� ������ ��������� � �����(��� ����� ����� ��������������� �������� DestroyWindow, ������� � ��� ���������������� ������� ��������).� ������ ���� � ����� ������ ��������� ��������� ���������, �� ������������ �������� �������� � ���������� ���������� �������.
//
