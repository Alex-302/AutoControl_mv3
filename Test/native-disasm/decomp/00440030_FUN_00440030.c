// FUN_00440030 @ 00440030 size=203 callers=4

int * __fastcall FUN_00440030(int *param_1)

{
  code *pcVar1;
  int *piVar2;
  bool bVar3;
  int iVar4;
  void *this;
  uint uVar5;
  int *local_18;
  char local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047df64;
  local_10 = ExceptionList;
  if (*(int *)(*(int *)(*param_1 + 4) + 0x38 + (int)param_1) != 0) {
    ExceptionList = &local_10;
    FUN_0043e460(&local_18,param_1);
    local_8 = 0;
    if ((local_14 != '\0') &&
       (pcVar1 = *(code **)(**(int **)(*(int *)(*param_1 + 4) + 0x38 + (int)param_1) + 0x34),
       pcVar1 != FUN_0043ba20)) {
      iVar4 = (*pcVar1)();
      if (iVar4 == -1) {
        this = (void *)(*(int *)(*param_1 + 4) + (int)param_1);
        uVar5 = *(uint *)((int)this + 0xc) | 4;
        if (*(int *)((int)this + 0x38) != 0) {
          uVar5 = *(uint *)((int)this + 0xc);
        }
        FUN_00402f00(this,uVar5 | 4,'\0');
      }
    }
    local_8 = 1;
    bVar3 = thunk_FUN_0045c732();
    if (!bVar3) {
      FUN_00440100(local_18);
    }
    local_8 = CONCAT31(local_8._1_3_,2);
    piVar2 = *(int **)(*(int *)(*local_18 + 4) + 0x38 + (int)local_18);
    if ((piVar2 != (int *)0x0) && (pcVar1 = *(code **)(*piVar2 + 8), pcVar1 != guard_check_icall)) {
      (*pcVar1)();
    }
  }
  ExceptionList = local_10;
  return param_1;
}


