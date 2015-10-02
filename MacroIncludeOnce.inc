
match any,macro@include@once
{
	macro includeonce path
	\{
		file@include equ path
		
		match head path tail,files@included
		\\{file@include equ \\}
		
		match head path,files@included
		\\{file@include equ \\}

		match file,file@include
		\\{include \\file \\}

		files@included equ files@included path	
	\}

	macro@include@once equ 
}
