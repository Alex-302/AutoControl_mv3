// FUN_0041bff0 @ 0041bff0 size=142 callers=5

void __fastcall FUN_0041bff0(undefined4 *param_1)

{
  void *pvVar1;
  
  DestroyWindow((HWND)param_1[10]);
  DeleteDC((HDC)param_1[0xb]);
  DeleteObject((HGDIOBJ)param_1[0xc]);
  pvVar1 = (void *)param_1[3];
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,(param_1[5] - (int)pvVar1) / 0x14,0x14);
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
  }
  pvVar1 = (void *)*param_1;
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,param_1[2] - (int)pvVar1 >> 2,4);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


