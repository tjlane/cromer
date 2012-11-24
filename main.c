#include <stdio.h>


/*	routine to compute the complex atomic structure factor */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <ctype.h>
#include <string.h>
#include "get_fp.h"

#define hc			12.39841857

double xask(double,char[]);
char *cask(char[],char[],char[],int);
char *upcase(char[],char[],int);


int main (int argc, const char * argv[]) {
 	fcomplex	fp;			/* atomic form factor includes fo and Honl corrections */
	fcomplex	dfp;		/* delta atomic form factor includes fo and Honl corrections */
	double		fo;			/* non-res atomic form factor */
	float		XK=8.;		/* energy in keV */
	float		H=0.;		/* 2*pi/d */
	char		atom[20];	/* atomtype, atom symbol + ionization */
	float		murho;		/* mu over rho (cm^2/g) */
	
	atom[0]='\0';
	atom[0]='Z' ; atom[1]='r' ; atom[2]='\0';
	
	cask(atom,"give the atom type (i.e. Fe+3)",atom,10);
	if (atom[0]==' ') { printf("No leading spaces allowed in atom type\n"); exit(1); }
	XK = xask(8.,"give the energy (KeV)");
	H = xask(H,"give the H vector (2π/d)");
	
	fo = get_fo(H,atom);
	fp = get_fp(atom,H,XK,2,&murho);
	dfp.r = fp.r - fo;
	dfp.i = fp.i;
	
	printf(" fo(Zr, %g Ang) = %g,     mu/rho = %g (cm^2/g)\n",hc/XK,fo,murho);
	printf(" df(Zr, %g keV) = %g + i %g\n",XK,fp.r,fp.i);
    return 0;
}




/***********************************************************************/

/*	Routine to request and return a string.  If a <cr> is the response
 *	then it returns "cdef".
 */
char	*cask(
char	*cdef,
char	*prompt,
char	*result,			/* final string */
int		n)					/* max length of result */
{
	int     id;				/* length of text in cdef */
	int     ip;				/* length of text in prompt */
	char    line[255];		/* used for getting inputline */
	
	id = strlen(cdef);
	ip = strlen(prompt);
	
	if (ip+7+3*id < 79) printf("%s, ['%s']: ",prompt,cdef);
	else if (3*id+6 < 79) printf("%s,\n['%s']: ",prompt,cdef);
	else if (ip+id+7 > 79) printf("%s, ['%s']:\n   ",prompt,cdef);
	else printf("%s,\n['%s']:\n   ",prompt,cdef);
	
	gets(line);
	if ((n<=0) || (n>254)) n=254;
	line[n] = '\0';						/* truncate to max length */
	if (strlen(line)>=1) {	strcpy(result,line); }
	else { strcpy(result,cdef); }
	return(result);
}


double  xask(
double  xdef,				/* default value */
char    *xname)				/* name of variable */
{
	/*
	 *      This routine asks for the value of variable "xname" and if no value
	 *      is given (ie. a <CR>) then returns "xdef".
	 */
	double  x;				/* the float read in */
	char    string[255];	/* input string */
	
	while (1) {
		printf("%s [<cr> --> %g] ",xname,xdef);
		gets(string);
		if (strlen(string)==0) return(xdef);
		if (sscanf(string,"%lf",&x)==1) return(x);
		upcase(string,string,255);
		if (!strcmp(string,"INF")) return (HUGE_VAL);
		printf("  ERROR -- try again\n");
	}
}


char *upcase(					/* FUNCTION, forces to upper case */
char	*from,
char	*to,
int     n)
{
	int     i;
	
	i = -1;
	do {
		i += 1;
		if (islower(from[i])) to[i] = from[i]-32;
		else to[i] = from[i];
	} while (to[i]!='\0' && i<n-1);
	to[n-1] = '\0';
	return(to);
}
