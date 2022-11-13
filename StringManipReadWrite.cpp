// Source(s) of logic assistance:  
// Gaddis, T. (2018). Starting out with C++:
// From control structures through objects. Pearson. 
// Inserting chars into a string
// https://stackoverflow.com/questions/3223302/c-insert-char-to-a-string
// Reading line by line with fstream
// https://copyprogramming.com/guide/how-to-read-file-line-by-line-using-for-loop-in-c
// Removing substrings
// https://thispointer.com/how-to-remove-substrings-from-a-string-in-c/

#include <iostream> // To use cin/cout
#include <iomanip>  // To access setw for output width
#include <cmath>    // To access power function for calculations
#include <string>   // To implement to_string function
#include <fstream>  // To utilize ifstream, ofstream, fstream
#include <ctime>    // Access random number generator
using namespace std;

// Global Constant Initialization
const string TITLE = "String Manipulator Functions Program";
const string AUTHOR_LINE = "By Forrest Moulin";

// Function prototypes to notify compiler
string fixName(string n);
string fixSSN(string sSN);
string fixPhone(string phoneNumber);
string fixAddress(string address);
string fixCity(string city);
string fixState(string state);

string extractField(string& s);

// Concatenate field and comma to a string
void buildLine(string& s, string field);

// Create output file stream object
// cout for console
// fout for output file
ofstream fout;

int main()
{
	// Dynamic Variable Initialization
	// Create input file stream object
	ifstream fin;
	string fullName, sSN,
		phoneNumber, address, city, state, line,
		zip;
	// Program Logic
	// File paths for input/output.txt
	string txtFilePath =
		"C:\\Users\\UserName\\Path\\To.FAKENAMES.TXT";
	string outFilePath =
		"C:\\Users\\UserName\\Path\\To.OUTPUT.TXT";

	// Program Logic
	// Use the txt/output file paths as args
	// to open the input/output stream file objects
	fin.open(txtFilePath);
	fout.open(outFilePath);

	// End program in event of file read/write failures
	if (fin.fail())
	{
		cout << "File open failure:" << endl
			<< txtFilePath << endl;
		fin.close();
		fout.close();
		return 0;
	}
	if (fout.fail())
	{
		cout << "File output failure:" << endl
			<< outFilePath << endl;
		fin.close();
		fout.close();
		return 0;
	}
	// Console visibility
	cout << fixed << setprecision(2)
		<< TITLE << endl
		<< AUTHOR_LINE << endl << endl;
	// Print to output file
	fout << fixed << setprecision(2)
		<< TITLE << endl
		<< AUTHOR_LINE << endl << endl;

	cout << "Input file read successfully :)" << endl
		<< "Data reformatted to Comma Separate Values (CSV)" 
		<< endl << endl;
	fout << "Comma Separated Values (CSV)" << endl << endl;
	
	// Getline from fin while there are still
	// string lines to be read
	while (getline(fin, line))
	{
		fullName = extractField(line);
		sSN = extractField(line);
		phoneNumber = extractField(line);
		address = extractField(line);
		city = extractField(line);
		state = extractField(line);
		zip = line;
		line = "";
		
		// Fix variable formatting
		fullName = fixName(fullName);
		sSN = fixSSN(sSN);
		phoneNumber = fixPhone(phoneNumber);
		address = fixAddress(address);
		city = fixCity(city);
		state = fixState(state);
		
		// Buildline concatenates in reverse order
		buildLine(line, state);
		buildLine(line, city);
		buildLine(line, address);
		buildLine(line, phoneNumber);
		buildLine(line, sSN);
		buildLine(line, fullName);
		line += zip;
		
		// Print formatted line on each iteration
		cout << line << endl;
		fout << line << endl;
	}
	cout << endl << "Output TXT file successfully created :)" 
		<< endl << "Thanks for choosing Forrest's Green Industries."
		<< endl << "Until next time!" << endl;
	fout << endl << "(c) 2022 Forrest's Green Industries";
	
	// Close file stream objects
	fin.close();
	fout.close();
}
// Converts firstName lastName to 
// lastName,firstName format
string fixName(string name)
{
	string firstName, lastName;
	int lastNameIndex = 0;
	for (int i = 0; i < name.length(); i++)
	{	// If last name index not reached
		if (lastNameIndex == 0)
		{
			if (i == 0)
			{	// Capitalized first char
				name[0] = toupper(name[0]);
			}
			// Last name index begins 1 char
			// after the space char, so skip 
			// the space
			if (name[i] == ' ')
			{
				lastNameIndex = i + 1;
				// Proceed to next iteration in loop, which 
				// is the beginning of last name at index i.
				continue;
			}
			else
			{
				// Add each char to 1st name
				firstName += name[i];
			}
		}
		// And if the index is updated,
		// add appropriate char to last name
		if (lastNameIndex != 0)
		{
			// Add each char to last name
			lastName += name[i];
		}
	}
	return lastName + "," + firstName;
}
// Return string in XXX-XX-XXXX format
string fixSSN(string sSN)
{	// Inserts '-' 1 time at index 3 & 6
	sSN.insert(3, 1, '-');
	sSN.insert(6, 1, '-');
	return sSN;
}
// Returns string in XXX-XXX-XXXX format
string fixPhone(string phoneNumber)
{	// Inserts '-' 1 time at index 3 & 7
	phoneNumber.insert(3, 1, '-');
	phoneNumber.insert(7, 1, '-');
	return phoneNumber;
}
// Capitalizes 1st char of each address word
string fixAddress(string address)
{
	for (int i = 0; i < address.length(); i++)
	{	// Capitalize 1st letter in address
		if (i == 0)
		{
			address[0] = toupper(address[0]);
		}
		// If preceding char is space,
		// capitilize next letter
		else if (i > 0 && address[(i - 1)] == ' ')
		{
			address[i] = toupper(address[i]);
		}
	}
	return address;
}
// Capitalizes 1st char of each city word
string fixCity(string city)
{
	for (int i = 0; i < city.length(); i++)
	{	// Capitalize 1st letter in city
		if (i == 0)
		{
			city[0] = toupper(city[0]);
		}
		// If preceding char is space,
		// capitilize next letter
		else if (i > 0 && city[i - 1] == ' ')
		{
			city[i] = toupper(city[i]);
		}
	}
	return city;
}
// Capitalizes all chars in state
string fixState(string state)
{
	// Capitalize state chars
	state[0] = toupper(state[0]);
	state[1] = toupper(state[1]);
	return state;
}
// Returns extracted field from line str
// reference parameter. Field is then deleted
// from original line string.
string extractField(string& str)
{
	string extraction = "";
	//string strCopy = str;
	for (int i = 0; i < str.length(); i++)
	{
		// If # is found
		if (str[i] == '#')
		{	// Then exit loop
			break;
		}
		extraction += str[i];
	}
	// Erase the substring beginning at 
	// index 0, for the length of the extracted
	// substring (removes extraction and # from str)
	str.erase(0, extraction.length() + 1);
	return extraction;
}
// Concatenates a field and comma to the line str
void buildLine(string& str, string field)
{
	// Add field to string, followed by comma
	field[0] = toupper(field[0]);
	str = field + "," + str;
}
/*
* FAKENAMES.TXT FILE
* john smith#165980076#8148337965#3rd & state st#erie#pa#16506
* martin gardner#164905543#4403542700#5244 heisley rd#mentor#oh#44123
* sarah vendetti#164879987#3302541122#29 millhaven st.#akron#oh#44532
* judy golumbiewski#194409976#7163347654#6187 fillmore ave#rochester#ny#07654
* terry merz#193976554#8002435799#19876 elm avenue#manchester#mo#63166
* kenisha jones#198432265#9193610419#902 east taylor rd#apex#nc#27709
* phil yee#176409976#6308602682#1976 wacker drive#chicago#il#60191
* jean caron#167453321#9738874700#1429 delben street#whippany#nj#07981
* sandy alicea#176419006#3054428202#12 la habana east#miami#fl#33134
* rob williams#206337765#3342715450#9854 fremont blvd#montgomery#al#36109
* jancy hilfiger#201876987#8148817654#3012 state st#pittsburgh#pa#1501
*/

