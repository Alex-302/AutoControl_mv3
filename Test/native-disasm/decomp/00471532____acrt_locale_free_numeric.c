// ___acrt_locale_free_numeric @ 00471532 size=105 callers=2

/* Library Function - Single Match
    ___acrt_locale_free_numeric
   
   Library: Visual Studio 2015 Release */

void __cdecl ___acrt_locale_free_numeric(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    if ((undefined *)*param_1 != PTR_DAT_0049d180) {
      FID_conflict__free((undefined *)*param_1);
    }
    if ((undefined *)param_1[1] != PTR_DAT_0049d184) {
      FID_conflict__free((undefined *)param_1[1]);
    }
    if ((undefined *)param_1[2] != PTR_DAT_0049d188) {
      FID_conflict__free((undefined *)param_1[2]);
    }
    if ((undefined *)param_1[0xc] != PTR_DAT_0049d1b0) {
      FID_conflict__free((undefined *)param_1[0xc]);
    }
    if ((undefined *)param_1[0xd] != PTR_DAT_0049d1b4) {
      FID_conflict__free((undefined *)param_1[0xd]);
    }
  }
  return;
}


