#ifndef tlImage_h
#define tlImage_h

#include "math/tlDataTypes.h"
#include "tlString.h"

// Pixel Format Definitions
typedef enum {
  /* --- RGB / RGBA Formats --- */
  TL_FORMAT_RGBA, // 32-bit: Red, Green, Blue, Alpha (Standard)
  TL_FORMAT_RGBX, // 32-bit: Red, Green, Blue, Padding (No Alpha)
  TL_FORMAT_BGRA, // 32-bit: Blue, Green, Red, Alpha (Windows/DirectX standard)
  TL_FORMAT_BGRX, // 32-bit: Blue, Green, Red, Padding
  TL_FORMAT_RGB,  // 24-bit: Red, Green, Blue (Unpacked packed format)
  TL_FORMAT_BGR,  // 24-bit: Blue, Green, Red (OpenCV standard layout)

  /* --- Luminance / Grayscale Formats --- */
  TL_FORMAT_GRAY8,  // 8-bit: Grayscale / Luminance only
  TL_FORMAT_GRAY16, // 16-bit: High-dynamic range Grayscale

  /* --- YUV Video Formats (Packed) --- */
  TL_FORMAT_YUYV, // 16-bit: YUV 4:2:2 (Also known as YUY2)
  TL_FORMAT_UYVY, // 16-bit: YUV 4:2:2 (Mac/UYNV standard)

  /* --- YUV Video Formats (Planar) --- */
  TL_FORMAT_I420, // 12-bit: YUV 4:2:0 fully planar (Standard web video)
  TL_FORMAT_NV12, // 12-bit: YUV 4:2:0 semi-planar (Android/iOS camera standard)
  TL_FORMAT_NV21, // 12-bit: YUV 4:2:0 semi-planar (Vuforia/Android standard)

  /* --- Bayer Pattern Formats (Raw Sensors) --- */
  TL_FORMAT_BAYER_RGGB, // 8-bit Raw Bayer: Red-Green / Green-Blue
  TL_FORMAT_BAYER_BGGR, // 8-bit Raw Bayer: Blue-Green / Green-Red
  TL_FORMAT_BAYER_GRBG, // 8-bit Raw Bayer: Green-Red / Blue-Green
  TL_FORMAT_BAYER_GBRG, // 8-bit Raw Bayer: Green-Blue / Red-Green

  /* --- Special High-Bit Depth Formats --- */
  TL_FORMAT_RGB565,  // 16-bit packed: 5 bits Red, 6 bits Green, 5 bits Blue
  TL_FORMAT_RGBA16F, // 64-bit: Half-precision floating-point RGBA
  TL_FORMAT_RGBA32F  // 128-bit: Full-precision floating-point RGBA

} tlRenderFormat_PixelFormat;

typedef enum {
  TL_FORMAT_UINT8,
  TL_FORMAT_UINT16,
  TL_FORMAT_UINT32
} tlRenderFormat_DataFormat;

// struct to represent a tlImage
typedef struct {
  uint8_t numChannels;
  tlRenderFormat_PixelFormat pixelFormat;
  tlRenderFormat_DataFormat dataFormat;

  void *pData;
} tlImage;

// Image Loaders
tlImage *LoadImagePath(const tlString *filePath);
tlImage *LoadImageData(void *pData);

// Returns a vector of all the pixel data
tlVector GetImageData(tlImage *pImage);

#endif
