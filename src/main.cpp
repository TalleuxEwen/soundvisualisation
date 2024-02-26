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
        //Network network;
        while (true) {
            //double *received = network.receive();
            double received[2] = {22, 0};
            session = Session();

            for (auto speaker : parser.getSessionProperties()->getSpeakers()) {
                if (std::get<4>(speaker).size() == 1) {
                    //std::cout << "received[std::get<4>(speaker)[0]] = " << received[std::get<4>(speaker)[0]] << std::endl;
                    parser.getSessionProperties()->setSpeakerLoudness(std::get<0>(speaker), std::get<1>(speaker), received[std::get<4>(speaker)[0]]);
                    //std::cout << "std::get<3>(speaker) = " << std::get<3>(speaker) << std::endl;
                } else {
                    double maxLoudness = 0;
                    for (auto channel : std::get<4>(speaker)) {
                        if (received[channel] > maxLoudness) {
                            maxLoudness = received[channel];
                        }
                    }
                    parser.getSessionProperties()->setSpeakerLoudness(std::get<0>(speaker), std::get<1>(speaker), maxLoudness);
                }
            }
            session.loadFromProperties(parser.getSessionProperties());
            session.createValuesMap();
            session.processValuesDistribution();

            session.colorizeMap();
            if (!alreadyDisplay) {
                session.display();
                alreadyDisplay = true;
            } else {
                session.redisplay();
            }
        }
    } else if (parser.getMode() == LOCAL) {
        session.loadFromProperties(parser.getSessionProperties());

        session.createValuesMap();
        session.processValuesDistribution();

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
