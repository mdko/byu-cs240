//sort240.cpp
//sorts lines in a text file
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
int lineCount;
bool r = false;
bool i = false;
bool n = false;
/////////////////////////////////////////////////////////////////////
class line{
	private:
		char* original;
		char* column;
	public:
		//char* column;
		//line(): original(NULL), column(NULL){		//necessary?
		//	return;
		//}
		line(char* str){
			original = new char[strlen(str)+1];		//get the memory
			strcpy(original,str);					//cpy arg to it (p462)
			column = new char[strlen(str)+1];		//wastes space, but simplest
		}
		//contains parsing algorithm
		void getColumnOfInterest(int col){
			char* ptrChr = &original[0];			//BEFORE, doing ...=original, but was wrong...
			bool lastWhite = true;
			int tokenNum = 0;
			while (*ptrChr){						//while not null, parse
				if (!isspace(*ptrChr)){				//if the current char is not a
					if (lastWhite)					// space and last char was white,
						++tokenNum;					// we have a new token
						if (tokenNum == col){
								//column = ptrChr;
							break;					//we found the column, so break while
							}
					lastWhite = false;
					}
				else
					lastWhite = true;
				++ptrChr;
			}
			
			strcpy(column,ptrChr);					//copy stuff from where ptrChr points
			int i = 0;								//  in original on, then cut below
			while (*(column+i)){					//now that we know where the token starts,
				if (isspace(*(column+i))){			// figure out where it should end
					*(column+i) = '\0';				// and put a null char there
					break;							//do I need the break?
				}
				++i;
			}
			//if (n)
			//	atoi(column);
		}
		void displayLine(){
			cout << original << endl;
		}
		char* getColumn(){
			return column;
		}
		void displayTokenOfInterest(){
			cout << column << endl;
		}
};
line* linesArray[1024];								//array of ptrs to line objs--Where to put?
/////////////////////////////////////////////////////////////////////
int order(const char* left, const char* right){
	int l = atoi(left);
	int r = atoi(right);
	if (l<r)
		return -1;
	else if (l == r)
		return 0;
	else
		return 1;
}
/////////////////////////////////////////////////////////////////////
int compare_lines(const void* a, const void* b){

	line* line1 = *((line**)a);						//review why this syntax works
	line* line2 = *((line**)b);
	
	if (n)
		return order(line1->getColumn(), line2->getColumn()); 
	if (i)
		return strcasecmp(line1->getColumn(), line2->getColumn());
	else
		return strcmp(line1->getColumn(), line2->getColumn());
}
/////////////////////////////////////////////////////////////////////
void checkOptions(char* options){
	if (strchr(options,'r')!=NULL)
		r = true;
	if (strchr(options,'i')!=NULL)
		i = true;
	if (strchr(options,'n')!=NULL)
		n = true;
}
/////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]){
	
	//validate command line
	if (argc < 3){
		cout << "USAGE: not enough arguments." << endl;
		return -1;
	}
	
	//open file, see Lecture 4 readfile.cpp
	ifstream file;
	file.open(argv[argc-1]);						//txt file is last argument
	
	if (!file.is_open()){
		cout << "Unable to open file: " << argv[argc-1] << endl;
		return -2;
	}
	
	lineCount = 0;
	char curLine[1024];								//array[evaluates to a pointer to address
	while (file.getline(curLine, sizeof(curLine))){	//  of 1st element] to store line in tmply
		line* newLine = new line(curLine);			//create new line, put on heap
		linesArray[lineCount] = newLine;			//add line obj to array
		++lineCount;
	}
	file.close();
	//there are options included in 3rd argument
	if (argc>3){
		checkOptions(argv[1]);
	}
	//print lines, free heap data
	for (int i=0; i<lineCount; i++){
		linesArray[i]->getColumnOfInterest(atoi(argv[argc-2]));	//change column char in argv to int
	}
	
	qsort(linesArray, lineCount, sizeof(line*), compare_lines);	//make sure to do sizeof(line*) 
	// and not size of line-- array of ptrs, not lines
	if (r){
		for (int i=(lineCount-1); i>=0; i--){
			linesArray[i]->displayLine();
			delete [] linesArray[i];					//delete whatever lA[i] pts to/clean up
			linesArray[i] = NULL;	
		}
	}
	else{
		for (int i=0; i<lineCount; i++){
			//cout << linesArray[i]->getColumn() << endl;
			linesArray[i]->displayLine();
			delete [] linesArray[i];					//delete whatever lA[i] pts to/clean up
			linesArray[i] = NULL;	
		}
	}
	return 0;
}
