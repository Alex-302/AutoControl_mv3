// FUN_00415570 @ 00415570 size=237 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00415570(int *param_1)

{
  int *piVar1;
  int *in_EAX;
  int *piVar2;
  int *unaff_ESI;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined4 uStack_10;
  int *piStack_c;
  undefined4 uStack_8;
  
  if (param_1[0xb] == 0) {
    piVar2 = (int *)*param_1;
    local_14 = 0;
    uStack_10 = 0;
    piStack_c = (int *)0x0;
    uStack_8 = 0;
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 0x34))
                (piVar2,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_14);
    }
    param_1[0xb] = (int)piStack_c;
    in_EAX = piStack_c;
  }
  if (param_1[0xb] != 0x25) {
    piVar2 = (int *)FUN_00414ec0(param_1);
    in_EAX = piVar2;
    if (piVar2[0xb] == 0) {
      piVar1 = (int *)*piVar2;
      local_14 = 0;
      uStack_10 = 0;
      piStack_c = (int *)0x0;
      uStack_8 = 0;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 0x34))
                  (piVar1,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_14);
      }
      piVar2[0xb] = (int)piStack_c;
      in_EAX = piStack_c;
    }
    if ((int *)piVar2[0xb] != (int *)0x25) {
      in_EAX = (int *)(DAT_004a23a4 - 0x55);
      if (((in_EAX < &DAT_0000000f) && (param_1[0xb] == 0x10)) &&
         (in_EAX = (int *)((-(uint)(0x56 < DAT_004a23a4) & 0xffffffd4) + 0x3c),
         (int *)piVar2[0xb] == in_EAX)) {
        if (param_1[0x11] == -1) {
          piVar2 = (int *)*param_1;
          uStack_18 = 0;
          in_EAX = (int *)0x0;
          if (piVar2 != (int *)0x0) {
            (**(code **)(*piVar2 + 0x20))(piVar2,&uStack_18);
            in_EAX = unaff_ESI;
          }
          param_1[0x11] = (int)in_EAX;
        }
        if (param_1[0x11] == 0) goto LAB_004155b2;
      }
      return (uint)in_EAX & 0xffffff00;
    }
  }
LAB_004155b2:
  return CONCAT31((int3)((uint)in_EAX >> 8),1);
}


