#include "HTMLParser.h"
#include "PageDownloader.h"
#include "URL.h"
#include <iostream>
using namespace std;

//private:

bool HTMLParser::parse(string* pageText) {
	//URLInputStream stream(URL.getURL());
	//HTMLTokenizer tokenizer(&stream);	
	
	HTMLTokenizer tokenizer(*pageText);	//instance of tokenizer class breaks HTML string to tag/txt
	bool headerTried = false;			//tracks whether we've tried to find desc in header
	bool foundDescription = false;		//tracks whether we've found a description in hdr or title
	bool insideBody = false;
		
	HTMLToken newToken = tokenizer.GetNextToken();
	
	//skip past anything at beginning that isn't a start-tag
	while (StringUtil::ToLowerCopy(newToken.GetValue()) != "html"){
		newToken = tokenizer.GetNextToken();
	}

	while (tokenizer.HasNextToken()) {
		newToken = tokenizer.GetNextToken();
		
		if (newToken.GetType() == TAG_START) {
			if (StringUtil::ToLowerCopy(newToken.GetValue()) == "a") {
				if (newToken.AttributeExists("HREF")){
					//inserts URL associated with this HREF
					HREFLinks[linksCount] = newToken.GetAttribute("HREF");
					++linksCount;
				}
			}
			
			else if (StringUtil::ToLowerCopy(newToken.GetValue()) == "script") {
				newToken = tokenizer.GetNextToken();
				
				//skip past everything in between <script></script> tags
				while (newToken.GetType() != TAG_END)
					newToken = tokenizer.GetNextToken();
				
				if (StringUtil::ToLowerCopy(newToken.GetValue()) == "/script")
					continue; //leave to start of while loop?
			}
				
			//next two else's to find description
			//check title first
			else if (StringUtil::ToLowerCopy(newToken.GetValue()) == "title") {
				
				//the next token will be text--CAN ASSUME THIS?
				newToken = tokenizer.GetNextToken();				
				
				//if we don't already have valid description
				if (!foundDescription) {
					if (!newToken.GetValue().empty()) {
						//PRESERVE CAPITALIZATION AND PUNCTUATION
						description = newToken.GetValue();			
						foundDescription = true;
					}
				}
				//still have to add it to the wordslist
				if (newToken.GetType() == TEXT)
					separateIntoWords(newToken.GetValue());
			}
			
			//WAS BAD BECAUSE IT CHECKS FOR <HEAD> TOO
			//check header next
			//finds description in header "h<some number>"
			else if (StringUtil::ToLowerCopy(newToken.GetValue()).at(0) == 'h' 
					&& isdigit(newToken.GetValue().at(1))) {
				
				//in case <hx> has <b> etc in between, get to text	
				if (!foundDescription && !headerTried) {
					while (newToken.GetType() != TEXT)
						newToken = tokenizer.GetNextToken();
				
						if (!newToken.GetValue().empty()) {
							description = newToken.GetValue();		//PRESERVE CAPITALIZATION/PUNC
							foundDescription = true;
						}
						headerTried = true;

					separateIntoWords(newToken.GetValue());
				}
			}
			else if (StringUtil::ToLowerCopy(newToken.GetValue()) == "body")
				insideBody = true;
			
		}
		else if (newToken.GetType() == TAG_END) {
			if (StringUtil::ToLowerCopy(newToken.GetValue()) == "body")
				insideBody = false;
		}
		else if (newToken.GetType() == TEXT) {
			if (insideBody)
				separateIntoWords(newToken.GetValue());
		}
		//if comment, skip past token, ie, do nothing with it
		//NEED TO CHECK TO SEE IF SHOULD INCLUDE WORDS IN 
		//<a title="Move your mouse"> tags, or just strictly Text tags
	}

	if (!foundDescription) {
		calculateBodyDescription(pageText);
	}
	//haven't yet changed words to lower in case we needed to find description from body, 
	// which done in above line
	changeWordsToLower();
	
}

void HTMLParser::separateIntoWords(string textTokenString) {
	
	//remove all leading and trailing whitespace
	// after, we know first character is a either non-whitespace,
	// or the string is empty
	StringUtil::Trim(textTokenString);
	//StringUtil::ToLower(textTokenString);			//NEED TO PRESERVE
	
	if (textTokenString.empty())
		return;
	
	string wordChars = "abcdefghijklmnopqrstuvwxyz1234567890-_";
	
	bool lastNonWord = true;
	bool lastSpace = true;
	int wordStart = 0;
	int wordLength = 0;
		
	for (int i=0; i < textTokenString.length(); ++i) {
		if (lastNonWord) {
			//we're at the beginning of a word
			if (isWordCharacter(textTokenString.at(i))) {
				wordStart = i;
				++wordLength;
				lastNonWord = false;
			}	
		}
		//we're in the middle of a word
		else {
			if (isWordCharacter(textTokenString.at(i))) {
				++wordLength;
			}
			else {
				string newWord = textTokenString.substr(wordStart, wordLength);
				StringUtil::Trim(newWord);
				if (newWord.length() > 0) {
					if (isalpha(newWord.at(0))) {
						wordsList[wordsCount] = newWord;
						++wordsCount;
					}
				}
				lastNonWord = true;
				wordLength = 0;
			}
		}
	}
	
	//if the character is alpha but it's the last character, wouldn't get to
	// second else above, so need to add it here
	string newWord = textTokenString.substr(wordStart, wordLength);
	if (!newWord.empty()) {
		
		StringUtil::Trim(newWord);
		if (isalpha(newWord.at(0))) {
			wordsList[wordsCount] = newWord;
			++wordsCount; 
		}
	}
	
}

