#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#include "Line.h"
#include "Parser.h"

#include <QList>

QList <Line> Parser::parse(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Couldn't open log file");
    }

    QList <Line> logs;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        Line logLine = parseLine(line);
        if (!logLine.m_line.empty()) 
        {
            logs << logLine;
        }
    }
    return logs;
}

void Parser::setRegex(const std::string& rawRegex) 
{
    m_rawRegex = rawRegex;
}

Line Parser::parseLine(const std::string& line) 
{
    std::regex re(m_rawRegex);
    std::smatch match;

    if (std::regex_search(line, match, re))
    {
        Line line;
        for (size_t i = 1; i < match.size(); ++i)
        {
            line.m_line << match.str(i).c_str();
        }
        return line;
    }
    return {};
}