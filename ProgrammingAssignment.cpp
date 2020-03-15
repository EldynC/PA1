//============================================================================
// Name        : ProgrammingAssignment1.cpp
// Author      : Eldyn Castillo
// Date	       : 01/29/2020
// Professor   : Nhut Nguyen
// Description : A program that verifies if a url is is valid and displays which parts of
//				 the url are not valid.
//============================================================================
//Extra comment here
//new comment
#include <iostream>
#include "version.h"
using namespace std;
//function prototypes
void hasProtocol(string);
int  countPeriods(string);
void hasDomain(string);
void getPort(string);
void getFilePath(string);
void getParameters(string);

static double version = 1.2;
bool isError = false; //global boolean variable that switches to true if any part of the program has an error, that way it ONLY displays the parts of the url that are incorrect

int main() {
	displayVersion(version);
	string url; //This will hold the enter url entered by the user
	//This loop runs until the user enters 1
	do{ //beginning of loop
	cout << "Please enter a url, press 1 when you are done: " << endl;
	cin >> url; //grab the url
	if(url!="1") //checks to see if the user entered 1
		hasDomain(url); //calls the hasDomain function
	else
		cout << "Exiting" << endl; //if the user presses 1 the program exits
	}while(url!="1"); //end of loop
	
	return 0;
}

void hasProtocol(string url) {
	string protocol_IDs[4] = { "http:", "https:", "ftp:", "ftps:" }; //This array holds all valid protocols
	//This loop loops through the protocol_IDs array and checks to see if the beginning of the url matches
	for (int i = 0; i < 4; i++) {

		if ((url.find(protocol_IDs[i]) != std::string::npos) && (isError == false)) { //This checks to see if the url contains a protocol ID as well as checks the boolean value isError, which indicates if there is an error in the program
																					  //If there is no issue, it will print the protocol
			cout << "Protocol: " << protocol_IDs[i].substr(0, (protocol_IDs[i].size() - 1)) << endl;
			break;

		} else if ((i == 3) && (url.find(protocol_IDs[i]) == std::string::npos)) { //Checks to see if the url has no protocol and outputs what the user entered and tells them that they don't have a valid protocol
			isError = true;
			string invalidStr = url.substr(0, url.find(':')); //this variable holds the invalid String the user entered at the beginning of the url
			cout << "Protocol: " << invalidStr << " is not a valid protocol" << endl;
		}

		else if(isError == true) //if there is an error in the program, nothing will happen and it will not display the protocol, regardless if the protocol is correct
		{

		}
	}

}

//this function counts the amount of periods in the given url
int countPeriods(string url)
{
	int count = 0; //count variable holds the number of  periods
	for(int i = 0; i < (int)url.size(); i++)
	{
		if(url[i] == '.')
			count++;
	}

	return count;
}
/*This function is a comprehensive function that determines what will the output be based on if there is an error in the url , whether or not the user put a port number and whether or not the user put parameters
 * If there is an error in the url, depending on where the error is, it will output where the error is in the url.
 * This function assumes that the user entered the correct "://" syntax and also assumes that the url is in the correct order.
 *
 * */
