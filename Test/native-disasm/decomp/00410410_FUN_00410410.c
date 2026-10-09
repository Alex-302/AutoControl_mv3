// FUN_00410410 @ 00410410 size=309 callers=1

undefined1 * __fastcall FUN_00410410(undefined1 *param_1,uint *param_2)

{
  bool bVar1;
  bool bVar2;
  uint *puVar3;
  uint uVar4;
  uint local_c;
  undefined1 *local_8;
  undefined4 local_4;
  
  local_4 = 0;
  local_c = 0xffff;
  uVar4 = 100000;
  if (param_2[4] < 100000) {
    uVar4 = param_2[4];
  }
  puVar3 = param_2;
  if (0xf < param_2[5]) {
    puVar3 = (uint *)*param_2;
  }
  local_8 = param_1;
  IsTextUnicode(puVar3,uVar4,(LPINT)&local_c);
  if (((local_c & 0xf00) == 0) && (1 < param_2[4])) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (2 < param_2[4]) {
    puVar3 = param_2;
    if (0xf < param_2[5]) {
      puVar3 = (uint *)*param_2;
    }
    if ((*puVar3 & 0xffffff) == 0xbfbbef) {
      bVar2 = true;
      goto LAB_004104a5;
    }
  }
  bVar2 = false;
LAB_004104a5:
  if (((local_c & 0xf) != 0) && (!bVar1)) {
    FUN_004355e0(param_1,(uint *)"UTF-16LE");
    return param_1;
  }
  if ((local_c & 0xf0) != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0xf;
    *(undefined4 *)(param_1 + 0x10) = 0;
    *param_1 = 0;
    FUN_0043ace0(param_1,(uint *)"UTF-16BE",8);
    return param_1;
  }
  if ((local_c & 0xf000) == 0) {
    if ((!bVar2) && (uVar4 = FUN_00410390(param_2), (char)uVar4 == '\0')) {
      FUN_004355e0(param_1,(uint *)"US-ASCII");
      return param_1;
    }
    FUN_004355e0(param_1,(uint *)"UTF-8");
    return param_1;
  }
  FUN_004355e0(param_1,(uint *)"unknown");
  return param_1;
}


