Cromer Form Factors
===================

This is a legacy code written by Don Cromer for calculating atomic form factors. 

This code was provided to me by Jon Tischler, and I am throwing it up here for posterity. I have made no attempts to verify its correctness or improve its usability. So use with caution. That said, the code is extensive and appears to provide decent support for computing cross sections.

Before using this code, however, you might want to check out Peter Kiezle's more modern python module, periodictable:

https://github.com/pkienzle/periodictable

Happy scattering!


Install
-------

Go into the make_cromer folder and build and run main.c.  This should create the file "XSECTDAT2X.BIN".  It will also create "RECORD.LIST" which you do not need.

Copy XSECTDAT2X.BIN to wherever the final executable will be.  The executable needs XSECTDAT2X.BIN to run.

Build & run main.c, get_fp.c

When you run it, use the default values are Zr and 8 keV.

This should produce the same values provided in in "old result".

Example
-------

When I run it my console shows:

	Running…
	warning: this program uses gets(), which is unsafe.
	give the atom type (i.e. Fe+3), ['Zr']: 
	give the energy (KeV) [<cr> --> 8] 
	give the H vector (2π/d) [<cr> --> 0] 
	 fo(Zr, 1.5498 Ang) = 39.9947,     mu/rho = 130.79 (cm^2/g)
	 df(Zr, 8 keV) = 39.6834 + i 2.26738
