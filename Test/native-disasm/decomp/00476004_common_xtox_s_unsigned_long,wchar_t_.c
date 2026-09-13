// common_xtox_s<unsigned_long,wchar_t> @ 00476004 size=95 callers=1

/* Library Function - Single Match
    int __cdecl common_xtox_s<unsigned long,wchar_t>(unsigned long,wchar_t * const,unsigned
   int,unsigned int,bool)
   
   Library: Visual Studio 2015 Release */

int __cdecl
common_xtox_s<unsigned_long,wchar_t>
          (ulong param_1,wchar_t *param_2,uint param_3,uint param_4,bool param_5)

{
  int *piVar1;
  int iVar2;
  
  if ((param_2 != (wchar_t *)0x0) && (param_3 != 0)) {
    *param_2 = L'\0';
    if (param_3 <= param_5 + 1) {
      piVar1 = __errno();
      iVar2 = 0x22;
      goto LAB_00476018;
    }
    if (param_4 - 2 < 0x23) {
      iVar2 = common_xtox<unsigned_long,wchar_t>(param_1,param_2,param_3,param_4,param_5);
      return iVar2;
    }
  }
  piVar1 = __errno();
  iVar2 = 0x16;
LAB_00476018:
  *piVar1 = iVar2;
  FUN_00465fa2();
  return iVar2;
}


