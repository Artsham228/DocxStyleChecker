#include <iostream>
#include "pugixml.hpp"
#include "Header.h"
#include <windows.h>
#include <iomanip>
int main() {
    SetConsoleOutputCP(CP_UTF8);
    pugi::xml_document doc;
    pugi::xml_document stl;

    if (!doc.load_file("word/document.xml")) {
        std::cerr << "Error: failed to find document.xml!" << std::endl;
        return 1;
    }
    if (!stl.load_file("word/styles.xml")) {
        std::cerr << "Error: failed to find styles.xml!" << std::endl;
        return 1;
    }
    auto body = doc.child("w:document").child("w:body");
    
    auto offset = 30;
    std::cout << "|Style name                      |  Font              | text      |\n";
    for (auto const& p: body.children("w:p"))

    {
        std::string rawText;
        auto styleId = p.child("w:pPr").child("w:pStyle").attribute("w:val").as_string();
        std::string stlVal = styleId;
        std::string query = "//w:style[@w:styleId='" + stlVal + "']";
        pugi::xpath_node style_in_styles_xml = stl.select_node(query.c_str()); 
    	pugi::xml_node node = style_in_styles_xml.node();
        pugi::xml_node fontNode = node.child("w:rPr").child("w:rFonts");
        pugi::xml_node labelNode = node.child("w:name");

        auto fontName = fontNode.attribute("w:ascii").value();

        auto fontLabel = labelNode.attribute("w:val").as_string();
        for (auto const& run :p.children("w:r")  )
        {
            auto textNode= run.child("w:t");
            rawText += textNode.text().as_string();
            
        }
    	//std::cout << "["<< std::left<< std::setw(offset) << fontLabel << " | " << fontName <<"] "<< rawText<<'\n';
        // 1. Склеюємо все в один рядок
        std::string fullLabel = "[" + std::string(fontLabel) + " | " + std::string(fontName) + "]";

        // 2. Тепер setw(55) спрацює на ВЕСЬ цей рядок
        std::cout << std::left << std::setw(55) << fullLabel << " | " << rawText << std::endl;
    }
    
   

	return 0;
}