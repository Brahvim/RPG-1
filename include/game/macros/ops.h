#pragma once

// Macro-operation macros. Macro-macros!

// These are both two calls deep because some compilers allow you to stringize *macro names* with this!

#define STR2(p_arg)	# p_arg
#define STR1(p_arg)	STR2(p_arg)
#define STR(p_arg)	STR1(p_arg)

// [ https://stackoverflow.com/q/2751870 ].

#define CAT2(p_one, p_two)	p_one ## p_two
#define CAT1(p_one, p_two)	CAT2(p_one, p_two)
#define CAT(p_one, p_two)	CAT1(p_one, p_two)
