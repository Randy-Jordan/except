# Except 

## Description
Exception implementation written in C.

## Table of Contents

- [Description](#description)
- [Features](#features) 
- [Installation](#installation)
- [Usage](#usage)
- [Credits / Resources](#credits--resources)
- [License](#license)

## Features / TODOS

- [ ] RAISE - Raise an exception. 
- [ ] RERAISE - Reraise the current exception.
- [ ] RETURN - Switch to the previous exception frame and return.
- [ ] TRY - Start a try block.
- [ ] EXCEPT - Catch a specific exception.
- [ ] ELSE - Catch all other exceptions.
- [ ] FINALLY - Execute final code.
- [ ] END_TRY - End a try block.
- [ ] hard_fail(char * fmt, ...) - Print errno along with msg to stderr and exit.

## Usage
except.c and except.h should be dropped into an existing project and compiled along with it.<br>

`make test` to build and test project. Tests usually contain usage examples.<br>
`make` to build the project.


## Credits / Resources
I found these resources extremely helpful.<br>
[C Interfaces and Implementations - David Hanson](https://github.com/drh/cii/tree/master)<br>
[Jacob Sorber](https://www.youtube.com/@JacobSorber)<br>


## License

This project is licensed under GPLv3 - see the [LICENSE](LICENSE) file for details.
