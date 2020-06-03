

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
	C - UTILS

	Useful functions for the C Programming Language.

	Contains several small useful functions for C 
	using only the standard libraries.
	These functions can be classified into:
	* Useful data types
	* Memory Management
	* String Manipulation
	* 1D number array manipulation
	* 2D matrix operations (WIP)
	* File manipulation (WIP)


	VERSIONS

	1.0 - 29/03/2020
		First version.
		DataType: Added 'uint'.
		Memory: Added 'xmalloc' and 'xfree'.
		String: Added slicing and reversion.
		1D Array: Added generation (0, 1, value, range),
				printing, concatenation, copying,
				and reversing.

	1.1 - 30/03/2020
		Added auto-allocation functions for 1D Arrays:
			intzerosA, a_intones, intvalA, a_intrange,
			intcpyA, a_intcat.
		Added maximum and minimum functions for 1D Arrays:
			intmax, intmin, intimax, intimin
		Added sum function for 1D Arrays: intsum

	1.2 - 31/03/2020
		Modified xmalloc to return NULL and print an error
			message to stderr on fail.

	1.3 - 28/05/2020
		Modified xmalloc to exit program with error code "-1"
			on fail.
		Modified xfree to return '-1' on fail.
		Removed dependence of xmalloc on functions that allocate memory.
			Standard library function malloc is used instead, and,
			on fail, a NULL pointer is returned.
		Added additional 1D integer array functions for
			element mnaipulation: introll, intdel, intins, a_intins
		Added additional 1D integer array arithmetics:
			intadd, intsub, intfunc, instadd, intsmult, intdot, intcmp

	1.4 - 29/05/2020
		Added all equivalent functions for double-type 1D arrays.
		Added 1D double array functions:
			fltinv, fltexp, fltsqrt, fltsin, fltcos, fltlog, 
			fltlog10, fltdot, fltmag, fltisval, fltisnan
		Added data type conversion functions:
			inttoflt, a_inttoflt, flttoint, a_flttoint
		Improved documentation.

	1.5 - 03/06/2020
		Added functions for Input/Output:
			getstr, strtoint, strtointArr, strtoflt, strtofltArr,
			CountTxtLines, ReadTxtLines, GenFromTxt
		Renamed all allocated functions from 'a_funcname' to 'funcnameA'.
		


	FUTURE PLANS

	Matrices
	I/O
	Plotting


		


*/



/*
	DATA TYPES
*/
typedef unsigned int uint;


/*
	MEMORY
*/
/*
Allocates some memory of length 'bytes',
and returns a pointer ot it.
On fail, it exits the program.
*/
void *
xmalloc(size_t bytes)
{
	if (bytes == 0){
		fprintf(stderr, " Error: can't allocate 0 bytes\n");
		exit(-1);
		return (NULL);
	}
    void *ptr = malloc(bytes);
    if (ptr)
        return ptr;

    fprintf(stderr, " Error: can't allocate %ld bytes\n", (long)bytes);
    exit(-1);
	return (NULL);
}

/*
Checks if pointer points to allocated memory
before freeing it.
*/
int
xfree(void *ptr)
{
	if (ptr){
		free(ptr);
		return 0;
	}
	fprintf(stderr, " Error: failed to free pointer");
	return (-1);
}



/*
	STRINGS
*/

/*
Copies an input string into allocated memory,
and returns a pointer to it.
Note: free the string once it has been used.
*/
char *
strcpyA(const char *str)
{
	if(!str)
		return (NULL);
	char *t = malloc((strlen(str)+1)*sizeof(char));
	if(!t){
		size_t bytes = strlen(str)*sizeof(char);
		fprintf(stderr, " Error: failed to allocate %Iu bytes\n", bytes);
		return (NULL);
	}
	strcpy(t, str);
	return t;
}


/*
Slices the input string from index i to index j,
and returns a pointer to it.
Note that it modifies the input string.
On fail, it returns a null pointer.
*/
char *
strslc(char *s, size_t i, size_t j)
{
	/* Input checks */
	if( (i>j) || strlen(s)<(j-i+1) )
		return (NULL);

	/* Move pointer to left slice */
	char *ptr;
	ptr = s + i;

	/* Null terminator after right slice */
	ptr[j-i+1] = '\0';
	
	s = ptr;
	return s;
}


/*
Slices a string 'str' from index i to index j
and stores the result in the input string 'dest',
leaving the original string untouched.
On fail, it returns a null pointer.
*/
char *
strslc2(char *dest, const char *str, size_t i, size_t j)
{
	/* Input checks */
	if( (i>j) || strlen(str)<(j-i+1) )
		return (NULL);

	//Make temporal string to slice
	char temp[strlen(str)];
	char *t = &(temp[0]);
	strcpy(t, str);

	/* Move pointer to left slice */
	char *ptr;
	ptr = t + i;

	/* Null terminator after right slice */
	ptr[j-i+1] = '\0';

	strcpy(dest, ptr);
	return dest;
}


