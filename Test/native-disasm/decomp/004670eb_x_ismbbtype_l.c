// x_ismbbtype_l @ 004670eb size=89 callers=1

/* Library Function - Single Match
    int __cdecl x_ismbbtype_l(struct __crt_locale_pointers *,unsigned int,int,int)
   
   Libraries: Visual Studio 2015 Debug, Visual Studio 2015 Release, Visual Studio 2017 Debug, Visual
   Studio 2017 Release */

int __cdecl x_ismbbtype_l(__crt_locale_pointers *param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int local_14;
  int *local_10;
  int local_c;
  char local_8;
  
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,param_1);
  if ((*(byte *)(local_c + 0x19 + (param_2 & 0xff)) & (byte)param_4) == 0) {
    iVar2 = 0;
    if (param_3 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = (uint)*(ushort *)(*local_10 + (param_2 & 0xff) * 2) & param_3;
    }
    if (uVar1 == 0) goto LAB_0046712d;
  }
  iVar2 = 1;
LAB_0046712d:
  if (local_8 != '\0') {
    *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
  }
  return iVar2;
}


