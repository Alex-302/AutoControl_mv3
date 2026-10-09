// FUN_004500a0 @ 004500a0 size=225 callers=1

undefined8 __fastcall FUN_004500a0(int param_1,int param_2,uint *param_3)

{
  uint uVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  ulonglong uVar6;
  
  if (param_1 != param_2) {
    puVar5 = (uint *)(param_1 + 0x14);
    iVar4 = param_1 - (int)param_3;
    iVar3 = param_2;
    do {
      if (param_3 != (uint *)0x0) {
        param_3[5] = 7;
        param_3[4] = 0;
        *(undefined2 *)param_3 = 0;
        if (*puVar5 < 8) {
          if (puVar5[-1] + 1 != 0) {
            uVar6 = FUN_0045b0e0(param_3,(uint *)(iVar4 + (int)param_3),(puVar5[-1] + 1) * 2);
            iVar3 = (int)(uVar6 >> 0x20);
          }
        }
        else {
          *param_3 = *(uint *)(iVar4 + (int)param_3);
          *(undefined4 *)(iVar4 + (int)param_3) = 0;
        }
        param_3[4] = puVar5[-1];
        param_3[5] = *puVar5;
        *puVar5 = 7;
        puVar5[-1] = 0;
        if (*puVar5 < 8) {
          puVar2 = (undefined2 *)(iVar4 + (int)param_3);
        }
        else {
          puVar2 = *(undefined2 **)(iVar4 + (int)param_3);
        }
        *puVar2 = 0;
        uVar1 = puVar5[1];
        puVar5[1] = 0;
        param_3[6] = uVar1;
        param_3[7] = puVar5[2];
        param_3[8] = puVar5[3];
        *(short *)(param_3 + 8) = (short)puVar5[3];
        *(char *)(param_3 + 9) = (char)puVar5[4];
        *(undefined1 *)((int)param_3 + 0x25) = *(undefined1 *)((int)puVar5 + 0x11);
        *(undefined1 *)((int)param_3 + 0x26) = *(undefined1 *)((int)puVar5 + 0x12);
      }
      param_3 = param_3 + 10;
      puVar5 = puVar5 + 10;
    } while (iVar4 + (int)param_3 != param_2);
    return CONCAT44(iVar3,param_3);
  }
  return CONCAT44(param_2,param_3);
}