/* Reverses input string */
char *
strrev(char *s)
{
	/*Check input */
	if(!s)
		return (NULL);

	/* Declaring temporary space to save string */
	uint len = strlen(s);
	char buffer[len];

	/* Copying original string */
	strcpy(buffer, s);

	/* Reversing string from buffer */
	for(size_t i=0; i<len; i++)
		s[i] = buffer[len-i-1];

	return s;
}




/*
	INTEGER 1D ARRAYS
*/


/* Generates an array of a given value */
int *
intval(int * arr, size_t s, int val)
{
	for(size_t i=0; i<s; i++)
		arr[i] = val;
	return arr;
}

/* Generates an array of a given value */
int *
intvalA(size_t s, int val)
{
	int *arr = malloc(s*sizeof(int));
	if(!arr)
		return (NULL);
	intval(arr, s, val);
	return arr;
}

/* Generates an array of zeros */
int *
intzeros(int *arr, size_t s)
{
	intval(arr, s, 0);
	return arr;
}

/*
Allocates and generates an array of zeros.
You will need to free the pointer afterwards manually.
*/
int *
intzerosA(size_t s)
{
	int *arr = intvalA(s, 0);
	return arr;
}

/* Generates an array of ones */
int *
intones(int *arr, size_t s)
{
	intval(arr, s, 1);
	return arr;
}

/*
Allocates and generates an array of ones.
You will need to free the pointer afterwards manually.
*/
int *
intonesA(size_t s)
{
	int *arr = intvalA(s, 1);
	return arr;
}

/* Generates an array of values in a range */
int *
intrange(int *arr, size_t s, 
		int start, int step)
{
	int val = start;
	for(size_t i=0; i<s; i++){
		arr[i] = val;
		val += step;
	}
	return arr;
}

/*
Allocates and generates an array of values in a range.
You will need to free the pointer afterwards.
*/
int *
intrangeA(size_t s, int start, int step)
{
	/*Allocating pointer*/
	int *arr = (int *) malloc(s*sizeof(int));
	if(!arr)
		return (NULL);
	/*Evaluating array*/
	int val = start;
	for(size_t i=0; i<s; i++){
		arr[i] = val;
		val += step;
	}
	return arr;
}

/* Copies an array to another */
int *
intcpy(int *dest, const int *src, size_t s)
{
	if( !dest || !src)
		return (NULL);
	for(size_t i=0; i<s; i++)
		dest[i] = src[i];
	return dest;
}

/*
Copies an array into another array it allocates,
and returns a pointer to it.
You will have to free it afterwards.
*/
int *
intcpyA(const int *src, size_t s)
{
	if(!src)
		return (NULL);
	int *dest = (int *) malloc(s*sizeof(int));
	if(!dest)
		return (NULL);
	intcpy(dest, src, s);
	return dest;
}

/* Concatenates two arrays of integers into destination */
int *
intcat(int *dest, const int *a, size_t as, 
		const int *b, size_t bs)
{
	/* Check input */
	if (!dest || !a || !b)
		return (NULL);
	/* Append first array */
	intcpy(dest, a, as);
	/* Append second array */
	intcpy(dest+as, b, bs);
	return dest;
}

/*
Concatenates two arrays of integers,
allocates an array with the result,
and returns a pointer to it.
You will have to free it afterwards.
*/
int *
intcatA(const int *a, size_t as, 
		const int *b, size_t bs)
{
	/* Check input */
	if (!a || !b)
		return (NULL);

	int *dest = (int *) malloc((as+bs)*sizeof(int));
	if(!dest)
		return (NULL);
	intcpy(dest, a, as);
	intcpy(dest+as, b, bs);
	return dest;
}

/* Prints an array of integers to stdout */
void
intprint(const int *src, size_t s)
{
	for(size_t i=0; i<s; i++)
		printf("%d ", src[i]);
	printf("\n");
}

/* Reverses input array */
int *
intrev(int *arr, size_t len)
{
	/*Check input */
	if(arr == NULL)
		return arr;

	/* Declaring temporary space to save string */
	int buffer[len];
	int *b = &(buffer[0]);

	/* Copying original string */
	intcpy(b, arr, len);

	/* Reversing string from buffer */
	for(size_t i=0; i<len; i++)
		arr[i] = buffer[len-i-1];

	return arr;
}



