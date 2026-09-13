// ___isa_available_init @ 0045ac7b size=410 callers=1

/* WARNING: Removing unreachable block (ram,0x0045acbc) */
/* WARNING: Removing unreachable block (ram,0x0045ad6c) */
/* WARNING: Removing unreachable block (ram,0x0045acf6) */
/* Library Function - Single Match
    ___isa_available_init
   
   Library: Visual Studio 2015 Release */

undefined4 ___isa_available_init(void)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  undefined8 uVar4;
  uint uVar5;
  BOOL BVar6;
  uint uVar7;
  uint uVar8;
  uint in_XCR0;
  uint local_14;
  uint local_10;
  
  DAT_0049f178 = 0;
  DAT_0049d0a0 = DAT_0049d0a0 | 1;
  BVar6 = IsProcessorFeaturePresent(10);
  uVar5 = DAT_0049d0a0;
  if (BVar6 != 0) {
    local_14 = 0;
    DAT_0049d0a0 = DAT_0049d0a0 | 2;
    DAT_0049f178 = 1;
    piVar1 = (int *)cpuid_basic_info(0);
    puVar2 = (uint *)cpuid_Version_info(1);
    uVar8 = puVar2[3];
    if (((piVar1[2] == 0x49656e69 && piVar1[3] == 0x6c65746e) && piVar1[1] == 0x756e6547) &&
       (((((uVar7 = *puVar2 & 0xfff3ff0, uVar7 == 0x106c0 || (uVar7 == 0x20660)) ||
          (uVar7 == 0x20670)) || ((uVar7 == 0x30650 || (uVar7 == 0x30660)))) || (uVar7 == 0x30670)))
       ) {
      DAT_0049f17c = DAT_0049f17c | 1;
    }
    if (6 < *piVar1) {
      iVar3 = cpuid_Extended_Feature_Enumeration_info(7);
      local_14 = *(uint *)(iVar3 + 4);
      if ((local_14 & 0x200) != 0) {
        DAT_0049f17c = DAT_0049f17c | 2;
      }
    }
    if ((uVar8 & 0x100000) != 0) {
      DAT_0049d0a0 = uVar5 | 6;
      DAT_0049f178 = 2;
      if (((uVar8 & 0x8000000) != 0) && ((uVar8 & 0x10000000) != 0)) {
        uVar4 = xinuse(0);
        local_10 = in_XCR0 & (uint)uVar4;
        if ((local_10 & 6) == 6) {
          DAT_0049d0a0 = uVar5 | 0xe;
          DAT_0049f178 = 3;
          if ((local_14 & 0x20) != 0) {
            DAT_0049d0a0 = uVar5 | 0x2e;
            DAT_0049f178 = 5;
          }
        }
      }
    }
  }
  return 0;
}


