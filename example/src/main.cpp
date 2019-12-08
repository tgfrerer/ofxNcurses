#include "ofMain.h"
#include "ofApp.h"
#include "ofAppCurses.h"

int main() {
    ofAppCurses window;
    ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
    
    ofRunApp(new ofApp());
}
