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

#ifndef _ObjectivelyMVC_TableCellView_h_
#define _ObjectivelyMVC_TableCellView_h_

#include <ObjectivelyMVC/Control.h>

/**
 * @file
 *
 * @brief ..
 */

typedef struct TableCellView TableCellView;
typedef struct TableCellViewInterface TableCellViewInterface;

/**
 * @brief The TableCellView type.
 *
 * @extends Control
 *
 * @ingroup
 */
struct TableCellView {
	
	/**
	 * @brief The parent.
	 *
	 * @private
	 */
	Control control;
	
	/**
	 * @brief The typed interface.
	 *
	 * @private
	 */
	TableCellViewInterface *interface;
	
	//..
};

/**
 * @brief The TableCellView interface.
 */
struct TableCellViewInterface {
	
	/**
	 * @brief The parent interface.
	 */
	ControlInterface controlInterface;
	
	/**
	 * @fn TableCellView *TableCellView::init(TableCellView *self)
	 *
	 * @brief Initializes this TableCellView.
	 *
	 * @return The initialized TableCellView, or `NULL` on error.
	 *
	 * @memberof TableCellView
	 */
	TableCellView *(*initWithValue)(TableCellView *self, ident value);
	
	// ..
};

/**
 * @brief The TableCellView Class.
 */
extern Class _TableCellView;

#endif /* _ObjectivelyMVC_TableCellView_h_ */
