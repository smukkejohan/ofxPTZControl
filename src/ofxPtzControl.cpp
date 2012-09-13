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
    ip = "192.168.0.11";
    port = 80;
}

void ofxPTZControl::init() {
    init(ip, port);
}

void ofxPTZControl::init(string ip_v, int port_v) {
    
    lastCMDTime = ofGetElapsedTimeMillis();
    
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
         
    string cmd = "http://" + ip + ":" + ofToString(port) + "/cgi-bin/aw_ptz?cmd=%23" + command + "&res=1";
    
    float currentTime = ofGetElapsedTimeMillis();
    
    if (currentTime - lastCMDTime > 120){
        // dont spam the same command
        response = sendRawCommand(cmd);
        lastcmd = cmd;
        lastCMDTime = currentTime;
    } else if (lastcmd != cmd) {
        // if it is a new command wait untill 120 ms since the last command send, then send it
        ofSleepMillis(120 - (currentTime - lastCMDTime));
        response = sendRawCommand(cmd);
        lastcmd = cmd;
        lastCMDTime = currentTime;
    }
    
    return response.data;
}

ofHttpResponse ofxPTZControl::sendRawCommand(string command) {
    cout<<"Sending command: " + command<<endl;
    response = ofLoadURL(command);
    cout<<"Response: "<<response.data<<endl;
    return response;
}

