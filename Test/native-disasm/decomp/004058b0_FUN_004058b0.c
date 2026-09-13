// FUN_004058b0 @ 004058b0 size=227 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

HWND __fastcall
FUN_004058b0(undefined4 *param_1,undefined4 param_2,undefined2 param_3,undefined2 param_4)

{
  HWND hWnd;
  int lParam;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 *local_14;
  
  hWnd = CreateWindowExA(8,"tooltips_class32",(LPCSTR)0x0,3,-0x80000000,-0x80000000,-0x80000000,
                         -0x80000000,(HWND)0x0,(HMENU)0x0,(HINSTANCE)0x0,(LPVOID)0x0);
  local_38 = 0x30;
  _memset(&local_34,0,0x2c);
  local_34 = 0xa0;
  if (7 < (uint)param_1[5]) {
    param_1 = (undefined4 *)*param_1;
  }
  local_30 = param_2;
  local_14 = param_1;
  SendMessageA(hWnd,0x432,0,(LPARAM)&local_38);
  lParam = GetSystemMetrics(0);
  SendMessageA(hWnd,0x418,0,lParam);
  local_48 = _DAT_0048f2c0;
  uStack_44 = _UNK_0048f2c4;
  uStack_40 = _UNK_0048f2c8;
  uStack_3c = _UNK_0048f2cc;
  SendMessageA(hWnd,0x41a,0,(LPARAM)&local_48);
  SendMessageA(hWnd,0x412,0,CONCAT22(param_4,param_3));
  SendMessageA(hWnd,0x411,1,(LPARAM)&local_38);
  return hWnd;
}