/* 	STATISTICS */
/* Finds maximum of array */
int
intmax(const int *arr, size_t len)
{
	/* Initialise max value on first array member */
	int max = arr[0];

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] > max)
			max = arr[i];
	}
	return max;
}

/* Finds minimum of array */
int
intmin(const int *arr, size_t len)
{
	/* Initialise min value on first array member */
	int min = arr[0];

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] < min)
			min = arr[i];
	}
	return min;
}

/* Finds index of maximum of array */
size_t
intimax(const int *arr, size_t len)
{
	/* Initialise max value and its index */
	int max = arr[0];
	size_t imax;

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] > max ){
			max = arr[i];
			imax = i;
		}
	}
	return imax;
}


/* Finds index of minimum of array */
size_t
intimin(const int *arr, size_t len)
{
	/* Initialise min value and its index */
	int min = arr[0];
	size_t imin = 0;

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] < min ){
			min = arr[i];
			imin = i;
		}
	}
	return imin;
}

/* Sums the members of an integer array */
int
intsum(const int *arr, size_t len)
{
	int sum = 0;
	for(size_t i=0; i<len; i++)
		sum += arr[i];
	return sum;
}

/* Makes all array members positive */
int *
intpos(int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = abs(arr[i]);
	return arr;
}

/* Makes all array members negative */
int *
intneg(int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = (-1)*abs(arr[i]);
	return arr;
}

/* Switch the sign of array members */
int *
intsign(int *arr, size_t len)
{
	for(size_t i=0; i<len; i++){
		if(arr[i] > 0)
			arr[i] = -arr[i];
		else
			arr[i] = abs(arr[i]);
	}
	return arr;
}

/*
Moves array values an input number of places in the array.
A positive offset moves values forward, and a negative one, backwards.
*/
int *
introll(int *arr, size_t len, int offset)
{
	if(offset == 0)
		return arr;

	int buffer[len];
	int *buff = &(buffer[0]);
	size_t ind = 0;

	//Simplifying offset
	while( (size_t)abs(offset) >= len)
	{
		if (offset > 0)
			offset = offset - len;
		else if (offset < 0)
			offset = offset + len;
	}

	//Calculating roll
	if (offset < 0)
	{
		for(size_t i=0; i<len; i++)
		{
			ind = i + abs(offset);
			if ( ind >= len )
				ind = i + abs(offset) - len;
			buff[i] = arr[ind];
		}
	}

	else if (offset > 0)
	{
		for(size_t i=0; i<len; i++)
		{
			ind = len + i - offset;
			if (ind >= len)
				ind = i - offset;
			buff[i] = arr[ind];
		}
	}

	arr = intcpy(arr, buffer, len);
	return arr;
}


/*
Delete array element specified by input index.
Note that new length is reduced by one.
*/
int *
intdel(int *arr, size_t len, size_t index)
{
	if (index >= len)
		return arr;
	for(size_t i=index; i<(len-1); i++)
		arr[i] = arr[i+1];
	return arr;
}


/*
Insert a given value at the specified index
of an array of given length.
Provide enough memory for new element in
destination array. A pointer to this array is returned.
*/
int *
intins(int *dest, const int *arr, size_t len, size_t index, int val)
{
	dest = intcpy(dest, arr, len);
	if (index >= len){
		dest[len] = val;
		return dest;
	}
	for(size_t i=len; i>index; i--)
		dest[i] = arr[i-1];
	dest[index] = val;
	return dest;
}

/*
Insert array element of input value at a specified index
to an input array of given length.
The resulting array is allocated and a pointer to it is
returned.
Note that the size of the new array is one integer longer
than the size of the previous one, and must be freed
after its use.
*/
int *
intinsA(const int *arr, size_t len, size_t index, int val)
{
	int *dest = intzerosA(len+1);
	if(!dest)
		return (NULL);
	intins(dest, arr, len, index, val);
	return dest;
}


//intissort - sorts array and returns list of array indices

/*
Adds the values of two integer arrays of equal length,
and the result is saved in the memory of the first array.
*/
int *
intadd(int *dest, const int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] + arr[i];
	return dest;
}

/*
Subtracts the values of two integer arrays of equal length;
the result is saved in the memory of the first array.
*/
int *
intsub(int *dest, const int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] - arr[i];
	return dest;
}

//intmult - multiplies members of two arrays
int *
intmult(int *dest, const int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] * arr[i];
	return dest;
}

//intfunc - applies given function to array members
int *
intfunc(int (*func)(int), int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = (*func)(arr[i]);
	return arr;
}

/*
Compares two arrays 'a' and 'b' and returns a value that
is zero if a==b, positive if a>b, and negative if a<b.
*/
int
intcmp(const int *a, const int *b, size_t len)
{
	int cmp = abs(intsum(a,len)) - abs(intsum(b,len));
	return cmp;
}

