#pragma once

#include <fstream>

void startSvgFile(std::ofstream &file)
{
    file << "<svg" << '\n'
         << "width=" << '"' << "21000mm" << '"' << '\n'
         << "height=" << '"' << "29700mm" << '"' << '\n'
         << "viewBox=" << '"' << "0 0 21000 29700" << '"' << '\n'
         << "xmlns=" << '"' << "http://www.w3.org/2000/svg" << '"' << '\n'
         << "xmlns:svg=" << '"' << "http://www.w3.org/2000/svg" << '"' << ">" << '\n';
}

void endSvgFile(std::ofstream &file){
    file << "</svg>\n";
}