void hasDomain(string url) {
	int numPeriods = countPeriods(url); //this will hold the number of periods in the url, will be used to determine whether the domain follows x.y.z format
	if(url.find(".html") == std::string::npos || (url.find(".htm") == std::string::npos)) //determines whether or not the ending ".htm" or ".html" is in the filePath, if it isn't then it sets isError to true
	{
		isError = true;
	}
	string validDomains[5] = { "com", "net", "edu", "biz", "gov" }; //contains all valid domain endings
	string findDomain; //will store the domain string
	string x; //Store x from domain
	string y; //Store y from domain
	string z; //Store z from domain

	for (int i = 0; i < 5; i++) { //runs through the validDomains array

		if (url.find(validDomains[i]) != std::string::npos && (isError == false)) { //runs the following block of code if there are no errors in the url and there is a valid domain in the url
			findDomain = url.substr(url.find("//") + 2); //sets findDomain to the beginning of the domain
			string temp = findDomain; //temporary string that will be used to determine how many periods are in the domain
			x = temp.substr(0, temp.find('.')); //finds the x part of the domain

			findDomain = findDomain.substr(findDomain.find('.') + 1); //sets the domain to the middle part of the domain
			temp = findDomain; //store findDomain
			y = temp.substr(0, temp.find('.')); //finds the y part of the domain
			findDomain = findDomain.substr(findDomain.find('.')); //finds the next period to set up for getting the z part of the domain

			if ((temp.find(':') != std::string::npos)) {//runs the following block of code if it finds a semicolon, meaning the user entered a port number

				temp = findDomain; //store findDomain
				z = temp.substr(1, temp.find(':') - 1); //stores z part of the domain
				findDomain = findDomain.substr(findDomain.find(':')); //stores the part of the url thats from the port number onward
				for (int i = 0; i < 5; i++) { //runs through the validDomains again to check if z matches any of the domains
					if (z == validDomains[i] && (findDomain.find('/') != std::string::npos)) { //runs the following code block if it finds a matching domain and there is a beginning / for the directory
						string temp2 = url.substr(url.find(x)); //temp2 stores the url string from the beginning of x(beginning of domain) onward
						hasProtocol(url); //calls hasProtocol function
						if(isError == false) //if there is no error, print domain
						{
							cout << "Domain: " << temp2.substr(0, temp2.find(':')) << endl;
						}
						getPort(findDomain); //run getPort function
						break;//break out of the loop
					}

					else if ((i == 4) && (z != validDomains[i])) { //runs this block of code if z does not match any of the domains in the validDomain array
							isError = true; //sets isError to true, signifying that there is an error with the url
							string temp2 = url.substr(url.find(x)); //temp2 stores the url string from the beginning of x(beginning of domain) onward
							hasProtocol(url); //call the hasProtocol function
							cout << "Domain: ." << z << " is an invalid domain name" << endl; //prints that the domain the user entered is incorrect
							getPort(findDomain); //moves on to get the port and determine if anything remaining is incorrect
					}

				}
			}
			//This entire block of code is the same thing as the previous if statement only that there is no port so it just skips grabbing the port
			else if ((temp.find('/') != std::string::npos)) {
				temp = findDomain;
				z = temp.substr(1, temp.find('/') - 1);
				findDomain = findDomain.substr(findDomain.find('/'));
				for (int i = 0; i < 5; i++) {
					//cout << "z is " << z << endl;
					if (z == validDomains[i] && (isError == false)) {
						string temp2 = url.substr(url.find(x));
						hasProtocol(url);
						if(isError == false)
						{
							cout << "Domain: " << temp2.substr(0, temp2.find('/')) << endl;
							getFilePath(findDomain);
						}

						break;
					}

					else if ((i == 4) && (z != validDomains[i])) {
						isError = true;
						cout << "Domain: " << z << " is an invalid domain name" << endl;
					}
				}
			}
			else{
				cout << "error" << endl;
			}
			break;
		}
		//This if statement block runs if the url does not contain any of the valid domains, follows the same code process as the previous if statement
		else if ((i == 4) && (url.find(validDomains[i]) == std::string::npos) && (isError == false)) {
			findDomain = url.substr(url.find("//") + 2);
			string temp = findDomain;
			x = temp.substr(0, temp.find('.'));
			findDomain = findDomain.substr(findDomain.find('.') + 1);

			temp = findDomain;
			y = temp.substr(0, temp.find('.'));
			findDomain = findDomain.substr(findDomain.find('.'));
			 if ((temp.find(':') != std::string::npos)) {
				temp = findDomain;
				z = temp.substr(1, temp.find(':') - 1);
				findDomain = findDomain.substr(findDomain.find(':'));
				for (int i = 0; i < 5; i++) {
					if (z == validDomains[i] && isError == false) {
						string temp2 = url.substr(url.find(x));
						hasProtocol(url);
						cout << "Domain: " << temp2.substr(0, temp2.find(':'))	<< endl;
						getPort(findDomain);
						break;
					}

					else if ((i == 4) && (z != validDomains[i])) {
						isError = true;
						cout << "Domain: " << z << " is an invalid domain name" << endl;
						getPort(findDomain);
					}
				}
			}

			else if ((temp.find('/') != std::string::npos)) {
				temp = findDomain;
				z = temp.substr(1, temp.find('/') - 1);
				findDomain = findDomain.substr(findDomain.find('/'));
				for (int i = 0; i < 5; i++) {
					if (z == validDomains[i] && isError == false) {
						string temp2 = url.substr(url.find(x));
						hasProtocol(url);
						cout << "Domain: " << temp2.substr(0, temp2.find('/')) << endl;
						getFilePath(findDomain);
						break;
					}

					else if ((i == 4) && (z != validDomains[i])) {
						isError = true;
						cout << "Domain: " << z << " is an invalid domain name" << endl;
						getPort(findDomain);
					}
				}
			}

		}

//This else if block runs of the number of periods in the entire url is only equal to 2(when it should be 3) or if there is an error in the url
		else if(numPeriods == 2 || isError==true)
		{
			//This if block basically runs the same as the if statement previously, determining if the url has a valid domain
			if (url.find(validDomains[i]) != std::string::npos) {
				findDomain = url.substr(url.find("//") + 2);
				string temp = findDomain;
				x = temp.substr(0, temp.find('.'));
				findDomain = findDomain.substr(findDomain.find('.') + 1);
				temp = findDomain;
				y = temp.substr(0, temp.find('.'));
				findDomain = findDomain.substr(findDomain.find('.'));
				//if block for if there is a port
				if ((temp.find(':') != std::string::npos)) {

					temp = findDomain;
					z = temp.substr(1, temp.find(':') - 1);
					findDomain = findDomain.substr(findDomain.find(':'));

					for (int b = 0; b < 5; b++) {
						//Biggest difference from the nonError if block, will not display the domain but still go ahead and run through getting the port and file path
						if (z == validDomains[b] && (findDomain.find('/') != std::string::npos)) {


							string temp2 = url.substr(url.find(x));
							getPort(findDomain);
							temp2 = temp2.substr(temp2.find('/'));
							getFilePath(temp2);
							break;
						}
						//this else if block prints out if the domain name is invalid
						else if ((b == 4) && (z != validDomains[b])) {

								isError = true;
								string temp2 = url.substr(url.find(x));
								cout << "Domain: ." << z << " is an invalid domain name" << endl;
								getPort(findDomain);
						}
					}
				}
				//if block for if there is no port and there is a file path
				else if ((temp.find('/') != std::string::npos)) {
					temp = findDomain;
					z = temp.substr(1, temp.find('/') - 1);
					findDomain = findDomain.substr(findDomain.find('/'));
					for (int i = 0; i < 5; i++) {
						if (z == validDomains[i]) {
							string temp2 = url.substr(url.find(x));
							getFilePath(findDomain);
							break;
						}

						else if ((i == 4) && (z != validDomains[i])) {
							isError = true;
							cout << "Domain: " << z << " is an invalid domain name" << endl;
							getPort(findDomain);
						}
					}
				}
				else{
					cout << "Cannot determine port or file path" << endl; //executes if the user did not enter a port or file path, meaning the url is completely invalid
				}
				break;
			}
			//this else if block runs if it is at the end of the loop and there is no valid domain, similar to previous blocks.
			else if ((i == 4) && (url.find(validDomains[i]) == std::string::npos)) {
				findDomain = url.substr(url.find("//") + 2);
				string temp = findDomain;
				x = temp.substr(0, temp.find('.'));
				findDomain = findDomain.substr(findDomain.find('.') + 1);
				temp = findDomain;
				y = temp.substr(0, temp.find('.'));

					//Special if block, if it cannot find a period(which would determine if the url follows x.y.z format) it will tell the user that the domain format is incorrect
					if(findDomain.find('.') == std::string::npos)
					{
						isError = true;
						cout << "Domain: The domain format is incorrect, should be x.y.z" << endl;
						break;
					}
					else{
						findDomain = findDomain.substr(findDomain.find('.'));
					}

			     //If block displays nothing if the domain is correct and display z if it is not a valid domain ending, then gets the port
				 if ((temp.find(':') != std::string::npos)) {
					temp = findDomain;
					z = temp.substr(1, temp.find(':') - 1);
					findDomain = findDomain.substr(findDomain.find(':'));

					for (int i = 0; i < 5; i++) {
						if (z == validDomains[i]) {
							string temp2 = url.substr(url.find(x));
							getPort(findDomain);
							temp2 = temp2.substr(temp2.find('/'));
							break;
						}

						else if ((i == 4) && (z != validDomains[i])) {
							isError = true;
							hasProtocol(url);
							cout << "Domain: " << z << " is an invalid domain name"	<< endl;
							getPort(findDomain);
						}
					}
				}
				 //If block displays nothing if the domain is correct and display z if it is not a valid domain ending, then gets the file path
				else if ((temp.find('/') != std::string::npos)) {
					temp = findDomain;
					z = temp.substr(1, temp.find('/') - 1);
					findDomain = findDomain.substr(findDomain.find('/'));
					for (int i = 0; i < 5; i++) {
						if (z == validDomains[i]) {
							string temp2 = url.substr(url.find(x));
							break;
						}

						else if ((i == 4) && (z != validDomains[i])) {
							isError = true;
							hasProtocol(url);
							cout << "Domain: " << z << " is an invalid domain name" << endl;
							getPort(findDomain);
						}
					}
				}

			}

			//final else block if it cannot find x.y.z format at all
			else
			{
				isError = true;
				hasProtocol(url);
				findDomain = url.substr(url.find("//") + 2);

				if(findDomain.find(':') != std::string::npos)
				{
					string temp = findDomain;
					findDomain = findDomain.substr(0,findDomain.find(':'));
					int numPeriodsInFindDomain = countPeriods(findDomain);
					if(numPeriodsInFindDomain != 2)
					{
						cout << "Domain: " << findDomain << " is invalid, should be x.y.z format" << endl;
						temp = temp.substr(temp.find(':'));
						getPort(temp);
					}
					else
					{
						temp = temp.substr(temp.find(':'));
						getPort(temp);
					}

				}

				else if(findDomain.find('/') != std::string::npos)
				{
					string temp = findDomain;
					findDomain = findDomain.substr(0,findDomain.find('/'));
					int numPeriodsInFindDomain = countPeriods(findDomain);
					if(numPeriodsInFindDomain != 2)
					{
						cout << "Domain: " << findDomain << " is invalid, should be x.y.z format" << endl;
						temp = temp.substr(temp.find('/'));
						getPort(temp);
					}
					else{
						temp = temp.substr(temp.find('/'));
						getPort(temp);
					}
				}
				break;
			}

		}

	}

}

