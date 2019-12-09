//     _____    ___
//    /    /   /  /     ofxNcurses
//   /  __/ * /  /__    (c) ponies & light, 2014.
//  /__/     /_____/    poniesandlight.co.uk
//
//  ofxNcurses
//  Created by Tim Gfrerer on 09/10/2014.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include "ofxNcurses.h"
#include <curses.h>
#include <form.h>

// ----------------------------------------------------------------------

#define thisWin static_cast<WINDOW *>( winP )
#define thisForm static_cast<FORM *>( formP )
#define thisField static_cast<FIELD *>( field[ 0 ] )

nc::Win::Win( int x_, int y_, int w_, int h_, bool scrollOK_, bool immedOK_ )
    : winP( nullptr )
    , x( x_ )
    , y( y_ )
    , w( w_ )
    , h( h_ )
    , scrollOK( scrollOK_ )
    , immedOK( immedOK_ ) {
	winP = newwin( h, w, y, x );

	immedok( thisWin, immedOK );
	scrollok( thisWin, scrollOK );
};

// ----------------------------------------------------------------------
nc::Win::Win( nc::Win::FLAG_STDSCR )
    : winP( stdscr )
    , x( 0 )
    , y( 0 )
    , w( COLS )
    , h( LINES )
    , scrollOK( false )
    , immedOK( false ) {

	::immedok( thisWin, immedOK );
	::scrollok( thisWin, scrollOK );
};

// ----------------------------------------------------------------------

nc::Win::~Win() {
	// destroy local win
	if ( winP ) {
		erase();
		delwin( thisWin );
		winP = nullptr;
	};
}

// ----------------------------------------------------------------------

void nc::Win::setPos( int x_, int y_ ) {
	x = x_;
	y = y_;
	wmove( thisWin, y, x );
}

// ----------------------------------------------------------------------

void nc::Win::setWidth( int width_ ) {
	resize( width_, h );
}

// ----------------------------------------------------------------------

void nc::Win::setHeight( int height_ ) {
	resize( w, height_ );
}

// ----------------------------------------------------------------------

void nc::Win::resize( int width_, int height_ ) {
	w = width_;
	h = height_;
	wresize( thisWin, h, w );
}

// ----------------------------------------------------------------------

void nc::Win::refresh() {
	wrefresh( thisWin );
}

// ----------------------------------------------------------------------

void nc::Win::erase() {
	werase( thisWin );
}

// ----------------------------------------------------------------------

void nc::Win::print( string line_ ) {
	wprintw( thisWin, "%s", line_.c_str() );
}

// ----------------------------------------------------------------------

void nc::Win::printC( char char_ ) {
	waddch( thisWin, static_cast<chtype>( char_ ) );
}

// ----------------------------------------------------------------------

void nc::Win::curMove( int x_, int y_ ) {
	mvcur( 0, 0, y_ + y, x_ + x ); // move physical cursor
}

// ----------------------------------------------------------------------

void nc::Win::moveTo( int x_, int y_ ) {
	wmove( thisWin, y_, x_ ); // move logical cursor
}

// ----------------------------------------------------------------------

string nc::Win::wrapString( string str_ ) {

	return ofxNcurses::wrapString( str_, w );
}

// ----------------------------------------------------------------------

void nc::Win::box( int, int ) {
	// wborder(thisWin, '|', '|', '-', '-', '+', '+', '+', '+');
	::box( thisWin, 0, 0 );
	// wrefresh(thisWin);
}

// ----------------------------------------------------------------------

void nc::Win::attrOn( Attr attr_ ) {
	switch ( attr_ ) {
	case Win::NORMAL:
		wattrset( thisWin, A_NORMAL );
		break;
	case Win::STANDOUT:
		wattron( thisWin, A_STANDOUT );
		break;
	case Win::REVERSE:
		wattron( thisWin, A_REVERSE );
		break;
	case Win::DIM:
		wattron( thisWin, A_DIM );
		break;
	case Win::COLOR_1:
		wattron( thisWin, COLOR_PAIR( 1 ) );
		break;
	case Win::COLOR_2:
		wattron( thisWin, COLOR_PAIR( 2 ) );
		break;
	case Win::BOLD:
		wattron( thisWin, A_BOLD );
		break;
	}
}

// ----------------------------------------------------------------------

void nc::Win::attrOff( Attr attr_ ) {
	switch ( attr_ ) {
	case Win::NORMAL:
		wattrset( thisWin, A_NORMAL );
		break;
	case Win::STANDOUT:
		wattroff( thisWin, A_STANDOUT );
		break;
	case Win::REVERSE:
		wattroff( thisWin, A_REVERSE );
		break;
	case Win::DIM:
		wattroff( thisWin, A_DIM );
		break;
	case Win::COLOR_1:
		wattroff( thisWin, COLOR_PAIR( 1 ) );
		break;
	case Win::COLOR_2:
		wattroff( thisWin, COLOR_PAIR( 2 ) );
		break;
	case Win::BOLD:
		wattroff( thisWin, A_BOLD );
		break;
	}
}

// ----------------------------------------------------------------------

nc::FormField::FormField()
    : formP( nullptr ) {
	field[ 0 ] = nullptr;
	field[ 1 ] = nullptr;
};

// ----------------------------------------------------------------------

nc::FormField::~FormField() {
	// deallocate memory
	if ( thisField )
		free_field( thisField );
	if ( thisForm )
		free_form( thisForm );
};

