// FUN_00473998 @ 00473998 size=169 callers=1

int __cdecl FUN_00473998(int param_1,wchar_t *param_2,rsize_t param_3)

{
  wchar_t *_Src;
  int iVar1;
  uint uVar2;
  errno_t eVar3;
  int iVar4;
  int iVar5;
  
  if ((((param_1 != 0) && (param_1 != 0x400)) && (param_1 != 0x800)) &&
     (((param_2 != (wchar_t *)0x0 || ((int)param_3 < 1)) && (-1 < (int)param_3)))) {
    iVar5 = 0;
    iVar4 = 0xe3;
    do {
      iVar1 = (iVar4 + iVar5) / 2;
      if (param_1 == *(int *)(&DAT_00487a28 + iVar1 * 8)) goto LAB_004739f9;
      if (param_1 - *(int *)(&DAT_00487a28 + iVar1 * 8) < 0) {
        iVar4 = iVar1 + -1;
      }
      else {
        iVar5 = iVar1 + 1;
      }
    } while (iVar5 <= iVar4);
    iVar1 = -1;
LAB_004739f9:
    if (-1 < iVar1) {
      _Src = *(wchar_t **)(&UNK_00487a2c + iVar1 * 8);
      uVar2 = FUN_00466f34(_Src,0x55);
      if (0 < (int)param_3) {
        if ((int)param_3 <= (int)uVar2) {
          return 0;
        }
        eVar3 = _wcscpy_s(param_2,param_3,_Src);
        if (eVar3 != 0) {
                    /* WARNING: Subroutine does not return */
          __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
        }
      }
      return uVar2 + 1;
    }
  }
  return 0;
}