//This function assumes that the url starts at the colon of the url after getting the domain and determines whether or not the port is too big, otherwise it displays the port and moves onto getting the filepath
//If there is not port the function will just invoke getting the file path
void getPort(string url) {
	string getPort; //stores the port in string format
	long long  portToNum; //stores the port in long long format

//if block that runs block of code it can find a / indicating file path
if(url.find('/') != std::string::npos)
{
	if (url[0] != '/'){ //if the url doesn't start with a file path(if it starts with a semicolon) it will grab the port number and convert it to integer format to determine whether it is in range
		getPort = url.substr(1, url.find("/") - 1); //grab port
		portToNum = stoll(getPort); //convert port to number format

	}

	//if block that determines if the port is in range also checking to make sure the url starts with a semicolon
	if (((portToNum < 1) || (portToNum > 65535)) && (url[0]) == ':') {
		isError = true; //setting program error to true
		cout << "Port: Port number must be between 1 and 65535" << endl; //outputting that the port isn't within the correct bounds
		string filePath = url.substr(url.find('/'));
		getFilePath(filePath); //gets file path
	} else if(isError == false) { //if there is no error, will output the port number and go find the file path
		cout << "Port: " << portToNum << endl;
		string filePath = url.substr(url.find('/'));
		getFilePath(filePath);
	}
	else if(isError == true && url.find('/') != std::string::npos) //if there is an error but also a file path, display nothing and determine if there is an error in the file path
	{
		string filePath = url.substr(url.find('/'));
		getFilePath(filePath);

	}

}

//this if block runs if it cannot find the beginning of a file path and prints the port and determines that the file path is incorrect
else
{
	string filePathString = url.substr(1); //stores file path string
	for(int i = 0; i < (int)filePathString.size(); i++)
	{

		if(isdigit(filePathString[i])) //if the filepath string is a digit(basically getting the port) it will store it in getPort
		{
			getPort = getPort + filePathString[i];
		}

		//if the error hasn't been presented yet and the character in the string is not a number then this is where the file path is skewed, meaning it does not start with a /
		if((!isdigit(filePathString[i])) && (isError == false))
		{
			cout << "Port: " << getPort << endl; //print port
			filePathString = filePathString.substr(i); //store the filepath string
			getFilePath(filePathString); //call getFilePath
			break; //break out of the loop because the error has been determined
		}
	}




}
}

