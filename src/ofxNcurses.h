#pragma once

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

#include "ofMain.h"

class ofxNcurses;

namespace nc {
	
	class Win {

		Win(){};

	public:
		
		struct FLAG_STDSCR {};
		Win(FLAG_STDSCR); // creates a base window from stdscr, this is only allowed

		Win(int x_, int y_, int w_, int h_, bool scrollOK_ = TRUE, bool immedOK_ = false);
		
		virtual ~Win();
		
		const int& getWidth() const  { return w; };
		const int& getHeight() const { return h; };
		
		void setWidth(int width_);
		void setHeight(int height_);
		void resize(int width_, int height_);
		
		void setPos(int x_, int y_);
		
		// draws box around window
		void box(int h_char = 0, int v_char = 0);
		
		void print(string line_);
		void printC(char char_);
		void refresh();
		void erase();
		
		/// move physical cursor
		void curMove(int x_, int y_);
		
		/// move virtual cursor
		void moveTo(int x_, int y_);

		string wrapString(string str_);
		
		enum Attr {
			NORMAL,
			STANDOUT,
			REVERSE,
			DIM,
			COLOR_1,
			COLOR_2,
			BOLD,
		};
		
		void attrOn(Attr attr_);
		void attrOff(Attr attr_);
		
		void * getWin() {return winP; };
		
	private:

		void * winP;
		
		int x;
		int y;
		int w;
		int h;
		
		bool scrollOK; /// whether scrolling is enabled.
		bool immedOK;
	};
	

	// a form with an (optionally) associated window.
	
	class FormField {
	public:
		FormField();
		
		/// assign form to window
		void setWindow(shared_ptr<nc::Win> win_);
		
		/// call setup after you have associated a window!
		void setup();
		void keyPressed(int key);
		void focusField();
		
		virtual ~FormField();
	private:
		nc::Win * winP;	// pointer to window
		void * formP;   // pointer to form
		void * field[2];  // arrays of 2 fields, null terminated.
	};
	
}

// ----------------------------------------------------------------------

class ofxNcurses {
public:

	// this will grab stdscr as the first window.
	static void setup();
	
	/// max width of terminal
	static int getWidth();
	/// max height of terminal
	static int getHeight();
	static void erase();
	static void refresh();
	
	static shared_ptr<nc::Win> addWindow(int x_, int y_, int w_, int h_, bool scrollOK_ = TRUE, bool immedOK_ = false);
	
	static void hideCursor();
	static void showCursor();

	static shared_ptr<nc::Win> getCurrentWindow();

	static string wrapString(string str_, int w_);
	
private:

	static bool hasColor;
	
	
	static shared_ptr<nc::Win> currentWin;
	static vector<shared_ptr<nc::Win> > windows;

};
