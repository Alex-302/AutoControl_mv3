// FUN_0042bf00 @ 0042bf00 size=265 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0042bf00(char *param_1)

{
  LONG LVar1;
  char *pcVar2;
  char local_19;
  tagPOINT local_18;
  LONG local_10;
  
  if (*param_1 == '\x04') {
    FUN_00453610(param_1,&local_19);
    if (local_19 == '\0') {
      FUN_004190a0((byte *)&DAT_004a2614);
      return;
    }
    if (*param_1 == '\x04') {
      GetCursorPos(&local_18);
      local_10 = local_18.x;
      goto LAB_0042bf8a;
    }
  }
  pcVar2 = (char *)FUN_00440dd0(param_1,(uint *)&DAT_0048d65c);
  FUN_004536b0(pcVar2,(uint *)&local_18);
  LVar1 = local_18.x;
  pcVar2 = (char *)FUN_00440dd0(param_1,(uint *)&DAT_0048d660);
  FUN_004536b0(pcVar2,(uint *)&local_18);
  local_10 = LVar1;
  local_18.y = local_18.x;
LAB_0042bf8a:
  _DAT_004a2640 = DAT_004a2848 * _DAT_0048f264;
  DAT_004a23e0 = local_10;
  _DAT_004a262c = local_10;
  _DAT_004a2634 = local_10;
  _DAT_004a2648 = 0x49010008;
  DAT_004a263c = 0;
  _DAT_004a2644 = 0;
  DAT_004a23e4 = local_18.y;
  _DAT_004a2630 = local_18.y;
  _DAT_004a2638 = local_18.y;
  FUN_004195f0(&DAT_004a2614,'\0',0);
  return;
}


