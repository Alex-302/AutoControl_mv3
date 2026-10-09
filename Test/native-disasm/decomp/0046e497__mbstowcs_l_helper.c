// _mbstowcs_l_helper @ 0046e497 size=377 callers=1

/* Library Function - Single Match
    unsigned int __cdecl _mbstowcs_l_helper(wchar_t *,char const *,unsigned int,struct
   __crt_locale_pointers *)
   
   Library: Visual Studio 2015 Release */

uint __cdecl
_mbstowcs_l_helper(wchar_t *param_1,char *param_2,uint param_3,__crt_locale_pointers *param_4)

{
  char *pcVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  DWORD DVar5;
  byte *pbVar6;
  uint uVar7;
  int local_1c;
  localeinfo_struct local_18;
  char local_10;
  uint local_c;
  byte *local_8;
  
  uVar7 = 0;
  if (param_1 != (wchar_t *)0x0) {
    if (param_3 == 0) {
      return 0;
    }
    *param_1 = L'\0';
  }
  if (param_2 == (char *)0x0) {
    piVar3 = __errno();
    *piVar3 = 0x16;
    FUN_00465fa2();
    return 0xffffffff;
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_1c,param_4);
  if (param_1 == (wchar_t *)0x0) {
    if ((local_18.locinfo)->locale_name[2] == (wchar_t *)0x0) {
      pcVar1 = param_2 + 1;
      do {
        cVar2 = *param_2;
        param_2 = param_2 + 1;
      } while (cVar2 != '\0');
      uVar7 = (int)param_2 - (int)pcVar1;
      goto LAB_0046e5f7;
    }
    uVar7 = 0xffffffff;
    iVar4 = MultiByteToWideChar((local_18.locinfo)->lc_collate_cp,9,param_2,-1,(LPWSTR)0x0,0);
    if (iVar4 == 0) {
      piVar3 = __errno();
      *piVar3 = 0x2a;
      goto LAB_0046e5f7;
    }
  }
  else {
    if ((local_18.locinfo)->locale_name[2] == (wchar_t *)0x0) {
      if (param_3 != 0) {
        do {
          *param_1 = (ushort)(byte)param_2[uVar7];
          if (param_2[uVar7] == '\0') break;
          uVar7 = uVar7 + 1;
          param_1 = param_1 + 1;
        } while (uVar7 < param_3);
      }
      goto LAB_0046e5f7;
    }
    iVar4 = MultiByteToWideChar((local_18.locinfo)->lc_collate_cp,9,param_2,-1,param_1,param_3);
    if (iVar4 == 0) {
      DVar5 = GetLastError();
      pbVar6 = (byte *)param_2;
      uVar7 = param_3;
      if (DVar5 == 0x7a) {
        while (local_8 = pbVar6, uVar7 != 0) {
          local_c = uVar7 - 1;
          if (*local_8 == 0) break;
          iVar4 = __isleadbyte_l((uint)*local_8,&local_18);
          pbVar6 = local_8;
          if ((iVar4 != 0) && (pbVar6 = local_8 + 1, *pbVar6 == 0)) goto LAB_0046e5a0;
          pbVar6 = pbVar6 + 1;
          uVar7 = local_c;
        }
        uVar7 = MultiByteToWideChar((local_18.locinfo)->lc_collate_cp,1,param_2,
                                    (int)local_8 - (int)param_2,param_1,param_3);
        if (uVar7 != 0) goto LAB_0046e5f7;
      }
LAB_0046e5a0:
      piVar3 = __errno();
      *piVar3 = 0x2a;
      *param_1 = L'\0';
      uVar7 = 0xffffffff;
      goto LAB_0046e5f7;
    }
  }
  uVar7 = iVar4 - 1;
LAB_0046e5f7:
  if (local_10 != '\0') {
    *(uint *)(local_1c + 0x350) = *(uint *)(local_1c + 0x350) & 0xfffffffd;
  }
  return uVar7;
}