//intsadd - add a scalar to all array members.
int *
intsadd(int *arr, size_t len, int val)
{
	for(size_t i=0; i<len; i++)
		arr[i] = arr[i] + val;
	return arr;
}

//intsmult - multiply all array members by a scalar
int *
intsmult(int *arr, size_t len, int val)
{
	for(size_t i=0; i<len; i++)
		arr[i] = arr[i]*val;
	return arr;
}

//intdot - dot product of two arrays
int
intdot(const int *a, const int *b, size_t len)
{
	int *arr = intcpyA(a, len);
	int dot = intsum(intmult(arr, b, len), len);
	free(arr); 
	return dot;
}






/*
	DOUBLE 1D ARRAYS
*/


/* Generates an array of a given value */
double *
fltval(double * arr, size_t s, double val)
{
	for(size_t i=0; i<s; i++)
		arr[i] = val;
	return arr;
}

/* Generates an array of a given value */
double *
fltvalA(size_t s, double val)
{
	double *arr = (double *) malloc(s*sizeof(double));
	if(!arr)
		return (NULL);
	fltval(arr, s, val);
	return arr;
}

/* Generates an array of zeros */
double *
fltzeros(double *arr, size_t s)
{
	fltval(arr, s, 0);
	return arr;
}

/*
Allocates and generates an array of zeros.
You will need to free the pointer afterwards manually.
*/
double *
fltzerosA(size_t s)
{
	double *arr = fltvalA(s, 0);
	return arr;
}

/* Generates an array of ones */
double *
fltones(double *arr, size_t s)
{
	fltval(arr, s, 1);
	return arr;
}

/*
Allocates and generates an array of ones.
You will need to free the pointer afterwards manually.
*/
double *
fltonesA(size_t s)
{
	double *arr = fltvalA(s, 1);
	return arr;
}

/* Generates an array of values in a range */
double *
fltrange(double *arr, size_t s, 
		double start, double step)
{
	double val = start;
	for(size_t i=0; i<s; i++){
		arr[i] = val;
		val += step;
	}
	return arr;
}

/*
Allocates and generates an array of values in a range.
You will need to free the pointer afterwards.
*/
double *
fltrangeA(size_t s, double start, double step)
{
	/*Allocating pointer*/
	double *arr = (double *) malloc(s*sizeof(double));
	if(!arr)
		return (NULL);
	/*Evaluating array*/
	double val = start;
	for(size_t i=0; i<s; i++){
		arr[i] = val;
		val += step;
	}
	return arr;
}

/* Copies an array to another */
double *
fltcpy(double *dest, const double *src, size_t s)
{
	if( !dest || !src)
		return (NULL);
	for(size_t i=0; i<s; i++)
		dest[i] = src[i];
	return dest;
}

/*
Copies an array into another array it allocates,
and returns a pointer to it.
You will have to free it afterwards.
*/
double *
fltcpyA(const double *src, size_t s)
{
	if(!src)
		return (NULL);
	double *dest = (double *) malloc(s*sizeof(double));
	if(!dest)
		return (NULL);
	fltcpy(dest, src, s);
	return dest;
}

/* Concatenates two arrays of integers into destination */
double *
fltcat(double *dest, const double *a, size_t as, 
		const double *b, size_t bs)
{
	/* Check input */
	if (!dest || !a || !b)
		return (NULL);
	/* Append first array */
	fltcpy(dest, a, as);
	/* Append second array */
	fltcpy(dest+as, b, bs);
	return dest;
}

/*
Concatenates two arrays of integers,
allocates an array with the result,
and returns a pointer to it.
You will have to free it afterwards.
*/
double *
fltcatA(const double *a, size_t as, 
		const double *b, size_t bs)
{
	/* Check input */
	if (!a || !b)
		return (NULL);

	double *dest = (double *) malloc((as+bs)*sizeof(double));
	if(!dest)
		return (NULL);
	fltcpy(dest, a, as);
	fltcpy(dest+as, b, bs);
	return dest;
}

/* Prints an array of integers to stdout */
void
fltprint(const double *src, size_t s)
{
	for(size_t i=0; i<s; i++)
		printf("%g ", src[i]);
	printf("\n");
}

/* Reverses input array */
double *
fltrev(double *arr, size_t len)
{
	/*Check input */
	if(arr == NULL)
		return arr;

	/* Declaring temporary space to save string */
	double buffer[len];
	double *b = &(buffer[0]);

	/* Copying original string */
	fltcpy(b, arr, len);

	/* Reversing string from buffer */
	for(size_t i=0; i<len; i++)
		arr[i] = buffer[len-i-1];

	return arr;
}



