// FUN_0043fa20 @ 0043fa20 size=494 callers=5

void __thiscall FUN_0043fa20(void *this,int *param_1,uint *param_2,uint param_3,undefined4 *param_4)

{
  void *pvVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined8 uVar9;
  
  iVar7 = *(int *)this;
  iVar6 = (int)param_2 - iVar7 >> 2;
  if (param_3 != 0) {
    uVar2 = *(uint *)((int)this + 4);
    if ((uint)((int)(*(int *)((int)this + 8) - uVar2) >> 2) < param_3) {
      iVar4 = (int)(uVar2 - iVar7) >> 2;
      if (param_3 <= 0x3fffffffU - iVar4) {
        uVar2 = iVar4 + param_3;
        uVar5 = *(int *)((int)this + 8) - iVar7 >> 2;
        uVar8 = 0;
        if (uVar5 <= 0x3fffffff - (uVar5 >> 1)) {
          uVar8 = (uVar5 >> 1) + uVar5;
        }
        if (uVar2 <= uVar8) {
          uVar2 = uVar8;
        }
        puVar3 = FUN_0043f960(uVar2);
        iVar7 = (int)param_2 - *(int *)this >> 2;
        FUN_00448200(puVar3 + iVar7,param_3,param_4);
        FUN_00450330(*(uint *)this,(uint)param_2,puVar3);
        FUN_00450330((uint)param_2,*(uint *)((int)this + 4),puVar3 + iVar7 + param_3);
        pvVar1 = *(void **)this;
        iVar7 = *(int *)((int)this + 4);
        if (pvVar1 != (void *)0x0) {
          FUN_00402430(pvVar1,*(int *)((int)this + 8) - (int)pvVar1 >> 2,4);
        }
        *(undefined4 **)((int)this + 8) = puVar3 + uVar2;
        *(undefined4 **)((int)this + 4) = puVar3 + param_3 + (iVar7 - (int)pvVar1 >> 2);
        *(undefined4 **)this = puVar3;
        *param_1 = (int)(puVar3 + iVar6);
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    param_4 = (undefined4 *)*param_4;
    if ((uint)((int)(uVar2 - (int)param_2) >> 2) < param_3) {
      FUN_00450330((uint)param_2,uVar2,param_2 + param_3);
      FUN_00448200(*(undefined4 **)((int)this + 4),
                   param_3 - ((int)*(undefined4 **)((int)this + 4) - (int)param_2 >> 2),&param_4);
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + param_3 * 4;
      FUN_00443b20(param_2,(undefined4 *)(*(int *)((int)this + 4) + param_3 * -4),&param_4);
      *param_1 = *(int *)this + iVar6 * 4;
      return;
    }
    uVar8 = uVar2 + param_3 * -4;
    uVar9 = FUN_00450330(uVar8,uVar2,(undefined4 *)uVar2);
    *(int *)((int)this + 4) = (int)uVar9;
    uVar8 = uVar8 - (int)param_2;
    FUN_0045b0e0((uint *)((int)((ulonglong)uVar9 >> 0x20) - uVar8),param_2,uVar8);
    FUN_00443b20(param_2,param_2 + param_3,&param_4);
  }
  *param_1 = *(int *)this + iVar6 * 4;
  return;
}