/*
* CONSOLE OUTPUT
* String Manipulator Functions Program
* By Forrest Moulin
*
* Input file read successfully :)
* Data reformatted to Comma Separate Values (CSV)
*
* Smith,John,165-98-0076,814-833-7965,3rd & State St,Erie,PA,16506
* Gardner,Martin,164-90-5543,440-354-2700,5244 Heisley Rd,Mentor,OH,44123
* Vendetti,Sarah,164-87-9987,330-254-1122,29 Millhaven St.,Akron,OH,44532
* Golumbiewski,Judy,194-40-9976,716-334-7654,6187 Fillmore Ave,Rochester,NY,07654
* Merz,Terry,193-97-6554,800-243-5799,19876 Elm Avenue,Manchester,MO,63166
* Jones,Kenisha,198-43-2265,919-361-0419,902 East Taylor Rd,Apex,NC,27709
* Yee,Phil,176-40-9976,630-860-2682,1976 Wacker Drive,Chicago,IL,60191
* Caron,Jean,167-45-3321,973-887-4700,1429 Delben Street,Whippany,NJ,07981
* Alicea,Sandy,176-41-9006,305-442-8202,12 La Habana East,Miami,FL,33134
* Williams,Rob,206-33-7765,334-271-5450,9854 Fremont Blvd,Montgomery,AL,36109
* Hilfiger,Jancy,201-87-6987,814-881-7654,3012 State St,Pittsburgh,PA,15011
*
* Output TXT file successfully created :)
* Thanks for choosing Forrest's Green Industries.
* Until next time!
*/

/*
* OUTPUT.TXT FILE CREATED
* String Manipulator Functions Program
* By Forrest Moulin
*
* Comma Separated Values (CSV)
*
* Smith,John,165-98-0076,814-833-7965,3rd & State St,Erie,PA,16506
* Gardner,Martin,164-90-5543,440-354-2700,5244 Heisley Rd,Mentor,OH,44123
* Vendetti,Sarah,164-87-9987,330-254-1122,29 Millhaven St.,Akron,OH,44532
* Golumbiewski,Judy,194-40-9976,716-334-7654,6187 Fillmore Ave,Rochester,NY,07654
* Merz,Terry,193-97-6554,800-243-5799,19876 Elm Avenue,Manchester,MO,63166
* Jones,Kenisha,198-43-2265,919-361-0419,902 East Taylor Rd,Apex,NC,27709
* Yee,Phil,176-40-9976,630-860-2682,1976 Wacker Drive,Chicago,IL,60191
* Caron,Jean,167-45-3321,973-887-4700,1429 Delben Street,Whippany,NJ,07981
* Alicea,Sandy,176-41-9006,305-442-8202,12 La Habana East,Miami,FL,33134
* Williams,Rob,206-33-7765,334-271-5450,9854 Fremont Blvd,Montgomery,AL,36109
* Hilfiger,Jancy,201-87-6987,814-881-7654,3012 State St,Pittsburgh,PA,15011
*
* (c) 2022 Forrest's Green Industries
*/
