<pre>
     _____    ___     
    /    /   /  /     ofxNcurses
   /  __/ * /  /__    (c) ponies & light, 2014. 
  /__/     /_____/    poniesandlight.co.uk

  ofxNcurses
  Created by Tim Gfrerer 2014.
  
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
</pre>

# ofxNcurses

Beautiful window-less console apps on *nix systems with openFrameworks. 

This addon is a thin wrapper around the commonly available ncurses 
library. This is an initial commit. API might change. PRs welcome.

Tested against OS X, linux (debian wheezy), raspberry pi.

# Version

0.1

## Features

* Easy access to most commonly used ncurses functions
* Thin wrapper around (growing) form text fields for text input.
* Asynchronous text input routed through ofApp::keyPressed()
* Thin c++ wrapper around most common ncurses element, with intelligent memory management
* Automatically cleans up after yourself
* Keeps your global namespace clean

# Linker flags

	-lncurses -lform

OS X provides curses and form by default. Linux distributions will need the ncurses dev packages:

    apt-get install ncurses-dev

Note that XCode can't run an ncurses based console app in it's debug window. You will have to launch your app manually from the terminal, or add the following run script to your build steps:

	open "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"

## Use

	// main.cpp

	#include "ofAppCurses.h"

	void main() {

		ofAppBaseWindow * window = new ofAppCurses;
		ofSetWindow(window);
		
		ofBaseApp * app = new ofApp();
		ofRunApp( app );
	}


	// ofApp.cpp

	#include "ofxNcurses.h"

	shared_ptr<nc::Win> mChatWindow;
	shared_ptr<nc::Win> mTextInputWindow;

	ofApp::setup(){

		ofxNcurses::setup();
		ofxNcurses::erase();
		ofxNcurses::refresh();
		
		mChatWindow			= ofxNcurses::addWindow(1, 1, ofxNcurses::getWidth()-2, ofxNcurses::getHeight()-6, true, true);

		mTextInputWindow	= ofxNcurses::addWindow(14, ofxNcurses::getHeight()-3, ofxNcurses::getWidth()-2-14, 2, false , false);
		
		mLabelInputWindow   = ofxNcurses::addWindow(0, ofxNcurses::getHeight()-3, 14, 2, false , false);
		
		ofxNcurses::hideCursor();
		mLabelInputWindow->moveTo(0, 0); // moves virtual cursor
		mLabelInputWindow->print("      INPUT : "); // prints into label window
		mLabelInputWindow->refresh(); // updates label window
		
		mTextForm = shared_ptr<nc::FormField>(new nc::FormField());
		mTextForm->setWindow(mTextInputWindow);
		mTextForm->setup();

		ofxNcurses::showCursor();

		mTextForm->focusField(); // moves input focus to text form

	}

	void ofApp::keyPressed(int key){
		// any key presses will be fed through keyPressed() as usual

		// we forward the key event to the form field.
		mTextForm->keyPressed(key);
	}

# Dependencies

	None. 

