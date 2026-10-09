// FUN_00410230 @ 00410230 size=338 callers=1

uint __fastcall FUN_00410230(undefined4 param_1,byte param_2,char param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined3 extraout_var;
  undefined4 *puVar5;
  int iVar6;
  uint local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  int local_4;
  
  iVar3 = (uint)param_2 << 8;
  if (DAT_004a24ae != '\0') {
    local_1c = 0;
    GetNumberOfPhysicalMonitorsFromHMONITOR(param_1,&local_1c);
    FUN_00432a70(&local_c,local_1c);
    iVar2 = GetPhysicalMonitorsFromHMONITOR(param_1,local_1c,local_c);
    uVar4 = 0;
    if (iVar2 != 0) {
      puVar5 = local_c;
      if (local_c != local_8) {
        do {
          iVar2 = GetMonitorBrightness(*puVar5,&local_14,&local_10,&local_18);
          if (iVar2 == 0) {
            bVar1 = FUN_00410150((char)((uint)iVar3 >> 8),param_3);
            iVar3 = CONCAT31((int3)((uint)iVar3 >> 8),bVar1);
          }
          else {
            if (param_3 == '\0') {
              iVar3 = (uint)((local_18 - local_14) * (int)(char)param_2) / 100 + local_14;
            }
            else {
              iVar6 = (char)param_2 + local_10;
              iVar2 = local_18;
              if (iVar6 < local_18) {
                iVar2 = iVar6;
              }
              iVar3 = local_14;
              if ((local_14 <= iVar2) && (iVar3 = local_18, iVar6 < local_18)) {
                iVar3 = iVar6;
              }
            }
            if ((iVar3 == local_10) || (iVar3 = SetMonitorBrightness(*puVar5,iVar3), iVar3 != 0)) {
              iVar3 = CONCAT31((uint3)param_2,1);
            }
            else {
              iVar3 = (uint)param_2 << 8;
            }
          }
          puVar5 = puVar5 + 0x41;
        } while (puVar5 != local_8);
      }
      uVar4 = DestroyPhysicalMonitors(local_1c,local_c);
    }
    if (local_c != (undefined4 *)0x0) {
      uVar4 = FUN_00402430(local_c,(local_4 - (int)local_c) / 0x104,0x104);
    }
    return CONCAT31((int3)((uint)uVar4 >> 8),(char)iVar3);
  }
  bVar1 = FUN_00410150(param_2,param_3);
  return CONCAT31(extraout_var,bVar1);
}


