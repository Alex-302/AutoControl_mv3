// __setmbcp_nolock @ 00470a82 size=497 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __setmbcp_nolock
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl __setmbcp_nolock(int param_1,__crt_multibyte_data *param_2)

{
  byte bVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  BOOL BVar5;
  BYTE *pBVar6;
  __crt_multibyte_data *p_Var7;
  wchar_t *pwVar8;
  byte *pbVar9;
  undefined4 uVar10;
  int iVar11;
  byte *pbVar12;
  undefined2 *puVar13;
  uint uVar14;
  int local_20;
  _cpinfo local_1c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  uVar3 = getSystemCP(param_1);
  if (uVar3 == 0) {
    setSBCS(param_2);
    return 0;
  }
  uVar14 = 0;
  uVar4 = 0;
  local_20 = 0;
LAB_00470ac0:
  if (*(uint *)((int)&DAT_0049d490 + uVar4) != uVar3) goto code_r0x00470acc;
  _memset(param_2 + 0x18,0,0x101);
  pbVar9 = (byte *)(local_20 * 0x30 + 0x49d4a0);
  do {
    bVar1 = *pbVar9;
    pbVar12 = pbVar9;
    while ((bVar1 != 0 && (bVar1 = pbVar12[1], bVar1 != 0))) {
      for (uVar4 = (uint)*pbVar12; (uVar4 <= bVar1 && (uVar4 < 0x100)); uVar4 = uVar4 + 1) {
        param_2[uVar4 + 0x19] =
             (__crt_multibyte_data)((byte)param_2[uVar4 + 0x19] | (&DAT_0049d488)[uVar14]);
        bVar1 = pbVar12[1];
      }
      pbVar12 = pbVar12 + 2;
      bVar1 = *pbVar12;
    }
    uVar14 = uVar14 + 1;
    pbVar9 = pbVar9 + 8;
  } while (uVar14 < 4);
  *(uint *)(param_2 + 4) = uVar3;
  *(undefined4 *)(param_2 + 8) = 1;
  pwVar8 = CPtoLocaleName(uVar3);
  *(wchar_t **)(param_2 + 0x21c) = pwVar8;
  p_Var7 = param_2 + 0xc;
  puVar13 = (undefined2 *)(local_20 * 0x30 + 0x49d494);
  iVar11 = 6;
  do {
    uVar2 = *puVar13;
    puVar13 = puVar13 + 1;
    *(undefined2 *)p_Var7 = uVar2;
    p_Var7 = p_Var7 + 2;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  goto LAB_00470c59;
code_r0x00470acc:
  local_20 = local_20 + 1;
  uVar4 = uVar4 + 0x30;
  if (0xef < uVar4) goto code_r0x00470ada;
  goto LAB_00470ac0;
code_r0x00470ada:
  if (((uVar3 == 65000) || (uVar3 == 0xfde9)) ||
     (BVar5 = IsValidCodePage(uVar3 & 0xffff), BVar5 == 0)) {
LAB_00470bae:
    uVar10 = 0xffffffff;
  }
  else {
    BVar5 = GetCPInfo(uVar3,&local_1c);
    if (BVar5 == 0) {
      if (DAT_0049fc04 == 0) goto LAB_00470bae;
      setSBCS(param_2);
    }
    else {
      _memset(param_2 + 0x18,0,0x101);
      *(uint *)(param_2 + 4) = uVar3;
      *(undefined4 *)(param_2 + 0x21c) = 0;
      if (local_1c.MaxCharSize < 2) {
        *(undefined4 *)(param_2 + 8) = 0;
      }
      else {
        pBVar6 = local_1c.LeadByte;
        while ((local_1c.LeadByte[0] != 0 && (bVar1 = pBVar6[1], bVar1 != 0))) {
          for (uVar3 = (uint)*pBVar6; uVar3 <= bVar1; uVar3 = uVar3 + 1) {
            param_2[uVar3 + 0x19] = (__crt_multibyte_data)((byte)param_2[uVar3 + 0x19] | 4);
          }
          pBVar6 = pBVar6 + 2;
          local_1c.LeadByte[0] = *pBVar6;
        }
        p_Var7 = param_2 + 0x1a;
        iVar11 = 0xfe;
        do {
          *p_Var7 = (__crt_multibyte_data)((byte)*p_Var7 | 8);
          p_Var7 = p_Var7 + 1;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
        pwVar8 = CPtoLocaleName(*(int *)(param_2 + 4));
        *(wchar_t **)(param_2 + 0x21c) = pwVar8;
        *(undefined4 *)(param_2 + 8) = 1;
      }
      *(undefined4 *)(param_2 + 0xc) = 0;
      *(undefined4 *)(param_2 + 0x10) = 0;
      *(undefined4 *)(param_2 + 0x14) = 0;
LAB_00470c59:
      setSBUpLow(param_2);
    }
    uVar10 = 0;
  }
  return uVar10;
}


