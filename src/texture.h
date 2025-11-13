#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <cimgui.h>
#include <GLFW/glfw3.h>

typedef struct {
	int width, height;
	GLuint id;
} Texture;

bool texture_new_from_png_data(Texture* this, const unsigned char* png_data, size_t png_size);
void texture_delete(Texture* this);
void texture_to_imtextureref(const Texture* texture, ImTextureRef* out_imtextureref);
