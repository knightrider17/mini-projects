; Н.Н.Полещук, readme.txt
; В книге "Программирование для AutoCAD 2013-2015"
; (издательство "ДМК Пресс", 2015)
;

AutoCAD 2015.
Проект App01 в решении Solution01 - пример ARX-приложения App01.arx,
построенного без мастера ObjectARX. Регистрирует команду ASTART (АСТАРТ) группы BOOK и LISP-функцию runstart.

Вызов команды: ASTART (англ.) или АСТАРТ (русск.).
Возможны варианты вызова BOOK.ASTART и BOOK.АСТАРТ.
Вызов LISP-функции: (funstart)

В обычном варианте компилируется только в конфигурации Release.
Для успешной компиляции в конфигурации Debug в данном проекте пришлось сделать еще одно изменение настроек по сравнению с теми,
что описаны в книге: убран символ _DEBUG в параметре

Configuration Properties > C/C++ > Preprocessor > Preprocessor Definitions.

В противном случае получим сообщение: 
rxapi.lib(libinit.obj) : error LNK2038: mismatch detected for 'RuntimeLibrary':
value 'MD_DynamicRelease' doesn't match value 'MDd_DynamicDebug' in App01.obj

