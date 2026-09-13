// FUN_00411ed0 @ 00411ed0 size=213 callers=2

void __fastcall FUN_00411ed0(void *param_1)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047aa58;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_00436540((int *)((int)param_1 + 4));
  FUN_00435e50(param_1,8);
  local_8 = 1;
  FUN_004362e0((int *)((int)param_1 + 0x30));
  FUN_00435e50((void *)((int)param_1 + 0x2c),8);
  local_8 = 2;
  FUN_004362e0((int *)((int)param_1 + 0x50));
  FUN_00435e50((void *)((int)param_1 + 0x4c),8);
  local_8 = 3;
  FUN_004361e0((int *)((int)param_1 + 0x70));
  FUN_00435e50((void *)((int)param_1 + 0x6c),8);
  puVar1 = *(undefined4 **)((int)param_1 + 0xc0);
  *(undefined4 *)((int)param_1 + 0xc0) = 0;
  if (puVar1 != (undefined4 *)0x0) {
    GdipDeleteFont(*puVar1);
    GdipFree(puVar1);
  }
  puVar1 = *(undefined4 **)((int)param_1 + 0xc4);
  *(undefined4 *)((int)param_1 + 0xc4) = 0;
  if (puVar1 != (undefined4 *)0x0) {
    GdipDeleteFont(*puVar1);
    GdipFree(puVar1);
  }
  ExceptionList = local_10;
  return;
}


