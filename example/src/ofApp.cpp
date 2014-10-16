#include "ofApp.h"
#include "ofxNcurses.h"

shared_ptr<nc::Win> mMainWindow;

vector<string> worldStr;

//--------------------------------------------------------------
void ofApp::setup(){

	worldStr.push_back("             ';lxO0kk00klll:'");
	worldStr.push_back("         .ldockMMMMMMMXl.;k0Oxol.");
	worldStr.push_back("       :xo'    KMMMMMMMMN0WMWx.'ox;");
	worldStr.push_back("     ,kc.     :WMMMMMMMMMMMMK:.   lk;");
	worldStr.push_back("    ok.       .XMMMMMMMMMMMN;      .xo");
	worldStr.push_back("   dd          'k0MMMMKxdldl         ox.");
	worldStr.push_back("  d0.           ..oMMX.    .          Ox");
	worldStr.push_back(" 'N,               ;kKxlOk            'X,");
	worldStr.push_back(" cO                    .;:d;  .;''.    xl");
	worldStr.push_back(" lx                        ''lWMMMWk:. do");
	worldStr.push_back(" :O                          cMMMMMMMx'Oc");
	worldStr.push_back(" .N;                        ;WMMMMMMMMMW'");
	worldStr.push_back("  lK.                       .0MMMMMMMMMo");
	worldStr.push_back("   lk                        .OWMMMMMWo");
	worldStr.push_back("    :O'                        OMMMMWc");
	worldStr.push_back("     .do.                    .OMMMWx.");
	worldStr.push_back("       'od:.                ,XMWXd.");
	worldStr.push_back("          ;looc,.        .,kN0o;");
	worldStr.push_back("              .;llllllllll;..");
	
	ofSetFrameRate(10);

	ofxNcurses::setup();
	ofxNcurses::hideCursor();
	
	mMainWindow         = ofxNcurses::addWindow(0, 0, ofxNcurses::getWidth(), ofxNcurses::getHeight(), true, true);
	mMainWindow->box();
	
}

//--------------------------------------------------------------
void ofApp::update(){

	int offset = ofGetFrameNum();
	
	mMainWindow->erase();
	for (int i=0; i<worldStr.size(); i++){
		mMainWindow->moveTo(10, (i + offset) % mMainWindow->getHeight());
		mMainWindow->print(worldStr[i]);
	}

	mMainWindow->moveTo(10,mMainWindow->getHeight() / 2);
	mMainWindow->attrOn(nc::Win::COLOR_1);
	mMainWindow->print("HELLO");
	mMainWindow->attrOff(nc::Win::COLOR_1);
	
	mMainWindow->refresh();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
		case 'Q':
		case 'q':
		case OF_KEY_ESC:
			ofExit();
			break;
			
  default:
			break;
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