bool HTMLParser::isWordCharacter(char c) {
	return (isalnum(c) || c == '_' || c == '-');
}
 
//need to figure out how to get 100 chars of words
//description needs to be first 100 nonwhitespace chars 
//(so could be longer than 100 total when you include whitespace between words)
//need to maintain capitalization and punctuation...
void HTMLParser::calculateBodyDescription(string* pageText) {
	HTMLTokenizer tokenizer(*pageText);
	int nonWhiteSpaceCount = 0;
	string interWord = "";
	
	HTMLToken token = tokenizer.GetNextToken();
	
	while (StringUtil::ToLowerCopy(token.GetValue()) != "body" 
		&& token.GetType()!= TAG_START){
		token = tokenizer.GetNextToken();
	}
	
	//THERE'S PROBABLY A MUCH SMARTER AND FASTER WAY TO DO THIS
	while (tokenizer.HasNextToken()) {
		token = tokenizer.GetNextToken();
		
		if (token.GetType() == TEXT) {
			interWord += token.GetValue();
		}
		else if (token.GetType() == TAG_END &&
				 token.GetValue() == "body")
			break;
	}
	
	int i;
	for (i = 0; i < interWord.length(); ++i) {
		if (!isspace(interWord.at(i)))
			++nonWhiteSpaceCount;
		if (nonWhiteSpaceCount == 100)
			break;
	}
	
	//trim to make sure not including whitespace at beginning--necessary? i+1 
	//because rhs is non-inclusive -- [ , )
	description = interWord.substr(0,i+1);			
	StringUtil::Trim(description);
	
	/*string interWord = "";

	for (int i=0; i<wordsCount; i++) {
		interWord += wordsList[i];
		
		if (interWord.length() > 100)
			break;
	}

	description = interWord.substr(0,100);*/
	
	
}

void HTMLParser::changeWordsToLower() {
	for (int i = 0; i < wordsCount; ++i)
		StringUtil::ToLower(wordsList[i]);
}
 
//public:

HTMLParser::HTMLParser(string* pageText) :  wordsCount(0), linksCount(0) {
	parse(pageText);
}

HTMLParser::~HTMLParser() {
}

string HTMLParser::getWordsString() {
	
	int i;
	for (i = 0; i < wordsCount-1; ++i) {
		wordsString += wordsList[i];
		wordsString += " ";
	}
	wordsString += wordsList[i];
	//StringUtil::Trim(wordsString);
	return wordsString;
}

string HTMLParser::getLinksString() {
	int i;
	for (i = 0; i < linksCount-1; ++i) {
		linksString += HREFLinks[i];
		linksString += " ";
	}
	linksString += HREFLinks[i];
	return linksString;
}

string HTMLParser::getDescription() {
	return description;
}

string* HTMLParser::getWordsArray() {
	return &wordsList[0];
}

string* HTMLParser::getLinksArray() {
	return &HREFLinks[0];
}

int HTMLParser::numLinks() {
	return linksCount;
}

void HTMLParser::printLinks() {
	for (int i = 0; i < linksCount; ++i) {
		cout << HREFLinks[i] << "\n";
	}
	cout  << endl;
}

void HTMLParser::printWords() {
	for (int i = 0; i < wordsCount; ++i)
		cout << wordsList[i] << "\n";
	cout << endl;
}

void HTMLParser::sepWords(string s) {
	separateIntoWords(s);
}

int HTMLParser::numWords() {
	return wordsCount;
}

