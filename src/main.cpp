//
// Created by ewen.talleux on 15/02/2024.
//

#include <iostream>
#include <unistd.h>
#include "Parser/Parser.hpp"
#include "Session/Session.hpp"

int main() {
    Parser parser;
    Session session;
    parser.loadFile("../testfile");
    parser.parseContent();
    double loudnessAddingValue = 1;
    double loudness = 42;
    bool alreadyDisplay = false;


    while (true) {
        if (loudness >= 42 || loudness <= 0) {
            loudnessAddingValue *= -1;
        }
        loudness += loudnessAddingValue;
        //session = Session();
        session.loadFromProperties(parser.getSessionProperties());

        session.setLoudness(loudness + loudnessAddingValue);
        session.createValuesMap();
        session.processValuesDistribution();
        session.updateFromValuesMap();

        session.colorizeMap();
        if (!alreadyDisplay) {
            session.display();
            alreadyDisplay = true;
        } else {
            session.redisplay();
        }
        usleep(500000);
    }


    return 0;
}
