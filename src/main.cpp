//
// Created by ewen.talleux on 15/02/2024.
//

#include <iostream>
#include "Parser/Parser.hpp"
#include "Session/Session.hpp"

int main() {
    Parser parser;
    Session session;
    parser.loadFile("../testfile");
    parser.parseContent();

    session.loadFromProperties(parser.getSessionProperties());
    session.createValuesMap();
    session.processValuesDistribution();
    session.updateFromValuesMap();

    session.colorizeMap();
    session.display();

    return 0;
}
