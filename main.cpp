#include <iostream>
#include "pugixml.hpp"
#include "Header.h"

int main() {
    pugi::xml_document stylesDoc;
    
    if (!stylesDoc.load_file("word/styles.xml")) {
        std::cerr << "Не вдалося знайти styles.xml!" << std::endl;
        return 1;
    }

    
    std::string testId = "51"; 
    Style myStyle(testId, stylesDoc);

    std::cout << "--- test Style ---" << std::endl;
    std::cout << "ID : " << testId << std::endl;
    std::cout << "font: " << myStyle.getFontName() << std::endl;
    std::cout << "size: " << myStyle.getFontSize() << " pt" << std::endl;


	return 0;
}