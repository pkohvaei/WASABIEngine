/********************************************************************************
**
** [W]ASABI [A]ffect [S]imulation [A]rchitecture for [B]elievable [I]nteractivity
**
** Copyright (C) 2011 Christian Becker-Asano.
** All rights reserved.
** Contact: Christian Becker-Asano (christian@becker-asano.de)
**
** This file is part of the WASABIEngine library.
**
** The WASABIEngine library is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** The WASABIEngine library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with the WASABIEngine library.  If not, see <http://www.gnu.org/licenses/>
**
********************************************************************************/

#include "WASABIEngine.h"
#include "cogaAttendee.h"

WASABIEngine::WASABIEngine(std::string emotionClass) {
    Class = "primary";
    if (emotionClass == "primary" || emotionClass == "secondary"){
        Class = emotionClass;
    }
    else {
        std::cerr << "WASABIEngine: emotionClass \"" << emotionClass << "\" not supported.";
    }
    initClass();
}

WASABIEngine::~WASABIEngine() {
    // TODO iterate the Vector of EmotionalAttendees here!
    //if (ownEmoAttendee) {
    //	delete ownEmoAttendee;
    //	ownEmoAttendee = 0;
    //}
}

void
WASABIEngine::initClass(){
    MaxSimulations = 10;
    nextID = 1;
    //ownEmoAttendee = new cogaEmotionalAttendee(getNextID());
    //emoAttendees.push_back(ownEmoAttendee);
}


bool
WASABIEngine::update() {
    std::vector<cogaEmotionalAttendee*>::iterator iter_ea;

    bool success = false;
    for (iter_ea = emoAttendees.begin(); iter_ea != emoAttendees.end(); ++iter_ea){
        cogaEmotionalAttendee* ea = (*iter_ea);
        success = ea->update();
        }

    return success;
}

/** retrieve the padString for the cogaEmotionalAttendee with matching uid
 * return false in case of failure, fill string padString and return true otherwise
 */

bool
WASABIEngine::getPADString(std::string& padString, int uid) {
            cogaEmotionalAttendee* ea = getEAfromID(uid);
            if (!ea){
                std::cout << "WASABIEngine::getPADString: uid " << uid << " not found!" << std::endl;
                return false;
            }
            padString = ea->PADstring;
            //std::cout << "WASABIEngine::getPADString: uid " << uid << " with padString \"" << padString << "\" returning true." << std::endl;
            return true;
        }


cogaEmotionalAttendee*
WASABIEngine::getEAfromID(int uid) {
    std::vector<cogaEmotionalAttendee*>::iterator iter_ea;
    for (iter_ea = emoAttendees.begin(); iter_ea != emoAttendees.end(); ++iter_ea){
        cogaEmotionalAttendee* ea = (*iter_ea);
        if (ea->getLocalID() == uid){
            return ea;
        }
    }
    std::cout << "WASABIEngine::getEAFromID: uid " << uid << " not found!" << std::endl;
    return NULL;
}


bool
WASABIEngine::emotionalImpulse(int impulse, int uid) {
    if (impulse > 200 || impulse < -200) {
        std::cout << "WASABIEngine::emotionalImpulse: impulse outside of [-200,200]!" << std::endl;
        return false;
    }
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::emotionalImpulse: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    int temp = ea->getXPos() + impulse;
    //cout << yPos2Reach << " = yPos2Reach! " << endl;
    if (temp > 100) {
        ea->setXPos(100);
    }
    else if (temp < -100) {
        ea->setXPos(-100);
    }
    else {
        ea->setXPos(temp);
    }
    ea->resetForces();
    return true;
}

bool
WASABIEngine::resetToZero(int uid) {
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::emotionalImpulse: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    ea->setXPos(0);
    ea->setYPos(0);
    ea->setZPos(0);
    ea->setPValue(0);
    ea->setAValue(0);
    ea->setDValue(0);
    ea->resetForces();
    return true;
}

bool
WASABIEngine::setXForce(int value, int uid){
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::setXForce: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    ea->setXTens(value);
    return true;
}
bool
WASABIEngine::setYForce(int value, int uid) {
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::setYForce: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    ea->setYTens(value);
    return true;
}
bool
WASABIEngine::setSlope(int value, int uid) {
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::setSlope: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    ea->setSlope(value);
    return true;
}

bool
WASABIEngine::setMass(int value, int uid) {
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::setMass: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    ea->setMass(value);
    return true;
}

bool
WASABIEngine::setUpdateRate(int value, int uid) {
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::setUpdateRate: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    ea->setUpdateRate(value);
    return true;
}

bool
WASABIEngine::setAlpha(int value, int uid) {
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::setAlpha: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    ea->setAlpha(value);
    return true;
}

bool
WASABIEngine::setBeta(int value, int uid) {
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::setBeta: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    ea->setBeta(value);
    return true;
}

bool
WASABIEngine::setFactor(int value, int uid) {
    cogaEmotionalAttendee* ea = getEAfromID(uid);
    if (!ea){
        std::cout << "WASABIEngine::setFactor: No emotionalAttendee with uid " << uid << " found!" << std::endl;
        return false;
    }
    ea->setFactor(value);
    return true;
}

int
WASABIEngine::addEmotionalAttendee(std::string name, std::string globalID) {
    std::cout << "WASABIEngine::addAttendee: requested to ADD '" << name << "' with globalID '" << globalID << "'.." << std::endl;
    int nID = getNextID();
    if (nID == 0){
        std::cout << "WASABIEngine::addEmotionalAttendee: ERROR maximum number of simulations (" << MaxSimulations << ") reached!" << std::endl;
        return 0;
    }
    cogaEmotionalAttendee* newEA = new cogaEmotionalAttendee();
    newEA->setName(name);
    newEA->setGlobalID(globalID);
    emoAttendees.push_back(newEA);
    return newEA->getLocalID();
}

void
WASABIEngine::initAllEAs() {
    std::vector<cogaEmotionalAttendee*>::iterator iter_ea;
    for (iter_ea = emoAttendees.begin(); iter_ea != emoAttendees.end(); ++iter_ea){
        cogaEmotionalAttendee* ea = (*iter_ea);
        if (!initEA(ea)){
            std::cout << "WASABIEngine::initAllEAs(): ERROR with ea '" << ea->getLocalID() << "'!" << std::endl;
        }
    }
}

bool
WASABIEngine::initEA(cogaEmotionalAttendee* ea) {
    if (ea->EmoConPerson->initEmoDyn() && ea->EmoConPerson->initEmoPAD()) {
        return true;
    }
    return false;
}

void
WASABIEngine::setMaxSimulations(int max){
    if (max > 0 && max < 50) {
        MaxSimulations = max;
        std::cout << "MaxSimulations set to " << MaxSimulations << std::endl;
    }
}

int
WASABIEngine::getNextID() {
    if (nextID < MaxSimulations) {
        nextID++;
        return nextID;
    }
    return 0; //i.e. failure code
}
