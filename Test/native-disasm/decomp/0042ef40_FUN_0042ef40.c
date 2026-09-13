// FUN_0042ef40 @ 0042ef40 size=161 callers=1

void __fastcall FUN_0042ef40(undefined4 *param_1)

{
  HWND this;
  HWND pHVar1;
  HWND pHVar2;
  HWND__ local_2c [5];
  uint local_18;
  HWND local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004536b0((char *)param_1[1],(uint *)&local_14);
  pHVar1 = FUN_0040eb10(local_2c,local_14);
  this = (HWND)*param_1;
  if (this != pHVar1) {
    if (7 < (uint)this[5].unused) {
      FUN_00402430((void *)this->unused,this[5].unused + 1,2);
    }
    this[5].unused = 7;
    this[4].unused = 0;
    pHVar2 = this;
    if (7 < (uint)this[5].unused) {
      pHVar2 = (HWND)this->unused;
    }
    *(undefined2 *)&pHVar2->unused = 0;
    FUN_0043a920(this,(uint *)pHVar1);
  }
  if (7 < local_18) {
    FUN_00402430((void *)local_2c[0].unused,local_18 + 1,2);
  }
  ExceptionList = local_10;
  return;
}


