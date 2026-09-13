// ___acrt_LCMapStringW @ 0046e08f size=62 callers=2

/* Library Function - Single Match
    ___acrt_LCMapStringW
   
   Library: Visual Studio 2015 Release */

void __cdecl
___acrt_LCMapStringW
          (wchar_t *param_1,DWORD param_2,LPCWSTR param_3,uint param_4,LPWSTR param_5,int param_6)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_4;
  if (0 < (int)param_4) {
    uVar1 = FUN_00466f34(param_3,param_4);
    uVar2 = uVar1 + 1;
    if ((int)param_4 <= (int)uVar1) {
      uVar2 = uVar1;
    }
  }
  ___acrt_LCMapStringEx_36(param_1,param_2,param_3,uVar2,param_5,param_6,0,0,0);
  return;
}