//This function gets the file path unless it is invalid, otherwise it will print an error message
void getFilePath(string url) {
	string validEndings[2] = { ".htm", ".html" }; //stores valid file path endings
	string filePath; //stores filepath
	//if the url doesn't start with a /, which indicates a file path, there is an error and prints an error message
	if (url[0] != '/') {
		isError = true;
		cout << "File Path: This is not a valid file path" << endl;
	}
	//otherwise grab the file path
	else {
		for (int i = 0; i <= 1; i++) {
			//if the valid ending matches for the url it will print the full filepath and then grab the parameter
		if (url.find(validEndings[i]) != std::string::npos && (isError == false)) {
				filePath = url.substr(0, url.find('?')); //stores filepath from url
				cout << "File path: " << filePath << endl; //prints filepath
				break;

			}
			//block executes if file path ending is invalid
			else if ((i == 1) && (url.find(validEndings[i]) == std::string::npos)) {
				isError = true;
				cout << "File path: Invalid File Path" << endl;
				if (url.find('?') != std::string::npos) { //if it can find a parameter, move onto determing whether parameter is valid or not
					string passProtocol = url.substr(url.find('?'));
					getParameters(passProtocol);
					break;
				}
				break;

			}
		}
		//if there is no error and there is a parameter, grab the parameter
		if (url.find('?') != std::string::npos && (isError == false)) {
			string passProtocol = url.substr(url.find('?'));
			getParameters(passProtocol);
		}

	}
}

