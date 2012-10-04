//OutputGenerator.cpp

#include "OutputGenerator.h"
#include "UnitTest.h"
using namespace std;

void OutputGenerator::generateHistory(PageHistory* pageHistory) {

	outFile << "\t<pages>\n";
	
	//call each page's getXMLinfo method, add it to outFile
	//for each page,
	outFile << pageHistory->getXML();

	outFile << "\t</pages>\n";
}

void OutputGenerator::generateWords(WordIndex* index) {

	outFile << "\t<index>\n";

	//call each word's getXMLinfo method
	//for each word
	outFile << index->getXML();

	outFile << "\t</index>\n";
}

//public:

OutputGenerator::OutputGenerator(char* file, URL& startURL) {
	outFile.open(file);
	url = startURL;
}

/*
* destructor
*/
OutputGenerator::~OutputGenerator() {

}


void OutputGenerator::generate(PageHistory* pageHistory, WordIndex* index) {
	
	outFile << "<website>\n";

	outFile << "\t<start-url>\n";
	outFile << "\t\t" << StringUtil::EncodeToXmlCopy(url.getURL()) << "\n";
	outFile << "\t</start-url>\n";

	generateHistory(pageHistory);
	generateWords(index);

	outFile << "</website>";
	
	outFile.close();
}
