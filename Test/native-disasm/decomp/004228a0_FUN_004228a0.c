// FUN_004228a0 @ 004228a0 size=270 callers=1

void __fastcall FUN_004228a0(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  byte *pbVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  byte *pbVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 local_10;
  byte *local_c;
  byte *local_8 [2];
  
  local_10 = param_1;
  FUN_00436250(&DAT_004a294c,(int *)&local_c,(byte *)&local_10);
  pbVar4 = local_c;
  if (local_c != DAT_004a2950) {
    pbVar1 = local_c + 0x10;
    if (((param_3 != 0 || param_4 != 0) && (param_4 <= *(int *)(local_c + 0x1c))) &&
       ((param_4 < *(int *)(local_c + 0x1c) || (param_3 < *(uint *)(local_c + 0x18))))) {
      pbVar2 = local_c + 0x20;
      FUN_00436250(&DAT_004a290c,(int *)&local_c,pbVar2);
      pbVar5 = local_c;
      if (local_c == DAT_004a2910) {
        local_c = pbVar2;
        FUN_0044a600(&DAT_004a290c,(int *)local_8,extraout_ECX,&local_c);
        pbVar5 = local_8[0];
      }
      pbVar5 = pbVar5 + 0xc;
      if (pbVar5 != pbVar1) {
        pbVar1[0] = 0;
        pbVar1[1] = 0;
        pbVar1[2] = 0;
        pbVar1[3] = 0;
        puVar3 = *(undefined4 **)pbVar5;
        *(undefined4 *)pbVar5 = *(undefined4 *)pbVar1;
        if (puVar3 != (undefined4 *)0x0) {
          (**(code **)*puVar3)(1);
        }
      }
    }
    FUN_00432710(&DAT_004a294c,(int *)&local_c,(int *)pbVar4);
  }
  FUN_00436250(&DAT_004a2770,(int *)&local_c,(byte *)&local_10);
  if (local_c == DAT_004a2774) {
    local_c = (byte *)&local_10;
    FUN_0044a3a0(&DAT_004a2770,(int *)local_8,extraout_ECX_00,&local_c);
    local_c = local_8[0];
  }
  *(undefined4 *)(local_c + 0xc) = param_2;
  DAT_004a27ac = 0;
  return;
}


