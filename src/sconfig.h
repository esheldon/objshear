#ifndef _SCONFIG_HEADER
#define _SCONFIG_HEADER

#include "defs.h"
#include "vector.h"
#include "config.h"

#define CONFIG_KEYSZ 50

typedef struct {
    double H0;
    double omega_m;

    int64 healpix_nside;

    int shear_style;    // REDUCED, LENSFIT or METACAL
    int mask_style;     // NONE, SDSS or EQ
    int scstyle;        // POINT, INTERP or SAMPLE
    int sourceid_style; // NONE or INDEX
    int weight_style;   // UNIFORM or OPTIMAL

    // if the distance to the lens is input
    int Dlens_input;

    // will be zero unless scstyle==SIGMACRIT_STYLE_INTERP
    int64 nzl;
    // only fill in for scstyle==SIGMACRIT_STYLE_INTERP
    dvector* zl;  

    int64 nbin;

    int r_units; // units for radius
    int shear_units; // DELTASIG, SHEAR or BOTH
    
    int64 pairlog_rmax, pairlog_rmin; // r bin numbers between which pairs are printed to file; 
                                      // pairlog_rmax=0 for no printing
    int64 pairlog_nmax; // maximum number of pairs printed in each radial bin; <=0 for no maximum
    FILE *pair_fd; // file descriptor of pair log file
    
    double rmin; // mpc/h
    double rmax;

    // we fill these in
    double log_rmin;
    double log_rmax;
    double log_binsize;

    // optional parameters

    // min z lens to allow instead
    // of the full interpolation range
    double min_zlens_interp;

    // can demand zs > zl + zdiff_min when using source
    // z as truth
    double zdiff_min;

} ShearConfig;

ShearConfig* sconfig_read(const char* url);

ShearConfig* sconfig_free(ShearConfig* config);
void sconfig_print(ShearConfig* config);
void sconfig_open_pair_url(ShearConfig* config, const char* url);

#endif
