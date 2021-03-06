#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	// scene
	{
		ofSetCircleResolution(300);
		halfx = ofGetWidth() / 2;
		halfy = ofGetHeight() / 2;
		pos = glm::vec2(halfx, halfy);
	}

	//--

	// capturer

	// default /rootPath/ is /bin/data/.
	// "ffmpeg.exe" -> must be located on /rootPath/.
	// converted output video output.mp4 will be placed into: /rootPath/Captures/.
	// /Captures/Snapshots/ and /Captures/Stills/ will be located on there.
	// This path can be customizable before call setup(), and should looks like:
	//capturer.setPathRoot("F:\\openFrameworks\\addons\\ofxSurfingCapturer\\example-BasicStills\\bin\\data\\");

	// we don't need depth testing for this 2D scene
	//capturer.setDephEnabled(false);

	//-

	capturer.setOutputFilename("video_1");

	//-

	capturer.setup("captures/test/", OF_IMAGE_FORMAT_TIFF);
	// capturer.setup();
	// customizable using arguments: destination, ffmpeg.exe and IMAGE_FORMAT.
	// default destination is bin/data/Captures. default image format is TIFF.

	//capturer.setOverwriteVideoOut(false); 
	// true by default. overwrites output.mp4 file. 
	// when setted to false will append timestamp to filename to allow multiple captures.

	//-

	// FFmpeg options

	// set to using CPU instead default GPU (Nvidia) when enconding video
	//capturer.setFfpmegGpu(false); 
	// Nvidia GPU HW accelerated is enabled by default. 
	// disable if you have an AMD GPU or you prefer CPU encoding

	// customizable FFmpeg script:
	//capturer.setFFmpegScript("-r 60 -c:v h264_nvenc -b:v 25M -crf 20 -preset slow");
	// this is the same interal harcoded GPU script. 
	// when you customize this script, take care of not duplicate things, re adding ffmpeg.exe, source, out...etc because they are already included !

	//-

	// local gui
	// optional. not required bc you can use command keys
	gui.setup();
	gui.add(capturer.params);
	capturer.refreshGui(gui);// refresh collapse sub menus
}

//--------------------------------------------------------------
void ofApp::update() {
	// scene
	{
		float w = 100;
		val = (ofGetFrameNum() % 120) / 120.f;// value from 0 to 1 in 2 seconds at 60 fps
		if ((ofGetFrameNum() % 60) == 0)// randomize position every second
		{
			pos = glm::vec2(ofRandom(halfx - w, halfx + w), ofRandom(halfy - w, halfy + w));
			size = ofRandom(1, 10);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	capturer.begin();
	{
		//-- draw your scene here --//

		// scene
		{
			ofClear(val * 32, 255);
			ofPushStyle();
			float radius = size * ofMap(val, 0, 1, 20, 100);
			float hue = ofMap(val, 0, 1, 50, 200);
			float y = ofMap(val, 0, 1, -200, 200);
			ofFill();
			ofColor c;
			c.setBrightness(200);
			c.setSaturation(128);
			c.setHue(hue);
			ofSetColor(c);
			float x = 200 * ofNoise(val);
			ofDrawCircle(pos.x + x, pos.y + y, radius);
			ofPopStyle();
		}
	}
	capturer.end();
	capturer.draw();// draw scene

	capturer.drawInfo();// gui help

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs &eventArgs) {
	capturer.keyPressed(eventArgs);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	capturer.windowResized(w, h);
}
