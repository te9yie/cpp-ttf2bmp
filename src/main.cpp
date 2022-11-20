#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char* argv[]) {
  if (argc < 1) return 0;

  FT_Error err;
  FT_Library lib;

  err = FT_Init_FreeType(&lib);
  if (err) {
    std::cerr << "init freetype: " << FT_Error_String(err) << std::endl;
    return 0;
  }

  FT_Face face;
  err = FT_New_Face(lib, argv[1], 0, &face);
  if (err) {
    std::cerr << argv[1] << ": " << FT_Error_String(err) << std::endl;
    return 0;
  }
  err = FT_Set_Pixel_Sizes(face, 0, 40);

  err = FT_Load_Char(face, 'A', FT_LOAD_RENDER);

  auto glyph = face->glyph;
  auto bitmap = glyph->bitmap;
  auto r =
      stbi_write_bmp("output.bmp", bitmap.width, bitmap.rows, 1, bitmap.buffer);

  FT_Done_Face(face);
  FT_Done_FreeType(lib);
  return 0;
}
