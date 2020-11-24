/*------------------------------------------------------------------------------

Program file: bgagnonp3.c
Author:       Brett Gagnon
Date:         2/17/2019
Assignment:   Program #3
Objective:    Write a C program that prompts the user to enter some information about up to ten
individuals. It should store this information in a structure. The program should obtain
the information from the structure, and output it in mailing label format.
              
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Two Function Prototypes */
/*----------------------------------------------------------------------------*/

void safer_gets (char array[], int max_chars);

bool equalStrings (const char  s1[], const char  s2[]);


/* Declare structures below */
/*----------------------------------------------------------------------------*/     			
struct information
{
	char full_name[35];
	char address[50];
	char city[25];
	char state[3];
	long zip_code;
};
            
struct  states
{
	char abbr[3];
}; 
			
int main()
{
	
/* Declare variables below */
/*----------------------------------------------------------------------------*/
	int entries = 51;
	int test;
	int x, n;
 	struct information person[10];
  	const struct states members[51] =
		{"AL",    "AK",    "AZ",    "AR",    "CA",    "CO",    "CT",    "DE",    "DC",   
      	"FL",    "GA",    "HI",    "ID",    "IL",    "IN",    "IA",    "KS",    "KY",   
      	"LA",    "ME",    "MD",    "MA",    "MI",    "MN",    "MS",    "MO",    "MT",   
      	"NE",    "NV",    "NH",    "NJ",    "NM",    "NY",    "NC",    "ND",    "OH",   
      	"OK",    "OR",    "PA",    "RI",    "SC",    "SD",    "TN",    "TX",    "UT",   
      	"VT",    "VA",    "WA",    "WV",    "WI",    "WY"};

/* Ask user how many labels they want generated */
/*----------------------------------------------------------------------------*/
             
	printf ("Welcome to the mailing label generator program.\n\n");
	printf ("How many people do you want to generate labels for (0-10)?: ");
		
/* Do while loop to make sure labels are between 0-10 */
/*----------------------------------------------------------------------------*/	
	do
	{				
		scanf ("%i", &x);
		fflush (stdin);
		if ( x == 0 )
		exit(0);
		
		else if ( x < 0 || x > 10 )
		printf ("Please enter a number between 1 and 10: ");
	}
		while ( x < 0 || x > 10 ); /*end while loop */
      		
/* Prompt user for the required info (name, address, etc) and store in struct */
/*----------------------------------------------------------------------------*/

	for ( n = 0;  n < x;  n++)
	{
		printf ("\nEnter name: ");
		safer_gets( person[n].full_name, 35);
		fflush (stdin);
			                          
 		printf ("Enter street address: ");
       	safer_gets( person[n].address, 50);
       	fflush (stdin);
                        
       	printf ("Enter city: ");
        safer_gets( person[n].city, 25);
        fflush (stdin);
            
/* Do while loop to make sure the state entered is valid */
/*----------------------------------------------------------------------------*/		
		do
		{ 	
			printf ("Enter state: ");
			fflush (stdin);
			scanf ("%2s", &person[n].state, 3);
			fflush (stdin);			
			strupr (person[n].state);
			
/* Use statesearch function to make sure the state entered matches a valid state */
/*----------------------------------------------------------------------------*/

			test = statesearch (members, person[n].state, entries);			
			if ( test == -1 )
			printf ("Please enter a two-letter abbreviation for a U.S. State: \n");
		}
			while ( test == -1 ); /*end while loop */
			
/* Do while loop to ensure zip code is 5 digits */
/*----------------------------------------------------------------------------*/                        
		do
		{
  			printf ("Enter zip code: ");
     		scanf ("%ld", &person[n].zip_code, 5);
			fflush (stdin);
			if 
			(  person[n].zip_code < 00001 || person[n].zip_code > 99999 )
			
			printf ("Please enter a 5-digit Zip Code:\n");
		}
			while 
			(  person[n].zip_code < 00001 || person[n].zip_code > 99999 ); /*end while loop */
						
						
            } /* end for loop */

/* Output the user's information in mailing label format */
/*----------------------------------------------------------------------------*/
     					
	printf ("\nBelow are your mailing labels:\n\n");
			
	for ( n = 0;  n < x;  n++)
 	{				
 		printf ("%s\n%s\n%s, %s %.5ld\n\n",
		person[n].full_name, person[n].address, 
		person[n].city, person[n].state, 
		person[n].zip_code ) ;
				
	} /* end for loop */

} /* end main */

/* Function safer_gets */
/*----------------------------------------------------------------------------*/
			
void safer_gets (char array[], int max_chars)
{
  int i;

/* Read name from input buffer, character by character,   */
/* up until the maximum number of characters in the array.*/
/* ------------------------------------------------------ */

  for (i = 0; i < max_chars; i++)
  {
     array[i] = getchar();

     /* If "this" character is the carriage return,      */
     /* replace it with a null terminator and exit loop. */
     /* ------------------------------------------------ */

     if (array[i] == '\n')
     {
            array[i] = '\0';
            break;
     }

   } /* end for */

   /* If we have pulled out the most we can,       */
   /* and, if there are more chars in the buffer,  */
   /* clear out the remaining chars in the buffer. */
   /* This is equivalent to the fflush() function. */
   /* -------------------------------------------- */
   if (i == max_chars - 1 )

     if (array[i-1] != '\0')

       while (getchar() != '\n');

   /* Ensure the last element in the array contains the null terminator. */
   /* ------------------------------------------------------------------ */
   array[max_chars-1] = '\0';

} /* end safer_gets */

/* Function equalStrings  (to be used below in statesearch function) */
/*----------------------------------------------------------------------------*/

bool equalStrings (const char  s1[], const char  s2[])
{
    int  i = 0;
    bool areEqual;

    while ( s1[i] == s2 [i]  &&
    		s1[i] != '\0' &&  s2[i] != '\0' )
        	++i;

    if ( s1[i] == '\0'  &&  s2[i] == '\0' )
       areEqual = true;
    else
       areEqual = false;

    return areEqual;
}

/* Function to search states from an array */
/*----------------------------------------------------------------------------*/

int  statesearch (const struct states  members[], const char  search[],
             const int  entries)
{
    int  i;
    bool equalStrings (const char s1[], const char s2[]);

    for ( i = 0;  i < entries;  ++i )
        if ( equalStrings (search, members[i].abbr) )
            return i;

    return -1;
}
