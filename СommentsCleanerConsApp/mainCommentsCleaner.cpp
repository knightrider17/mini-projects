//
//	TASK: CPP-COMMENTS-CLEANER
//
// Удалить файла однострочные и многострочные комментарии
// имеются ввиду C-Style комментарии, а именно // и /* */  
// Коммантарии содержащиеся внутри строк (внутри двойных ковычек) не учитывать
//

#include <iostream>

//
// C-Style Solution
//

// Касательно перевода строк:
// \n - символ перевода строки
// \r - символ возврата коретки (возвращение на начало строки)

// Вероятные проблемы совместимости:
// Перевод строки:
// 1) в  Win \r\n
// 2) в *NIX \n
// 3) в  Mac \r
// В зависимости от того ОТКУДА получим наш .cpp файл ... придётся доработку делать :\

enum CHARS_THAT_WE_MET
{
	  MET_CLEAR = 0	//пусто / закончилась политика комманта или строки / только начали парсить
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

// Переводы строк оставим на своих местах, но чисто для красоты.
// Формально надо бы удалять и их, особенно, если это переносы строк из комментаривев
// ибо согласно банальной логике, переносы строк внутри комментариев тоже чвсть комментриев.
//
// ОДНАКО согласно примеру в задании внутри блока комметарии визуально убранны именно так,
// тоесть с оставленными пробелами, так что делаем так как по Шаблону в задании
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

		// Рассмотрим решение посимвольного парсера 
		// Алгоритм заходит в switch по предыдущему, а внутри
		// проверяет и выставляет предыдущим нынешний
		switch (metChar)
		{
		case MET_CLEAR:
			switch (curChar)
			{
			// Одинарную кавычку пихаем в out, но и выставляем
			// факт её наличия на предыдущем шаге
			case '\'':	metChar = MET_ONE_QUOTE;
						isOneQuote = true;
						putc(curChar, pOutFile);
				break;
			// Первый слэш нельзя начать писать в out, ибо если он коммент,
			// то комменты не должны писаться даже с начальным первым
			// слешом внезависимости от типа коммента
			case '/':	metChar = MET_SLASH;
				break;
			// Кавычки писать в out можно сразу
			case '\"':	metChar = MET_QUOTES;
						isString = true;
			default:	putc(curChar, pOutFile);
			}
		break;

		case MET_SLASH_COMMENTS:
			isLastBackslash = ( !isLastBackslash && (curChar == '\\' /*|| curChar == ' '*/ || curChar == '\r' || curChar == '\n') );

			switch (curChar)
			{
			// Позволяет односрочному комменту продолжиться
			// С учётом того, что индикатором конца однострочного коммментария может быть только '\n'
			// ТО перед концом каждой строки и ПЕРЕД символом первода корретки нам нужно проверять
			// не былло ли перед переаодом корретки этого симола '\\' или просто \ (обратный слеш)
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
			// C многострочными комментами всё проще, нужно найти только комбинацию '*/'
			case '*': metChar = MET_STAR;
			}
			addNewLine(curChar, pOutFile);
			break;

		case MET_STAR:
			switch (curChar)
			{
			// C многострочными комментами всё проще, нужно найти только комбинацию '*/'
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
					// На предыдущем шаге встретили слэш и НЕ записали, ибо не знали, что будет дальше
					// так что теперь добавим его обратно, ибо коммент таки не начался (=>)
					if(prevChar == '/')
					putc('/', pOutFile);
					// (=>) и только после этого добавим текущий символ
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
				// Внутри строки с обычными кавычками есть всего 1 уникальный случай, когда внутри
				// строки имеется сама же ЗАЭКРАНИРОВАННЫЕ двойные ковычки причём обратным слешем, а именно \" 
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
