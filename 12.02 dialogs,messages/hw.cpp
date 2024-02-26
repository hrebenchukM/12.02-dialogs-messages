#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

TCHAR str1[20];
HWND mystatic[100]; // Массив для хранения хэндлов статиков
HINSTANCE hInst1;
int staticCount = 0; // Порядковые номера статиков(их количество)
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst1 = hInst;
	MSG msg;
	// создаём главное окно приложения на основе немодального диалога
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
	// Отображаем окно
	ShowWindow(hDialog, nCmdShow);
	//Запускаем цикл обработки сообщений
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
		// закрываем немодальный диалог
		DestroyWindow(hWnd); // разрушаем окно
		PostQuitMessage(0); // останавливаем цикл обработки сообщений
		return TRUE;
	case WM_MOUSEMOVE:
		wsprintf(str1, TEXT("X=%d  Y=%d"), LOWORD(lp), HIWORD(lp)); // текущие координаты курсора мыши
		SetWindowText(hWnd, str1);
		break;
	case WM_LBUTTONDOWN:
	{
		x = LOWORD(lp);
		y = HIWORD(lp);

	}
	break;



	//1)Пользователь «щелкает» левой кнопкой мыши по форме диалога и, не отпуская кнопку, ведёт по ней мышку,
	//  а в момент отпускания кнопки по полученным координатам прямоугольника(как известно, двух точек на плоскости достаточно для создания прямоугольника)
	//  создаётся «статик», который содержит свой порядковый номер(имеется в виду порядок появления «статика» на форме).
	case WM_LBUTTONUP:
	{
		int width = LOWORD(lp) - x;
		int height = HIWORD(lp) - y;
		

		//2)Минимальный размер «статика» составляет 10х10, а при попытке создания элемента управления меньших размеров
		//  пользователь должен увидеть соответствующее предупреждение.
		if (width < 10 || height < 10)
		{
			MessageBox(hWnd, TEXT("Размеры статика должны быть не меньше 10х10!"), TEXT("Предупреждение для тебя,дорогой ты мой пользователь!!!"), MB_OK | MB_ICONWARNING);
			break;
		}
		
		mystatic[staticCount] = CreateWindowEx(0, TEXT("STATIC"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
			x, y, width, height, hWnd, 0, hInst1, 0);
		staticCount++;
		TCHAR staticInfo[100];
		wsprintf(staticInfo, TEXT("Статик №%d: Ширина=%d, Высота=%d, X=%d, Y=%d"), staticCount, width, height, x, y);
		SetWindowText(hWnd, staticInfo);
	}

	return FALSE;



	//3)При щелчке правой кнопкой мыши над поверхностью «статика» в заголовке окна должна появиться информация о статике
	// (порядковый номер «статика», ширина и высота, а также координаты «статика» относительно родительского окна).
	// В случае если в точке щелчка находится несколько «статиков», TO предпочтение отдается «статику» наибольшим порядковым номером.
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
	//4)При двойном щелчке левой кнопки мыши над поверхностью << статика» он должен исчезнуть с формы(для этого можно воспользоваться функцией DestroyWindow,4
	//  вызывая её для соответствующего объекта «статика»).В случае если в точке щелчка находится несколько «статиков», то предпочтение отдается «статику» с наименьшим порядковым номером.
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



