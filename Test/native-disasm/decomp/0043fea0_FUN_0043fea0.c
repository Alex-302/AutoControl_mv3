// FUN_0043fea0 @ 0043fea0 size=138 callers=1

void __thiscall FUN_0043fea0(void *this,uint param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  puVar1 = *(undefined4 **)((int)this + 4);
  puVar2 = *(undefined4 **)this;
  uVar3 = (int)puVar1 - (int)puVar2 >> 2;
  if (param_1 < uVar3) {
    *(undefined4 **)((int)this + 4) = puVar1 + (param_1 - uVar3);
    return;
  }
  if (uVar3 < param_1) {
    if ((param_2 < puVar1) && (puVar2 <= param_2)) {
      FUN_00440190(this,param_1 - uVar3);
      param_2 = (undefined4 *)(*(int *)this + ((int)param_2 - (int)puVar2 >> 2) * 4);
    }
    else {
      FUN_00440190(this,param_1 - uVar3);
    }
    FUN_00448200(*(undefined4 **)((int)this + 4),
                 param_1 - ((int)*(undefined4 **)((int)this + 4) - *(int *)this >> 2),param_2);
    *(int *)((int)this + 4) =
         *(int *)((int)this + 4) + (param_1 - (*(int *)((int)this + 4) - *(int *)this >> 2)) * 4;
  }
  return;
}


