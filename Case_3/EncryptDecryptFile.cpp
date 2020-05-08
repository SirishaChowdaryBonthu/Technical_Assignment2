/*Purpose 	:For Calculating the sum of squares of a given Number
	Language	:C++
	Author  	: Sirisha Chowdary Bonthu
	Date    	: 8/05/2020
	
	
 CASE 3 :Given a sample text file as input, scan all the words in the text file and
a. Create a new file, which encodes all the word in the source file by reversing each word in text
file and replacing all the spaces in between the words with an alpha numeric character.
E.g : This is a sample text
 Siht*si*a*elpmas*txet  Encoded format
 
b. Ask the user to enter a secret key before initiating the encoding sequence

c. Provide the option to decode the file, upon the user’s choice and start the decoding only when
the secret key matches with the one obtained in the previous step to provide the original text
file format. */	

#include"Pch.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<string.h>
using namespace std;

//Method to Reverse a word	
string EncodeDecode:: ReversingWord(string sWordInFile)
{
    //iIndex1 and iIndex2 to iterate from starting to end of word
	iIndex1=0;
	iIndex2=sWordInFile.length()-1;
	while(iIndex1<=iIndex2)
	{
	    sTemp[iIndex1]=sWordInFile[iIndex1];
	    sWordInFile[iIndex1]=sWordInFile[iIndex2];
	    sWordInFile[iIndex2]=sTemp[iIndex1];
	    iIndex1++;
	    iIndex2--;
	    
	}
	return sWordInFile;
    
}
//Method to write Encoded data to file
void EncodeDecode:: WriteEncodeFile(string sfileName,string sNewFile,string sKey,string sAlphaNum)
{
    file.open(sfileName);
    myfile.open(sNewFile);
    myfile<<"key="<<sKey<<endl;
	while(getline(file, sLineInFile))
	{
	    istringstream iss(sLineInFile);
	    while (iss>>sWordInFile)
	    {
	        sWordInFile=ReversingWord(sWordInFile);
		    cout<<sWordInFile<<sAlphaNum;
	        myfile<<sWordInFile<<sAlphaNum;
	        
	    }
	    iIndex2=0;
	    cout<<endl;
	    myfile<<endl;
	    
	}
	file.close();
	myfile.close();
    
}
//Method to Generate Newfile name
string EncodeDecode:: GenerateFileName(string sfileName,string sToReplace,string sToUpdate)
{
    sNewFile = sfileName.c_str();
    size_t sPosToReplc = sNewFile.find(sToReplace);
    sNewFile.replace(sPosToReplc, sToReplace.length(), sToUpdate);
    return sNewFile;
    
}
//Method to Encrypt and Decrypt key
string EncodeDecode:: GetKey(string sKey) {
    //char key = 'K'; //Any char will work
    string OutKey = sKey;
    
    for (iIndex1 = 0; iIndex1 < sKey.size(); iIndex1++)
        OutKey[iIndex1] = sKey[iIndex1] ^ 'I';
    
    return OutKey;
}

//Method to Encrypt data and write to file
void EncodeDecode:: DecodeFile(string sfileName,string sKey)
{
    ifstream file(sfileName);
    if(!file.is_open())
    cout<<"Could not open file"<<endl;
    else
    if(file.is_open())
    {
        sToReplace="_encode.txt";
        sToUpdate="_decode.txt";
        sNewFile=GenerateFileName(sfileName,sToReplace,sToUpdate);
        myfile.open(sNewFile);
        while(getline(file,sLineInFile) )
        {
            size_t pos = sLineInFile.find("=");
			string Keyinfile = sLineInFile.substr(pos+1);
			sKey=GetKey(sKey);
			if(Keyinfile==sKey)
			while(getline(file, sLineInFile))
	       {
	           istringstream iss(sLineInFile);
	           while (getline(iss,sWordInFile,'*'))
	           {
	               sWordInFile=ReversingWord(sWordInFile);
	               cout<<sWordInFile<<" ";
	               myfile<<sWordInFile<<" ";
	               
	           }
	           iIndex2=0;
	           cout<<endl;
               myfile<<endl;
              
	        }
			else
            cout<<"Invalid Password.Enter correct password to Decrypt file."<<endl;
            
        }
        
    }
    file.close();
    myfile.close();
}
//Method used to encode data
void EncodeDecode:: EncodeFile(string sfileName,string sKey)
{
    ifstream file(sfileName);
    if(!file.is_open())
    cout<<"Could not open file"<<endl;
    else if(file.is_open())
    {
        sToReplace=".txt";
        sToUpdate="_encode.txt";
        string sAlphaNum;
        cout<<"Enter alpha numeric to be replaced with space"<<endl;
        cin>>sAlphaNum;
        string sNewFile=GenerateFileName(sfileName,sToReplace,sToUpdate);
        sKey=GetKey(sKey);
        WriteEncodeFile(sfileName,sNewFile,sKey,sAlphaNum);
        
    }
}
//Method to select Encrypt or Decrypt file	  
void EncodeDecode:: SecuredFile(char** cArgVar)
{
    string sEncryptDecrypt=cArgVar[1];
    string sfileName=cArgVar[2];
    string sKey=cArgVar[4];
    if(sEncryptDecrypt=="-e")
    EncodeFile(sfileName,sKey);
    else if(sEncryptDecrypt=="-d")
    DecodeFile(sfileName,sKey);
    else if(sEncryptDecrypt!="e"&& sEncryptDecrypt!="d")
    cout<<"Invalid Input.Enter -h for program usage"<<endl;
}  

int main(int argc,char* argv[])
{
    EncodeDecode obj;
     if (argc==2 && argv[1]=="-h")
		cout<<"Usage:"<<argv[0]<<"-d/-e(decrypt/encrypt) -f [Filename] -k [key]"<<endl;
    else if(argc==6)
    obj.SecuredFile(argv);
	else
	cout<<"Invalid Input.Enter -h for program usage"<<endl;
	return 0;
}
