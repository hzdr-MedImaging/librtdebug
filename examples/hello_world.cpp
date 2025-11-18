/*
  librtdebug - C++ thread-safe runtime debugging library
               https://github.com/hzdr-MedImaging/librtdebug
 
  Copyright (C) 2003-2025 hzdr.de and contributors
 
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
 
    http://www.apache.org/licenses/LICENSE-2.0
 
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

/*
 * This is a small hello world example on how to use librtdebug which
 * should demonstrate how easy it is to integrate rtdebug into everyone's
 * projects. By using just a small set of preprocessor macros (defined in
 * rtdebug.h) a user can easily setup his program for outputting very
 * detailed and sophisticated debugging output.
 *
 * And by using an environment variable, this output is then even dynamically 
 * selectable upon startup of the application.
 *
 */

#include <iostream>

// rtdebug main include which will define all our
// preprocessor macros
#include <rtdebug.h>

using namespace std;

// prototypes
void output(const char* text);

// main function
int main(int argc, char* argv[])
{
	int returnCode = EXIT_SUCCESS; // return no error on default

	// for being able to filter the debugging output via
	// an environment variable, a user can use ::init() to
	// define that ENV-variable.
	#if defined(DEBUG)
	CRTDebug::init("hello_world");
	#endif

	// we delay the first function entry marker because of ::init()
	ENTER();

	// we measure the time of the execution from here on
	STARTCLOCK("output() measurement");

	// now we branch into the output() function
	output("Hello to rtDebug!");

	// signal that we are finished
	STOPCLOCK("output() measurement");

	// before we really exit the main function we have to
	// use RETURN() to report the return value to the debug framework
	RETURN(returnCode);

	// for properly cleaning up the debug environment we have to
	// call ::destroy() as the very last method of CRTDebug
	#if defined(DEBUG)
	CRTDebug::destroy();
	#endif

	return returnCode;
}

void output(const char* text)
{
	ENTER();
	bool result = true;

	// for debug purposes we can output the content of a c string
	// via SHOWSTRING()
	SHOWSTRING(text);

	cout << text << endl;

	LEAVE();
}
