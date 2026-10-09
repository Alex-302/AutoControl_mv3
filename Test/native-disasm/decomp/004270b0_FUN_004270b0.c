// FUN_004270b0 @ 004270b0 size=450 callers=2

void __fastcall FUN_004270b0(undefined4 *param_1)

{
  char cVar1;
  char *pcVar2;
  UINT UVar3;
  undefined8 uVar4;
  void *local_3c [4];
  undefined4 local_2c;
  uint local_28;
  char local_24 [8];
  undefined8 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c610;
  local_10 = ExceptionList;
  if ((DAT_004a2998 != 0) || (DAT_004a299c != 0)) {
    local_24[0] = '\0';
    local_1c = 0;
    ExceptionList = &local_10;
    FUN_00451040(local_24,DAT_004a29bc);
    local_8 = 0;
    pcVar2 = (char *)FUN_00440e70((void *)*param_1,(uint *)"marked");
    cVar1 = *pcVar2;
    *pcVar2 = local_24[0];
    uVar4 = *(undefined8 *)(pcVar2 + 8);
    *(undefined4 *)(pcVar2 + 8) = (undefined4)local_1c;
    *(undefined4 *)(pcVar2 + 0xc) = local_1c._4_4_;
    local_24[0] = cVar1;
    local_1c = uVar4;
    FUN_00434820(local_24);
    local_24[0] = '\0';
    local_1c = 0;
    FUN_00451040(local_24,DAT_004a29c0);
    local_8 = 1;
    pcVar2 = (char *)FUN_00440e70((void *)*param_1,(uint *)"hilited");
    local_8 = 0xffffffff;
    cVar1 = *pcVar2;
    *pcVar2 = local_24[0];
    uVar4 = *(undefined8 *)(pcVar2 + 8);
    *(undefined4 *)(pcVar2 + 8) = (undefined4)local_1c;
    *(undefined4 *)(pcVar2 + 0xc) = local_1c._4_4_;
    local_24[0] = cVar1;
    local_1c = uVar4;
    FUN_00434820(local_24);
    local_28 = 0xf;
    local_2c = 0;
    local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
    FUN_0043ace0(local_3c,(uint *)"usePrvMsPos",0xb);
    local_8 = 2;
    cVar1 = FUN_00441100((void *)param_1[1],local_3c);
    if (cVar1 == '\0') {
      uVar4 = FUN_00410800('\0');
    }
    else {
      uVar4 = CONCAT44(DAT_004a23e4,DAT_004a23e0);
    }
    UVar3 = FUN_0041d3c0('\0',(LONG)uVar4,(LONG)((ulonglong)uVar4 >> 0x20));
    local_24[0] = '\0';
    local_1c = 0;
    FUN_00451040(local_24,UVar3);
    local_8 = CONCAT31(local_8._1_3_,3);
    pcVar2 = (char *)FUN_00440e70((void *)*param_1,(uint *)"hovered");
    cVar1 = *pcVar2;
    *pcVar2 = local_24[0];
    uVar4 = *(undefined8 *)(pcVar2 + 8);
    *(undefined4 *)(pcVar2 + 8) = (undefined4)local_1c;
    *(undefined4 *)(pcVar2 + 0xc) = local_1c._4_4_;
    local_24[0] = cVar1;
    local_1c = uVar4;
    FUN_00434820(local_24);
    if (0xf < local_28) {
      FUN_00402430(local_3c[0],local_28 + 1,1);
    }
  }
  ExceptionList = local_10;
  return;
}


