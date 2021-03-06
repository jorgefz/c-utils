
# ARGLIB - Input Argument Library

This library provides tools to interpret input command line arguments and extract data from them.

Command line arguments may contain a series of options, called with a single character label '-o' or a multi-character string label '--option'. Options may require an argument that follows its label (e.g. '--integer 42') Options that require no argument are called flags, and are similar to a boolean (false by default, and true when called) (e.g. '--flag').

## Initialise
A custom option list is stored in the struct `_ARGS`.
Initialise the options list with the following function:
```c
arglib_init();
```
This function automatically adds the help flag option, with labels '-h' and '--help'.

## Add new options
In order to add a custom option, use the function:
```c
arglib_add_option(
		const char c_label, 
		const char *s_label,  
		const char *descr, 
		int type, int req);
```
Here, 'c_label' is the single character label, 's_label' is the multi-character string label (of max length 12), 'descr' is a string that describes the option, 'type' is the data type of option, and 'req' describes whether the option is required or optional.

Both the type and the required flag are defined with library-provided macros:

| dtype   | macro     | value |
|---------|-----------|-------|
| flag    | ARG_FLAG  | 0     |
| int     | ARG_INT   | 1     |
| double  | ARG_FLOAT | 2     |
| char [] | ARG_STR   | 3     |

| meaning  | macro     | value |
|----------|-----------|-------|
| required | ARG_REQ   | 0     |
| optional | ARG_OPT   | 1     |

If the labels are identical to previously defined options, the new option isn't added and NULL is returned.

It is not necessary to provide a description, or both the string and character labels simultaneously (only one is necessary). Instead of a string, pass a NULL pointer, and instead of a character, pass the `\0` character (or `(char)0`).

The 'help' option is added automatically. Called with '-h' or '--help', it will display the available options, with their labels, descriptions, data types, and required/optional tag.

### Examples
```c
arglib_init();

// Adds an option that asks for the number of iterations on a simulation, with labels '-i' and '--iter', that expects an integer as an argument, and must be defined (is required).
arglib_add_option('i', "iter", "Number of iterations in the simulation", ARG_INT, ARG_REQ);

// This option asks for the path and filename for output files, with labels '-o' and '--output', and expects a string argument. This option, however, is optional.
arglib_add_option('o', "output", "Output filename & path", ARG_STR, ARG_OPT);
```

### Number of options
To retrieve the number of defined options so far, use the function:
```c
int argnum = arglib_argnum();
```

## Parse arguments
The next step is to parse the input arguments with the defined options, using the following function:
```c
arglib_parse(int argc, const char *argv[]);
```
This function will search for option labels on the input arguments and read their arguments where applicable. If an error occurs, the function returns NULL; this includes an unrecognised option, a missing option argument or of the wrong data type, an undefined required option, or if one of the options is the help flag ('-h' or '--help').

## Get Values
Now, the option values can be retrieved. This is done with the function:
```c
void *ret = arglib_get_value(const char *arg_label);
```
Providing the option's predefined label (either one, as a string), will retrieve a void pointer to the memory location where the value is stored. The return value must be cast to the appropriate data type. If the option was not given a value, a NULL pointer is returned.

For flags, if a flag is called, then the return pointer points to a location in memory and will evaluate to true. Otherwise, NULL is returned.

## Freeing option list
The option list is freed with the following function:
```c
void arglib_free();
```
Note that the memory locations to which `arglib_get_value()` points will also be freed.
