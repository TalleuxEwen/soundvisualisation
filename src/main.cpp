//
// Created by ewen.talleux on 15/02/2024.
//

#include <iostream>
#include <unistd.h>
#include "Parser/Parser.hpp"
#include "Session/Session.hpp"
#include "Network/Network.hpp"

int main(int argc, char **argv) {
    Parser parser;
    Session session;
    parser.parseArguments(argc, argv);
    parser.loadFile(parser.getFilename());
    parser.parseContent();
    double loudnessAddingValue = 0.3;
    double loudness = 42;
    bool alreadyDisplay = false;

    if (parser.getMode() == REMOTE) {
        Network network;
        while (network.isConnected()) {
            double *received = network.receive();
            session.loadFromProperties(parser.getSessionProperties());
            parser.getSessionProperties()->setSpeakerLoudness(0, 42);

        }
    } else if (parser.getMode() == LOCAL) {
        parser.getSessionProperties()->setSpeakerLoudness(1, 0);
        parser.getSessionProperties()->setSpeakerLoudness(0, 42);
        session.loadFromProperties(parser.getSessionProperties());


        //session.setLoudness(loudness + loudnessAddingValue);
        session.createValuesMap();
        session.processValuesDistribution();
        //session.updateFromValuesMap();

        session.colorizeMap();
        session.display();
    }

    /*while (true) {
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
        usleep(100000);
    }*/


    return 0;
}
