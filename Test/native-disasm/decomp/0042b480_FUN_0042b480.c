// FUN_0042b480 @ 0042b480 size=149 callers=1

undefined1 * __cdecl FUN_0042b480(undefined1 *param_1,char *param_2)

{
  int *piVar1;
  UINT UVar2;
  void *local_c [2];
  int local_4;
  
  piVar1 = FUN_0040c190((int *)local_c,param_2,0xd6c18935,'\x01');
  UVar2 = SendInput((piVar1[1] - *piVar1) / 0x1c,(LPINPUT)*piVar1,0x1c);
  *param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  FUN_00451040(param_1,UVar2);
  if (local_c[0] != (void *)0x0) {
    FUN_00402430(local_c[0],(local_4 - (int)local_c[0]) / 0x1c,0x1c);
  }
  return param_1;
}


