// roundf @ 004631bb size=82 callers=50

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _roundf
   
   Library: Visual Studio 2015 Release */

float10 __cdecl roundf(float param_1)

{
  int iVar1;
  
  iVar1 = __fd_int((ushort *)&param_1,1);
  if ((((short)iVar1 < 1) || (2 < (short)iVar1)) &&
     (iVar1 = __fd_int((ushort *)&param_1,0), (short)iVar1 != 0)) {
    if (((uint)param_1 & 0x80000000) == 0) {
      param_1 = param_1 + (float)_DAT_004851a8;
    }
    else {
      param_1 = param_1 - (float)_DAT_004851a8;
    }
  }
  return (float10)param_1;
}


