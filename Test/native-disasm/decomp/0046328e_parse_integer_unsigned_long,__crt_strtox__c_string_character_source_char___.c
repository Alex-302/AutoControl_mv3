// parse_integer<unsigned_long,__crt_strtox::c_string_character_source<char>_> @ 0046328e size=552 callers=2

/* Library Function - Single Match
    unsigned long __cdecl __crt_strtox::parse_integer<unsigned long,class
   __crt_strtox::c_string_character_source<char> >(struct __crt_locale_pointers * const,class
   __crt_strtox::c_string_character_source<char>,int,bool)
   
   Library: Visual Studio 2015 Release */

ulong __cdecl
__crt_strtox::parse_integer<unsigned_long,__crt_strtox::c_string_character_source<char>_>
          (__crt_locale_pointers *param_1,byte *param_2,undefined4 *param_3,uint param_4,
          char param_5)

{
  byte bVar1;
  bool bVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  int local_2c;
  localeinfo_struct local_28;
  char local_20;
  byte *local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  byte local_8;
  undefined3 uStack_7;
  
  bVar2 = c_string_character_source<char>::validate((c_string_character_source<char> *)&param_2);
  uVar8 = param_4;
  if (bVar2) {
    if ((param_4 == 0) || ((1 < (int)param_4 && ((int)param_4 < 0x25)))) {
      _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_2c,param_1);
      local_10 = 0;
      local_1c = param_2;
      do {
        bVar7 = *param_2;
        param_2 = param_2 + 1;
        _local_8 = CONCAT31(uStack_7,bVar7);
        iVar4 = __ischartype_l((uint)bVar7,8,&local_28);
      } while (iVar4 != 0);
      local_c = (uint)(param_5 != '\0');
      if (bVar7 == 0x2d) {
        local_c = local_c | 2;
LAB_00463331:
        bVar7 = *param_2;
        param_2 = param_2 + 1;
        _local_8 = CONCAT31(uStack_7,bVar7);
      }
      else if (bVar7 == 0x2b) goto LAB_00463331;
      if ((uVar8 == 0) || (uVar8 == 0x10)) {
        if ((byte)(bVar7 - 0x30) < 10) {
          iVar4 = (char)bVar7 + -0x30;
        }
        else if ((byte)(bVar7 + 0x9f) < 0x1a) {
          iVar4 = (char)bVar7 + -0x57;
        }
        else if ((byte)(bVar7 + 0xbf) < 0x1a) {
          iVar4 = (char)bVar7 + -0x37;
        }
        else {
          iVar4 = -1;
        }
        if (iVar4 == 0) {
          bVar1 = *param_2;
          local_14 = CONCAT31(local_14._1_3_,bVar1);
          if ((bVar1 == 0x78) || (bVar1 == 0x58)) {
            if (uVar8 == 0) {
              uVar8 = 0x10;
            }
            bVar7 = param_2[1];
            param_2 = param_2 + 2;
            _local_8 = CONCAT31(uStack_7,bVar7);
          }
          else {
            if (uVar8 == 0) {
              uVar8 = 8;
            }
            param_2 = param_2 + 1;
            c_string_character_source<char>::unget
                      ((c_string_character_source<char> *)&param_2,bVar1);
          }
        }
        else if (uVar8 == 0) {
          uVar8 = 10;
        }
      }
      local_14 = (uint)(0xffffffff / (ulonglong)uVar8);
      local_18 = (uint)(0xffffffff % (ulonglong)uVar8);
      while( true ) {
        if ((byte)(bVar7 - 0x30) < 10) {
          uVar5 = (int)(char)bVar7 - 0x30;
        }
        else if ((byte)(bVar7 + 0x9f) < 0x1a) {
          uVar5 = (int)(char)bVar7 - 0x57;
        }
        else if ((byte)(bVar7 + 0xbf) < 0x1a) {
          uVar5 = (int)(char)bVar7 - 0x37;
        }
        else {
          uVar5 = 0xffffffff;
        }
        if ((uVar5 == 0xffffffff) || (uVar8 <= uVar5)) break;
        uVar6 = local_c | 8;
        if ((local_10 < local_14) || ((local_10 == local_14 && (uVar5 <= local_18)))) {
          local_10 = local_10 * uVar8 + uVar5;
        }
        else {
          uVar6 = local_c | 0xc;
        }
        bVar7 = *param_2;
        param_2 = param_2 + 1;
        _local_8 = CONCAT31(uStack_7,bVar7);
        local_c = uVar6;
      }
      c_string_character_source<char>::unget
                ((c_string_character_source<char> *)&param_2,(char)_local_8);
      uVar5 = local_c;
      uVar8 = local_10;
      if ((local_c & 8) == 0) {
        uVar8 = 0;
        param_2 = local_1c;
      }
      else {
        bVar2 = is_overflow_condition<unsigned_long>(local_c,local_10);
        if (bVar2) {
          piVar3 = __errno();
          *piVar3 = 0x22;
          if ((uVar5 & 1) == 0) {
            uVar8 = 0xffffffff;
          }
          else if ((uVar5 & 2) == 0) {
            uVar8 = 0x7fffffff;
          }
          else {
            uVar8 = 0x80000000;
          }
        }
        else if ((uVar5 & 2) != 0) {
          uVar8 = -uVar8;
        }
      }
      if (local_20 != '\0') {
        *(uint *)(local_2c + 0x350) = *(uint *)(local_2c + 0x350) & 0xfffffffd;
      }
      goto LAB_004632c7;
    }
    piVar3 = __errno();
    *piVar3 = 0x16;
    FUN_00465fa2();
  }
  uVar8 = 0;
LAB_004632c7:
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = param_2;
  }
  return uVar8;
}


