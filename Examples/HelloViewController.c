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

#include <ObjectivelyMVC.h>

#include "HelloViewController.h"

#define _Class _HelloViewController

#pragma mark - Actions

/**
 * @brief ActionFunction for Button.
 */
static void buttonAction(Control *control, const SDL_Event *event, ident sender, ident data) {
	printf("Button clicked\n");
}

/**
 * @brief ActionFunction for Checkbox.
 */
static void checkboxAction(Control *control, const SDL_Event *event, ident sender, ident data) {
	if ($(control, selected)) {
		printf("Checkbox selected\n");
	} else {
		printf("Checkbox deselected\n");
	}
}

#pragma mark - SliderDelegate

/**
 * @brief SliderDelegate callback.
 */
static void sliderDidSetValue(Slider *slider) {
	printf("Slider value: %.1f\n", slider->value);
}

#pragma mark - TableViewDataSource

/**
 * @see TableViewDataSource::numberOfRows(const TableView *)
 */
static size_t numberOfRows(const TableView *tableView) {
	return 3;
}

/**
 * @see TableViewDataSource::valueForColumnAndRow(const TableView *, const TableColumn *, int)
 */
static ident valueForColumnAndRow(const TableView *tableView,
								  const TableColumn *column,
								  int row) {

	const Array *columns = (Array *) tableView->columns;
	const int col = $(columns, indexOfObject, (ident) column);
	return (intptr_t) (columns->count * row + col);
}

#pragma mark - TableViewDelegate

/**
 * @see TableViewDelegate::cellForColumnAndRow(const TableView *, const TableColumn *, int)
 */
static TableCellView *cellForColumnAndRow(const TableView *tableView,
										  const TableColumn *column,
										  int row) {

	TableCellView *cell = $(alloc(TableCellView), initWithFrame, NULL);

	const intptr_t value = valueForColumnAndRow(tableView, column, row);

	char chars[8];
	snprintf(chars, sizeof(chars), "%zd", value);
	$(cell->text, setText, chars);

	return cell;
}

#pragma mark - ViewController

/**
 * @see ViewController::loadView(ViewController *)
 */
static void loadView(ViewController *self) {

	super(ViewController, self, loadView);

	const SDL_Rect frame = { .x = 50, .y = 50 };
	Panel *panel = $(alloc(Panel), initWithFrame, &frame);

	panel->view.autoresizingMask = ViewAutoresizingContain;

	$(self->view, addSubview, (View *) panel);
	
	StackView *stackView = $(alloc(StackView), initWithFrame, NULL);
	stackView->view.autoresizingMask = ViewAutoresizingContain;
	stackView->spacing = 10;
	
	$((View *) panel, addSubview, (View *) stackView);
	
	Button *button = $(alloc(Button), initWithFrame, NULL, ControlStyleDefault);
	$(button->title, setText, "This is a Button");
	$((Control *) button, addActionForEventType, SDL_MOUSEBUTTONUP, buttonAction, self, NULL);
	
	$((View *) stackView, addSubview, (View *) button);

	TextView *textView = $(alloc(TextView), initWithFrame, NULL, ControlStyleDefault);
	textView->defaultText = "This is a TextView";
	
	$((View *) stackView, addSubview, (View *) textView);

	Checkbox *checkbox = $(alloc(Checkbox), initWithFrame, NULL, ControlStyleDefault);
	Label *checkboxLabel = $(alloc(Label), initWithText, "This is a checkbox:", NULL);
	Input *checkboxInput = $(alloc(Input), initWithOrientation, InputOrientationLeft, (Control *) checkbox, checkboxLabel);
	$((Control *) checkbox, addActionForEventType, SDL_MOUSEBUTTONUP, checkboxAction, self, NULL);

	$((View *) stackView, addSubview, (View *) checkboxInput);

	Select *select = $(alloc(Select), initWithFrame, NULL, ControlStyleDefault);
	$(select, addOption, "This is a select", (ident) 1);
	$(select, addOption, "This is an option", (ident) 2);
	$(select, addOption, "This is another", (ident) 3);
	$((View *) select, sizeToFit);
	
	$((View *) stackView, addSubview, (View *) select);

	Slider *slider = $(alloc(Slider), initWithFrame, NULL, ControlStyleDefault);
	slider->delegate.didSetValue = sliderDidSetValue;
	slider->min = 0.1, slider->max = 10.0, slider->step = 0.1;
	$(slider, setValue, 5.0);

	$((View *) stackView, addSubview, (View *) slider);

	TableView *tableView = $(alloc(TableView), initWithFrame, NULL);
	tableView->dataSource.numberOfRows = numberOfRows;
	tableView->dataSource.valueForColumnAndRow = valueForColumnAndRow;
	tableView->delegate.cellForColumnAndRow = cellForColumnAndRow;

	TableColumn *column1 = $(alloc(TableColumn), initWithIdentifier, "One");
	TableColumn *column2 = $(alloc(TableColumn), initWithIdentifier, "Two");
	TableColumn *column3 = $(alloc(TableColumn), initWithIdentifier, "Three");

	$(tableView, addColumn, column1);
	$(tableView, addColumn, column2);
	$(tableView, addColumn, column3);

	$(tableView, reloadData);

	$((View *) stackView, addSubview, (View *) tableView);
	$((View *) stackView, sizeToFit);

	$((View *) panel, sizeToFit);

	release(button);
	release(textView);
	release(checkbox);
	release(checkboxInput);
	release(select);
	release(slider);
	release(column1);
	release(column2);
	release(column3);
	release(tableView);
	release(stackView);
	release(panel);
}

#pragma mark - Class lifecycle

/**
 * @see Class::initialize(Class *)
 */
static void initialize(Class *clazz) {

	((ViewControllerInterface *) clazz->interface)->loadView = loadView;
}

Class _HelloViewController = {
	.name = "HelloViewController",
	.superclass = &_ViewController,
	.instanceSize = sizeof(HelloViewController),
	.interfaceOffset = offsetof(HelloViewController, interface),
	.interfaceSize = sizeof(HelloViewControllerInterface),
	.initialize = initialize,
};

#undef _Class
