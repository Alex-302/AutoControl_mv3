// FUN_00434940 @ 00434940 size=222 callers=39

void * __thiscall FUN_00434940(void *this,undefined1 *param_1)

{
  undefined4 local_10;
  undefined4 local_c;
  
  *(undefined1 *)this = *param_1;
  *(undefined8 *)((int)this + 8) = 0;
  switch(*(undefined1 *)this) {
  case 1:
    FUN_004380e0(&local_10,*(int **)(param_1 + 8));
    *(undefined4 *)((int)this + 8) = local_10;
    *(undefined4 *)((int)this + 0xc) = local_c;
    return this;
  case 2:
    FUN_00438070(&local_10,*(int **)(param_1 + 8));
    *(undefined4 *)((int)this + 8) = local_10;
    *(undefined4 *)((int)this + 0xc) = local_c;
    return this;
  case 3:
    FUN_00438150(&local_10,*(undefined4 **)(param_1 + 8));
    *(undefined4 *)((int)this + 8) = local_10;
    *(undefined4 *)((int)this + 0xc) = local_c;
    return this;
  case 4:
    local_10 = CONCAT31(local_10._1_3_,param_1[8]);
    *(undefined4 *)((int)this + 8) = local_10;
    *(undefined4 *)((int)this + 0xc) = local_c;
    return this;
  case 5:
  case 6:
    *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
    return this;
  case 7:
    *(undefined8 *)((int)this + 8) = *(undefined8 *)(param_1 + 8);
  }
  return this;
}


