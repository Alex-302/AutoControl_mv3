// __seh_filter_exe @ 0046715c size=371 callers=0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __seh_filter_exe
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl __seh_filter_exe(uint param_1,undefined4 param_2)

{
  uint *puVar1;
  code *pcVar2;
  undefined4 uVar3;
  __acrt_ptd *p_Var4;
  undefined4 uVar5;
  uint *puVar6;
  uint *puVar7;
  
  p_Var4 = ___acrt_getptd_noexit();
  uVar5 = 0;
  if (p_Var4 != (__acrt_ptd *)0x0) {
    puVar1 = *(uint **)p_Var4;
    for (puVar7 = puVar1; puVar7 != puVar1 + 0x24; puVar7 = puVar7 + 3) {
      if (*puVar7 == param_1) goto LAB_0046719f;
    }
    puVar7 = (uint *)0x0;
LAB_0046719f:
    if ((puVar7 == (uint *)0x0) || (pcVar2 = (code *)puVar7[2], pcVar2 == (code *)0x0)) {
      uVar5 = 0;
    }
    else if (pcVar2 == (code *)0x5) {
      puVar7[2] = 0;
      uVar5 = 1;
    }
    else {
      if (pcVar2 != (code *)0x1) {
        uVar5 = *(undefined4 *)(p_Var4 + 4);
        *(undefined4 *)(p_Var4 + 4) = param_2;
        if (puVar7[1] == 8) {
          for (puVar6 = puVar1 + 9; puVar6 != puVar1 + 0x24; puVar6 = puVar6 + 3) {
            puVar6[2] = 0;
          }
          uVar3 = *(undefined4 *)(p_Var4 + 8);
          if (*puVar7 < 0xc0000092) {
            if (*puVar7 == 0xc0000091) {
              *(undefined4 *)(p_Var4 + 8) = 0x84;
            }
            else if (*puVar7 == 0xc000008d) {
              *(undefined4 *)(p_Var4 + 8) = 0x82;
            }
            else if (*puVar7 == 0xc000008e) {
              *(undefined4 *)(p_Var4 + 8) = 0x83;
            }
            else if (*puVar7 == 0xc000008f) {
              *(undefined4 *)(p_Var4 + 8) = 0x86;
            }
            else if (*puVar7 == 0xc0000090) {
              *(undefined4 *)(p_Var4 + 8) = 0x81;
            }
          }
          else if (*puVar7 == 0xc0000092) {
            *(undefined4 *)(p_Var4 + 8) = 0x8a;
          }
          else if (*puVar7 == 0xc0000093) {
            *(undefined4 *)(p_Var4 + 8) = 0x85;
          }
          else if (*puVar7 == 0xc00002b4) {
            *(undefined4 *)(p_Var4 + 8) = 0x8e;
          }
          else if (*puVar7 == 0xc00002b5) {
            *(undefined4 *)(p_Var4 + 8) = 0x8d;
          }
          (*(code *)PTR_guard_check_icall_004805b0)(8,*(undefined4 *)(p_Var4 + 8));
          (*pcVar2)();
          *(undefined4 *)(p_Var4 + 8) = uVar3;
        }
        else {
          puVar7[2] = 0;
          (*(code *)PTR_guard_check_icall_004805b0)(puVar7[1]);
          (*pcVar2)();
        }
        *(undefined4 *)(p_Var4 + 4) = uVar5;
      }
      uVar5 = 0xffffffff;
    }
  }
  return uVar5;
}


