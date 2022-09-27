typedef struct
{
  HWND TargetWindow;
  HDC MemoryDC;
  //HBITMAP BitmapHandle;
  BITMAPINFO Bitmap;
  uint32_t* Pixels;
} gdi_renderer;


static void Renderer_Resize(gdi_renderer* Renderer)
{
  if (Renderer->Pixels)
  {
    free(Renderer->Pixels);
  }
  RECT WindowRect;
  GetClientRect(Renderer->TargetWindow, &WindowRect);
  int NewWidth = WindowRect.right - WindowRect.left;
  int NewHeight = WindowRect.bottom - WindowRect.top;
  Renderer->Bitmap.bmiHeader.biWidth = NewWidth;
  Renderer->Bitmap.bmiHeader.biHeight = NewHeight; // negative for top-down bitmap
  int AllocSize = sizeof(*Renderer->Pixels) * NewWidth * NewHeight;
  Renderer->Pixels = malloc(AllocSize);
  ASSERT(Renderer->Pixels);
}

static gdi_renderer* Renderer_Create(HWND Window)
{
  gdi_renderer* Result = malloc(sizeof(*Result));
  ASSERT(Result);
  memset(Result, 0, sizeof(*Result));
  Result->TargetWindow = Window;
  Renderer_Resize(Result);
  HDC WindowDC = GetDC(Window);
  Result->MemoryDC = CreateCompatibleDC(WindowDC);
  ReleaseDC(Window, WindowDC);
  Result->Bitmap.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  Result->Bitmap.bmiHeader.biPlanes = 1;
  Result->Bitmap.bmiHeader.biBitCount = 32;
  Result->Bitmap.bmiHeader.biCompression = BI_RGB;
  return Result;
}


static void Renderer_Update(gdi_renderer* Renderer)
{
  int RendererWidth = Renderer->Bitmap.bmiHeader.biWidth;
  int RendererHeight = Renderer->Bitmap.bmiHeader.biHeight;
  HDC WindowDC = GetDC(Renderer->TargetWindow);
#if 1
  StretchDIBits(WindowDC, 0, 0, RendererWidth, RendererHeight, 0, 0, RendererWidth, RendererHeight, Renderer->Pixels, &Renderer->Bitmap, DIB_RGB_COLORS, SRCCOPY);
#else
  // do CreateDIBSection() first
  BitBlt(WindowDC, 0, 0, RendererWidth, RendererHeight, Renderer->MemoryDC, 0, 0, SRCCOPY);
#endif
  ReleaseDC(Renderer->TargetWindow, WindowDC);
}

static void Renderer_Clear(gdi_renderer* Renderer, uint32_t ClearColor)
{
  int RendererWidth = Renderer->Bitmap.bmiHeader.biWidth;
  int RendererHeight = Renderer->Bitmap.bmiHeader.biHeight;
  int BufferSize = RendererWidth * RendererHeight;
  for (int Index = 0; Index < BufferSize; Index += 1)
  {
    Renderer->Pixels[Index] = ClearColor;
  }
}

static void Renderer_DrawPixel(gdi_renderer* Renderer, uint32_t X, uint32_t Y, uint32_t Color)
{
  uint32_t RendererWidth = Renderer->Bitmap.bmiHeader.biWidth;
  uint32_t RendererHeight = Renderer->Bitmap.bmiHeader.biHeight;
  if (X < RendererWidth && Y < RendererHeight)
  {
    Renderer->Pixels[X + (Y * RendererWidth)] = Color;
  }
}

