format binary

include "MacroLibraryFASM.inc"

org 0x100000
main:
;	DefineFunction global HelloWorld(int,int,int)
	DeclareFunction HelloWorld(int,int,int)
	ret
