MACROFCT_TRUE = 0
MACROFCT_FALSE = 1
include "MacroIncludeOnce.inc"
;includeonce "MacroHelperMacros.inc"


macro DeclareFunction [func]
{
	common
	mfunction_settings_global = MACROFCT_FALSE
	mfunction_settings_no_stack = MACROFCT_FALSE
	mfunction_settings_arg_count equ
	mfunction_settings_func_name equ

	forward irps value, func
	\{
		match (,\value
		\\{
			DefineIfEmpty mfunction_settings_func_name, CurrToken	
		\\}
	
		CurrToken equ \value

		match any,mfunction_settings_func_name
		\\{
			AppendAtSymbol mfunction_settings_arg_count,\value
		\\}

		if \`value eq "global"
			mfunction_settings_global = MACROFCT_TRUE
		else if \`value eq "no_stack"
			mfunction_settings_no_stack = MACROFCT_TRUE
		end if
	\}
	common

	match (arguments),mfunction_settings_arg_count
	\{
		mfunction_settings_arg_count equ
		forward
			AppendAtSymbol mfunction_settings_arg_count,_1
		common
	\}

	match (),mfunction_settings_arg_count
	\{
		mfunction_settings_arg_count equ _0
	\}


	AppendAtSymbol mfunction_settings_func_name, mfunction_settings_arg_count
	match comp_func_name,mfunction_settings_func_name
	\{
		if ~ defined \comp_func_name\#_settings_target
			display "Function is defined",13,10,0			
		end if
	\}

}
macro DefineFunction [func]
{
	common
	mfunction_settings_global = MACROFCT_FALSE
	mfunction_settings_no_stack = MACROFCT_FALSE
	mfunction_settings_target equ
	mfunction_settings_target_final equ
	mfunction_settings_arg_count equ
	mfunction_settings_func_name equ

	forward irps value, func
	\{
		match (,\value
		\\{
			DefineIfEmpty mfunction_settings_func_name, CurrToken	
		\\}

		match <,CurrToken
		\\{
			mfunction_settings_target equ 0
		\\}	
	
		CurrToken equ \value

		match >,\value
		\\{
			restore mfunction_settings_target
		\\}
		
		match any,mfunction_settings_target
		\\{
			AppendAtSymbol mfunction_settings_target_final,\value
		\\}

		match any,mfunction_settings_func_name
		\\{
			AppendAtSymbol mfunction_settings_arg_count,\value
		\\}

		if \`value eq "global"
			mfunction_settings_global = MACROFCT_TRUE
		else if \`value eq "no_stack"
			mfunction_settings_no_stack = MACROFCT_TRUE
		end if
	\}
	common

	match (arguments),mfunction_settings_arg_count
	\{
		mfunction_settings_arg_count equ
		forward
			AppendAtSymbol mfunction_settings_arg_count,_1
		common
	\}

	match (),mfunction_settings_arg_count
	\{
		mfunction_settings_arg_count equ _0
	\}

	display "Function name: "
	DisplaySymbol mfunction_settings_func_name
	display 13,10,0
	display "Function argument list: "
	DisplaySymbol mfunction_settings_arg_count
	display 13,10,0
	AppendAtSymbol mfunction_settings_func_name, mfunction_settings_arg_count
	display "Function label name: "
	DisplaySymbol mfunction_settings_func_name
	display 13,10,0

	match ,mfunction_settings_target_final
	\{
		mfunction_settings_target_final equ mfunction_settings_func_name
	\}

	display "Function redirected call: "
	DisplaySymbol mfunction_settings_target_final
	display 13,10,0

	match comp_func_name,mfunction_settings_target_final
	\{
		\comp_func_name\#_settings_global = mfunction_settings_global
		\comp_func_name\#_settings_no_stack = mfunction_settings_no_stack
		\comp_func_name\#_settings_target equ mfunction_settings_target_final
	\}
}
