#define NOMINMAX
#define _NO_CRT_STDIO_INLINE
#include<windows.h>
//#include<commctrl.h>
#include<stdint.h>
#include<limits.h>
#include<stdbool.h>
#include<stdio.h> // REMOVE ASAP!
#include<math.h>
#include<intrin.h>
#include<emmintrin.h>
#include<tmmintrin.h>
//#include<d3d11.h>
//#include<xinput.h>

#include"refps2_win64.h"
#include"refps2.h"
#include"refps2_ee_r3000.h"
//#include"refps2_ee_r5900.h"
#include"refps2_ee_cpu_cop0.h"
//#include"refps2_tlb.h"
#include"refps2_ee_cpu.h"
#include"refps2_ee.h"
#include"refps2_elf_file.h"
#include"refps2_opcodes.h"
//#include"refps2_iso_file.h"
//#include"refps2_renderer_d3d11.h"
//#include"refps2_renderer_opengl.h"
//#include"refps2_renderer_wingdi.h"
#include"refps2_gs.h"
#include"refps2_console.h"

#include"refps2.c"
//#include"refps2_tlb.c"
#include"refps2_ee_cpu.c"
#include"refps2_memory.c"
#include"refps2_opcodes_mips.c"
#include"refps2_opcodes_ex.c"
#include"refps2_opcodes_cop0.c"
#include"refps2_opcodes_cop1.c"
#include"refps2_opcodes_mmi.c"
#include"refps2_opcodes_tables.c"
#include"refps2_ee_r5900.c"
//#include"ps2_iso_file.c"
//#include"ps2_elf_file.c"
//#include"refps2_disassembler.c"
//#include"refps2_renderer_opengl.c"
//#include"refps2_renderer_d3d11.c"
//#include"refps2_renderer_wingdi.c"
#include"refps2_console.c"

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "comdlg32.lib")


static LRESULT CALLBACK
GameWindowProc(HWND Window, UINT Message, WPARAM Wparam, LPARAM Lparam)
{
  switch(Message)
  {
    case WM_CLOSE:
    {
      DestroyWindow(Window);
    } break;
    default:
    {
      return DefWindowProcW(Window, Message, Wparam, Lparam);
    }
  }
  return 0;
}


