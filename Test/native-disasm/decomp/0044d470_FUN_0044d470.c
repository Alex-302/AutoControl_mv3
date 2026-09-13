// FUN_0044d470 @ 0044d470 size=68 callers=1

void __thiscall FUN_0044d470(void *this,char param_1)

{
  int *piVar1;
  
  *(undefined ***)this = &PTR_LAB_0048ec98;
  piVar1 = *(int **)((int)this + 0x2c);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x10))(piVar1 != (int *)((int)this + 8));
    *(undefined4 *)((int)this + 0x2c) = 0;
  }
  *(undefined ***)this = &PTR_FUN_0048ed18;
  if (param_1 != '\0') {
    FID_conflict__free(this);
  }
  return;
}