/* 	STATISTICS */
/* Finds maximum of array */
double
fltmax(const double *arr, size_t len)
{
	/* Initialise max value on first array member */
	double max = arr[0];
	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] > max)
			max = arr[i];
	}
	return max;
}

/* Finds minimum of array */
double
fltmin(const double *arr, size_t len)
{
	/* Initialise min value on first array member */
	double min = arr[0];

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] < min)
			min = arr[i];
	}
	return min;
}

/* Finds index of maximum of array */
size_t
fltimax(const double *arr, size_t len)
{
	/* Initialise max value and its index */
	double max = arr[0];
	size_t imax;

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] > max ){
			max = arr[i];
			imax = i;
		}
	}
	return imax;
}

/* Finds index of minimum of array */
size_t
fltimin(const double *arr, size_t len)
{
	/* Initialise min value and its index */
	double min = arr[0];
	size_t imin = 0;

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] < min ){
			min = arr[i];
			imin = i;
		}
	}
	return imin;
}

/* Sums the members of an integer array */
double
fltsum(const double *arr, size_t len)
{
	double sum = 0;
	for(size_t i=0; i<len; i++)
		sum += arr[i];
	return sum;
}

/* Makes all array members positive */
double *
fltpos(double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = fabs(arr[i]);
	return arr;
}

/* Makes all array members negative */
double *
fltneg(double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = (-1)*fabs(arr[i]);
	return arr;
}

/* Switch the sign of array members */
double *
fltsign(double *arr, size_t len)
{
	for(size_t i=0; i<len; i++){
		if(arr[i] > 0)
			arr[i] = -arr[i];
		else
			arr[i] = fabs(arr[i]);
	}
	return arr;
}

/*
Moves array values an input number of places in the array.
A positive offset moves values forward, and a negative one, backwards.
*/
double *
fltroll(double *arr, size_t len, int offset)
{
	if(offset == 0)
		return arr;

	double buffer[len];
	double *buff = &(buffer[0]);
	size_t ind = 0;

	//Simplifying offset
	while( (size_t)abs(offset) >= len)
	{
		if (offset > 0)
			offset = offset - len;
		else if (offset < 0)
			offset = offset + len;
	}

	//Calculating roll
	if (offset < 0)
	{
		for(size_t i=0; i<len; i++)
		{
			ind = i + abs(offset);
			if ( ind >= len )
				ind = i + abs(offset) - len;
			buff[i] = arr[ind];
		}
	}

	else if (offset > 0)
	{
		for(size_t i=0; i<len; i++)
		{
			ind = len + i - offset;
			if (ind >= len)
				ind = i - offset;
			buff[i] = arr[ind];
		}
	}

	arr = fltcpy(arr, buffer, len);
	return arr;
}


/*
Delete array element specified by input index,
store in input array 'dest', and return a pointer to it.
Note that 'must' have a size of at least len-1.
*/
double *
fltdel(double *dest, const double *arr, 
			size_t len, size_t index)
{
	fltcpy(dest, arr, len-1);
	if (index >= len)
		return dest;
	for(size_t i=index; i<(len-1); i++)
		dest[i] = arr[i+1];
	return dest;
}


/*
Delete array element specified by input index,
store new array in allocated memory, and return a
pointer to it.
Note that the size of the new array is one integer shorter
than the size of the previous one, and must be freed
after its use.
*/
double *
fltdelA(const double *arr, size_t len, size_t index)
{

	double *dest = fltcpyA(arr, len-1);
	if (index >= len)
		return dest;
	for(size_t i=index; i<(len-1); i++)
		dest[i] = arr[i+1];
	return dest;
}


/*
Insert a given value at the specified index
of an array of given length.
Provide enough memory for new element in
destination array. A pointer to this array is returned.
*/
double *
fltins(double *dest, const double *arr, 
		size_t len, size_t index, double val)
{
	dest = fltcpy(dest, arr, len);
	if (index >= len){
		dest[len] = val;
		return dest;
	}
	for(size_t i=len; i>index; i--)
		dest[i] = arr[i-1];
	dest[index] = val;
	return dest;
}

/*
Insert array element of input value at a specified index
to an input array of given length.
The resulting array is allocated and a pointer to it is
returned.
Note that the size of the new array is one integer longer
than the size of the previous one, and must be freed
after its use.
*/
double *
fltinsA(const double *arr, size_t len, size_t index, double val)
{
	double *temp = fltzerosA(len+1);
	if(!temp)
		return (NULL);
	fltins(temp, arr, len, index, val);
	return temp;
}


//intissort - sorts array and returns list of array indices

