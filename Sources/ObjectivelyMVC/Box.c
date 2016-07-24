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

#include <assert.h>

#include <ObjectivelyMVC/Box.h>

#define _Class _Box

#pragma mark - Object

/**
 * @see Object::dealloc(Object *)
 */
static void dealloc(Object *self) {
	
	Box *this = (Box *) self;

	release(this->label);
	
	super(Object, self, dealloc);
}

#pragma mark - View

/**
 * @see View::layoutSubviews(View *)
 */
static void layoutSubviews(View *self) {

	Box *this = (Box *) self;

	super(View, self, layoutSubviews);
}

#pragma mark - Box

/**
 * @fn Box *Box::initWithFrame(Box *self, const SDL_Rect *frame)
 *
 * @memberof Box
 */
static Box *initWithFrame(Box *self, const SDL_Rect *frame) {
	
	self = (Box *) super(View, self, initWithFrame, frame);
	if (self) {
		
		self->label = $(alloc(Label), initWithText, NULL, NULL);
		assert(self->label);

		self->label->view.frame.x = DEFAULT_BOX_LABEL_X;

//		$((View *) self, addSubview, (View *) self->label);

		self->view.borderColor = Colors.Gray;
		self->view.borderWidth = 1;

		self->view.padding.top = DEFAULT_BOX_PADDING;
		self->view.padding.right = DEFAULT_BOX_PADDING;
		self->view.padding.bottom = DEFAULT_BOX_PADDING;
		self->view.padding.left = DEFAULT_BOX_PADDING;
	}
	
	return self;
}

#pragma mark - Class lifecycle

/**
 * @see Class::initialize(Class *)
 */
static void initialize(Class *clazz) {
	
	((ObjectInterface *) clazz->interface)->dealloc = dealloc;

	((ViewInterface *) clazz->interface)->layoutSubviews = layoutSubviews;

	((BoxInterface *) clazz->interface)->initWithFrame = initWithFrame;
}

Class _Box = {
	.name = "Box",
	.superclass = &_View,
	.instanceSize = sizeof(Box),
	.interfaceOffset = offsetof(Box, interface),
	.interfaceSize = sizeof(BoxInterface),
	.initialize = initialize,
};

#undef _Class
