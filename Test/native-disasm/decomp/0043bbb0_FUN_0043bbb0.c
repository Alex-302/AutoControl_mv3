// FUN_0043bbb0 @ 0043bbb0 size=307 callers=2

/* WARNING: Removing unreachable block (ram,0x0043bc08) */
/* WARNING: Removing unreachable block (ram,0x0043bc16) */

longlong __thiscall FUN_0043bbb0(void *this,uint *param_1,uint param_2,int param_3)

{
  code *pcVar1;
  byte *pbVar2;
  longlong lVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  longlong lVar7;
  int local_14;
  
  local_14 = param_3;
  if ((param_3 < 0) || ((param_3 < 1 && (param_2 == 0)))) {
    return 0;
  }
  lVar3 = 0;
  do {
    do {
      lVar7 = FUN_0043e3e0((int)this);
      if (lVar7 < 1) {
        pcVar1 = *(code **)(*(int *)this + 0x1c);
        if (pcVar1 == std::basic_streambuf<char,std::char_traits<char>_>::uflow) {
          iVar4 = (**(code **)(*(int *)this + 0x18))();
          if (iVar4 == -1) {
            uVar5 = 0xffffffff;
          }
          else {
            **(int **)((int)this + 0x2c) = **(int **)((int)this + 0x2c) + -1;
            pbVar2 = (byte *)**(int **)((int)this + 0x1c);
            **(int **)((int)this + 0x1c) = (int)(pbVar2 + 1);
            uVar5 = (uint)*pbVar2;
          }
        }
        else {
          uVar5 = (*pcVar1)();
        }
        if (uVar5 == 0xffffffff) {
          return lVar3;
        }
        *(char *)param_1 = (char)uVar5;
        param_1 = (uint *)((int)param_1 + 1);
        lVar3 = lVar3 + 1;
        bVar6 = param_2 != 0;
        param_2 = param_2 - 1;
        local_14 = local_14 + -1 + (uint)bVar6;
      }
      else {
        if (CONCAT44(local_14,param_2) < lVar7) {
          lVar7 = CONCAT44(local_14,param_2);
        }
        uVar5 = (uint)lVar7;
        if (uVar5 != 0) {
          FUN_0045c870(param_1,(uint *)**(undefined4 **)((int)this + 0x1c),uVar5);
        }
        param_1 = (uint *)((int)param_1 + uVar5);
        lVar3 = lVar7 + lVar3;
        bVar6 = param_2 < uVar5;
        param_2 = param_2 - uVar5;
        local_14 = (local_14 - (int)((ulonglong)lVar7 >> 0x20)) - (uint)bVar6;
        **(int **)((int)this + 0x2c) = **(int **)((int)this + 0x2c) - uVar5;
        **(int **)((int)this + 0x1c) = **(int **)((int)this + 0x1c) + uVar5;
      }
    } while (0 < local_14);
    if (local_14 < 0) {
      return lVar3;
    }
  } while (param_2 != 0);
  return lVar3;
}


