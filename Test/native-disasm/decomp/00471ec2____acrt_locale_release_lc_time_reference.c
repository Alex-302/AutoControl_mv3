// ___acrt_locale_release_lc_time_reference @ 00471ec2 size=41 callers=2

/* Library Function - Single Match
    ___acrt_locale_release_lc_time_reference
   
   Library: Visual Studio 2015 Release */

undefined * __cdecl ___acrt_locale_release_lc_time_reference(undefined **param_1)

{
  undefined **ppuVar1;
  undefined *puVar2;
  
  if ((param_1 != (undefined **)0x0) && (param_1 != &PTR_DAT_00486728)) {
    LOCK();
    ppuVar1 = param_1 + 0x2c;
    puVar2 = *ppuVar1;
    *ppuVar1 = *ppuVar1 + -1;
    UNLOCK();
    return puVar2 + -1;
  }
  return (undefined *)0x7fffffff;
}


