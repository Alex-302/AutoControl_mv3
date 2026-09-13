// FUN_0040cab0 @ 0040cab0 size=309 callers=4

uint * __fastcall FUN_0040cab0(uint *param_1,undefined4 *param_2)

{
  ushort uVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  ushort *puVar6;
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047a079;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_8 = 0;
  puVar6 = (ushort *)*param_2;
  uVar4 = (uint)((int)param_2[1] + (1 - (int)puVar6)) >> 1;
  local_18 = 0;
  if ((ushort *)param_2[1] < puVar6) {
    uVar4 = 0;
  }
  if (uVar4 != 0) {
    do {
      uVar1 = *puVar6;
      local_14 = (uint)uVar1;
      uVar5 = local_14 & 0xff;
      if ((((0x20 < uVar5) && (uVar5 < 0x29)) || (uVar5 == 0x2d)) ||
         ((uVar5 == 0x2e || (uVar5 == 0xd)))) {
        uVar5 = local_14;
      }
      if ((*(uint *)(DAT_004a28b0 + (uVar5 >> 5) * 4) & 1 << ((byte)uVar5 & 0x1f)) != 0) {
        puVar2 = (uint *)param_1[1];
        if (&local_14 < puVar2) {
          puVar3 = (uint *)*param_1;
          if (&local_14 < puVar3) goto LAB_0040cb9b;
          if (puVar2 == (uint *)param_1[2]) {
            FUN_004375a0((int *)param_1);
          }
          if ((undefined2 *)param_1[1] != (undefined2 *)0x0) {
            *(undefined2 *)param_1[1] =
                 *(undefined2 *)(*param_1 + ((int)&local_14 - (int)puVar3 >> 1) * 2);
          }
        }
        else {
LAB_0040cb9b:
          if (puVar2 == (uint *)param_1[2]) {
            FUN_004375a0((int *)param_1);
          }
          if ((ushort *)param_1[1] != (ushort *)0x0) {
            *(ushort *)param_1[1] = uVar1;
          }
        }
        param_1[1] = param_1[1] + 2;
      }
      puVar6 = puVar6 + 1;
      local_18 = local_18 + 1;
    } while (local_18 != uVar4);
  }
  FUN_0040c850(param_1,'\x01');
  ExceptionList = local_10;
  return param_1;
}


