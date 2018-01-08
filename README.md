DFCLS
=====
DFCLS is the command-line-shell project.

Development Environment
-----------------------
* Development Programming Language: C++
* Development Operating System: Microsoft Windows 10

files
-----
* .gitignore  
(Git's file)

* class.h  
A header of class

* command-function.h  
A header of command functions declarations

* CommandLine.cpp  
A source file of dfcls::CommandLine function

* CommandProcess.cpp  
A source file of dfcls::CommandProcess function

* commands.cpp  
A source file of command functions defines

* constant.h  
A header of constants defines

* extern.h  
A header of gloval variables declarations

* LICENSE  
A license file of GPL

* LogProcess.cpp  
A source file of dfcls::LogProcess class member functions

* main.cpp  
A source file of main function

* normal-function.h  
A header of normal functions declarations

* prepering.cpp  
A source file of dfcls::prepering function

commands
--------
* directory
	* mdir  
	Make a directory  
	Usage: `mdir [dirname]`

	* rdir  
	Remove a directory  
	Usage: `rdir [dirname]`

	* chdir  
	Change current working directory  
	Usage: `chdir [dirname]`

	* cwdir  
	Print current working directory  
	Usage: `cwdir`

* file
	* mfile  
	Make a file  
	Usage: `mfile [filename]`

	* rfile  
	Remove a file  
	Usage: `rfile [filename]`

	* cfile  
	Copy file  
	Usage: `cfile [from] [to]`

	* lfile  
	Print list of file  
	Usage: `lfile [dirname]`

* directory & file
	* rename  
	Rename a directory or a file  
	Usage: `rename [name]`

* viewer
	* tview  
	View a text-file  
	Usage: `tview [filename]`

	* bview  
	View a binary-file  
	Usage: `bview [filename]`

* other
	* version  
	Print current version of DFCLS  
	Usage: `version`

	* app  
	Execution a application  
	Usage: `app [executable-filename] <arguments>`

	* date  
	Print current date  
	Usage: `date`

	* time  
	Print current time  
	Usage: `time`

	* now  
	Print current date and current time  
	Usage: `now`

	* exit  
	Exit DFCLS  
	Usage: `exit`

History
-------
* 1.0 (January 8th, 2018)
	* First version