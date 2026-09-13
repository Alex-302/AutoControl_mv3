// FUN_0041ebf0 @ 0041ebf0 size=180 callers=2

void FUN_0041ebf0(void)

{
  undefined **local_3c [9];
  undefined ***local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047afd8;
  local_10 = ExceptionList;
  if (DAT_004a29dc == *(int *)(DAT_004a250c + -4)) {
    local_18 = local_3c;
    DAT_004a2426 = 0;
    local_3c[0] = &PTR_LAB_0048ea50;
    local_8 = 0;
    ExceptionList = &local_10;
    FUN_0040f6b0(DAT_004a23dc,(int *)local_18,0);
    if (local_18 != (undefined ***)0x0) {
      (*(code *)(*local_18)[4])(local_18 != local_3c);
      ExceptionList = local_10;
      return;
    }
  }
  else {
    DAT_004a2426 = 1;
    ExceptionList = &local_10;
    PostMessageA(*(HWND *)(&DAT_004a2470 + *(int *)(*(int *)ThreadLocalStoragePointer + 4) * 4),
                 0x100,0x1b,0);
  }
  ExceptionList = local_10;
  return;
}


