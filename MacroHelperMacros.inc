
macro CreateNewList ListName, Content
{
	ListName equ Content
}

macro AddToList ListName, appendix
{
	match anything:app,ListName:appendix
	\{
		ListName equ \anything\#,\#app
	\}
	match :app,ListName:appendix
	\{
		ListName equ \app
	\}
}

macro DisplayList ListName
{
	match any, ListName
	\{	
		irps value, \any
		\\{
			display \\`value
			display " "
		\\}
	\}
}

macro DefineIfEmpty SymbolName, DefineVal
{
	match ,SymbolName
	\{
		SymbolName equ DefineVal
	\}
}

macro CreateNewSymbol SymbolName, Content
{
	SymbolName equ Content
}

macro AppendAtSymbol SymbolName, appendix
{
	match symbC:appCont,SymbolName:appendix
	\{
		SymbolName equ \symbC\#appCont
	\}	
	match :appCont,SymbolName:appendix
	\{
		SymbolName equ \appCont
	\}
}

macro DisplaySymbol SymbolName
{
	DisplayList SymbolName
}

