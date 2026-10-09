// ___FrameUnwindFilter @ 0045c496 size=69 callers=0

/* Library Function - Single Match
    ___FrameUnwindFilter
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

undefined4 __cdecl ___FrameUnwindFilter(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  if ((*piVar1 == -0x1fbcbcae) || (*piVar1 == -0x1fbcb0b3)) {
    iVar2 = ___vcrt_getptd();
    if (0 < *(int *)(iVar2 + 0x18)) {
      iVar2 = ___vcrt_getptd();
      *(int *)(iVar2 + 0x18) = *(int *)(iVar2 + 0x18) + -1;
    }
  }
  else if (*piVar1 == -0x1f928c9d) {
    iVar2 = ___vcrt_getptd();
    *(undefined4 *)(iVar2 + 0x18) = 0;
                    /* WARNING: Subroutine does not return */
    FUN_00464131();
  }
  return 0;
}


