#include "PageHistory.h"

PageHistory::PageHistory() : size(0) {
}

PageHistory::~PageHistory() {
}

bool PageHistory::add(Page page) {
	Page newPage = page;
	return (historyTree.insert(newPage) != NULL) ? 1 : 0;
}

bool PageHistory::contains(Page page) {
	return (historyTree.find(page) != NULL) ? 1 : 0;
}

bool PageHistory::contains(URL& url) {
	//Page* toFind = new Page(url);
	Page toFind(url);
	return contains(toFind);
}

int PageHistory::getSize() {
	return historyTree.getSize();
}

void PageHistory::printHistory() const {
	historyTree.printTree();
}

string PageHistory::getXML() {
	return historyTree.printTreeXML();
}

bool PageHistory::Test(ostream& os) {
	bool success = true;
	
	PageHistory ph;
	URL url1("http://www.google.com");
	string des1("DESCRIPTION");
	
	//when I was storing page pointers in page history (better for memory, 
	// but more complicated with accessing values/printing)
	//Page* p1 = new Page(url1, des1);
	Page p1(url1, des1);
	ph.add(p1);
	
	TEST(ph.getSize() == 1);
	TEST(ph.contains(p1));
	
	URL url2("http://yahoo.com");
	string des2("DESCRIPTION 2");
	//Page* p2 = new Page(url2, des2);
	Page p2(url2, des2);
	
	//TEST(!ph.contains(p2));
	
	ph.add(p2);
	
	TEST(ph.getSize() == 2);
	
	URL url3("http://www.google.com");
	//TEST(ph.contains(url3));
	
	//cout << ph.getXML();
	
	return success;
}
