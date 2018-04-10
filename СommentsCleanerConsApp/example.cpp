s=("a\bc\
def";
//abc\
def

/*
/* \ */
*/

/**** Multiline\n\
comment */

//a++; /* Multiline\n\
		comment */\n";


#include <iostream>
#include <string>

/**

	This is a demo function

*/

void demo(void)
{
	/* Multiline\n\
	comment */

	//a++; /* Multiline\n\
		comment */\n";

	// OPTION_1
	const char *tst = "my\"" "line" "\"";//it's comment\
											 It's comment

	// Application description
	std::string message = "Application must remove single line and multiline comments.\n \
								Example:\n \
									int a = 0; // single line comment \n \
									a++; /* Multiline\n \
											comment */\n";
	
	std::cout << message << std::endl; // Out message
	
	/*
		Code generation
	*/
	for (int i = 0; i < 10; i++)
		std::cout << "int var" << i << " = 0;" << "//This is a variable number "
		<< i << std::endl; // Out variable

	// Let us add some more comments:
	
	// OPTION_EXAMPLE
	//std::string message = "Application must remove single line and multiline comments.\n \
								Example:\n \
									int a = 0; // single line comment \n \
									a++; /* Multiline\n \
											comment */\n";

	// OPTION_1
	const char *pChar = "my\"" "line" "\"";//it's comment\
											 It's comment

	// OPTION_2
	std::cout << "what if: \"/////////\"" << std::endl;

	// OPTION_3
	std::string myStr_1 = "Some text /* then a comment */ comment again; goes till here */ text goes on and finishes.";

	// OPTION_4
	std::string myStr_2 = "***/";

	// OPTION_5
	int our = 1, /* super!*/ syntetic = 2, /*comment*/ code = 3;
	// thst must return "our syntetic code"

	// OPTION_6
	/* if we meet a*=2, then it has to be not the end of the comment.
	need to compare 2 symbols: */

	// OPTION_7
	char c = '\\';
	if (c == '\\')
	{ /* we have to handle this too */ }

	// OPTION_8
	int OPTION_8 = 8;//

	// OPTION_9
	/*All*/
	/*
	*type
	*
	*/
	//of comments

	// OPTION_10
	std::string strWithComment = "/* aaa */"; // string with a /* */ comment inside

	// OPTION_11
	/*
	khg
	dmflkdms
	fvsd
	kf;sd;l
	////////piouhjkl
	5
    sxsalkxas
    //
    */

	// OPTION_11
	char *notAComment = "\"//";

	// MY_OPTION

	/////////////////////////////////////////////////////////
	/*	I personaly like to comment like this
		Because we have an option to just (*)
	//*/

	/////////////////////////////////////////////////////////
	//*	(*) add a single "/" to the left side of the "/*" part
	
	char main = '/', thing = '*';
	char is = '*', that = '/';
	
	// to uncomment the whole part
	
	char _this = '\/\//\\', _code = '*';
	char has = '////', to = '*';
	char stay = '/n';
	
	//*/	
	/////////////////////////////////////////////////////////

	/*	BUT What if !!!
	
	char main = '/', thing = '*';
	char is = '*', that = '/';

	/* We have Multiple 
	/* Milticommets one
	/* inside another */
	
	char _this = '\/\//\\', _code = '*';
	char has = '////', to = '*';
	char stay = '/n';
	
	//*/	
	/////////////////////////////////////////////////////////

}