/*
Adds the values of two integer arrays of equal length,
and the result is saved in the memory of the first array.
*/
double *
fltadd(double *dest, const double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] + arr[i];
	return dest;
}

/*
Subtracts the values of two integer arrays of equal length;
the result is saved in the memory of the first array.
*/
double *
fltsub(double *dest, const double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] - arr[i];
	return dest;
}
/* Multiplies two arrays element-wise */
double *
fltmult(double *dest, const double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] * arr[i];
	return dest;
}

/* Applies an input function to the array elements individually */
double *
fltfunc(double (*func)(), double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = (*func)(arr[i]);
	return arr;
}

/*
Compares two arrays 'a' and 'b' and returns a value that
is zero if a==b, and non-zero if a!=b.
*/
double
fltcmp(const double *a, const double *b, size_t len)
{
	double temp[len];
	double *t = &(temp[0]);
	t = fltcpy(t, a, len);
	fltsub(t, b, len);
	double cmp = fltsum(fltpos(t, len), len);
	return cmp;
}

/* Adds a scalar value to all array elements */
double *
fltsadd(double *arr, size_t len, double val)
{
	for(size_t i=0; i<len; i++)
		arr[i] = arr[i] + val;
	return arr;
}

/* Multiplies all array elements by a scalar value */
double *
fltsmult(double *arr, size_t len, double val)
{
	for(size_t i=0; i<len; i++)
		arr[i] = arr[i]*val;
	return arr;
}

/* Calculates inverse of array elements */
double *
fltinv(double *arr, size_t len)
{
	for(size_t i=0; i<len; i++){
		arr[i] = pow(arr[i], -1);
	}
	return arr;
}

