#ifndef PAGE_DOWNLOADER_H
#define PAGE_DOWNLOADER_H

#include "URLInputStream.h"
#include "URL.h"
#include "UnitTest.h"
#include <string>
#include <iostream>

/*
 * PageDownloader.h
 * downloads a web page
 */
class PageDownloader{
	private:
		string* pageText;					//or could be string pageText, but would return a copy in download method...
		
		void putContentsToString (InputStream& stream) {
			while (!stream.IsDone())
				*pageText += stream.Read();
		}
	
	public:
		/*
		 * no-arg constructor
		 */
		PageDownloader();
		 
		/*
		 * destructor
		 */
		~PageDownloader();
		
		/*
		 * downloads a webpage, stores it in a string
		 *  to be used by HTML parser
		 *  (opens a stream with url)
		 *
		 * Parameters:
		 *  url--URL object containing the resolved URL
		 *
		 * Returns:
		 *  a string containing the entire contents of webpage
		 */
		string* download(URL& url);
		
		static bool Test(ostream& os);

};

#endif
