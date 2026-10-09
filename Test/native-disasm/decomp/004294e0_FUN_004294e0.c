// FUN_004294e0 @ 004294e0 size=234 callers=1

void * __thiscall FUN_004294e0(void *this,uint *param_1)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  iVar5 = 4;
  iVar4 = (int)param_1 - (int)this;
  puVar6 = (uint *)((int)this + 0x14);
  ExceptionList = &local_10;
  do {
    if (puVar6 + -5 != param_1) {
      if (0xf < *puVar6) {
        FUN_00402430((void *)puVar6[-5],*puVar6 + 1,1);
      }
      *puVar6 = 0xf;
      puVar3 = puVar6 + -5;
      puVar6[-1] = 0;
      puVar2 = puVar3;
      if (0xf < *puVar6) {
        puVar2 = (uint *)*puVar3;
      }
      *(undefined1 *)puVar2 = 0;
      if (*(uint *)(iVar4 + (int)puVar6) < 0x10) {
        if (param_1[4] + 1 != 0) {
          FUN_0045b0e0(puVar3,param_1,param_1[4] + 1);
        }
      }
      else {
        *puVar3 = *param_1;
        *param_1 = 0;
      }
      puVar6[-1] = param_1[4];
      *puVar6 = *(uint *)(iVar4 + (int)puVar6);
      *(undefined4 *)(iVar4 + (int)puVar6) = 0xf;
      uVar1 = *(uint *)(iVar4 + (int)puVar6);
      param_1[4] = 0;
      puVar3 = param_1;
      if (0xf < uVar1) {
        puVar3 = (uint *)*param_1;
      }
      *(undefined1 *)puVar3 = 0;
    }
    param_1 = param_1 + 6;
    puVar6 = puVar6 + 6;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  ExceptionList = local_10;
  return this;
}


