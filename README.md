
## LAB 3
For lab assignment 3b we implemented the following semantic analysis checks:
	- Undeclared Variables ( checkIfIdentifierIsDeclared )
	- Identifiers Declared Multiple Times ( insert )
	- Wrong number of arguments ( checkParameterCountAndTypes )
	- Wrong types of argument in function call ( checkParameterCountAndTypes )
	- Array indices should be integers ( checkIfArrayIndexIsInteger, checkIfMultipleArrayIndicesAreAllIntegers )
	- Assigning variables to functions/arrays/procedures ( checkIdentifierIdType, checkIdentifierSecondaryType)
	- Type Checking (checkTypes, checkIdentifierSecondaryType, checkAssignment, checkCondition, checkParameterCountAndTypes)
		* Type checking also takes into account infered types

The semantical analyser also gives warnings in the following cases:
	- Using reals in combination with "mod" and "div"
	- Assigning reals to integers
	- Comparing integers with reals

To implement these checks we used a stack of symboltables in combination with a stringtable.
Declared variables, functions, procedures and parameters are stored as the datatype IdEntry.
Using the stack the scope of the variables is handled.

The compiler can be compiled using the "make" command, "make cs" will run all
test cases of 3b/4 and "make test" will run all test cases from 3a.

## LAB 4
