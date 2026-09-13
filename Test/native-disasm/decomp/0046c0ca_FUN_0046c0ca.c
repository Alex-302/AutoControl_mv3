// FUN_0046c0ca @ 0046c0ca size=330 callers=2

undefined4 __cdecl
FUN_0046c0ca(char *param_1,uint param_2,int param_3,char param_4,int param_5,int *param_6,
            char param_7,__crt_locale_pointers *param_8)

{
  int *piVar1;
  char *_SizeInBytes;
  errno_t eVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  int local_14;
  int local_10;
  char local_8;
  
  iVar5 = param_3;
  if (param_3 < 1) {
    iVar5 = 0;
  }
  if (iVar5 + 9U < param_2) {
    _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,param_8);
    if (param_7 != '\0') {
      shift_bytes(param_1,param_2,param_1 + (*param_6 == 0x2d),(uint)(0 < param_3));
    }
    pcVar6 = param_1;
    if (*param_6 == 0x2d) {
      *param_1 = '-';
      pcVar6 = param_1 + 1;
    }
    if (0 < param_3) {
      *pcVar6 = pcVar6[1];
      pcVar6 = pcVar6 + 1;
      *pcVar6 = *(char *)**(undefined4 **)(local_10 + 0x88);
    }
    pcVar6 = pcVar6 + (uint)(param_7 == '\0') + param_3;
    _SizeInBytes = (char *)0xffffffff;
    if (param_2 != 0xffffffff) {
      _SizeInBytes = param_1 + (param_2 - (int)pcVar6);
    }
    eVar2 = _strcpy_s(pcVar6,(rsize_t)_SizeInBytes,"e+000");
    if (eVar2 != 0) {
                    /* WARNING: Subroutine does not return */
      __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
    }
    if (param_4 != '\0') {
      *pcVar6 = 'E';
    }
    if (*(char *)param_6[2] != '0') {
      iVar5 = param_6[1] + -1;
      if (iVar5 < 0) {
        iVar5 = -iVar5;
        pcVar6[1] = '-';
      }
      if (99 < iVar5) {
        iVar3 = iVar5 / 100;
        iVar5 = iVar5 % 100;
        pcVar6[2] = pcVar6[2] + (char)iVar3;
      }
      if (9 < iVar5) {
        iVar3 = iVar5 / 10;
        iVar5 = iVar5 % 10;
        pcVar6[3] = pcVar6[3] + (char)iVar3;
      }
      pcVar6[4] = pcVar6[4] + (char)iVar5;
    }
    if ((param_5 == 2) && ((char)*(uint *)(pcVar6 + 2) == '0')) {
      FUN_0045b0e0((uint *)(pcVar6 + 2),(uint *)(pcVar6 + 3),3);
    }
    if (local_8 != '\0') {
      *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
    }
    uVar4 = 0;
  }
  else {
    piVar1 = __errno();
    uVar4 = 0x22;
    *piVar1 = 0x22;
    FUN_00465fa2();
  }
  return uVar4;
}


