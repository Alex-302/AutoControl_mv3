// FUN_0040e030 @ 0040e030 size=275 callers=1

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall FUN_0040e030(undefined4 *param_1,int *param_2)

{
  int *piVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  IAccessible *pIVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int local_40;
  int aiStack_3c [4];
  POINT local_2c;
  IAccessible *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047a312;
  local_1c = ExceptionList;
  aiStack_3c[3] = 0;
  piVar1 = (int *)*param_2;
  local_40 = 0;
  aiStack_3c[0] = 0;
  aiStack_3c[1] = 0;
  aiStack_3c[2] = 0;
  ExceptionList = &local_1c;
  puVar2 = &stack0xfffffffc;
  if (piVar1 != (int *)0x0) {
    ExceptionList = &local_1c;
    local_2c.y = (LONG)param_1;
    (**(code **)(*piVar1 + 0x58))
              (piVar1,&local_40,aiStack_3c,aiStack_3c + 1,aiStack_3c + 2,_DAT_0048e618,_UNK_0048e61c
               ,_UNK_0048e620,_UNK_0048e624);
    puVar2 = puStack_20;
  }
  puStack_20 = puVar2;
  local_2c.x = local_40 + aiStack_3c[2] / 2;
  local_2c.y = aiStack_3c[2] / 2 + aiStack_3c[0];
  FUN_0040b610(&local_24,&local_2c);
  uVar8 = 0x32;
  iVar7 = 1;
  iVar6 = 0x2a;
  uVar5 = 5;
  local_14 = 0;
  pIVar4 = local_24;
  if (local_24 != (IAccessible *)0x0) {
    (*local_24->lpVtbl->AddRef)(local_24);
  }
  puVar3 = FUN_0040bcc0(&local_2c.y,0x14,(int *)pIVar4,uVar5);
  local_14._0_1_ = 2;
  FUN_0040bb70(param_1,puVar3,iVar6,iVar7,uVar8);
  local_14 = CONCAT31(local_14._1_3_,3);
  if ((int *)local_2c.y != (int *)0x0) {
    (**(code **)(*(int *)local_2c.y + 8))(local_2c.y);
  }
  local_14 = 4;
  if (local_24 != (IAccessible *)0x0) {
    (*local_24->lpVtbl->Release)(local_24);
  }
  ExceptionList = local_1c;
  return param_1;
}


