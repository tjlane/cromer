/*  convert cromer xsect data to binary
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define DATAFILE	"XSECTDAT2.ORG"
#define	LISTFILE	"RECORD.LIST"
#define	BINFILE		"XSECTDAT2X.BIN"


int fgetl(char *line, int n, FILE *fp);

int main (int argc, const char * argv[])
{
	FILE	*in;				/* file id for input file */
	FILE	*out;				/* file descriptor for output */
	FILE	*list;
	int		n;					/* number of term read in */
	int		i;					/* loop index */
	fpos_t	frecord;			/* starting record for an element */
	unsigned long record[104];	/* starting record for an element */
	int		z;					/* the atomic number */
	int		if_flag;
	int		nj;
	int		fgetl();
	size_t	c_byte;				/* size of atom name to write */
	size_t	i_byte;				/* size of an integer */
	size_t	d_byte;				/* size of a double */
	double	a,b,c,d;
	char	shell[7];
	char	nat[3];
	char	line[81];
	char	elements[104][3] ={ "  ",
		"H ","HE","LI","BE","B ","C ","N ","O ","F ","NE",
		"NA","MG","AL","SI","P ","S ","CL","AR","K ","CA",
		"SC","TI","V ","CR","MN","FE","CO","NI","CU","ZN",
		"GA","GE","AS","SE","BR","KR","RB","SR","Y ","ZR",
		"NB","MO","TC","RU","RH","PD","AG","CD","IN","SN",
		"SB","TE","I ","XE","CS","BA","LA","CE","PR","ND",
		"PM","SM","EU","GD","TB","DY","HO","ER","TM","YB",
		"LU","HF","TA","W ","RE","OS","IR","PT","AU","HG",
		"TL","PB","BI","PO","AT","RN","FR","RA","AC","TH",
		"PA","U ","NP","PU","AM","CM","BK","CF","ES","FM",
		"MD","NO","LW" };
	
	for(i=0;i<104;i++) {
		elements[i][2]='\0';
		record[i] = 0;
	}
	
	printf("sizeof(fpos_t) = %ld\n",sizeof(fpos_t));
	
	c_byte = 2;
	i_byte = sizeof nj;
	d_byte = sizeof b;
	
	z = 2;							/* this corresponds to He */
	
	in = fopen(DATAFILE,"r");
	if (in==NULL) { printf("unable to open input file '%s'\n",DATAFILE); exit(1); }
	out = fopen(BINFILE,"wb");		/* open(out,file=BIN,status='new',access='direct',recl=30) */
	
	while (1) {
		line[0] = '\0';
		if (!fgetl(line, 80,in)) { printf("EOF in fgetl"); break; }
		n = sscanf(line,"%2s%6d %s %15le%15le%15le%15le%2d",nat, &nj, shell, &a, &b, &c, &d, &if_flag);
		if (nat[1]<' ') {nat[1]=' ';nat[2]='\0';}	/* names must be exactly 2 chars */
		if (!strcmp(nat,elements[z+1])) {			/* nat is next element, so increment z */
			z += 1;
			fgetpos(out,&frecord);		/* fgetpos(out,record+z); */
			record[z] = frecord;
			printf("starting work on %s,   Atomic No. = %d\n",nat,z);
		}
		if (n==EOF) { printf("found EOF in sscanf\n"); break; }
		if (n!=6 && n!=8) { printf("n not 8 or 6, big problem\n"); exit(1); }
		fwrite(nat,1,c_byte,out);
		fwrite(&nj,1,i_byte,out);
		fwrite(&b,1,d_byte,out);
		fwrite(&c,1,d_byte,out);
		if(n==8) {
			fwrite(&d,1,d_byte,out);
			fwrite(&if_flag,1,i_byte,out);
		}
	}
	fclose (in);
	fclose(out);
	
	list = fopen(LISTFILE,"w");
	for (i=0;i<104;i++) {
		fprintf(list," %lu,",record[i]);
		if (((i+1)-(((i+1)/7)*7))==0) fprintf(list,"\n");	/* (i-((i/7)*7)) = mod(i,7) */
		/* WRITE (3,"(3X,7(I5,', '))") record */
	}
	
	fclose(list);
	return 0;
}



int fgetl(
char	*line,
int		n,						/* maximum length to read */
FILE	*fp)
{
	int		j;
	
	if (fgets(line,n,fp)==NULL) {		/*	status = fgets(line,n,fp);	*/
		line[0] = '\0';
		return(0);
	}
	
	for (j=0; j<n; j++) {
		if (line[j]=='\n') {
			line[j] = '\0';
			return(1);
		}
	}
	line[n] = '\0';
	return(1);
}
