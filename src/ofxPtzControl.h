//
//  ofxPTZControl.h
//  ptzControl
//
//  Created by Johan Bichel Lindegaard on 29/06/12.
//


#pragma once

#include "ofMain.h"

class ofxPTZControl {
public:
    ofxPTZControl();
    
    
    void init();
    void init(string ip, int port);
    
    string ip;
    int port;
    
    void powerOn();
    void powerOff();
    
    // sc: speed control functions
    // pc: position command
    
    void scPanTilt(int panSpeed, int tiltSpeed);
    void scTilt(int tiltSpeed);
    void scPan(int panSpeed);
    void scZoom(int zoomSpeed);
    
    void pcPanTilt(int panPos, int tiltPos);
    
    pair<int,int> getPanTiltPos();

    int getZoomPos();
    
    int getTiltSpeed();
    int getPanSpeed();
    int getZoomSpeed();
    
    
    
    
    
    //void stop();
    
    
    
private:
    
    ofHttpResponse response;
    
    string sendCommand(string cmd);
    
};
