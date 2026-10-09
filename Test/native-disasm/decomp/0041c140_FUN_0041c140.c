// FUN_0041c140 @ 0041c140 size=114 callers=5

void __fastcall FUN_0041c140(int param_1)

{
  POINT local_28;
  tagRECT local_20;
  
  local_20.left = 0;
  local_20.top = 0;
  local_20.right = 0;
  local_20.bottom = 0;
  GetWindowRect(*(HWND *)(param_1 + 0x28),&local_20);
  local_20.top = local_20.bottom - local_20.top;
  local_20.left = local_20.right - local_20.left;
  local_28.x = 0;
  local_28.y = 0;
  UpdateLayeredWindow(*(HWND *)(param_1 + 0x28),(HDC)0x0,(POINT *)0x0,(SIZE *)&local_20,
                      *(HDC *)(param_1 + 0x2c),&local_28,0,(BLENDFUNCTION *)&DAT_0049d9e8,2);
  return;
}


