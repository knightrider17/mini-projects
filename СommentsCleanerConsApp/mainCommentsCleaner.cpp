//
//	TASK: CPP-COMMENTS-CLEANER
//
// ������� ����� ������������ � ������������� �����������
// ������� ����� C-Style �����������, � ������ // � /* */  
// ����������� ������������ ������ ����� (������ ������� �������) �� ���������
//

#include <iostream>

//
// C-Style Solution
//

// ���������� �������� �����:
// \n - ������ �������� ������
// \r - ������ �������� ������� (����������� �� ������ ������)

// ��������� �������� �������������:
// ������� ������:
// 1) �  Win \r\n
// 2) � *NIX \n
// 3) �  Mac \r
// � ����������� �� ���� ������ ������� ��� .cpp ���� ... ������� ��������� ������ :\

enum CHARS_THAT_WE_MET
{
	  MET_CLEAR = 0	//����� / ����������� �������� �������� ��� ������ / ������ ������ �������
	, MET_SLASH			// /  = '/'			
	, MET_STAR			// *  = '*'			
	, MET_STAR_COMMENTS	// /*  = '/' + '*'			
	, MET_SLASH_COMMENTS// //  = '/' + '/'			
	, MET_ONE_QUOTE		// '  = '\''		
	, MET_QUOTES		// "  = '\"'		
	//, MET_BACKSLASH	// \  = '\\'		
	//, MET_NEW_LINE	// \n = '\n' or \r = '\r' or \r\n = '\r' + '\n'			
	//				symbl	coments		string
};

// �������� ����� ������� �� ����� ������, �� ����� ��� �������.
// ��������� ���� �� ������� � ��, ��������, ���� ��� �������� ����� �� �������������
// ��� �������� ��������� ������, �������� ����� ������ ������������ ���� ����� �����������.
//
// ������ �������� ������� � ������� ������ ����� ���������� ��������� ������� ������ ���,
// ������ � ������������ ���������, ��� ��� ������ ��� ��� �� ������� � �������
//
void addNewLine(int curChar, FILE *pOutFile)
{
	if(curChar == '\n')
	{
		putc(curChar, pOutFile);
	}
}


void main()
{
	const std::string strInFile  = "example.cpp";
	const std::string strOutFile = "example_clear.cpp";

	std::string strInFileBuff;
	std::string strOutFileBuff;

	int curChar = 0, prevChar = 0;
	bool isSlashCmnt = false, isStarCmnt = false, isString = false, isOneQuote = false, isLastBackslash = true;
	CHARS_THAT_WE_MET metChar = MET_CLEAR;

	FILE *pInFile = 0;
	FILE *pOutFile = 0;
	errno_t errCodeIn = fopen_s(&pInFile, strInFile.c_str(), "rb");
	errno_t errCodeOut = fopen_s(&pOutFile, strOutFile.c_str(), "wb");


	while ((curChar = getc(pInFile)) != EOF)
	{
		char curCharChar = (char)(curChar);

		// ���������� ������� ������������� ������� 
		// �������� ������� � switch �� �����������, � ������
		// ��������� � ���������� ���������� ��������
		switch (metChar)
		{
		case MET_CLEAR:
			switch (curChar)
			{
			// ��������� ������� ������ � out, �� � ����������
			// ���� � ������� �� ���������� ����
			case '\'':	metChar = MET_ONE_QUOTE;
						isOneQuote = true;
						putc(curChar, pOutFile);
				break;
			// ������ ���� ������ ������ ������ � out, ��� ���� �� �������,
			// �� �������� �� ������ �������� ���� � ��������� ������
			// ������ �������������� �� ���� ��������
			case '/':	metChar = MET_SLASH;
				break;
			// ������� ������ � out ����� �����
			case '\"':	metChar = MET_QUOTES;
						isString = true;
			default:	putc(curChar, pOutFile);
			}
		break;

		case MET_SLASH_COMMENTS:
			isLastBackslash = ( !isLastBackslash && (curChar == '\\' /*|| curChar == ' '*/ || curChar == '\r' || curChar == '\n') );

			switch (curChar)
			{
			// ��������� ������������ �������� ������������
			// � ������ ����, ��� ����������� ����� ������������� ������������ ����� ���� ������ '\n'
			// �� ����� ������ ������ ������ � ����� �������� ������� �������� ��� ����� ���������
			// �� ����� �� ����� ��������� �������� ����� ������ '\\' ��� ������ \ (�������� ����)
			case '\n':
				if (!isLastBackslash)
				{
					metChar = MET_CLEAR;
					isSlashCmnt = false;
					isLastBackslash = true;
				}
				addNewLine(curChar, pOutFile);
			}
		break;

		case MET_STAR_COMMENTS:
			switch (curChar)
			{
			// C �������������� ���������� �� �����, ����� ����� ������ ���������� '*/'
			case '*': metChar = MET_STAR;
			}
			addNewLine(curChar, pOutFile);
			break;

		case MET_STAR:
			switch (curChar)
			{
			// C �������������� ���������� �� �����, ����� ����� ������ ���������� '*/'
			case '/':
				if (prevChar == '*')
				{
					metChar = MET_CLEAR;
					isStarCmnt = false;
				}
			}
			addNewLine(curChar, pOutFile);
			break;

		case MET_SLASH:
			switch (curChar)
			{
			case '/':
				if(isString)
				{
					putc(curChar, pOutFile);
				}
				else
				{
					if (prevChar == '/')
					{
						isSlashCmnt = true;
						metChar = MET_SLASH_COMMENTS;
					}
				}
			break;
			case '*':
				if (isString)
				{
					putc(curChar, pOutFile);
				}
				else
				{
					if (prevChar == '/')
					{
						isStarCmnt = true;
						metChar = MET_STAR_COMMENTS;
					}
				}
			break;
			default:
				if (!(isSlashCmnt || isStarCmnt))
				{
					// �� ���������� ���� ��������� ���� � �� ��������, ��� �� �����, ��� ����� ������
					// ��� ��� ������ ������� ��� �������, ��� ������� ���� �� ������� (=>)
					if(prevChar == '/')
					putc('/', pOutFile);
					// (=>) � ������ ����� ����� ������� ������� ������
					putc(curChar, pOutFile);
				}
				else
				{
					addNewLine(curChar, pOutFile);
				}
			}
		break;

		case MET_QUOTES: 
			if (curChar == '\"')
			{
				// ������ ������ � �������� ��������� ���� ����� 1 ���������� ������, ����� ������
				// ������ ������� ���� �� ���������������� ������� ������� ������ �������� ������, � ������ \" 
				if(prevChar != '\\')
				{
					metChar = MET_CLEAR;
					isString = false;
				}
			}
			putc(curChar, pOutFile);
		break;

		case MET_ONE_QUOTE:
			if (curChar == '\'')
			{
				metChar = MET_CLEAR;
				isOneQuote = false;
			}
			putc(curChar, pOutFile);
		break;

		}

		prevChar = curChar;
	}

	fclose(pInFile);
	fclose(pOutFile);
}
