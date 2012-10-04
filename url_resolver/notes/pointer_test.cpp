if (testing){
		char * baseV = argv[1];
		
		cout << base << endl;
		cout << relative << endl;
		
		cout << strlen(base) << endl;
		cout << strlen(relative) << endl;
		
		/*
		 * three ways of accessing each element in the c-string/array
		 */
		for (int i=0; i<strlen(base); i++){			//access via pointers; strlen computes # of elements, not size
			cout << *(base+i);			
		}
		cout << endl;
		
		for (int i=0; i<strlen(base); i++){			//access via array notation
			cout << base[i];
		}
		cout << endl;
		
		while (*base)								//access via pointers--change where base points to by the end
			cout << *base++;
		cout << endl;
		
		//cout << base << endl;						//base points to end of array, not beginning anymore
		cout << baseV << endl;
		
		for (int i=0; i<5; i++){					//access via pointers
			cout << *(baseV++) << endl;				//increment pointer that hold address; doesn't increment what pointer points to
		}
		///cout << baseV << endl;					//baseV points to end of array, not beginning
	}
