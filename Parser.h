#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#include "Line.h"

#include <QList>

class Parser
{
public:
    QList<Line> parse(const std::string& filename);
    void setRegex(const std::string& rawRegex);
private:
    Line parseLine(const std::string& line);
    std::string m_rawRegex = R"(\[(\d{4}\-\d{2}\-\d{2} \d{2}:\d{2}:\d{2}\.\d{3})\] \[(0x[\dabcdef]{1,})\] \[(DEBUG|ERROR|WARNING|INFO)\] (.*))";
    std::string m_exampleRegext = R"(\[.*\]) (.*)";
};