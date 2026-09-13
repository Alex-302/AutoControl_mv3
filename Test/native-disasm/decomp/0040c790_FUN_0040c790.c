// FUN_0040c790 @ 0040c790 size=185 callers=1

void * __fastcall FUN_0040c790(void *param_1,undefined4 *param_2,char param_3)

{
  ushort *puVar1;
  char *extraout_ECX;
  ushort *puVar2;
  char local_30 [8];
  undefined8 local_28;
  void *local_20;
  uint local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0047a001;
  local_10 = ExceptionList;
  local_8 = 0;
  local_18 = 0;
  ExceptionList = &local_10;
  local_20 = param_1;
  FUN_00434b00(param_1,(char *)0x0,(char *)0x0);
  local_8 = 0;
  puVar2 = (ushort *)*param_2;
  puVar1 = (ushort *)param_2[1];
  local_18 = 1;
  if (puVar2 != puVar1) {
    local_1c = 0x400;
    if (param_3 != '\0') {
      local_1c = 0;
    }
    do {
      local_30[0] = '\0';
      local_28 = 0;
      FUN_00450f50(local_30,*puVar2 | local_1c);
      local_8 = 1;
      FUN_00433e10(param_1,extraout_ECX);
      local_8 = local_8 & 0xffffff00;
      FUN_00434820(local_30);
      puVar2 = puVar2 + 1;
    } while (puVar2 != puVar1);
  }
  ExceptionList = local_10;
  return param_1;
}


