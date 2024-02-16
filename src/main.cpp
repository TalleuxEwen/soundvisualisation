//
// Created by ewen.talleux on 15/02/2024.
//

#include <iostream>
#include "Parser/Parser.hpp"
#include "Session/Session.hpp"

int main() {
    std::cout << "\033[48;2;200;255;0m    Hello World\033[0m" << std::endl;
    Parser parser;
    Session session;
    parser.loadFile("../testfile");
    parser.parseContent();

    session.loadFromProperties(parser.getSessionProperties());



    return 0;
}
