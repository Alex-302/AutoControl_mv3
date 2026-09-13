// FUN_0040a870 @ 0040a870 size=156 callers=2

void * __thiscall FUN_0040a870(void *this,void *param_1,LONG param_2)

{
  HDC hdc;
  HDC hdc_00;
  HBITMAP pHVar1;
  BITMAPINFO local_2c;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  hdc = GetDC((HWND)0x0);
  hdc_00 = CreateCompatibleDC(hdc);
  local_2c.bmiHeader.biHeight = param_2;
  *(HDC *)this = hdc_00;
  local_2c.bmiHeader.biSize = 0x28;
  local_2c.bmiHeader.biSizeImage = 0;
  local_2c.bmiHeader.biXPelsPerMeter = 0;
  local_2c.bmiHeader.biYPelsPerMeter = 0;
  local_2c.bmiHeader.biClrUsed = 0;
  local_2c.bmiHeader.biWidth = (LONG)param_1;
  local_2c.bmiHeader.biClrImportant = 0;
  local_2c.bmiColors[0].rgbBlue = '\0';
  local_2c.bmiColors[0].rgbGreen = '\0';
  local_2c.bmiColors[0].rgbRed = '\0';
  local_2c.bmiColors[0].rgbReserved = '\0';
  local_2c.bmiHeader.biPlanes = 1;
  local_2c.bmiHeader.biBitCount = 0x20;
  local_2c.bmiHeader.biCompression = 0;
  pHVar1 = CreateDIBSection(hdc_00,&local_2c,0,&param_1,(HANDLE)0x0,0);
  *(HBITMAP *)((int)this + 4) = pHVar1;
  ReleaseDC((HWND)0x0,hdc);
  SelectObject(*(HDC *)this,*(HGDIOBJ *)((int)this + 4));
  return this;
}


