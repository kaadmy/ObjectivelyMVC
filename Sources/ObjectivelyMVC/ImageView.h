/*
 * ObjectivelyMVC: MVC framework for OpenGL and SDL2 in c.
 * Copyright (C) 2014 Jay Dolan <jay@jaydolan.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef _ObjectivelyMVC_ImageView_h_
#define _ObjectivelyMVC_ImageView_h_

#include <ObjectivelyMVC/View.h>

/**
 * @file
 *
 * @brief ImageView implementation.
 */

typedef struct ImageView ImageView;
typedef struct ImageViewInterface ImageViewInterface;

/**
 * @brief The ImageView type.
 */
struct ImageView {

	View view;
	ImageViewInterface *interface;

	SDL_Texture *texture;
	GLfloat alpha;

	struct {
		GLenum src;
		GLenum dst;
	} blend;
};

/**
 * @brief The ImageView interface.
 */
struct ImageViewInterface {

	ViewInterface viewInterface;

	ImageView *(*initWithFrameAndTexture)(ImageView *self, SDL_Rect *frame, SDL_Texture *texture);
};

extern Class _ImageView;

#endif