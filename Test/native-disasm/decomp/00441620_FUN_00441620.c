// FUN_00441620 @ 00441620 size=145 callers=1

undefined4 * __fastcall FUN_00441620(undefined4 *param_1,char *param_2)

{
  char *pcVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  pcVar1 = param_2;
  if (0xf < *(uint *)(param_2 + 0x14)) {
    pcVar1 = *(char **)param_2;
  }
  uVar2 = FUN_004023b0(0,0,pcVar1);
  param_1[5] = 0xf;
  param_1[4] = 0;
  *(undefined1 *)param_1 = 0;
  FUN_0043ac10(param_1,uVar2,'\0');
  if (0xf < *(uint *)(param_2 + 0x14)) {
    param_2 = *(char **)param_2;
  }
  puVar3 = param_1;
  if (0xf < (uint)param_1[5]) {
    puVar3 = (undefined4 *)*param_1;
  }
  FUN_004023b0(puVar3,uVar2 + 1,param_2);
  return param_1;
}


