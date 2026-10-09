// FUN_00419480 @ 00419480 size=365 callers=1

undefined4 * __fastcall FUN_00419480(undefined4 *param_1,char *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  void *pvVar3;
  byte *pbVar4;
  uint uVar5;
  undefined4 extraout_ECX;
  uint uVar6;
  uint extraout_EDX;
  ushort uVar7;
  void **ppvVar8;
  void *local_44 [5];
  uint local_30;
  int local_2c;
  undefined1 local_28;
  undefined4 *local_24;
  char *local_20;
  byte *local_1c;
  int local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0047b341;
  local_10 = ExceptionList;
  local_8 = 0;
  local_18[1] = 0;
  ExceptionList = &local_10;
  local_24 = param_1;
  local_20 = param_2;
  FUN_00433680(param_1);
  local_8 = 0;
  local_18[1] = 1;
  uVar7 = 0;
  iVar2 = FUN_00434070(param_2);
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      ppvVar8 = local_44;
      pvVar3 = (void *)FUN_00434550(param_2,uVar6);
      pbVar4 = (byte *)FUN_00440d90(pvVar3,ppvVar8);
      local_8 = 1;
      FUN_00436020(param_1,local_18,pbVar4);
      if (local_18[0] == param_1[1]) {
        puVar1 = *(undefined4 **)param_1[1];
        local_1c = pbVar4;
        iVar2 = FUN_00455240(puVar1,(undefined4 *)puVar1[1],extraout_ECX,&local_1c);
        if (param_1[2] == 0x71c71c6) {
                    /* WARNING: Subroutine does not return */
          FUN_00458ec4("list<T> too long");
        }
        param_1[2] = param_1[2] + 1;
        puVar1[1] = iVar2;
        **(int **)(iVar2 + 4) = iVar2;
        FUN_0044f420(param_1,&local_2c,(byte *)(*(int **)param_1[1] + 2),*(int **)param_1[1]);
      }
      else {
        local_2c = local_18[0];
        local_28 = 0;
      }
      local_8 = local_8 & 0xffffff00;
      *(ushort *)(local_2c + 0x20) = uVar7 | 0x1000;
      if (0xf < local_30) {
        pvVar3 = local_44[0];
        if ((0xfff < local_30 + 1) &&
           ((((((uint)local_44[0] & 0x1f) != 0 ||
              (pvVar3 = *(void **)((int)local_44[0] + -4), local_44[0] <= pvVar3)) ||
             ((uint)((int)local_44[0] - (int)pvVar3) < 4)) ||
            (0x23 < (uint)((int)local_44[0] - (int)pvVar3))))) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        FID_conflict__free(pvVar3);
      }
      param_2 = local_20;
      uVar7 = uVar7 + 1;
      uVar5 = FUN_00434070(local_20);
      uVar6 = extraout_EDX;
    } while (extraout_EDX < uVar5);
  }
  ExceptionList = local_10;
  return param_1;
}


