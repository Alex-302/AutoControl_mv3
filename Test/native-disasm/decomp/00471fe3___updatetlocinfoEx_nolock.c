// __updatetlocinfoEx_nolock @ 00471fe3 size=80 callers=4

/* Library Function - Single Match
    __updatetlocinfoEx_nolock
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

undefined ** __cdecl __updatetlocinfoEx_nolock(undefined4 *param_1,undefined **param_2)

{
  undefined **ppuVar1;
  
  if ((param_2 == (undefined **)0x0) || (param_1 == (undefined4 *)0x0)) {
    param_2 = (undefined **)0x0;
  }
  else {
    ppuVar1 = (undefined **)*param_1;
    if (ppuVar1 != param_2) {
      *param_1 = param_2;
      ___acrt_add_locale_ref((int)param_2);
      if (((ppuVar1 != (undefined **)0x0) &&
          (___acrt_release_locale_ref((int)ppuVar1), ppuVar1[3] == (undefined *)0x0)) &&
         (ppuVar1 != &PTR_DAT_0049d230)) {
        ___acrt_free_locale(ppuVar1);
      }
    }
  }
  return param_2;
}


