; ��������� ������������� ����� �� ����� ������ � ����� � ��������� ������� ���������� �������� EAX

.686		; ���������� ���������� ��� ���������� Intel Pentium IV
.model flat, stdcall	; ���������� "�������" ������ ������ � ������ ������ ������� ��� Win32
;
; ���� ����������� ������������ ������ � ���������
include	macroses.inc		; ����������� ����� �� ����������� ����������� Win API

; ������� ������
.data
include vars.inc            ; ����������� ����� �� ������������ �����������
promt DB 'Input the number: '  ; ����������� ��������� ���������� promt

; ������� ����
.code
include procedures.inc      ; ����������� ����� �� ������������ �����������

WinMain PROC				; ����� ����� � ����������

	INIT_CONSOLE			; ������ ��� ������������� �������
	
	WRITE '����� ������...'
	WRITELN '����� ������ � ������� �� ����� ������...'
	
	WRITE_STRING promt	    ; ����� ������-���������� promt
	
	INVOKE READNUMBER		; ������ ������ �����, ��������� ���������� � eax
	
	WRITE '��������� ����� = '
	WRITE_NUMBER eax
	NEW_LINE                ; ������� �� ����� ������
	
	WRITE '����������: '
	xor eax, eax            ; �������� eax
	WRITE_NUMBER eax        ; ������� ����� �� ����� - �������� � 0
	WRITE_COMMA             ; ������� �������
	WRITE_SPACE             ; ������� ������
		; ��� ��� ����� ���� ������� ����� WRITE ', ' �� ��� ��� ������ ������ �������� WRITE
	inc eax                 ; ����������� (��������������) eax �� 1
	WRITE_NUMBER eax  ; ������� ����� �� ����� - ��� ����� 1
	WRITE ', ' ; ��� � ��� ��� ������������� ������ WRITE_SPACE � WRITE_COMMA
	
	inc eax	;
	WRITE_NUMBER eax   ; ������� ����� �� ����� - ��� ����� 2
	WRITE ', '
	
	inc eax
	WRITE_NUMBER eax ; ������� ����� �� ����� - ��� ����� 3
	WRITE ', '

	inc eax
	WRITE_NUMBER eax ; ������� ����� �� ����� - ��� ����� 4
	WRITE ', '
	
	inc eax
	WRITE_NUMBER eax ; ������� ����� �� ����� - ��� ����� 5
	WRITE ',...'
	
	NEW_LINE
	NEW_LINE
	WRITE '�����.'
	
	READLN_CONSOLE         	 ; ������ ��� �������� ������� ENTER
	INVOKE ExitProcess, 0	; ����� ������� ��� ���������� ����������
WinMain ENDP			; ����� ��������� WinMain

end	WinMain			; ����� ���������