// FUN_00402430 @ 00402430 size=90 callers=514

void __cdecl FUN_00402430(void *param_1,uint param_2,uint param_3)

{
  void *pvVar1;
  uint uVar2;
  
  if ((uint)(0xffffffff / (ulonglong)param_3) < param_2) {
code_r0x00465fb2:
    FUN_00465f27((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
                    /* WARNING: Subroutine does not return */
    __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
  }
  if (0xfff < param_2 * param_3) {
    if (((((uint)param_1 & 0x1f) != 0) ||
        (pvVar1 = *(void **)((int)param_1 + -4), param_1 <= pvVar1)) ||
       (uVar2 = (int)param_1 - (int)pvVar1, uVar2 < 4)) goto code_r0x00465fb2;
    param_1 = pvVar1;
    if (0x23 < uVar2) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
  }
  FID_conflict__free(param_1);
  return;
}


