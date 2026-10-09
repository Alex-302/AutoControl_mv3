// ___scrt_initialize_onexit_tables @ 0045a4e9 size=150 callers=1

/* Library Function - Single Match
    ___scrt_initialize_onexit_tables
   
   Library: Visual Studio 2015 Release */

uint __cdecl ___scrt_initialize_onexit_tables(int param_1)

{
  byte bVar1;
  bool bVar2;
  undefined3 extraout_var;
  uint uVar3;
  int iVar4;
  
  if ((param_1 != 0) && (param_1 != 1)) {
                    /* WARNING: Subroutine does not return */
    ___scrt_fastfail();
  }
  bVar2 = ___scrt_is_ucrt_dll_in_use();
  if ((CONCAT31(extraout_var,bVar2) == 0) || (param_1 != 0)) {
    bVar1 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
    DAT_0049f140 = (0xffffffffU >> bVar1 | -1 << 0x20 - bVar1) ^ DAT_0049d070;
    uVar3 = CONCAT31((int3)(DAT_0049f140 >> 8),1);
    DAT_0049f144 = DAT_0049f140;
    DAT_0049f148 = DAT_0049f140;
    DAT_0049f14c = DAT_0049f140;
    DAT_0049f150 = DAT_0049f140;
    DAT_0049f154 = DAT_0049f140;
  }
  else {
    uVar3 = __initialize_onexit_table(&DAT_0049f140);
    if (uVar3 == 0) {
      iVar4 = __initialize_onexit_table(&DAT_0049f14c);
      uVar3 = CONCAT31((int3)((uint)-iVar4 >> 8),'\x01' - (iVar4 != 0));
    }
    else {
      uVar3 = uVar3 & 0xffffff00;
    }
  }
  return uVar3;
}


