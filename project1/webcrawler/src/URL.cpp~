//URL.cpp
#include "URL.h"
#include "UnitTest.h"
#include "StringUtil.h"
using namespace std;
	
URL::URL() {
	//value = new string("DEFAULT CONSTRUCTOR STRING");
	value = "DEFAULT CONSTRUCTOR STRING";
}

//only for first URL from argv[], which is already resolved
URL::URL(char* startURL) {
	value = startURL;
	removeFrags(value);
	//removeFragsAndQueries(value);
}

URL::URL(char* baseURL, char* otherURL) {
	
	//string base(baseURL);
	string other(otherURL);
	
	//if the other url is already resolved
	if (StringUtil::IsPrefix(other, "http://") ||
		StringUtil::IsPrefix(other, "file://")) {
		value = other;
		//removeFragsAndQueries(value); 
		removeFrags(value);
	}
	else {
		
		resolve(baseURL, otherURL);
		//removeFragsAndQueries(value);
		removeFrags(value);
	}
}

URL::URL(string& base, string& other){

	//if the other url is already resolved
	if (StringUtil::IsPrefix(other, "http://") ||
		StringUtil::IsPrefix(other, "file://"))
		value = other;
	else {
		//removeFragsAndQueries(base);
		removeFrags(base);
		char baseURL[200];						//REVIEW HOW THIS WORKS, versus just "char* baseURL";
		char otherURL[200];
	
		strcpy(baseURL, base.c_str());			//don't just convert base to a cstring via c_str()
		strcpy(otherURL, other.c_str());		// because returns a const, need to change it
	
		resolve(baseURL, otherURL);
	}
	//removeFragsAndQueries(value);
	removeFrags(value);
}

//copy constructor
URL::URL(const URL& other) : 
	value(other.value) {
}

//assignment operator, makes a copy of its argument
//returns reference to oneself
URL& URL::operator =(const URL& other) {
	if (&other != this) {
		//delete value;
		value = other.value;
	}
	return *this;
}

bool URL::operator ==(const URL& other) const {
	return (value.compare(other.value) == 0) ? 1 : 0;	
}

bool URL::operator <(const URL& other) const {			//function is const so g++ knows we cannot modify member data
	return (value.compare(other.value) < 0) ? 1: 0;
}

bool URL::operator !=(const URL& other) const {
	return (value.compare(other.value) == 0) ? 0 : 1;
}

URL::~URL() {
	//delete value;						//FIGURE OUT HOW TO NOT DELETE TWICE, ONCE IN ANOTHER CALL
} 

string URL::getURL() const {
	return /* * */value;				//no star because value is the string object, not pointer to string object
}

ostream& operator <<(ostream& s, URL& u) {
	s << /* * */(u.getURL());				//WAS that value returns pointer to string on heap, need to derefence, but not anymore. need to call member function?
	return s;
}

void URL::resolve(char* baseURL, char* relURL) {
	
	char* base = baseURL;
	char* relative = relURL;
	char bas[200];
	char rel[200];
	memcpy(bas, base, strlen(base)+1);					//so I don't mess with original char*?
	memcpy(rel, relative, strlen(relative)+1);
	
	base = &bas[0];
	relative = &rel[0];
	
	char* netLocation = base+7;
	if ((strchr(netLocation,'/')) == NULL)
		strcat(base,"/");
	char* pathLocation = strchr(netLocation, '/');
	char* lastSlash = strrchr(base,'/');
	
	while (strncmp(relative,".",1)==0){
		if (strncmp(relative,"./",2)==0){
			*lastSlash = '\0';
			relative += 2;								
		}
		else if (strncmp(relative,"../",2)==0){
			*lastSlash = '\0';
			lastSlash = strrchr(base,'/');
			*lastSlash = '\0';
			relative += 3;
		}
	}
	if (strncmp(relative,"/",1)==0){
		if ((strncmp(base,"file://",7))==0)
			*(base+7)='\0';
		else
			*pathLocation = '\0';
		strcat(base,rel);
	}
	else if (strncmp(relative,"#",1)==0){
		strcat(base,relative);
	}
	else{
		*lastSlash = '\0';
		strcat(base,"/");
		strcat(base,relative);
	}
	value = base;							//store c-string value in string object
}

void URL::removeFragsAndQueries(string& s) {
	string noQuery = s.substr(0, s.find("?"));					//if a query present, get everything before it; if not present, normal string
	string noFrag = noQuery.substr(0, noQuery.find("#"));		//no +1 because don't want to include "#" in string to be evaluated
	s = noFrag;
}

void URL::removeFrags(string& s) {
	string noFrag = s.substr(0, s.find("#"));
	s = noFrag;
}

