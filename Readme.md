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

# Reference Render

![image](http://poniesandlight.co.uk/static/ascii_world.png)

# Version

0.1

## Features

* Easy access to most commonly used ncurses functions
* Thin wrapper around (growing) form text fields for text input.
* Asynchronous text input routed through ofApp::keyPressed()
* Thin c++ wrapper around most common ncurses element, with intelligent memory management
* Word wrapping helper for multi-line paragraphs.
* Automatically cleans up after yourself
* Keeps your global namespace clean


## Use

See Example Project. Note that you will have to edit main.cpp to get a purely console-based application.

# Dependencies 

As the name suggests, this addon depends on ncurses and form. Ncurses is supplied by default in many *nix environments, including OS X, which also supplies the header files for both libraries. If your linux system does not supply the header files, install ```ncurses-dev``` using your favourite package manager.

## Linker flags

	-lncurses -lform

# Note

XCode can't run an ncurses based console app in it's debug window. You will have to launch your app manually from the terminal, or add the following "Run Script Phase" to your build steps:

	open "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"


## Additional Credits 

Ascii art for example project created using jp2a, http://csl.name/jp2a/