//This function gets the parameters based on the fact that the url starts with a ?, if it doesn't nothing prints
void getParameters(string url)
{
	string parameter; //stores parameter
	//if statement runs block if the first character of the url is a ? and there is no error with the program
	if(url[0] == '?' && (isError == false))
	{
		parameter = url.substr(1);
		cout << "Parameters: " << parameter << endl;
	}
	else{ //else do nothing

	}


}
/*
Test Cases
Valid:
	https://cs.utdallas.edu:80/directory/faculty/people.html?name=Robert
	ftps://cs.utdallas.edu:80/directory/faculty/people.html?name=Robert
	ftp://cs.utdallas.edu/directory/faculty/people.html?name=Robert
	http://cs.utdallas.edu/directory/faculty/people.html
	https://webapp4.asu.edu/catalog/classlist.html


Invalid:
	html://cs.utdallas.edu/directory/faculty/people.html?name=Robert
	ftppps://cs.utdallas.edu/directory/faculty/people.test?name=Robert
	ftppps://cs.edu/directory/faculty/people.test?name=Robert
	httpz://cs.utdallas.edu:80000/people.html?name=Robert
	httpz://utdallas.edu:80000/people.html?name=Robert
	httpz://utdallas.edu:8080/people.html?name=Robert
	httpz://utdallas.edu:8080/people.chickensandwich?name=Robert
	httpz://cs.utdallas.adu:948021984021/people.htx
	ftps://cs.edu/people.aba?name=Robert

*/



