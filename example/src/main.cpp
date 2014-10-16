#include "ofMain.h"
#include "ofApp.h"
#include "ofAppCurses.h"

int main() {
	
	ofAppBaseWindow * window = new ofAppCurses;
	ofSetWindow(window);
	
	ofBaseApp * app = new ofApp();
	ofRunApp( app );
}