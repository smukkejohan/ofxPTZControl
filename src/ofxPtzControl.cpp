//
//  ofxPtzControl.cpp
//  ptzControl
//
//  Created by Johan Bichel Lindegaard on 29/06/12.
//

#include "ofxPtzControl.h"
#include "ofMain.h"


ofxPtzControl::ofxPtzControl(){
    // consider loading settings from xml
    
    ip = "192.168.0.10";
    port = 80;
}


void ofxPtzControl::powerOn(){
    sendCommand("O1");
}

void ofxPtzControl::powerOff(){
    sendCommand("O0");
}

void ofxPtzControl::scPanTilt(int panSpeed, int tiltSpeed) {
    // pan and til speed value between 1 and 99
    sendCommand("PTS" + ofToString(panSpeed) + ofToString(tiltSpeed));
}

void ofxPtzControl::scZoom(int zoomSpeed) {
    // zoom speed value between 1 and 99
    sendCommand("Z" + ofToString(zoomSpeed));
}

void ofxPtzControl::pcPanTilt(int panPos, int tiltPos) {
    // pan and tilt can be set to a value between 1 and 65535
    sendCommand("APC" + ofToHex(panPos) + ofToHex(tiltPos));
}

pair<int, int> ofxPtzControl::getPanTiltPos(){
    //Example use:
    //pair<int, int> pantilt = ptzC.getPanTiltPos();
    //cout<<"pan: "<<pantilt.first<<endl;
    //cout<<"tilt: "<<pantilt.second<<endl;
    
    string data = sendCommand("APC");
    return make_pair(ofHexToInt(data.substr(3,4)), ofHexToInt(data.substr(7,4)));    
}

string ofxPtzControl::sendCommand(string command){
    
    // todo: add 120ms timer to not overflow with movement commands
    
    string cmd = "http://" + ip + ":" + ofToString(port) + "/cgi-bin/aw_ptz?cmd=%23" + command + "&res=1";
    cout<<"Sending command: " + cmd<<endl;
    response = ofLoadURL(cmd);
    cout<<"Response: "<<response.data<<endl;
    return response.data;
}

