# librtdebug

**librtdebug** is a small but powerful debugging library for C++ developers.  
Its purpose is to provide a set of C-language macro definitions that can be easily inserted into all kinds of applications. These macros call internal class methods of the debugging library, which then output the desired data during program execution.

The library automatically takes care of the correct indentation of the output, providing an easy way to visually follow program flow and track potential problems via standard output devices.

In addition, librtdebug can detect whether it is being called from different threads and uses different indentation levels and other variations to make it easy to recognize when output originates from another thread context.

## Features

- Small and easy macro-based interface
- Fully object-oriented design and implementation using C++
- Thread-safe implementation allowing you to track the output of individual threads
- Highly portable implementation due to the use of **Qt**

## Requirements

As the library is fully written in C++, you will need at least a modern, up-to-date C++ compiler, preferably **GCC**. In addition, it requires the **Qt** library to be installed during a debugging session. Note, that if you compile your program, which uses **librtdebug**, without debugging you won't require Qt at all during runtime. This just during a debugging session you will require **Qt** to be installed.

> **Note:**  
> The library itself does **not** use any Qt classes nor link against Qt libraries at runtime. Qt is only required for the build system. This means librtdebug can be used with non-Qt applications as well.

## Building from Source

1. Make sure you have:
   - A C++ compiler (e.g. GCC)
   - **Qt 5+** (including `qmake`)

2. Clone the repository:
   ```bash
   git clone https://github.com/hzdr-MedImaging/librtdebug.git
   cd librtdebug
   ```

3. Build the library:
   ```bash
   make
   ```
   After a successful build, you should obtain a static or shared library (depending on your configuration) that you can link against in your C++ projects.

## Usage Overview

1. Add the librtdebug headers to your project’s include path.
2. Include the appropriate header file(s) in the C or C++ source files where you want to add debugging output.
3. Use the provided macros to emit debug output from within your code. The macros will:
   - Automatically handle indentation based on call depth
   - Distinguish between different threads
   - Route output to standard output (or other targets, depending on the implementation)

## Threading and Indentation

librtdebug is designed with multithreaded applications in mind:
- Each thread can be tracked separately.
- Indentation levels can reflect call depth or logical scopes.
- Output from different threads is visually distinguishable, making it easier to debug complex, concurrent applications.

## License
librtdebug is licensed under the Apache-2.0 license – see `LICENSE` file for details.
