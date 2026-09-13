// FUN_00458200 @ 00458200 size=156 callers=1

char * __fastcall FUN_00458200(int *param_1,int *param_2,char *param_3)

{
  char cVar1;
  undefined8 uVar2;
  uint uVar3;
  uint uVar4;
  char local_10 [8];
  undefined8 local_8;
  
  uVar3 = (uint)((int)param_2 + (3 - (int)param_1)) >> 2;
  uVar4 = 0;
  if (param_2 < param_1) {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    return param_3;
  }
  do {
    if (param_3 != (char *)0x0) {
      *param_3 = '\0';
      param_3[8] = '\0';
      param_3[9] = '\0';
      param_3[10] = '\0';
      param_3[0xb] = '\0';
      param_3[0xc] = '\0';
      param_3[0xd] = '\0';
      param_3[0xe] = '\0';
      param_3[0xf] = '\0';
      local_10[0] = '\0';
      local_8 = 0;
      FUN_00450f50(local_10,*param_1);
      cVar1 = *param_3;
      *param_3 = local_10[0];
      uVar2 = *(undefined8 *)(param_3 + 8);
      *(undefined4 *)(param_3 + 8) = (undefined4)local_8;
      *(undefined4 *)(param_3 + 0xc) = local_8._4_4_;
      local_10[0] = cVar1;
      local_8 = uVar2;
      FUN_00434820(local_10);
    }
    uVar4 = uVar4 + 1;
    param_3 = param_3 + 0x10;
    param_1 = param_1 + 1;
  } while (uVar4 != uVar3);
  return param_3;
}


