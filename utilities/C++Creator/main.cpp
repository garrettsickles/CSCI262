//
//	C++Creator.cpp
//	C++ Project Creator
//
//  Created by Garrett Frank Sickles on 10/7/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

int main() {
	string name;
	string path;
	string class_buffer;
	string main_buffer;

	queue<string> classes;

	cout << "Please enter a name for your new project:\n";
	cin >> name;
	cout << endl;

	do {
		cout << "Please enter the Path to your new project:\n";
		cin >> path;
		cout << endl;
	} while(system(("mkdir " + path + "/" + name).c_str()));

	cout << "Please enter class names. Type \"done\" when finished:\n";
	while(true) {
		cin >> class_buffer;
		if(class_buffer == "done")
			break;
		else if(class_buffer != "main")
			classes.push(class_buffer);
		else
			cout << "ERROR: Class name cannot be \"main\"\n";
	}
	while(!classes.empty()) {
		class_buffer = "echo '#pragma once\n\nclass " + classes.front() + " {\nprivate:\n\t\n\npublic:\n\t" + classes.front() + "();\n\t~" + classes.front() + "();\n};' > " + path + "/" + name + "/" + classes.front() + ".h";
		system(class_buffer.c_str());
		class_buffer = "echo '#include \"" + classes.front() + ".h\"\n\n" + classes.front() + "::" + classes.front() + "() {\n}\n\n" + classes.front() + "::~" + classes.front() + "() {\n}' > " + path + "/" + name + "/" + classes.front() + ".cpp";
		system(class_buffer.c_str());
		main_buffer += ("#include \"" + classes.front() + ".h\"\n"); 
		classes.pop();
	}
	class_buffer = "echo '" + main_buffer + "#include <iostream>\n\nusing namespace std;\n\nint main() {\n\t\n}\n\n' > " + path + "/" + name + "/main.cpp";
	system(class_buffer.c_str());
}