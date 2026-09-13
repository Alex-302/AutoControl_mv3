// FUN_004015d0 @ 004015d0 size=73 callers=1

void FUN_004015d0(void)

{
  undefined8 uVar1;
  _FILETIME local_8;
  
  GetSystemTimeAsFileTime(&local_8);
  uVar1 = __alldiv(local_8.dwLowDateTime,local_8.dwHighDateTime,10000,0);
  uVar1 = __alldiv((uint)uVar1 + 0xcf499800,
                   ((int)((ulonglong)uVar1 >> 0x20) + -0xa97) - (uint)((uint)uVar1 < 0x30b66800),
                   86400000,0);
  DAT_004a255c = (int)uVar1;
  return;
}


