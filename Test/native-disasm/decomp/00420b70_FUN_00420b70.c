// FUN_00420b70 @ 00420b70 size=393 callers=1

void __fastcall FUN_00420b70(int *param_1)

{
  uint *puVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  char *extraout_ECX;
  undefined **local_64 [9];
  undefined ***local_40;
  char local_3c [16];
  undefined1 local_2c [8];
  undefined8 local_24;
  int local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bb53;
  local_10 = ExceptionList;
  if (param_1[3] == DAT_004a29e8) {
    iVar3 = *param_1;
    ExceptionList = &local_10;
    *(undefined1 *)(iVar3 + 0x1f) = 0;
    FUN_004190a0((byte *)param_1[1]);
    iVar4 = DAT_004a28b0;
    if (*(char *)(iVar3 + 0x21) != '\0') {
      uVar2 = *(ushort *)(param_1 + 2);
      if ((uVar2 & 0xfc00) == 0) {
        if (((uVar2 & 0xfc00) == 0) || ((uVar2 & 0xfc00) == 0x400)) {
          if ((1 << ((byte)uVar2 & 0x1f) & *(uint *)(DAT_004a28b0 + ((uVar2 & 0x3ff) >> 5) * 4)) !=
              0) {
            FUN_00413270(&local_18,uVar2);
            local_2c[0] = 0;
            puVar1 = (uint *)(iVar4 + ((local_18 & 0xffff) >> 5) * 4);
            local_24 = 0;
            *puVar1 = *puVar1 & ~(1 << (local_18 & 0x1f));
            (&DAT_004a26b8)[local_18._3_1_] = (&DAT_004a26b8)[local_18._3_1_] + -1;
            FUN_004512e0(local_2c,local_18);
            local_8 = 0;
            FUN_00434b50(local_3c,extraout_ECX,(char *)&local_1c,'\x01','\x02');
            local_8 = CONCAT31(local_8._1_3_,1);
            piVar5 = FUN_0040c190(&local_1c,local_3c,0xd6c18935,'\0');
            FUN_0040c000(piVar5);
            FUN_00432b50(&local_1c);
            FUN_00434820(local_3c);
            local_8 = 0xffffffff;
            _eh_vector_destructor_iterator_(local_2c,0x10,1,FUN_00434820);
          }
        }
      }
    }
    local_40 = local_64;
    local_64[0] = &PTR_LAB_0048e820;
    local_8 = 2;
    FUN_0040f6b0(DAT_004a23dc,(int *)local_40,0);
    if (local_40 != (undefined ***)0x0) {
      (*(code *)(*local_40)[4])(local_40 != local_64);
    }
  }
  ExceptionList = local_10;
  return;
}


