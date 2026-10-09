// FUN_00440100 @ 00440100 size=133 callers=4

void __fastcall FUN_00440100(int *param_1)

{
  code *pcVar1;
  int iVar2;
  void *this;
  uint uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047df70;
  local_10 = ExceptionList;
  local_8 = 0;
  iVar2 = *(int *)(*param_1 + 4);
  if (((*(int *)(iVar2 + 0xc + (int)param_1) == 0) &&
      ((*(byte *)(iVar2 + 0x14 + (int)param_1) & 2) != 0)) &&
     (pcVar1 = *(code **)(**(int **)(iVar2 + 0x38 + (int)param_1) + 0x34), pcVar1 != FUN_0043ba20))
  {
    ExceptionList = &local_10;
    iVar2 = (*pcVar1)();
    if (iVar2 == -1) {
      this = (void *)(*(int *)(*param_1 + 4) + (int)param_1);
      uVar3 = *(uint *)((int)this + 0xc) | 4;
      if (*(int *)((int)this + 0x38) != 0) {
        uVar3 = *(uint *)((int)this + 0xc);
      }
      FUN_00402f00(this,uVar3 | 4,'\0');
    }
  }
  ExceptionList = local_10;
  return;
}