// ----------------------------------------------------------------------

void nc::FormField::setWindow( shared_ptr<nc::Win> win_ ) {
	winP = win_.get();
}

// ----------------------------------------------------------------------

void nc::FormField::setup() {

	if ( winP == nullptr ) {
		ofLogError() << "You need to set a window for the field before calling setup()";
		return;
	}

	//--------| Invariant: we have a valid window pointer

	// create new field
	field[ 0 ] = new_field( 1, winP->getWidth(), 0, 0, 0, 0 );

	/* Set field options */
	set_field_back( thisField, A_NORMAL ); /* Print a line for the option 	*/
	field_opts_off( thisField, O_STATIC ); // allows field to grow with input.

	/* Create the form and post it */
	formP = new_form( reinterpret_cast<FIELD **>( field ) );

	set_field_just( thisField, JUSTIFY_LEFT ); /* Center Justification */
	set_field_buffer( thisField, 0, "" );

	// associate form to window
	set_form_win( thisForm, static_cast<WINDOW *>( winP->getWin() ) );
	set_form_sub( thisForm, derwin( static_cast<WINDOW *>( winP->getWin() ), winP->getHeight(), winP->getWidth(), 0, 0 ) );
	/* Initialize the field  */
	post_form( thisForm );
	winP->refresh();
}

// ----------------------------------------------------------------------

void nc::FormField::focusField() {
	form_driver( thisForm, REQ_FIRST_FIELD );
	winP->refresh();
}

// ----------------------------------------------------------------------

void nc::FormField::keyPressed( int key ) {
	switch ( key ) {
	case KEY_BACKSPACE:
	case OF_KEY_BACKSPACE:

		if ( data_behind( thisForm ) ) {
			form_driver( thisForm, REQ_SCR_BCHAR ); // scroll horizontally backward.
			form_driver( thisForm, REQ_DEL_CHAR );  // delete character
		} else {
			form_driver( thisForm, REQ_DEL_PREV ); // delete character
		}
		break;
	case OF_KEY_RETURN:
	case 10: {
		form_driver( thisForm, REQ_END_LINE ); // go to end of line
		char * buf = field_buffer( thisField, 0 );
		string msg( buf );                     // get contents.
		form_driver( thisForm, REQ_DEL_LINE ); // delete field contents.
		winP->refresh();
		ofSendMessage( ofMessage( "L|K|" + msg ) );
		break;
	}
	default:
		form_driver( thisForm, key );
		winP->refresh();
		break;
	}
	winP->refresh();
}

// ----------------------------------------------------------------------

// STATIC Elements

shared_ptr<nc::Win>         ofxNcurses::currentWin;
vector<shared_ptr<nc::Win>> ofxNcurses::windows;
bool                        ofxNcurses::hasColor = false;

// ----------------------------------------------------------------------

void ofxNcurses::setup() {

	windows.clear();
	// this will fetch stdscr as the first window.
	shared_ptr<nc::Win> win = shared_ptr<nc::Win>( new nc::Win( nc::Win::FLAG_STDSCR() ) );
	windows.push_back( win );
	currentWin = win;

	hasColor = has_colors();
	if ( hasColor ) {
		start_color();
		init_pair( 1, COLOR_GREEN, COLOR_BLACK );
		init_pair( 2, COLOR_YELLOW, COLOR_BLACK );
	}
}

// ----------------------------------------------------------------------

shared_ptr<nc::Win> ofxNcurses::addWindow( int x_, int y_, int w_, int h_, bool scrollOk_, bool immedOk_ ) {
	shared_ptr<nc::Win> win = shared_ptr<nc::Win>( new nc::Win( x_, y_, w_, h_, scrollOk_, immedOk_ ) );
	windows.push_back( win );
	currentWin = win;
	return win;
}

// ----------------------------------------------------------------------

void ofxNcurses::refresh() {
	::refresh();
}

// ----------------------------------------------------------------------

int ofxNcurses::getWidth() {
	return COLS;
}

// ----------------------------------------------------------------------

int ofxNcurses::getHeight() {
	return LINES;
}

// ----------------------------------------------------------------------

void ofxNcurses::erase() {
	::erase();
}

// ----------------------------------------------------------------------

void ofxNcurses::hideCursor() {
	curs_set( 0 );
}

// ----------------------------------------------------------------------

void ofxNcurses::showCursor() {
	curs_set( 1 );
}

// ----------------------------------------------------------------------
string ofxNcurses::wrapString( string str_, int w_ ) {
	string wS = "";

	vector<string> sV = ofSplitString( str_, " ", true, true );

	// what happens if there is a carriage return character?

	int cur_pos = 0;
	for ( auto &s : sV ) {
		if ( cur_pos + s.size() + 1 > w_ ) {
			wS += string( w_ - cur_pos, ' ' ) + s + " ";
			cur_pos = s.size() + 1;
		} else if ( cur_pos + s.size() + 1 == w_ ) {
			// exactly end of line.
			cur_pos = 0;
			wS += s + " ";
		} else {
			cur_pos += ( s.size() + 1 ) % w_;
			wS += s + " ";
		}
	}

	return wS;
}

// ----------------------------------------------------------------------

shared_ptr<nc::Win> ofxNcurses::getCurrentWindow() {
	return currentWin;
}

// ----------------------------------------------------------------------