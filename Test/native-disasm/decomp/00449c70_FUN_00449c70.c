// FUN_00449c70 @ 00449c70 size=424 callers=3

byte * __thiscall FUN_00449c70(void *this,byte *param_1,byte *param_2,int param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  
  if (param_3 == 0) {
    param_3 = *(int *)((int)this + 0x58);
  }
  if (param_1 == param_2) {
    return param_1;
  }
  do {
    if (param_3 == 0) {
      return param_1;
    }
    switch(*(undefined4 *)(param_3 + 4)) {
    case 1:
    case 8:
    case 9:
    case 0xd:
    case 0xe:
    case 0x14:
      param_3 = *(int *)(param_3 + 0xc);
      break;
    case 2:
      if ((*(byte *)((int)this + 0x60) & 1) != 0) {
        return param_2;
      }
      do {
        if (param_1[-1] == 10) {
          return param_1;
        }
        param_1 = param_1 + 1;
      } while (param_1 != param_2);
      return param_1;
    case 3:
      if ((*(byte *)((int)this + 0x60) & 2) != 0) {
        return param_2;
      }
      do {
        if (*param_1 == 10) {
          return param_1;
        }
        param_1 = param_1 + 1;
      } while (param_1 != param_2);
      return param_1;
    default:
      return param_1;
    case 6:
      goto switchD_00449caa_caseD_6;
    case 7:
      goto switchD_00449caa_caseD_7;
    case 0xc:
    case 0x15:
      param_3 = 0;
      break;
    case 0x10:
      do {
        if (param_3 == 0) {
          return param_2;
        }
        param_2 = FUN_00449c70(this,param_1,param_2,*(int *)(param_3 + 0xc));
        param_3 = *(int *)(param_3 + 0x18);
      } while (param_1 != param_2);
      return param_2;
    }
  } while( true );
switchD_00449caa_caseD_7:
  bVar1 = *param_1;
  if ((*(uint **)(param_3 + 0x14) == (uint *)0x0) ||
     (pbVar4 = (byte *)FUN_0044f050((char *)param_1,(char *)(param_1 + 1),*(uint **)(param_3 + 0x14)
                                   ), pbVar4 == param_1)) {
    uVar5 = (uint)bVar1;
    if (*(int *)(param_3 + 0x20) != 0) {
      if ((*(uint *)((int)this + 0x5c) & 0x800) != 0) {
        cVar2 = FUN_0044d7d0(*(void **)((int)this + 0x70),bVar1);
        uVar5 = (uint)cVar2;
      }
      uVar5 = FUN_0044ef90(uVar5 & 0xff,*(int *)(param_3 + 0x20));
      if ((char)uVar5 != '\0') {
        uVar5 = 1;
        goto LAB_00449dd3;
      }
    }
    if ((*(int *)(param_3 + 0x18) == 0) ||
       ((*(byte *)((uint)(bVar1 >> 3) + *(int *)(param_3 + 0x18)) & (byte)(1 << (bVar1 & 7))) == 0))
    {
      uVar5 = 0;
    }
    else {
      uVar5 = 1;
    }
  }
  else {
    uVar5 = 1;
  }
LAB_00449dd3:
  if (uVar5 != (*(uint *)(param_3 + 8) & 1)) {
    return param_1;
  }
  param_1 = param_1 + 1;
  if (param_1 == param_2) {
    return param_1;
  }
  goto switchD_00449caa_caseD_7;
switchD_00449caa_caseD_6:
  do {
    pbVar4 = param_1 + 1;
    pbVar3 = FUN_0044efd0(param_1,pbVar4,*(byte **)(param_3 + 0x1c),*(byte **)(param_3 + 0x1c) + 1,
                          *(int *)((int)this + 0x70),*(uint *)((int)this + 0x5c));
    if (pbVar3 != param_1) {
      return param_1;
    }
    param_1 = pbVar4;
  } while (pbVar4 != param_2);
  return pbVar4;
}


