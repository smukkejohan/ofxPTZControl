//
//  ofxPTZControl.cpp
//  ptzControl
//
//  Created by Johan Bichel Lindegaard on 29/06/12.
//

#include "ofxPTZControl.h"
#include "ofMain.h"


ofxPTZControl::ofxPTZControl(){
    // consider loading settings from xml
    
    ip = "192.168.0.10";
    port = 80;
}

void ofxPTZControl::init() {
    init(ip, port);
}

void ofxPTZControl::init(string ip_v, int port_v) {
    ip = ip_v;
    port = port_v;
    powerOn();
}


void ofxPTZControl::powerOn(){
    sendCommand("O1");
}

void ofxPTZControl::powerOff(){
    sendCommand("O0");
}

void ofxPTZControl::scPanTilt(int panSpeed, int tiltSpeed) {
    // pan and til speed value between 1 and 99
    sendCommand("PTS" + ofToString(panSpeed) + ofToString(tiltSpeed));
}

void ofxPTZControl::scZoom(int zoomSpeed) {
    // zoom speed value between 1 and 99
    sendCommand("Z" + ofToString(zoomSpeed));
}

void ofxPTZControl::pcPanTilt(int panPos, int tiltPos) {
    // pan and tilt can be set to a value between 1 and 65535
    sendCommand("APC" + ofToHex(panPos) + ofToHex(tiltPos));
}

pair<int, int> ofxPTZControl::getPanTiltPos(){
    //Example use:
    //pair<int, int> pantilt = ptzC.getPanTiltPos();
    //cout<<"pan: "<<pantilt.first<<endl;
    //cout<<"tilt: "<<pantilt.second<<endl;
    
    string data = sendCommand("APC");
    return make_pair(ofHexToInt(data.substr(3,4)), ofHexToInt(data.substr(7,4)));    
}

string ofxPTZControl::sendCommand(string command){
    
    // todo: add 120ms timer to not overflow with movement commands
    
    string cmd = "http://" + ip + ":" + ofToString(port) + "/cgi-bin/aw_ptz?cmd=%23" + command + "&res=1";
    cout<<"Sending command: " + cmd<<endl;
    response = ofLoadURL(cmd);
    cout<<"Response: "<<response.data<<endl;
    return response.data;
}

