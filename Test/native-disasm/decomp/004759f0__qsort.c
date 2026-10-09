// _qsort @ 004759f0 size=916 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    _qsort
   
   Library: Visual Studio 2015 Release */

void __cdecl
_qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,_PtFuncCompare *_PtFuncCompare)

{
  uint uVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  size_t sVar8;
  char *in_stack_fffffec4;
  void *pvVar9;
  char *pcVar10;
  char *local_118;
  char *local_114;
  char *local_110;
  int local_10c;
  char *local_108;
  undefined4 auStack_f8 [30];
  undefined4 auStack_80 [30];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  local_108 = _Base;
  if ((((_Base == (void *)0x0) && (_NumOfElements != 0)) || (_SizeOfElements == 0)) ||
     (_PtFuncCompare == (_PtFuncCompare *)0x0)) {
    piVar3 = __errno();
    *piVar3 = 0x16;
    FUN_00465fa2();
    return;
  }
  local_10c = 0;
  if (_NumOfElements < 2) {
    return;
  }
  pcVar5 = (char *)((_NumOfElements - 1) * _SizeOfElements + (int)_Base);
LAB_00475a75:
  while (uVar1 = (uint)((int)pcVar5 - (int)local_108) / _SizeOfElements + 1, 8 < uVar1) {
    pcVar7 = local_108 + (uVar1 >> 1) * _SizeOfElements;
    pcVar6 = local_108;
    pcVar10 = pcVar7;
    (*(code *)PTR_guard_check_icall_004805b0)();
    pvVar9 = (void *)0x475ab4;
    iVar4 = (*_PtFuncCompare)(pcVar6,pcVar10);
    if (0 < iVar4) {
      swap(local_108,pcVar7,_SizeOfElements);
    }
    pcVar6 = local_108;
    pcVar10 = pcVar5;
    (*(code *)PTR_guard_check_icall_004805b0)();
    iVar4 = (*_PtFuncCompare)(pcVar6,pcVar10);
    if (0 < iVar4) {
      swap(local_108,pcVar5,_SizeOfElements);
    }
    (*(code *)PTR_guard_check_icall_004805b0)(pcVar7,pcVar5);
    iVar4 = (*_PtFuncCompare)(in_stack_fffffec4,pvVar9);
    local_110 = local_108;
    local_118 = pcVar5;
    local_114 = pcVar7;
    if (0 < iVar4) {
      in_stack_fffffec4 = (char *)0x475b22;
      swap(pcVar7,pcVar5,_SizeOfElements);
    }
LAB_00475b40:
    if (local_110 < pcVar7) {
      do {
        local_110 = local_110 + _SizeOfElements;
        if (pcVar7 <= local_110) goto LAB_00475b81;
        pvVar9 = (void *)0x475b5e;
        (*(code *)PTR_guard_check_icall_004805b0)(local_110,pcVar7);
        iVar4 = (*_PtFuncCompare)(in_stack_fffffec4,pvVar9);
      } while (iVar4 < 1);
      if (pcVar7 <= local_110) goto LAB_00475b81;
    }
    else {
LAB_00475b81:
      do {
        local_110 = local_110 + _SizeOfElements;
        if (pcVar5 < local_110) break;
        pvVar9 = (void *)0x475b91;
        (*(code *)PTR_guard_check_icall_004805b0)(local_110,pcVar7);
        iVar4 = (*_PtFuncCompare)(in_stack_fffffec4,pvVar9);
      } while (iVar4 < 1);
    }
    do {
      local_118 = local_118 + -_SizeOfElements;
      if (local_118 <= pcVar7) break;
      pvVar9 = (void *)0x475bd6;
      (*(code *)PTR_guard_check_icall_004805b0)(local_118,pcVar7);
      iVar4 = (*_PtFuncCompare)(in_stack_fffffec4,pvVar9);
    } while (0 < iVar4);
    if (local_110 <= local_118) {
      pcVar6 = local_118;
      sVar8 = _SizeOfElements;
      if (local_110 != local_118) {
        do {
          pcVar7 = pcVar6 + 1;
          cVar2 = pcVar7[(int)(local_110 + (-1 - (int)local_118))];
          pcVar7[(int)(local_110 + (-1 - (int)local_118))] = *pcVar6;
          *pcVar6 = cVar2;
          sVar8 = sVar8 - 1;
          pcVar6 = pcVar7;
          pcVar7 = local_114;
        } while (sVar8 != 0);
      }
      if (pcVar7 == local_118) {
        local_114 = local_110;
        pcVar7 = local_110;
      }
      goto LAB_00475b40;
    }
    local_118 = local_118 + _SizeOfElements;
    if (pcVar7 < local_118) {
      do {
        local_118 = local_118 + -_SizeOfElements;
        if (local_118 <= pcVar7) goto LAB_00475c91;
        pvVar9 = (void *)0x475c74;
        (*(code *)PTR_guard_check_icall_004805b0)(local_118,pcVar7);
        iVar4 = (*_PtFuncCompare)(in_stack_fffffec4,pvVar9);
      } while (iVar4 == 0);
      if (local_118 <= pcVar7) goto LAB_00475c91;
    }
    else {
LAB_00475c91:
      do {
        local_118 = local_118 + -_SizeOfElements;
        if (local_118 <= local_108) break;
        pvVar9 = (void *)0x475ca5;
        (*(code *)PTR_guard_check_icall_004805b0)(local_118,pcVar7);
        iVar4 = (*_PtFuncCompare)(in_stack_fffffec4,pvVar9);
      } while (iVar4 == 0);
    }
    if ((int)local_118 - (int)local_108 < (int)pcVar5 - (int)local_110) goto LAB_00475d0b;
    if (local_108 < local_118) {
      auStack_f8[local_10c] = local_108;
      auStack_80[local_10c] = local_118;
      local_10c = local_10c + 1;
    }
    local_108 = local_110;
    if (pcVar5 <= local_110) goto LAB_00475d52;
  }
  shortsort(local_108,pcVar5,_SizeOfElements,(_func_int_void_ptr_void_ptr *)_PtFuncCompare);
  in_stack_fffffec4 = local_108;
  goto LAB_00475d52;
LAB_00475d0b:
  if (local_110 < pcVar5) {
    auStack_f8[local_10c] = local_110;
    auStack_80[local_10c] = pcVar5;
    local_10c = local_10c + 1;
  }
  pcVar5 = local_118;
  if (local_118 <= local_108) {
LAB_00475d52:
    local_10c = local_10c + -1;
    if (local_10c < 0) {
      return;
    }
    local_108 = (char *)auStack_f8[local_10c];
    pcVar5 = (char *)auStack_80[local_10c];
  }
  goto LAB_00475a75;
}


