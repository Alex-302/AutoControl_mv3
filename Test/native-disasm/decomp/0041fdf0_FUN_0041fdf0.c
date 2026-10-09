// FUN_0041fdf0 @ 0041fdf0 size=270 callers=1

undefined4 __fastcall FUN_0041fdf0(undefined4 *param_1)

{
  char cVar1;
  char cVar2;
  void *pvVar3;
  uint uVar4;
  char *extraout_EDX;
  char *pcVar5;
  void *pvVar6;
  undefined4 uStack_4;
  
  cVar1 = *(char *)((int)param_1 + 0x45);
  uStack_4 = param_1;
  if ((cVar1 != 'N') || ((DAT_004a26c2 & 0xfc00) != 0x1800)) {
    pvVar6 = (void *)param_1[0xf];
    pvVar3 = _memchr((void *)param_1[0xe],(uint)DAT_004a26b3,(int)pvVar6 - (int)param_1[0xe]);
    if (pvVar3 != (void *)0x0) {
      pvVar6 = pvVar3;
    }
    if ((pvVar6 == (void *)param_1[0xf]) || ((int)pvVar6 - param_1[0xe] == -1)) goto LAB_0041fea3;
  }
  if (DAT_004a264a != '\0') {
    pvVar6 = (void *)param_1[0xf];
    pvVar3 = _memchr((void *)param_1[0xe],0x62,(int)pvVar6 - (int)param_1[0xe]);
    if (pvVar3 != (void *)0x0) {
      pvVar6 = pvVar3;
    }
    if ((pvVar6 != (void *)param_1[0xf]) && ((int)pvVar6 - param_1[0xe] != -1)) goto LAB_0041fea3;
  }
  cVar2 = DAT_004a26b2;
  if (cVar1 == 'N') {
    FUN_00434d30(param_1,param_1 + 7);
    param_1[3] = param_1[10];
    param_1[4] = param_1[0xb];
    param_1[5] = param_1[0xc];
    pvVar3 = (void *)CONCAT22((short)((uint)param_1[0xc] >> 0x10),*(undefined2 *)(param_1 + 0xd));
    *(undefined2 *)(param_1 + 6) = *(undefined2 *)(param_1 + 0xd);
    *(undefined1 *)((int)param_1 + 0x45) = 0x53;
LAB_0041fea3:
    return CONCAT31((int3)((uint)pvVar3 >> 8),1);
  }
  cVar1 = *(char *)((int)param_1 + 0x45);
  *(char *)((int)param_1 + 0x45) = DAT_004a26b2;
  pcVar5 = (char *)*param_1;
  if ((param_1[1] - (int)pcVar5 != 1) || (uVar4 = 0, *pcVar5 != '\0')) {
    if ((cVar1 != 'D') || (cVar2 != 'U')) {
      pvVar3 = (void *)FUN_004131d0(&DAT_004a26b0);
      pcVar5 = extraout_EDX;
      if ((char)pvVar3 != '\0') goto LAB_0041fea3;
    }
    param_1[1] = pcVar5;
    uStack_4 = (undefined4 *)((uint)uStack_4 & 0xffffff);
    uVar4 = FUN_00434cd0(param_1,(undefined1 *)((int)&uStack_4 + 3));
  }
  return uVar4 & 0xffffff00;
}