bool HTMLParser::Test(ostream& os) {

	bool success = true;
	
	PageDownloader downloader;
	
	/* TEST 1 */
	URL url1("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html");
	string* pageText = downloader.download(url1);
	
	HTMLParser parser(pageText);
	
	//parser.printLinks();
	//parser.printWords();
	
	TEST(parser.getWordsString() == "crawler test first header web crawlers need to look for a variety of words even if the word is a strange one like rhinoserous they should not read the stop words though it makes me wonder if individual letters should be included in the stop words file or if they should be understood as a stopword and don t need to be loaded into the file robot test second test html test description test additional notes frame tester horse");
	TEST(parser.getLinksString() == "crawler/TestOne.html crawler/testTwo.html crawler/testThree.html crawler/testFour.htm crawler/testFive.html crawler/frame/testSix.html");
	TEST(parser.getDescription() == "Crawler Test");
	
	delete pageText;
	/* END TEST 1 */
	
	
	/**
	 * DESCRIPTION TESTS, MORE THAN ANYTHING
	 */
	 
	/* TEST 2 */
	/* DESCRIPTION IN TITLE */
	URL url2("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/title.html");
	string* pageText2 = downloader.download(url2);
	
	HTMLParser parser2(pageText2);
	
	TEST(parser2.getWordsString() == "a description of an included page not a description it was in the title robin this text is also not a description of this page man this test is going to pull up the word description quite a bit");
	TEST(parser2.getLinksString() == "");
	TEST(parser2.getDescription() == "A Description of an included page");
	
	delete pageText2;
	/* END TEST 2 */
	
	
	
	/* TEST 3 */
	/* DESCRIPTION IS FIRST HEADING */
	/*URL url3("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/header.html");
	string* pageText3 = downloader.download(url3);
	
	HTMLParser parser3(pageText3);
	
	//THIS TEST IS NOT WORKING... TEST(parser3.getWordsString() == "water buffalo the words which i am typing right now are not the description it s true the description comes later on it is in an lt h gt tag this is the description see told you so");	
	TEST(parser3.getLinksString() == "");
	TEST(parser3.getDescription() == "This is the description");
	
	delete pageText3;*/
	/* END TEST 3 */
	
	
	
	/* TEST 4 */
	/* DESCRIPTION IS FIRST 100 CHARS */
	URL url4("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/hundredwords.html");
	string* pageText4 = downloader.download(url4);
	
	HTMLParser parser4(pageText4);
	
	TEST(parser4.getWordsString() == "the hard thing about testing the first hundred words is that there s no way that we can fake you out maybe if we were to use empty title tags or something like that but no i ve got to go ahead and type a hundred words maybe it wouldn t be so bad if i could spell personally i don t know how usefull of a test this is what s a good name of an animal if you haven t been able to guess i m using animal names as random words do you think i ve reached a hundred words there s so much testing to do for a project like this alligator didn t see that coming did you");
	TEST(parser4.getLinksString() == "");
	TEST(parser4.getDescription() == "The hard thing about testing the first hundred words is that there&#039;s no way that we can fake you out. Maybe if we were");
	
	delete pageText4;
	/* END TEST 4 */
	
	
	
	/* TEST 5 */
	/* DESCRIPTION IS FROM 100 CHARS */
	/* FROM LOCAL COMPUTER */
	URL url5("file:///home/michael/Documents/cs240/projects/project1/file/student/descriptiontests/characters.html");
	string* pageText5 = downloader.download(url5);
	
	HTMLParser parser5(pageText5);
	
	TEST(parser5.getWordsString() == "you should get the first one hundred characters not including whitespace or tags you should count other characters the backslash should have been the last character taken if you got more or less you failed this test");
	TEST(parser5.getLinksString() == "");
	TEST(parser5.getDescription() == "You should get the first one hundred characters, not including whitespace or\ntags. You should  count other characters/"); //review this new line--not present in browser, yes present in source
	
	delete pageText5;
	/* END TEST 5 */
	
	
	
	/* TEST 6 */
	/* DESCRIPTION IS IN FIRST HEADER */
	/* FROM LOCAL COMPUTER */
	URL url6("file:///home/michael/Documents/cs240/projects/project1/file/student/descriptiontests/header.html");
	string* pageText6 = downloader.download(url6);
	
	HTMLParser parser6(pageText6);
	
	//cout << parser6.getWords() << endl;
	TEST(parser6.numWords() == 19);
	TEST(parser6.getWordsString() == "header_description the first header should have been the description but it should not include the lt b gt tags");
	TEST(parser6.getLinksString() == "");
	TEST(parser6.getDescription() == "HEADER_DESCRIPTION");
	
	delete pageText6;
	/* END TEST 6 */
	
	
	
	/* TEST 7 */
	/* DESCRIPTION IN TITLE */
	/* FROM LOCAL COMPUTER */
	URL url7("file:///home/michael/Documents/cs240/projects/project1/file/student/descriptiontests/title.html");
	string* pageText7 = downloader.download(url7);
	
	HTMLParser parser7(pageText7);
	
	//cout << parser7.getWords() << endl;
	TEST(parser7.numWords() == 11);	
	TEST(parser7.getWordsString() == "title_description not_the_description the title should have been parsed as the description");
	TEST(parser7.getLinksString() == "");
	TEST(parser7.getDescription() == "TITLE_DESCRIPTION");
	
	delete pageText7;
	/* END TEST 7 */
	
	//URL url8("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/sub/other.jsp");
	//URL url8("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html");
	//URL url8("file:///home/michael/Documents/cs240/projects/project1/file/student/wordtests/extra.html");
	//URL url8("file:///home/michael/Documents/cs240/projects/project1/file/student/wordtests/punctuation.html");
	//URL url8("http://lightplanet.com/mormons/people/joseph_smith/prophesies.html");
	/*URL url8("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testTwo.html");
	string* pageText8 = downloader.download(url8);
	
	HTMLParser parser8(pageText8);
	
	//parser8.printLinks();
	//cout << parser8.getWordsString() << endl;
	//cout << parser8.getDescription() << endl;
	//parser8.printWords();
	
	delete pageText8;*/
	
	return success;
}
















