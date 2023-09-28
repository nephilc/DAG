#ifndef FONT_HPP
#define FONT_HPP


#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>


#include <iostream>
#include <map>
#include <string>
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Shader.hpp>


//one shader used by all fonts.

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::vec2   Size;      // Size of glyph
    glm::vec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};


class Font {
private:
static Shader *shader;
std::map<GLchar, Character> Characters;
unsigned int VAO, VBO;
static glm::mat4 projection;

public:
Font(std::string fileName);
void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

};


#endif