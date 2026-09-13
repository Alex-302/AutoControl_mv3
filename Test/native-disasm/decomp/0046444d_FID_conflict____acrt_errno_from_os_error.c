// FID_conflict:___acrt_errno_from_os_error @ 0046444d size=67 callers=2

/* Library Function - Multiple Matches With Different Base Names
    ___acrt_errno_from_os_error
    __get_errno_from_oserr
   
   Libraries: Visual Studio 2012 Release, Visual Studio 2015 Release, Visual Studio 2017 Release,
   Visual Studio 2019 Release */

int __cdecl FID_conflict____acrt_errno_from_os_error(ulong param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if (param_1 == (&DAT_004851b0)[uVar1 * 2]) {
      return *(int *)(&UNK_004851b4 + uVar1 * 8);
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x2d);
  if (param_1 - 0x13 < 0x12) {
    return 0xd;
  }
  return (-(uint)(0xe < param_1 - 0xbc) & 0xe) + 8;
}