bool URL::Test(ostream& os) {
	bool success = true;
	
	char* base1 = "http://www.cnn.com/news/financial/index.html";
	char* base2 = "file:///news/financial/index.html";
	char* test1 = "/images/nasdaq.jpg";
	char* test2 = "./images/nasdaq.jpg";
	char* test3 = "../images/nasdaq.jpg";
	char* test4 = "#HEADLINES";
	char* test5 = "images/nasdaq.jpg";
	char* test6 = "./../.././stuff";
	
	URL url10(base1);						//created on stack, so dot operator, not ->, used below
	URL url11(base1, test1);
	URL url12(base1, test2);
	URL url13(base1, test3);
	URL url14(base1, test4);
	URL url15(base1, test5);
	URL url16(base1, test6);
	
	URL url20(base2);
	URL url21(base2, test1);
	URL url22(base2, test2);
	URL url23(base2, test3);
	URL url24(base2, test4);
	URL url25(base2, test5);
	URL url26(base2, test6);
	
	TEST(url10.getURL() == "http://www.cnn.com/news/financial/index.html");
	TEST(url11.getURL() == "http://www.cnn.com/images/nasdaq.jpg");
	TEST(url12.getURL() == "http://www.cnn.com/news/financial/images/nasdaq.jpg");
	TEST(url13.getURL() == "http://www.cnn.com/news/images/nasdaq.jpg");
	TEST(url14.getURL() == "http://www.cnn.com/news/financial/index.html");
	TEST(url15.getURL() == "http://www.cnn.com/news/financial/images/nasdaq.jpg");
	TEST(url16.getURL() == "http://www.cnn.com/stuff");
	
	TEST(url20.getURL() == "file:///news/financial/index.html");
	TEST(url21.getURL() == "file:///images/nasdaq.jpg");
	TEST(url22.getURL() == "file:///news/financial/images/nasdaq.jpg");
	TEST(url23.getURL() == "file:///news/images/nasdaq.jpg");
	TEST(url24.getURL() == "file:///news/financial/index.html");
	TEST(url25.getURL() == "file:///news/financial/images/nasdaq.jpg");
	TEST(url26.getURL() == "file:///stuff");
	
	URL url1("http://cs-online.cs.byu.edu/cs240/hello#STUFF");
	URL url2("http://cs-online.cs.byu.edu/cs235/hello#STUFF");
	URL url3("http://cs-online.cs.byu.edu/cs240/mamamia.htm#STUFF");
	URL url4("http://cs-online.cs.byu.edu/cs240/yo.html?name=joe&age=12");
	URL url5("http://cs-online.cs.byu.edu/cs240/yo.jv?name=joe&age=12");
	
	TEST(url1.getURL() == "http://cs-online.cs.byu.edu/cs240/hello");
	TEST(url2.getURL() == "http://cs-online.cs.byu.edu/cs235/hello");
	TEST(url3.getURL() == "http://cs-online.cs.byu.edu/cs240/mamamia.htm");
	TEST(url4.getURL() == "http://cs-online.cs.byu.edu/cs240/yo.html?name=joe&age=12");
	TEST(url5.getURL() == "http://cs-online.cs.byu.edu/cs240/yo.jv?name=joe&age=12");
	
	URL url30("http://www.google.com");
	TEST(url30.getURL() == "http://www.google.com");
	
	URL url31("http://www.google.com", "http://www.yahoo.com");
	TEST(url31.getURL() == "http://www.yahoo.com");
	
	string base40("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testFive.html");
	string rel40("scale.php?sec=");
	URL url40(base40, rel40);
	TEST(url40.getURL() == "http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/scale.php?sec=");
	
	string base41("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/scale.php?sec=");
	string rel41("scale.php?sec=tortoise");
	URL url41(base41, rel41);
	TEST(url41.getURL() == "http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/scale.php?sec=tortoise");
	
	string base42("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testTwo.html");
	
	string rel42("fine.html");
	string rel43("../../../~jrv28/index.html");
	string rel44("sub/sub.html");
	string rel45("/~cs240ta/crawler_tests/crawler/root.html");
	string rel46("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/sub/other.jsp");
	string rel47("http://www.angelfire.com/theforce/jrv28/");
	string rel48("http://star.cs.byu.edu/~snell/Classes/CS684/");
	string rel49("../crawler/makefile.php");
	string rel50("/~cs240ta/crawler_tests/crawler/makefile.php#comments");
	string rel51("#hook");
	string rel52("http://www.gamespot.com/index.html");
	
	URL url42(base42, rel42);
	URL url43(base42, rel43);
	URL url44(base42, rel44);
	URL url45(base42, rel45);
	URL url46(base42, rel46);	
	URL url47(base42, rel47);
	URL url48(base42, rel48);
	URL url49(base42, rel49);
	URL url50(base42, rel50);
	URL url51(base42, rel51);
	
	/*cout << url42.getURL() << endl;
	cout << url43.getURL() << endl;
	cout << url44.getURL() << endl;
	cout << url45.getURL() << endl;
	cout << url46.getURL() << endl;
	cout << url47.getURL() << endl;
	cout << url48.getURL() << endl;
	cout << url49.getURL() << endl;
	cout << url50.getURL() << endl;
	cout << url51.getURL() << endl;*/
	
	string base43("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testTwo.html#hook");
	
	URL url53(base43, rel42);
	URL url54(base43, rel44);
	URL url55(base43, rel45);
	URL url56(base43, rel46);
	URL url57(base43, rel47);
	URL url58(base43, rel48);
	URL url59(base43, rel49);
	URL url60(base43, rel50);
	URL url61(base43, rel51);
	URL url62(base43, rel52);
	URL url63(base43, rel43);
	
	
	/*cout << url53.getURL() << endl;
	cout << url54.getURL() << endl;
	cout << url55.getURL() << endl;
	cout << url56.getURL() << endl;
	cout << url57.getURL() << endl;
	cout << url58.getURL() << endl;
	cout << url59.getURL() << endl;
	cout << url60.getURL() << endl;
	cout << url61.getURL() << endl;
	cout << url62.getURL() << endl;
	cout << url63.getURL() << endl;*/
	//need to add bad tests
	
	return success;
	
}
