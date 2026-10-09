// parse_floating_point_from_source<__crt_strtox::c_string_character_source<char>_> @ 004600f6 size=1010 callers=1

/* Library Function - Single Match
    enum __crt_strtox::floating_point_parse_result __cdecl
   __crt_strtox::parse_floating_point_from_source<class
   __crt_strtox::c_string_character_source<char> >(struct __crt_locale_pointers * const,class
   __crt_strtox::c_string_character_source<char> &,struct __crt_strtox::floating_point_string &)
   
   Library: Visual Studio 2015 Release */

floating_point_parse_result __cdecl
__crt_strtox::parse_floating_point_from_source<__crt_strtox::c_string_character_source<char>_>
          (__crt_locale_pointers *param_1,c_string_character_source<char> *param_2,
          floating_point_string *param_3)

{
  undefined1 uVar1;
  byte *pbVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  uint uVar8;
  floating_point_parse_result fVar9;
  byte bVar10;
  uint uVar11;
  int iVar12;
  floating_point_string *pfVar13;
  char cVar14;
  c_string_character_source<char> *local_28;
  byte *local_24;
  byte **local_20;
  floating_point_string *local_1c;
  floating_point_string *local_18;
  byte *local_14;
  int local_10;
  byte local_9 [4];
  char local_5;
  
  bVar4 = c_string_character_source<char>::validate(param_2);
  if (!bVar4) {
    return 7;
  }
  local_14 = *(byte **)param_2;
  bVar10 = *local_14;
  *(byte **)param_2 = local_14 + 1;
  local_24 = local_9;
  local_20 = &local_14;
  local_28 = param_2;
  while( true ) {
    local_9[0] = bVar10;
    iVar5 = __ischartype_l((uint)bVar10,8,(_locale_t)param_1);
    if (iVar5 == 0) break;
    bVar10 = **(byte **)param_2;
    *(byte **)param_2 = *(byte **)param_2 + 1;
  }
  local_18 = param_3 + 0x308;
  *local_18 = (floating_point_string)(local_9[0] == 0x2d);
  if ((local_9[0] == 0x2d) || (bVar10 = local_9[0], local_9[0] == 0x2b)) {
    bVar10 = **(byte **)param_2;
    local_9[0] = bVar10;
    *(byte **)param_2 = *(byte **)param_2 + 1;
  }
  if ((bVar10 == 0x49) || (bVar10 == 0x69)) {
    fVar9 = parse_floating_point_possible_infinity<char,__crt_strtox::c_string_character_source<char>,char_const*>
                      ((char *)local_9,param_2,(char *)local_14);
    return fVar9;
  }
  if ((bVar10 == 0x4e) || (bVar10 == 0x6e)) {
    fVar9 = parse_floating_point_possible_nan<char,__crt_strtox::c_string_character_source<char>,char_const*>
                      ((char *)local_9,param_2,(char *)local_14);
    return fVar9;
  }
  iVar5 = 0;
  local_5 = '\0';
  if (bVar10 == 0x30) {
    pbVar2 = *(byte **)param_2;
    bVar10 = *pbVar2;
    local_1c = (floating_point_string *)CONCAT31(local_1c._1_3_,bVar10);
    *(byte **)param_2 = pbVar2 + 1;
    if ((bVar10 == 0x78) || (bVar10 == 0x58)) {
      bVar10 = pbVar2[1];
      local_5 = '\x01';
      local_9[0] = bVar10;
      *(byte **)param_2 = pbVar2 + 2;
      local_14 = pbVar2;
    }
    else {
      c_string_character_source<char>::unget(param_2,bVar10);
      bVar10 = local_9[0];
    }
  }
  uVar8 = (uint)bVar10;
  local_1c = param_3 + 8;
  if (bVar10 == 0x30) {
    uVar8 = 0x100;
    do {
      cVar14 = **(char **)param_2;
      uVar8 = CONCAT31((int3)(uVar8 >> 8),cVar14);
      local_9[0] = cVar14;
      *(char **)param_2 = *(char **)param_2 + 1;
    } while (cVar14 == '0');
  }
  uVar11 = ((local_5 == '\0') - 1 & 6) + 9;
  pfVar13 = local_1c;
  while( true ) {
    cVar14 = (char)uVar8;
    if ((byte)(cVar14 - 0x30U) < 10) {
      uVar6 = (int)cVar14 - 0x30;
    }
    else if ((byte)(cVar14 + 0x9fU) < 0x1a) {
      uVar6 = (int)cVar14 - 0x57;
    }
    else if ((byte)(cVar14 + 0xbfU) < 0x1a) {
      uVar6 = (int)cVar14 - 0x37;
    }
    else {
      uVar6 = 0xffffffff;
    }
    if (uVar11 < uVar6) break;
    if (pfVar13 != local_18) {
      *pfVar13 = SUB41(uVar6,0);
      pfVar13 = pfVar13 + 1;
    }
    iVar5 = iVar5 + 1;
    local_9[0] = **(undefined1 **)param_2;
    uVar8 = (uint)CONCAT11(1,local_9[0]);
    *(undefined1 **)param_2 = *(undefined1 **)param_2 + 1;
  }
  iVar12 = 0;
  local_10 = iVar5;
  if (cVar14 == *(char *)**(undefined4 **)(*(int *)param_1 + 0x88)) {
    local_9[0] = **(char **)param_2;
    uVar8 = CONCAT31((int3)(uVar8 >> 8),local_9[0]);
    pcVar7 = *(char **)param_2 + 1;
    *(char **)param_2 = pcVar7;
    if ((pfVar13 == local_1c) && (local_9[0] == '0')) {
      uVar8 = 0x100;
      do {
        cVar14 = *pcVar7;
        uVar8 = CONCAT31((int3)(uVar8 >> 8),cVar14);
        local_10 = local_10 + -1;
        pcVar7 = pcVar7 + 1;
        local_9[0] = cVar14;
        *(char **)param_2 = pcVar7;
      } while (cVar14 == '0');
    }
    while( true ) {
      cVar14 = (char)uVar8;
      if ((byte)(cVar14 - 0x30U) < 10) {
        uVar6 = (int)cVar14 - 0x30;
      }
      else if ((byte)(cVar14 + 0x9fU) < 0x1a) {
        uVar6 = (int)cVar14 - 0x57;
      }
      else if ((byte)(cVar14 + 0xbfU) < 0x1a) {
        uVar6 = (int)cVar14 - 0x37;
      }
      else {
        uVar6 = 0xffffffff;
      }
      if (uVar11 < uVar6) break;
      if (pfVar13 != local_18) {
        *pfVar13 = SUB41(uVar6,0);
        pfVar13 = pfVar13 + 1;
      }
      uVar1 = **(undefined1 **)param_2;
      uVar8 = (uint)CONCAT11(1,uVar1);
      local_9[0] = uVar1;
      *(undefined1 **)param_2 = *(undefined1 **)param_2 + 1;
    }
  }
  if ((char)(uVar8 >> 8) == '\0') {
    bVar4 = <lambda_3a2f1c4b88a94fdfdc7bccff06592946>::operator()
                      ((<lambda_3a2f1c4b88a94fdfdc7bccff06592946> *)&local_28);
    if (!bVar4) {
      return 7;
    }
    return ((local_5 == '\0') - 1 & 0xfffffffb) + 7;
  }
  c_string_character_source<char>::unget(param_2,local_9[0]);
  local_14 = *(byte **)param_2;
  bVar10 = *local_14;
  *(byte **)param_2 = local_14 + 1;
  if (bVar10 == 0x45) {
LAB_00460345:
    cVar14 = local_5 == '\0';
  }
  else {
    if (bVar10 != 0x50) {
      if (bVar10 == 0x65) goto LAB_00460345;
      cVar14 = '\0';
      if (bVar10 != 0x70) goto LAB_0046034c;
    }
    cVar14 = local_5;
  }
LAB_0046034c:
  local_9[0] = bVar10;
  if (cVar14 != '\0') {
    local_9[0] = local_14[1];
    bVar4 = local_9[0] == 0x2d;
    *(byte **)param_2 = local_14 + 2;
    if ((local_9[0] == 0x2b) || (local_9[0] == 0x2d)) {
      local_9[0] = local_14[2];
      *(byte **)param_2 = local_14 + 3;
    }
    bVar3 = false;
    if (local_9[0] == 0x30) {
      bVar3 = true;
      do {
        local_9[0] = **(byte **)param_2;
        *(byte **)param_2 = *(byte **)param_2 + 1;
      } while (local_9[0] == 0x30);
    }
    while( true ) {
      if ((byte)(local_9[0] - 0x30) < 10) {
        uVar8 = (int)(char)local_9[0] - 0x30;
      }
      else if ((byte)(local_9[0] + 0x9f) < 0x1a) {
        uVar8 = (int)(char)local_9[0] - 0x57;
      }
      else if ((byte)(local_9[0] + 0xbf) < 0x1a) {
        uVar8 = (int)(char)local_9[0] - 0x37;
      }
      else {
        uVar8 = 0xffffffff;
      }
      if (9 < uVar8) goto LAB_004603e6;
      bVar3 = true;
      iVar12 = iVar12 * 10 + uVar8;
      if (0x1450 < iVar12) break;
      local_9[0] = **(byte **)param_2;
      *(byte **)param_2 = *(byte **)param_2 + 1;
    }
    iVar12 = 0x1451;
LAB_004603e6:
    while( true ) {
      if ((byte)(local_9[0] - 0x30) < 10) {
        uVar8 = (int)(char)local_9[0] - 0x30;
      }
      else if ((byte)(local_9[0] + 0x9f) < 0x1a) {
        uVar8 = (int)(char)local_9[0] - 0x57;
      }
      else if ((byte)(local_9[0] + 0xbf) < 0x1a) {
        uVar8 = (int)(char)local_9[0] - 0x37;
      }
      else {
        uVar8 = 0xffffffff;
      }
      if (9 < uVar8) break;
      local_9[0] = **(byte **)param_2;
      *(byte **)param_2 = *(byte **)param_2 + 1;
    }
    if (bVar4) {
      iVar12 = -iVar12;
    }
    if (!bVar3) {
      bVar4 = <lambda_3a2f1c4b88a94fdfdc7bccff06592946>::operator()
                        ((<lambda_3a2f1c4b88a94fdfdc7bccff06592946> *)&local_28);
      if (!bVar4) {
        return 7;
      }
      local_9[0] = **(byte **)param_2;
      *(byte **)param_2 = *(byte **)param_2 + 1;
    }
  }
  c_string_character_source<char>::unget(param_2,local_9[0]);
  if (pfVar13 != local_1c) {
    do {
      if (pfVar13[-1] != (floating_point_string)0x0) break;
      pfVar13 = pfVar13 + -1;
    } while (pfVar13 != local_1c);
    if (pfVar13 != local_1c) {
      if (0x1450 < iVar12) {
        return 9;
      }
      if (-0x1451 < iVar12) {
        iVar12 = iVar12 + (((local_5 == '\0') - 1 & 3) + 1) * local_10;
        if (0x1450 < iVar12) {
          return 9;
        }
        if (-0x1451 < iVar12) {
          *(int *)param_3 = iVar12;
          *(int *)(param_3 + 4) = (int)pfVar13 - (int)local_1c;
          return (uint)(local_5 != '\0');
        }
      }
      return 8;
    }
  }
  return 2;
}


