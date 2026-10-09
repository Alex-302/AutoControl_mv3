// ___report_securityfailure @ 0045af50 size=204 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    ___report_securityfailure
   
   Library: Visual Studio 2015 Release */

void __cdecl ___report_securityfailure(undefined4 param_1)

{
  code *pcVar1;
  uint uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar3;
  uint extraout_EDX;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined2 in_ES;
  undefined2 in_CS;
  undefined2 in_SS;
  undefined2 in_DS;
  undefined2 in_FS;
  undefined2 in_GS;
  byte bVar4;
  byte bVar5;
  byte in_AF;
  byte bVar6;
  byte bVar7;
  byte in_TF;
  byte in_IF;
  byte bVar8;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  longlong lVar9;
  undefined4 unaff_retaddr;
  
  uVar2 = IsProcessorFeaturePresent(0x17);
  bVar4 = 0;
  bVar8 = 0;
  bVar7 = (int)uVar2 < 0;
  bVar6 = uVar2 == 0;
  bVar5 = (POPCOUNT(uVar2 & 0xff) & 1U) == 0;
  lVar9 = (ulonglong)extraout_EDX << 0x20;
  uVar3 = extraout_ECX;
  if (!(bool)bVar6) {
    pcVar1 = (code *)swi(0x29);
    lVar9 = (*pcVar1)();
    uVar3 = extraout_ECX_00;
  }
  _DAT_0049f278 = (undefined4)((ulonglong)lVar9 >> 0x20);
  _DAT_0049f280 = (undefined4)lVar9;
  _DAT_0049f290 =
       (uint)(in_NT & 1) * 0x4000 | (uint)(bVar8 & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
       (uint)(in_TF & 1) * 0x100 | (uint)(bVar7 & 1) * 0x80 | (uint)(bVar6 & 1) * 0x40 |
       (uint)(in_AF & 1) * 0x10 | (uint)(bVar5 & 1) * 4 | (uint)(bVar4 & 1) |
       (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 | (uint)(in_VIF & 1) * 0x80000 |
       (uint)(in_AC & 1) * 0x40000;
  _DAT_0049f294 = &param_1;
  _DAT_0049f180 = 0xc0000409;
  _DAT_0049f184 = 1;
  _DAT_0049f190 = 1;
  DAT_0049f194 = param_1;
  _DAT_0049f18c = unaff_retaddr;
  _DAT_0049f25c = in_GS;
  _DAT_0049f260 = in_FS;
  _DAT_0049f264 = in_ES;
  _DAT_0049f268 = in_DS;
  _DAT_0049f26c = unaff_EDI;
  _DAT_0049f270 = unaff_ESI;
  _DAT_0049f274 = unaff_EBX;
  _DAT_0049f27c = uVar3;
  _DAT_0049f284 = unaff_EBP;
  DAT_0049f288 = unaff_retaddr;
  _DAT_0049f28c = in_CS;
  _DAT_0049f298 = in_SS;
                    /* WARNING: Subroutine does not return */
  ___raise_securityfailure((_EXCEPTION_POINTERS *)&PTR_DAT_00483db8);
}


