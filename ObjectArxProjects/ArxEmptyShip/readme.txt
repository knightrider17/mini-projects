; �.�.�������, readme.txt
; � ����� "���������������� ��� AutoCAD 2013-2015"
; (������������ "��� �����", 2015)
;

AutoCAD 2015.
������ App01 � ������� Solution01 - ������ ARX-���������� App01.arx,
������������ ��� ������� ObjectARX. ������������ ������� ASTART (������) ������ BOOK � LISP-������� runstart.

����� �������: ASTART (����.) ��� ������ (�����.).
�������� �������� ������ BOOK.ASTART � BOOK.������.
����� LISP-�������: (funstart)

� ������� �������� ������������� ������ � ������������ Release.
��� �������� ���������� � ������������ Debug � ������ ������� �������� ������� ��� ���� ��������� �������� �� ��������� � ����,
��� ������� � �����: ����� ������ _DEBUG � ���������

Configuration Properties > C/C++ > Preprocessor > Preprocessor Definitions.

� ��������� ������ ������� ���������: 
rxapi.lib(libinit.obj) : error LNK2038: mismatch detected for 'RuntimeLibrary':
value 'MD_DynamicRelease' doesn't match value 'MDd_DynamicDebug' in App01.obj

