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

#ifndef _ObjectivelyMVC_Colors_h_
#define _ObjectivelyMVC_Colors_h_

#include <SDL2/SDL_pixels.h>

/**
 * @brief Color constants.
 */
typedef struct {
	
	/**
	 * @brief The default background color for newly initialized elements.
	 */
	SDL_Color backgroundColor;
	
	/**
	 * @brief The default foreground color for newly initialized elements.
	 */
	SDL_Color foregroundColor;
	
	SDL_Color white;
	SDL_Color black;
	SDL_Color gray;
	SDL_Color red;
	SDL_Color green;
	SDL_Color blue;
	SDL_Color clear;
} Colors_t;

extern const Colors_t Colors;

#define SetRenderDrawColor(renderer, color) \
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a)

#endif