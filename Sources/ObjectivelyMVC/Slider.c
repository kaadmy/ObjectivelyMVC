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

#include <ObjectivelyMVC/Log.h>
#include <ObjectivelyMVC/Slider.h>

#define _Class _Slider

#pragma mark - Object

/**
 * @see Object::dealloc(Object *)
 */
static void dealloc(Object *self) {
	
	Slider *this = (Slider *) self;

	release(this->bar);
	release(this->handle);
	release(this->label);
	
	super(Object, self, dealloc);
}

#pragma mark - View

/**
 * @see View::layoutSubviews(View *)
 */
static void layoutSubviews(View *self) {
	
	super(View, self, layoutSubviews);
	
	Slider *this = (Slider *) self;

	const View *label = (View *) this->label;
	if (!label->hidden) {
		this->bar->frame.w -= label->frame.w;
	}

	if (this->max > this->min) {

		const double fraction = clamp((this->value - this->min) / (this->max - this->min), 0.0, 1.0);
		const SDL_Rect bounds = $(this->bar, bounds);

		View *handle = (View *) this->handle;
		handle->frame.x = (bounds.w * fraction) - handle->frame.w * 0.5;
	} else {
		LogWarn("max > min");
	}
}

/**
 * @see View::render(View *, SDL_Renderer *)
 */
static void render(View *self, SDL_Renderer *renderer) {
	
	super(View, self, render, renderer);

	Slider *this = (Slider *) self;

	const SDL_Rect frame = $(this->bar, renderFrame);

	const int y = frame.y + frame.h * 0.5;
	const int x = frame.x + frame.w;

	SDL_RenderDrawLine(renderer, frame.x, y, x, y);
}

#pragma mark - Control

/**
 * @see Control::captureEvent(Control *, const SDL_Event *)
 */
static _Bool captureEvent(Control *self, const SDL_Event *event) {
	
	Slider *this = (Slider *) self;
	
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if ($((View *) this->handle, didReceiveEvent, event)) {
			self->state |= ControlStateHighlighted;
		}
	}
	
	else if (event->type == SDL_MOUSEBUTTONUP) {
		if (self->state & ControlStateHighlighted) {
			self->state &= ~ControlStateHighlighted;
		}
	}
	
	else if (event->type == SDL_MOUSEMOTION) {
		if (self->state & ControlStateHighlighted) {
			if ($((View *) self, didReceiveEvent, event)) {
				if (event->motion.xrel) {
					if (this->bar->frame.w) {
						const double scale = (this->max - this->min) / this->bar->frame.w;
						const double delta = scale * event->motion.xrel;
						$(this, setValue, this->value + delta);
						return true;
					}
				}
			}
		}
	}
	
	return super(Control, self, captureEvent, event);
}

#pragma mark - Slider

/**
 * @fn Slider *Slider::init(Slider *self)
 *
 * @memberof Slider
 */
static Slider *initWithFrame(Slider *self, const SDL_Rect *frame, ControlStyle style) {
	
	self = (Slider *) super(Control, self, initWithFrame, frame, style);
	if (self) {
		
		self->control.view.backgroundColor = Colors.Clear;

		self->bar = $(alloc(View), initWithFrame, frame);
		assert(self->bar);

		self->bar->alignment = ViewAlignmentMiddleLeft;
		self->bar->autoresizingMask = ViewAutoresizingFill;

		$((View *) self, addSubview, self->bar);

		self->handle = $(alloc(Control), initWithFrame, NULL, style);
		assert(self->handle);

		$(self->bar, addSubview, (View *) self->handle);

		self->label = $(alloc(Label), initWithText, NULL, NULL);
		assert(self->label);

		self->label->view.alignment = ViewAlignmentMiddleRight;
		self->label->view.padding.left = DEFAULT_SLIDER_LABEL_PADDING;

		$((View *) self, addSubview, (View *) self->label);

		self->labelFormat = "%0.1f";
		
		if (self->control.style == ControlStyleDefault) {

			if (self->control.view.frame.w == 0) {
				self->control.view.frame.w = DEFAULT_SLIDER_WIDTH;
			}
			
			self->handle->bevel = BevelTypeOutset;
			self->handle->view.frame.w = DEFAULT_SLIDER_HANDLE_WIDTH;
			self->handle->view.frame.h = DEFAULT_SLIDER_HANDLE_HEIGHT;
		}
	}
	
	return self;
}

/**
 * @fn void Slider::setValue(Slider *self, double value)
 *
 * @memberof Slider
 */
static void setValue(Slider *self, double value) {

	value = clamp(value, self->min, self->max);

	const double delta = fabs(self->value - value);
	if (delta > __DBL_EPSILON__) {
		self->value = value;
		self->control.view.needsLayout = true;

		char text[64];
		snprintf(text, sizeof(text), self->labelFormat, self->value);

		$(self->label, setText, text);

		if (self->delegate.didSetValue) {
			self->delegate.didSetValue(self);
		}
	}
}

#pragma mark - Class lifecycle

/**
 * @see Class::initialize(Class *)
 */
static void initialize(Class *clazz) {
	
	((ObjectInterface *) clazz->interface)->dealloc = dealloc;

	((ViewInterface *) clazz->interface)->layoutSubviews = layoutSubviews;
	((ViewInterface *) clazz->interface)->render = render;
	
	((ControlInterface *) clazz->interface)->captureEvent = captureEvent;
	
	((SliderInterface *) clazz->interface)->initWithFrame = initWithFrame;
	((SliderInterface *) clazz->interface)->setValue = setValue;
}

Class _Slider = {
	.name = "Slider",
	.superclass = &_Control,
	.instanceSize = sizeof(Slider),
	.interfaceOffset = offsetof(Slider, interface),
	.interfaceSize = sizeof(SliderInterface),
	.initialize = initialize,
};

#undef _Class

