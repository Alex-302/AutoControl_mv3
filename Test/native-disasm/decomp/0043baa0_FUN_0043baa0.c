// FUN_0043baa0 @ 0043baa0 size=261 callers=2

/* WARNING: Removing unreachable block (ram,0x0043baf4) */
/* WARNING: Removing unreachable block (ram,0x0043bafe) */

longlong __thiscall FUN_0043baa0(void *this,uint *param_1,uint param_2,int param_3)

{
  longlong lVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  longlong lVar5;
  
  if ((-1 < param_3) && ((0 < param_3 || (param_2 != 0)))) {
    lVar1 = 0;
    while( true ) {
      do {
        lVar5 = FUN_0043e3c0((int)this);
        if (lVar5 < 1) {
          iVar2 = (**(code **)(*(int *)this + 0xc))((char)*param_1);
          if (iVar2 == -1) {
            return lVar1;
          }
          param_1 = (uint *)((int)param_1 + 1);
          lVar1 = lVar1 + 1;
          bVar4 = param_2 != 0;
          param_2 = param_2 - 1;
          param_3 = param_3 + -1 + (uint)bVar4;
        }
        else {
          if (CONCAT44(param_3,param_2) < lVar5) {
            lVar5 = CONCAT44(param_3,param_2);
          }
          uVar3 = (uint)lVar5;
          if (uVar3 != 0) {
            FUN_0045c870((uint *)**(undefined4 **)((int)this + 0x20),param_1,uVar3);
          }
          param_1 = (uint *)((int)param_1 + uVar3);
          lVar1 = lVar5 + lVar1;
          bVar4 = param_2 < uVar3;
          param_2 = param_2 - uVar3;
          param_3 = (param_3 - (int)((ulonglong)lVar5 >> 0x20)) - (uint)bVar4;
          **(int **)((int)this + 0x30) = **(int **)((int)this + 0x30) - uVar3;
          **(int **)((int)this + 0x20) = **(int **)((int)this + 0x20) + uVar3;
        }
      } while (0 < param_3);
      if (param_3 < 0) break;
      if (param_2 == 0) {
        return lVar1;
      }
    }
    return lVar1;
  }
  return 0;
}


