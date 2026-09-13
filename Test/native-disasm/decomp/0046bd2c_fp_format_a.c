// fp_format_a @ 0046bd2c size=771 callers=1

/* Library Function - Single Match
    int __cdecl fp_format_a(double const * const,char *,unsigned int,char * const,unsigned
   int,int,bool,unsigned int,struct __crt_locale_pointers * const)
   
   Library: Visual Studio 2015 Release */

int __cdecl
fp_format_a(double *param_1,char *param_2,uint param_3,char *param_4,uint param_5,int param_6,
           bool param_7,uint param_8,__crt_locale_pointers *param_9)

{
  int *piVar1;
  int iVar2;
  undefined1 (*pauVar3) [16];
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  char *_Dst;
  char *pcVar7;
  bool bVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  int local_34;
  int local_30;
  char local_28;
  undefined4 local_24;
  int local_20;
  char *local_1c;
  uint local_14;
  uint local_10;
  int local_c;
  uint local_8;
  
  if (param_6 < 0) {
    param_6 = 0;
  }
  *param_2 = '\0';
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_34,param_9);
  if (param_3 <= param_6 + 0xbU) {
    piVar1 = __errno();
    iVar2 = 0x22;
    *piVar1 = 0x22;
    FUN_00465fa2();
    goto LAB_0046c016;
  }
  local_24 = *(undefined4 *)param_1;
  if ((*(uint *)((int)param_1 + 4) >> 0x14 & 0x7ff) == 0x7ff) {
    iVar2 = fp_format_e(param_1,param_2,param_3,param_4,param_5,param_6,false,param_8,
                        (__crt_locale_pointers *)0x0);
    if (iVar2 == 0) {
      pauVar3 = FUN_00477950((undefined1 (*) [16])param_2,0x65);
      if (pauVar3 != (undefined1 (*) [16])0x0) {
        (*pauVar3)[0] = (!param_7 - 1U & 0xe0) + 0x70;
        (*pauVar3)[3] = 0;
      }
      iVar2 = 0;
    }
    else {
      *param_2 = '\0';
    }
    goto LAB_0046c016;
  }
  if ((*(uint *)((int)param_1 + 4) & 0x80000000) != 0) {
    *param_2 = '-';
    param_2 = param_2 + 1;
  }
  local_10 = 0x3ff;
  iVar2 = (!param_7 - 1 & 0xffffffe0) + 0x27;
  if (((ulonglong)*param_1 & 0x7ff0000000000000) == 0) {
    *param_2 = '0';
    if (*(int *)param_1 == 0 && ((ulonglong)*param_1 & 0xfffff00000000) == 0) {
      local_10 = 0;
    }
    else {
      local_10 = 0x3fe;
    }
  }
  else {
    *param_2 = '1';
  }
  local_1c = param_2 + 1;
  _Dst = param_2 + 2;
  if (param_6 == 0) {
    *local_1c = '\0';
  }
  else {
    *local_1c = *(char *)**(undefined4 **)(local_30 + 0x88);
  }
  local_20 = iVar2;
  if ((((ulonglong)*param_1 & 0xfffff00000000) != 0) || (local_14 = 0, *(int *)param_1 != 0)) {
    local_8 = 0;
    local_c = 0x30;
    local_14 = 0xf0000;
    do {
      if (param_6 < 1) break;
      uVar9 = __aullshr((byte)local_c,*(uint *)((int)param_1 + 4) & local_14 & 0xfffff);
      uVar4 = (uint)(ushort)((short)uVar9 + 0x30);
      if (0x39 < uVar4) {
        uVar4 = uVar4 + iVar2;
      }
      *_Dst = (char)uVar4;
      _Dst = _Dst + 1;
      local_8 = local_8 >> 4 | local_14 << 0x1c;
      local_14 = local_14 >> 4;
      local_c = local_c + -4;
      param_6 = param_6 - 1;
    } while (-1 < (short)local_c);
    if ((-1 < (short)local_c) &&
       (uVar9 = __aullshr((byte)local_c,*(uint *)((int)param_1 + 4) & local_14 & 0xfffff),
       pcVar7 = _Dst, 8 < (ushort)uVar9)) {
      while( true ) {
        pcVar5 = pcVar7 + -1;
        if ((*pcVar5 != 'f') && (*pcVar5 != 'F')) break;
        *pcVar5 = '0';
        pcVar7 = pcVar5;
      }
      if (pcVar5 == local_1c) {
        pcVar7[-2] = pcVar7[-2] + '\x01';
      }
      else if (*pcVar5 == '9') {
        *pcVar5 = (char)local_20 + ':';
      }
      else {
        *pcVar5 = *pcVar5 + '\x01';
      }
    }
  }
  if (0 < param_6) {
    _memset(_Dst,0x30,param_6);
    _Dst = _Dst + param_6;
  }
  if (*local_1c == '\0') {
    _Dst = local_1c;
  }
  *_Dst = (!param_7 - 1U & 0xe0) + 0x70;
  uVar9 = __aullshr(0x34,*(uint *)((int)param_1 + 4));
  uVar4 = (uint)uVar9 & 0x7ff;
  uVar6 = uVar4 - local_10;
  uVar4 = -(uint)(uVar4 < local_10);
  if ((int)uVar4 < 0) {
    _Dst[1] = '-';
    bVar8 = uVar6 != 0;
    uVar6 = -uVar6;
    uVar4 = -(uVar4 + bVar8);
  }
  else {
    _Dst[1] = '+';
  }
  pcVar5 = _Dst + 2;
  *pcVar5 = '0';
  pcVar7 = pcVar5;
  if (-1 < (int)uVar4) {
    if (((int)uVar4 < 1) && (uVar6 < 1000)) {
LAB_0046bfc9:
      if (((int)uVar4 < 0) || (((int)uVar4 < 1 && (uVar6 < 100)))) goto LAB_0046bfe7;
    }
    else {
      uVar10 = __alldvrm(uVar6,uVar4,1000,0);
      local_20 = (int)((ulonglong)uVar10 >> 0x20);
      *pcVar5 = (char)uVar10 + '0';
      pcVar7 = _Dst + 3;
      uVar6 = extraout_ECX;
      if (pcVar7 == pcVar5) goto LAB_0046bfc9;
    }
    uVar10 = __alldvrm(uVar6,uVar4,100,0);
    local_20 = (int)((ulonglong)uVar10 >> 0x20);
    *pcVar7 = (char)uVar10 + '0';
    pcVar7 = pcVar7 + 1;
    uVar6 = extraout_ECX_00;
  }
LAB_0046bfe7:
  if ((pcVar7 != pcVar5) || ((-1 < (int)uVar4 && ((0 < (int)uVar4 || (9 < uVar6)))))) {
    uVar10 = __alldvrm(uVar6,uVar4,10,0);
    *pcVar7 = (char)uVar10 + '0';
    pcVar7 = pcVar7 + 1;
    uVar6 = extraout_ECX_01;
  }
  iVar2 = 0;
  *pcVar7 = (char)uVar6 + '0';
  pcVar7[1] = '\0';
LAB_0046c016:
  if (local_28 != '\0') {
    *(uint *)(local_34 + 0x350) = *(uint *)(local_34 + 0x350) & 0xfffffffd;
  }
  return iVar2;
}


