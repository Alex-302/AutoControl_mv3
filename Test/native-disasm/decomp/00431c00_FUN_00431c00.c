// FUN_00431c00 @ 00431c00 size=50 callers=54

void __fastcall FUN_00431c00(int *param_1)

{
  int *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004790f0;
  local_10 = ExceptionList;
  piVar1 = (int *)*param_1;
  if (piVar1 != (int *)0x0) {
    ExceptionList = &local_10;
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  ExceptionList = local_10;
  return;
}