/* Calculates exp() of array elements */
double *
fltexp(double *arr, size_t len)
{
	double (*func_ptr)(double) = &exp;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates square root of array elements */
double *
fltsqrt(double *arr, size_t len)
{
	double (*func_ptr)(double) = &sqrt;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates sine of array elements */
double *
fltsin(double *arr, size_t len)
{
	double (*func_ptr)(double) = &sin;
	fltfunc(func_ptr, arr, len);
	return arr;
}

/* Calculates cosine of array elements */
double *
fltcos(double *arr, size_t len)
{
	double (*func_ptr)(double) = &cos;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates natural log of array elements */
double *
fltlog(double *arr, size_t len)
{
	double (*func_ptr)(double) = &log;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates base 10 log of array elements */
double *
fltlog10(double *arr, size_t len)
{
	double (*func_ptr)(double) = &log10;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates dot product of array */
double
fltdot(const double *a, const double *b, size_t len)
{
	double temp[len];
	double *t = &(temp[0]); 
	t = fltcpy(t, a, len);
	double dot = fltsum(fltmult(t, b, len), len);
	return dot;
}

/* Get magnitude of array vector */
double
fltmag(const double *arr, size_t len)
{
	return sqrt(fltdot(arr,arr,len));
}

/*
Find if array member is a value.
Returns array of 0s and 1s, where 0 is not value, and 1 is value.
Note that return array must have enough memory.
*/
int *
fltisval(int *dest, const double *arr, size_t len, double val)
{
	dest = intzeros(dest, len);
	for (size_t i=0; i<len; i++){
		if(arr[i] == val)
			dest[i] = 1;
	}
	return dest;
}


/*
Looks for NaN values in array
Returns array of 0s and 1s.
Note that return array must have enough memory.
*/
int *
fltisnan(int *dest, const double *arr, size_t len)
{
	dest = intzeros(dest, len);
	for (size_t i=0; i<len; i++){
		if(arr[i] != arr[i])
			dest[i] = 1;
	}
	return dest;
}


/* Converts an array of integers into an array of doubles */
double *
inttoflt(double *dest, const int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = (double)(arr[i]);
	return dest;
}

/*
Converts an array of integers into an array of doubles,
allocates the new array, and returns a pointer to it.
*/
double *
inttofltA(const int *arr, size_t len)
{
	double *dest = fltzerosA(len);
	for(size_t i=0; i<len; i++)
		dest[i] = (double)(arr[i]);
	return dest;
}

/* Converts an array of doubles into an array of integers */
int *
flttoint(int *dest, const double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = (int)(arr[i]);
	return dest;
}

/*
Converts an array of doubles into an array of integers,
allocates the new array, and returns a pointer to it.
*/
int *
flttointA(const double *arr, size_t len)
{
	int *dest = intzerosA(len);
	for(size_t i=0; i<len; i++)
		dest[i] = (int)(arr[i]);
	return dest;
}






/*
	INPUT FUNCTIONS
*/


/*
Asks user for input with a message,
and returns a string.
*/
char *
getstr(char *dest, const char *msg)
{
	size_t max_read = (size_t) 1E5;
	printf("%s", msg);
	char *ptr = fgets(dest, max_read, stdin);
	if(!ptr){
		printf(" Warning: no input read.\n");
		return (NULL);
	}
	// Removes newline character from end of string
	if (strchr(dest, '\n'))
		strslc(dest, 0, strlen(dest)-2);
	return dest;
}


/*
Converts a input string 'str' into an integer.
The result is stored at the input pointer 'dest'.
On fail, NULL is returned.
*/
int *
strtoint(int *dest, const char *str)
{
	char *endptr;
	int val;
	if(!str){
		fprintf(stderr, " Error: can't convert NULL to int.\n");
		return (NULL);
	}
	//Convert string to integer.
	val = (int) strtol(str, &endptr, 10);
	//Checks if conversion worked
	if(endptr == str){
		fprintf(stderr, " Error: can't convert '%s' to int.\n", str);
		return (NULL);
	}
	*dest = val;
	return dest;
}


/*
Converts and array of strings if length 'size' 
into an array of integers.
Values are stored in memory of input array 'dest'.
*/
int *
strtointArr(int *dest, const char **str, size_t size)
{
	for(size_t i=0; i<size; i++){
		int *ret = strtoint(&(dest[i]), str[i]);
		if(!ret)
			return (NULL);
	}
	return dest;
}



/*
Convert string to double.
*/
double *
strtoflt(double *dest, const char *str)
{
	char *endptr;
	int val;
	if(!str){
		fprintf(stderr, " Error: can't convert NULL to double.\n");
		return (NULL);
	}
	// Converts string to double
	val = (double) strtod(str, &endptr);
	// Checks if conversion worked
	if(endptr == str){
		fprintf(stderr, " Error: can't convert '%s' to double.\n", str);
		return (NULL);
	}
	*dest = val;
	return dest;
}

/*
Converts and array of strings of length 'size' 
into an array of doubles.
Values are stored in memory of input array 'dest'.
*/
double *
strtofltArr(double *dest, const char **str, size_t size)
{
	for(size_t i=0; i<size; i++){
		double *ret = strtoint(&(dest[i]), str[i]);
		if(!ret)
			return (NULL);
	}
	return dest;
}



/*
Given a string and a delimiter,
it returns the number of tokens in the string.
*/
size_t
strtokn(char *str, const char *delim)
{
	if(!str)
		return 0;
	size_t n = 0;
	for(size_t i=0; i<strlen(str); i++){
		if(str[i] == *delim)
			n++;
	}
	return (n+1);
}


/*
Given a string and a delimiter,
it runs through the first field
of the string until the delimiter,
substitutes the delimiter by a "\0",
and returns a pointer to the next field.
If the end of the string is reached, a NULL
pointer is returned.
*/
char *
strpar(char *ptr, const char delim)
{
	if(!ptr)
		return (NULL);
 
	while(1)
	{
		if(ptr[0] == delim){
			ptr[0] = '\0';
			ptr++;
			break;
		}

		else if(ptr[0] == '\0')
			return (NULL);
		ptr++;
	}

	return ptr;
}

/*
Given a string 'str' and a delimiter 'delim',
it splits the string at the delimiters, stores
the pointers to the tokens in 'dest', and returns
a pointer to it.
On fail, it returns NULL.
*/
char **
strsplit(char **dest, char *str, const char delim)
{
	if(!str)
		return (NULL);

	char *ptr = str;
	size_t c = 0;

	while( ptr != NULL ){
		dest[c] = ptr;
		c++;
		ptr = strpar(ptr, delim);
	}

	return dest;
}




/*
Counts the lines in a txt file,
and returns the value.
The counting process discards empty lines
and comment lines, defined by an input starting character.

Input:
	size_t maxRead:	maximum size in which to store a file line.
	char *path:		string to file path.
	char *comment:	pointer to character that defines file comment.
Output:
	size_t lineCount:	number of non-comment non-empty lines in file.
*/
size_t
CountTxtLines(size_t maxRead, const char *path, const char *comment)
{
	FILE *fdata;
    fdata = fopen(path, "r");
    if(!fdata){
    	fprintf(stderr, " Error: '%s' file not found.\n", path);
    	return 0;
    }

	char line[maxRead];
    size_t lineCount = 0;
    while(fgets(line, maxRead, fdata))
    {
    	//Ignore comment lines
    	if (line[0] == *comment)
    		continue;
    	//Ignore empty lines
    	if (line[0] == '\n')
    		continue;
    	lineCount++;
    }

    fclose(fdata);
    return lineCount;
}


/*
Reads the non-comment lines from a txt 
and returns the strings.
One should first call CountTxTLines, then initialize
enough memory.

Input:
	char *path: 	string with file path.
	char **lines: 	pointer to array of pointers of strings
					with enough memory to hold all the lines.
	size_t MaxRead: memory size of each line in chars.
	char *comment: 	comment character.

Output:
	NULL:			if file not found.
	char **lines:	input pointer defined above.
*/
char **
ReadTxtLines(char **lines, size_t maxRead, 
				const char *path, const char *comment)
{
	// Open file
	FILE *fdata;
    fdata = fopen(path, "r");
    if(!fdata){
    	fprintf(stderr, " Error: '%s' file not found.\n", path);
    	return (NULL);
    }

	char line[maxRead];
    size_t lineCount = 0;
    while(fgets(line, maxRead, fdata))
    {
    	//Ignore comment lines
    	if (line[0] == *comment)
    		continue;
    	//Ignore empty lines
    	if (line[0] == '\n')
    		continue;
    	strcpy(lines[lineCount], line);
    	lineCount++;
    }
    return lines;
}


/*
Reads data from a file, separated into rows and columns
by an input delimiter

Input:
	size_t *shape: 	pointer to array of two members, stores
					number of rows and columns of data.
	size_t maxSize:	maximum size in which to store file line.
	char *path: 	string with file path.
	char delim:		character data delimiter.
	char comment:	character that indicates a comment to skip
					in the file.
Output:
	char **data:	pointer to allocated memory of size
					shape[0] * shape[1] * maxSize
					Individual strings can be accessed via
					data[r*cols + c]
					where 'r' and 'c' are the row and column
					of the string, and 'cols' is the total number
					of columns.
					As it is allocated, it must be freed afterwards.
					Both the pointer **data and the individual strings
					must be freed.
	NULL:			If file not found, empty, or has uenxpected format;
					and if memory allocation error occurs.
*/
char **
GenFromTxt(const char *path, size_t *shape, const size_t maxSize, 
			const char delim, const char comment)
{
	//Initialise shape to 0
	shape[0] = 0;
	shape[1] = 0;

	//Counting rows
	size_t lineCount = CountTxtLines(maxSize, path, &comment);
	if(lineCount == 0)
		return (NULL);

	//Initializing pointer to array of lines
	char lines[lineCount][maxSize];
	char *lptr[lineCount];
	for(size_t i=0; i<lineCount; i++)
		lptr[i] = &(lines[i][0]);
	char **l = &(lptr[0]);

	//Reading lines
	ReadTxtLines(l, maxSize, path, &comment);

	//Removing final newline characters
	for(size_t i=0; i<lineCount; i++)
		strslc(l[i], 0, strlen(l[i])-2);

	//Read delimiters from each line to confirm
	//expected number of tokens
	size_t tokens[lineCount];
	for(size_t i=0; i<lineCount; i++){
		tokens[i] = strtokn(l[i], &delim);
	}

	//Compare all tokens to first one
	size_t initToken = tokens[0];
	for(size_t i=0; i<lineCount; i++){
		if (tokens[i] != initToken){
			fprintf(stderr, " Error: wrong number of columns at line %d\n", (int) i);
			return (NULL);
		}
	}

	//Allocate array of strings
	size_t bytes = lineCount*initToken*sizeof(char*);
	char **m = malloc(bytes);
	if(!m){
		fprintf(stderr, " Error: failed to allocate %Iu bytes\n", bytes);
		return (NULL);
	}

	//Allocate individual strings
	int allocFail = (-1);
	for(size_t i=0; i<(lineCount*initToken); i++){
		m[i] = malloc(maxSize*sizeof(char));
		if(!m){
			allocFail = (int)i;
			fprintf(stderr, " Error: failed to allocate %Iu bytes\n", maxSize*sizeof(char));
			break;
		}
	}

	//If failed to allocate a string, free those already allocated
	if(allocFail >= 0){
		for(int i=0; i<allocFail; i++)
			free(m[i]);
		free(m);
		return(NULL);
	}

	//Tokenize
	for(size_t i=0; i<(lineCount); i++){
		//Split lines
		char *ptr = l[i];
		size_t c = 0;
		char *p[initToken];
		while( ptr != NULL ){
			p[c] = ptr;
			c++;
			ptr = strpar(ptr, delim);
		}
		//Save in allocated memory
		for(size_t j=0; j<(initToken); j++)
			strcpy(m[j+i*initToken],p[j]);
	}
	
	//Save shape in input pointer
	shape[0] = lineCount;
	shape[1] = initToken;

	return (m);
}



//int SaveToTxt(const char **data, size_t *shape, char *filename)


//array of doubles into strings
//array of ints into strings