static void
HandleMenuMessages(HWND Window, WPARAM Wparam)
{
  ps2_console* Console = (ps2_console*)GetWindowLongPtrW(Window, GWLP_USERDATA);
  switch(LOWORD(Wparam))
  {
    case MENUITEM_CDVD_LOAD_ISO:
    {
      WCHAR FileName[MAX_PATH] = {0};
      OPENFILENAMEW OFN = {0};
      OFN.lStructSize = sizeof(OFN);
      OFN.hwndOwner = Window;
      OFN.nMaxFile = sizeof(FileName);
      OFN.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
      OFN.lpstrFile = FileName;
      OFN.lpstrFilter = L"ISO Files\0*.iso\0All Files\0*.*\0";
      OFN.lpstrDefExt = L"iso";
      BOOL FileWasChosen = GetOpenFileNameW(&OFN);
      if(!FileWasChosen)
      {
        return;
      }
    } break;
    case MENUITEM_CDVD_LOAD_ELF:
    {
      WCHAR FileName[MAX_PATH] = {0};
      OPENFILENAMEW OFN = {0};
      OFN.lStructSize = sizeof(OFN);
      OFN.hwndOwner = Window;
      OFN.nMaxFile = sizeof(FileName);
      OFN.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
      OFN.lpstrFile = FileName;
      OFN.lpstrFilter = L"ELF Files\0*.elf\0All Files\0*.*\0";
      OFN.lpstrDefExt = L"elf";
      BOOL FileWasChosen = GetOpenFileNameW(&OFN);
      if(!FileWasChosen)
      {
        return;
      }
      HANDLE ElfFile = CreateFileW(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      ASSERT(ElfFile != INVALID_HANDLE_VALUE);
      elf_header ElfHeader = {0};
      DWORD BytesRead = 0;
      ReadFile(ElfFile, &ElfHeader, sizeof(ElfHeader), &BytesRead, NULL);
      ASSERT(BytesRead == sizeof(ElfHeader));
      LARGE_INTEGER NewFilePointer = {0};
      SetFilePointerEx(ElfFile, (LARGE_INTEGER){ElfHeader.EntryPoint}, &NewFilePointer, FILE_BEGIN);
      ASSERT(NewFilePointer.QuadPart == ElfHeader.EntryPoint);

      PostMessageW(Window, WM_COMMAND, MENUITEM_FILE_RUN, 0);
    } break;
    case MENUITEM_CDVD_LOAD_BIOS:
    {
      PS2Console_CopyBiosToMemory(Console, L"../../bios/SCPH-10000_BIOS_V1_JAP_100.BIN");
      PS2Console_Execute(Console);
    } break;
    case MENUITEM_FILE_RUN:
    {
      HWND GameWindow = CreateWindowExW(0, REFPS2_WNDCLASS_NAME, L"", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, Window, NULL, GetModuleHandle(NULL), NULL);
      ASSERT(IsWindow(GameWindow));
      SetWindowLongPtrW(GameWindow, GWLP_WNDPROC, (LONG_PTR)GameWindowProc);
      //PS2Console_Execute(Console);
    } break;

    case MENUITEM_CONFIG_INPUT:
    case MENUITEM_CONFIG_VIDEO:
    case MENUITEM_CONFIG_SOUND:
    {
      PROPSHEETHEADERW Header = {0};
      //INT_PTR Result = PropertySheetW(&Header);
    } break;
    case MENUITEM_FILE_EXIT:
    {
      PostMessageW(Window, WM_CLOSE, 0, 0);
    } break;
  }
}

static LRESULT CALLBACK
WindowProc(HWND Window, UINT Message, WPARAM Wparam, LPARAM Lparam)
{
  LRESULT Result = 0;
  switch (Message)
  {
    case WM_CLOSE:
    {
      PostQuitMessage((int)Wparam);
    } break;
    case WM_DESTROY:
    {
      PostMessageW(Window, WM_CLOSE, -1, 0);
    } break;
    case WM_COMMAND:
    {
      HandleMenuMessages(Window, Wparam);
    } break;
    default:
    {
      Result = DefWindowProcW(Window, Message, Wparam, Lparam);
    } break;
  }
  return Result;
}

static HMENU
CreateWindowMainMenu(void)
{
  HMENU Result = CreateMenu();
  HMENU SubMenu = CreatePopupMenu();
  AppendMenuW(SubMenu, MF_STRING | MF_GRAYED, MENUITEM_FILE_RUN, L"Run");
  AppendMenuW(SubMenu, MF_STRING, MENUITEM_FILE_EXIT, L"Exit");
  AppendMenuW(Result, MF_STRING | MF_POPUP, (UINT_PTR)SubMenu, L"File");
  SubMenu = CreatePopupMenu();
  AppendMenuW(SubMenu, MF_STRING, MENUITEM_CDVD_LOAD_ISO, L"Load ISO");
  AppendMenuW(SubMenu, MF_STRING, MENUITEM_CDVD_LOAD_ELF, L"Load ELF");
  AppendMenuW(SubMenu, MF_STRING, MENUITEM_CDVD_LOAD_BIOS, L"Load BIOS");
  AppendMenuW(Result, MF_STRING | MF_POPUP, (UINT_PTR)SubMenu, L"CDVD");
  SubMenu = CreatePopupMenu();
  AppendMenuW(SubMenu, MF_STRING, MENUITEM_CONFIG_VIDEO, L"Video");
  AppendMenuW(SubMenu, MF_STRING, MENUITEM_CONFIG_SOUND, L"Sound");
  AppendMenuW(SubMenu, MF_STRING, MENUITEM_CONFIG_INPUT, L"Input");
  AppendMenuW(Result, MF_STRING | MF_POPUP, (UINT_PTR)SubMenu, L"Config");
  SubMenu = CreatePopupMenu();
  AppendMenuW(SubMenu, MF_STRING, MENUITEM_DEBUG_SHOWCONSOLE, L"Show Console");
  AppendMenuW(Result, MF_STRING | MF_POPUP, (UINT_PTR)SubMenu, L"Debug");
  return Result;
}

static HWND
CreateMainWindow(void)
{
  WNDCLASSEXW WindowClass = {0};
  WindowClass.cbSize = sizeof(WindowClass);
  WindowClass.hInstance = GetModuleHandle(NULL);
  WindowClass.lpfnWndProc = WindowProc;
  WindowClass.lpszClassName = REFPS2_WNDCLASS_NAME;
  RegisterClassExW(&WindowClass);
  DWORD WindowStyle = WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU;
  HMENU WindowMenu = CreateWindowMainMenu();
  HWND Result = CreateWindowExW(0, WindowClass.lpszClassName, L"refps2", WindowStyle, CW_USEDEFAULT, CW_USEDEFAULT, 480, 320, NULL, WindowMenu, WindowClass.hInstance, NULL);
  ASSERT(IsWindow(Result));
  return Result;
}

static void
DisableDPIScaling(void)
{
  HMODULE User32Lib = LoadLibraryW(L"user32.dll");
  void* FunctionPointer = GetProcAddress(User32Lib, "SetProcessDpiAwarenessContext");
  if(FunctionPointer)
  {
    void (*SetProcessDpiAwarenessContext)(DPI_AWARENESS_CONTEXT) = FunctionPointer;
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
    return;
  }
  FunctionPointer = GetProcAddress(User32Lib, "SetProcessDpiAware");
  if(FunctionPointer)
  {
    void (*SetProcessDpiAware)(void) = FunctionPointer;
    SetProcessDpiAware();
  }
}

int APIENTRY
wWinMain(HINSTANCE Instance, HINSTANCE Unused, LPWSTR CmdLine, int CmdShow)
//void WinMainCRTStartup()
{
  DisableDPIScaling();
  HWND MainWindow = CreateMainWindow();
  Console = VirtualAlloc(NULL, sizeof(*Console), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  SetWindowLongPtrW(MainWindow, GWLP_USERDATA, (LONG_PTR)Console);

  MSG Msg = {0};
  for (;;)
  {
    GetMessageW(&Msg, NULL, 0, 0);
    if (Msg.message == WM_QUIT)
    {
      UINT ExitCode = (UINT)Msg.wParam;
      ExitProcess(ExitCode);
    }
    DispatchMessageW(&Msg);
  }
}