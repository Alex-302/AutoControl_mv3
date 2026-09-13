// __query_new_handler @ 00468e70 size=70 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __query_new_handler
   
   Library: Visual Studio 2015 Release */

uint __query_new_handler(void)

{
  byte bVar1;
  uint uVar2;
  
  ___acrt_lock(0);
  bVar1 = (byte)DAT_0049d070 & 0x1f;
  uVar2 = DAT_0049d070 ^ _DAT_0049f800;
  FUN_00468eb9();
  return uVar2 >> bVar1 | uVar2 << 0x20 - bVar1;
}


