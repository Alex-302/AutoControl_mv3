// FUN_00470d2d @ 00470d2d size=570 callers=1

undefined4 __cdecl FUN_00470d2d(uint *param_1,int param_2)

{
  uint uVar1;
  char *_SizeInBytes;
  int *piVar2;
  uint *puVar3;
  char **ppcVar4;
  uint uVar5;
  char *_Dst;
  errno_t eVar6;
  BOOL BVar7;
  uint *puVar8;
  undefined4 uVar9;
  uint *puVar10;
  bool bVar11;
  
  if (param_1 == (uint *)0x0) {
    piVar2 = __errno();
    *piVar2 = 0x16;
    return 0xffffffff;
  }
  puVar3 = FUN_0045c740(param_1,'=');
  puVar10 = param_1;
  if ((puVar3 == (uint *)0x0) || (puVar3 == param_1)) {
LAB_00470db0:
    piVar2 = __errno();
    *piVar2 = 0x16;
  }
  else {
    bVar11 = *(char *)((int)puVar3 + 1) == '\0';
    if (DAT_0049f7c0 == DAT_0049f7cc) {
      DAT_0049f7c0 = FUN_00470f68(DAT_0049f7c0);
    }
    uVar9 = 0;
    if (DAT_0049f7c0 == (int *)0x0) {
      if ((param_2 != 0) && (DAT_0049f7c4 != (LPVOID)0x0)) {
        ppcVar4 = common_get_or_create_environment_nolock<char>();
        if (ppcVar4 != (char **)0x0) goto LAB_00470e24;
        goto LAB_00470db0;
      }
      if (bVar11) {
        uVar9 = 0;
        goto LAB_00470dbe;
      }
      DAT_0049f7c0 = __calloc_base(1,4);
      FID_conflict__free((void *)0x0);
      if (DAT_0049f7c0 != (int *)0x0) {
        if (DAT_0049f7c4 == (LPVOID)0x0) {
          DAT_0049f7c4 = __calloc_base(1,4);
          FID_conflict__free((void *)0x0);
          if (DAT_0049f7c4 == (LPVOID)0x0) goto LAB_00470dbb;
        }
LAB_00470e24:
        if (DAT_0049f7c0 != (int *)0x0) goto LAB_00470e28;
      }
    }
    else {
LAB_00470e28:
      piVar2 = DAT_0049f7c0;
      uVar5 = find_in_environment_nolock<char>((char *)param_1,(int)puVar3 - (int)param_1);
      if ((-1 < (int)uVar5) && (*piVar2 != 0)) {
        FID_conflict__free((void *)piVar2[uVar5]);
        if (bVar11) {
          for (; piVar2[uVar5] != 0; uVar5 = uVar5 + 1) {
            piVar2[uVar5] = piVar2[uVar5 + 1];
          }
          piVar2 = FUN_00473270(piVar2,uVar5,4);
          FID_conflict__free((void *)0x0);
          if (piVar2 != (int *)0x0) {
LAB_00470ed7:
            DAT_0049f7c0 = piVar2;
          }
        }
        else {
          piVar2[uVar5] = (int)param_1;
          puVar10 = (uint *)0x0;
        }
        if (param_2 != 0) {
          puVar8 = param_1;
          do {
            uVar5 = *puVar8;
            puVar8 = (uint *)((int)puVar8 + 1);
          } while ((char)uVar5 != '\0');
          _SizeInBytes = (char *)((int)puVar8 + (2 - ((int)param_1 + 1)));
          _Dst = __calloc_base((uint)_SizeInBytes,1);
          if (_Dst != (char *)0x0) {
            eVar6 = _strcpy_s(_Dst,(rsize_t)_SizeInBytes,(char *)param_1);
            if (eVar6 != 0) {
                    /* WARNING: Subroutine does not return */
              __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
            }
            (_Dst + (int)puVar3 + (1 - (int)param_1))[-1] = '\0';
            BVar7 = SetEnvironmentVariableA
                              (_Dst,(LPCSTR)(~-(uint)bVar11 &
                                            (uint)(_Dst + (int)puVar3 + (1 - (int)param_1))));
            if (BVar7 == 0) {
              piVar2 = __errno();
              uVar9 = 0xffffffff;
              *piVar2 = 0x2a;
            }
          }
          FID_conflict__free(_Dst);
        }
        goto LAB_00470dbe;
      }
      if (bVar11) goto LAB_00470dbe;
      uVar1 = -uVar5 + 2;
      if ((-uVar5 <= uVar1) && (uVar1 < 0x3fffffff)) {
        piVar2 = FUN_00473270(piVar2,uVar1,4);
        FID_conflict__free((void *)0x0);
        if (piVar2 != (int *)0x0) {
          piVar2[-uVar5] = (int)param_1;
          piVar2[1 - uVar5] = 0;
          puVar10 = (uint *)0x0;
          goto LAB_00470ed7;
        }
      }
    }
  }
LAB_00470dbb:
  uVar9 = 0xffffffff;
LAB_00470dbe:
  FID_conflict__free(puVar10);
  return uVar9;
}


