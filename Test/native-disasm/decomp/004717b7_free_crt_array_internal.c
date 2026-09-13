// free_crt_array_internal @ 004717b7 size=60 callers=10

/* Library Function - Single Match
    void __cdecl free_crt_array_internal(void const * * const,unsigned int)
   
   Library: Visual Studio 2015 Release */

void __cdecl free_crt_array_internal(void **param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  uVar1 = ~-(uint)(param_1 + param_2 < param_1) &
          (uint)((int)(param_1 + param_2) + (3 - (int)param_1)) >> 2;
  if (uVar1 != 0) {
    do {
      FID_conflict__free(*param_1);
      uVar2 = uVar2 + 1;
      param_1 = param_1 + 1;
    } while (uVar2 != uVar1);
  }
  return;
}


