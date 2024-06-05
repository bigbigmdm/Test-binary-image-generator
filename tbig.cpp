#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
int main(int argc, char* argv[])
{
   int fileSize, addrSize, txtSize, i, j, k, curPos, hiDigit;
   cout << "Test binary image generator for programmer devices." << endl;
   if (argc > 2)
   {
       cout << "File name = " << argv[1] << "   Size = " << argv[2] << " bytes." << endl;
       fileSize = strtol(argv[2], NULL, 10);
       if ((fileSize < 1) || (fileSize > 134217728))
       {  
	  cout << "File size is too big!" << endl;
	  return -1;
       }   
       addrSize = 0;
       j = fileSize;
       hiDigit = 1;
       while (j > 1)
       {
		   j = j / 16;
		   addrSize ++;
		   hiDigit = hiDigit * 16;   
	   }
	   int digits[addrSize];	   
	   txtSize = 16 - addrSize - 4;
       ofstream file(argv[1]);
       
       if (!file)
       {
           cout << "File not opened!" << endl;
           return 0;
       }
       curPos = 0;
       k = 0x40;
       while (curPos < fileSize)
       {
		   //String
		  file.put('<');
		  file.put('0');
		  file.put('x');


          //calculate digits
		  i = hiDigit / 16;
		  for (j=addrSize - 1; j>=0; j--)
		  {
			  digits[j] = (curPos / i) % 16;
			  i = i / 16;
		  }
          for (j = addrSize -1; j >=0; j--)
          {
			 if (digits[j] < 10) digits[j] = digits[j] + 0x30;
		     else digits[j] = digits[j] + 0x37;
		     file.put (digits[j]);  
		  }
		 
		  file.put('>');
		  for (i = 0; i < txtSize; i++)
		  {
			  file.put(k);
			  k ++;
			  if (k > 0x7e) k = 0x40;
		  }
		  curPos = curPos + 16;    
	   }      
       file.close();
       cout << "Done!" << endl;   
   }
   else cout << "Use: tbig <File name> <File size>\nExample: tbig 25q32.bin 4194304\n" << endl;
}	

