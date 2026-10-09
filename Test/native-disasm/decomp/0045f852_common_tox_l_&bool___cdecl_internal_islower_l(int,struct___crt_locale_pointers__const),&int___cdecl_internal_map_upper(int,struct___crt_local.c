// common_tox_l<&bool___cdecl_internal_islower_l(int,struct___crt_locale_pointers*_const),&int___cdecl_internal_map_upper(int,struct___crt_locale_pointers*_const)> @ 0045f852 size=330 callers=1

/* Library Function - Single Match
    int __cdecl common_tox_l<&bool __cdecl internal_islower_l(int,struct __crt_locale_pointers *
   const),&int __cdecl internal_map_upper(int,struct __crt_locale_pointers * const)>(int,unsigned
   long,struct __crt_locale_pointers * const)
   
   Library: Visual Studio 2015 Release */

int __cdecl
common_tox_l<&bool___cdecl_internal_islower_l(int,struct___crt_locale_pointers*_const),&int___cdecl_internal_map_upper(int,struct___crt_locale_pointers*_const)>
          (int param_1,ulong param_2,__crt_locale_pointers *param_3)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  int local_20;
  localeinfo_struct local_1c;
  char local_14;
  uint local_10;
  byte local_c [4];
  undefined2 local_8;
  undefined1 local_6;
  
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_20,param_3);
  if ((uint)param_1 < 0x100) {
    bVar2 = internal_islower_l(param_1,(__crt_locale_pointers *)&local_1c);
    if (bVar2) {
      bVar1 = (local_1c.locinfo)->pcumap[param_1];
      if (local_14 == '\0') {
        return (uint)bVar1;
      }
      *(uint *)(local_20 + 0x350) = *(uint *)(local_20 + 0x350) & 0xfffffffd;
      return (uint)bVar1;
    }
    if (local_14 == '\0') {
      return param_1;
    }
    *(uint *)(local_20 + 0x350) = *(uint *)(local_20 + 0x350) & 0xfffffffd;
    return param_1;
  }
  local_8 = 0;
  local_6 = 0;
  if (1 < (int)(local_1c.locinfo)->lc_codepage) {
    local_10 = param_1 >> 8;
    iVar3 = __isleadbyte_l(local_10 & 0xff,&local_1c);
    if (iVar3 != 0) {
      local_8 = CONCAT11((byte)param_1,(char)local_10);
      local_6 = 0;
      iVar3 = 2;
      goto LAB_0045f912;
    }
  }
  piVar4 = __errno();
  *piVar4 = 0x2a;
  iVar3 = 1;
  local_8 = (ushort)(byte)param_1;
LAB_0045f912:
  local_c[0] = 0;
  local_c[1] = 0;
  local_c[2] = 0;
  iVar3 = ___acrt_LCMapStringA
                    ((__crt_locale_pointers *)&local_1c,(local_1c.locinfo)->locale_name[2],param_2,
                     (char *)&local_8,iVar3,(char *)local_c,3,(local_1c.locinfo)->lc_collate_cp,1);
  if (iVar3 == 0) {
    if (local_14 != '\0') {
      *(uint *)(local_20 + 0x350) = *(uint *)(local_20 + 0x350) & 0xfffffffd;
    }
  }
  else if (iVar3 == 1) {
    param_1 = (int)local_c[0];
    if (local_14 != '\0') {
      *(uint *)(local_20 + 0x350) = *(uint *)(local_20 + 0x350) & 0xfffffffd;
    }
  }
  else {
    param_1 = (int)CONCAT11(local_c[0],local_c[1]);
    if (local_14 != '\0') {
      *(uint *)(local_20 + 0x350) = *(uint *)(local_20 + 0x350) & 0xfffffffd;
    }
  }
  return param_1;
}


