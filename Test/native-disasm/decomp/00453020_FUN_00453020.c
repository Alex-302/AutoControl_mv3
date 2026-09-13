// FUN_00453020 @ 00453020 size=273 callers=1

undefined4 * __fastcall
FUN_00453020(undefined4 *param_1,undefined1 *param_2,undefined1 *param_3,uint *param_4)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  uint uVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined1 local_a [2];
  int local_8;
  undefined4 *local_4;
  
  local_4 = param_1;
  do {
    if (param_2 == param_3) {
      *local_4 = param_4;
      return local_4;
    }
    local_a[1] = *param_2;
    puVar1 = (undefined1 *)param_4[1];
    local_a[0] = local_a[1];
    if ((local_a < puVar1) && (puVar3 = (undefined1 *)*param_4, puVar3 <= local_a)) {
      puVar2 = (undefined1 *)param_4[2];
      local_8 = (int)local_a - (int)puVar3;
      if ((puVar1 == puVar2) && (puVar2 == puVar1)) {
        if ((int)puVar3 - (int)puVar1 == 1) {
LAB_00453127:
                    /* WARNING: Subroutine does not return */
          FUN_00458ec4("vector<T> too long");
        }
        uVar4 = (int)puVar2 - (int)puVar3;
        puVar2 = (undefined1 *)0x0;
        if (uVar4 <= ~(uVar4 >> 1)) {
          puVar2 = (undefined1 *)((uVar4 >> 1) + uVar4);
        }
        puVar6 = puVar1 + (1 - (int)puVar3);
        if (puVar1 + (1 - (int)puVar3) <= puVar2) {
          puVar6 = puVar2;
        }
        FUN_0043d780(param_4,(uint)puVar6);
      }
      if ((undefined1 *)param_4[1] != (undefined1 *)0x0) {
        *(undefined1 *)param_4[1] = *(undefined1 *)(local_8 + *param_4);
      }
    }
    else {
      puVar3 = (undefined1 *)param_4[2];
      if ((puVar1 == puVar3) && (puVar3 == puVar1)) {
        uVar4 = *param_4;
        if (uVar4 - (int)puVar1 == 1) goto LAB_00453127;
        uVar5 = (int)puVar3 - uVar4;
        puVar3 = (undefined1 *)0x0;
        if (uVar5 <= ~(uVar5 >> 1)) {
          puVar3 = (undefined1 *)((uVar5 >> 1) + uVar5);
        }
        puVar2 = puVar1 + (1 - uVar4);
        if (puVar1 + (1 - uVar4) <= puVar3) {
          puVar2 = puVar3;
        }
        FUN_0043d780(param_4,(uint)puVar2);
      }
      if ((undefined1 *)param_4[1] != (undefined1 *)0x0) {
        *(undefined1 *)param_4[1] = local_a[1];
      }
    }
    param_4[1] = param_4[1] + 1;
    param_2 = param_2 + 1;
  } while( true );
}


