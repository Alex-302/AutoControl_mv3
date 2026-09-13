// FUN_00446b50 @ 00446b50 size=328 callers=1

void __thiscall FUN_00446b50(void *this,uint *param_1,uint *param_2,int param_3)

{
  void *pvVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  
  uVar5 = param_3 - (int)param_2 >> 4;
  if (uVar5 != 0) {
    puVar2 = *(uint **)((int)this + 4);
    if ((uint)(*(int *)((int)this + 8) - (int)puVar2 >> 4) < uVar5) {
      iVar3 = (int)puVar2 - *(int *)this >> 4;
      if (uVar5 <= 0xfffffffU - iVar3) {
        uVar4 = iVar3 + uVar5;
        uVar7 = *(int *)((int)this + 8) - *(int *)this >> 4;
        uVar6 = 0;
        if (uVar7 <= 0xfffffff - (uVar7 >> 1)) {
          uVar6 = (uVar7 >> 1) + uVar7;
        }
        if (uVar4 <= uVar6) {
          uVar4 = uVar6;
        }
        puVar2 = FUN_0043fde0(uVar4);
        uVar6 = (int)param_1 - (int)*(uint **)this;
        FUN_0045b0e0(puVar2,*(uint **)this,uVar6);
        puVar8 = (uint *)((int)puVar2 + uVar6);
        FUN_0045b0e0(puVar8,param_2,param_3 - (int)param_2);
        FUN_0045b0e0((uint *)((param_3 - (int)param_2) + (int)puVar8),param_1,
                     *(int *)((int)this + 4) - (int)param_1);
        pvVar1 = *(void **)this;
        iVar3 = *(int *)((int)this + 4);
        if (pvVar1 != (void *)0x0) {
          FUN_00402430(pvVar1,*(int *)((int)this + 8) - (int)pvVar1 >> 4,0x10);
        }
        *(uint **)((int)this + 8) = puVar2 + uVar4 * 4;
        *(uint **)((int)this + 4) = puVar2 + (uVar5 + (iVar3 - (int)pvVar1 >> 4)) * 4;
        *(uint **)this = puVar2;
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    FUN_0045b0e0(puVar2,param_2,param_3 - (int)param_2);
    puVar2 = *(uint **)((int)this + 4);
    if ((param_1 != puVar2) && (puVar2 != puVar2 + uVar5 * 4)) {
      FUN_00452cc0(param_1,puVar2,puVar2 + uVar5 * 4);
    }
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + uVar5 * 0x10;
  }
  return;
}


