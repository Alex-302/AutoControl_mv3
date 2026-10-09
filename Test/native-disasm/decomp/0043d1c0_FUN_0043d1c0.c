// FUN_0043d1c0 @ 0043d1c0 size=652 callers=1

void __thiscall FUN_0043d1c0(void *this,int *param_1,char *param_2,uint param_3,undefined1 *param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  undefined1 *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char local_3c [20];
  int local_28;
  uint local_24;
  void *local_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047de70;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffb4;
  local_24 = *(uint *)this;
  iVar8 = (int)((int)param_2 - local_24) >> 4;
  local_28 = iVar8;
  if (param_3 != 0) {
    iVar1 = *(int *)((int)this + 4);
    local_20 = this;
    if ((uint)(*(int *)((int)this + 8) - iVar1 >> 4) < param_3) {
      iVar8 = iVar1 - *(int *)this >> 4;
      if (0xfffffffU - iVar8 < param_3) {
        ExceptionList = &local_10;
        local_14 = &stack0xffffffb4;
                    /* WARNING: Subroutine does not return */
        FUN_00458ec4("vector<T> too long");
      }
      uVar7 = iVar8 + param_3;
      uVar5 = (int)(*(int *)((int)this + 8) - local_24) >> 4;
      uVar6 = 0;
      if (uVar5 <= 0xfffffff - (uVar5 >> 1)) {
        uVar6 = (uVar5 >> 1) + uVar5;
      }
      local_24 = uVar7;
      if (uVar7 <= uVar6) {
        local_24 = uVar6;
      }
      ExceptionList = &local_10;
      local_14 = &stack0xffffffb4;
      local_18 = FUN_0043fde0(local_24);
      local_20 = (void *)((int)param_2 - *(int *)this >> 4);
      local_8 = 0;
      local_1c = 0;
      FUN_00448170(local_18 + (int)local_20 * 0x10,param_3,param_4);
      iVar8 = local_28;
      local_1c = 1;
      FUN_00450230(*(undefined1 **)this,param_2,local_18);
      local_1c = 2;
      FUN_00450230(param_2,*(undefined1 **)((int)this + 4),
                   local_18 + ((int)local_20 + param_3) * 0x10);
      pcVar2 = *(char **)((int)this + 4);
      pcVar3 = *(char **)this;
      if (pcVar3 != (char *)0x0) {
        FUN_0043f5c0(pcVar3,pcVar2);
        FUN_00402430(*(void **)this,*(int *)((int)this + 8) - (int)*(void **)this >> 4,0x10);
      }
      *(undefined1 **)((int)this + 8) = local_18 + local_24 * 0x10;
      *(undefined1 **)((int)this + 4) =
           local_18 + (param_3 + ((int)pcVar2 - (int)pcVar3 >> 4)) * 0x10;
      *(undefined1 **)this = local_18;
      local_28 = iVar8;
    }
    else if ((uint)(iVar1 - (int)param_2 >> 4) < param_3) {
      ExceptionList = &local_10;
      local_14 = &stack0xffffffb4;
      FUN_00434940(local_3c,param_4);
      local_8 = 2;
      local_28 = param_3 * 0x10;
      FUN_00450230(param_2,*(undefined1 **)((int)this + 4),param_2 + local_28);
      local_8 = CONCAT31(local_8._1_3_,3);
      FUN_00448170(*(void **)((int)this + 4),param_3 - (*(int *)((int)this + 4) - (int)param_2 >> 4)
                   ,local_3c);
      local_8 = 2;
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + local_28;
      FUN_0044ae00(param_2,(char *)(*(int *)((int)this + 4) - local_28),local_3c);
      FUN_00434820(local_3c);
      local_28 = iVar8;
    }
    else {
      ExceptionList = &local_10;
      FUN_00434940(local_3c,param_4);
      local_8 = 5;
      pcVar2 = *(char **)((int)this + 4);
      puVar4 = FUN_00450230(pcVar2 + param_3 * -0x10,pcVar2,pcVar2);
      *(undefined1 **)((int)this + 4) = puVar4;
      FUN_00448030(param_2,pcVar2 + param_3 * -0x10,pcVar2);
      FUN_0044ae00(param_2,param_2 + param_3 * 0x10,local_3c);
      FUN_00434820(local_3c);
    }
  }
  *param_1 = local_28 * 0x10 + *(int *)this;
  ExceptionList = local_10;
  return;
}


