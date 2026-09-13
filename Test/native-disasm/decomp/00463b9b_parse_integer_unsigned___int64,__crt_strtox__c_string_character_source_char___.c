// parse_integer<unsigned___int64,__crt_strtox::c_string_character_source<char>_> @ 00463b9b size=678 callers=2

/* WARNING: Removing unreachable block (ram,0x00463d70) */
/* Library Function - Single Match
    unsigned __int64 __cdecl __crt_strtox::parse_integer<unsigned __int64,class
   __crt_strtox::c_string_character_source<char> >(struct __crt_locale_pointers * const,class
   __crt_strtox::c_string_character_source<char>,int,bool)
   
   Library: Visual Studio 2015 Release */

__uint64 __cdecl
__crt_strtox::parse_integer<unsigned___int64,__crt_strtox::c_string_character_source<char>_>
          (__crt_locale_pointers *param_1,byte *param_2,undefined4 *param_3,uint param_4,
          char param_5)

{
  ulonglong uVar1;
  bool bVar2;
  int *piVar3;
  byte bVar4;
  uint extraout_ECX;
  char cVar5;
  int unaff_EBX;
  undefined3 uVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  ulonglong uVar10;
  longlong lVar11;
  int iVar12;
  int local_44;
  localeinfo_struct local_40;
  char local_38;
  byte *local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18;
  uint local_14;
  byte local_10;
  undefined3 uStack_f;
  uint local_c;
  byte local_5;
  
  bVar2 = c_string_character_source<char>::validate((c_string_character_source<char> *)&param_2);
  if (bVar2) {
    if ((param_4 == 0) || ((1 < (int)param_4 && ((int)param_4 < 0x25)))) {
      iVar12 = unaff_EBX;
      _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_44,param_1);
      local_14 = 0;
      local_34 = param_2;
      do {
        bVar4 = *param_2;
        uVar6 = (undefined3)((uint)unaff_EBX >> 8);
        unaff_EBX = CONCAT31(uVar6,bVar4);
        param_2 = param_2 + 1;
        _local_10 = CONCAT31(uStack_f,bVar4);
        local_5 = bVar4;
        iVar7 = __ischartype_l((uint)bVar4,8,&local_40);
      } while (iVar7 != 0);
      local_c = (uint)(param_5 != '\0');
      if (bVar4 == 0x2d) {
        local_c = local_c | 2;
LAB_00463c49:
        local_5 = *param_2;
        unaff_EBX = CONCAT31(uVar6,local_5);
        param_2 = param_2 + 1;
        _local_10 = CONCAT31(uStack_f,local_5);
      }
      else if (bVar4 == 0x2b) goto LAB_00463c49;
      if ((param_4 == 0) || (param_4 == 0x10)) {
        cVar5 = (char)unaff_EBX;
        if ((byte)(cVar5 - 0x30U) < 10) {
          iVar7 = cVar5 + -0x30;
        }
        else if ((byte)(cVar5 + 0x9fU) < 0x1a) {
          iVar7 = cVar5 + -0x57;
        }
        else if ((byte)(cVar5 + 0xbfU) < 0x1a) {
          iVar7 = cVar5 + -0x37;
        }
        else {
          iVar7 = -1;
        }
        if (iVar7 == 0) {
          bVar4 = *param_2;
          local_20 = CONCAT31(local_20._1_3_,bVar4);
          if ((bVar4 == 0x78) || (bVar4 == 0x58)) {
            if (param_4 == 0) {
              param_4 = 0x10;
            }
            local_5 = param_2[1];
            param_2 = param_2 + 2;
            _local_10 = CONCAT31(uStack_f,local_5);
          }
          else {
            if (param_4 == 0) {
              param_4 = 8;
            }
            param_2 = param_2 + 1;
            c_string_character_source<char>::unget
                      ((c_string_character_source<char> *)&param_2,bVar4);
          }
        }
        else if (param_4 == 0) {
          param_4 = 10;
        }
      }
      pbVar9 = param_2;
      local_2c = (int)param_4 >> 0x1f;
      local_30 = param_4;
      uVar10 = __aulldvrm(0xffffffff,0xffffffff,param_4,local_2c);
      uVar1 = (ulonglong)local_14;
      bVar4 = local_5;
      local_28 = extraout_ECX;
      local_24 = unaff_EBX;
      while( true ) {
        iVar7 = (int)(uVar1 >> 0x20);
        local_14 = (uint)uVar1;
        local_20 = (undefined4)(uVar10 >> 0x20);
        local_1c = (undefined4)uVar10;
        if ((byte)(bVar4 - 0x30) < 10) {
          local_18 = (int)(char)bVar4 - 0x30;
        }
        else if ((byte)(bVar4 + 0x9f) < 0x1a) {
          local_18 = (int)(char)bVar4 - 0x57;
        }
        else if ((byte)(bVar4 + 0xbf) < 0x1a) {
          local_18 = (int)(char)bVar4 - 0x37;
        }
        else {
          local_18 = 0xffffffff;
        }
        if ((local_18 == 0xffffffff) || (param_4 <= local_18)) break;
        if ((uVar1 < uVar10) || ((uVar10 == uVar1 && ((local_24 != 0 || (local_18 <= local_28))))))
        {
          local_c = local_c | 8;
          lVar11 = __allmul(local_30,local_2c,local_14,iVar7);
          uVar10 = CONCAT44(local_20,local_1c);
          uVar1 = lVar11 + (ulonglong)local_18;
        }
        else {
          local_c = local_c | 0xc;
        }
        bVar4 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        _local_10 = CONCAT31(uStack_f,bVar4);
        param_2 = pbVar9;
      }
      c_string_character_source<char>::unget
                ((c_string_character_source<char> *)&param_2,(char)_local_10);
      uVar8 = local_14;
      if ((local_c & 8) == 0) {
        param_2 = local_34;
        uVar8 = 0;
        iVar7 = 0;
      }
      else {
        bVar2 = is_overflow_condition<unsigned___int64>(local_c,CONCAT44(iVar12,iVar7));
        if (bVar2) {
          piVar3 = __errno();
          *piVar3 = 0x22;
          if ((local_c & 1) == 0) {
            uVar8 = 0xffffffff;
            iVar7 = -1;
          }
          else if ((local_c & 2) == 0) {
            uVar8 = 0xffffffff;
            iVar7 = 0x7fffffff;
          }
          else {
            uVar8 = 0;
            iVar7 = -0x80000000;
          }
        }
        else if ((local_c & 2) != 0) {
          bVar2 = uVar8 != 0;
          uVar8 = -uVar8;
          iVar7 = -(iVar7 + (uint)bVar2);
        }
      }
      if (local_38 != '\0') {
        *(uint *)(local_44 + 0x350) = *(uint *)(local_44 + 0x350) & 0xfffffffd;
      }
      goto LAB_00463bd8;
    }
    piVar3 = __errno();
    *piVar3 = 0x16;
    FUN_00465fa2();
  }
  uVar8 = 0;
  iVar7 = 0;
LAB_00463bd8:
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = param_2;
  }
  return CONCAT44(iVar7,uVar8);
}


