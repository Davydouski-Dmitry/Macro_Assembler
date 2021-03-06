;
; ���� ����������� ������������ ������ � ���������
;
include		windows.inc		; ���������� ���� �� ����������� ����������� Win API
includelib	kernel32.lib	; ���������� ���������� ���� Win32

;
; �������� �������������� �������
;
ExitProcess   PROTO :DWORD
AllocConsole  PROTO
GetStdHandle  PROTO :DWORD
WriteConsoleA PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
ReadConsoleA  PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
GetTickCount  PROTO

;
; ������ ��� ������������� �������
;
INIT_CONSOLE MACRO
	INVOKE AllocConsole
	INVOKE GetStdHandle, STD_OUTPUT_HANDLE
	mov stdout, eax
	INVOKE GetStdHandle, STD_INPUT_HANDLE
	mov stdin, eax
ENDM

;
; ������ ��� ������ � �������
;
; PARAM1 - ����� ������ ��� ������
; PARAM2 - ������ ������
;
WRITE_CONSOLE MACRO PARAM1, PARAM2
	push eax
	push ecx
	push edx
	INVOKE WriteConsoleA, stdout, PARAM1, PARAM2, OFFSET cWritten, NULL
	pop edx
	pop ecx
	pop eax
ENDM

;
; ������ ��� ������ ������ �� �������
;
; PARAM - ������
;
WRITE_STRING MACRO PARAM
    WRITE_CONSOLE OFFSET PARAM, SIZEOF PARAM	
ENDM

;
; ������ ��� ������ ������ ����� �� �������
;
; PARAM - �����
;
WRITE_NUMBER MACRO PARAM
	push eax
	push ebx
	INVOKE HEX2ASCII, PARAM
    WRITE_CONSOLE ebx, eax
	pop ebx
	pop eax
ENDM

;
; ������ ��� �������� ������� �� ����� ������
;
NEW_LINE MACRO
	WRITE_CONSOLE OFFSET EOL, SIZEOF EOL
ENDM

;
; ������ ��� ������ �������
;
WRITE_SPACE MACRO
	WRITE_CONSOLE OFFSET SPACE, SIZEOF SPACE
ENDM

;
; ������ ��� ������ �������
;
WRITE_COMMA MACRO
	WRITE_CONSOLE OFFSET COMMA, SIZEOF COMMA
ENDM

;
; ������ ��� �������� ������� ������� ����
;
READLN_CONSOLE MACRO
	push eax
	push ecx
	push edx
	INVOKE ReadConsoleA, stdin, OFFSET cEmpty, 0, OFFSET cWritten, NULL
	pop edx
	pop ecx
	pop eax
ENDM

;
; ������ ��� ������ ������ � ����������
;
; PARAM1 - ����� ��� �����
; �����: eax - ������ ��������� ������
;
READ_STRING MACRO PARAM1
	push ecx
	push edx	
	
	INVOKE ReadConsoleA, stdin, OFFSET PARAM1, SIZEOF PARAM1, OFFSET cWritten, NULL
	mov eax, cWritten
	sub eax, 2
	
	pop edx
	pop ecx
ENDM

;
; ������ ��� ����������� �����
; PARAM - �������� �����
;
; �������������: RUS <msg1, msg2, msg3>
;
RUS MACRO PARAM
    IRP i, <PARAM>
        INVOKE ConvertToRus, OFFSET i, SIZEOF i
	ENDM
ENDM

;
; ������ ��� ������ ��������������� ��������� ������ �� �����
; PARAM - ���������������� ������
;
; �������������: WRITE 'Hello, world!'
;
WRITE MACRO PARAM
  LOCAL lab 
  LOCAL stroka 

  push eax
  jmp lab
  stroka db param
lab:  
  INVOKE OutputString, OFFSET stroka, SIZEOF stroka
  pop eax
ENDM

;
; ������ ��� ������ ��������������� ��������� ������ �� �����
; � ����� ������ ������� ����������� �� ����� ������
; PARAM - ���������������� ������
;
; �������������: WRITELN 'Hello, world!'
;
WRITELN MACRO PARAM
  WRITE PARAM
  WRITE_STRING EOL
ENDM

;
; ������ ��� ������������� ��������� ������
;
; PARAM1 - ����������, � ������� ����� �������� ����� ������
; PARAM2 - ������ ������ � ������
;
GETMEM MACRO PARAM1, PARAM2
	push eax
	push ecx
	push edx
	
	INVOKE GlobalAlloc, NULL, PARAM2
	.IF eax == NULL
	  WRITE '���������� �������� ������!'
	  READLN_CONSOLE
	  INVOKE ExitProcess, 0
	.ELSE
	  mov PARAM1, eax
	.ENDIF
	
	pop edx
	pop ecx
	pop eax
ENDM

;
; ������ ��� ������������� ��������� ������
;
; PARAM - ����� ������
;
FREEMEM MACRO PARAM
	push eax
	push ecx
	push edx
	INVOKE GlobalFree, PARAM
	pop edx
	pop ecx
	pop eax
ENDM