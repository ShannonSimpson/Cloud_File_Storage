Cloud_File_Storage
==================

Mycloud Server: A mycloud server that accepts requests to store a file, retrieve a file, delete a file, and list the files stored on the server. Mycloud Applications: Four client mycloud applications that will store, retrieve, delete, and list files on your mycloud server.


CS485
Project 4
My Cloud File Storage
12/10/2014

/////////////////////
// Programmers:	   //
// Ashley Poe	   //
// Shannon Simpson //
/////////////////////

  FILES  :
README.md --------- This file
Documentation.txt - File that contains a brief description of the project including 
			algorithms used. Special features and limitations included in 
			this file.
LICENSE ----------- Protect our rights to our program.


  C FILES  :
makefile ---------- File that will generate .o files, compile, and run executables generated.
mycloudclient.c --- Handles the client and connection to the server.
mycloudlib.c ------ File that contains the functions the execute library functions.
mycloudserver.c --- Handles the server side of the connection. Remains connected until forced out.
reqresp.c --------- Struct and functions for requests and responses. 

  HEADERS  :
mycloudlib.h ------ Declaration of mycloudlib.c file and funcitons
reqresp.h --------- Declaration of reqresp.c file and functions

  MC FILES:
mcdel ------------- Can be used to execute delete <~/../mcdel <host> <port> <key> <filename>
mcput ------------- Can be used to execute put <~/../mcput <host> <port> <key> <filename>
mcget ------------- Can be used to execute delete <~/../mcget <host> <port> <key> <filename>
mclist ------------- Can be used to execute list <~/../mclist <host> <port> <key>
