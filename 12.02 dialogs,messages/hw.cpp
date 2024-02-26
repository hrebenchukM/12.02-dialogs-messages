#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

TCHAR str1[20];
HWND mystatic[100]; // ������ ��� �������� ������� ��������
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



	//1)������������ �������� ����� ������� ���� �� ����� ������� �, �� �������� ������, ���� �� ��� �����,
	//  � � ������ ���������� ������ �� ���������� ����������� ��������������(��� ��������, ���� ����� �� ��������� ���������� ��� �������� ��������������)
	//  �������� �������, ������� �������� ���� ���������� �����(������� � ���� ������� ��������� �������� �� �����).
	case WM_LBUTTONUP:
	{
		int width = LOWORD(lp) - x;
		int height = HIWORD(lp) - y;
		

		//2)����������� ������ �������� ���������� 10�10, � ��� ������� �������� �������� ���������� ������� ��������
		//  ������������ ������ ������� ��������������� ��������������.
		if (width < 10 || height < 10)
		{
			MessageBox(hWnd, TEXT("������� ������� ������ ���� �� ������ 10�10!"), TEXT("�������������� ��� ����,������� �� ��� ������������!!!"), MB_OK | MB_ICONWARNING);
			break;
		}
		
		mystatic[staticCount] = CreateWindowEx(0, TEXT("STATIC"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
			x, y, width, height, hWnd, 0, hInst1, 0);
		staticCount++;
		TCHAR staticInfo[100];
		wsprintf(staticInfo, TEXT("������ �%d: ������=%d, ������=%d, X=%d, Y=%d"), staticCount, width, height, x, y);
		SetWindowText(hWnd, staticInfo);
	}

	return FALSE;



	//3)��� ������ ������ ������� ���� ��� ������������ �������� � ��������� ���� ������ ��������� ���������� � �������
	// (���������� ����� ��������, ������ � ������, � ����� ���������� �������� ������������ ������������� ����).
	// � ������ ���� � ����� ������ ��������� ��������� ���������, TO ������������ �������� �������� ���������� ���������� �������.
	case WM_RBUTTONDOWN:
	{
	
		int mouseX = LOWORD(lp);
		int mouseY = HIWORD(lp);

		for (int i = staticCount - 1; i >= 0; --i) {
			RECT rc;
			GetWindowRect(mystatic[i], &rc);
			if (mouseX >= rc.left && mouseX <= rc.right && mouseY >= rc.top && mouseY <= rc.bottom) {
				TCHAR staticInfo[100];
				GetWindowText(mystatic[i], staticInfo, 100);
				SetWindowText(hWnd, staticInfo);
				break;
			}
		}
	}
	break;
	//4)��� ������� ������ ����� ������ ���� ��� ������������ << ������� �� ������ ��������� � �����(��� ����� ����� ��������������� �������� DestroyWindow,4
	//  ������� � ��� ���������������� ������� ��������).� ������ ���� � ����� ������ ��������� ��������� ���������, �� ������������ �������� �������� � ���������� ���������� �������.
	case WM_LBUTTONDBLCLK:
	{
		int mouseX = LOWORD(lp);
		int mouseY = HIWORD(lp);

		
		for (int i = 0; i < staticCount; ++i) {
			RECT rc;
			GetWindowRect(mystatic[i], &rc);
			if (mouseX >= rc.left && mouseX <= rc.right && mouseY >= rc.top && mouseY <= rc.bottom) {
				DestroyWindow(mystatic[i]);
				
				mystatic[i] = mystatic[staticCount - 1];
				staticCount--;
				break;
			}
		}
	}
	break;
	}
	return FALSE;

}



