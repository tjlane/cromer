#ifndef _FCOMPLEX_DECLARE_T_typedef struct FCOMPLEX {float r,i;} fcomplex;#define _FCOMPLEX_DECLARE_T_#endifdouble get_fo(double,char[]);fcomplex get_fp(char	atom_in[],	/* atomtype, atom symbol + ionization */double	H,			/* 2*�/d */double	xk,			/* energy in KeV */int		nord,		/* order of interpolation [0,3] */float	*pmu);		/* mu over rho (cm^2/g) */