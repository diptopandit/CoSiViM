CoSiViM
=======


Registers: 64bit
================================================================
Name	Description			|	Name	Description
================================================================
EIP		Instruction pointer	| 	REG0	General purpose register
ESP		Stack pointer		| 	REG1			,,
EFP		Frame pointer		|	REG2			,,
ELR		Link register		|	REG3			,,
PSR		Status register		|	REG4			,,
EAX		Executive A			|	REG5			,,
EBX		Executive B			|	REG6			,,
ECX		Executive C			|	REG7			,,

Instruction: 16bit
====================================================================
Nemonics	Opcode	Description	|	Nemonics	Opcode	Description
====================================================================
NOP			0x00	No Operation|	AND			0x10	A <-- A&B
LOAD		0x01	A <-- #		|	ANDI		0x11	A <-- A&#
MOV			0x02	B <-- A		|	PUSH		0x12	[S] <- A
ADD			0x03	A <-- A+B	|	PSHI		0x13	[S] <- #
ADDI		0x04	A <-- A+#	|	POP			0x14	A <- [S]
SUB			0x05	A <-- A-B	|	CMP			0x15	Compare A B and update status
SUBI		0x06	A <-- A-#	|	CMPI		0x16	Compare A # and update status
MUL			0x07	A <-- A*B	|	JZ			0x17	Jump to @ if Zero
MULI		0x08	A <-- A*#	|	JNZ			0x18	Jump to @ if non-zero
MOD			0x09	A <-- A%B	|	JMP			0x19	Jump to @
MODI		0x0A	A <-- A%#	|	CALL		0x1A	Save state and update EIP
NOT			0x0B	A <-- !A	|	RET			0x1B	Restore state and update EIP
XOR			0x0C	A <-- A^B	|	RES1		0x1C	Reserved
XORI		0x0D	A <-- A^#	|	RES2		0x1D	Reserved
OR			0x0E	A <-- A|B	|	RES3		0x1E	Reserved
ORI			0x0F	A <-- A|#	|	HALT		0x1F	Stop Execution
0
