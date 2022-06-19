#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;


/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void createHistogram() {
	ifstream inFs;
	ofstream outfs;
	string food = "";
	string frequency = "";
	int frequencyNum = 0;
	string histoCount = "";

	inFs.open("frequency.dat");

	//check if file can be opened
	if (!inFs.is_open()) {
		cout << "frequency.dat file could not be opened";
	}

	//read line by line to recieve data
	while (inFs >> food >> frequency) {		
		frequencyNum = stoi(frequency);
		//add symbol to frequency
		for (int i = 1; i <= frequencyNum; i++) {
			histoCount.append("*");
		}
		//display food item with number of astericks
		cout << food << " " << histoCount << endl;
		//reset hostogram symbol
		histoCount = "";
	}
	//close the file
	inFs.close();
}

void main()
{

	int userInput = 0;
	int userChoice = 0;
	string frequencyChoice = "";

	cout << "Hello User! Please select an option below" << endl;
	for (;;) {
		//display menu
		cout << setw(54) << setfill('*') << "\n";
		cout << "*" << "    1: Find frequency of all items purchased       *" << endl;
		cout << "*" << "    2: Find frequency of individual selection      *" << endl;
		cout << "*" << "    3: Produce a histogram for items purchased     *" << endl;
		cout << "*" << "    4: Exit                                        *" << endl;
		cout << "*" << "    Enter your selection as a number 1, 2, 3, or 4 *" << endl;
		cout << setw(54) << setfill('*') << "\n";
		//take user input
		cin >> userChoice;

		//type check userInput
		if (cin.fail()) {
			cout << "Please enter an integer 1-4" << endl;
		}
		else {
			switch (userChoice) {
			case 1:
				cout << "Finding Frequency of all items..." << endl;
				CallProcedure("PrintFrequencyAll");
				break;
			case 2:
				cout << "enter item to find frequency of: " << endl;
				cin >> frequencyChoice;
				cout << "Finding Frequency of... " << frequencyChoice << endl;
				callIntFunc("PrintFrequencyOne", frequencyChoice);
				break;
			case 3:
				cout << "Creating frequency.dat file..." << endl;
				CallProcedure("createFreqFile");
				cout << "displaying your requested histogram..." << endl;
				createHistogram();
				break;
			case 4:
				cout << "exiting...";
				return;
			default:
				cout << "Please enter a valid response" << endl;
			}
		}
		//clear cin for next input
		cin.clear();
		cin.ignore();
	}
	return;
}