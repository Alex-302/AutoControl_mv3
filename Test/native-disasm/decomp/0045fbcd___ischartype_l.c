// __ischartype_l @ 0045fbcd size=51 callers=8

/* Library Function - Single Match
    __ischartype_l
   
   Library: Visual Studio 2015 Release */

void __cdecl __ischartype_l(int param_1,int param_2,_locale_t param_3)

{
  if ((param_3 == (_locale_t)0x0) || ((int)param_3->locinfo->lc_codepage < 2)) {
    __chvalidchk_l(param_1,(ushort)param_2,&param_3->locinfo);
  }
  else {
    __isctype_l(param_1,param_2,param_3);
  }
  return;
}


