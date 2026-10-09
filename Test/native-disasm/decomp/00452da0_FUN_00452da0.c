// FUN_00452da0 @ 00452da0 size=253 callers=1

void __fastcall FUN_00452da0(undefined4 *param_1,undefined4 *param_2)

{
  void **this;
  undefined4 uVar1;
  void **ppvVar2;
  void **ppvVar3;
  void *local_28 [4];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047e95c;
  local_10 = ExceptionList;
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  uVar1 = *param_1;
  ppvVar3 = (void **)(param_1 + 1);
  ExceptionList = &local_10;
  FUN_0043b1c0(local_28,(uint *)ppvVar3);
  *param_1 = *param_2;
  this = (void **)(param_2 + 1);
  if (ppvVar3 != this) {
    if (0xf < (uint)param_1[6]) {
      FUN_00402430(*ppvVar3,param_1[6] + 1,1);
    }
    param_1[6] = 0xf;
    param_1[5] = 0;
    ppvVar2 = ppvVar3;
    if (0xf < (uint)param_1[6]) {
      ppvVar2 = *ppvVar3;
    }
    *(undefined1 *)ppvVar2 = 0;
    FUN_0043b1c0(ppvVar3,(uint *)this);
  }
  *param_2 = uVar1;
  if (this != local_28) {
    if (0xf < (uint)param_2[6]) {
      FUN_00402430(*this,param_2[6] + 1,1);
    }
    param_2[6] = 0xf;
    param_2[5] = 0;
    ppvVar3 = this;
    if (0xf < (uint)param_2[6]) {
      ppvVar3 = *this;
    }
    *(undefined1 *)ppvVar3 = 0;
    FUN_0043b1c0(this,(uint *)local_28);
  }
  if (0xf < local_14) {
    FUN_00402430(local_28[0],local_14 + 1,1);
  }
  ExceptionList = local_10;
  return;
}