static void Renderer_Delete(gdi_renderer* Renderer)
{
  free(Renderer->Pixels);
  DeleteDC(Renderer->MemoryDC);
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
static void Renderer_DrawLine(gdi_renderer* Renderer, int X0, int Y0, int X1, int Y1)
{
  int DeltaX =  ABS(X1 - X0);
  int DeltaY = -ABS(Y1 - Y0);
  int StepX = (X0 < X1) ? 1 : -1;
  int StepY = (Y0 < Y1) ? 1 : -1;
  int Error = DeltaX + DeltaY;
  for (;;)
  {
    Renderer_DrawPixel(Renderer, X0, Y0, 0x00ff0000);
    if (X0 == X1 && Y0 == Y1)
    {
      break;
    }
    int Error2 = Error * 2;
    if (DeltaY <= Error2)
    {
      Error += DeltaY;
      X0 += StepX;
    }
    if (DeltaX >= Error2)
    {
      Error += DeltaX;
      Y0 += StepY;
    }
  }
}


static void Renderer_DrawTriangle(gdi_renderer* Renderer, triangle2d Trig)
{
  Renderer_DrawLine(Renderer, Trig.Points[0].X, Trig.Points[0].Y, Trig.Points[1].X, Trig.Points[1].Y);
  Renderer_DrawLine(Renderer, Trig.Points[0].X, Trig.Points[0].Y, Trig.Points[2].X, Trig.Points[2].Y);
  Renderer_DrawLine(Renderer, Trig.Points[1].X, Trig.Points[1].Y, Trig.Points[2].X, Trig.Points[1].Y);
}


static void Renderer_FillTriangle(gdi_renderer* Renderer, triangle2d Trig)
{
  int MinX = MIN(Trig.Points[0].X, MIN(Trig.Points[1].X, Trig.Points[2].X));
  int MinY = MIN(Trig.Points[0].Y, MIN(Trig.Points[1].Y, Trig.Points[2].Y));
  int MaxX = MAX(Trig.Points[0].X, MAX(Trig.Points[1].X, Trig.Points[2].X));
  int MaxY = MAX(Trig.Points[0].Y, MAX(Trig.Points[1].Y, Trig.Points[2].Y));

  for (float Y = MinY; Y <= MaxY; Y += 1)
  {
    for (float X = MinX; X <= MaxX; X += 1)
    {
      point2d Pixel = { X, Y };
      if (Point2D_IsInsideTriangle(Pixel, Trig))
      {
        Renderer_DrawPixel(Renderer, X, Y, 0x00ff0000);
      }
    }
  }
}


static void Renderer_DrawTriangle3D(gdi_renderer* Renderer, triangle3d T3D)
{
  if (Triangle3D_IsBackFaced(T3D))
  {
    return;
  }
  triangle2d T2D = Triangle3D_ToTriangle2D(T3D);
  int RendererWidth = Renderer->Bitmap.bmiHeader.biWidth;
  int RendererHeight = Renderer->Bitmap.bmiHeader.biHeight;
  T2D = Triangle2D_MapToViewport(T2D, RendererWidth, RendererHeight);
  //Renderer_DrawTriangle(Renderer, T2D);
  Renderer_FillTriangle(Renderer, T2D);
}

static void Renderer_DrawTriangles(gdi_renderer* Renderer, triangle3d* Tris, int TrisCount)
{
  for (int TriIndex = 0; TriIndex < TrisCount; TriIndex += 1)
  {
    triangle3d Triangle = Tris[TriIndex];

  }
}


static void Renderer_DebugTest(gdi_renderer* Renderer, obj_model* Model)
{
  camera MainCamera = Camera_Create((vector3) { 0.0, 0.0, -5.0 });
  //matrix4 Mat = Camera_Matrix(&MainCamera);
  matrix4 Translation = Matrix4_Translate((vector3) { 0, 0, 5 });
  matrix4 Rotation = Matrix4_RotateZ(90);
  matrix4 View = Matrix4_MultiplyMatrix4(Rotation, Translation);
  matrix4 Projection = Matrix4_Perspective(9.0 / 16.0, 90, 0.001, 1000.0);
  matrix4 TestMatrix = Matrix4_MultiplyMatrix4(Projection, View);
  for (int FaceIndex = 0; FaceIndex < Model->FacesCount; FaceIndex += 1)
  {
    vector3 Verts[3];
    Verts[0] = Model->Verts[Model->Faces[FaceIndex].Index[0]];
    Verts[1] = Model->Verts[Model->Faces[FaceIndex].Index[1]];
    Verts[2] = Model->Verts[Model->Faces[FaceIndex].Index[2]];

    triangle3d Example;
    Example.Points[0] = Matrix4_MultiplyVector3(TestMatrix, Verts[0]);
    Example.Points[1] = Matrix4_MultiplyVector3(TestMatrix, Verts[1]);
    Example.Points[2] = Matrix4_MultiplyVector3(TestMatrix, Verts[2]);
    Renderer_DrawTriangle3D(Renderer, Example);
  }
}

