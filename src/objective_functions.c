/**
	List of objective functions used for non-linear minimization and to generate pseudocompounds
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <complex.h> 
#include "nlopt.h"
#include "MAGEMin.h"
#include "toolkit.h"

/**************************************************************************************/
/**************************************************************************************/
/**********************METABASITE DATABASE (Gree et al., 2016)*************************/
/**************************************************************************************/
/**************************************************************************************/

/**
    Endmember to xeos for L
*/
void p2x_mb_liq(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[7]  = d->p[8];
    d->iguess[2]   = d->p[1]/(d->p[1] + d->p[2]);
    d->iguess[3]   = (d->p[3] + d->iguess[7])/(d->iguess[7] + 1.0);
    d->iguess[4]  = (d->p[4] + d->iguess[7])/(d->iguess[7] + 1.0);
    d->iguess[0]    = d->p[0]/(d->iguess[7] + 1.0);
    d->iguess[6]   = d->p[5]/(d->p[5] + d->p[6]);
    d->iguess[1]  = (d->p[1] + d->p[2])/(d->iguess[7] + 1.0);
    d->iguess[5]  = (d->p[5] + d->p[6])/(d->iguess[7] + 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for hb
*/
void p2x_mb_hb(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[7]   = d->p[10];
    d->iguess[6]   = d->p[8];
    d->iguess[2]   = d->iguess[6] + d->p[3];
    d->iguess[3]   = d->p[2] + d->p[9];
    d->iguess[4]   = d->p[9]/(d->p[2] + d->p[9]);
    d->iguess[5]   = d->iguess[3] + d->p[0] + d->p[1] + d->iguess[7];
    d->iguess[1]   = -0.5*d->iguess[3] + d->iguess[5] - 1.0*d->iguess[6] - 1.0*d->p[0] - 1.0*d->iguess[7] + d->iguess[2];
    d->iguess[0]  = (5.0*d->iguess[5] + 5.0*d->p[4] - 2.0*d->p[5] + d->p[6] + 5.0*d->iguess[2] - 5.0)/(2.0*d->iguess[5] + 2.0*d->iguess[6] + 2.0*d->iguess[7] + 2.0*d->iguess[1] + 2.0*d->iguess[2] - 7.0);
    d->iguess[8]  = -0.4*d->iguess[5]*d->iguess[0] + 2.0*d->iguess[5] - 0.4*d->iguess[6]*d->iguess[0] + 2.0*d->p[4] - 0.4*d->p[5] + 1.2*d->p[6] - 0.4*d->iguess[7]*d->iguess[0] - 0.4*d->iguess[0]*d->iguess[1] - 0.4*d->iguess[0]*d->iguess[2] + 2.4*d->iguess[0] + 2.0*d->iguess[2] - 2.0;
    d->iguess[9]  = (-2.0*d->iguess[5]*d->iguess[0] + 5.0*d->iguess[5] + 5.0*d->p[4] + 3.0*d->p[6] - 2.0*d->iguess[0]*d->iguess[2] + 5.0*d->iguess[0] + 5.0*d->iguess[2] - 5.0)/(2.0*d->iguess[6] + 2.0*d->iguess[7] + 2.0*d->iguess[1] - 2.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for aug
*/
void p2x_mb_aug(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[6]  = d->p[5];
    d->iguess[1]    = d->p[6] + d->iguess[6];
    d->iguess[2]    = d->p[4];
    d->iguess[4]    = d->iguess[2] + d->p[3];
    d->iguess[3]    = d->p[0] + d->iguess[1];
    d->iguess[0]   = (2.0*d->iguess[4] + 2.0*d->p[1] + d->p[7] + 2.0*d->iguess[3] - 2.0)/(2.0*d->iguess[4] + d->iguess[1] + d->iguess[3] - 2.0);
    d->iguess[5]   = (4.0*d->iguess[4]*d->p[1] + 4.0*d->iguess[4]*d->p[2] + 2.0*d->iguess[4]*d->p[7] + 4.0*d->iguess[4]*d->iguess[1] + 4.0*d->iguess[4]*d->iguess[3] - 8.0*d->iguess[4] + 4.0*d->iguess[4]*d->iguess[4] + 4.0*d->p[1]*d->iguess[1] - 4.0*d->p[1] + 2.0*d->p[2]*d->iguess[1] + 2.0*d->p[2]*d->iguess[3] - 4.0*d->p[2] + 2.0*d->p[7]*d->iguess[1] - 2.0*d->p[7] + 4.0*d->iguess[1]*d->iguess[3] - 4.0*d->iguess[1] - 4.0*d->iguess[3] + 4.0)/(d->iguess[4]*d->iguess[1] + 3.0*d->iguess[4]*d->iguess[3] - 4.0*d->iguess[4] + 2.0*d->iguess[4]*d->iguess[4] + d->iguess[1]*d->iguess[3] - 1.0*d->iguess[1] - 3.0*d->iguess[3] + d->iguess[3]*d->iguess[3] + 2.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for dio
*/
void p2x_mb_dio(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[4]  = 0.5*d->p[6];
    d->iguess[3]  = 0.5*d->p[4];
    d->iguess[1]    = d->iguess[3] + d->p[0] + d->p[3] + 2.0*d->iguess[4];
    d->iguess[5]   = (d->iguess[3]*d->p[2] + 0.5*d->iguess[3]*d->p[5] + 0.5*d->iguess[1]*d->p[5] - 0.5*d->p[5])/(d->iguess[3]*d->iguess[1] - 1.0*d->iguess[3] - 2.0*d->iguess[1] + d->iguess[1]*d->iguess[1] + 1.0);
    d->iguess[0]   = (-1.0*d->iguess[3]*d->iguess[5] - 1.0*d->iguess[1]*d->iguess[5] + 0.5*d->p[5] + d->iguess[5])/d->iguess[3];
    d->iguess[2]    = (-1.0*d->iguess[3] + d->iguess[1] - 1.0*d->p[0] - 1.0*d->iguess[4])/d->iguess[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for opx
*/
void p2x_mb_opx(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1]  = d->p[3];
    d->iguess[2]  = d->p[4];
    d->iguess[3]  = d->p[5];
    d->iguess[0]  = (d->iguess[3] + d->iguess[2] + d->p[0] - 1.0*d->p[1] + d->iguess[1] - 1.0)/(d->iguess[3] + d->iguess[2] + d->iguess[1] - 2.0);
    d->iguess[4]  = (-1.0*d->iguess[3]*d->iguess[0] + d->iguess[2]*d->iguess[0] - 1.0*d->p[2] + d->iguess[0]*d->iguess[1])/(d->iguess[3] - 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for g
*/
void p2x_mb_g(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[3];
    d->iguess[1]  = d->p[2];
    d->iguess[0]  = d->p[1]/(1.0 - 1.0*d->iguess[1]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ol
*/
void p2x_mb_ol(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for fsp
*/
void p2x_mb_fsp(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1]  = d->p[2];
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for abc
*/
void p2x_mb_abc(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for k4tr
*/
void p2x_mb_k4tr(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[0];
    d->iguess[1]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for sp
*/
void p2x_mb_sp(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]   = d->p[3];
    d->iguess[1]  = -1.0*d->p[2] - 1.0*d->iguess[2] + 1.0;
    d->iguess[0]  = (-1.0*d->p[1] + d->iguess[2] + 1.0)/(d->iguess[2] + 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ilm
*/
void p2x_mb_ilm(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1]   = d->p[0];
    d->iguess[0]  = d->p[1] + d->iguess[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ilmm
*/
void p2x_mb_ilmm(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]   = d->p[0];
    d->iguess[0]  = 1.0 - 1.0*d->p[2];
    d->iguess[1]   = d->p[3];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ep
*/
void p2x_mb_ep(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1]  = 0.5*d->p[1];
    d->iguess[0]  = d->p[2] + d->iguess[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for bi
*/
void p2x_mb_bi(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[5];
    d->iguess[3]  = d->p[4];
    d->iguess[1]  = d->p[3];
    d->iguess[0]  = (-3.0*d->p[1] - 1.0*d->p[2])/(d->iguess[2] + d->iguess[3] + d->iguess[1] - 3.0);
    d->iguess[4]  = 1.5*d->iguess[2]*d->iguess[0] - 1.5*d->iguess[2] + 1.5*d->p[0] + 1.5*d->iguess[3]*d->iguess[0] - 1.5*d->iguess[3] + 1.5*d->iguess[0]*d->iguess[1] - 1.5*d->iguess[0] - 1.5*d->iguess[1] + 1.5;
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for mu
*/
void p2x_mb_mu(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[5];
    d->iguess[4]  = d->p[4];
    d->iguess[3]  = d->p[3];
    d->iguess[1]  = d->iguess[4] + d->iguess[2] + d->iguess[3] + d->p[0];
    d->iguess[0]  = (d->p[1] + d->iguess[1] - 1.0)/(d->iguess[1] - 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for chl
*/
void p2x_mb_chl(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[6];
    d->iguess[3]  = 0.5*d->p[0] + 0.5*d->p[3];
    d->iguess[1]  = d->p[2] + d->iguess[3];
    d->iguess[5]  = (5.0*d->iguess[2]*d->p[0] + d->iguess[2]*d->p[1] - 3.0*d->iguess[2]*d->p[4] - 8.0*d->iguess[2]*d->iguess[3] + 2.0*d->iguess[2]*d->iguess[1] - 2.0*d->iguess[2] + d->iguess[2]*d->iguess[2] + 5.0*d->p[0]*d->iguess[3] + 5.0*d->p[0]*d->iguess[1] - 5.0*d->p[0] + d->p[1]*d->iguess[3] + d->p[1]*d->iguess[1] - 1.0*d->p[1] - 4.0*d->p[4]*d->iguess[3] - 2.0*d->p[4]*d->iguess[1] - 2.0*d->p[4] - 8.0*d->iguess[3]*d->iguess[1] + 8.0*d->iguess[3] - 9.0*d->iguess[3]*d->iguess[3] - 2.0*d->iguess[1] + d->iguess[1]*d->iguess[1] + 1.0)/(d->iguess[2]*d->iguess[3] + 3.0*d->iguess[2]*d->iguess[1] - 7.0*d->iguess[2] + d->iguess[2]*d->iguess[2] + 2.0*d->iguess[3]*d->iguess[1] - 6.0*d->iguess[3] - 8.0*d->iguess[1] + 2.0*d->iguess[1]*d->iguess[1] + 6.0);
    d->iguess[0]  = (d->iguess[2]*d->iguess[5] - 1.0*d->p[4] + d->iguess[5]*d->iguess[3] + d->iguess[5]*d->iguess[1] - 1.0*d->iguess[5])/(d->iguess[2] + d->iguess[3] + d->iguess[1] - 1.0);
    d->iguess[4]  = (d->iguess[2]*d->iguess[5] - 0.8*d->iguess[2]*d->iguess[0] - 0.8*d->p[5] + d->iguess[5]*d->iguess[3] + d->iguess[5]*d->iguess[1] - 1.0*d->iguess[5] - 1.6*d->iguess[0]*d->iguess[1] + 0.8*d->iguess[0])/(d->iguess[3] - 1.0*d->iguess[1] + 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Update dpdx matrix of L
*/
void dpdx_mb_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[7] + 1.0;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = 0.0;      dp_dx[0][3] = 0.0;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 0.0;      dp_dx[0][6] = 0.0;      dp_dx[0][7] = x[0];      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = x[2]*(x[7] + 1.0);      dp_dx[1][2] = x[1]*(x[7] + 1.0);      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      dp_dx[1][7] = x[1]*x[2];      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = (1.0 -x[2])*(x[7] + 1.0);      dp_dx[2][2] = -x[1]*(x[7] + 1.0);      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      dp_dx[2][7] = x[1]*(1.0 -x[2]);      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = x[7] + 1.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      dp_dx[3][7] = x[3] - 1.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = x[7] + 1.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = 0.0;      dp_dx[4][7] = x[4] - 1.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = x[6]*(x[7] + 1.0);      dp_dx[5][6] = x[5]*(x[7] + 1.0);      dp_dx[5][7] = x[5]*x[6];      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = (1.0 -x[6])*(x[7] + 1.0);      dp_dx[6][6] = -x[5]*(x[7] + 1.0);      dp_dx[6][7] = x[5]*(1.0 -x[6]);      
    dp_dx[7][0] = -x[7] - 1.0;      dp_dx[7][1] = -x[7] - 1.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = -x[7] - 1.0;      dp_dx[7][4] = -x[7] - 1.0;      dp_dx[7][5] = -x[7] - 1.0;      dp_dx[7][6] = 0.0;      dp_dx[7][7] = -x[0] -x[1] -x[3] -x[4] -x[5] + 1.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = 1.00;      
}


/**
    Update dpdx matrix of hb
*/
void dpdx_mb_hb(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = -1.00;      dp_dx[0][2] = 1.00;      dp_dx[0][3] = -0.500;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 1.00;      dp_dx[0][6] = -1.00;      dp_dx[0][7] = -1.00;      dp_dx[0][8] = 0.0;      dp_dx[0][9] = 0.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 1.00;      dp_dx[1][2] = -1.00;      dp_dx[1][3] = -0.500;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 1.00;      dp_dx[1][7] = 0.0;      dp_dx[1][8] = 0.0;      dp_dx[1][9] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 1.0 -x[4];      dp_dx[2][4] = -x[3];      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 0.0;      dp_dx[2][8] = 0.0;      dp_dx[2][9] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.00;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = -1.00;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      dp_dx[3][9] = 0.0;      
    dp_dx[4][0] = x[2] + x[5] - 1.0;      dp_dx[4][1] = x[9];      dp_dx[4][2] = x[0] - 1.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = x[0] - 1.0;      dp_dx[4][6] = x[9];      dp_dx[4][7] = x[9];      dp_dx[4][8] = -1.50;      dp_dx[4][9] = x[1] + x[6] + x[7] - 1.0;      
    dp_dx[5][0] = -x[1] + x[2] + x[5] -x[6] -x[7] + 1.0;      dp_dx[5][1] = -x[0] + 2.0*x[9];      dp_dx[5][2] = x[0];      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = x[0];      dp_dx[5][6] = -x[0] + 2.0*x[9];      dp_dx[5][7] = -x[0] + 2.0*x[9];      dp_dx[5][8] = -2.50;      dp_dx[5][9] = 2.0*x[1] + 2.0*x[6] + 2.0*x[7] - 2.0;      
    dp_dx[6][0] = -x[2] -x[5];      dp_dx[6][1] = -x[9];      dp_dx[6][2] = -x[0];      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = -x[0];      dp_dx[6][6] = -x[9];      dp_dx[6][7] = -x[9];      dp_dx[6][8] = 2.50;      dp_dx[6][9] = -x[1] -x[6] -x[7] + 1.0;      
    dp_dx[7][0] = x[1] -x[2] -x[5] + x[6] + x[7];      dp_dx[7][1] = x[0] - 2.0*x[9];      dp_dx[7][2] = -x[0];      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = -x[0];      dp_dx[7][6] = x[0] - 2.0*x[9];      dp_dx[7][7] = x[0] - 2.0*x[9];      dp_dx[7][8] = 1.50;      dp_dx[7][9] = -2.0*x[1] - 2.0*x[6] - 2.0*x[7] + 2.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 1.00;      dp_dx[8][7] = 0.0;      dp_dx[8][8] = 0.0;      dp_dx[8][9] = 0.0;      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = x[4];      dp_dx[9][4] = x[3];      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = 0.0;      dp_dx[9][9] = 0.0;      
    dp_dx[10][0] = 0.0;      dp_dx[10][1] = 0.0;      dp_dx[10][2] = 0.0;      dp_dx[10][3] = 0.0;      dp_dx[10][4] = 0.0;      dp_dx[10][5] = 0.0;      dp_dx[10][6] = 0.0;      dp_dx[10][7] = 1.00;      dp_dx[10][8] = 0.0;      dp_dx[10][9] = 0.0;      
}


/**
    Update dpdx matrix of aug
*/
void dpdx_mb_aug(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = -1.00;      dp_dx[0][2] = 0.0;      dp_dx[0][3] = 1.00;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 0.0;      dp_dx[0][6] = 0.0;      
    dp_dx[1][0] = x[3] + x[4] - 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = x[0] + 0.5*x[5] - 1.0;      dp_dx[1][4] = x[0] + 0.5*x[5] - 1.0;      dp_dx[1][5] = 0.5*x[3] + 0.5*x[4] - 0.5;      dp_dx[1][6] = 0.0;      
    dp_dx[2][0] = -x[1] -x[4] + 1.0;      dp_dx[2][1] = -x[0];      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.5*x[5];      dp_dx[2][4] = -x[0] + 0.5*x[5];      dp_dx[2][5] = 0.5*x[3] + 0.5*x[4] - 0.5;      dp_dx[2][6] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = -1.00;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 1.00;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 1.00;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 1.00;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 1.00;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      dp_dx[6][6] = -1.00;      
    dp_dx[7][0] = x[1] -x[3];      dp_dx[7][1] = x[0];      dp_dx[7][2] = 0.0;      dp_dx[7][3] = -x[0] -x[5];      dp_dx[7][4] = -x[5];      dp_dx[7][5] = -x[3] -x[4] + 1.0;      dp_dx[7][6] = 0.0;      
}


/**
    Update dpdx matrix of dio
*/
void dpdx_mb_dio(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.0 -x[2];      dp_dx[0][2] = -x[1];      dp_dx[0][3] = -1.00;      dp_dx[0][4] = -1.00;      dp_dx[0][5] = 0.0;      
    dp_dx[1][0] = x[1] -x[3] - 1.0;      dp_dx[1][1] = x[0] -x[5] - 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = -x[0] -x[5] - 1.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = -x[1] -x[3] + 1.0;      
    dp_dx[2][0] = -x[1] -x[3] + 1.0;      dp_dx[2][1] = -x[0] -x[5];      dp_dx[2][2] = 0.0;      dp_dx[2][3] = -x[0] -x[5];      dp_dx[2][4] = 0.0;      dp_dx[2][5] = -x[1] -x[3] + 1.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = x[2];      dp_dx[3][2] = x[1];      dp_dx[3][3] = 0.0;      dp_dx[3][4] = -1.00;      dp_dx[3][5] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 2.00;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      
    dp_dx[5][0] = 2.0*x[3];      dp_dx[5][1] = 2.0*x[5];      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 2.0*x[0] + 2.0*x[5];      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 2.0*x[1] + 2.0*x[3] - 2.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 2.00;      dp_dx[6][5] = 0.0;      
}


/**
    Update dpdx matrix of opx
*/
void dpdx_mb_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[3] - 1.0;      dp_dx[0][1] = -1.00;      dp_dx[0][2] = -1.00;      dp_dx[0][3] = x[0] + 0.5*x[4] - 1.0;      dp_dx[0][4] = 0.5*x[3] - 0.5;      
    dp_dx[1][0] = -x[1] -x[2] + 1.0;      dp_dx[1][1] = -x[0];      dp_dx[1][2] = -x[0];      dp_dx[1][3] = 0.5*x[4];      dp_dx[1][4] = 0.5*x[3] - 0.5;      
    dp_dx[2][0] = x[1] + x[2] -x[3];      dp_dx[2][1] = x[0];      dp_dx[2][2] = x[0];      dp_dx[2][3] = -x[0] -x[4];      dp_dx[2][4] = 1.0 -x[3];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.00;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 1.00;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 1.00;      dp_dx[5][4] = 0.0;      
}


/**
    Update dpdx matrix of g
*/
void dpdx_mb_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = -1.00;      
    dp_dx[1][0] = 1.0 -x[1];      dp_dx[1][1] = -x[0];      dp_dx[1][2] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.00;      dp_dx[2][2] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.00;      
}


/**
    Update dpdx matrix of ol
*/
void dpdx_mb_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      
    dp_dx[1][0] = 1.00;      
}


/**
    Update dpdx matrix of fsp
*/
void dpdx_mb_fsp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      dp_dx[0][1] = -1.00;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.00;      
}


/**
    Update dpdx matrix of abc
*/
void dpdx_mb_abc(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      
    dp_dx[1][0] = 1.00;      
}


/**
    Update dpdx matrix of k4tr
*/
void dpdx_mb_k4tr(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 1.00;      dp_dx[0][1] = 0.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 1.00;      
    dp_dx[2][0] = -1.00;      dp_dx[2][1] = -1.00;      
}


/**
    Update dpdx matrix of sp
*/
void dpdx_mb_sp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[2] + 1.0;      dp_dx[0][1] = 1.00;      dp_dx[0][2] = x[0] - 1.0;      
    dp_dx[1][0] = -x[2] - 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 1.0 -x[0];      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = -1.00;      dp_dx[2][2] = -1.00;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.00;      
}


/**
    Update dpdx matrix of ilm
*/
void dpdx_mb_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.00;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = -1.00;      
    dp_dx[2][0] = -1.00;      dp_dx[2][1] = 0.0;      
}


/**
    Update dpdx matrix of ilmm
*/
void dpdx_mb_ilmm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = 1.00;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = -1.00;      dp_dx[1][2] = -1.00;      
    dp_dx[2][0] = -1.00;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.00;      dp_dx[3][2] = 0.0;      
}


/**
    Update dpdx matrix of ep
*/
void dpdx_mb_ep(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      dp_dx[0][1] = -1.00;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 2.00;      
    dp_dx[2][0] = 1.00;      dp_dx[2][1] = -1.00;      
}


/**
    Update dpdx matrix of bi
*/
void dpdx_mb_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] + x[2] + x[3] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = x[0] - 1.0;      dp_dx[0][3] = x[0] - 1.0;      dp_dx[0][4] = -2.0/3.0;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = -1.0/3.0;      
    dp_dx[2][0] = -x[1] -x[2] -x[3];      dp_dx[2][1] = -x[0];      dp_dx[2][2] = -x[0];      dp_dx[2][3] = -x[0];      dp_dx[2][4] = 1.00;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.00;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.00;      dp_dx[4][4] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 1.00;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      
}


/**
    Update dpdx matrix of mu
*/
void dpdx_mb_mu(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.00;      dp_dx[0][2] = -1.00;      dp_dx[0][3] = -1.00;      dp_dx[0][4] = -1.00;      
    dp_dx[1][0] = x[1] - 1.0;      dp_dx[1][1] = x[0] - 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      
    dp_dx[2][0] = 1.0 -x[1];      dp_dx[2][1] = -x[0];      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 1.00;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 1.00;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 1.00;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      
}


/**
    Update dpdx matrix of chl
*/
void dpdx_mb_chl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -x[1] -x[2] -x[3];      dp_dx[0][1] = -x[0] + 0.25*x[4] + 1.25*x[5];      dp_dx[0][2] = -x[0] + 1.25*x[5];      dp_dx[0][3] = -x[0] - 0.25*x[4] + 1.25*x[5] + 2.0;      dp_dx[0][4] = 0.25*x[1] - 0.25*x[3] - 0.25;      dp_dx[0][5] = 1.25*x[1] + 1.25*x[2] + 1.25*x[3] - 1.25;      
    dp_dx[1][0] = 3.0*x[1] + 2.0*x[2] + x[3] - 2.0;      dp_dx[1][1] = 3.0*x[0] - 1.25*x[4] - 2.25*x[5] - 1.0;      dp_dx[1][2] = 2.0*x[0] - 2.25*x[5] - 1.0;      dp_dx[1][3] = x[0] + 1.25*x[4] - 2.25*x[5] - 1.0;      dp_dx[1][4] = -1.25*x[1] + 1.25*x[3] + 1.25;      dp_dx[1][5] = -2.25*x[1] - 2.25*x[2] - 2.25*x[3] + 2.25;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.00;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = -1.00;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 0.0;      
    dp_dx[3][0] = x[1] + x[2] + x[3];      dp_dx[3][1] = x[0] - 0.25*x[4] - 1.25*x[5];      dp_dx[3][2] = x[0] - 1.25*x[5];      dp_dx[3][3] = x[0] + 0.25*x[4] - 1.25*x[5];      dp_dx[3][4] = -0.25*x[1] + 0.25*x[3] + 0.25;      dp_dx[3][5] = -1.25*x[1] - 1.25*x[2] - 1.25*x[3] + 1.25;      
    dp_dx[4][0] = -x[1] -x[2] -x[3] + 1.0;      dp_dx[4][1] = -x[0] + x[5];      dp_dx[4][2] = -x[0] + x[5];      dp_dx[4][3] = -x[0] + x[5];      dp_dx[4][4] = 0.0;      dp_dx[4][5] = x[1] + x[2] + x[3] - 1.0;      
    dp_dx[5][0] = -2.0*x[1] -x[2] + 1.0;      dp_dx[5][1] = -2.0*x[0] + 1.25*x[4] + 1.25*x[5];      dp_dx[5][2] = -x[0] + 1.25*x[5];      dp_dx[5][3] = -1.25*x[4] + 1.25*x[5];      dp_dx[5][4] = 1.25*x[1] - 1.25*x[3] - 1.25;      dp_dx[5][5] = 1.25*x[1] + 1.25*x[2] + 1.25*x[3] - 1.25;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 1.00;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      
}

    
/**
    Endmember fraction of L
*/
void px_mb_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*(x[7] + 1.0);
        p[1]           = x[1]*x[2]*(x[7] + 1.0);
        p[2]           = x[1]*(1.0 -x[2])*(x[7] + 1.0);
        p[3]           = x[3]*(x[7] + 1.0) -x[7];
        p[4]           = x[4]*(x[7] + 1.0) -x[7];
        p[5]           = x[5]*x[6]*(x[7] + 1.0);
        p[6]           = x[5]*(1.0 -x[6])*(x[7] + 1.0);
        p[7]           = x[7] + (x[7] + 1.0)*(-1.0*x[0] -x[1] -x[3] -x[4] -x[5]) + 1.0;
        p[8]           = x[7];
}

    
/**
    Endmember fraction of hb
*/
void px_mb_hb(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[1] + x[2] - 0.5*x[3] + x[5] -x[6] -x[7];
        p[1]           = x[1] -x[2] - 0.5*x[3] + x[6];
        p[2]           = -x[3]*x[4] + x[3];
        p[3]           = x[2] -x[6];
        p[4]           = x[0]*x[2] + x[0]*x[5] -x[0] + x[1]*x[9] -x[2] -x[5] + x[6]*x[9] + x[7]*x[9] - 1.5*x[8] -x[9] + 1.0;
        p[5]           = -x[0]*x[1] + x[0]*x[2] + x[0]*x[5] -x[0]*x[6] -x[0]*x[7] + x[0] + 2.0*x[1]*x[9] + 2.0*x[6]*x[9] + 2.0*x[7]*x[9] - 2.5*x[8] - 2.0*x[9];
        p[6]           = -x[0]*x[2] -x[0]*x[5] -x[1]*x[9] -x[6]*x[9] -x[7]*x[9] + 2.5*x[8] + x[9];
        p[7]           = x[0]*x[1] -x[0]*x[2] -x[0]*x[5] + x[0]*x[6] + x[0]*x[7] - 2.0*x[1]*x[9] - 2.0*x[6]*x[9] - 2.0*x[7]*x[9] + 1.5*x[8] + 2.0*x[9];
        p[8]           = x[6];
        p[9]           = x[3]*x[4];
        p[10]           = x[7];
}

    
/**
    Endmember fraction of aug
*/
void px_mb_aug(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[1] + x[3];
        p[1]           = x[0]*x[3] + x[0]*x[4] -x[0] + 0.5*x[3]*x[5] -x[3] + 0.5*x[4]*x[5] -x[4] - 0.5*x[5] + 1.0;
        p[2]           = -x[0]*x[1] -x[0]*x[4] + x[0] + 0.5*x[3]*x[5] + 0.5*x[4]*x[5] - 0.5*x[5];
        p[3]           = -x[2] + x[4];
        p[4]           = x[2];
        p[5]           = x[6];
        p[6]           = x[1] -x[6];
        p[7]           = x[0]*x[1] -x[0]*x[3] -x[3]*x[5] -x[4]*x[5] + x[5];
}

    
/**
    Endmember fraction of dio
*/
void px_mb_dio(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[1]*x[2] + x[1] -x[3] -x[4];
        p[1]           = x[0]*x[1] -x[0]*x[3] -x[0] -x[1]*x[5] -x[1] -x[3]*x[5] -x[3] + x[5] + 1.0;
        p[2]           = -x[0]*x[1] -x[0]*x[3] + x[0] -x[1]*x[5] -x[3]*x[5] + x[5];
        p[3]           = x[1]*x[2] -x[4];
        p[4]           = 2.0*x[3];
        p[5]           = 2.0*x[0]*x[3] + 2.0*x[1]*x[5] + 2.0*x[3]*x[5] - 2.0*x[5];
        p[6]           = 2.0*x[4];
}

    
/**
    Endmember fraction of opx
*/
void px_mb_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[3] -x[0] -x[1] -x[2] + 0.5*x[3]*x[4] -x[3] - 0.5*x[4] + 1.0;
        p[1]           = -x[0]*x[1] -x[0]*x[2] + x[0] + 0.5*x[3]*x[4] - 0.5*x[4];
        p[2]           = x[0]*x[1] + x[0]*x[2] -x[0]*x[3] -x[3]*x[4] + x[4];
        p[3]           = x[1];
        p[4]           = x[2];
        p[5]           = x[3];
}

    
/**
    Endmember fraction of g
*/
void px_mb_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] -x[0] -x[1] -x[2] + 1.0;
        p[1]           = -x[0]*x[1] + x[0];
        p[2]           = x[1];
        p[3]           = x[2];
}

    
/**
    Endmember fraction of ol
*/
void px_mb_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 -x[0];
        p[1]           = x[0];
}

    
/**
    Endmember fraction of fsp
*/
void px_mb_fsp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[0] -x[1] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}

    
/**
    Endmember fraction of abc
*/
void px_mb_abc(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 -x[0];
        p[1]           = x[0];
}

    
/**
    Endmember fraction of k4tr
*/
void px_mb_k4tr(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0];
        p[1]           = x[1];
        p[2]           = -x[0] -x[1] + 1.0;
}

    
/**
    Endmember fraction of sp
*/
void px_mb_sp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1] + (x[0] - 1.0)*(x[2] + 1.0);
        p[1]           = (1.0 -x[0])*(x[2] + 1.0);
        p[2]           = -x[1] -x[2] + 1.0;
        p[3]           = x[2];
}

    
/**
    Endmember fraction of ilm
*/
void px_mb_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1];
        p[1]           = x[0] -x[1];
        p[2]           = 1.0 -x[0];
}

    
/**
    Endmember fraction of ilmm
*/
void px_mb_ilmm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[2];
        p[1]           = x[0] -x[1] -x[2];
        p[2]           = 1.0 -x[0];
        p[3]           = x[1];
}

    
/**
    Endmember fraction of ep
*/
void px_mb_ep(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[0] -x[1] + 1.0;
        p[1]           = 2.0*x[1];
        p[2]           = x[0] -x[1];
}

    
/**
    Endmember fraction of bi
*/
void px_mb_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] -x[0] -x[1] -x[2] -x[3] - 2.0/3.0*x[4] + 1.0;
        p[1]           = x[0] - 1.0/3.0*x[4];
        p[2]           = -x[0]*x[1] -x[0]*x[2] -x[0]*x[3] + x[4];
        p[3]           = x[1];
        p[4]           = x[3];
        p[5]           = x[2];
}

    
/**
    Endmember fraction of mu
*/
void px_mb_mu(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1] -x[2] -x[3] -x[4];
        p[1]           = x[0]*x[1] -x[0] -x[1] + 1.0;
        p[2]           = -x[0]*x[1] + x[0];
        p[3]           = x[3];
        p[4]           = x[4];
        p[5]           = x[2];
}

    
/**
    Endmember fraction of chl
*/
void px_mb_chl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[0]*x[1] -x[0]*x[2] -x[0]*x[3] + 0.25*x[1]*x[4] + 1.25*x[1]*x[5] + 1.25*x[2]*x[5] - 0.25*x[3]*x[4] + 1.25*x[3]*x[5] + 2.0*x[3] - 0.25*x[4] - 1.25*x[5];
        p[1]           = 3.0*x[0]*x[1] + 2.0*x[0]*x[2] + x[0]*x[3] - 2.0*x[0] - 1.25*x[1]*x[4] - 2.25*x[1]*x[5] -x[1] - 2.25*x[2]*x[5] -x[2] + 1.25*x[3]*x[4] - 2.25*x[3]*x[5] -x[3] + 1.25*x[4] + 2.25*x[5] + 1.0;
        p[2]           = x[1] -x[3];
        p[3]           = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - 0.25*x[1]*x[4] - 1.25*x[1]*x[5] - 1.25*x[2]*x[5] + 0.25*x[3]*x[4] - 1.25*x[3]*x[5] + 0.25*x[4] + 1.25*x[5];
        p[4]           = -x[0]*x[1] -x[0]*x[2] -x[0]*x[3] + x[0] + x[1]*x[5] + x[2]*x[5] + x[3]*x[5] -x[5];
        p[5]           = -2.0*x[0]*x[1] -x[0]*x[2] + x[0] + 1.25*x[1]*x[4] + 1.25*x[1]*x[5] + 1.25*x[2]*x[5] - 1.25*x[3]*x[4] + 1.25*x[3]*x[5] - 1.25*x[4] - 1.25*x[5];
        p[6]           = x[2];
}



/**
    Objective function of L
*/
double obj_mb_liq(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mb_liq(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = -x[7] +(x[7] + 1.0)*(x[0] + x[1] + x[3] + x[4] + x[5]);
    sf[1]          = x[0]*(x[7] + 1.0);
    sf[2]          = x[1]*x[2]*(x[7] + 1.0);
    sf[3]          = x[1]*(1.0 -x[2])*(x[7] + 1.0);
    sf[4]          = x[3]*(x[7] + 1.0) - x[7];
    sf[5]          = x[4]*(x[7] + 1.0) - x[7];
    sf[6]          = x[7] +(x[7] + 1.0)*(-1.0*x[0] -x[1] -x[3] -x[4] -x[5]) + 1.0;
    sf[7]          = x[7];
    sf[8]          = x[5]*(x[7] + 1.0);
    sf[9]          = x[6];
    sf[10]         = 1.0 - x[6];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[1])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*sf[2])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[3])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*sf[4])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[0]*sf[5])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[0]*sf[8]*cpow(sf[9], 5.0))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(sf[0]*cpow(sf[10], 5.0)*sf[8])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(cpow(sf[6], 2.0))) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(sf[0]*sf[7])) + mu_Gex[8];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_liq(SS_ref_db,x);

        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of hb
*/
double obj_mb_hb(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_hb(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    for (int i = 0; i < d->n_em; i++){
        mu_Gex[i] = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < d->n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
    }
    
    sf[0]          = 1.0 - x[3];
    sf[1]          = -x[3]*x[4] +x[3];
    sf[2]          =x[3]*x[4];
    sf[3]          = -x[0] +x[8] + 1.0;
    sf[4]          =x[0] - x[8];
    sf[5]          =x[0]*x[1] +x[0]*x[6] +x[0]*x[7] - x[0] - x[1]*x[9] - x[1] - x[6]*x[9] - x[6] - x[7]*x[9] - x[7] +x[9] + 1.0;
    sf[6]          = -x[0]*x[1] - x[0]*x[6] - x[0]*x[7] +x[0] +x[1]*x[9] +x[6]*x[9] +x[7]*x[9] - x[9];
    sf[7]          =x[1];
    sf[8]          =x[6];
    sf[9]          =x[7];
    sf[10]          =x[5];
    sf[11]          =x[0]*x[2] +x[0]*x[5] - x[0] +x[1]*x[9] - x[2] - x[5] +x[6]*x[9] +x[7]*x[9] - 1.5*x[8] - x[9] + 1.0;
    sf[12]          = -x[0]*x[2] - x[0]*x[5] +x[0] - x[1]*x[9] - x[6]*x[9] - x[7]*x[9] + 1.5*x[8] +x[9];
    sf[13]          =x[2];
    sf[14]          = -0.5*x[1] + 0.5*x[2] - 0.25*x[3] - 0.5*x[6] - 0.5*x[7] + 1.0;
    sf[15]          = 0.5*x[1] - 0.5*x[2] + 0.25*x[3] + 0.5*x[6] + 0.5*x[7];
    sf[16]          = 1.0 - x[7];
    sf[17]          =x[7];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*cpow(sf[10], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[0]*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[7], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(8.0*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*sf[1]*cpow(sf[3], 3.0)*sf[5]*sf[7])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*cpow(sf[13], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[7], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[0]*cpow(sf[11], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[4], 3.0)*cpow(sf[6], 2.0))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[6], 2.0))) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[4], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(sf[0]*cpow(sf[13], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[8], 2.0) + d_em[8])) + mu_Gex[8];
    mu[9]          = gb[9] + R*T*creal(clog(8.0*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*sf[2]*cpow(sf[3], 3.0)*sf[5]*sf[7])) + mu_Gex[9];
    mu[10]          = gb[10] + R*T*creal(clog(2.0*sf[0]*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[17], 2.0)*cpow(sf[3], 3.0)*cpow(sf[9], 2.0)  + d_em[10] )) + mu_Gex[10];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_hb(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of aug
*/
double obj_mb_aug(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_aug(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    for (int i = 0; i < d->n_em; i++){
        mu_Gex[i] = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < d->n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
    }
    
    sf[0]          =x[0]*x[1] +x[0]*x[4] - x[0] - x[1] - 0.5*x[3]*x[5] - 0.5*x[4]*x[5] - x[4] + 0.5*x[5] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[4] +x[0] + 0.5*x[3]*x[5] + 0.5*x[4]*x[5] - 0.5*x[5];
    sf[2]          =x[1] - x[2] +x[4];
    sf[3]          =x[2];
    sf[4]          =x[0]*x[3] +x[0]*x[4] - x[0] + 0.5*x[3]*x[5] - x[3] + 0.5*x[4]*x[5] - x[4] - 0.5*x[5] + 1.0;
    sf[5]          = -x[0]*x[3] - x[0]*x[4] +x[0] - 0.5*x[3]*x[5] - 0.5*x[4]*x[5] + 0.5*x[5];
    sf[6]          =x[3];
    sf[7]          =x[4];
    sf[8]          = -0.5*x[1] + 0.5*x[6] + 1.0;
    sf[9]          = 0.5*x[1] - 0.5*x[6];
    sf[10]          = -0.5*x[1] - 0.5*x[6] + 1.0;
    sf[11]          = 0.5*x[1] + 0.5*x[6];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*cpow(sf[10], 0.25)*sf[6]*cpow(sf[8], 0.25))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*cpow(sf[10], 0.25)*sf[4]*cpow(sf[8], 0.25))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[10], 0.25)*sf[1]*sf[5]*cpow(sf[8], 0.25))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[10], 0.25)*sf[2]*sf[7]*cpow(sf[8], 0.25))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(cpow(sf[10], 0.25)*sf[3]*sf[7]*cpow(sf[8], 0.25) + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(cpow(sf[11], 0.25)*sf[2]*sf[6]*cpow(sf[8], 0.25))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(1.4142*cpow(sf[10], 0.125)*cpow(sf[11], 0.125)*sf[2]*sf[6]*cpow(sf[8], 0.125)*cpow(sf[9], 0.125))) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(sf[0]*cpow(sf[10], 0.25)*sf[5]*cpow(sf[8], 0.25))) + mu_Gex[7];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_aug(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of dio
*/
double obj_mb_dio(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_dio(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          =x[0]*x[1] - x[0]*x[3] - x[0] - x[1]*x[5] - x[1] - x[3]*x[5] +x[3] +x[5] + 1.0;
    sf[1]          = -x[0]*x[1] +x[0]*x[3] +x[0] +x[1]*x[5] +x[3]*x[5] - x[5];
    sf[2]          =x[1]*x[2] - x[4];
    sf[3]          = -x[1]*x[2] +x[1] - x[3] +x[4];
    sf[4]          =x[0]*x[1] +x[0]*x[3] - x[0] +x[1]*x[5] - x[1] +x[3]*x[5] - x[3] - x[5] + 1.0;
    sf[5]          = -x[0]*x[1] - x[0]*x[3] +x[0] - x[1]*x[5] - x[3]*x[5] +x[5];
    sf[6]          =x[1]*x[2] +x[4];
    sf[7]          = -x[1]*x[2] +x[1] +x[3] - x[4];
    sf[8]          =x[1] - x[3];
    sf[9]          = -x[1] +x[3] + 1.0;
    sf[10]          =x[1] +x[3];
    sf[11]          = -x[1] - x[3] + 1.0;
    
    
    mu[0]          = gb[0] + R*T*creal(clog(csqrt(sf[10])*csqrt(sf[3])*csqrt(sf[7])*csqrt(sf[8]))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(csqrt(sf[0])*csqrt(sf[11])*csqrt(sf[4])*csqrt(sf[9]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(csqrt(sf[11])*csqrt(sf[1])*csqrt(sf[5])*csqrt(sf[9]))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(csqrt(sf[10])*csqrt(sf[2])*csqrt(sf[6])*csqrt(sf[8]) +d_em[3])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(csqrt(sf[0])*csqrt(sf[10])*csqrt(sf[7])*csqrt(sf[9]))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(csqrt(sf[11])*csqrt(sf[1])*csqrt(sf[4])*csqrt(sf[9]))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(csqrt(sf[10])*csqrt(sf[3])*csqrt(sf[6])*csqrt(sf[8]) +d_em[6])) + mu_Gex[6];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_dio(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of opx
*/
double obj_mb_opx(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_opx(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    for (int i = 0; i < d->n_em; i++){
        mu_Gex[i] = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < d->n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
    }
    
    sf[0]          =x[0]*x[1] +x[0]*x[2] - x[0] - x[1] - x[2] - 0.5*x[3]*x[4] + 0.5*x[4] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[2] +x[0] + 0.5*x[3]*x[4] - 0.5*x[4];
    sf[2]          =x[2];
    sf[3]          =x[1];
    sf[4]          =x[0]*x[3] - x[0] + 0.5*x[3]*x[4] - x[3] - 0.5*x[4] + 1.0;
    sf[5]          = -x[0]*x[3] +x[0] - 0.5*x[3]*x[4] + 0.5*x[4];
    sf[6]          =x[3];
    sf[7]          = 0.5*x[1] + 0.5*x[2];
    sf[8]          = -0.5*x[1] - 0.5*x[2] + 1.0;
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[4]*csqrt(sf[8]))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[5]*csqrt(sf[8]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[5]*csqrt(sf[8]))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(1.4142*sf[3]*sf[4]*cpow(sf[7], 0.25)*cpow(sf[8], 0.25))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(1.4142*sf[2]*sf[4]*cpow(sf[7], 0.25)*cpow(sf[8], 0.25) + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[0]*sf[6]*csqrt(sf[8]))) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_opx(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of g
*/
double obj_mb_g(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_g(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    for (int i = 0; i < d->n_em; i++){
        mu_Gex[i] = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < d->n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
    }
    
    sf[0]          =x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[1]          = -x[0]*x[1] +x[0];
    sf[2]          =x[1];
    sf[3]          = 1.0 - x[2];
    sf[4]          =x[2];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[1], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[2], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[0], 3.0)*cpow(sf[4], 2.0) + d_em[3])) + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_g(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of ol
*/
double obj_mb_ol(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mb_ol(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = 1.0 - x[0];
    sf[1]          =x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[1], 2.0))) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_ol(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of fsp
*/
double obj_mb_fsp(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mb_fsp(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    for (int i = 0; i < d->n_em; i++){
        mu_Gex[i] = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < d->n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
    }
    
    sf[0]          = -x[0] - x[1] + 1.0;
    sf[1]          =x[0];
    sf[2]          =x[1];
    sf[3]          = 0.25*x[0] + 0.25;
    sf[4]          = 0.75 - 0.25*x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(1.7548*sf[0]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[1]*csqrt(sf[3])*csqrt(sf[4]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(1.7548*sf[2]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_fsp(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of abc
*/
double obj_mb_abc(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mb_abc(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    for (int i = 0; i < d->n_em; i++){
        mu_Gex[i] = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < d->n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
    }
    
    sf[0]          = 1.0 - x[0];
    sf[1]          =x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1])) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_abc(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of k4tr
*/
double obj_mb_k4tr(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mb_k4tr(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    for (int i = 0; i < d->n_em; i++){
        mu_Gex[i] = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < d->n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
    }
    
    sf[0]          =x[0];
    sf[1]          =x[1];
    sf[2]          = -x[0] - x[1] + 1.0;
    sf[3]          = 0.25*x[1] + 0.25;
    sf[4]          = 0.75 - 0.25*x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(1.7548*sf[0]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[1]*csqrt(sf[3])*csqrt(sf[4]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(1.7548*sf[2]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_k4tr(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of sp
*/
double obj_mb_sp(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_sp(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          =x[1];
    sf[1]          = -x[1] - x[2] + 1.0;
    sf[2]          =x[2];
    sf[3]          = 1.0 - x[0];
    sf[4]          =x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[4])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*sf[3])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[1]*sf[4] + d_em[2])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[2]*sf[4] + d_em[3])) + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_sp(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of ilm
*/
double obj_mb_ilm(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_ilm(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = 0.5*x[0] + 0.5*x[1];
    sf[1]          = 0.5*x[0] - 0.5*x[1];
    sf[2]          = 1.0 - x[0];
    sf[3]          = 0.5*x[0] - 0.5*x[1];
    sf[4]          = 0.5*x[0] + 0.5*x[1];
    sf[5]          = 1.0 - x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[4] + d_em[0])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(4.0*csqrt(sf[0])*csqrt(sf[1])*csqrt(sf[3])*csqrt(sf[4]) + d_em[1])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[2]*sf[5] + d_em[2] )) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_ilm(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of ilmm
*/
double obj_mb_ilmm(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mb_ilmm(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = 0.5*x[0] - 0.5*x[1] + 0.5*x[2];
    sf[1]          = 0.5*x[0] - 0.5*x[1] - 0.5*x[2];
    sf[2]          =x[1];
    sf[3]          = 1.0 - x[0];
    sf[4]          = 0.5*x[0] - 0.5*x[1] - 0.5*x[2];
    sf[5]          = 0.5*x[0] + 0.5*x[1] + 0.5*x[2];
    sf[6]          = 1.0 - x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[5])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(4.0*csqrt(sf[0])*csqrt(sf[1])*csqrt(sf[4])*csqrt(sf[5]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[3]*sf[6])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[2]*sf[5])) + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_ilmm(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of ep
*/
double obj_mb_ep(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_ep(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          =x[0] - x[1];
    sf[1]          = -x[0] +x[1] + 1.0;
    sf[2]          =x[0] +x[1];
    sf[3]          = -x[0] - x[1] + 1.0;
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[1]*sf[3])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[2] + d_em[1])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[2] + d_em[2])) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_ep(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of bi
*/
double obj_mb_bi(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_bi(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          =x[0]*x[1] +x[0]*x[2] +x[0]*x[3] - x[0] - x[1] - x[2] - x[3] - 2.0/3.0*x[4] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[2] - x[0]*x[3] +x[0] + 2.0/3.0*x[4];
    sf[2]          =x[2];
    sf[3]          =x[3];
    sf[4]          =x[1];
    sf[5]          = -x[0] + 1.0/3.0*x[4] + 1.0;
    sf[6]          =x[0] - 1.0/3.0*x[4];
    sf[7]          = -0.5*x[1] - 0.5*x[2] + 0.5;
    sf[8]          = 0.5*x[1] + 0.5*x[2] + 0.5;
    sf[9]          = 1.0 - x[3];
    sf[10]          =x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(4.0*sf[0]*cpow(sf[5], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(4.0*sf[1]*cpow(sf[6], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(4.0*sf[1]*cpow(sf[5], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[4]*cpow(sf[5], 2.0)*cpow(sf[8], 2.0)*cpow(sf[9], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(4.0*cpow(sf[10], 2.0)*sf[3]*cpow(sf[5], 2.0)*sf[7]*sf[8] + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[2]*cpow(sf[5], 2.0)*cpow(sf[8], 2.0)*cpow(sf[9], 2.0) + d_em[5])) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_bi(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of mu
*/
double obj_mb_mu(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_mu(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    for (int i = 0; i < d->n_em; i++){
        mu_Gex[i] = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < d->n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
    }
    
    sf[0]          = -x[3] - x[4] + 1.0;
    sf[1]          =x[3];
    sf[2]          =x[4];
    sf[3]          =x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[4]          = -x[0]*x[1] +x[0];
    sf[5]          =x[1];
    sf[6]          = 1.0 - x[2];
    sf[7]          =x[2];
    sf[8]          = -0.5*x[1] - 0.5*x[4] + 1.0;
    sf[9]          = 0.5*x[1] + 0.5*x[4];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(4.0*sf[0]*sf[5]*sf[6]*sf[8]*sf[9])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*sf[3]*sf[6]*cpow(sf[8], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[4]*sf[6]*cpow(sf[8], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(4.0*sf[1]*sf[5]*sf[6]*sf[8]*sf[9])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[2]*sf[5]*sf[6]*cpow(sf[9], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(4.0*sf[0]*sf[5]*sf[7]*sf[8]*sf[9]+ d_em[5])) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_mu(SS_ref_db,x);
         for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}
    
/**
    Objective function of chl
*/
double obj_mb_chl(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mb_chl(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          =x[0]*x[1] - x[0]*x[3] - x[0] - x[1]*x[4] - x[1] +x[3]*x[4] +x[3] +x[4] + 1.0;
    sf[1]          = -x[0]*x[1] +x[0]*x[3] +x[0] +x[1]*x[4] - x[3]*x[4] - x[4];
    sf[2]          =x[1] - x[3];
    sf[3]          = -x[0] + 0.25*x[1]*x[4] + 0.25*x[1]*x[5] + 0.25*x[2]*x[5] - 0.25*x[3]*x[4] + 0.25*x[3]*x[5] - 0.25*x[4] - 0.25*x[5] + 1.0;
    sf[4]          =x[0] - 0.25*x[1]*x[4] - 0.25*x[1]*x[5] - 0.25*x[2]*x[5] + 0.25*x[3]*x[4] - 0.25*x[3]*x[5] + 0.25*x[4] + 0.25*x[5];
    sf[5]          =x[0]*x[1] +x[0]*x[2] +x[0]*x[3] - x[0] - x[1]*x[5] - x[1] - x[2]*x[5] - x[2] - x[3]*x[5] - x[3] +x[5] + 1.0;
    sf[6]          = -x[0]*x[1] - x[0]*x[2] - x[0]*x[3] +x[0] +x[1]*x[5] +x[2]*x[5] +x[3]*x[5] - x[5];
    sf[7]          =x[2];
    sf[8]          =x[1] +x[3];
    sf[9]          = -x[1] - 0.5*x[2] + 1.0;
    sf[10]          =x[1] + 0.5*x[2];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(4.0*sf[0]*sf[10]*cpow(sf[3], 4.0)*sf[8]*sf[9])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*cpow(sf[3], 4.0)*sf[5]*cpow(sf[9], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[10], 2.0)*sf[2]*cpow(sf[3], 4.0)*sf[8])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(4.0*sf[10]*sf[1]*cpow(sf[4], 4.0)*sf[8]*sf[9])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[0]*cpow(sf[4], 4.0)*sf[6]*cpow(sf[9], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[1]*cpow(sf[3], 4.0)*sf[5]*cpow(sf[9], 2.0))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(4.0*sf[0]*sf[10]*cpow(sf[3], 4.0)*sf[7]*sf[9] + d_em[6])) + mu_Gex[6];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mb_chl(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }

    }

    return d->df;
}



/**************************************************************************************/
/**************************************************************************************/
/**********************ULTRAMAFIC DATABASE (Evans & Frost., 2021)**********************/
/**************************************************************************************/
/**************************************************************************************/

/**
    Update dpdx matrix of fluid
*/
void dpdx_um_fluid(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 1.0;      
    dp_dx[1][0] = -1.0;      
}


/**
    Update dpdx matrix of ol
*/
void dpdx_um_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      
    dp_dx[1][0] = 1.0;      
}


/**
    Update dpdx matrix of br
*/
void dpdx_um_br(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      
    dp_dx[1][0] = 1.0;      
}


/**
    Update dpdx matrix of ch
*/
void dpdx_um_ch(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      
    dp_dx[1][0] = 1.0;      
}


/**
    Update dpdx matrix of atg
*/
void dpdx_um_atg(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] + x[2] - 1.0;      dp_dx[0][1] = x[0] -x[3] - 1.0;      dp_dx[0][2] = x[0] -x[3] - 1.0;      dp_dx[0][3] = -x[1] -x[2] + 1.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = -0.5*x[3];      dp_dx[1][2] = -0.5*x[3];      dp_dx[1][3] = -0.5*x[1] - 0.5*x[2] + 0.5;      
    dp_dx[2][0] = -x[1] -x[2];      dp_dx[2][1] = -x[0] + 1.5*x[3];      dp_dx[2][2] = -x[0] + 1.5*x[3];      dp_dx[2][3] = 1.5*x[1] + 1.5*x[2] - 1.5;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 1.0;      dp_dx[4][3] = 0.0;      
}


/**
    Update dpdx matrix of g
*/
void dpdx_um_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      
    dp_dx[1][0] = 1.0;      
}


/**
    Update dpdx matrix of ta
*/
void dpdx_um_ta(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] + x[2] - 1.0;      dp_dx[0][1] = x[0] - 2.0;      dp_dx[0][2] = x[0] - 2.0;      dp_dx[0][3] = 0.5*x[4] + 1.0;      dp_dx[0][4] = 0.5*x[3] - 0.5;      
    dp_dx[1][0] = 1.0 -x[3];      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = -x[0] + x[4];      dp_dx[1][4] = x[3] - 1.0;      
    dp_dx[2][0] = -x[1] -x[2] + x[3];      dp_dx[2][1] = -x[0];      dp_dx[2][2] = -x[0];      dp_dx[2][3] = x[0] - 1.5*x[4];      dp_dx[2][4] = 1.5 - 1.5*x[3];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 2.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = -2.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 2.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 1.0;      dp_dx[5][4] = 0.0;      
}


/**
    Update dpdx matrix of chl
*/
void dpdx_um_chl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -x[1] -x[2] -x[3];      dp_dx[0][1] = -x[0] + 0.25*x[4] + 1.25*x[5];      dp_dx[0][2] = -x[0] + 1.25*x[5];      dp_dx[0][3] = -x[0] - 0.25*x[4] + 1.25*x[5] + 2.0;      dp_dx[0][4] = 0.25*x[1] - 0.25*x[3] - 0.25;      dp_dx[0][5] = 1.25*x[1] + 1.25*x[2] + 1.25*x[3] - 1.25;      
    dp_dx[1][0] = 3.0*x[1] + 2.0*x[2] + x[3] - 2.0;      dp_dx[1][1] = 3.0*x[0] - 1.25*x[4] - 2.25*x[5] - 1.0;      dp_dx[1][2] = 2.0*x[0] - 2.25*x[5] - 1.0;      dp_dx[1][3] = x[0] + 1.25*x[4] - 2.25*x[5] - 1.0;      dp_dx[1][4] = -1.25*x[1] + 1.25*x[3] + 1.25;      dp_dx[1][5] = -2.25*x[1] - 2.25*x[2] - 2.25*x[3] + 2.25;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = -1.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 0.0;      
    dp_dx[3][0] = x[1] + x[2] + x[3];      dp_dx[3][1] = x[0] - 0.25*x[4] - 1.25*x[5];      dp_dx[3][2] = x[0] - 1.25*x[5];      dp_dx[3][3] = x[0] + 0.25*x[4] - 1.25*x[5];      dp_dx[3][4] = -0.25*x[1] + 0.25*x[3] + 0.25;      dp_dx[3][5] = -1.25*x[1] - 1.25*x[2] - 1.25*x[3] + 1.25;      
    dp_dx[4][0] = -x[1] -x[2] -x[3] + 1.0;      dp_dx[4][1] = -x[0] + x[5];      dp_dx[4][2] = -x[0] + x[5];      dp_dx[4][3] = -x[0] + x[5];      dp_dx[4][4] = 0.0;      dp_dx[4][5] = x[1] + x[2] + x[3] - 1.0;      
    dp_dx[5][0] = -2.0*x[1] -x[2] + 1.0;      dp_dx[5][1] = -2.0*x[0] + 1.25*x[4] + 1.25*x[5];      dp_dx[5][2] = -x[0] + 1.25*x[5];      dp_dx[5][3] = -1.25*x[4] + 1.25*x[5];      dp_dx[5][4] = 1.25*x[1] - 1.25*x[3] - 1.25;      dp_dx[5][5] = 1.25*x[1] + 1.25*x[2] + 1.25*x[3] - 1.25;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 1.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      
}



/**
    Update dpdx matrix of anth
*/
void dpdx_um_anth(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      dp_dx[0][1] = x[3] - 1.0;      dp_dx[0][2] = -1.50;      dp_dx[0][3] = x[1] - 1.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 1.00;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      
    dp_dx[2][0] = 1.0 - x[1];      dp_dx[2][1] =-x[0] + 2.0*x[3];      dp_dx[2][2] = -2.50;      dp_dx[2][3] = 2.0*x[1] - 2.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] =-x[3];      dp_dx[3][2] = 2.50;      dp_dx[3][3] = 1.0 - x[1];      
    dp_dx[4][0] = x[1];      dp_dx[4][1] = x[0] - 2.0*x[3];      dp_dx[4][2] = 1.50;      dp_dx[4][3] = 2.0 - 2.0*x[1];      
}


/**
    Update dpdx matrix of spi
*/
void dpdx_um_spi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 1.0;      dp_dx[0][1] = 1.0;      
    dp_dx[1][0] = -1.0;      dp_dx[1][1] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = -1.0;      
}


/**
    Update dpdx matrix of opx
*/
void dpdx_um_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -0.50;      
    dp_dx[1][0] = -x[1] -x[2] + 1.0;      dp_dx[1][1] = -x[0];      dp_dx[1][2] = -x[0];      dp_dx[1][3] = -0.50;      
    dp_dx[2][0] = x[1] + x[2];      dp_dx[2][1] = x[0];      dp_dx[2][2] = x[0];      dp_dx[2][3] = 1.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 1.0;      dp_dx[4][3] = 0.0;      
}


/**
    Update dpdx matrix of po
*/
void dpdx_um_po(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 8.0;      
    dp_dx[1][0] = -8.0;      
}

//-----------------------px for ev------------------- 
//--------------------------------------------------- 
/**
    Endmember fraction of fluid
*/
void px_um_fluid(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0];
        p[1]           = 1.0 -x[0];
}

    
/**
    Endmember fraction of ol
*/
void px_um_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 -x[0];
        p[1]           = x[0];
}

    
/**
    Endmember fraction of br
*/
void px_um_br(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 -x[0];
        p[1]           = x[0];
}

    
/**
    Endmember fraction of ch
*/
void px_um_ch(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 -x[0];
        p[1]           = x[0];
}

    
/**
    Endmember fraction of atg
*/
void px_um_atg(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] + x[0]*x[2] -x[0] -x[1]*x[3] -x[1] -x[2]*x[3] -x[2] + x[3] + 1.0;
        p[1]           = x[0] - 0.5*x[1]*x[3] - 0.5*x[2]*x[3] + 0.5*x[3];
        p[2]           = -x[0]*x[1] -x[0]*x[2] + 1.5*x[1]*x[3] + 1.5*x[2]*x[3] - 1.5*x[3];
        p[3]           = x[1];
        p[4]           = x[2];
}

    
/**
    Endmember fraction of g
*/
void px_um_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 -x[0];
        p[1]           = x[0];
}

    
/**
    Endmember fraction of ta
*/
void px_um_ta(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] + x[0]*x[2] -x[0] - 2.0*x[1] - 2.0*x[2] + 0.5*x[3]*x[4] + x[3] - 0.5*x[4] + 1.0;
        p[1]           = -x[0]*x[3] + x[0] + x[3]*x[4] -x[4];
        p[2]           = -x[0]*x[1] -x[0]*x[2] + x[0]*x[3] - 1.5*x[3]*x[4] + 1.5*x[4];
        p[3]           = 2.0*x[1] - 2.0*x[3];
        p[4]           = 2.0*x[2];
        p[5]           = x[3];
}

    
/**
    Endmember fraction of chl
*/
void px_um_chl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[0]*x[1] -x[0]*x[2] -x[0]*x[3] + 0.25*x[1]*x[4] + 1.25*x[1]*x[5] + 1.25*x[2]*x[5] - 0.25*x[3]*x[4] + 1.25*x[3]*x[5] + 2.0*x[3] - 0.25*x[4] - 1.25*x[5];
        p[1]           = 3.0*x[0]*x[1] + 2.0*x[0]*x[2] + x[0]*x[3] - 2.0*x[0] - 1.25*x[1]*x[4] - 2.25*x[1]*x[5] -x[1] - 2.25*x[2]*x[5] -x[2] + 1.25*x[3]*x[4] - 2.25*x[3]*x[5] -x[3] + 1.25*x[4] + 2.25*x[5] + 1.0;
        p[2]           = x[1] -x[3];
        p[3]           = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - 0.25*x[1]*x[4] - 1.25*x[1]*x[5] - 1.25*x[2]*x[5] + 0.25*x[3]*x[4] - 1.25*x[3]*x[5] + 0.25*x[4] + 1.25*x[5];
        p[4]           = -x[0]*x[1] -x[0]*x[2] -x[0]*x[3] + x[0] + x[1]*x[5] + x[2]*x[5] + x[3]*x[5] -x[5];
        p[5]           = -2.0*x[0]*x[1] -x[0]*x[2] + x[0] + 1.25*x[1]*x[4] + 1.25*x[1]*x[5] + 1.25*x[2]*x[5] - 1.25*x[3]*x[4] + 1.25*x[3]*x[5] - 1.25*x[4] - 1.25*x[5];
        p[6]           = x[2];
}

    
/**
    Endmember fraction of anth
*/
void px_um_anth(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           =-x[0] + x[1]*x[3] - x[1] - 1.5*x[2] - x[3] + 1.0;
        p[1]           = x[1];
        p[2]           =-x[0]*x[1] + x[0] + 2.0*x[1]*x[3] - 2.5*x[2] - 2.0*x[3];
        p[3]           =-x[1]*x[3] + 2.5*x[2] + x[3];
        p[4]           = x[0]*x[1] - 2.0*x[1]*x[3] + 1.5*x[2] + 2.0*x[3];
}

/**
    Endmember fraction of spi
*/
void px_um_spi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0] + x[1] - 1.0;
        p[1]           = 1.0 -x[0];
        p[2]           = 1.0 -x[1];
}

    
/**
    Endmember fraction of opx
*/
void px_um_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[0] -x[1] -x[2] - 0.5*x[3] + 1.0;
        p[1]           = -x[0]*x[1] -x[0]*x[2] + x[0] - 0.5*x[3];
        p[2]           = x[0]*x[1] + x[0]*x[2] + x[3];
        p[3]           = x[1];
        p[4]           = x[2];
}

    
/**
    Endmember fraction of po
*/
void px_um_po(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 8.0*x[0];
        p[1]           = 1.0 - 8.0*x[0];
}


//-----------------------obj for ev------------------- 
//--------------------------------------------------- 

    
/**
    Objective function of fluid
*/
double obj_um_fluid(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_fluid(SS_ref_db,x);

    
    sf[0]          = x[0];
    sf[1]          = 1.0 - x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]));
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]));
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_fluid(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ol
*/
double obj_um_ol(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_ol(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = 1.0 - x[0];
    sf[1]          = x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[1], 2.0))) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_ol(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of br
*/
double obj_um_br(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_br(SS_ref_db,x);

    
    sf[0]          = 1.0 - x[0];
    sf[1]          = x[0];
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]));
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]));
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_br(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ch
*/
double obj_um_ch(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_ch(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = 1.0 - x[0];
    sf[1]          = x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 9.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[1], 9.0))) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_ch(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of atg
*/
double obj_um_atg(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_atg(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0]*x[1] + x[0]*x[2] - x[0] - x[1]*x[3] - x[1] - x[2]*x[3] - x[2] + x[3] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[2] + x[0] + x[1]*x[3] + x[2]*x[3] - x[3];
    sf[2]          = x[2];
    sf[3]          = x[1];
    sf[4]          = -x[0] + 0.5*x[1]*x[3] + 0.5*x[2]*x[3] - 0.5*x[3] + 1.0;
    sf[5]          = x[0] - 0.5*x[1]*x[3] - 0.5*x[2]*x[3] + 0.5*x[3];
    sf[6]          = -0.5*x[1] - 0.5*x[2] + 1.0;
    sf[7]          = 0.5*x[1] + 0.5*x[2];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*cpow(sf[4], 2.0)*cpow(sf[6], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*cpow(sf[5], 2.0)*cpow(sf[6], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[1]*cpow(sf[4], 2.0)*cpow(sf[6], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(4.0*sf[3]*cpow(sf[4], 2.0)*sf[6]*sf[7])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(4.0*sf[2]*cpow(sf[4], 2.0)*sf[6]*sf[7])) + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_atg(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of g
*/
double obj_um_g(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_g(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = 1.0 - x[0];
    sf[1]          = x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 3.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[1], 3.0))) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_g(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ta
*/
double obj_um_ta(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_ta(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0]*x[3] - x[0] - x[3]*x[4] - x[3] + x[4] + 1.0;
    sf[1]          = -x[0]*x[3] + x[0] + x[3]*x[4] - x[4];
    sf[2]          = x[3];
    sf[3]          = x[0]*x[1] + x[0]*x[2] - x[0] - x[1] - x[2] + 0.5*x[3]*x[4] - 0.5*x[4] + 1.0;
    sf[4]          = -x[0]*x[1] - x[0]*x[2] + x[0] - 0.5*x[3]*x[4] + 0.5*x[4];
    sf[5]          = x[2];
    sf[6]          = x[1];
    sf[7]          = -x[1] - x[2] + x[3] + 1.0;
    sf[8]          = x[1] + x[2] - x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*cpow(sf[3], 2.0)*cpow(sf[7], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*cpow(sf[4], 2.0)*cpow(sf[7], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*cpow(sf[4], 2.0)*cpow(sf[7], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(16.0*sf[0]*sf[3]*sf[6]*sf[7]*sf[8])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(16.0*sf[0]*sf[3]*sf[5]*sf[7]*sf[8])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[2]*cpow(sf[6], 2.0)*cpow(sf[7], 2.0))) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_ta(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of chl
*/
double obj_um_chl(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_chl(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0]*x[1] - x[0]*x[3] - x[0] - x[1]*x[4] - x[1] + x[3]*x[4] + x[3] + x[4] + 1.0;
    sf[1]          = -x[0]*x[1] + x[0]*x[3] + x[0] + x[1]*x[4] - x[3]*x[4] - x[4];
    sf[2]          = x[1] - x[3];
    sf[3]          = -x[0] + 0.25*x[1]*x[4] + 0.25*x[1]*x[5] + 0.25*x[2]*x[5] - 0.25*x[3]*x[4] + 0.25*x[3]*x[5] - 0.25*x[4] - 0.25*x[5] + 1.0;
    sf[4]          = x[0] - 0.25*x[1]*x[4] - 0.25*x[1]*x[5] - 0.25*x[2]*x[5] + 0.25*x[3]*x[4] - 0.25*x[3]*x[5] + 0.25*x[4] + 0.25*x[5];
    sf[5]          = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - x[0] - x[1]*x[5] - x[1] - x[2]*x[5] - x[2] - x[3]*x[5] - x[3] + x[5] + 1.0;
    sf[6]          = -x[0]*x[1] - x[0]*x[2] - x[0]*x[3] + x[0] + x[1]*x[5] + x[2]*x[5] + x[3]*x[5] - x[5];
    sf[7]          = x[2];
    sf[8]          = x[1] + x[3];
    sf[9]          = -x[1] - 0.5*x[2] + 1.0;
    sf[10]          = x[1] + 0.5*x[2];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(4.0*sf[0]*sf[10]*cpow(sf[3], 4.0)*sf[8]*sf[9])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*cpow(sf[3], 4.0)*sf[5]*cpow(sf[9], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[10], 2.0)*sf[2]*cpow(sf[3], 4.0)*sf[8])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(4.0*sf[10]*sf[1]*cpow(sf[4], 4.0)*sf[8]*sf[9])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[0]*cpow(sf[4], 4.0)*sf[6]*cpow(sf[9], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[1]*cpow(sf[3], 4.0)*sf[5]*cpow(sf[9], 2.0))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(4.0*sf[0]*sf[10]*cpow(sf[3], 4.0)*sf[7]*sf[9])) + mu_Gex[6];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_chl(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of anth
*/
double obj_um_anth(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_anth(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -x[0] + x[1]*x[3] - 1.5*x[2] - x[3] + 1.0;
    sf[1]          = x[0] - x[1]*x[3] + 1.5*x[2] + x[3];
    sf[2]          = -x[0] + x[2] + 1.0;
    sf[3]          = x[0] - x[2];
    sf[4]          = x[1];
    sf[5]          = x[0]*x[1] - x[0] - x[1]*x[3] - x[1] + x[3] + 1.0;
    sf[6]          = -x[0]*x[1] + x[0] + x[1]*x[3] - x[3];
    sf[7]          = 0.5*x[1];
    sf[8]          = 1.0 - 0.5*x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 2.0)*cpow(sf[2], 3.0)*cpow(sf[5], 2.0)*sf[8])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*cpow(sf[0], 2.0)*cpow(sf[2], 3.0)*cpow(sf[4], 2.0)*csqrt(sf[7])*csqrt(sf[8]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[1], 2.0)*cpow(sf[3], 3.0)*cpow(sf[6], 2.0)*sf[8])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[1], 2.0)*cpow(sf[2], 3.0)*cpow(sf[6], 2.0)*sf[8])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(cpow(sf[1], 2.0)*cpow(sf[3], 3.0)*cpow(sf[5], 2.0)*sf[8])) + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_anth(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}   
    
/**
    Objective function of spi
*/
double obj_um_spi(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_spi(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[1];
    sf[1]          = 1.0 - x[1];
    sf[2]          = 1.0 - x[0];
    sf[3]          = x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[3])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*sf[2])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[1]*sf[3])) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_spi(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of opx
*/
double obj_um_opx(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_opx(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0]*x[1] + x[0]*x[2] - x[0] - x[1] - x[2] + 0.5*x[3] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[2] + x[0] - 0.5*x[3];
    sf[2]          = x[2];
    sf[3]          = x[1];
    sf[4]          = -x[0] - 0.5*x[3] + 1.0;
    sf[5]          = x[0] + 0.5*x[3];
    sf[6]          = 0.5*x[1] + 0.5*x[2];
    sf[7]          = -0.5*x[1] - 0.5*x[2] + 1.0;
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[4]*csqrt(sf[7]))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[5]*csqrt(sf[7]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[5]*csqrt(sf[7]))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(1.4142*sf[3]*sf[4]*cpow(sf[6], 0.25)*cpow(sf[7], 0.25))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(1.4142*sf[2]*sf[4]*cpow(sf[6], 0.25)*cpow(sf[7], 0.25))) + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_opx(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of po
*/
double obj_um_po(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_um_po(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = 1.0 - x[0];
    sf[1]          = x[0];
    
    mu[0]          = gb[0] + R*T*creal(clog(1.4576*cpow(sf[0], 0.875)*cpow(sf[1], 0.125))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0])) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_um_po(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}



//-----------------------p2x for ev------------------- 
//--------------------------------------------------- 

/**
    Endmember to xeos for fluid
*/
void p2x_um_fluid(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[0];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ol
*/
void p2x_um_ol(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}


/**
    Endmember to xeos for br
*/
void p2x_um_br(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ch
*/
void p2x_um_ch(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for atg
*/
void p2x_um_atg(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = (3.0*d->p[1] + d->p[2])/(d->p[0] + d->p[1] + d->p[2] + 2.0);
    d->iguess[1]  = d->p[3];
    d->iguess[2]  = d->p[4];
    d->iguess[3]  = d->iguess[0] - (d->p[1]+d->p[2])/(d->p[1]+d->p[2]+d->p[0]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for g
*/
void p2x_um_g(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ta
*/
void p2x_um_ta(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = (3*d->p[1]+2*d->p[2])/(1+2*(d->p[0]+d->p[1]+d->p[2])+d->p[3]+d->p[4]-d->p[5]);
    d->iguess[1]  = d->p[5]+0.5*d->p[3];
    d->iguess[2]  = 0.5*d->p[4];
    d->iguess[3]  = d->p[5];
    d->iguess[4]  = d->iguess[0]-d->p[1]/(1-d->p[5]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for chl
*/
void p2x_um_chl(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]   = d->p[6];
    d->iguess[3] = d->p[0]/2.0 + d->p[3]/2.0;
    d->iguess[1]   = d->p[2] + d->iguess[3];
    d->iguess[0]  = (5.0*(d->p[3] + d->p[4]) + d->p[5])/(5.0 + d->p[1] - d->p[2] + d->p[4] + d->p[5]);
    d->iguess[5] = d->iguess[0] - d->p[4]/(d->p[1] + d->p[4] + d->p[5]);
    d->iguess[4] = d->iguess[0] - (d->p[3] + d->p[5])/(1 - d->p[2]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}


/**
    Endmember to xeos for anth
*/
void p2x_um_anth(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1] = d->p[1];
    d->iguess[0] = (2.0*(1.0-d->p[0]-d->p[1])+5.0*d->p[2]+2.0*d->p[3]+3.0*d->p[4])/(7.0-2.0*(d->p[1]));
    d->iguess[2] = d->iguess[0] - d->p[2] -d->p[4];
    d->iguess[3] = (d->p[3] - d->p[4] - d->iguess[2] + d->iguess[0]*d->iguess[1])/(d->iguess[1] - 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}



/**
    Endmember to xeos for spi
*/
void p2x_um_spi(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1]  = d->p[0]+d->p[1];
    d->iguess[0]  = d->iguess[1] - d->p[1] + d->p[2];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for opx
*/
void p2x_um_opx(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = (2*d->p[1]+d->p[2])/(2-d->p[3]-d->p[4]);
    d->iguess[1]  = d->p[3];
    d->iguess[2]  = d->p[4];
    d->iguess[3]  = 2*(d->p[1]+d->p[2]-d->iguess[0]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for po
*/
void p2x_um_po(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = (1.0-d->p[1])/8.0;
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}


/**************************************************************************************/
/**************************************************************************************/
/********************IGNEOUS ALKALINE DATABASE (Weller et al., 2023)*******************/
/**************************************************************************************/
/**************************************************************************************/


/**
    Endmember to xeos for ness
*/
void p2x_alk_ness(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[3]  = d->p[5];
    d->iguess[4]  = 0.333333333333333*d->p[4];
    d->iguess[2]  = d->p[3];
    d->iguess[0]  = 3.0*d->iguess[4] + d->p[1];
    d->iguess[1]  = (4.0*d->iguess[3] + 4.0*d->p[0] + 3.0*d->iguess[2] + 4.0*d->iguess[0] - 4.0)/(3.0*d->iguess[4] + d->iguess[0] - 4.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for kals
*/
void p2x_alk_kals(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for lct
*/
void p2x_alk_lct(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[0];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for mel
*/
void p2x_alk_mel(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[3]  = d->p[4];
    d->iguess[1]  = 0.5*d->p[3];
    d->iguess[2]  = 2.0*d->iguess[1] + d->p[0];
    d->iguess[0]  = (d->iguess[3] + d->p[1] + d->iguess[2] - 1.0)/(d->iguess[3] + d->iguess[2] - 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for fl
*/
void p2x_alk_fl(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[3];
    d->iguess[1]  = d->p[2];
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for liq
*/
void p2x_alk_liq(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[10]  = d->p[10];
    d->iguess[11]  = d->p[11];
    d->iguess[12]  = d->p[12];
    d->iguess[13]  = d->p[13];
    d->iguess[9]  = 6.0*d->p[14]/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    d->iguess[8]  = (6.0*d->p[9] + 6.0*d->iguess[13])/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    d->iguess[7]  = 6.0*d->p[8]/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    d->iguess[6]  = 6.0*d->p[7]/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    d->iguess[5]  = 6.0*d->p[6]/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    d->iguess[4]  = (6.0*d->p[5] + 6.0*d->iguess[11])/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    d->iguess[3]  = 6.0*d->p[4]/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    d->iguess[2]  = (6.0*d->p[3] + 3.0*d->iguess[12])/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    d->iguess[0]  = (6.0*d->p[2] + 6.0*d->iguess[10])/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    d->iguess[1]  = (6.0*d->p[1] + 3.0*d->iguess[11] + 6.0*d->iguess[10] + 3.0*d->iguess[13])/(7.0*d->iguess[11] + 6.0*d->iguess[10] - d->iguess[12] + 7.0*d->iguess[13] + 6.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/** 
  endmembers to xeos (biotite)
*/
void p2x_alk_bi(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[5];
    d->iguess[3]  = d->p[4];
    d->iguess[1]  = d->p[3];
    d->iguess[0]  = (-3.0*d->p[1] - 1.0*d->p[2])/(d->iguess[2] + d->iguess[3] + d->iguess[1] - 3.0);
    d->iguess[4]  = 1.5*d->iguess[2]*d->iguess[0] - 1.5*d->iguess[2] - 1.5*d->p[0] + 1.5*d->iguess[3]*d->iguess[0] - 1.5*d->iguess[3] + 1.5*d->iguess[0]*d->iguess[1] - 1.5*d->iguess[0] - 1.5*d->iguess[1] + 1.5;
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/** 
  endmembers to xeos (cordierite)
*/
void p2x_alk_cd(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;
	
	d->iguess[0]  = d->p[1];
	d->iguess[1]  = d->p[2];
	
	if (d->z_em[2]  == 0.0){ d->iguess[1]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (clinopyroxene)
*/
void p2x_alk_cpx(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = (2.0*d->p[1] + d->p[8])/(d->p[1] - d->p[2] - d->p[3] - d->p[4] - 0.5*d->p[5] - d->p[6] + d->p[7] + d->p[8] - d->p[9] + 1.0);	
	d->iguess[1]  = d->p[2] + d->p[3] + d->p[4] + d->p[5];
	d->iguess[2]  = d->p[1]+d->p[7]+d->p[8];
	d->iguess[3]  = d->p[6];
	d->iguess[4]  = (d->p[7] + ((2.0*d->p[1] + d->p[8])/(d->p[1] - d->p[2] - d->p[3] - d->p[4] - 0.5*d->p[5] - d->p[6] + d->p[7] + d->p[8] - d->p[9] + 1.0) - 1.0)*(d->p[1] + d->p[7] + d->p[8]))/(-d->p[2] - d->p[3] - d->p[4] - 0.5*d->p[5] - d->p[6] - d->p[9] + 1.0);
	d->iguess[5]  = d->p[4];
	d->iguess[6]  = d->p[3];
	d->iguess[7]  = d->p[5]/2.0;	
	d->iguess[8]  = d->p[9];	

	if (d->z_em[3]  == 0.0){ d->iguess[6]  = eps;}
	if (d->z_em[4]  == 0.0){ d->iguess[5]  = eps;}
	if (d->z_em[5]  == 0.0){ d->iguess[7]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (epidote)
*/
void p2x_alk_ep(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = d->p[2] + d->p[1]/2.0;
	d->iguess[1]  = d->p[1]/2.0;

	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (garnet)
*/
void p2x_alk_g(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[4]  = 0.25*d->p[5];
    d->iguess[3]  = d->p[4];
    d->iguess[2]  = d->p[3];
    d->iguess[1]  = d->iguess[2] + d->p[2];
    d->iguess[0]  = (d->iguess[1] + d->iguess[3] + d->p[0] + 4.0*d->iguess[4] - 1.0)/(d->iguess[1] - 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/** 
  endmembers to xeos (hornblende)
*/
void p2x_alk_hb(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0] = (-3.5*d->p[5] - 2.0*d->p[6] - 2.5*d->p[7])/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 1.5*d->p[4] - 1.5*d->p[5] - 1.5*d->p[6] - 1.5*d->p[7] + 0.5*d->p[8] - 2.0);
	d->iguess[1] = (d->p[1]-d->p[0] + 1.0-d->p[3]-d->p[8]-d->p[4]-d->p[6]-d->p[5]-d->p[7] -2*d->p[8] - d->p[10] + 2*(d->p[3] + d->p[8]))/2.0;
	d->iguess[2] = d->p[3] + d->p[8];
	d->iguess[3] = d->p[2] + d->p[9];
	d->iguess[4] = d->p[9]/(d->p[2]+d->p[9]);
	d->iguess[5] = 1.0-d->p[3]-d->p[8]-d->p[4]-d->p[6]-d->p[5]-d->p[7];
	d->iguess[6] = d->p[8];
	d->iguess[7] = d->p[10];
	d->iguess[8] = (-3.5*d->p[5] - 2.0*d->p[6] - 2.5*d->p[7])/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 1.5*d->p[4] - 1.5*d->p[5] - 1.5*d->p[6] - 1.5*d->p[7] + 0.5*d->p[8] - 2.0) -d->p[5] -d->p[7];
	d->iguess[9] = (d->p[5] + d->p[6] - (-3.5*d->p[5] - 2.0*d->p[6] - 2.5*d->p[7])*(0.5*d->p[0] - 0.5*d->p[1] - 0.5*d->p[10] - 0.5*d->p[3] + 0.5*d->p[4] + 0.5*d->p[5] + 0.5*d->p[6] + 0.5*d->p[7] - 0.5*d->p[8] + 0.5)/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 1.5*d->p[4] - 1.5*d->p[5] - 1.5*d->p[6] - 1.5*d->p[7] + 0.5*d->p[8] - 2.0))/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 0.5*d->p[4] - 0.5*d->p[5] - 0.5*d->p[6] - 0.5*d->p[7] + 0.5*d->p[8] - 0.5);

	if (d->z_em[8]  == 0){ d->iguess[6]  = eps;}
	if (d->z_em[10] == 0){ d->iguess[7]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (ilm)
*/
/** DEPRECATED */
void p2x_alk_ilm(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0] = d->p[1]+d->p[0];
	d->iguess[1] = d->p[0];
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (olivine)
*/
void p2x_alk_ol(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = (2.0*d->p[1]+d->p[3])/(2.0-d->p[0]);
	d->iguess[1]  = d->p[0];
	d->iguess[2]  = -d->p[0] - d->p[2] + 1.0 + (d->p[0] - 1.0)*(2.0*d->p[1] + d->p[3])/(2.0 - d->p[0]);
	
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (orthopyroxene)
*/
void p2x_alk_opx(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0] = (2.0*d->p[1] + d->p[2])/(d->p[0] + d->p[1] + d->p[2] + 0.5*d->p[6] - d->p[8] + 1.0);
	d->iguess[1] = 1.0 - d->p[3] - d->p[8] - d->p[0] - d->p[1] - d->p[2];
	d->iguess[2] = d->p[3];
	d->iguess[3] = (d->p[1] + d->p[2] + (2.0*d->p[1] + d->p[2])*(d->p[3] + d->p[8] - 1.0)/(d->p[0] + d->p[1] + d->p[2] + 0.5*d->p[6] - d->p[8] + 1.0))/(-d->p[0] - d->p[1] - d->p[2] - d->p[3] - 0.5*d->p[6]);
	d->iguess[4] = d->p[7];
	d->iguess[5] = d->p[6]/2.0;
	d->iguess[6] = d->p[5];
	d->iguess[7] = d->p[8];
	
	if (d->z_em[5]  == 0.0){ d->iguess[6]  = eps;}
	if (d->z_em[4]  == 0.0){ d->iguess[4]  = eps;}
	if (d->z_em[6]  == 0.0){ d->iguess[5]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (plagioclase)
*/
void p2x_alk_fsp(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;
	
	d->iguess[0] = d->p[1];
	d->iguess[1] = d->p[2];
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (spinel)
*/
void p2x_alk_spn(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2] = d->p[6];
    d->iguess[3] = d->p[7];
    d->iguess[1] = (-d->p[4] - d->p[5])/(d->iguess[2] + d->iguess[3] - 1.0);
    d->iguess[0] = (-d->iguess[2] - d->p[0] - d->p[1] + d->iguess[3] + 1.0)/(d->iguess[3] + 1.0);
    d->iguess[4] = -3.0*d->p[1]/2.0 - d->iguess[3]*d->iguess[0] + d->iguess[3] - d->iguess[0] + 1.0;
    d->iguess[6] = d->iguess[2]*d->iguess[1] + 3.0*d->p[5]/2.0 + d->iguess[3]*d->iguess[1] - d->iguess[1];
    d->iguess[5] = -d->iguess[6] + d->iguess[2]*d->iguess[1] - 3.0*d->p[3]/2.0 + d->iguess[3]*d->iguess[0] + d->iguess[3]*d->iguess[1] - 3.0*d->iguess[3]/2.0 + d->iguess[0] - d->iguess[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}



/**
    Update dpdx matrix of liq
*/
void dpdx_alk_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][1] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][2] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][3] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][4] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][5] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][6] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][7] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][8] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][9] =-x[10] - 7.0/6.0*x[11] + 1.0/6.0*x[12] - 7.0/6.0*x[13] - 1.0;      dp_dx[0][10] =-x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0;      dp_dx[0][11] = -7.0/6.0*x[0] - 7.0/6.0*x[1] - 7.0/6.0*x[2] - 7.0/6.0*x[3] - 7.0/6.0*x[4] - 7.0/6.0*x[5] - 7.0/6.0*x[6] - 7.0/6.0*x[7] - 7.0/6.0*x[8] - 7.0/6.0*x[9] + 0.5;      dp_dx[0][12] = 1.0/6.0*x[0] + 1.0/6.0*x[1] + 1.0/6.0*x[2] + 1.0/6.0*x[3] + 1.0/6.0*x[4] + 1.0/6.0*x[5] + 1.0/6.0*x[6] + 1.0/6.0*x[7] + 1.0/6.0*x[8] + 1.0/6.0*x[9] - 0.5;      dp_dx[0][13] = -7.0/6.0*x[0] - 7.0/6.0*x[1] - 7.0/6.0*x[2] - 7.0/6.0*x[3] - 7.0/6.0*x[4] - 7.0/6.0*x[5] - 7.0/6.0*x[6] - 7.0/6.0*x[7] - 7.0/6.0*x[8] - 7.0/6.0*x[9] + 0.5;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      dp_dx[1][7] = 0.0;      dp_dx[1][8] = 0.0;      dp_dx[1][9] = 0.0;      dp_dx[1][10] = x[1] - 1.0;      dp_dx[1][11] = 7.0/6.0*x[1] - 0.5;      dp_dx[1][12] = -1.0/6.0*x[1];      dp_dx[1][13] = 7.0/6.0*x[1] - 0.5;      
    dp_dx[2][0] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 0.0;      dp_dx[2][8] = 0.0;      dp_dx[2][9] = 0.0;      dp_dx[2][10] = x[0] - 1.0;      dp_dx[2][11] = 7.0/6.0*x[0];      dp_dx[2][12] = -1.0/6.0*x[0];      dp_dx[2][13] = 7.0/6.0*x[0];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      dp_dx[3][9] = 0.0;      dp_dx[3][10] = x[2];      dp_dx[3][11] = 7.0/6.0*x[2];      dp_dx[3][12] = -1.0/6.0*x[2] - 0.5;      dp_dx[3][13] = 7.0/6.0*x[2];      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = 0.0;      dp_dx[4][7] = 0.0;      dp_dx[4][8] = 0.0;      dp_dx[4][9] = 0.0;      dp_dx[4][10] = x[3];      dp_dx[4][11] = 7.0/6.0*x[3];      dp_dx[4][12] = -1.0/6.0*x[3];      dp_dx[4][13] = 7.0/6.0*x[3];      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 0.0;      dp_dx[5][7] = 0.0;      dp_dx[5][8] = 0.0;      dp_dx[5][9] = 0.0;      dp_dx[5][10] = x[4];      dp_dx[5][11] = 7.0/6.0*x[4] - 1.0;      dp_dx[5][12] = -1.0/6.0*x[4];      dp_dx[5][13] = 7.0/6.0*x[4];      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      dp_dx[6][8] = 0.0;      dp_dx[6][9] = 0.0;      dp_dx[6][10] = x[5];      dp_dx[6][11] = 7.0/6.0*x[5];      dp_dx[6][12] = -1.0/6.0*x[5];      dp_dx[6][13] = 7.0/6.0*x[5];      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[7][7] = 0.0;      dp_dx[7][8] = 0.0;      dp_dx[7][9] = 0.0;      dp_dx[7][10] = x[6];      dp_dx[7][11] = 7.0/6.0*x[6];      dp_dx[7][12] = -1.0/6.0*x[6];      dp_dx[7][13] = 7.0/6.0*x[6];      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[8][8] = 0.0;      dp_dx[8][9] = 0.0;      dp_dx[8][10] = x[7];      dp_dx[8][11] = 7.0/6.0*x[7];      dp_dx[8][12] = -1.0/6.0*x[7];      dp_dx[8][13] = 7.0/6.0*x[7];      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = 0.0;      dp_dx[9][4] = 0.0;      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[9][9] = 0.0;      dp_dx[9][10] = x[8];      dp_dx[9][11] = 7.0/6.0*x[8];      dp_dx[9][12] = -1.0/6.0*x[8];      dp_dx[9][13] = 7.0/6.0*x[8] - 1.0;      
    dp_dx[10][0] = 0.0;      dp_dx[10][1] = 0.0;      dp_dx[10][2] = 0.0;      dp_dx[10][3] = 0.0;      dp_dx[10][4] = 0.0;      dp_dx[10][5] = 0.0;      dp_dx[10][6] = 0.0;      dp_dx[10][7] = 0.0;      dp_dx[10][8] = 0.0;      dp_dx[10][9] = 0.0;      dp_dx[10][10] = 1.00;      dp_dx[10][11] = 0.0;      dp_dx[10][12] = 0.0;      dp_dx[10][13] = 0.0;      
    dp_dx[11][0] = 0.0;      dp_dx[11][1] = 0.0;      dp_dx[11][2] = 0.0;      dp_dx[11][3] = 0.0;      dp_dx[11][4] = 0.0;      dp_dx[11][5] = 0.0;      dp_dx[11][6] = 0.0;      dp_dx[11][7] = 0.0;      dp_dx[11][8] = 0.0;      dp_dx[11][9] = 0.0;      dp_dx[11][10] = 0.0;      dp_dx[11][11] = 1.00;      dp_dx[11][12] = 0.0;      dp_dx[11][13] = 0.0;      
    dp_dx[12][0] = 0.0;      dp_dx[12][1] = 0.0;      dp_dx[12][2] = 0.0;      dp_dx[12][3] = 0.0;      dp_dx[12][4] = 0.0;      dp_dx[12][5] = 0.0;      dp_dx[12][6] = 0.0;      dp_dx[12][7] = 0.0;      dp_dx[12][8] = 0.0;      dp_dx[12][9] = 0.0;      dp_dx[12][10] = 0.0;      dp_dx[12][11] = 0.0;      dp_dx[12][12] = 1.00;      dp_dx[12][13] = 0.0;      
    dp_dx[13][0] = 0.0;      dp_dx[13][1] = 0.0;      dp_dx[13][2] = 0.0;      dp_dx[13][3] = 0.0;      dp_dx[13][4] = 0.0;      dp_dx[13][5] = 0.0;      dp_dx[13][6] = 0.0;      dp_dx[13][7] = 0.0;      dp_dx[13][8] = 0.0;      dp_dx[13][9] = 0.0;      dp_dx[13][10] = 0.0;      dp_dx[13][11] = 0.0;      dp_dx[13][12] = 0.0;      dp_dx[13][13] = 1.00;      
    dp_dx[14][0] = 0.0;      dp_dx[14][1] = 0.0;      dp_dx[14][2] = 0.0;      dp_dx[14][3] = 0.0;      dp_dx[14][4] = 0.0;      dp_dx[14][5] = 0.0;      dp_dx[14][6] = 0.0;      dp_dx[14][7] = 0.0;      dp_dx[14][8] = 0.0;      dp_dx[14][9] = x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0;      dp_dx[14][10] = x[9];      dp_dx[14][11] = 7.0/6.0*x[9];      dp_dx[14][12] = -1.0/6.0*x[9];      dp_dx[14][13] = 7.0/6.0*x[9];      
}


/**
    Update dpdx matrix of fl
*/
void dpdx_alk_fl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      dp_dx[0][1] = -1.00;      dp_dx[0][2] = -1.00;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.00;      dp_dx[2][2] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.00;      
}


/**
    Update dpdx matrix of fsp
*/
void dpdx_alk_fsp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      dp_dx[0][1] = -1.00;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.00;      
}


/**
    Update dpdx matrix of spn
*/
void dpdx_alk_spn(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0/3.0*x[3] - 1.0/3.0;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = -1.00;      dp_dx[0][3] = 1.0/3.0 - 1.0/3.0*x[0];      dp_dx[0][4] = 2.0/3.0;      dp_dx[0][5] = 0.0;      dp_dx[0][6] = 0.0;      
    dp_dx[1][0] = -2.0/3.0*x[3] - 2.0/3.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 2.0/3.0 - 2.0/3.0*x[0];      dp_dx[1][4] = -2.0/3.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      
    dp_dx[2][0] = 1.0/3.0*x[3] + 1.0/3.0;      dp_dx[2][1] = 1.0/3.0*x[2] + 1.0/3.0*x[3] - 1.0/3.0;      dp_dx[2][2] = 1.0/3.0*x[1];      dp_dx[2][3] = 1.0/3.0*x[0] + 1.0/3.0*x[1] - 1.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 2.0/3.0;      dp_dx[2][6] = 2.0/3.0;      
    dp_dx[3][0] = 2.0/3.0*x[3] + 2.0/3.0;      dp_dx[3][1] = 2.0/3.0*x[2] + 2.0/3.0*x[3] - 2.0/3.0;      dp_dx[3][2] = 2.0/3.0*x[1];      dp_dx[3][3] = 2.0/3.0*x[0] + 2.0/3.0*x[1] - 1.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = -2.0/3.0;      dp_dx[3][6] = -2.0/3.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = -1.0/3.0*x[2] - 1.0/3.0*x[3] + 1.0/3.0;      dp_dx[4][2] = -1.0/3.0*x[1];      dp_dx[4][3] = -1.0/3.0*x[1];      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = -2.0/3.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = -2.0/3.0*x[2] - 2.0/3.0*x[3] + 2.0/3.0;      dp_dx[5][2] = -2.0/3.0*x[1];      dp_dx[5][3] = -2.0/3.0*x[1];      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 2.0/3.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 1.00;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      dp_dx[6][6] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 1.00;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      
}


/**
    Update dpdx matrix of g
*/
void dpdx_alk_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = 0.0;      dp_dx[0][3] = -1.00;      dp_dx[0][4] = -4.00;      
    dp_dx[1][0] = 1.0 - x[1];      dp_dx[1][1] =-x[0];      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.00;      dp_dx[2][2] = -1.00;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.00;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.00;      dp_dx[4][4] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 4.00;      
}


/**
    Update dpdx matrix of ol
*/
void dpdx_alk_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.00;      dp_dx[0][2] = 0.0;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = -1.00;      
    dp_dx[2][0] = x[1] - 1.0;      dp_dx[2][1] = x[0] - 1.0;      dp_dx[2][2] = -1.00;      
    dp_dx[3][0] =-x[1];      dp_dx[3][1] =-x[0];      dp_dx[3][2] = 2.00;      
}


/**
    Update dpdx matrix of opx
*/
void dpdx_alk_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[2] + x[7] - 1.0;      dp_dx[0][1] =-x[3] - 1.0;      dp_dx[0][2] = x[0] - 1.0;      dp_dx[0][3] =-x[1] + x[5] - x[7] + 1.0;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = x[3];      dp_dx[0][6] = 0.0;      dp_dx[0][7] = x[0] - x[3] - 1.0;      
    dp_dx[1][0] =-x[1] + x[5] - x[7] + 1.0;      dp_dx[1][1] =-x[0] - x[3];      dp_dx[1][2] = 0.0;      dp_dx[1][3] =-x[1] + x[5] - x[7] + 1.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = x[0] + x[3];      dp_dx[1][6] = 0.0;      dp_dx[1][7] =-x[0] - x[3];      
    dp_dx[2][0] = x[1] - x[2] - x[5];      dp_dx[2][1] = x[0] + 2.0*x[3];      dp_dx[2][2] =-x[0];      dp_dx[2][3] = 2.0*x[1] - 2.0*x[5] + 2.0*x[7] - 2.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] =-x[0] - 2.0*x[3];      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 2.0*x[3];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.00;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      dp_dx[3][7] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 1.00;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = -1.00;      dp_dx[4][5] = -2.00;      dp_dx[4][6] = -1.00;      dp_dx[4][7] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 1.00;      dp_dx[5][7] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 2.00;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 1.00;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      dp_dx[7][7] = 0.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = 1.00;      
}


/**
    Update dpdx matrix of cpx
*/
void dpdx_alk_cpx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = -1.00;      dp_dx[0][2] = -1.00;      dp_dx[0][3] = -1.00;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 0.0;      dp_dx[0][6] = 0.0;      dp_dx[0][7] = 0.0;      dp_dx[0][8] = -1.00;      
    dp_dx[1][0] =-x[1] - x[3] + x[7] - x[8] + 1.0;      dp_dx[1][1] =-x[0] - x[4];      dp_dx[1][2] = 0.0;      dp_dx[1][3] =-x[0] - x[4];      dp_dx[1][4] =-x[1] - x[3] + x[7] - x[8] + 1.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      dp_dx[1][7] = x[0] + x[4];      dp_dx[1][8] =-x[0] - x[4];      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.00;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = -1.00;      dp_dx[2][6] = -1.00;      dp_dx[2][7] = -2.00;      dp_dx[2][8] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 1.00;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 1.00;      dp_dx[4][6] = 0.0;      dp_dx[4][7] = 0.0;      dp_dx[4][8] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 0.0;      dp_dx[5][7] = 2.00;      dp_dx[5][8] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 1.00;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      dp_dx[6][8] = 0.0;      
    dp_dx[7][0] =-x[2];      dp_dx[7][1] =-x[4];      dp_dx[7][2] = 1.0 - x[0];      dp_dx[7][3] =-x[4];      dp_dx[7][4] =-x[1] - x[3] + x[7] - x[8] + 1.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      dp_dx[7][7] = x[4];      dp_dx[7][8] =-x[4];      
    dp_dx[8][0] = x[1] + x[2] + x[3] - x[7] + x[8] - 1.0;      dp_dx[8][1] = x[0] + 2.0*x[4];      dp_dx[8][2] = x[0];      dp_dx[8][3] = x[0] + 2.0*x[4];      dp_dx[8][4] = 2.0*x[1] + 2.0*x[3] - 2.0*x[7] + 2.0*x[8] - 2.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] =-x[0] - 2.0*x[4];      dp_dx[8][8] = x[0] + 2.0*x[4];      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = 0.0;      dp_dx[9][4] = 0.0;      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = 1.00;      
}


/**
    Update dpdx matrix of ilm
*/
void dpdx_alk_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = 1.00;      dp_dx[0][3] = 0.0;      
    dp_dx[1][0] = 1.0 - x[1];      dp_dx[1][1] =-x[0];      dp_dx[1][2] = -1.00;      dp_dx[1][3] = 0.0;      
    dp_dx[2][0] = -1.00;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = -1.00;      dp_dx[3][3] = 1.00;      
    dp_dx[4][0] = x[1];      dp_dx[4][1] = x[0];      dp_dx[4][2] = 1.00;      dp_dx[4][3] = -1.00;      
}


/**
    Update dpdx matrix of ness
*/
void dpdx_alk_ness(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.25*x[1] - 1.0;      dp_dx[0][1] = 0.25*x[0] + 0.75*x[4] - 1.0;      dp_dx[0][2] = -0.750;      dp_dx[0][3] = -1.00;      dp_dx[0][4] = 0.75*x[1];      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = -3.00;      
    dp_dx[2][0] = -0.25*x[1];      dp_dx[2][1] = -0.25*x[0] - 0.75*x[4] + 1.0;      dp_dx[2][2] = -0.250;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = -0.75*x[1];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.00;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 3.00;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 1.00;      dp_dx[5][4] = 0.0;      
}


/**
    Update dpdx matrix of lct
*/
void dpdx_alk_lct(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 1.00;      
    dp_dx[1][0] = -1.00;      
}


/**
    Update dpdx matrix of kals
*/
void dpdx_alk_kals(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      
    dp_dx[1][0] = 1.00;      
}


/**
    Update dpdx matrix of mel
*/
void dpdx_alk_mel(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = -2.00;      dp_dx[0][2] = 1.00;      dp_dx[0][3] = 0.0;      
    dp_dx[1][0] = x[2] + x[3] - 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = x[0] - 1.0;      dp_dx[1][3] = x[0] - 1.0;      
    dp_dx[2][0] =-x[2] - x[3] + 1.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] =-x[0];      dp_dx[2][3] =-x[0];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 2.00;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.00;      
}


/**
    Update dpdx matrix of hb
*/
void dpdx_alk_hb(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = -1.00;      dp_dx[0][2] = 1.00;      dp_dx[0][3] = -0.500;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 1.00;      dp_dx[0][6] = -1.00;      dp_dx[0][7] = -1.00;      dp_dx[0][8] = 0.0;      dp_dx[0][9] = 0.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 1.00;      dp_dx[1][2] = -1.00;      dp_dx[1][3] = -0.500;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 1.00;      dp_dx[1][7] = 0.0;      dp_dx[1][8] = 0.0;      dp_dx[1][9] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 1.0 - x[4];      dp_dx[2][4] =-x[3];      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 0.0;      dp_dx[2][8] = 0.0;      dp_dx[2][9] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.00;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = -1.00;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      dp_dx[3][9] = 0.0;      
    dp_dx[4][0] = x[2] + x[5] - 1.0;      dp_dx[4][1] = x[9];      dp_dx[4][2] = x[0] - 1.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = x[0] - 1.0;      dp_dx[4][6] = x[9];      dp_dx[4][7] = x[9];      dp_dx[4][8] = -1.50;      dp_dx[4][9] = x[1] + x[6] + x[7] - 1.0;      
    dp_dx[5][0] =-x[1] + x[2] + x[5] - x[6] - x[7] + 1.0;      dp_dx[5][1] =-x[0] + 2.0*x[9];      dp_dx[5][2] = x[0];      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = x[0];      dp_dx[5][6] =-x[0] + 2.0*x[9];      dp_dx[5][7] =-x[0] + 2.0*x[9];      dp_dx[5][8] = -2.50;      dp_dx[5][9] = 2.0*x[1] + 2.0*x[6] + 2.0*x[7] - 2.0;      
    dp_dx[6][0] =-x[2] - x[5];      dp_dx[6][1] =-x[9];      dp_dx[6][2] =-x[0];      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] =-x[0];      dp_dx[6][6] =-x[9];      dp_dx[6][7] =-x[9];      dp_dx[6][8] = 2.50;      dp_dx[6][9] =-x[1] - x[6] - x[7] + 1.0;      
    dp_dx[7][0] = x[1] - x[2] - x[5] + x[6] + x[7];      dp_dx[7][1] = x[0] - 2.0*x[9];      dp_dx[7][2] =-x[0];      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] =-x[0];      dp_dx[7][6] = x[0] - 2.0*x[9];      dp_dx[7][7] = x[0] - 2.0*x[9];      dp_dx[7][8] = 1.50;      dp_dx[7][9] = -2.0*x[1] - 2.0*x[6] - 2.0*x[7] + 2.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 1.00;      dp_dx[8][7] = 0.0;      dp_dx[8][8] = 0.0;      dp_dx[8][9] = 0.0;      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = x[4];      dp_dx[9][4] = x[3];      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = 0.0;      dp_dx[9][9] = 0.0;      
    dp_dx[10][0] = 0.0;      dp_dx[10][1] = 0.0;      dp_dx[10][2] = 0.0;      dp_dx[10][3] = 0.0;      dp_dx[10][4] = 0.0;      dp_dx[10][5] = 0.0;      dp_dx[10][6] = 0.0;      dp_dx[10][7] = 1.00;      dp_dx[10][8] = 0.0;      dp_dx[10][9] = 0.0;      
}


/**
    Update dpdx matrix of bi
*/
void dpdx_alk_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] + x[2] + x[3] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = x[0] - 1.0;      dp_dx[0][3] = x[0] - 1.0;      dp_dx[0][4] = -2.0/3.0;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = -1.0/3.0;      
    dp_dx[2][0] =-x[1] - x[2] - x[3];      dp_dx[2][1] =-x[0];      dp_dx[2][2] =-x[0];      dp_dx[2][3] =-x[0];      dp_dx[2][4] = 1.00;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.00;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.00;      dp_dx[4][4] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 1.00;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      
}


/**
    Update dpdx matrix of ep
*/
void dpdx_alk_ep(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      dp_dx[0][1] = -1.00;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 2.00;      
    dp_dx[2][0] = 1.00;      dp_dx[2][1] = -1.00;      
}


/**
    Update dpdx matrix of cd
*/
void dpdx_alk_cd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      dp_dx[0][1] = -1.00;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.00;      
}

    
/**
    Endmember fraction of liq
*/
void px_alk_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           =-x[0] + x[10]*(-1.0*x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0) + 1.0/6.0*x[11]*(-7.0*x[0] - 7.0*x[1] - 7.0*x[2] - 7.0*x[3] - 7.0*x[4] - 7.0*x[5] - 7.0*x[6] - 7.0*x[7] - 7.0*x[8] - 7.0*x[9] + 3.0) + 1.0/6.0*x[12]*(x[0] + x[1] + x[2] + x[3] + x[4] + x[5] + x[6] + x[7] + x[8] + x[9] - 3.0) + 1.0/6.0*x[13]*(-7.0*x[0] - 7.0*x[1] - 7.0*x[2] - 7.0*x[3] - 7.0*x[4] - 7.0*x[5] - 7.0*x[6] - 7.0*x[7] - 7.0*x[8] - 7.0*x[9] + 3.0) - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0;
        p[1]           = x[10]*x[1] - x[10] + 7.0/6.0*x[11]*x[1] - 0.5*x[11] - 1.0/6.0*x[12]*x[1] + 7.0/6.0*x[13]*x[1] - 0.5*x[13] + x[1];
        p[2]           = x[0]*x[10] + 7.0/6.0*x[0]*x[11] - 1.0/6.0*x[0]*x[12] + 7.0/6.0*x[0]*x[13] + x[0] - x[10];
        p[3]           = x[10]*x[2] + 7.0/6.0*x[11]*x[2] - 1.0/6.0*x[12]*x[2] - 0.5*x[12] + 7.0/6.0*x[13]*x[2] + x[2];
        p[4]           = x[10]*x[3] + 7.0/6.0*x[11]*x[3] - 1.0/6.0*x[12]*x[3] + 7.0/6.0*x[13]*x[3] + x[3];
        p[5]           = x[10]*x[4] + 7.0/6.0*x[11]*x[4] - x[11] - 1.0/6.0*x[12]*x[4] + 7.0/6.0*x[13]*x[4] + x[4];
        p[6]           = x[10]*x[5] + 7.0/6.0*x[11]*x[5] - 1.0/6.0*x[12]*x[5] + 7.0/6.0*x[13]*x[5] + x[5];
        p[7]           = x[10]*x[6] + 7.0/6.0*x[11]*x[6] - 1.0/6.0*x[12]*x[6] + 7.0/6.0*x[13]*x[6] + x[6];
        p[8]           = x[10]*x[7] + 7.0/6.0*x[11]*x[7] - 1.0/6.0*x[12]*x[7] + 7.0/6.0*x[13]*x[7] + x[7];
        p[9]           = x[10]*x[8] + 7.0/6.0*x[11]*x[8] - 1.0/6.0*x[12]*x[8] + 7.0/6.0*x[13]*x[8] - x[13] + x[8];
        p[10]           = x[10];
        p[11]           = x[11];
        p[12]           = x[12];
        p[13]           = x[13];
        p[14]           = x[10]*x[9] + 7.0/6.0*x[11]*x[9] - 1.0/6.0*x[12]*x[9] + 7.0/6.0*x[13]*x[9] + x[9];
}

    
/**
    Endmember fraction of fl
*/
void px_alk_fl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           =-x[0] - x[1] - x[2] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
        p[3]           = x[2];
}

    
/**
    Endmember fraction of fsp
*/
void px_alk_fsp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           =-x[0] - x[1] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}

    
/**
    Endmember fraction of spn
*/
void px_alk_spn(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -1.0/3.0*x[0]*x[3] - 1.0/3.0*x[0] - x[2] + 1.0/3.0*x[3] + 2.0/3.0*x[4] + 1.0/3.0;
        p[1]           = -2.0/3.0*x[0]*x[3] - 2.0/3.0*x[0] + 2.0/3.0*x[3] - 2.0/3.0*x[4] + 2.0/3.0;
        p[2]           = 1.0/3.0*x[0]*x[3] + 1.0/3.0*x[0] + 1.0/3.0*x[1]*x[2] + 1.0/3.0*x[1]*x[3] - 1.0/3.0*x[1] - x[3] + 2.0/3.0*x[5] + 2.0/3.0*x[6];
        p[3]           = 2.0/3.0*x[0]*x[3] + 2.0/3.0*x[0] + 2.0/3.0*x[1]*x[2] + 2.0/3.0*x[1]*x[3] - 2.0/3.0*x[1] - x[3] - 2.0/3.0*x[5] - 2.0/3.0*x[6];
        p[4]           = -1.0/3.0*x[1]*x[2] - 1.0/3.0*x[1]*x[3] + 1.0/3.0*x[1] - 2.0/3.0*x[6];
        p[5]           = -2.0/3.0*x[1]*x[2] - 2.0/3.0*x[1]*x[3] + 2.0/3.0*x[1] + 2.0/3.0*x[6];
        p[6]           = x[2];
        p[7]           = x[3];
}

    
/**
    Endmember fraction of g
*/
void px_alk_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] - x[0] - x[1] - x[3] - 4.0*x[4] + 1.0;
        p[1]           =-x[0]*x[1] + x[0];
        p[2]           = x[1] - x[2];
        p[3]           = x[2];
        p[4]           = x[3];
        p[5]           = 4.0*x[4];
}

    
/**
    Endmember fraction of ol
*/
void px_alk_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1];
        p[1]           = x[0] - x[2];
        p[2]           = x[0]*x[1] - x[0] - x[1] - x[2] + 1.0;
        p[3]           =-x[0]*x[1] + 2.0*x[2];
}

    
/**
    Endmember fraction of opx
*/
void px_alk_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[2] + x[0]*x[7] - x[0] - x[1]*x[3] - x[1] - x[2] + x[3]*x[5] - x[3]*x[7] + x[3] - x[7] + 1.0;
        p[1]           =-x[0]*x[1] + x[0]*x[5] - x[0]*x[7] + x[0] - x[1]*x[3] + x[3]*x[5] - x[3]*x[7] + x[3];
        p[2]           = x[0]*x[1] - x[0]*x[2] - x[0]*x[5] + 2.0*x[1]*x[3] - 2.0*x[3]*x[5] + 2.0*x[3]*x[7] - 2.0*x[3];
        p[3]           = x[2];
        p[4]           = x[1] - x[4] - 2.0*x[5] - x[6];
        p[5]           = x[6];
        p[6]           = 2.0*x[5];
        p[7]           = x[4];
        p[8]           = x[7];
}

    
/**
    Endmember fraction of cpx
*/
void px_alk_cpx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           =-x[1] - x[2] - x[3] - x[8] + 1.0;
        p[1]           =-x[0]*x[1] - x[0]*x[3] + x[0]*x[7] - x[0]*x[8] + x[0] - x[1]*x[4] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
        p[2]           = x[1] - x[5] - x[6] - 2.0*x[7];
        p[3]           = x[6];
        p[4]           = x[5];
        p[5]           = 2.0*x[7];
        p[6]           = x[3];
        p[7]           =-x[0]*x[2] - x[1]*x[4] + x[2] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
        p[8]           = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - x[0]*x[7] + x[0]*x[8] - x[0] + 2.0*x[1]*x[4] + 2.0*x[3]*x[4] - 2.0*x[4]*x[7] + 2.0*x[4]*x[8] - 2.0*x[4];
        p[9]           = x[8];
}

    
/**
    Endmember fraction of ilm
*/
void px_alk_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[2];
        p[1]           =-x[0]*x[1] + x[0] - x[2];
        p[2]           = 1.0 - x[0];
        p[3]           =-x[2] + x[3];
        p[4]           = x[0]*x[1] + x[2] - x[3];
}

    
/**
    Endmember fraction of ness
*/
void px_alk_ness(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 0.25*x[0]*x[1] - x[0] + 0.75*x[1]*x[4] - x[1] - 0.75*x[2] - x[3] + 1.0;
        p[1]           = x[0] - 3.0*x[4];
        p[2]           = -0.25*x[0]*x[1] - 0.75*x[1]*x[4] + x[1] - 0.25*x[2];
        p[3]           = x[2];
        p[4]           = 3.0*x[4];
        p[5]           = x[3];
}

    
/**
    Endmember fraction of lct
*/
void px_alk_lct(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0];
        p[1]           = 1.0 - x[0];
}

    
/**
    Endmember fraction of kals
*/
void px_alk_kals(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 - x[0];
        p[1]           = x[0];
}

    
/**
    Endmember fraction of mel
*/
void px_alk_mel(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -2.0*x[1] + x[2];
        p[1]           = x[0]*x[2] + x[0]*x[3] - x[0] - x[2] - x[3] + 1.0;
        p[2]           =-x[0]*x[2] - x[0]*x[3] + x[0];
        p[3]           = 2.0*x[1];
        p[4]           = x[3];
}

    
/**
    Endmember fraction of hb
*/
void px_alk_hb(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           =-x[1] + x[2] - 0.5*x[3] + x[5] - x[6] - x[7];
        p[1]           = x[1] - x[2] - 0.5*x[3] + x[6];
        p[2]           =-x[3]*x[4] + x[3];
        p[3]           = x[2] - x[6];
        p[4]           = x[0]*x[2] + x[0]*x[5] - x[0] + x[1]*x[9] - x[2] - x[5] + x[6]*x[9] + x[7]*x[9] - 1.5*x[8] - x[9] + 1.0;
        p[5]           =-x[0]*x[1] + x[0]*x[2] + x[0]*x[5] - x[0]*x[6] - x[0]*x[7] + x[0] + 2.0*x[1]*x[9] + 2.0*x[6]*x[9] + 2.0*x[7]*x[9] - 2.5*x[8] - 2.0*x[9];
        p[6]           =-x[0]*x[2] - x[0]*x[5] - x[1]*x[9] - x[6]*x[9] - x[7]*x[9] + 2.5*x[8] + x[9];
        p[7]           = x[0]*x[1] - x[0]*x[2] - x[0]*x[5] + x[0]*x[6] + x[0]*x[7] - 2.0*x[1]*x[9] - 2.0*x[6]*x[9] - 2.0*x[7]*x[9] + 1.5*x[8] + 2.0*x[9];
        p[8]           = x[6];
        p[9]           = x[3]*x[4];
        p[10]           = x[7];
}

    
/**
    Endmember fraction of bi
*/
void px_alk_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - x[0] - x[1] - x[2] - x[3] - 2.0/3.0*x[4] + 1.0;
        p[1]           = x[0] - 1.0/3.0*x[4];
        p[2]           =-x[0]*x[1] - x[0]*x[2] - x[0]*x[3] + x[4];
        p[3]           = x[1];
        p[4]           = x[3];
        p[5]           = x[2];
}

    
/**
    Endmember fraction of ep
*/
void px_alk_ep(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           =-x[0] - x[1] + 1.0;
        p[1]           = 2.0*x[1];
        p[2]           = x[0] - x[1];
}

    
/**
    Endmember fraction of cd
*/
void px_alk_cd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           =-x[0] - x[1] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}

    
/**
    Objective function of liq
*/
double obj_alk_liq(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_liq(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -x[0] + x[10]*(-1.0*x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0) + 1.0/6.0*x[11]*(-7.0*x[0] - 7.0*x[1] - 7.0*x[2] - 7.0*x[3] - 7.0*x[4] - 7.0*x[5] - 7.0*x[6] - 7.0*x[7] - 7.0*x[8] - 7.0*x[9] + 3.0) + 1.0/6.0*x[12]*(x[0] + x[1] + x[2] + x[3] + x[4] + x[5] + x[6] + x[7] + x[8] + x[9] - 3.0) + 1.0/6.0*x[13]*(-7.0*x[0] - 7.0*x[1] - 7.0*x[2] - 7.0*x[3] - 7.0*x[4] - 7.0*x[5] - 7.0*x[6] - 7.0*x[7] - 7.0*x[8] - 7.0*x[9] + 3.0) - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0;
    sf[1]          = x[10]*x[1] - x[10] + 7.0/6.0*x[11]*x[1] - 0.5*x[11] - 1.0/6.0*x[12]*x[1] + 7.0/6.0*x[13]*x[1] - 0.5*x[13] + x[1];
    sf[2]          = x[0]*x[10] + 7.0/6.0*x[0]*x[11] - 1.0/6.0*x[0]*x[12] + 7.0/6.0*x[0]*x[13] + x[0] - x[10];
    sf[3]          = x[10]*x[4] + 7.0/6.0*x[11]*x[4] - x[11] - 1.0/6.0*x[12]*x[4] + 7.0/6.0*x[13]*x[4] + x[4];
    sf[4]          = x[10]*x[5] + 7.0/6.0*x[11]*x[5] - 1.0/6.0*x[12]*x[5] + 7.0/6.0*x[13]*x[5] + x[5];
    sf[5]          = x[10]*x[6] + 7.0/6.0*x[11]*x[6] - 1.0/6.0*x[12]*x[6] + 7.0/6.0*x[13]*x[6] + x[6];
    sf[6]          = x[10]*x[7] + 7.0/6.0*x[11]*x[7] - 1.0/6.0*x[12]*x[7] + 7.0/6.0*x[13]*x[7] + x[7];
    sf[7]          = x[10]*x[8] + 7.0/6.0*x[11]*x[8] - 1.0/6.0*x[12]*x[8] + 7.0/6.0*x[13]*x[8] - x[13] + x[8];
    sf[8]          = x[11];
    sf[9]          = x[10];
    sf[10]          = x[12];
    sf[11]          = x[13];
    sf[12]          = x[10]*(x[2] + x[3]) + 7.0/6.0*x[11]*(x[2] + x[3]) - 1.0/6.0*x[12]*(x[2] + x[3]) - 0.5*x[12] + 7.0/6.0*x[13]*(x[2] + x[3]) + x[2] + x[3];
    sf[13]          = -x[10]*x[9] - 7.0/6.0*x[11]*x[9] + 1.0/6.0*x[12]*x[9] - 7.0/6.0*x[13]*x[9] - x[9] + 1.0;
    sf[14]          = x[10]*x[9] + 7.0/6.0*x[11]*x[9] - 1.0/6.0*x[12]*x[9] + 7.0/6.0*x[13]*x[9] + x[9];
    sf[15]          = -x[10]*x[9] - 7.0/6.0*x[11]*x[9] + 1.0/6.0*x[12]*x[9] - 7.0/6.0*x[13]*x[9] - x[9] + 1.0;
    sf[16]          = -2.0*x[12] + 4.0*x[2]*(x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0);
    sf[17]          = 4.0*x[3]*(x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0);
    sf[18]          = x[0]*(x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0) - x[10];
    sf[19]          = -x[10] - 0.5*x[11] - 0.5*x[13] + x[1]*(x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0);
    sf[20]          = -2.0*x[10] - 0.5*x[11] - 2.0*x[12] - 0.5*x[13] + (x[0] + x[1] + 4.0*x[2] + 4.0*x[3])*(x[10] + 7.0/6.0*x[11] - 1.0/6.0*x[12] + 7.0/6.0*x[13] + 1.0);
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*1.0/sf[13]*cpow(sf[15], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(1.0/sf[13]*cpow(sf[15], 2.0)*sf[19]*sf[1]*1.0/sf[20])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(1.0/sf[13]*cpow(sf[15], 2.0)*sf[18]*1.0/sf[20]*sf[2])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[12]*1.0/sf[13]*cpow(sf[15], 2.0)*cpow(sf[16], 4.0)*cpow(sf[20], -4.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[12]*1.0/sf[13]*cpow(sf[15], 2.0)*cpow(sf[17], 4.0)*cpow(sf[20], -4.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(1.0/sf[13]*cpow(sf[15], 2.0)*sf[3])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(1.0/sf[13]*cpow(sf[15], 2.0)*sf[4] + d_em[6])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(1.0/sf[13]*cpow(sf[15], 2.0)*sf[5] + d_em[7])) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(1.0/sf[13]*cpow(sf[15], 2.0)*sf[6])) + mu_Gex[8];
    mu[9]          = gb[9] + R*T*creal(clog(1.0/sf[13]*cpow(sf[15], 2.0)*sf[7])) + mu_Gex[9];
    mu[10]          = gb[10] + R*T*creal(clog(1.0/sf[13]*cpow(sf[15], 2.0)*sf[9])) + mu_Gex[10];
    mu[11]          = gb[11] + R*T*creal(clog(1.0/sf[13]*cpow(sf[15], 2.0)*sf[8])) + mu_Gex[11];
    mu[12]          = gb[12] + R*T*creal(clog(sf[10]*1.0/sf[13]*cpow(sf[15], 2.0))) + mu_Gex[12];
    mu[13]          = gb[13] + R*T*creal(clog(sf[11]*1.0/sf[13]*cpow(sf[15], 2.0))) + mu_Gex[13];
    mu[14]          = gb[14] + R*T*creal(clog(cpow(sf[14], 2.0) + d_em[14])) + mu_Gex[14];

    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_liq(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of fl
*/
double obj_alk_fl(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_alk_fl(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = -x[0] - x[1] - x[2] + 1.0;
    sf[1]          = x[0];
    sf[2]          = x[1];
    sf[3]          = x[2];
    sf[4]          = 1.0 - x[2];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[4])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[4])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[2]*sf[4])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[3], 2.0))) + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_fl(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of fsp
*/
double obj_alk_fsp(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_alk_fsp(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -x[0] - x[1] + 1.0;
    sf[1]          = x[0];
    sf[2]          = x[1];
    sf[3]          = 0.25*x[0] + 0.25;
    sf[4]          = 0.75 - 0.25*x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(1.7548*sf[0]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[1]*csqrt(sf[3])*csqrt(sf[4]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(1.7548*sf[2]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_fsp(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of spn
*/
double obj_alk_spn(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_spn(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -1.0/3.0*x[0]*x[3] - 1.0/3.0*x[0] + 1.0/3.0*x[3] + 2.0/3.0*x[4] + 1.0/3.0;
    sf[1]          = 1.0/3.0*x[0]*x[3] + 1.0/3.0*x[0] + 2.0/3.0*x[5];
    sf[2]          = 2.0/3.0*x[1]*x[2] + 2.0/3.0*x[1]*x[3] - 2.0/3.0*x[1] - 1.0/3.0*x[3] - 2.0/3.0*x[4] - 2.0/3.0*x[5] - 2.0/3.0*x[6] + 2.0/3.0;
    sf[3]          = -2.0/3.0*x[1]*x[2] - 2.0/3.0*x[1]*x[3] + 2.0/3.0*x[1] + 2.0/3.0*x[6];
    sf[4]          = -1.0/3.0*x[0]*x[3] - 1.0/3.0*x[0] + 1.0/3.0*x[3] - 1.0/3.0*x[4] + 1.0/3.0;
    sf[5]          = 1.0/3.0*x[0]*x[3] + 1.0/3.0*x[0] - 1.0/3.0*x[5];
    sf[6]          = 2.0/3.0*x[1]*x[2] + 2.0/3.0*x[1]*x[3] - 2.0/3.0*x[1] - x[2] - 5.0/6.0*x[3] + 1.0/3.0*x[4] + 1.0/3.0*x[5] + 1.0/3.0*x[6] + 2.0/3.0;
    sf[7]          = -2.0/3.0*x[1]*x[2] - 2.0/3.0*x[1]*x[3] + 2.0/3.0*x[1] - 1.0/3.0*x[6];
    sf[8]          = x[2];
    sf[9]          = 0.5*x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[6])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[2]*csqrt(sf[4])*csqrt(sf[6]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[1]*sf[6])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(2.0*sf[2]*csqrt(sf[5])*csqrt(sf[6]))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[1]*sf[7] + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(2.0*sf[3]*csqrt(sf[5])*csqrt(sf[7]) + d_em[5])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(sf[0]*sf[8] + d_em[6])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(2.0*sf[1]*csqrt(sf[5])*csqrt(sf[9]))) + mu_Gex[7];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_spn(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of g
*/
double obj_alk_g(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_g(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[1]          = -x[0]*x[1] + x[0];
    sf[2]          = x[1];
    sf[3]          = -x[2] - x[3] - 2.0*x[4] + 1.0;
    sf[4]          = x[3];
    sf[5]          = x[2];
    sf[6]          = x[4];
    sf[7]          = x[4];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[1], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[2], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[2], 3.0)*cpow(sf[5], 2.0) + d_em[3])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(cpow(sf[0], 3.0)*cpow(sf[4], 2.0) + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(8.0*cpow(sf[0], 3.0)*sf[3]*csqrt(sf[6])*csqrt(sf[7]))) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_g(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ol
*/
double obj_alk_ol(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_alk_ol(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = -x[0] + x[2] + 1.0;
    sf[1]          = x[0] - x[2];
    sf[2]          = x[0]*x[1] - x[0] - x[1] - x[2] + 1.0;
    sf[3]          = -x[0]*x[1] + x[0] + x[2];
    sf[4]          = x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[4])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[3])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[2])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*sf[3])) + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_ol(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of opx
*/
double obj_alk_opx(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_opx(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0]*x[1] - x[0]*x[5] + x[0]*x[7] - x[0] + x[1]*x[3] - x[1] - x[3]*x[5] + x[3]*x[7] - x[3] + x[5] - x[7] + 1.0;
    sf[1]          = -x[0]*x[1] + x[0]*x[5] - x[0]*x[7] + x[0] - x[1]*x[3] + x[3]*x[5] - x[3]*x[7] + x[3];
    sf[2]          = x[1] - x[4] - 2.0*x[5] - x[6] + x[7];
    sf[3]          = x[4];
    sf[4]          = x[6];
    sf[5]          = x[5];
    sf[6]          = x[0]*x[2] + x[0]*x[7] - x[0] - x[1]*x[3] - x[2] + x[3]*x[5] - x[3]*x[7] + x[3] - x[7] + 1.0;
    sf[7]          = -x[0]*x[2] - x[0]*x[7] + x[0] + x[1]*x[3] - x[3]*x[5] + x[3]*x[7] - x[3];
    sf[8]          = x[2];
    sf[9]          = x[7];
    sf[10]          = 1.0 - 0.5*x[1];
    sf[11]          = 0.5*x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*csqrt(sf[10])*sf[6])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(csqrt(sf[10])*sf[1]*sf[7])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*csqrt(sf[10])*sf[7])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*csqrt(sf[10])*sf[8])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(1.4142*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*sf[2]*sf[6])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(1.4142*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*sf[4]*sf[6] + d_em[5])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(2.8284*csqrt(sf[0])*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*csqrt(sf[5])*sf[6])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(1.4142*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*sf[3]*sf[6] + d_em[7])) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(csqrt(sf[10])*sf[2]*sf[9])) + mu_Gex[8];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_opx(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of cpx
*/
double obj_alk_cpx(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_cpx(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0]*x[1] + x[0]*x[3] - x[0]*x[7] + x[0]*x[8] - x[0] + x[1]*x[4] - x[1] + x[3]*x[4] - x[3] - x[4]*x[7] + x[4]*x[8] - x[4] + x[7] - x[8] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[3] + x[0]*x[7] - x[0]*x[8] + x[0] - x[1]*x[4] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
    sf[2]          = x[1] + x[3] - x[5] - x[6] - 2.0*x[7] + x[8];
    sf[3]          = x[5];
    sf[4]          = x[6];
    sf[5]          = x[7];
    sf[6]          = -x[0]*x[2] - x[1]*x[4] + x[2] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
    sf[7]          = x[0]*x[2] + x[1]*x[4] + x[3]*x[4] - x[4]*x[7] + x[4]*x[8] - x[4];
    sf[8]          = -x[2] - x[3] - x[8] + 1.0;
    sf[9]          = x[3];
    sf[10]          = x[8];
    sf[11]          = 1.0 - 0.5*x[1];
    sf[12]          = 0.5*x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*csqrt(sf[11])*sf[8])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(csqrt(sf[11])*sf[1]*sf[7])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(1.4142*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*sf[2]*sf[8])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(1.4142*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*sf[4]*sf[8] + d_em[3])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(1.4142*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*sf[3]*sf[8] + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(2.8284*csqrt(sf[0])*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*csqrt(sf[5])*sf[8])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(csqrt(sf[11])*sf[2]*sf[9])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(sf[0]*csqrt(sf[11])*sf[6])) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(sf[0]*csqrt(sf[11])*sf[7])) + mu_Gex[8];
    mu[9]          = gb[9] + R*T*creal(clog(sf[10]*csqrt(sf[11])*sf[2])) + mu_Gex[9];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_cpx(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ilm
*/
double obj_alk_ilm(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_ilm(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = -0.5*x[0]*x[1] + 0.5*x[0] + 0.5*x[2];
    sf[1]          = 0.5*x[0] - 0.5*x[3];
    sf[2]          = 1.0 - x[0];
    sf[3]          = 0.5*x[0]*x[1] - 0.5*x[2] + 0.5*x[3];
    sf[4]          = -0.5*x[0]*x[1] + 0.5*x[0] - 0.5*x[2];
    sf[5]          = 0.5*x[0] + 0.5*x[3];
    sf[6]          = 1.0 - x[0];
    sf[7]          = 0.5*x[0]*x[1] + 0.5*x[2] - 0.5*x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(csqrt(sf[0])*csqrt(sf[5]))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*cpow(sf[0], 0.25)*cpow(sf[1], 0.25)*cpow(sf[4], 0.25)*cpow(sf[5], 0.25))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(csqrt(sf[2])*csqrt(sf[6]) + d_em[2])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(csqrt(sf[3])*csqrt(sf[5]))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(2.0*cpow(sf[1], 0.25)*cpow(sf[3], 0.25)*cpow(sf[5], 0.25)*cpow(sf[7], 0.25))) + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_ilm(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ness
*/
double obj_alk_ness(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_ness(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = 0.25*x[0]*x[1] + 0.75*x[1]*x[4] - x[1] + 0.25*x[2] - x[4] + 1.0;
    sf[1]          = -0.25*x[0]*x[1] - 0.75*x[1]*x[4] + x[1] - 0.25*x[2];
    sf[2]          = x[4];
    sf[3]          = 0.25*x[0]*x[1] - x[0] + 0.75*x[1]*x[4] - x[1] - 0.75*x[2] + 1.0;
    sf[4]          = -0.25*x[0]*x[1] - 0.75*x[1]*x[4] + x[1] + 0.75*x[2];
    sf[5]          = x[0];
    sf[6]          = -0.25*x[0] - x[3] + 0.75*x[4] + 1.0;
    sf[7]          = 0.25*x[0] - 0.75*x[4];
    sf[8]          = x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 3.0)*sf[3]*cpow(sf[6], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(3.0792*cpow(sf[0], 3.0)*sf[5]*cpow(sf[6], 1.5)*csqrt(sf[7]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[1], 3.0)*sf[4]*cpow(sf[6], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[0], 3.0)*sf[4]*cpow(sf[6], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(6.75*cpow(sf[0], 2.0)*sf[2]*sf[5]*cpow(sf[6], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(cpow(sf[0], 3.0)*sf[3]*cpow(sf[8], 2.0) + d_em[5])) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_ness(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of lct
*/
double obj_alk_lct(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_alk_lct(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0];
    sf[1]          = 1.0 - x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1])) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_lct(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of kals
*/
double obj_alk_kals(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_alk_kals(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0];
    sf[1]          = 1.0 - x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[1])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0])) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_kals(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of mel
*/
double obj_alk_mel(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_mel(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[1];
    sf[1]          = 1.0 - x[1];
    sf[2]          = x[0]*x[2] + x[0]*x[3] - x[0] - x[2] - x[3] + 1.0;
    sf[3]          = -x[0]*x[2] - x[0]*x[3] + x[0];
    sf[4]          = x[2];
    sf[5]          = x[3];
    sf[6]          = -x[1] + 0.5*x[2] + 0.5*x[3];
    sf[7]          = x[1] - 0.5*x[2] - 0.5*x[3] + 1.0;
    
    
    mu[0]          = gb[0] + R*T*creal(clog(2.0*cpow(sf[1], 2.0)*sf[4]*csqrt(sf[6])*csqrt(sf[7]))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[1], 2.0)*sf[2]*sf[7])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[1], 2.0)*sf[3]*sf[7])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(4.0*sf[0]*sf[1]*sf[4]*sf[7])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(2.0*cpow(sf[1], 2.0)*sf[5]*csqrt(sf[6])*csqrt(sf[7]) + d_em[4])) + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_mel(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of hb
*/
double obj_alk_hb(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_hb(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = 1.0 - x[3];
    sf[1]          = -x[3]*x[4] + x[3];
    sf[2]          = x[3]*x[4];
    sf[3]          = -x[0] + x[8] + 1.0;
    sf[4]          = x[0] - x[8];
    sf[5]          = x[0]*x[1] + x[0]*x[6] + x[0]*x[7] - x[0] - x[1]*x[9] - x[1] - x[6]*x[9] - x[6] - x[7]*x[9] - x[7] + x[9] + 1.0;
    sf[6]          = -x[0]*x[1] - x[0]*x[6] - x[0]*x[7] + x[0] + x[1]*x[9] + x[6]*x[9] + x[7]*x[9] - x[9];
    sf[7]          = x[1];
    sf[8]          = x[6];
    sf[9]          = x[7];
    sf[10]          = x[5];
    sf[11]          = x[0]*x[2] + x[0]*x[5] - x[0] + x[1]*x[9] - x[2] - x[5] + x[6]*x[9] + x[7]*x[9] - 1.5*x[8] - x[9] + 1.0;
    sf[12]          = -x[0]*x[2] - x[0]*x[5] + x[0] - x[1]*x[9] - x[6]*x[9] - x[7]*x[9] + 1.5*x[8] + x[9];
    sf[13]          = x[2];
    sf[14]          = -0.5*x[1] + 0.5*x[2] - 0.25*x[3] - 0.5*x[6] - 0.5*x[7] + 1.0;
    sf[15]          = 0.5*x[1] - 0.5*x[2] + 0.25*x[3] + 0.5*x[6] + 0.5*x[7];
    sf[16]          = 1.0 - x[7];
    sf[17]          = x[7];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*cpow(sf[10], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[0]*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[7], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(8.0*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*sf[1]*cpow(sf[3], 3.0)*sf[5]*sf[7])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*cpow(sf[13], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[7], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[0]*cpow(sf[11], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[4], 3.0)*cpow(sf[6], 2.0))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[6], 2.0))) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[4], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(sf[0]*cpow(sf[13], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[8], 2.0) + d_em[8])) + mu_Gex[8];
    mu[9]          = gb[9] + R*T*creal(clog(8.0*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*sf[2]*cpow(sf[3], 3.0)*sf[5]*sf[7])) + mu_Gex[9];
    mu[10]          = gb[10] + R*T*creal(clog(2.0*sf[0]*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[17], 2.0)*cpow(sf[3], 3.0)*cpow(sf[9], 2.0))) + mu_Gex[10];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_hb(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of bi
*/
double obj_alk_bi(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_bi(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - x[0] - x[1] - x[2] - x[3] - 2.0/3.0*x[4] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[2] - x[0]*x[3] + x[0] + 2.0/3.0*x[4];
    sf[2]          = x[2];
    sf[3]          = x[3];
    sf[4]          = x[1];
    sf[5]          = -x[0] + 1.0/3.0*x[4] + 1.0;
    sf[6]          = x[0] - 1.0/3.0*x[4];
    sf[7]          = -0.5*x[1] - 0.5*x[2] + 0.5;
    sf[8]          = 0.5*x[1] + 0.5*x[2] + 0.5;
    sf[9]          = 1.0 - x[3];
    sf[10]          = x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(4.0*sf[0]*cpow(sf[5], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(4.0*sf[1]*cpow(sf[6], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(4.0*sf[1]*cpow(sf[5], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[4]*cpow(sf[5], 2.0)*cpow(sf[8], 2.0)*cpow(sf[9], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(4.0*cpow(sf[10], 2.0)*sf[3]*cpow(sf[5], 2.0)*sf[7]*sf[8])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[2]*cpow(sf[5], 2.0)*cpow(sf[8], 2.0)*cpow(sf[9], 2.0) + d_em[5])) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_bi(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ep
*/
double obj_alk_ep(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_ep(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0] - x[1];
    sf[1]          = -x[0] + x[1] + 1.0;
    sf[2]          = x[0] + x[1];
    sf[3]          = -x[0] - x[1] + 1.0;
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[1]*sf[3])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[2] + d_em[1])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[2] + d_em[2])) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_ep(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of cd
*/
double obj_alk_cd(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_alk_cd(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0];
    sf[1]          = 1.0 - x[0];
    sf[2]          = x[1];
    sf[3]          = 1.0 - x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[1], 2.0)*sf[3])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[0], 2.0)*sf[3])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[1], 2.0)*sf[2])) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_cd(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

/**************************************************************************************/
/**************************************************************************************/
/*********************IGNEOUS DRY DATABASE (Green et al., 2023)************************/
/**************************************************************************************/
/**************************************************************************************/
/**
    Update dpdx matrix of fper_S11
*/
void dpdx_igd_fper(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      
    dp_dx[1][0] = 1.0;      
}

/**
    Update dpdx matrix of liq
*/
void dpdx_igd_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][1] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][2] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][3] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][4] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][5] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][6] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][7] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][8] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][9] = - x[10] - 2./3.*x[11] + 1./6.*x[12] - 1./3.*x[13] - 1.0;      dp_dx[0][10] = - x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0;      dp_dx[0][11] = -2./3.*x[0] - 2./3.*x[1] - 2./3.*x[2] - 2./3.*x[3] - 2./3.*x[4] - 2./3.*x[5] - 2./3.*x[6] - 2./3.*x[7] - 2./3.*x[8] - 2./3.*x[9];      dp_dx[0][12] = 1./6.*x[0] + 1./6.*x[1] + 1./6.*x[2] + 1./6.*x[3] + 1./6.*x[4] + 1./6.*x[5] + 1./6.*x[6] + 1./6.*x[7] + 1./6.*x[8] + 1./6.*x[9] - 0.5;      dp_dx[0][13] = -1./3.*x[0] - 1./3.*x[1] - 1./3.*x[2] - 1./3.*x[3] - 1./3.*x[4] - 1./3.*x[5] - 1./3.*x[6] - 1./3.*x[7] - 1./3.*x[8] - 1./3.*x[9];      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      dp_dx[1][7] = 0.0;      dp_dx[1][8] = 0.0;      dp_dx[1][9] = 0.0;      dp_dx[1][10] = x[1] - 1.0;      dp_dx[1][11] = 2./3.*x[1];      dp_dx[1][12] = -1./6.*x[1];      dp_dx[1][13] = 1./3.*x[1];      
    dp_dx[2][0] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 0.0;      dp_dx[2][8] = 0.0;      dp_dx[2][9] = 0.0;      dp_dx[2][10] = x[0] - 1.0;      dp_dx[2][11] = 2./3.*x[0];      dp_dx[2][12] = -1./6.*x[0];      dp_dx[2][13] = 1./3.*x[0];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      dp_dx[3][9] = 0.0;      dp_dx[3][10] = x[2];      dp_dx[3][11] = 2./3.*x[2];      dp_dx[3][12] = -1./6.*x[2] - 0.5;      dp_dx[3][13] = 1./3.*x[2];      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = 0.0;      dp_dx[4][7] = 0.0;      dp_dx[4][8] = 0.0;      dp_dx[4][9] = 0.0;      dp_dx[4][10] = x[3];      dp_dx[4][11] = 2./3.*x[3];      dp_dx[4][12] = -1./6.*x[3];      dp_dx[4][13] = 1./3.*x[3];      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 0.0;      dp_dx[5][7] = 0.0;      dp_dx[5][8] = 0.0;      dp_dx[5][9] = 0.0;      dp_dx[5][10] = x[4];      dp_dx[5][11] = 2./3.*x[4] - 1.0;      dp_dx[5][12] = -1./6.*x[4];      dp_dx[5][13] = 1./3.*x[4];      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      dp_dx[6][8] = 0.0;      dp_dx[6][9] = 0.0;      dp_dx[6][10] = x[5];      dp_dx[6][11] = 2./3.*x[5];      dp_dx[6][12] = -1./6.*x[5];      dp_dx[6][13] = 1./3.*x[5];      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[7][7] = 0.0;      dp_dx[7][8] = 0.0;      dp_dx[7][9] = 0.0;      dp_dx[7][10] = x[6];      dp_dx[7][11] = 2./3.*x[6];      dp_dx[7][12] = -1./6.*x[6];      dp_dx[7][13] = 1./3.*x[6];      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[8][8] = 0.0;      dp_dx[8][9] = 0.0;      dp_dx[8][10] = x[7];      dp_dx[8][11] = 2./3.*x[7];      dp_dx[8][12] = -1./6.*x[7];      dp_dx[8][13] = 1./3.*x[7];      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = 0.0;      dp_dx[9][4] = 0.0;      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[9][9] = 0.0;      dp_dx[9][10] = x[8];      dp_dx[9][11] = 2./3.*x[8];      dp_dx[9][12] = -1./6.*x[8];      dp_dx[9][13] = 1./3.*x[8] - 1.0;      
    dp_dx[10][0] = 0.0;      dp_dx[10][1] = 0.0;      dp_dx[10][2] = 0.0;      dp_dx[10][3] = 0.0;      dp_dx[10][4] = 0.0;      dp_dx[10][5] = 0.0;      dp_dx[10][6] = 0.0;      dp_dx[10][7] = 0.0;      dp_dx[10][8] = 0.0;      dp_dx[10][9] = 0.0;      dp_dx[10][10] = 1.0;      dp_dx[10][11] = 0.0;      dp_dx[10][12] = 0.0;      dp_dx[10][13] = 0.0;      
    dp_dx[11][0] = 0.0;      dp_dx[11][1] = 0.0;      dp_dx[11][2] = 0.0;      dp_dx[11][3] = 0.0;      dp_dx[11][4] = 0.0;      dp_dx[11][5] = 0.0;      dp_dx[11][6] = 0.0;      dp_dx[11][7] = 0.0;      dp_dx[11][8] = 0.0;      dp_dx[11][9] = 0.0;      dp_dx[11][10] = 0.0;      dp_dx[11][11] = 1.0;      dp_dx[11][12] = 0.0;      dp_dx[11][13] = 0.0;      
    dp_dx[12][0] = 0.0;      dp_dx[12][1] = 0.0;      dp_dx[12][2] = 0.0;      dp_dx[12][3] = 0.0;      dp_dx[12][4] = 0.0;      dp_dx[12][5] = 0.0;      dp_dx[12][6] = 0.0;      dp_dx[12][7] = 0.0;      dp_dx[12][8] = 0.0;      dp_dx[12][9] = 0.0;      dp_dx[12][10] = 0.0;      dp_dx[12][11] = 0.0;      dp_dx[12][12] = 1.0;      dp_dx[12][13] = 0.0;      
    dp_dx[13][0] = 0.0;      dp_dx[13][1] = 0.0;      dp_dx[13][2] = 0.0;      dp_dx[13][3] = 0.0;      dp_dx[13][4] = 0.0;      dp_dx[13][5] = 0.0;      dp_dx[13][6] = 0.0;      dp_dx[13][7] = 0.0;      dp_dx[13][8] = 0.0;      dp_dx[13][9] = 0.0;      dp_dx[13][10] = 0.0;      dp_dx[13][11] = 0.0;      dp_dx[13][12] = 0.0;      dp_dx[13][13] = 1.0;      
    dp_dx[14][0] = 0.0;      dp_dx[14][1] = 0.0;      dp_dx[14][2] = 0.0;      dp_dx[14][3] = 0.0;      dp_dx[14][4] = 0.0;      dp_dx[14][5] = 0.0;      dp_dx[14][6] = 0.0;      dp_dx[14][7] = 0.0;      dp_dx[14][8] = 0.0;      dp_dx[14][9] = x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0;      dp_dx[14][10] = x[9];      dp_dx[14][11] = 2./3.*x[9];      dp_dx[14][12] = -1./6.*x[9];      dp_dx[14][13] = 1./3.*x[9];      
}


/**
    Update dpdx matrix of fl
*/
void dpdx_igd_fl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      dp_dx[0][2] = -1.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      
}


/**
    Update dpdx matrix of fsp
*/
void dpdx_igd_fsp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      
}


/**
    Update dpdx matrix of spn
*/
void dpdx_igd_spn(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1./3.*x[3] - 1./3.;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = 1./3. - 1./3.*x[0];      dp_dx[0][4] = 2./3.;      dp_dx[0][5] = 0.0;      dp_dx[0][6] = 0.0;      
    dp_dx[1][0] = -2./3.*x[3] - 2./3.;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 2./3. - 2./3.*x[0];      dp_dx[1][4] = -2./3.;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      
    dp_dx[2][0] = 1./3.*x[3] + 1./3.;      dp_dx[2][1] = 1./3.*x[2] + 1./3.*x[3] - 1./3.;      dp_dx[2][2] = 1./3.*x[1];      dp_dx[2][3] = 1./3.*x[0] + 1./3.*x[1] - 1.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 2./3.;      dp_dx[2][6] = 2./3.;      
    dp_dx[3][0] = 2./3.*x[3] + 2./3.;      dp_dx[3][1] = 2./3.*x[2] + 2./3.*x[3] - 2./3.;      dp_dx[3][2] = 2./3.*x[1];      dp_dx[3][3] = 2./3.*x[0] + 2./3.*x[1] - 1.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = -2./3.;      dp_dx[3][6] = -2./3.;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = -1./3.*x[2] - 1./3.*x[3] + 1./3.;      dp_dx[4][2] = -1./3.*x[1];      dp_dx[4][3] = -1./3.*x[1];      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = -2./3.;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = -2./3.*x[2] - 2./3.*x[3] + 2./3.;      dp_dx[5][2] = -2./3.*x[1];      dp_dx[5][3] = -2./3.*x[1];      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 2./3.;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 1.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      dp_dx[6][6] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 1.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      
}


/**
    Update dpdx matrix of g
*/
void dpdx_igd_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = 0.0;      dp_dx[0][3] = -1.0;      dp_dx[0][4] = -4.0;      
    dp_dx[1][0] = 1.0 - x[1];      dp_dx[1][1] = - x[0];      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = -1.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.0;      dp_dx[4][4] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 4.0;      
}


/**
    Update dpdx matrix of ol
*/
void dpdx_igd_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.0;      dp_dx[0][2] = 0.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = -1.0;      
    dp_dx[2][0] = x[1] - 1.0;      dp_dx[2][1] = x[0] - 1.0;      dp_dx[2][2] = -1.0;      
    dp_dx[3][0] = - x[1];      dp_dx[3][1] = - x[0];      dp_dx[3][2] = 2.0;      
}


/**
    Update dpdx matrix of opx
*/
void dpdx_igd_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[2] + x[7] - 1.0;      dp_dx[0][1] = - x[3] - 1.0;      dp_dx[0][2] = x[0] - 1.0;      dp_dx[0][3] = - x[1] + x[5] - x[7] + 1.0;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = x[3];      dp_dx[0][6] = 0.0;      dp_dx[0][7] = x[0] - x[3] - 1.0;      
    dp_dx[1][0] = - x[1] + x[5] - x[7] + 1.0;      dp_dx[1][1] = - x[0] - x[3];      dp_dx[1][2] = 0.0;      dp_dx[1][3] = - x[1] + x[5] - x[7] + 1.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = x[0] + x[3];      dp_dx[1][6] = 0.0;      dp_dx[1][7] = - x[0] - x[3];      
    dp_dx[2][0] = x[1] - x[2] - x[5];      dp_dx[2][1] = x[0] + 2.0*x[3];      dp_dx[2][2] = - x[0];      dp_dx[2][3] = 2.0*x[1] - 2.0*x[5] + 2.0*x[7] - 2.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = - x[0] - 2.0*x[3];      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 2.0*x[3];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      dp_dx[3][7] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 1.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = -1.0;      dp_dx[4][5] = -2.0;      dp_dx[4][6] = -1.0;      dp_dx[4][7] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 1.0;      dp_dx[5][7] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 2.0;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 1.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      dp_dx[7][7] = 0.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = 1.0;      
}


/**
    Update dpdx matrix of cpx
*/
void dpdx_igd_cpx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = -1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -1.0;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 0.0;      dp_dx[0][6] = 0.0;      dp_dx[0][7] = 0.0;      dp_dx[0][8] = -1.0;      
    dp_dx[1][0] = - x[1] - x[3] + x[7] - x[8] + 1.0;      dp_dx[1][1] = - x[0] - x[4];      dp_dx[1][2] = 0.0;      dp_dx[1][3] = - x[0] - x[4];      dp_dx[1][4] = - x[1] - x[3] + x[7] - x[8] + 1.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      dp_dx[1][7] = x[0] + x[4];      dp_dx[1][8] = - x[0] - x[4];      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = -1.0;      dp_dx[2][6] = -1.0;      dp_dx[2][7] = -2.0;      dp_dx[2][8] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 1.0;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 1.0;      dp_dx[4][6] = 0.0;      dp_dx[4][7] = 0.0;      dp_dx[4][8] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 0.0;      dp_dx[5][7] = 2.0;      dp_dx[5][8] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 1.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      dp_dx[6][8] = 0.0;      
    dp_dx[7][0] = - x[2];      dp_dx[7][1] = - x[4];      dp_dx[7][2] = 1.0 - x[0];      dp_dx[7][3] = - x[4];      dp_dx[7][4] = - x[1] - x[3] + x[7] - x[8] + 1.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      dp_dx[7][7] = x[4];      dp_dx[7][8] = - x[4];      
    dp_dx[8][0] = x[1] + x[2] + x[3] - x[7] + x[8] - 1.0;      dp_dx[8][1] = x[0] + 2.0*x[4];      dp_dx[8][2] = x[0];      dp_dx[8][3] = x[0] + 2.0*x[4];      dp_dx[8][4] = 2.0*x[1] + 2.0*x[3] - 2.0*x[7] + 2.0*x[8] - 2.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = - x[0] - 2.0*x[4];      dp_dx[8][8] = x[0] + 2.0*x[4];      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = 0.0;      dp_dx[9][4] = 0.0;      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = 1.0;      
}


/**
    Update dpdx matrix of ilm
*/
void dpdx_igd_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = 1.0;      dp_dx[0][3] = 0.0;      
    dp_dx[1][0] = 1.0 - x[1];      dp_dx[1][1] = - x[0];      dp_dx[1][2] = -1.0;      dp_dx[1][3] = 0.0;      
    dp_dx[2][0] = -1.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = -1.0;      dp_dx[3][3] = 1.0;      
    dp_dx[4][0] = x[1];      dp_dx[4][1] = x[0];      dp_dx[4][2] = 1.0;      dp_dx[4][3] = -1.0;      
}


/**
    Update dpdx matrix of hb
*/
void dpdx_igd_hb(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = -1.0;      dp_dx[0][2] = 1.0;      dp_dx[0][3] = -0.50;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 1.0;      dp_dx[0][6] = -1.0;      dp_dx[0][7] = -1.0;      dp_dx[0][8] = 0.0;      dp_dx[0][9] = 0.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 1.0;      dp_dx[1][2] = -1.0;      dp_dx[1][3] = -0.50;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 1.0;      dp_dx[1][7] = 0.0;      dp_dx[1][8] = 0.0;      dp_dx[1][9] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 1.0 - x[4];      dp_dx[2][4] = - x[3];      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 0.0;      dp_dx[2][8] = 0.0;      dp_dx[2][9] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = -1.0;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      dp_dx[3][9] = 0.0;      
    dp_dx[4][0] = x[2] + x[5] - 1.0;      dp_dx[4][1] = x[9];      dp_dx[4][2] = x[0] - 1.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = x[0] - 1.0;      dp_dx[4][6] = x[9];      dp_dx[4][7] = x[9];      dp_dx[4][8] = -1.5;      dp_dx[4][9] = x[1] + x[6] + x[7] - 1.0;      
    dp_dx[5][0] = - x[1] + x[2] + x[5] - x[6] - x[7] + 1.0;      dp_dx[5][1] = - x[0] + 2.0*x[9];      dp_dx[5][2] = x[0];      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = x[0];      dp_dx[5][6] = - x[0] + 2.0*x[9];      dp_dx[5][7] = - x[0] + 2.0*x[9];      dp_dx[5][8] = -2.5;      dp_dx[5][9] = 2.0*x[1] + 2.0*x[6] + 2.0*x[7] - 2.0;      
    dp_dx[6][0] = - x[2] - x[5];      dp_dx[6][1] = - x[9];      dp_dx[6][2] = - x[0];      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = - x[0];      dp_dx[6][6] = - x[9];      dp_dx[6][7] = - x[9];      dp_dx[6][8] = 2.5;      dp_dx[6][9] = - x[1] - x[6] - x[7] + 1.0;      
    dp_dx[7][0] = x[1] - x[2] - x[5] + x[6] + x[7];      dp_dx[7][1] = x[0] - 2.0*x[9];      dp_dx[7][2] = - x[0];      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = - x[0];      dp_dx[7][6] = x[0] - 2.0*x[9];      dp_dx[7][7] = x[0] - 2.0*x[9];      dp_dx[7][8] = 1.5;      dp_dx[7][9] = -2.0*x[1] - 2.0*x[6] - 2.0*x[7] + 2.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 1.0;      dp_dx[8][7] = 0.0;      dp_dx[8][8] = 0.0;      dp_dx[8][9] = 0.0;      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = x[4];      dp_dx[9][4] = x[3];      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = 0.0;      dp_dx[9][9] = 0.0;      
    dp_dx[10][0] = 0.0;      dp_dx[10][1] = 0.0;      dp_dx[10][2] = 0.0;      dp_dx[10][3] = 0.0;      dp_dx[10][4] = 0.0;      dp_dx[10][5] = 0.0;      dp_dx[10][6] = 0.0;      dp_dx[10][7] = 1.0;      dp_dx[10][8] = 0.0;      dp_dx[10][9] = 0.0;      
}


/**
    Update dpdx matrix of bi
*/
void dpdx_igd_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] + x[2] + x[3] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = x[0] - 1.0;      dp_dx[0][3] = x[0] - 1.0;      dp_dx[0][4] = -2./3.;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = -1./3.;      
    dp_dx[2][0] = - x[1] - x[2] - x[3];      dp_dx[2][1] = - x[0];      dp_dx[2][2] = - x[0];      dp_dx[2][3] = - x[0];      dp_dx[2][4] = 1.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.0;      dp_dx[4][4] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 1.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      
}


/**
    Update dpdx matrix of ep
*/
void dpdx_igd_ep(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 2.0;      
    dp_dx[2][0] = 1.0;      dp_dx[2][1] = -1.0;      
}


/**
    Update dpdx matrix of cd
*/
void dpdx_igd_cd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      
}


/**
    Endmember fraction of fper_S11
*/
void px_igd_fper(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 - 1.0*x[0];
        p[1]           = x[0];
}
   
/**
    Endmember fraction of liq
*/
void px_igd_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[0] + x[10]*(- x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0) + 2./3.*x[11]*(- x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9]) + 1./6.*x[12]*(x[0] + x[1] + x[2] + x[3] + x[4] + x[5] + x[6] + x[7] + x[8] + x[9] - 3.0) + 1./3.*x[13]*(- x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9]) - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0;
        p[1]           = x[10]*x[1] - x[10] + 2./3.*x[11]*x[1] - 1./6.*x[12]*x[1] + 1./3.*x[13]*x[1] + x[1];
        p[2]           = x[0]*x[10] + 2./3.*x[0]*x[11] - 1./6.*x[0]*x[12] + 1./3.*x[0]*x[13] + x[0] - x[10];
        p[3]           = x[10]*x[2] + 2./3.*x[11]*x[2] - 1./6.*x[12]*x[2] - 0.5*x[12] + 1./3.*x[13]*x[2] + x[2];
        p[4]           = x[10]*x[3] + 2./3.*x[11]*x[3] - 1./6.*x[12]*x[3] + 1./3.*x[13]*x[3] + x[3];
        p[5]           = x[10]*x[4] + 2./3.*x[11]*x[4] - x[11] - 1./6.*x[12]*x[4] + 1./3.*x[13]*x[4] + x[4];
        p[6]           = x[10]*x[5] + 2./3.*x[11]*x[5] - 1./6.*x[12]*x[5] + 1./3.*x[13]*x[5] + x[5];
        p[7]           = x[10]*x[6] + 2./3.*x[11]*x[6] - 1./6.*x[12]*x[6] + 1./3.*x[13]*x[6] + x[6];
        p[8]           = x[10]*x[7] + 2./3.*x[11]*x[7] - 1./6.*x[12]*x[7] + 1./3.*x[13]*x[7] + x[7];
        p[9]           = x[10]*x[8] + 2./3.*x[11]*x[8] - 1./6.*x[12]*x[8] + 1./3.*x[13]*x[8] - x[13] + x[8];
        p[10]          = x[10];
        p[11]          = x[11];
        p[12]          = x[12];
        p[13]          = x[13];
        p[14]          = x[10]*x[9] + 2./3.*x[11]*x[9] - 1./6.*x[12]*x[9] + 1./3.*x[13]*x[9] + x[9];
}

    
/**
    Endmember fraction of fl
*/
void px_igd_fl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[0] - x[1] - x[2] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
        p[3]           = x[2];
}

    
/**
    Endmember fraction of fsp
*/
void px_igd_fsp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[0] - x[1] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}

    
/**
    Endmember fraction of spn
*/
void px_igd_spn(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -1./3.*x[0]*x[3] - 1./3.*x[0] - x[2] + 1./3.*x[3] + 2./3.*x[4] + 1./3.;
        p[1]           = -2./3.*x[0]*x[3] - 2./3.*x[0] + 2./3.*x[3] - 2./3.*x[4] + 2./3.;
        p[2]           = 1./3.*x[0]*x[3] + 1./3.*x[0] + 1./3.*x[1]*x[2] + 1./3.*x[1]*x[3] - 1./3.*x[1] - x[3] + 2./3.*x[5] + 2./3.*x[6];
        p[3]           = 2./3.*x[0]*x[3] + 2./3.*x[0] + 2./3.*x[1]*x[2] + 2./3.*x[1]*x[3] - 2./3.*x[1] - x[3] - 2./3.*x[5] - 2./3.*x[6];
        p[4]           = -1./3.*x[1]*x[2] - 1./3.*x[1]*x[3] + 1./3.*x[1] - 2./3.*x[6];
        p[5]           = -2./3.*x[1]*x[2] - 2./3.*x[1]*x[3] + 2./3.*x[1] + 2./3.*x[6];
        p[6]           = x[2];
        p[7]           = x[3];
}

    
/**
    Endmember fraction of g
*/
void px_igd_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] - x[0] - x[1] - x[3] - 4.0*x[4] + 1.0;
        p[1]           = - x[0]*x[1] + x[0];
        p[2]           = x[1] - x[2];
        p[3]           = x[2];
        p[4]           = x[3];
        p[5]           = 4.0*x[4];
}

    
/**
    Endmember fraction of ol
*/
void px_igd_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1];
        p[1]           = x[0] - x[2];
        p[2]           = x[0]*x[1] - x[0] - x[1] - x[2] + 1.0;
        p[3]           = - x[0]*x[1] + 2.0*x[2];
}

    
/**
    Endmember fraction of opx
*/
void px_igd_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[2] + x[0]*x[7] - x[0] - x[1]*x[3] - x[1] - x[2] + x[3]*x[5] - x[3]*x[7] + x[3] - x[7] + 1.0;
        p[1]           = - x[0]*x[1] + x[0]*x[5] - x[0]*x[7] + x[0] - x[1]*x[3] + x[3]*x[5] - x[3]*x[7] + x[3];
        p[2]           = x[0]*x[1] - x[0]*x[2] - x[0]*x[5] + 2.0*x[1]*x[3] - 2.0*x[3]*x[5] + 2.0*x[3]*x[7] - 2.0*x[3];
        p[3]           = x[2];
        p[4]           = x[1] - x[4] - 2.0*x[5] - x[6];
        p[5]           = x[6];
        p[6]           = 2.0*x[5];
        p[7]           = x[4];
        p[8]           = x[7];
}

    
/**
    Endmember fraction of cpx
*/
void px_igd_cpx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[1] - x[2] - x[3] - x[8] + 1.0;
        p[1]           = - x[0]*x[1] - x[0]*x[3] + x[0]*x[7] - x[0]*x[8] + x[0] - x[1]*x[4] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
        p[2]           = x[1] - x[5] - x[6] - 2.0*x[7];
        p[3]           = x[6];
        p[4]           = x[5];
        p[5]           = 2.0*x[7];
        p[6]           = x[3];
        p[7]           = - x[0]*x[2] - x[1]*x[4] + x[2] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
        p[8]           = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - x[0]*x[7] + x[0]*x[8] - x[0] + 2.0*x[1]*x[4] + 2.0*x[3]*x[4] - 2.0*x[4]*x[7] + 2.0*x[4]*x[8] - 2.0*x[4];
        p[9]           = x[8];
}

    
/**
    Endmember fraction of ilm
*/
void px_igd_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[2];
        p[1]           = - x[0]*x[1] + x[0] - x[2];
        p[2]           = 1.0 - x[0];
        p[3]           = - x[2] + x[3];
        p[4]           = x[0]*x[1] + x[2] - x[3];
}

    
/**
    Endmember fraction of hb
*/
void px_igd_hb(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[1] + x[2] - 0.5*x[3] + x[5] - x[6] - x[7];
        p[1]           = x[1] - x[2] - 0.5*x[3] + x[6];
        p[2]           = - x[3]*x[4] + x[3];
        p[3]           = x[2] - x[6];
        p[4]           = x[0]*x[2] + x[0]*x[5] - x[0] + x[1]*x[9] - x[2] - x[5] + x[6]*x[9] + x[7]*x[9] - 1.5*x[8] - x[9] + 1.0;
        p[5]           = - x[0]*x[1] + x[0]*x[2] + x[0]*x[5] - x[0]*x[6] - x[0]*x[7] + x[0] + 2.0*x[1]*x[9] + 2.0*x[6]*x[9] + 2.0*x[7]*x[9] - 2.5*x[8] - 2.0*x[9];
        p[6]           = - x[0]*x[2] - x[0]*x[5] - x[1]*x[9] - x[6]*x[9] - x[7]*x[9] + 2.5*x[8] + x[9];
        p[7]           = x[0]*x[1] - x[0]*x[2] - x[0]*x[5] + x[0]*x[6] + x[0]*x[7] - 2.0*x[1]*x[9] - 2.0*x[6]*x[9] - 2.0*x[7]*x[9] + 1.5*x[8] + 2.0*x[9];
        p[8]           = x[6];
        p[9]           = x[3]*x[4];
        p[10]           = x[7];
}

    
/**
    Endmember fraction of bi
*/
void px_igd_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - x[0] - x[1] - x[2] - x[3] - 2./3.*x[4] + 1.0;
        p[1]           = x[0] - 1./3.*x[4];
        p[2]           = - x[0]*x[1] - x[0]*x[2] - x[0]*x[3] + x[4];
        p[3]           = x[1];
        p[4]           = x[3];
        p[5]           = x[2];
}

    
/**
    Endmember fraction of ep
*/
void px_igd_ep(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[0] - x[1] + 1.0;
        p[1]           = 2.0*x[1];
        p[2]           = x[0] - x[1];
}

    
/**
    Endmember fraction of cd
*/
void px_igd_cd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[0] - x[1] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}


/**
    Endmember to xeos for fper_S11
*/
void p2x_igd_fper(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/** 
  endmembers to xeos (biotite)
*/
void p2x_igd_bi(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[5];
    d->iguess[3]  = d->p[4];
    d->iguess[1]  = d->p[3];
    d->iguess[0]  = (-3.0*d->p[1] - 1.0*d->p[2])/(d->iguess[2] + d->iguess[3] + d->iguess[1] - 3.0);
    d->iguess[4]  = 1.5*d->iguess[2]*d->iguess[0] - 1.5*d->iguess[2] - 1.5*d->p[0] + 1.5*d->iguess[3]*d->iguess[0] - 1.5*d->iguess[3] + 1.5*d->iguess[0]*d->iguess[1] - 1.5*d->iguess[0] - 1.5*d->iguess[1] + 1.5;
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/** 
  endmembers to xeos (cordierite)
*/
void p2x_igd_cd(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;
	
	d->iguess[0]  = d->p[1];
	d->iguess[1]  = d->p[2];
	
	if (d->z_em[2]  == 0.0){ d->iguess[1]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (clinopyroxene)
*/
void p2x_igd_cpx(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = (2.0*d->p[1] + d->p[8])/(d->p[1] - d->p[2] - d->p[3] - d->p[4] - 0.5*d->p[5] - d->p[6] + d->p[7] + d->p[8] - d->p[9] + 1.0);	
	d->iguess[1]  = d->p[2] + d->p[3] + d->p[4] + d->p[5];
	d->iguess[2]  = d->p[1]+d->p[7]+d->p[8];
	d->iguess[3]  = d->p[6];
	d->iguess[4]  = (d->p[7] + ((2.0*d->p[1] + d->p[8])/(d->p[1] - d->p[2] - d->p[3] - d->p[4] - 0.5*d->p[5] - d->p[6] + d->p[7] + d->p[8] - d->p[9] + 1.0) - 1.0)*(d->p[1] + d->p[7] + d->p[8]))/(-d->p[2] - d->p[3] - d->p[4] - 0.5*d->p[5] - d->p[6] - d->p[9] + 1.0);
	d->iguess[5]  = d->p[4];
	d->iguess[6]  = d->p[3];
	d->iguess[7]  = d->p[5]/2.0;	
	d->iguess[8]  = d->p[9];	

	if (d->z_em[3]  == 0.0){ d->iguess[6]  = eps;}
	if (d->z_em[4]  == 0.0){ d->iguess[5]  = eps;}
	if (d->z_em[5]  == 0.0){ d->iguess[7]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (epidote)
*/
void p2x_igd_ep(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = d->p[2] + d->p[1]/2.0;
	d->iguess[1]  = d->p[1]/2.0;

	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (fluid)
*/
void p2x_igd_fl(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;
	
	d->iguess[0]  = d->p[1];
	d->iguess[1]  = d->p[2];
	d->iguess[2]  = d->p[3];
	
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (garnet)
*/
void p2x_igd_g(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[4]  = 0.25*d->p[5];
    d->iguess[3]  = d->p[4];
    d->iguess[2]  = d->p[3];
    d->iguess[1]  = d->iguess[2] + d->p[2];
    d->iguess[0]  = (d->iguess[1] + d->iguess[3] + d->p[0] + 4.0*d->iguess[4] - 1.0)/(d->iguess[1] - 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/** 
  endmembers to xeos (hornblende)
*/
void p2x_igd_hb(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0] = (-3.5*d->p[5] - 2.0*d->p[6] - 2.5*d->p[7])/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 1.5*d->p[4] - 1.5*d->p[5] - 1.5*d->p[6] - 1.5*d->p[7] + 0.5*d->p[8] - 2.0);
	d->iguess[1] = (d->p[1]-d->p[0] + 1.0-d->p[3]-d->p[8]-d->p[4]-d->p[6]-d->p[5]-d->p[7] -2*d->p[8] - d->p[10] + 2*(d->p[3] + d->p[8]))/2.0;
	d->iguess[2] = d->p[3] + d->p[8];
	d->iguess[3] = d->p[2] + d->p[9];
	d->iguess[4] = d->p[9]/(d->p[2]+d->p[9]);
	d->iguess[5] = 1.0-d->p[3]-d->p[8]-d->p[4]-d->p[6]-d->p[5]-d->p[7];
	d->iguess[6] = d->p[8];
	d->iguess[7] = d->p[10];
	d->iguess[8] = (-3.5*d->p[5] - 2.0*d->p[6] - 2.5*d->p[7])/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 1.5*d->p[4] - 1.5*d->p[5] - 1.5*d->p[6] - 1.5*d->p[7] + 0.5*d->p[8] - 2.0) -d->p[5] -d->p[7];
	d->iguess[9] = (d->p[5] + d->p[6] - (-3.5*d->p[5] - 2.0*d->p[6] - 2.5*d->p[7])*(0.5*d->p[0] - 0.5*d->p[1] - 0.5*d->p[10] - 0.5*d->p[3] + 0.5*d->p[4] + 0.5*d->p[5] + 0.5*d->p[6] + 0.5*d->p[7] - 0.5*d->p[8] + 0.5)/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 1.5*d->p[4] - 1.5*d->p[5] - 1.5*d->p[6] - 1.5*d->p[7] + 0.5*d->p[8] - 2.0))/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 0.5*d->p[4] - 0.5*d->p[5] - 0.5*d->p[6] - 0.5*d->p[7] + 0.5*d->p[8] - 0.5);

	if (d->z_em[8]  == 0){ d->iguess[6]  = eps;}
	if (d->z_em[10] == 0){ d->iguess[7]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (ilm)
*/
/** DEPRECATED */
void p2x_igd_ilm(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0] = d->p[1]+d->p[0];
	d->iguess[1] = d->p[0];
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}


/**
    Endmember to xeos for liq
*/
void p2x_igd_liq(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[10] = d->p[10];
    d->iguess[11] = d->p[11];
    d->iguess[12] = d->p[12];
    d->iguess[13] = d->p[13];
    d->iguess[9] = -6.*d->p[14]/(4.*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    d->iguess[8]  = 6.*(-d->p[9] + d->iguess[13])/(4.*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    d->iguess[7]  = -6.*d->p[8]/(4.*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    d->iguess[6]  = -6.*d->p[7]/(4*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    d->iguess[5]  = -6.*d->p[6]/(4*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    d->iguess[4]  = 6.*(-d->p[5] + d->iguess[11])/(4.*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    d->iguess[3]  = -6.*d->p[4]/(4*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    d->iguess[2]  = 3.*(-2.*d->p[3] + d->iguess[12])/(4.*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    d->iguess[0]  = 6.*(-d->p[2] + d->iguess[10])/(4.*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    d->iguess[1]  = 6.*(-d->p[1] + d->iguess[10])/(4.*d->iguess[11] + 6.*d->iguess[10] - d->iguess[12] + 2.*d->iguess[13] - 6.);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}




/** 
  endmembers to xeos (olivine)
*/
void p2x_igd_ol(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = (2.0*d->p[1]+d->p[3])/(2.0-d->p[0]);
	d->iguess[1]  = d->p[0];
	d->iguess[2]  = -d->p[0] - d->p[2] + 1.0 + (d->p[0] - 1.0)*(2.0*d->p[1] + d->p[3])/(2.0 - d->p[0]);
	
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (orthopyroxene)
*/
void p2x_igd_opx(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0] = (2.0*d->p[1] + d->p[2])/(d->p[0] + d->p[1] + d->p[2] + 0.5*d->p[6] - d->p[8] + 1.0);
	d->iguess[1] = 1.0 - d->p[3] - d->p[8] - d->p[0] - d->p[1] - d->p[2];
	d->iguess[2] = d->p[3];
	d->iguess[3] = (d->p[1] + d->p[2] + (2.0*d->p[1] + d->p[2])*(d->p[3] + d->p[8] - 1.0)/(d->p[0] + d->p[1] + d->p[2] + 0.5*d->p[6] - d->p[8] + 1.0))/(-d->p[0] - d->p[1] - d->p[2] - d->p[3] - 0.5*d->p[6]);
	d->iguess[4] = d->p[7];
	d->iguess[5] = d->p[6]/2.0;
	d->iguess[6] = d->p[5];
	d->iguess[7] = d->p[8];
	
	if (d->z_em[5]  == 0.0){ d->iguess[6]  = eps;}
	if (d->z_em[4]  == 0.0){ d->iguess[4]  = eps;}
	if (d->z_em[6]  == 0.0){ d->iguess[5]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (plagioclase)
*/
void p2x_igd_fsp(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;
	
	d->iguess[0] = d->p[1];
	d->iguess[1] = d->p[2];
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (spinel)
*/
void p2x_igd_spn(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2] = d->p[6];
    d->iguess[3] = d->p[7];
    d->iguess[1] = (-d->p[4] - d->p[5])/(d->iguess[2] + d->iguess[3] - 1.0);
    d->iguess[0] = (-d->iguess[2] - d->p[0] - d->p[1] + d->iguess[3] + 1.0)/(d->iguess[3] + 1.0);
    d->iguess[4] = -3.0*d->p[1]/2.0 - d->iguess[3]*d->iguess[0] + d->iguess[3] - d->iguess[0] + 1.0;
    d->iguess[6] = d->iguess[2]*d->iguess[1] + 3.0*d->p[5]/2.0 + d->iguess[3]*d->iguess[1] - d->iguess[1];
    d->iguess[5] = -d->iguess[6] + d->iguess[2]*d->iguess[1] - 3.0*d->p[3]/2.0 + d->iguess[3]*d->iguess[0] + d->iguess[3]*d->iguess[1] - 3.0*d->iguess[3]/2.0 + d->iguess[0] - d->iguess[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Objective function of fper_S11
*/
double obj_igd_fper(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_igd_fper(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = 1.0*x[0];
    sf[1]          = 1.0 - x[0];
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[1])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0])) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_fper(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

/**
    Objective function of liq
*/
double obj_igd_liq(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_igd_liq(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -x[0] + x[10]*(- x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0) + 2./3.*x[11]*(- x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9]) + 1./6.*x[12]*(x[0] + x[1] + x[2] + x[3] + x[4] + x[5] + x[6] + x[7] + x[8] + x[9] - 3.0) + 1./3.*x[13]*(- x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9]) - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0;
    sf[1]          = x[10]*x[1] - x[10] + 2./3.*x[11]*x[1] - 1./6.*x[12]*x[1] + 1./3.*x[13]*x[1] + x[1];
    sf[2]          = x[0]*x[10] + 2./3.*x[0]*x[11] - 1./6.*x[0]*x[12] + 1./3.*x[0]*x[13] + x[0] - x[10];
    sf[3]          = x[10]*x[4] + 2./3.*x[11]*x[4] - x[11] - 1./6.*x[12]*x[4] + 1./3.*x[13]*x[4] + x[4];
    sf[4]          = x[10]*x[5] + 2./3.*x[11]*x[5] - 1./6.*x[12]*x[5] + 1./3.*x[13]*x[5] + x[5];
    sf[5]          = x[10]*x[6] + 2./3.*x[11]*x[6] - 1./6.*x[12]*x[6] + 1./3.*x[13]*x[6] + x[6];
    sf[6]          = x[10]*x[7] + 2./3.*x[11]*x[7] - 1./6.*x[12]*x[7] + 1./3.*x[13]*x[7] + x[7];
    sf[7]          = x[10]*x[8] + 2./3.*x[11]*x[8] - 1./6.*x[12]*x[8] + 1./3.*x[13]*x[8] - x[13] + x[8];
    sf[8]          = x[11];
    sf[9]          = x[10];
    sf[10]          = x[12];
    sf[11]          = x[13];
    sf[12]          = x[10]*(x[2] + x[3]) + 2./3.*x[11]*(x[2] + x[3]) - 1./6.*x[12]*(x[2] + x[3]) - 0.5*x[12] + 1./3.*x[13]*(x[2] + x[3]) + x[2] + x[3];
    sf[13]          = -x[10]*x[9] - 2./3.*x[11]*x[9] + 1./6.*x[12]*x[9] - 1./3.*x[13]*x[9] - x[9] + 1.0;
    sf[14]          = x[10]*x[9] + 2./3.*x[11]*x[9] - 1./6.*x[12]*x[9] + 1./3.*x[13]*x[9] + x[9];
    sf[15]          = -x[10]*x[9] - 2./3.*x[11]*x[9] + 1./6.*x[12]*x[9] - 1./3.*x[13]*x[9] - x[9] + 1.0;
    sf[16]          = -2.0*x[12] + 4.0*x[2]*(x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0);
    sf[17]          = 4.0*x[3]*(x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0);
    sf[18]          = x[0]*(x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0) - x[10];
    sf[19]          = -x[10] + x[1]*(x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0);
    sf[20]          = -2.0*x[10] - 2.0*x[12] + (x[0] + x[1] + 4.0*x[2] + 4.0*x[3])*(x[10] + 2./3.*x[11] - 1./6.*x[12] + 1./3.*x[13] + 1.0);
    
    double t1       = 1.0/sf[13]*cpow(sf[15], 2.0);
    mu[0]           = gb[0] + R*T*creal(clog(sf[0]*t1)) + mu_Gex[0];
    mu[1]           = gb[1] + R*T*creal(clog(t1*sf[19]*sf[1]*1.0/sf[20])) + mu_Gex[1];
    mu[2]           = gb[2] + R*T*creal(clog(t1*sf[18]*1.0/sf[20]*sf[2])) + mu_Gex[2];
    mu[3]           = gb[3] + R*T*creal(clog(sf[12]*t1*cpow(sf[16], 4.0)*cpow(sf[20], -4.0))) + mu_Gex[3];
    mu[4]           = gb[4] + R*T*creal(clog(sf[12]*t1*cpow(sf[17], 4.0)*cpow(sf[20], -4.0))) + mu_Gex[4];
    mu[5]           = gb[5] + R*T*creal(clog(t1*sf[3])) + mu_Gex[5];
    mu[6]           = gb[6] + R*T*creal(clog(t1*sf[4] + d_em[6])) + mu_Gex[6];
    mu[7]           = gb[7] + R*T*creal(clog(t1*sf[5] + d_em[7])) + mu_Gex[7];
    mu[8]           = gb[8] + R*T*creal(clog(t1*sf[6])) + mu_Gex[8];
    mu[9]           = gb[9] + R*T*creal(clog(t1*sf[7])) + mu_Gex[9];
    mu[10]          = gb[10] + R*T*creal(clog(t1*sf[9])) + mu_Gex[10];
    mu[11]          = gb[11] + R*T*creal(clog(t1*sf[8])) + mu_Gex[11];
    mu[12]          = gb[12] + R*T*creal(clog(sf[10]*t1)) + mu_Gex[12];
    mu[13]          = gb[13] + R*T*creal(clog(sf[11]*t1)) + mu_Gex[13];
    mu[14]          = gb[14] + R*T*creal(clog(cpow(sf[14], 2.0) + d_em[14])) + mu_Gex[14];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_liq(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of fl
*/
double obj_igd_fl(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_igd_fl(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = -x[0] - x[1] - x[2] + 1.0;
    sf[1]          = x[0];
    sf[2]          = x[1];
    sf[3]          = x[2];
    sf[4]          = 1.0 - x[2];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[4])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[4])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[2]*sf[4])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[3], 2.0))) + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_fl(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of fsp
*/
double obj_igd_fsp(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_igd_fsp(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -x[0] - x[1] + 1.0;
    sf[1]          = x[0];
    sf[2]          = x[1];
    sf[3]          = 0.25*x[0] + 0.25;
    sf[4]          = 0.75 - 0.25*x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(1.7548*sf[0]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[1]*csqrt(sf[3])*csqrt(sf[4]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(1.7548*sf[2]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_fsp(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of spn
*/
double obj_igd_spn(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_igd_spn(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -1.0/3.0*x[0]*x[3] - 1.0/3.0*x[0] + 1.0/3.0*x[3] + 2.0/3.0*x[4] + 1.0/3.0;
    sf[1]          = 1.0/3.0*x[0]*x[3] + 1.0/3.0*x[0] + 2.0/3.0*x[5];
    sf[2]          = 2.0/3.0*x[1]*x[2] + 2.0/3.0*x[1]*x[3] - 2.0/3.0*x[1] - 1.0/3.0*x[3] - 2.0/3.0*x[4] - 2.0/3.0*x[5] - 2.0/3.0*x[6] + 2.0/3.0;
    sf[3]          = -2.0/3.0*x[1]*x[2] - 2.0/3.0*x[1]*x[3] + 2.0/3.0*x[1] + 2.0/3.0*x[6];
    sf[4]          = -1.0/3.0*x[0]*x[3] - 1.0/3.0*x[0] + 1.0/3.0*x[3] - 1.0/3.0*x[4] + 1.0/3.0;
    sf[5]          = 1.0/3.0*x[0]*x[3] + 1.0/3.0*x[0] - 1.0/3.0*x[5];
    sf[6]          = 2.0/3.0*x[1]*x[2] + 2.0/3.0*x[1]*x[3] - 2.0/3.0*x[1] - x[2] - 5.0/6.0*x[3] + 1.0/3.0*x[4] + 1.0/3.0*x[5] + 1.0/3.0*x[6] + 2.0/3.0;
    sf[7]          = -2.0/3.0*x[1]*x[2] - 2.0/3.0*x[1]*x[3] + 2.0/3.0*x[1] - 1.0/3.0*x[6];
    sf[8]          = x[2];
    sf[9]          = 0.5*x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[6])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[2]*csqrt(sf[4])*csqrt(sf[6]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[1]*sf[6])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(2.0*sf[2]*csqrt(sf[5])*csqrt(sf[6]))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[1]*sf[7] + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(2.0*sf[3]*csqrt(sf[5])*csqrt(sf[7]) + d_em[5])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(sf[0]*sf[8] + d_em[6])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(2.0*sf[1]*csqrt(sf[5])*csqrt(sf[9]))) + mu_Gex[7];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_spn(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of g
*/
double obj_igd_g(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_igd_g(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[1]          = -x[0]*x[1] + x[0];
    sf[2]          = x[1];
    sf[3]          = -x[2] - x[3] - 2.0*x[4] + 1.0;
    sf[4]          = x[3];
    sf[5]          = x[2];
    sf[6]          = x[4];
    sf[7]          = x[4];
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[1], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[2], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[2], 3.0)*cpow(sf[5], 2.0) + d_em[3])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(cpow(sf[0], 3.0)*cpow(sf[4], 2.0) + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(8.0*cpow(sf[0], 3.0)*sf[3]*csqrt(sf[6])*csqrt(sf[7]))) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_g(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ol
*/
double obj_igd_ol(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_igd_ol(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = -x[0] + x[2] + 1.0;
    sf[1]          = x[0] - x[2];
    sf[2]          = x[0]*x[1] - x[0] - x[1] - x[2] + 1.0;
    sf[3]          = -x[0]*x[1] + x[0] + x[2];
    sf[4]          = x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[4])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[3])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[2])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*sf[3])) + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_ol(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of opx
*/
double obj_igd_opx(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_igd_opx(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0]*x[1] - x[0]*x[5] + x[0]*x[7] - x[0] + x[1]*x[3] - x[1] - x[3]*x[5] + x[3]*x[7] - x[3] + x[5] - x[7] + 1.0;
    sf[1]          = -x[0]*x[1] + x[0]*x[5] - x[0]*x[7] + x[0] - x[1]*x[3] + x[3]*x[5] - x[3]*x[7] + x[3];
    sf[2]          = x[1] - x[4] - 2.0*x[5] - x[6] + x[7];
    sf[3]          = x[4];
    sf[4]          = x[6];
    sf[5]          = x[5];
    sf[6]          = x[0]*x[2] + x[0]*x[7] - x[0] - x[1]*x[3] - x[2] + x[3]*x[5] - x[3]*x[7] + x[3] - x[7] + 1.0;
    sf[7]          = -x[0]*x[2] - x[0]*x[7] + x[0] + x[1]*x[3] - x[3]*x[5] + x[3]*x[7] - x[3];
    sf[8]          = x[2];
    sf[9]          = x[7];
    sf[10]          = 1.0 - 0.5*x[1];
    sf[11]          = 0.5*x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*csqrt(sf[10])*sf[6])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(csqrt(sf[10])*sf[1]*sf[7])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*csqrt(sf[10])*sf[7])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*csqrt(sf[10])*sf[8])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(1.4142*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*sf[2]*sf[6])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(1.4142*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*sf[4]*sf[6] + d_em[5])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(2.8284*csqrt(sf[0])*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*csqrt(sf[5])*sf[6])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(1.4142*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*sf[3]*sf[6] + d_em[7])) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(csqrt(sf[10])*sf[2]*sf[9])) + mu_Gex[8];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_opx(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of cpx
*/
double obj_igd_cpx(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_igd_cpx(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0]*x[1] + x[0]*x[3] - x[0]*x[7] + x[0]*x[8] - x[0] + x[1]*x[4] - x[1] + x[3]*x[4] - x[3] - x[4]*x[7] + x[4]*x[8] - x[4] + x[7] - x[8] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[3] + x[0]*x[7] - x[0]*x[8] + x[0] - x[1]*x[4] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
    sf[2]          = x[1] + x[3] - x[5] - x[6] - 2.0*x[7] + x[8];
    sf[3]          = x[5];
    sf[4]          = x[6];
    sf[5]          = x[7];
    sf[6]          = -x[0]*x[2] - x[1]*x[4] + x[2] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
    sf[7]          = x[0]*x[2] + x[1]*x[4] + x[3]*x[4] - x[4]*x[7] + x[4]*x[8] - x[4];
    sf[8]          = -x[2] - x[3] - x[8] + 1.0;
    sf[9]          = x[3];
    sf[10]          = x[8];
    sf[11]          = 1.0 - 0.5*x[1];
    sf[12]          = 0.5*x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*csqrt(sf[11])*sf[8])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(csqrt(sf[11])*sf[1]*sf[7])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(1.4142*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*sf[2]*sf[8])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(1.4142*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*sf[4]*sf[8] + d_em[3])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(1.4142*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*sf[3]*sf[8] + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(2.8284*csqrt(sf[0])*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*csqrt(sf[5])*sf[8])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(csqrt(sf[11])*sf[2]*sf[9])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(sf[0]*csqrt(sf[11])*sf[6])) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(sf[0]*csqrt(sf[11])*sf[7])) + mu_Gex[8];
    mu[9]          = gb[9] + R*T*creal(clog(sf[10]*csqrt(sf[11])*sf[2])) + mu_Gex[9];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_cpx(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ilm
*/
double obj_igd_ilm(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_igd_ilm(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = -0.5*x[0]*x[1] + 0.5*x[0] + 0.5*x[2];
    sf[1]          = 0.5*x[0] - 0.5*x[3];
    sf[2]          = 1.0 - x[0];
    sf[3]          = 0.5*x[0]*x[1] - 0.5*x[2] + 0.5*x[3];
    sf[4]          = -0.5*x[0]*x[1] + 0.5*x[0] - 0.5*x[2];
    sf[5]          = 0.5*x[0] + 0.5*x[3];
    sf[6]          = 1.0 - x[0];
    sf[7]          = 0.5*x[0]*x[1] + 0.5*x[2] - 0.5*x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(csqrt(sf[0])*csqrt(sf[5]))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*cpow(sf[0], 0.25)*cpow(sf[1], 0.25)*cpow(sf[4], 0.25)*cpow(sf[5], 0.25))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(csqrt(sf[2])*csqrt(sf[6]) + d_em[2])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(csqrt(sf[3])*csqrt(sf[5]))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(2.0*cpow(sf[1], 0.25)*cpow(sf[3], 0.25)*cpow(sf[5], 0.25)*cpow(sf[7], 0.25))) + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_ilm(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of hb
*/
double obj_igd_hb(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_alk_hb(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = 1.0 - x[3];
    sf[1]          = -x[3]*x[4] + x[3];
    sf[2]          = x[3]*x[4];
    sf[3]          = -x[0] + x[8] + 1.0;
    sf[4]          = x[0] - x[8];
    sf[5]          = x[0]*x[1] + x[0]*x[6] + x[0]*x[7] - x[0] - x[1]*x[9] - x[1] - x[6]*x[9] - x[6] - x[7]*x[9] - x[7] + x[9] + 1.0;
    sf[6]          = -x[0]*x[1] - x[0]*x[6] - x[0]*x[7] + x[0] + x[1]*x[9] + x[6]*x[9] + x[7]*x[9] - x[9];
    sf[7]          = x[1];
    sf[8]          = x[6];
    sf[9]          = x[7];
    sf[10]          = x[5];
    sf[11]          = x[0]*x[2] + x[0]*x[5] - x[0] + x[1]*x[9] - x[2] - x[5] + x[6]*x[9] + x[7]*x[9] - 1.5*x[8] - x[9] + 1.0;
    sf[12]          = -x[0]*x[2] - x[0]*x[5] + x[0] - x[1]*x[9] - x[6]*x[9] - x[7]*x[9] + 1.5*x[8] + x[9];
    sf[13]          = x[2];
    sf[14]          = -0.5*x[1] + 0.5*x[2] - 0.25*x[3] - 0.5*x[6] - 0.5*x[7] + 1.0;
    sf[15]          = 0.5*x[1] - 0.5*x[2] + 0.25*x[3] + 0.5*x[6] + 0.5*x[7];
    sf[16]          = 1.0 - x[7];
    sf[17]          = x[7];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*cpow(sf[10], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[0]*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[7], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(8.0*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*sf[1]*cpow(sf[3], 3.0)*sf[5]*sf[7])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*cpow(sf[13], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[7], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[0]*cpow(sf[11], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[4], 3.0)*cpow(sf[6], 2.0))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[6], 2.0))) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[4], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(sf[0]*cpow(sf[13], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[8], 2.0) + d_em[8])) + mu_Gex[8];
    mu[9]          = gb[9] + R*T*creal(clog(8.0*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*sf[2]*cpow(sf[3], 3.0)*sf[5]*sf[7])) + mu_Gex[9];
    mu[10]          = gb[10] + R*T*creal(clog(2.0*sf[0]*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[17], 2.0)*cpow(sf[3], 3.0)*cpow(sf[9], 2.0))) + mu_Gex[10];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_alk_hb(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of bi
*/
double obj_igd_bi(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_igd_bi(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - x[0] - x[1] - x[2] - x[3] - 2.0/3.0*x[4] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[2] - x[0]*x[3] + x[0] + 2.0/3.0*x[4];
    sf[2]          = x[2];
    sf[3]          = x[3];
    sf[4]          = x[1];
    sf[5]          = -x[0] + 1.0/3.0*x[4] + 1.0;
    sf[6]          = x[0] - 1.0/3.0*x[4];
    sf[7]          = -0.5*x[1] - 0.5*x[2] + 0.5;
    sf[8]          = 0.5*x[1] + 0.5*x[2] + 0.5;
    sf[9]          = 1.0 - x[3];
    sf[10]          = x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(4.0*sf[0]*cpow(sf[5], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(4.0*sf[1]*cpow(sf[6], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(4.0*sf[1]*cpow(sf[5], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[4]*cpow(sf[5], 2.0)*cpow(sf[8], 2.0)*cpow(sf[9], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(4.0*cpow(sf[10], 2.0)*sf[3]*cpow(sf[5], 2.0)*sf[7]*sf[8])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[2]*cpow(sf[5], 2.0)*cpow(sf[8], 2.0)*cpow(sf[9], 2.0) + d_em[5])) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_bi(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ep
*/
double obj_igd_ep(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_igd_ep(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0] - x[1];
    sf[1]          = -x[0] + x[1] + 1.0;
    sf[2]          = x[0] + x[1];
    sf[3]          = -x[0] - x[1] + 1.0;
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[1]*sf[3])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[2] + d_em[1])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[2] + d_em[2])) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_ep(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of cd
*/
double obj_igd_cd(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_igd_cd(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0];
    sf[1]          = 1.0 - x[0];
    sf[2]          = x[1];
    sf[3]          = 1.0 - x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[1], 2.0)*sf[3])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[0], 2.0)*sf[3])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[1], 2.0)*sf[2])) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_igd_cd(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}




/**************************************************************************************/
/**************************************************************************************/
/*********************METAPELITE DATABASE (White et al., 2014)*************************/
/**************************************************************************************/
/**************************************************************************************/
/**
    Update dpdx matrix of liq_mp
*/
void dpdx_mp_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 1.0;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = 0.0;      dp_dx[0][3] = 0.0;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 0.0;      dp_dx[0][6] = 0.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = x[2];      dp_dx[1][2] = x[1];      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0 - x[2];      dp_dx[2][2] = -x[1];      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 1.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      
    dp_dx[4][0] = -1.0;      dp_dx[4][1] = -1.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = -1.0;      dp_dx[4][4] = -1.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = -1.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 1.0 - x[5];      dp_dx[5][5] = -x[4];      dp_dx[5][6] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = x[5];      dp_dx[6][5] = x[4];      dp_dx[6][6] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 1.0;      
}


/**
    Update dpdx matrix of fsp_mp
*/
void dpdx_mp_fsp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      
}


/**
    Update dpdx matrix of bi_mp
*/
void dpdx_mp_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[3] + 3.0*x[1] + x[4] + x[2] - 1.0;      dp_dx[0][1] = 3.0*x[0] - 1.0;      dp_dx[0][2] = x[0] - 1.0;      dp_dx[0][3] = x[0] - 1.0;      dp_dx[0][4] = x[0] - 1.0;      dp_dx[0][5] = -2.0/3.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = -1.0/3.0;      
    dp_dx[2][0] = -x[3] - 3.0*x[1] - x[4] - x[2];      dp_dx[2][1] = -3.0*x[0];      dp_dx[2][2] = -x[0];      dp_dx[2][3] = -x[0];      dp_dx[2][4] = -x[0];      dp_dx[2][5] = 1.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 1.0;      dp_dx[4][5] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 1.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 1.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      
}



/**
    Update dpdx matrix of g_mp
*/
void dpdx_mp_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[2] + x[1] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = x[0] - 1.0;      dp_dx[0][3] = -1.0;      
    dp_dx[1][0] = -x[2] - x[1] + 1.0;      dp_dx[1][1] = -x[0];      dp_dx[1][2] = -x[0];      dp_dx[1][3] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 1.0;      dp_dx[2][3] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.0;      
}



/**
    Update dpdx matrix of ep_mp
*/
void dpdx_mp_ep(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 2.0;      
    dp_dx[2][0] = 1.0;      dp_dx[2][1] = -1.0;      
}

/**
    Update dpdx matrix of ma_mp
*/
void dpdx_mp_ma(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -1.0;      dp_dx[0][4] = -1.0;      
    dp_dx[1][0] = x[1] - 1.0;      dp_dx[1][1] = x[0] - 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      
    dp_dx[2][0] = 1.0 - x[1];      dp_dx[2][1] = -x[0];      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 1.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 1.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 1.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      
}

/**
    Update dpdx matrix of mu_mp
*/
void dpdx_mp_mu(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -1.0;      dp_dx[0][4] = -1.0;      
    dp_dx[1][0] = x[1] - 1.0;      dp_dx[1][1] = x[0] - 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      
    dp_dx[2][0] = 1.0 - x[1];      dp_dx[2][1] = -x[0];      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 1.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 1.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 1.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      
}

/**
    Update dpdx matrix of opx_mp
*/
void dpdx_mp_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[4] + x[1] - 1.0;      dp_dx[0][1] = 0.5*x[5] + x[0] - 1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -1.0;      dp_dx[0][4] = 0.5*x[5] + x[0] - 1.0;      dp_dx[0][5] = 0.5*x[4] + 0.5*x[1] - 0.5;      
    dp_dx[1][0] = -x[3] - x[1] - x[2] + 1.0;      dp_dx[1][1] = 0.5*x[5] - x[0];      dp_dx[1][2] = -x[0];      dp_dx[1][3] = -x[0];      dp_dx[1][4] = 0.5*x[5];      dp_dx[1][5] = 0.5*x[4] + 0.5*x[1] - 0.5;      
    dp_dx[2][0] = -x[4] + x[3] + x[2];      dp_dx[2][1] = -x[5];      dp_dx[2][2] = x[0];      dp_dx[2][3] = x[0];      dp_dx[2][4] = -x[5] - x[0];      dp_dx[2][5] = -x[4] - x[1] + 1.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 1.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 1.0;      dp_dx[6][5] = 0.0;      
}

/**
    Update dpdx matrix of sa_mp
*/
void dpdx_mp_sa(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -0.25;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      
    dp_dx[2][0] = -x[2] - x[1] + 1.0;      dp_dx[2][1] = -x[0];      dp_dx[2][2] = -x[0];      dp_dx[2][3] = -0.75;      
    dp_dx[3][0] = x[2] + x[1];      dp_dx[3][1] = x[0];      dp_dx[3][2] = x[0];      dp_dx[3][3] = 1.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 1.0;      dp_dx[4][3] = 0.0;      
}

/**
    Update dpdx matrix of cd
*/
void dpdx_mp_cd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = -1.0;      
    dp_dx[1][0] = 1.0 - 1.0*x[1];      dp_dx[1][1] = -1.0*x[0];      dp_dx[1][2] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 1.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.00;      dp_dx[3][2] = 0.0;      
}

/**
    Update dpdx matrix of st_mp
*/
void dpdx_mp_st(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -4.0/3.0;      
    dp_dx[1][0] = 1.0 - x[1];      dp_dx[1][1] = -x[0];      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 4.0/3.0;      
}

/**
    Update dpdx matrix of chl_mp
*/
void dpdx_mp_chl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -x[2] + x[3] - x[4] - x[1];      dp_dx[0][1] = 0.25*x[5] + 1.25*x[6] - x[0];      dp_dx[0][2] = 1.25*x[6] - x[0];      dp_dx[0][3] = 0.25*x[5] + x[0] - 1.0;      dp_dx[0][4] = -0.25*x[5] + 1.25*x[6] - x[0] + 2.0;      dp_dx[0][5] = 0.25*x[3] - 0.25*x[4] + 0.25*x[1] - 0.25;      dp_dx[0][6] = 1.25*x[2] + 1.25*x[4] + 1.25*x[1] - 1.25;      
    dp_dx[1][0] = 2.0*x[2] + x[4] + 3.0*x[1] - 2.0;      dp_dx[1][1] = -1.25*x[5] - 2.25*x[6] + 3.0*x[0] - 1.0;      dp_dx[1][2] = -2.25*x[6] + 2.0*x[0] - 1.0;      dp_dx[1][3] = -1.25*x[5];      dp_dx[1][4] = 1.25*x[5] - 2.25*x[6] + x[0] - 1.0;      dp_dx[1][5] = -1.25*x[3] + 1.25*x[4] - 1.25*x[1] + 1.25;      dp_dx[1][6] = -2.25*x[2] - 2.25*x[4] - 2.25*x[1] + 2.25;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = -1.0;      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      
    dp_dx[3][0] = x[2] - x[3] + x[4] + x[1];      dp_dx[3][1] = -0.25*x[5] - 1.25*x[6] + x[0];      dp_dx[3][2] = -1.25*x[6] + x[0];      dp_dx[3][3] = -0.25*x[5] - x[0];      dp_dx[3][4] = 0.25*x[5] - 1.25*x[6] + x[0];      dp_dx[3][5] = -0.25*x[3] + 0.25*x[4] - 0.25*x[1] + 0.25;      dp_dx[3][6] = -1.25*x[2] - 1.25*x[4] - 1.25*x[1] + 1.25;      
    dp_dx[4][0] = -x[2] - x[4] - x[1] + 1.0;      dp_dx[4][1] = x[6] - x[0];      dp_dx[4][2] = x[6] - x[0];      dp_dx[4][3] = 0.0;      dp_dx[4][4] = x[6] - x[0];      dp_dx[4][5] = 0.0;      dp_dx[4][6] = x[2] + x[4] + x[1] - 1.0;      
    dp_dx[5][0] = -x[2] - 2.0*x[1] + 1.0;      dp_dx[5][1] = 1.25*x[5] + 1.25*x[6] - 2.0*x[0];      dp_dx[5][2] = 1.25*x[6] - x[0];      dp_dx[5][3] = 1.25*x[5];      dp_dx[5][4] = -1.25*x[5] + 1.25*x[6];      dp_dx[5][5] = 1.25*x[3] - 1.25*x[4] + 1.25*x[1] - 1.25;      dp_dx[5][6] = 1.25*x[2] + 1.25*x[4] + 1.25*x[1] - 1.25;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 1.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      dp_dx[6][6] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 1.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      
}
/**
    Update dpdx matrix of ctd_mp
*/
void dpdx_mp_ctd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = -1.0;      
    dp_dx[1][0] = 1.0 - x[1];      dp_dx[1][1] = -x[0];      dp_dx[1][2] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      
}

/**
    Update dpdx matrix of sp_mp
*/
void dpdx_mp_sp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[2] + 1.0;      dp_dx[0][1] = 1.0;      dp_dx[0][2] = x[0] - 1.0;      
    dp_dx[1][0] = -x[2] - 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 1.0 - x[0];      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = -1.0;      dp_dx[2][2] = -1.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      
}

/**
    Update dpdx matrix of ilm
*/
void dpdx_mp_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.00;      
    dp_dx[1][0] = 1.00;      dp_dx[1][1] = -1.00;      
    dp_dx[2][0] = -1.00;      dp_dx[2][1] = 0.0;      
}


/**
    Update dpdx matrix of ilmm_mp
*/
void dpdx_mp_ilmm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = 0.0;      dp_dx[0][3] = 1.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = -1.0;      dp_dx[1][2] = -1.0;      dp_dx[1][3] = -1.0;      
    dp_dx[2][0] = -1.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 1.0;      dp_dx[4][3] = 0.0;      
}

/**
    Update dpdx matrix of mt_mp
*/
void dpdx_mp_mt(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -2.0;      dp_dx[0][1] = 3.0;      
    dp_dx[1][0] = 3.0;      dp_dx[1][1] = -3.0;      
    dp_dx[2][0] = -1.0;      dp_dx[2][1] = 0.0;      
}

/**
    Endmember fraction of liq_mp
*/
void px_mp_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0];
        p[1]           = x[1]*x[2];
        p[2]           = x[1]*(1.0 - x[2]);
        p[3]           = x[3];
        p[4]           = -x[3] - x[1] - x[6] - x[4] - x[0] + 1.0;
        p[5]           = x[4]*(1.0 - x[5]);
        p[6]           = x[4]*x[5];
        p[7]           = x[6];
}
    
/**
    Endmember fraction of fsp_mp
*/
void px_mp_fsp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[0] - x[1] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}
/**
    Endmember fraction of bi_mp
*/
void px_mp_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[3]*x[0] - x[3] + 3.0*x[1]*x[0] - x[1] - 2.0/3.0*x[5] + x[4]*x[0] - x[4] + x[0]*x[2] - x[0] - x[2] + 1.0;
        p[1]           = -1.0/3.0*x[5] + x[0];
        p[2]           = -x[3]*x[0] - 3.0*x[1]*x[0] + x[5] - x[4]*x[0] - x[0]*x[2];
        p[3]           = x[2];
        p[4]           = x[4];
        p[5]           = x[3];
        p[6]           = x[1];
}
    
/**
    Endmember fraction of g_mp
*/
void px_mp_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[3] + x[2]*x[0] - x[2] + x[0]*x[1] - x[0] - x[1] + 1.0;
        p[1]           = -x[2]*x[0] - x[0]*x[1] + x[0];
        p[2]           = x[2];
        p[3]           = x[1];
        p[4]           = x[3];
}

/**
    Endmember fraction of ep_mp
*/
void px_mp_ep(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[0] - x[1] + 1.0;
        p[1]           = 2.0*x[1];
        p[2]           = x[0] - x[1];
}
    
/**
    Endmember fraction of ma_mp
*/
void px_mp_ma(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[4] - x[2] - x[3] + x[1];
        p[1]           = x[0]*x[1] - x[0] - x[1] + 1.0;
        p[2]           = -x[0]*x[1] + x[0];
        p[3]           = x[3];
        p[4]           = x[4];
        p[5]           = x[2];
}
    
/**
    Endmember fraction of mu_mp
*/
void px_mp_mu(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[4] - x[2] - x[3] + x[1];
        p[1]           = x[0]*x[1] - x[0] - x[1] + 1.0;
        p[2]           = -x[0]*x[1] + x[0];
        p[3]           = x[3];
        p[4]           = x[4];
        p[5]           = x[2];
}
    
/**
    Endmember fraction of opx_mp
*/
void px_mp_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 0.5*x[4]*x[5] + x[4]*x[0] - x[4] - x[3] + 0.5*x[1]*x[5] + x[1]*x[0] - x[1] - 0.5*x[5] - x[0] - x[2] + 1.0;
        p[1]           = 0.5*x[4]*x[5] - x[3]*x[0] + 0.5*x[1]*x[5] - x[1]*x[0] - 0.5*x[5] - x[0]*x[2] + x[0];
        p[2]           = -x[4]*x[5] - x[4]*x[0] + x[3]*x[0] - x[1]*x[5] + x[5] + x[0]*x[2];
        p[3]           = x[2];
        p[4]           = x[3];
        p[5]           = x[1];
        p[6]           = x[4];
}
    
/**
    Endmember fraction of sa_mp
*/
void px_mp_sa(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[2] - 0.25*x[3] - x[0] - x[1] + 1.0;
        p[1]           = x[1];
        p[2]           = -x[2]*x[0] - 0.75*x[3] - x[0]*x[1] + x[0];
        p[3]           = x[2]*x[0] + x[3] + x[0]*x[1];
        p[4]           = x[2];
}
    
/**
    Endmember fraction of cd
*/
void px_mp_cd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] - 1.0*x[0] - 1.0*x[1] - 1.0*x[2] + 1.0;
        p[1]           = -1.0*x[0]*x[1] + x[0];
        p[2]           = x[2];
        p[3]           = x[1];
}

    
/**
    Endmember fraction of st_mp
*/
void px_mp_st(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[2] + x[1]*x[0] - x[1] - 4.0/3.0*x[3] - x[0] + 1.0;
        p[1]           = -x[1]*x[0] + x[0];
        p[2]           = x[1];
        p[3]           = x[2];
        p[4]           = 4.0/3.0*x[3];
}

/**
    Endmember fraction of chl_mp
*/
void px_mp_chl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.25*x[2]*x[6] - x[2]*x[0] + 0.25*x[3]*x[5] + x[3]*x[0] - x[3] - 0.25*x[5]*x[4] + 0.25*x[5]*x[1] - 0.25*x[5] + 1.25*x[6]*x[4] + 1.25*x[6]*x[1] - 1.25*x[6] - x[4]*x[0] + 2.0*x[4] - x[0]*x[1];
        p[1]           = -2.25*x[2]*x[6] + 2.0*x[2]*x[0] - x[2] - 1.25*x[3]*x[5] + 1.25*x[5]*x[4] - 1.25*x[5]*x[1] + 1.25*x[5] - 2.25*x[6]*x[4] - 2.25*x[6]*x[1] + 2.25*x[6] + x[4]*x[0] - x[4] + 3.0*x[0]*x[1] - 2.0*x[0] - x[1] + 1.0;
        p[2]           = -x[4] + x[1];
        p[3]           = -1.25*x[2]*x[6] + x[2]*x[0] - 0.25*x[3]*x[5] - x[3]*x[0] + 0.25*x[5]*x[4] - 0.25*x[5]*x[1] + 0.25*x[5] - 1.25*x[6]*x[4] - 1.25*x[6]*x[1] + 1.25*x[6] + x[4]*x[0] + x[0]*x[1];
        p[4]           = x[2]*x[6] - x[2]*x[0] + x[6]*x[4] + x[6]*x[1] - x[6] - x[4]*x[0] - x[0]*x[1] + x[0];
        p[5]           = 1.25*x[2]*x[6] - x[2]*x[0] + 1.25*x[3]*x[5] - 1.25*x[5]*x[4] + 1.25*x[5]*x[1] - 1.25*x[5] + 1.25*x[6]*x[4] + 1.25*x[6]*x[1] - 1.25*x[6] - 2.0*x[0]*x[1] + x[0];
        p[6]           = x[2];
        p[7]           = x[3];
}
     
/**
    Endmember fraction of ctd_mp
*/
void px_mp_ctd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[2] + x[1]*x[0] - x[1] - x[0] + 1.0;
        p[1]           = -x[1]*x[0] + x[0];
        p[2]           = x[1];
        p[3]           = x[2];
}

/**
    Endmember fraction of sp_mp
*/
void px_mp_sp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1] + (x[0] - 1.0)*(x[2] + 1.0);
        p[1]           = (1.0 - x[0])*(x[2] + 1.0);
        p[2]           = -x[1] - x[2] + 1.0;
        p[3]           = x[2];
}

/**
    Endmember fraction of ilm
*/
void px_mp_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1];
        p[1]           = x[0] - 1.0*x[1];
        p[2]           = 1.0 - 1.0*x[0];
}
 
/**
    Endmember fraction of ilmm_mp
*/
void px_mp_ilmm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[3];
        p[1]           = -x[1] + x[0] - x[2] - x[3];
        p[2]           = 1.0 - x[0];
        p[3]           = x[1];
        p[4]           = x[2];
}
    
/**
    Endmember fraction of mt_mp
*/
void px_mp_mt(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 3.0*x[1] - 2.0*x[0];
        p[1]           = -3.0*x[1] + 3.0*x[0];
        p[2]           = 1.0 - x[0];
}


/**
    Objective function of liq_mp
*/
double obj_mp_liq(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mp_liq(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = 1.0 - x[6];
    sf[1]          = x[0];
    sf[2]          = x[1]*x[2];
    sf[3]          = x[1]*(1.0 - x[2]);
    sf[4]          = x[3];
    sf[5]          = -x[3] - x[1] - x[6] - x[4] - x[0] + 1.0;
    sf[6]          = x[4];
    sf[7]          = x[5];
    sf[8]          = 1.0 - x[5];
    sf[9]          = x[6];
    
    
    mu[0]          = R*T*creal(clog(sf[0]*sf[1])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(sf[0]*sf[2])) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(sf[0]*sf[3])) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(sf[0]*sf[4])) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(sf[0]*sf[5])) + gb[4] + mu_Gex[4];
    mu[5]          = R*T*creal(clog(sf[0]*sf[6]*cpow(sf[8], 5.0))) + gb[5] + mu_Gex[5];
    mu[6]          = R*T*creal(clog(sf[0]*sf[6]*cpow(sf[7], 5.0))) + gb[6] + mu_Gex[6];
    mu[7]          = R*T*creal(clog(cpow(sf[9], 2.0))) + gb[7] + mu_Gex[7];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_liq(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

/**
    Objective function of fsp_mp
*/
double obj_mp_fsp(unsigned n, const double *x, double *grad, void *SS_ref_db){

	SS_ref *d  = (SS_ref *) SS_ref_db;

	int n_em   = d->n_em;
	double P   = d->P;
	double T   = d->T;
	double R   = d->R;

	double *gb     = d->gb_lvl;
	double *mat_phi= d->mat_phi;
	double *mu_Gex = d->mu_Gex;
	double *sf     = d->sf;
	double *mu     = d->mu;

	px_mp_fsp(SS_ref_db,x);

	d->sum_v = 0.0;
	for (int i = 0; i < d->n_em; i++){
		d->sum_v += d->p[i]*d->v[i];
	}
	for (int i = 0; i < d->n_em; i++){
		d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
	}

	for (int i = 0; i < d->n_em; i++){
		mu_Gex[i] = 0.0;
		int it = 0;
		for (int j = 0; j < d->n_xeos; j++){
			for (int k = j+1; k < d->n_em; k++){
				mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
				it += 1;
			}
		}
	}
	
    sf[0]           = -x[0] - x[1] + 1.0;
    sf[1]           = x[0];
    sf[2]           = x[1];
    sf[3]           = 0.25*x[0] + 0.25;
    sf[4]           = 0.75 - 0.25*x[0];

	mu[0]          = R*T*creal(clog(1.7548*sf[0]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) 	+ gb[0] + mu_Gex[0];
	mu[1]          = R*T*creal(clog(2.0*sf[1]*csqrt(sf[3])*csqrt(sf[4]))) 				+ gb[1] + mu_Gex[1];
	mu[2]          = R*T*creal(clog(1.7548*sf[2]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) 	+ gb[2] + mu_Gex[2];

	d->sum_apep = 0.0;
	for (int i = 0; i < n_em; i++){
	   d->sum_apep += d->ape[i]*d->p[i];
	}
	d->factor = d->fbc/d->sum_apep;

	d->df_raw = 0.0;
	for (int i = 0; i < d->n_em; i++){
		d->df_raw += mu[i]*d->p[i];
	}
	d->df = d->df_raw * d->factor;
	
	if (grad){
	double *dfx    = d->dfx;
	double **dp_dx = d->dp_dx;
		dpdx_mp_fsp(SS_ref_db,x);
		for (int i = 0; i < (d->n_xeos); i++){
		   dfx[i] = 0.0;
		   for (int j = 0; j < n_em; j++){
			   dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
		   }
		   grad[i] = creal(dfx[i]);
		}
	}

	return d->df;
}
    
/**
    Objective function of bi_mp
*/
double obj_mp_bi(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_bi(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[3]*x[0] - x[3] + 3.0*x[1]*x[0] - x[1] - 2./3.*x[5] + x[4]*x[0] - x[4] + x[0]*x[2] - x[0] - x[2] + 1.0;
    sf[1]          = x[1];
    sf[2]          = -x[3]*x[0] - 3.0*x[1]*x[0] + 2./3.*x[5] - x[4]*x[0] - x[0]*x[2] + x[0];
    sf[3]          = x[3];
    sf[4]          = x[4];
    sf[5]          = x[2];
    sf[6]          = -x[1] + 1./3.*x[5] - x[0] + 1.0;
    sf[7]          = x[1];
    sf[8]          = -1./3.*x[5] + x[0];
    sf[9]          = -0.5*x[3] - 0.5*x[2] + 0.5;
    sf[10]          = 0.5*x[3] + 0.5*x[2] + 0.5;
    sf[11]          = 1.0 - x[4];
    sf[12]          = x[4];
    
    
    mu[0]          = R*T*creal(clog(4.0*sf[10]*cpow(sf[6], 2.0)*sf[0]*cpow(sf[11], 2.0)*sf[9])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(4.0*sf[10]*cpow(sf[8], 2.0)*sf[2]*cpow(sf[11], 2.0)*sf[9])) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(4.0*sf[10]*sf[2]*cpow(sf[6], 2.0)*cpow(sf[11], 2.0)*sf[9])) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(sf[5]*cpow(sf[10], 2.0)*cpow(sf[6], 2.0)*cpow(sf[11], 2.0))) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(4.0*sf[10]*cpow(sf[6], 2.0)*cpow(sf[12], 2.0)*sf[9]*sf[4])) + gb[4] + mu_Gex[4];
    mu[5]          = R*T*creal(clog(cpow(sf[10], 2.0)*sf[3]*cpow(sf[6], 2.0)*cpow(sf[11], 2.0) + d_em[5])) + gb[5] + mu_Gex[5];
    mu[6]          = R*T*creal(clog(4.0*sf[10]*cpow(sf[7], 2.0)*sf[1]*cpow(sf[11], 2.0)*sf[9])) + gb[6] + mu_Gex[6];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_bi(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    

/**
    Objective function of g_mp
*/
double obj_mp_g(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_g(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[2]*x[0] - x[2] + x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[1]          = -x[2]*x[0] - x[0]*x[1] + x[0];
    sf[2]          = x[2];
    sf[3]          = x[1];
    sf[4]          = 1.0 - x[3];
    sf[5]          = x[3];
    
    mu[0]          = R*T*creal(clog(cpow(sf[4], 2.0)*cpow(sf[0], 3.0))) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(cpow(sf[4], 2.0)*cpow(sf[1], 3.0))) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(cpow(sf[4], 2.0)*cpow(sf[2], 3.0))) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(cpow(sf[4], 2.0)*cpow(sf[3], 3.0))) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(cpow(sf[5], 2.0)*cpow(sf[0], 3.0)+ d_em[4])) + gb[4] + mu_Gex[4];
    

	d->sum_apep = 0.0;
	for (int i = 0; i < n_em; i++){
	   d->sum_apep += d->ape[i]*d->p[i];
	}
	d->factor = d->fbc/d->sum_apep;

	d->df_raw = 0.0;
	for (int i = 0; i < d->n_em; i++){
		d->df_raw += mu[i]*d->p[i];
	}
	d->df = d->df_raw * d->factor;
	
    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_g(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ep_mp
*/
double obj_mp_ep(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_ep(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0] - x[1];
    sf[1]          = -x[0] + x[1] + 1.0;
    sf[2]          = x[0] + x[1];
    sf[3]          = -x[0] - x[1] + 1.0;
    
    
    mu[0]          = R*T*creal(clog(sf[1]*sf[3])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(sf[1]*sf[2] + d_em[1])) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(sf[0]*sf[2] + d_em[2])) + gb[2] + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_ep(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ma_mp
*/
double obj_mp_ma(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_ma(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -x[4] - x[3] + 1.0;
    sf[1]          = x[3];
    sf[2]          = x[4];
    sf[3]          = x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[4]          = -x[0]*x[1] + x[0];
    sf[5]          = x[1];
    sf[6]          = 1.0 - x[2];
    sf[7]          = x[2];
    sf[8]          = -0.5*x[4] - 0.5*x[1] + 1.0;
    sf[9]          = 0.5*x[4] + 0.5*x[1];
    
    
    mu[0]          = R*T*creal(clog(4.0*sf[5]*sf[6]*sf[9]*sf[0]*sf[8])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(sf[6]*sf[0]*sf[3]*cpow(sf[8], 2.0))) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(sf[6]*sf[4]*sf[0]*cpow(sf[8], 2.0))) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(4.0*sf[5]*sf[6]*sf[9]*sf[1]*sf[8])) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(sf[5]*sf[6]*cpow(sf[9], 2.0)*sf[2])) + gb[4] + mu_Gex[4];
    mu[5]          = R*T*creal(clog(4.0*sf[5]*sf[9]*sf[7]*sf[0]*sf[8] + d_em[5])) + gb[5] + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_ma(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of mu_mp
*/
double obj_mp_mu(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_mu(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -x[4] - x[3] + 1.0;
    sf[1]          = x[3];
    sf[2]          = x[4];
    sf[3]          = x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[4]          = -x[0]*x[1] + x[0];
    sf[5]          = x[1];
    sf[6]          = 1.0 - x[2];
    sf[7]          = x[2];
    sf[8]          = -0.5*x[4] - 0.5*x[1] + 1.0;
    sf[9]          = 0.5*x[4] + 0.5*x[1];
    
    
    mu[0]          = R*T*creal(clog(4.0*sf[5]*sf[6]*sf[9]*sf[0]*sf[8])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(sf[6]*sf[0]*sf[3]*cpow(sf[8], 2.0))) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(sf[6]*sf[4]*sf[0]*cpow(sf[8], 2.0))) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(4.0*sf[5]*sf[6]*sf[9]*sf[1]*sf[8])) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(sf[5]*sf[6]*cpow(sf[9], 2.0)*sf[2])) + gb[4] + mu_Gex[4];
    mu[5]          = R*T*creal(clog(4.0*sf[5]*sf[9]*sf[7]*sf[0]*sf[8] + d_em[5])) + gb[5] + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_mu(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of opx_mp
*/
double obj_mp_opx(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_opx(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -0.5*x[4]*x[5] + x[3]*x[0] - x[3] - 0.5*x[1]*x[5] + x[1]*x[0] - x[1] + 0.5*x[5] + x[0]*x[2] - x[0] - x[2] + 1.0;
    sf[1]          = 0.5*x[4]*x[5] - x[3]*x[0] + 0.5*x[1]*x[5] - x[1]*x[0] - 0.5*x[5] - x[0]*x[2] + x[0];
    sf[2]          = x[1];
    sf[3]          = x[3];
    sf[4]          = x[2];
    sf[5]          = 0.5*x[4]*x[5] + x[4]*x[0] - x[4] + 0.5*x[1]*x[5] + x[1]*x[0] - x[1] - 0.5*x[5] - x[0] + 1.0;
    sf[6]          = -0.5*x[4]*x[5] - x[4]*x[0] - 0.5*x[1]*x[5] - x[1]*x[0] + 0.5*x[5] + x[0];
    sf[7]          = x[1];
    sf[8]          = x[4];
    sf[9]          = 0.5*x[3] + 0.5*x[2];
    sf[10]         = -0.5*x[3] - 0.5*x[2] + 1.0;
    
    
    mu[0]          = R*T*creal(clog(sf[0]*sf[5]*csqrt(sf[10]))) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(sf[1]*sf[6]*csqrt(sf[10]))) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(sf[6]*sf[0]*csqrt(sf[10]))) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(1.4142*sf[4]*cpow(sf[9], 0.25)*sf[5]*cpow(sf[10], 0.25))) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(1.4142*cpow(sf[9], 0.25)*sf[3]*sf[5]*cpow(sf[10], 0.25) + d_em[4])) + gb[4] + mu_Gex[4];
    mu[5]          = R*T*creal(clog(sf[2]*sf[7]*csqrt(sf[10]))) + gb[5] + mu_Gex[5];
    mu[6]          = R*T*creal(clog(sf[8]*sf[0]*csqrt(sf[10]))) + gb[6] + mu_Gex[6];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_opx(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of sa_mp
*/
double obj_mp_sa(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_sa(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[2]*x[0] - x[2] + 0.75*x[3] + x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[1]          = -x[2]*x[0] - 0.75*x[3] - x[0]*x[1] + x[0];
    sf[2]          = x[2];
    sf[3]          = x[1];
    sf[4]          = -0.25*x[3] - x[0] + 1.0;
    sf[5]          = 0.25*x[3] + x[0];
    sf[6]          = -x[2] - x[1] + 1.0;
    sf[7]          = x[2] + x[1];
    
    
    mu[0]          = R*T*creal(clog(sf[0]*cpow(sf[4], 3.0)*sf[6])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(sf[3]*sf[7]*cpow(sf[4], 3.0))) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(sf[1]*cpow(sf[5], 3.0)*sf[6])) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(cpow(sf[5], 3.0)*sf[0]*sf[6])) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(sf[7]*sf[2]*cpow(sf[4], 3.0) + d_em[4])) + gb[4] + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_sa(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of cd_mp
*/
double obj_mp_cd(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mp_cd(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = -x[0]*x[1] + 1.0*x[0];
    sf[1]          = 1.0*x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[2]          = 1.0*x[1];
    sf[3]          = 1.0*x[2];
    sf[4]          = 1.0 - x[2];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[1], 2.0)*sf[4])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[0], 2.0)*sf[4])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[1], 2.0)*sf[3])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[2], 2.0)*sf[4])) + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_cd(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of st_mp
*/
double obj_mp_st(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_st(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[1]*x[0] - x[1] - x[0] + 1.0;
    sf[1]          = -x[1]*x[0] + x[0];
    sf[2]          = x[1];
    sf[3]          = -x[2] - 1.33333333333333*x[3] + 1.0;
    sf[4]          = x[2];
    sf[5]          = x[3];
    sf[6]          = 1./3.*x[3];
    
    
    mu[0]          = R*T*creal(clog(cpow(sf[3], 2.0)*cpow(sf[0], 4.0))) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(cpow(sf[3], 2.0)*cpow(sf[1], 4.0))) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(cpow(sf[3], 2.0)*cpow(sf[2], 4.0))) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(cpow(sf[4], 2.0)*cpow(sf[0], 4.0) + d_em[3])) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(3.0792*cpow(sf[0], 4.0)*cpow(sf[5], 1.5)*csqrt(sf[6]))) + gb[4] + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_st(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of chl_mp
*/
double obj_mp_chl(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_chl(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = -x[3]*x[5] + x[3]*x[0] - x[3] + x[5]*x[4] - x[5]*x[1] + x[5] - x[4]*x[0] + x[4] + x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[1]          = x[3]*x[5] - x[3]*x[0] - x[5]*x[4] + x[5]*x[1] - x[5] + x[4]*x[0] - x[0]*x[1] + x[0];
    sf[2]          = -x[4] + x[1];
    sf[3]          = 0.25*x[2]*x[6] + 0.25*x[3]*x[5] + x[3]*x[0] - x[3] - 0.25*x[5]*x[4] + 0.25*x[5]*x[1] - 0.25*x[5] + 0.25*x[6]*x[4] + 0.25*x[6]*x[1] - 0.25*x[6] - x[0] + 1.0;
    sf[4]          = x[3];
    sf[5]          = -0.25*x[2]*x[6] - 0.25*x[3]*x[5] - x[3]*x[0] + 0.25*x[5]*x[4] - 0.25*x[5]*x[1] + 0.25*x[5] - 0.25*x[6]*x[4] - 0.25*x[6]*x[1] + 0.25*x[6] + x[0];
    sf[6]          = -x[2]*x[6] + x[2]*x[0] - x[2] - x[6]*x[4] - x[6]*x[1] + x[6] + x[4]*x[0] - x[4] + x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[7]          = x[2]*x[6] - x[2]*x[0] + x[6]*x[4] + x[6]*x[1] - x[6] - x[4]*x[0] - x[0]*x[1] + x[0];
    sf[8]          = x[2];
    sf[9]          = x[4] + x[1];
    sf[10]          = -0.5*x[2] - x[1] + 1.0;
    sf[11]          = 0.5*x[2] + x[1];
    
    
    mu[0]          = R*T*creal(clog(4.0*sf[9]*sf[11]*sf[0]*cpow(sf[3], 4.0)*sf[10])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(sf[0]*cpow(sf[3], 4.0)*sf[6]*cpow(sf[10], 2.0))) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(sf[2]*sf[9]*cpow(sf[11], 2.0)*cpow(sf[3], 4.0))) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(4.0*sf[9]*sf[11]*sf[1]*cpow(sf[5], 4.0)*sf[10])) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(cpow(sf[5], 4.0)*sf[7]*sf[0]*cpow(sf[10], 2.0))) + gb[4] + mu_Gex[4];
    mu[5]          = R*T*creal(clog(sf[1]*cpow(sf[3], 4.0)*sf[6]*cpow(sf[10], 2.0))) + gb[5] + mu_Gex[5];
    mu[6]          = R*T*creal(clog(4.0*sf[11]*sf[8]*sf[0]*cpow(sf[3], 4.0)*sf[10] + d_em[6])) + gb[6] + mu_Gex[6];
    mu[7]          = R*T*creal(clog(4.0*sf[9]*sf[11]*cpow(sf[4], 5.0)*sf[10])) + gb[7] + mu_Gex[7];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_chl(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ctd_mp
*/
double obj_mp_ctd(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_ctd(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = 1.0 - x[2];
    sf[1]          = x[2];
    sf[2]          = -x[1]*x[0] + x[0];
    sf[3]          = x[1]*x[0] - x[1] - x[0] + 1.0;
    sf[4]          = x[1];
    
    
    mu[0]          = R*T*creal(clog(csqrt(sf[0])*sf[3])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(csqrt(sf[0])*sf[2])) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(csqrt(sf[0])*sf[4])) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(csqrt(sf[1])*sf[3] + d_em[3])) + gb[3] + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_ctd(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of sp_mp
*/
double obj_mp_sp(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_sp(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[1];
    sf[1]          = -x[1] - x[2] + 1.0;
    sf[2]          = x[2];
    sf[3]          = 1.0 - x[0];
    sf[4]          = x[0];
    
    
    mu[0]          = R*T*creal(clog(sf[0]*sf[4])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(sf[0]*sf[3])) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(sf[4]*sf[1] + d_em[2])) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(sf[4]*sf[2])) + gb[3] + mu_Gex[3];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_sp(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

    
/**
    Objective function of ilm
*/
double obj_mp_ilm(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mp_ilm(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = 0.5*x[0] + 0.5*x[1];
    sf[1]          = 0.5*x[0] - 0.5*x[1];
    sf[2]          = 1.0 - x[0];
    sf[3]          = 0.5*x[0] - 0.5*x[1];
    sf[4]          = 0.5*x[0] + 0.5*x[1];
    sf[5]          = 1.0 - x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[4])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(4.0*csqrt(sf[0])*csqrt(sf[1])*csqrt(sf[3])*csqrt(sf[4]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[2]*sf[5])) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_ilm(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}


/**
    Objective function of ilmm_mp
*/
double obj_mp_ilmm(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_mp_ilmm(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = 0.5*x[0] - 0.5*x[1] - 0.5*x[2] + 0.5*x[3];
    sf[1]          = 0.5*x[0] - 0.5*x[1] - 0.5*x[2] - 0.5*x[3];
    sf[2]          = 1.0*x[1];
    sf[3]          = 1.0*x[2];
    sf[4]          = 1.0 - x[0];
    sf[5]          = 0.5*x[0] - 0.5*x[1] - 0.5*x[2] - 0.5*x[3];
    sf[6]          = 0.5*x[0] + 0.5*x[1] + 0.5*x[2] + 0.5*x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[6])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(4.0*csqrt(sf[0])*csqrt(sf[1])*csqrt(sf[5])*csqrt(sf[6]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[4], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[2]*sf[6])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[3]*sf[6])) + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_ilmm(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of mt_mp
*/
double obj_mp_mt(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_mp_mt(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = 0.5 - 0.5*x[0];
    sf[1]          = -0.5*x[1] + x[0];
    sf[2]          = 0.5*x[1] - 0.5*x[0] + 0.5;
    sf[3]          = x[1];
    sf[4]          = 1.0 - x[1];
    
    
    mu[0]          = R*T*creal(clog(4.0*sf[1]*sf[3]*sf[2] + d_em[0])) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(6.75*cpow(sf[1], 4.0/3.0)*cpow(sf[3], 2.0/3.0)*cpow(sf[2], 2.0/3.0)*cpow(sf[4], 1.0/3.0) + d_em[1])) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(4.0*sf[2]*sf[4]*sf[0])) + gb[2] + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_mp_mt(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
/**************************************************************************************/
/**************************************************************************************/
/*********************IGNEOUS DATABASE (Holland et al., 2018)**************************/
/**************************************************************************************/
/**************************************************************************************/
/**
    Endmember to xeos for fper_S11
*/
void p2x_ig_fper(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}
/** 
  endmembers to xeos (biotite)
*/
void p2x_ig_bi(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[5];
    d->iguess[3]  = d->p[4];
    d->iguess[1]  = d->p[3];
    d->iguess[0]  = (-3.0*d->p[1] - 1.0*d->p[2])/(d->iguess[2] + d->iguess[3] + d->iguess[1] - 3.0);
    d->iguess[4]  = 1.5*d->iguess[2]*d->iguess[0] - 1.5*d->iguess[2] - 1.5*d->p[0] + 1.5*d->iguess[3]*d->iguess[0] - 1.5*d->iguess[3] + 1.5*d->iguess[0]*d->iguess[1] - 1.5*d->iguess[0] - 1.5*d->iguess[1] + 1.5;
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/** 
  endmembers to xeos (cordierite)
*/
void p2x_ig_cd(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;
	
	d->iguess[0]  = d->p[1];
	d->iguess[1]  = d->p[2];
	
	if (d->z_em[2]  == 0.0){ d->iguess[1]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (clinopyroxene)
*/
void p2x_ig_cpx(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = (2.0*d->p[1] + d->p[8])/(d->p[1] - d->p[2] - d->p[3] - d->p[4] - 0.5*d->p[5] - d->p[6] + d->p[7] + d->p[8] - d->p[9] + 1.0);	
	d->iguess[1]  = d->p[2] + d->p[3] + d->p[4] + d->p[5];
	d->iguess[2]  = d->p[1]+d->p[7]+d->p[8];
	d->iguess[3]  = d->p[6];
	d->iguess[4]  = (d->p[7] + ((2.0*d->p[1] + d->p[8])/(d->p[1] - d->p[2] - d->p[3] - d->p[4] - 0.5*d->p[5] - d->p[6] + d->p[7] + d->p[8] - d->p[9] + 1.0) - 1.0)*(d->p[1] + d->p[7] + d->p[8]))/(-d->p[2] - d->p[3] - d->p[4] - 0.5*d->p[5] - d->p[6] - d->p[9] + 1.0);
	d->iguess[5]  = d->p[4];
	d->iguess[6]  = d->p[3];
	d->iguess[7]  = d->p[5]/2.0;	
	d->iguess[8]  = d->p[9];	

	if (d->z_em[3]  == 0.0){ d->iguess[6]  = eps;}
	if (d->z_em[4]  == 0.0){ d->iguess[5]  = eps;}
	if (d->z_em[5]  == 0.0){ d->iguess[7]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (epidote)
*/
void p2x_ig_ep(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = d->p[2] + d->p[1]/2.0;
	d->iguess[1]  = d->p[1]/2.0;

	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (fluid)
*/
void p2x_ig_fl(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;
	
	d->iguess[0]  = d->p[2];
	d->iguess[1]  = d->p[1];
	d->iguess[2]  = d->p[3];
	d->iguess[3]  = d->p[4];
	d->iguess[4]  = d->p[5];
	d->iguess[5]  = d->p[6];
	d->iguess[6]  = d->p[7];
	d->iguess[7]  = d->p[8];
	d->iguess[8]  = d->p[9];
	d->iguess[9]  = d->p[10];
	
	if (d->z_em[10] == 0.0){ d->iguess[9]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (garnet)
*/
void p2x_ig_g(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[4]  = 0.25*d->p[5];
    d->iguess[3]  = d->p[4];
    d->iguess[2]  = d->p[3];
    d->iguess[1]  = d->iguess[2] + d->p[2];
    d->iguess[0]  = (d->iguess[1] + d->iguess[3] + d->p[0] + 4.0*d->iguess[4] - 1.0)/(d->iguess[1] - 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/** 
  endmembers to xeos (hornblende)
*/
void p2x_ig_hb(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0] = (-3.5*d->p[5] - 2.0*d->p[6] - 2.5*d->p[7])/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 1.5*d->p[4] - 1.5*d->p[5] - 1.5*d->p[6] - 1.5*d->p[7] + 0.5*d->p[8] - 2.0);
	d->iguess[1] = (d->p[1]-d->p[0] + 1.0-d->p[3]-d->p[8]-d->p[4]-d->p[6]-d->p[5]-d->p[7] -2*d->p[8] - d->p[10] + 2*(d->p[3] + d->p[8]))/2.0;
	d->iguess[2] = d->p[3] + d->p[8];
	d->iguess[3] = d->p[2] + d->p[9];
	d->iguess[4] = d->p[9]/(d->p[2]+d->p[9]);
	d->iguess[5] = 1.0-d->p[3]-d->p[8]-d->p[4]-d->p[6]-d->p[5]-d->p[7];
	d->iguess[6] = d->p[8];
	d->iguess[7] = d->p[10];
	d->iguess[8] = (-3.5*d->p[5] - 2.0*d->p[6] - 2.5*d->p[7])/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 1.5*d->p[4] - 1.5*d->p[5] - 1.5*d->p[6] - 1.5*d->p[7] + 0.5*d->p[8] - 2.0) -d->p[5] -d->p[7];
	d->iguess[9] = (d->p[5] + d->p[6] - (-3.5*d->p[5] - 2.0*d->p[6] - 2.5*d->p[7])*(0.5*d->p[0] - 0.5*d->p[1] - 0.5*d->p[10] - 0.5*d->p[3] + 0.5*d->p[4] + 0.5*d->p[5] + 0.5*d->p[6] + 0.5*d->p[7] - 0.5*d->p[8] + 0.5)/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 1.5*d->p[4] - 1.5*d->p[5] - 1.5*d->p[6] - 1.5*d->p[7] + 0.5*d->p[8] - 2.0))/(-0.5*d->p[0] + 0.5*d->p[1] + 0.5*d->p[10] + 0.5*d->p[3] - 0.5*d->p[4] - 0.5*d->p[5] - 0.5*d->p[6] - 0.5*d->p[7] + 0.5*d->p[8] - 0.5);

	if (d->z_em[8]  == 0){ d->iguess[6]  = eps;}
	if (d->z_em[10] == 0){ d->iguess[7]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (ilm)
*/
/** DEPRECATED */
void p2x_ig_ilm(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0] = d->p[1]+d->p[0];
	d->iguess[1] = d->p[0];
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}


/** 
  endmembers to xeos (liquid)
*/
void p2x_ig_liq(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;
		
	d->iguess[0]  = (d->p[2]+d->p[10])/(1.0+3./4.*d->p[10]);	
	d->iguess[1]  = (d->p[1]+d->p[10])/(1.0+3./4.*d->p[10]);
	d->iguess[2]  = d->p[3]/(1.0+3./4.*d->p[10]);
	d->iguess[3]  = d->p[4]/(1.0+3./4.*d->p[10]);
	d->iguess[4]  = d->p[5]/(1.0+3./4.*d->p[10]);
	d->iguess[5]  = d->p[6]/(1.0+3./4.*d->p[10]);
	d->iguess[6]  = d->p[7]/(1.0+3./4.*d->p[10]);
	d->iguess[7]  = d->p[8]/(1.0+3./4.*d->p[10]);
	d->iguess[8]  = d->p[9]/(1.0+3./4.*d->p[10]);
	d->iguess[9]  = d->p[10];
	d->iguess[10] = d->p[11]/(1.0+3./4.*d->p[10]);
		
	if (d->z_em[11] == 0.0){ d->iguess[10] = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (muscovite)
*/
void p2x_ig_mu(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = d->p[2]/(1-(d->p[0]+d->p[4]+d->p[5]+d->p[3]));
	d->iguess[1]  = d->p[0]+d->p[4]+d->p[5]+d->p[3];
	d->iguess[2]  = d->p[5];
	d->iguess[3]  = d->p[3];
	d->iguess[4]  = d->p[4];

	if (d->z_em[5]  == 0.0){ d->iguess[2]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (olivine)
*/
void p2x_ig_ol(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0]  = (2.0*d->p[1]+d->p[3])/(2.0-d->p[0]);
	d->iguess[1]  = d->p[0];
	d->iguess[2]  = -d->p[0] - d->p[2] + 1.0 + (d->p[0] - 1.0)*(2.0*d->p[1] + d->p[3])/(2.0 - d->p[0]);
	
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (orthopyroxene)
*/
void p2x_ig_opx(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	d->iguess[0] = (2.0*d->p[1] + d->p[2])/(d->p[0] + d->p[1] + d->p[2] + 0.5*d->p[6] - d->p[8] + 1.0);
	d->iguess[1] = 1.0 - d->p[3] - d->p[8] - d->p[0] - d->p[1] - d->p[2];
	d->iguess[2] = d->p[3];
	d->iguess[3] = (d->p[1] + d->p[2] + (2.0*d->p[1] + d->p[2])*(d->p[3] + d->p[8] - 1.0)/(d->p[0] + d->p[1] + d->p[2] + 0.5*d->p[6] - d->p[8] + 1.0))/(-d->p[0] - d->p[1] - d->p[2] - d->p[3] - 0.5*d->p[6]);
	d->iguess[4] = d->p[7];
	d->iguess[5] = d->p[6]/2.0;
	d->iguess[6] = d->p[5];
	d->iguess[7] = d->p[8];
	
	if (d->z_em[5]  == 0.0){ d->iguess[6]  = eps;}
	if (d->z_em[4]  == 0.0){ d->iguess[4]  = eps;}
	if (d->z_em[6]  == 0.0){ d->iguess[5]  = eps;}
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (plagioclase)
*/
void p2x_ig_fsp(void *SS_ref_db, double eps){
	SS_ref *d  = (SS_ref *) SS_ref_db;
	
	d->iguess[0] = d->p[1];
	d->iguess[1] = d->p[2];
		
	for (int i = 0; i < d->n_xeos; i++){
		if (d->iguess[i] < d->bounds[i][0]){
			d->iguess[i] = d->bounds[i][0];
		}
		if (d->iguess[i] > d->bounds[i][1]){
			d->iguess[i] = d->bounds[i][1];
		}
	}
}

/** 
  endmembers to xeos (spinel)
*/
void p2x_ig_spn(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2] = d->p[6];
    d->iguess[3] = d->p[7];
    d->iguess[1] = (-d->p[4] - d->p[5])/(d->iguess[2] + d->iguess[3] - 1.0);
    d->iguess[0] = (-d->iguess[2] - d->p[0] - d->p[1] + d->iguess[3] + 1.0)/(d->iguess[3] + 1.0);
    d->iguess[4] = -3.0*d->p[1]/2.0 - d->iguess[3]*d->iguess[0] + d->iguess[3] - d->iguess[0] + 1.0;
    d->iguess[6] = d->iguess[2]*d->iguess[1] + 3.0*d->p[5]/2.0 + d->iguess[3]*d->iguess[1] - d->iguess[1];
    d->iguess[5] = -d->iguess[6] + d->iguess[2]*d->iguess[1] - 3.0*d->p[3]/2.0 + d->iguess[3]*d->iguess[0] + d->iguess[3]*d->iguess[1] - 3.0*d->iguess[3]/2.0 + d->iguess[0] - d->iguess[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ma
*/
void p2x_ig_ma(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[5];
    d->iguess[4]  = d->p[4];
    d->iguess[3]  = d->p[3];
    d->iguess[1]  = d->p[0] + d->iguess[4] + d->iguess[3] + d->iguess[2];
    d->iguess[0] = d->p[2]/(1.0-d->iguess[1]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for chl
*/
void p2x_ig_chl(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]    = d->p[6];
    d->iguess[3]  = -0.25*d->iguess[2] + 0.25*d->p[0] - 0.25*d->p[1] - 0.25*d->p[2] + 0.25*d->p[3] - 0.25*d->p[4] - 0.25*d->p[5] + 0.25;
    d->iguess[1]    = d->p[2] + d->iguess[3];
    d->iguess[0]   = (d->p[0] - 4.0*d->p[3] - 5.0*d->p[4] - 1.0*d->p[5] - 2.0*d->iguess[3])/(d->iguess[2] + 2.0*d->iguess[1] - 6.0);
    d->iguess[5]   = (d->iguess[2]*d->p[0] - 4.0*d->iguess[2]*d->p[3] - 4.0*d->iguess[2]*d->p[4] - 1.0*d->iguess[2]*d->p[5] - 2.0*d->iguess[2]*d->iguess[3] + d->p[0]*d->iguess[3] + d->p[0]*d->iguess[1] - 1.0*d->p[0] - 4.0*d->p[3]*d->iguess[3] - 4.0*d->p[3]*d->iguess[1] + 4.0*d->p[3] - 5.0*d->p[4]*d->iguess[3] - 3.0*d->p[4]*d->iguess[1] - 1.0*d->p[4] - 1.0*d->p[5]*d->iguess[3] - 1.0*d->p[5]*d->iguess[1] + d->p[5] - 2.0*d->iguess[3]*d->iguess[1] + 2.0*d->iguess[3] - 2.0*d->iguess[3]*d->iguess[3])/(d->iguess[2]*d->iguess[3] + 3.0*d->iguess[2]*d->iguess[1] - 7.0*d->iguess[2] + d->iguess[2]*d->iguess[2] + 2.0*d->iguess[3]*d->iguess[1] - 6.0*d->iguess[3] - 8.0*d->iguess[1] + 2.0*d->iguess[1]*d->iguess[1] + 6.0);
    d->iguess[4]   = (-1.0*d->iguess[2]*d->p[0] - 4.0*d->iguess[2]*d->p[1] + 4.0*d->iguess[2]*d->p[3] - 4.0*d->iguess[2]*d->p[4] + d->iguess[2]*d->p[5] - 2.0*d->iguess[2]*d->iguess[3] - 12.0*d->iguess[2]*d->iguess[1] + 28.0*d->iguess[2] - 4.0*d->iguess[2]*d->iguess[2] - 5.0*d->p[0]*d->iguess[3] + 3.0*d->p[0]*d->iguess[1] + d->p[0] - 8.0*d->p[1]*d->iguess[1] + 24.0*d->p[1] + 20.0*d->p[3]*d->iguess[3] - 12.0*d->p[3]*d->iguess[1] - 4.0*d->p[3] + 25.0*d->p[4]*d->iguess[3] - 33.0*d->p[4]*d->iguess[1] + 49.0*d->p[4] + 5.0*d->p[5]*d->iguess[3] - 3.0*d->p[5]*d->iguess[1] - 1.0*d->p[5] - 14.0*d->iguess[3]*d->iguess[1] + 22.0*d->iguess[3] + 10.0*d->iguess[3]*d->iguess[3] + 32.0*d->iguess[1] - 8.0*d->iguess[1]*d->iguess[1] - 24.0)/(-5.0*d->iguess[2]*d->iguess[3] + 5.0*d->iguess[2]*d->iguess[1] - 5.0*d->iguess[2] - 10.0*d->iguess[3]*d->iguess[1] + 30.0*d->iguess[3] - 40.0*d->iguess[1] + 10.0*d->iguess[1]*d->iguess[1] + 30.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for car
*/
void p2x_ig_car(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]    = d->p[1];
    d->iguess[1]  = d->p[2];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ta
*/
void p2x_ig_ta(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
     d->iguess[2]  = d->p[3];
    d->iguess[1]  = 0.5*d->p[4] + d->iguess[2];
    d->iguess[3]  = (2.0*d->p[0]*d->iguess[2] - 2.0*d->p[0] + 2.0*d->p[1]*d->iguess[1] - 2.0*d->p[1] + 4.0*d->iguess[1]*d->iguess[2] - 4.0*d->iguess[1] - 2.0*d->iguess[2]*d->iguess[2] + 2.0)/(2.0*d->iguess[1]*d->iguess[2] - 4.0*d->iguess[1] + d->iguess[1]*d->iguess[1] - 2.0*d->iguess[2] + 3.0);
    d->iguess[0]  = (-1.0*d->p[2] - 1.5*d->iguess[3]*d->iguess[1] + 1.5*d->iguess[3])/(d->iguess[1] - 1.0*d->iguess[2]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ctd
*/
void p2x_ig_ctd(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]    = d->p[1];
    d->iguess[1]  = d->p[2];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for zoi
*/
void p2x_ig_zoi(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}













/**
    Endmember to xeos for bi_mp
*/
void p2x_mp_bi(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1]  = d->p[6];
    d->iguess[3]  = d->p[5];
    d->iguess[4]  = d->p[4];
    d->iguess[2]  = d->p[3];
    d->iguess[5]  = 3.0*(-d->iguess[3]*d->p[1] + d->iguess[3] - 3.0*d->iguess[1]*d->p[1] + d->iguess[1] + d->p[0] - d->p[1]*d->iguess[4] - d->p[1]*d->iguess[2] + d->p[1] + d->iguess[4] + d->iguess[2] - 1.0)/(d->iguess[3] + 3.0*d->iguess[1] + d->iguess[4] + d->iguess[2] - 3.0);
    d->iguess[0]  = (-d->p[2] + d->iguess[5])/(d->iguess[3] + 3.0*d->iguess[1] + d->iguess[4] + d->iguess[2]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for cd_mp
*/
void p2x_mp_cd(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;

    d->iguess[1]  = d->p[3];
    d->iguess[2]  = d->p[2];
    d->iguess[0] = d->p[1]/(1.0 - d->p[3]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for chl_mp
*/
void p2x_mp_chl(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]   =  d->p[6];
    d->iguess[3]   =  d->p[7];
    d->iguess[4] = (d->iguess[3] + 1.0 - d->iguess[2] -(d->p[1] - d->p[3]+d->p[5]-d->p[0] + d->p[2]+d->p[4]))/4.0;
    d->iguess[1]   =  d->p[2] + d->iguess[4];
    d->iguess[0]  = (-2.0*d->iguess[4] + d->iguess[3] + d->p[0] - 4.0*d->p[3] - 5.0*d->p[4] - d->p[5])/(d->iguess[2] + 5.0*d->iguess[3] + 2.0*d->iguess[1] - 6.0);
    d->iguess[6]  = (-2.0*pow(d->iguess[4],2.0) - 2.0*d->iguess[4]*d->iguess[2] + d->iguess[4]*d->iguess[3] + d->iguess[4]*d->p[0] - 4.0*d->iguess[4]*d->p[3] - 5.0*d->iguess[4]*d->p[4] - d->iguess[4]*d->p[5] - 2.0*d->iguess[4]*d->iguess[1] + 2.0*d->iguess[4] + d->iguess[2]*d->iguess[3] + d->iguess[2]*d->p[0] - 4.0*d->iguess[2]*d->p[3] - 4.0*d->iguess[2]*d->p[4] - d->iguess[2]*d->p[5] + 5.0*d->iguess[3]*d->p[4] + d->iguess[3]*d->iguess[1] - d->iguess[3] + d->p[0]*d->iguess[1] - d->p[0] - 4.0*d->p[3]*d->iguess[1] + 4.0*d->p[3] - 3.0*d->p[4]*d->iguess[1] - d->p[4] - d->p[5]*d->iguess[1] + d->p[5])/(d->iguess[4]*d->iguess[2] + 5.0*d->iguess[4]*d->iguess[3] + 2.0*d->iguess[4]*d->iguess[1] - 6.0*d->iguess[4] + pow(d->iguess[2],2.0) + 5.0*d->iguess[2]*d->iguess[3] + 3.0*d->iguess[2]*d->iguess[1] - 7.0*d->iguess[2] + 5.0*d->iguess[3]*d->iguess[1] - 5.0*d->iguess[3] + 2.0*pow(d->iguess[1],2.0) - 8.0*d->iguess[1] + 6.0);
    d->iguess[5]  = (10.0*pow(d->iguess[4],2.0) - 2.0*d->iguess[4]*d->iguess[2] - 25.0*d->iguess[4]*d->iguess[3] - 5.0*d->iguess[4]*d->p[0] + 20.0*d->iguess[4]*d->p[3] + 25.0*d->iguess[4]*d->p[4] + 5.0*d->iguess[4]*d->p[5] - 14.0*d->iguess[4]*d->iguess[1] + 22.0*d->iguess[4] - 4.0*pow(d->iguess[2],2.0) - 21.0*d->iguess[2]*d->iguess[3] - d->iguess[2]*d->p[0] - 4.0*d->iguess[2]*d->p[1] + 4.0*d->iguess[2]*d->p[3] - 4.0*d->iguess[2]*d->p[4] + d->iguess[2]*d->p[5] - 12.0*d->iguess[2]*d->iguess[1] + 28.0*d->iguess[2] - 20.0*d->iguess[3]*d->p[1] - 45.0*d->iguess[3]*d->p[4] - 17.0*d->iguess[3]*d->iguess[1] + 21.0*d->iguess[3] + 3.0*d->p[0]*d->iguess[1] + d->p[0] - 8.0*d->p[1]*d->iguess[1] + 24.0*d->p[1] - 12.0*d->p[3]*d->iguess[1] - 4.0*d->p[3] - 33.0*d->p[4]*d->iguess[1] + 49.0*d->p[4] - 3.0*d->p[5]*d->iguess[1] - d->p[5] - 8.0*pow(d->iguess[1],2.0) + 32.0*d->iguess[1] - 24.0)/(5.0*(-d->iguess[4]*d->iguess[2] - 5.0*d->iguess[4]*d->iguess[3] - 2.0*d->iguess[4]*d->iguess[1] + 6.0*d->iguess[4] + d->iguess[2]*d->iguess[3] + d->iguess[2]*d->iguess[1] - d->iguess[2] + 5.0*pow(d->iguess[3],2.0) + 7.0*d->iguess[3]*d->iguess[1] - 11.0*d->iguess[3] + 2.0*pow(d->iguess[1],2.0) - 8.0*d->iguess[1] + 6.0));
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ctd_mp
*/
void p2x_mp_ctd(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[3];
    d->iguess[1]  = d->p[2];
    d->iguess[0] = d->p[1]/(1.0 - d->iguess[1]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ep_mp
*/
void p2x_mp_ep(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1]   =  d->p[1]/2.0;
    d->iguess[0]   =  d->p[2] + d->iguess[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for g_mp
*/
void p2x_mp_g(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[3]   =  d->p[4];
    d->iguess[1]   =  d->p[3];
    d->iguess[2]   =  d->p[2];
    d->iguess[0]  =  d->p[1]/(1.0 - d->iguess[2] - d->iguess[1]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ilm
*/
void p2x_mp_ilm(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1]   = d->p[0];
    d->iguess[0]  = d->p[1] + d->iguess[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for ilmm_mp
*/
void p2x_mp_ilmm(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[4];
    d->iguess[1]  = d->p[3];
    d->iguess[3]  = d->p[0];
    d->iguess[0]  = 1.0 - d->p[2];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}
 
/**
    Endmember to xeos for liq_mp
*/
void p2x_mp_liq(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]   = d->p[0];
    d->iguess[3]  = d->p[3];
    d->iguess[6] = d->p[7];
    d->iguess[1] = d->p[1] + d->p[2];
    d->iguess[2]  = d->p[1]/d->iguess[1];
    d->iguess[4]  = 1.0 - d->iguess[0] - d->iguess[1] - d->iguess[3] - d->iguess[6] - d->p[4];
    d->iguess[5]   = d->p[6]/d->iguess[4];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}
 
/**
    Endmember to xeos for ma_mp
*/
void p2x_mp_ma(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[5];
    d->iguess[4]  = d->p[4];
    d->iguess[3]  = d->p[3];
    d->iguess[1]  = d->p[0] + d->iguess[4] + d->iguess[3] + d->iguess[2];
    d->iguess[0] = d->p[2]/(1.0-d->iguess[1]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}
 
/**
    Endmember to xeos for mt_mp
*/
void p2x_mp_mt(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[0]  = 1.0 - d->p[2];
    d->iguess[1]   = (3.0*d->iguess[0] - d->p[1])/3.0;
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}
  
/**
    Endmember to xeos for mu_mp
*/
void p2x_mp_mu(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[5];
    d->iguess[4]  = d->p[4];
    d->iguess[3]  = d->p[3];
    d->iguess[1]  = d->p[0] + d->iguess[4] + d->iguess[3] + d->iguess[2];
    d->iguess[0] = d->p[2]/(1.0-d->iguess[1]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for opx_mp
*/
void p2x_mp_opx(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[4]  = d->p[6];
    d->iguess[1]  = d->p[5];
    d->iguess[3]  = d->p[4];
    d->iguess[2]  = d->p[3];
    d->iguess[0] = (-2.0*d->p[1] - d->p[2])/(d->iguess[4] + d->iguess[3] + 2.0*d->iguess[1] + d->iguess[2] - 2.0);
    d->iguess[5]  = 2.0*(pow(d->iguess[4], 2) + 2.0*d->iguess[4]*d->iguess[3] + 3.0*d->iguess[4]*d->iguess[1] + d->iguess[4]*d->p[0] + 2.0*d->iguess[4]*d->p[1] + d->iguess[4]*d->p[2] + 2.0*d->iguess[4]*d->iguess[2] - 3.0*d->iguess[4] + pow(d->iguess[3], 2) + 3.0*d->iguess[3]*d->iguess[1] + d->iguess[3]*d->p[0] + 2.0*d->iguess[3]*d->iguess[2] - 3.0*d->iguess[3] + 2.0*pow(d->iguess[1], 2) + 2.0*d->iguess[1]*d->p[0] + 2.0*d->iguess[1]*d->p[1] + d->iguess[1]*d->p[2] + 3.0*d->iguess[1]*d->iguess[2] - 4.0*d->iguess[1] + d->p[0]*d->iguess[2] - 2.0*d->p[0] - 2.0*d->p[1] - d->p[2] + pow(d->iguess[2], 2) - 3.0*d->iguess[2] + 2.0)/(pow(d->iguess[4], 2) + d->iguess[4]*d->iguess[3] + 3.0*d->iguess[4]*d->iguess[1] + d->iguess[4]*d->iguess[2] - 3.0*d->iguess[4] + d->iguess[3]*d->iguess[1] - d->iguess[3] + 2.0*pow(d->iguess[1], 2) + d->iguess[1]*d->iguess[2] - 4.0*d->iguess[1] - d->iguess[2] + 2.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}
    
/**
    Endmember to xeos for fsp_mp
*/
void p2x_mp_fsp(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[1]   = d->p[2];
    d->iguess[0]  = d->p[1];
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for sa_mp
*/
void p2x_mp_sa(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[4];
    d->iguess[1]  = d->p[1];
    d->iguess[0] = (4.0*d->iguess[2] + 4.0*d->p[0] + d->p[3] + 4.0*d->iguess[1] - 4.0)/(d->iguess[2] + d->iguess[1] - 4.0);
    d->iguess[3]  = 4.0/3.0*(-4.0*pow(d->iguess[2], 2) - 4.0*d->iguess[2]*d->p[0] - d->iguess[2]*d->p[2] - d->iguess[2]*d->p[3] - 8.0*d->iguess[2]*d->iguess[1] + 8.0*d->iguess[2] - 4.0*d->p[0]*d->iguess[1] + 4.0*d->p[0] - d->p[2]*d->iguess[1] + 4.0*d->p[2] - d->p[3]*d->iguess[1] + d->p[3] - 4.0*pow(d->iguess[1], 2) + 8.0*d->iguess[1] - 4.0)/(d->iguess[2] + d->iguess[1] - 4.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}


/**
    Endmember to xeos for sp_mp
*/
void p2x_mp_sp(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[2]  = d->p[3];
    d->iguess[1]  = 1.0 - d->p[2] - d->iguess[2];
    d->iguess[0] = (-d->p[1] + d->iguess[2] + 1.0)/(d->iguess[2] + 1.0);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for st_mp
*/
void p2x_mp_st(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    
    d->iguess[3]  = d->p[4]/(4.0/3.0);
    d->iguess[2]  = d->p[3];
    d->iguess[1]  = d->p[2];
    d->iguess[0] = d->p[1]/(1.0 - d->iguess[1]);
    
    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}

/**
    Endmember to xeos for mt_mp
*/
void p2x_aq17(void *SS_ref_db, double eps){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    int n_em = d->n_em;

    for (int i = 0; i < n_em; i++){
      d->iguess[i]  = d->p[i];
    }

    for (int i = 0; i < d->n_xeos; i++){
        if (d->iguess[i] < d->bounds[i][0]){
            d->iguess[i] = d->bounds[i][0];
        }
        if (d->iguess[i] > d->bounds[i][1]){
            d->iguess[i] = d->bounds[i][1];
        }
    }
}
  
/**
    Update dpdx matrix of fper_S11
*/
void dpdx_ig_fper(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      
    dp_dx[1][0] = 1.0;      
}


/** 
  update dpdpx matrix (biotite)
*/
void dpdx_ig_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[2] + x[3] + x[1] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = x[0] - 1.0;      dp_dx[0][3] = x[0] - 1.0;      dp_dx[0][4] = -2.0/3.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = -1.0/3.0;      
    dp_dx[2][0] = -x[2] - x[3] - x[1];      dp_dx[2][1] = -x[0];      dp_dx[2][2] = -x[0];      dp_dx[2][3] = -x[0];      dp_dx[2][4] = 1.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 1.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.0;      dp_dx[4][4] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 1.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      
}

/** 
  update dpdpx matrix (cordierite)
*/
void dpdx_ig_cd(void *SS_ref_db, const double *x){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	double **dp_dx = d->dp_dx;
   
	dp_dx[0][0]  = -1.;	   dp_dx[0][1]   = -1.;	   
	dp_dx[1][0]  =  1.;	   dp_dx[1][1]   =  0.;	   
	dp_dx[2][0]  =  0.;	   dp_dx[2][1]   =  1.;	   
}

/** 
  update dpdpx matrix (clinopyroxene)
*/
void dpdx_ig_cpx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = -1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -1.0;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 0.0;      dp_dx[0][6] = 0.0;      dp_dx[0][7] = 0.0;      dp_dx[0][8] = -1.0;      
    dp_dx[1][0] = -x[8] - x[3] + x[7] - x[1] + 1.0;      dp_dx[1][1] = -x[4] - x[0];      dp_dx[1][2] = 0.0;      dp_dx[1][3] = -x[4] - x[0];      dp_dx[1][4] = -x[8] - x[3] + x[7] - x[1] + 1.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      dp_dx[1][7] = x[4] + x[0];      dp_dx[1][8] = -x[4] - x[0];      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = -1.0;      dp_dx[2][6] = -1.0;      dp_dx[2][7] = -2.0;      dp_dx[2][8] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 1.0;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 1.0;      dp_dx[4][6] = 0.0;      dp_dx[4][7] = 0.0;      dp_dx[4][8] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 0.0;      dp_dx[5][7] = 2.0;      dp_dx[5][8] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 1.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      dp_dx[6][8] = 0.0;      
    dp_dx[7][0] = -x[2];      dp_dx[7][1] = -x[4];      dp_dx[7][2] = 1.0 - x[0];      dp_dx[7][3] = -x[4];      dp_dx[7][4] = -x[8] - x[3] + x[7] - x[1] + 1.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      dp_dx[7][7] = x[4];      dp_dx[7][8] = -x[4];      
    dp_dx[8][0] = x[8] + x[3] + x[2] - x[7] + x[1] - 1.0;      dp_dx[8][1] = 2.0*x[4] + x[0];      dp_dx[8][2] = x[0];      dp_dx[8][3] = 2.0*x[4] + x[0];      dp_dx[8][4] = 2.0*x[8] + 2.0*x[3] - 2.0*x[7] + 2.0*x[1] - 2.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = -2.0*x[4] - x[0];      dp_dx[8][8] = 2.0*x[4] + x[0];      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = 0.0;      dp_dx[9][4] = 0.0;      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = 1.0;      
}

/** 
  update dpdpx matrix (epidote)
*/
void dpdx_ig_ep(void *SS_ref_db, const double *x){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	double **dp_dx = d->dp_dx;
	
	dp_dx[0][0] = -1.0;         dp_dx[0][1] = -1.0;     
	dp_dx[1][0] =  0.0;         dp_dx[1][1] =  2.0;     
	dp_dx[2][0] =  1.0;         dp_dx[2][1] = -1.0;     
}

/** 
  update dpdpx matrix (fluid)
*/
void dpdx_ig_fl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.00;      dp_dx[0][1] = -1.00;      dp_dx[0][2] = -1.00;      dp_dx[0][3] = -1.00;      dp_dx[0][4] = -1.00;      dp_dx[0][5] = -1.00;      dp_dx[0][6] = -1.00;      dp_dx[0][7] = -1.00;      dp_dx[0][8] = -1.00;      dp_dx[0][9] = -1.00;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 1.00;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      dp_dx[1][7] = 0.0;      dp_dx[1][8] = 0.0;      dp_dx[1][9] = 0.0;      
    dp_dx[2][0] = 1.00;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 0.0;      dp_dx[2][8] = 0.0;      dp_dx[2][9] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.00;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      dp_dx[3][9] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.00;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = 0.0;      dp_dx[4][7] = 0.0;      dp_dx[4][8] = 0.0;      dp_dx[4][9] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 1.00;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 0.0;      dp_dx[5][7] = 0.0;      dp_dx[5][8] = 0.0;      dp_dx[5][9] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 1.00;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      dp_dx[6][8] = 0.0;      dp_dx[6][9] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 1.00;      dp_dx[7][7] = 0.0;      dp_dx[7][8] = 0.0;      dp_dx[7][9] = 0.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = 1.00;      dp_dx[8][8] = 0.0;      dp_dx[8][9] = 0.0;      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = 0.0;      dp_dx[9][4] = 0.0;      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = 1.00;      dp_dx[9][9] = 0.0;      
    dp_dx[10][0] = 0.0;      dp_dx[10][1] = 0.0;      dp_dx[10][2] = 0.0;      dp_dx[10][3] = 0.0;      dp_dx[10][4] = 0.0;      dp_dx[10][5] = 0.0;      dp_dx[10][6] = 0.0;      dp_dx[10][7] = 0.0;      dp_dx[10][8] = 0.0;      dp_dx[10][9] = 1.00;      
}


/** 
  update dpdpx matrix (garnet)
*/
void dpdx_ig_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] - 1.0;      dp_dx[0][1] = x[0] - 1.0;      dp_dx[0][2] = 0.0;      dp_dx[0][3] = -1.0;      dp_dx[0][4] = -4.0;      
    dp_dx[1][0] = 1.0 - x[1];      dp_dx[1][1] = -x[0];      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = -1.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 1.0;      dp_dx[4][4] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 4.0;      
}

/** 
  update dpdpx matrix (hornblende)
*/
void dpdx_ig_hb(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = -1.0;      dp_dx[0][2] = 1.0;      dp_dx[0][3] = -0.50;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = 1.0;      dp_dx[0][6] = -1.0;      dp_dx[0][7] = -1.0;      dp_dx[0][8] = 0.0;      dp_dx[0][9] = 0.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 1.0;      dp_dx[1][2] = -1.0;      dp_dx[1][3] = -0.50;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 1.0;      dp_dx[1][7] = 0.0;      dp_dx[1][8] = 0.0;      dp_dx[1][9] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 1.0 - x[4];      dp_dx[2][4] = -x[3];      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 0.0;      dp_dx[2][8] = 0.0;      dp_dx[2][9] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = -1.0;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      dp_dx[3][9] = 0.0;      
    dp_dx[4][0] = x[5] + x[2] - 1.0;      dp_dx[4][1] = x[9];      dp_dx[4][2] = x[0] - 1.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = x[0] - 1.0;      dp_dx[4][6] = x[9];      dp_dx[4][7] = x[9];      dp_dx[4][8] = -1.5;      dp_dx[4][9] = x[6] + x[7] + x[1] - 1.0;      
    dp_dx[5][0] = x[5] - x[6] - x[7] - x[1] + x[2] + 1.0;      dp_dx[5][1] = 2.0*x[9] - x[0];      dp_dx[5][2] = x[0];      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = x[0];      dp_dx[5][6] = 2.0*x[9] - x[0];      dp_dx[5][7] = 2.0*x[9] - x[0];      dp_dx[5][8] = -2.5;      dp_dx[5][9] = 2.0*x[6] + 2.0*x[7] + 2.0*x[1] - 2.0;      
    dp_dx[6][0] = -x[5] - x[2];      dp_dx[6][1] = -x[9];      dp_dx[6][2] = -x[0];      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = -x[0];      dp_dx[6][6] = -x[9];      dp_dx[6][7] = -x[9];      dp_dx[6][8] = 2.5;      dp_dx[6][9] = -x[6] - x[7] - x[1] + 1.0;      
    dp_dx[7][0] = -x[5] + x[6] + x[7] + x[1] - x[2];      dp_dx[7][1] = -2.0*x[9] + x[0];      dp_dx[7][2] = -x[0];      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = -x[0];      dp_dx[7][6] = -2.0*x[9] + x[0];      dp_dx[7][7] = -2.0*x[9] + x[0];      dp_dx[7][8] = 1.5;      dp_dx[7][9] = -2.0*x[6] - 2.0*x[7] - 2.0*x[1] + 2.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 1.0;      dp_dx[8][7] = 0.0;      dp_dx[8][8] = 0.0;      dp_dx[8][9] = 0.0;      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = x[4];      dp_dx[9][4] = x[3];      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = 0.0;      dp_dx[9][9] = 0.0;      
    dp_dx[10][0] = 0.0;      dp_dx[10][1] = 0.0;      dp_dx[10][2] = 0.0;      dp_dx[10][3] = 0.0;      dp_dx[10][4] = 0.0;      dp_dx[10][5] = 0.0;      dp_dx[10][6] = 0.0;      dp_dx[10][7] = 1.0;      dp_dx[10][8] = 0.0;      dp_dx[10][9] = 0.0;      
}


/**
    Update dpdx matrix of ilm
*/
void dpdx_ig_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = 1.0;      dp_dx[0][3] = 0.0;      
    dp_dx[1][0] = 1.0 - x[1];      dp_dx[1][1] = - x[0];      dp_dx[1][2] = -1.0;      dp_dx[1][3] = 0.0;      
    dp_dx[2][0] = -1.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = -1.0;      dp_dx[3][3] = 1.0;      
    dp_dx[4][0] = x[1];      dp_dx[4][1] = x[0];      dp_dx[4][2] = 1.0;      dp_dx[4][3] = -1.0;      
}


/**
    Update dpdx matrix of liqHw
*/
void dpdx_ig_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -0.75*x[9] - 1.0;      dp_dx[0][1] = -0.75*x[9] - 1.0;      dp_dx[0][2] = -0.75*x[9] - 1.0;      dp_dx[0][3] = -0.75*x[9] - 1.0;      dp_dx[0][4] = -0.75*x[9] - 1.0;      dp_dx[0][5] = -0.75*x[9] - 1.0;      dp_dx[0][6] = -0.75*x[9] - 1.0;      dp_dx[0][7] = -0.75*x[9] - 1.0;      dp_dx[0][8] = -0.75*x[9] - 1.0;      dp_dx[0][9] = -0.75*x[6] - 0.75*x[3] - 0.75*x[2] - 0.75*x[10] - 0.75*x[5] - 0.75*x[4] - 0.75*x[8] - 0.75*x[1] - 0.75*x[7] - 0.75*x[0] + 1.0;      dp_dx[0][10] = -0.75*x[9] - 1.0;      
    dp_dx[1][0] = 0.0;      dp_dx[1][1] = 0.75*x[9] + 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      dp_dx[1][7] = 0.0;      dp_dx[1][8] = 0.0;      dp_dx[1][9] = 0.75*x[1] - 1.0;      dp_dx[1][10] = 0.0;      
    dp_dx[2][0] = 0.75*x[9] + 1.0;      dp_dx[2][1] = 0.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 0.0;      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 0.0;      dp_dx[2][8] = 0.0;      dp_dx[2][9] = 0.75*x[0] - 1.0;      dp_dx[2][10] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.75*x[9] + 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      dp_dx[3][7] = 0.0;      dp_dx[3][8] = 0.0;      dp_dx[3][9] = 0.75*x[2];      dp_dx[3][10] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.75*x[9] + 1.0;      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = 0.0;      dp_dx[4][7] = 0.0;      dp_dx[4][8] = 0.0;      dp_dx[4][9] = 0.75*x[3];      dp_dx[4][10] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.75*x[9] + 1.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 0.0;      dp_dx[5][7] = 0.0;      dp_dx[5][8] = 0.0;      dp_dx[5][9] = 0.75*x[4];      dp_dx[5][10] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.75*x[9] + 1.0;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      dp_dx[6][8] = 0.0;      dp_dx[6][9] = 0.75*x[5];      dp_dx[6][10] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.75*x[9] + 1.0;      dp_dx[7][7] = 0.0;      dp_dx[7][8] = 0.0;      dp_dx[7][9] = 0.75*x[6];      dp_dx[7][10] = 0.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = 0.75*x[9] + 1.0;      dp_dx[8][8] = 0.0;      dp_dx[8][9] = 0.75*x[7];      dp_dx[8][10] = 0.0;      
    dp_dx[9][0] = 0.0;      dp_dx[9][1] = 0.0;      dp_dx[9][2] = 0.0;      dp_dx[9][3] = 0.0;      dp_dx[9][4] = 0.0;      dp_dx[9][5] = 0.0;      dp_dx[9][6] = 0.0;      dp_dx[9][7] = 0.0;      dp_dx[9][8] = 0.75*x[9] + 1.0;      dp_dx[9][9] = 0.75*x[8];      dp_dx[9][10] = 0.0;      
    dp_dx[10][0] = 0.0;      dp_dx[10][1] = 0.0;      dp_dx[10][2] = 0.0;      dp_dx[10][3] = 0.0;      dp_dx[10][4] = 0.0;      dp_dx[10][5] = 0.0;      dp_dx[10][6] = 0.0;      dp_dx[10][7] = 0.0;      dp_dx[10][8] = 0.0;      dp_dx[10][9] = 1.0;      dp_dx[10][10] = 0.0;      
    dp_dx[11][0] = 0.0;      dp_dx[11][1] = 0.0;      dp_dx[11][2] = 0.0;      dp_dx[11][3] = 0.0;      dp_dx[11][4] = 0.0;      dp_dx[11][5] = 0.0;      dp_dx[11][6] = 0.0;      dp_dx[11][7] = 0.0;      dp_dx[11][8] = 0.0;      dp_dx[11][9] = 0.75*x[10];      dp_dx[11][10] = 0.75*x[9] + 1.0;      
}
/** 
  update dpdpx matrix (muscovite)
*/ 
void dpdx_ig_mu(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -1.0;      dp_dx[0][4] = -1.0;      
    dp_dx[1][0] = x[1] - 1.0;      dp_dx[1][1] = x[0] - 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      
    dp_dx[2][0] = 1.0 - x[1];      dp_dx[2][1] = -x[0];      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 1.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 1.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 1.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      
}

/** 
  update dpdpx matrix (olivine)
*/
void dpdx_ig_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.0;      dp_dx[0][2] = 0.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = -1.0;      
    dp_dx[2][0] = x[1] - 1.0;      dp_dx[2][1] = x[0] - 1.0;      dp_dx[2][2] = -1.0;      
    dp_dx[3][0] = -x[1];      dp_dx[3][1] = -x[0];      dp_dx[3][2] = 2.0;      
}

/** 
  update dpdpx matrix (orthopyroxene)
*/
void dpdx_ig_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[2] + x[7] - 1.0;      dp_dx[0][1] = -x[3] - 1.0;      dp_dx[0][2] = x[0] - 1.0;      dp_dx[0][3] = -x[7] + x[5] - x[1] + 1.0;      dp_dx[0][4] = 0.0;      dp_dx[0][5] = x[3];      dp_dx[0][6] = 0.0;      dp_dx[0][7] = -x[3] + x[0] - 1.0;      
    dp_dx[1][0] = -x[7] + x[5] - x[1] + 1.0;      dp_dx[1][1] = -x[3] - x[0];      dp_dx[1][2] = 0.0;      dp_dx[1][3] = -x[7] + x[5] - x[1] + 1.0;      dp_dx[1][4] = 0.0;      dp_dx[1][5] = x[3] + x[0];      dp_dx[1][6] = 0.0;      dp_dx[1][7] = -x[3] - x[0];      
    dp_dx[2][0] = -x[2] - x[5] + x[1];      dp_dx[2][1] = 2.0*x[3] + x[0];      dp_dx[2][2] = -x[0];      dp_dx[2][3] = 2.0*x[7] - 2.0*x[5] + 2.0*x[1] - 2.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = -2.0*x[3] - x[0];      dp_dx[2][6] = 0.0;      dp_dx[2][7] = 2.0*x[3];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = 0.0;      dp_dx[3][6] = 0.0;      dp_dx[3][7] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 1.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = -1.0;      dp_dx[4][5] = -2.0;      dp_dx[4][6] = -1.0;      dp_dx[4][7] = 0.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 0.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 1.0;      dp_dx[5][7] = 0.0;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 0.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 2.0;      dp_dx[6][6] = 0.0;      dp_dx[6][7] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 0.0;      dp_dx[7][4] = 1.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      dp_dx[7][7] = 0.0;      
    dp_dx[8][0] = 0.0;      dp_dx[8][1] = 0.0;      dp_dx[8][2] = 0.0;      dp_dx[8][3] = 0.0;      dp_dx[8][4] = 0.0;      dp_dx[8][5] = 0.0;      dp_dx[8][6] = 0.0;      dp_dx[8][7] = 1.0;      
}

/** 
  update dpdpx matrix (plagioclase)
*/
void dpdx_ig_fsp(void *SS_ref_db, const double *x){
	SS_ref *d  = (SS_ref *) SS_ref_db;

	double **dp_dx = d->dp_dx;

	dp_dx[0][0] = -1.0;         dp_dx[0][1] = -1.0;      
	dp_dx[1][0] =  1.0;         dp_dx[1][1] =  0.0;      
	dp_dx[2][0] =  0.0;         dp_dx[2][1] =  1.0;  
}

/** 
  update dpdpx matrix (spinel)
*/
void dpdx_ig_spn(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1./3.*x[3] - 1./3.;      dp_dx[0][1] = 0.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = 1./3. - 1./3.*x[0];      dp_dx[0][4] = 2./3.;      dp_dx[0][5] = 0.0;      dp_dx[0][6] = 0.0;      
    dp_dx[1][0] = -2./3.*x[3] - 2./3.;      dp_dx[1][1] = 0.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 2./3. - 2./3.*x[0];      dp_dx[1][4] = -2./3.;      dp_dx[1][5] = 0.0;      dp_dx[1][6] = 0.0;      
    dp_dx[2][0] = 1./3.*x[3] + 1./3.;      dp_dx[2][1] = 1./3.*x[2] + 1./3.*x[3] - 1./3.;      dp_dx[2][2] = 1./3.*x[1];      dp_dx[2][3] = 1./3.*x[0] + 1./3.*x[1] - 1.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 2./3.;      dp_dx[2][6] = 2./3.;      
    dp_dx[3][0] = 2./3.*x[3] + 2./3.;      dp_dx[3][1] = 2./3.*x[2] + 2./3.*x[3] - 2./3.;      dp_dx[3][2] = 2./3.*x[1];      dp_dx[3][3] = 2./3.*x[0] + 2./3.*x[1] - 1.0;      dp_dx[3][4] = 0.0;      dp_dx[3][5] = -2./3.;      dp_dx[3][6] = -2./3.;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = -1./3.*x[2] - 1./3.*x[3] + 1./3.;      dp_dx[4][2] = -1./3.*x[1];      dp_dx[4][3] = -1./3.*x[1];      dp_dx[4][4] = 0.0;      dp_dx[4][5] = 0.0;      dp_dx[4][6] = -2./3.;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = -2./3.*x[2] - 2./3.*x[3] + 2./3.;      dp_dx[5][2] = -2./3.*x[1];      dp_dx[5][3] = -2./3.*x[1];      dp_dx[5][4] = 0.0;      dp_dx[5][5] = 0.0;      dp_dx[5][6] = 2./3.;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 1.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      dp_dx[6][6] = 0.0;      
    dp_dx[7][0] = 0.0;      dp_dx[7][1] = 0.0;      dp_dx[7][2] = 0.0;      dp_dx[7][3] = 1.0;      dp_dx[7][4] = 0.0;      dp_dx[7][5] = 0.0;      dp_dx[7][6] = 0.0;      
}


/**
    Update dpdx matrix of ma
*/
void dpdx_ig_ma(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = 0.0;      dp_dx[0][1] = 1.0;      dp_dx[0][2] = -1.0;      dp_dx[0][3] = -1.0;      dp_dx[0][4] = -1.0;      
    dp_dx[1][0] = x[1] - 1.0;      dp_dx[1][1] = x[0] - 1.0;      dp_dx[1][2] = 0.0;      dp_dx[1][3] = 0.0;      dp_dx[1][4] = 0.0;      
    dp_dx[2][0] = 1.0 - 1.0*x[1];      dp_dx[2][1] = -1.0*x[0];      dp_dx[2][2] = 0.0;      dp_dx[2][3] = 0.0;      dp_dx[2][4] = 0.0;      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 0.0;      dp_dx[3][3] = 1.0;      dp_dx[3][4] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 0.0;      dp_dx[4][2] = 0.0;      dp_dx[4][3] = 0.0;      dp_dx[4][4] = 1.0;      
    dp_dx[5][0] = 0.0;      dp_dx[5][1] = 0.0;      dp_dx[5][2] = 1.0;      dp_dx[5][3] = 0.0;      dp_dx[5][4] = 0.0;      
}

/**
    Update dpdx matrix of chl
*/
void dpdx_ig_chl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0*x[1] - 1.0*x[2] - 1.0*x[3];      dp_dx[0][1] = -1.0*x[0] + 0.25*x[4] + 1.25*x[5];      dp_dx[0][2] = -1.0*x[0] + 1.25*x[5];      dp_dx[0][3] = -1.0*x[0] - 0.25*x[4] + 1.25*x[5] + 2.0;      dp_dx[0][4] = 0.25*x[1] - 0.25*x[3] - 0.25;      dp_dx[0][5] = 1.25*x[1] + 1.25*x[2] + 1.25*x[3] - 1.25;      
    dp_dx[1][0] = 3.0*x[1] + 2.0*x[2] + x[3] - 2.0;      dp_dx[1][1] = 3.0*x[0] - 1.25*x[4] - 2.25*x[5] - 1.0;      dp_dx[1][2] = 2.0*x[0] - 2.25*x[5] - 1.0;      dp_dx[1][3] = x[0] + 1.25*x[4] - 2.25*x[5] - 1.0;      dp_dx[1][4] = -1.25*x[1] + 1.25*x[3] + 1.25;      dp_dx[1][5] = -2.25*x[1] - 2.25*x[2] - 2.25*x[3] + 2.25;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      dp_dx[2][2] = 0.0;      dp_dx[2][3] = -1.0;      dp_dx[2][4] = 0.0;      dp_dx[2][5] = 0.0;      
    dp_dx[3][0] = x[1] + x[2] + x[3];      dp_dx[3][1] = x[0] - 0.25*x[4] - 1.25*x[5];      dp_dx[3][2] = x[0] - 1.25*x[5];      dp_dx[3][3] = x[0] + 0.25*x[4] - 1.25*x[5];      dp_dx[3][4] = -0.25*x[1] + 0.25*x[3] + 0.25;      dp_dx[3][5] = -1.25*x[1] - 1.25*x[2] - 1.25*x[3] + 1.25;      
    dp_dx[4][0] = -1.0*x[1] - 1.0*x[2] - 1.0*x[3] + 1.0;      dp_dx[4][1] = -1.0*x[0] + x[5];      dp_dx[4][2] = -1.0*x[0] + x[5];      dp_dx[4][3] = -1.0*x[0] + x[5];      dp_dx[4][4] = 0.0;      dp_dx[4][5] = x[1] + x[2] + x[3] - 1.0;      
    dp_dx[5][0] = -2.0*x[1] - 1.0*x[2] + 1.0;      dp_dx[5][1] = -2.0*x[0] + 1.25*x[4] + 1.25*x[5];      dp_dx[5][2] = -1.0*x[0] + 1.25*x[5];      dp_dx[5][3] = -1.25*x[4] + 1.25*x[5];      dp_dx[5][4] = 1.25*x[1] - 1.25*x[3] - 1.25;      dp_dx[5][5] = 1.25*x[1] + 1.25*x[2] + 1.25*x[3] - 1.25;      
    dp_dx[6][0] = 0.0;      dp_dx[6][1] = 0.0;      dp_dx[6][2] = 1.0;      dp_dx[6][3] = 0.0;      dp_dx[6][4] = 0.0;      dp_dx[6][5] = 0.0;      
}


/**
    Update dpdx matrix of ctd
*/
void dpdx_ig_ctd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      
}


/**
    Update dpdx matrix of car
*/
void dpdx_ig_car(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      dp_dx[0][1] = -1.0;      
    dp_dx[1][0] = 1.0;      dp_dx[1][1] = 0.0;      
    dp_dx[2][0] = 0.0;      dp_dx[2][1] = 1.0;      
}


/**
    Update dpdx matrix of ta
*/
void dpdx_ig_ta(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = x[1] - 1.0;      dp_dx[0][1] = x[0] + x[3] - 2.0;      dp_dx[0][2] = 1.0;      dp_dx[0][3] = x[1] - 1.0;      
    dp_dx[1][0] = 1.0 - 1.0*x[2];      dp_dx[1][1] = 0.5*x[3];      dp_dx[1][2] = -1.0*x[0];      dp_dx[1][3] = 0.5*x[1] - 0.5;      
    dp_dx[2][0] = -1.0*x[1] + x[2];      dp_dx[2][1] = -1.0*x[0] - 1.5*x[3];      dp_dx[2][2] = x[0];      dp_dx[2][3] = 1.5 - 1.5*x[1];      
    dp_dx[3][0] = 0.0;      dp_dx[3][1] = 0.0;      dp_dx[3][2] = 1.0;      dp_dx[3][3] = 0.0;      
    dp_dx[4][0] = 0.0;      dp_dx[4][1] = 2.0;      dp_dx[4][2] = -2.0;      dp_dx[4][3] = 0.0;      
}


/**
    Update dpdx matrix of zoi
*/
void dpdx_ig_zoi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double **dp_dx = d->dp_dx;

    dp_dx[0][0] = -1.0;      
    dp_dx[1][0] = 1.0;      
}





/**
    Endmember fraction of fper_S11
*/
void px_ig_fper(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 - 1.0*x[0];
        p[1]           = x[0];
}

/** 
  update dpdpx matrix (biotite)
*/
void px_ig_bi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -2.*x[4]/3.0 + x[2]*x[0] - x[2] + x[3]*x[0] - x[3] + x[0]*x[1] - x[0] - x[1] + 1.0;
        p[1]           = -x[4]/3.0 + x[0];
        p[2]           = x[4] - x[2]*x[0] - x[3]*x[0] - x[0]*x[1];
        p[3]           = x[1];
        p[4]           = x[3];
        p[5]           = x[2];
}

/** 
  update px matrix (cordierite)
*/
void px_ig_cd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[1] - x[0] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}

/** 
  update px matrix (clinopyroxene)
*/
void px_ig_cpx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[8] - x[3] - x[2] - x[1] + 1.0;
        p[1]           = - x[4]*x[8] - x[4]*x[3] + x[4]*x[7] - x[4]*x[1] + x[4] - x[8]*x[0] - x[3]*x[0] + x[7]*x[0] - x[0]*x[1] + x[0];
        p[2]           = - x[6] - x[5] - 2.0*x[7] + x[1];
        p[3]           = x[6];
        p[4]           = x[5];
        p[5]           = 2.0*x[7];
        p[6]           = x[3];
        p[7]           = - x[4]*x[8] - x[4]*x[3] + x[4]*x[7] - x[4]*x[1] + x[4] - x[2]*x[0] + x[2];
        p[8]           = 2.0*x[4]*x[8] + 2.0*x[4]*x[3] - 2.0*x[4]*x[7] + 2.0*x[4]*x[1] - 2.0*x[4] + x[8]*x[0] + x[3]*x[0] + x[2]*x[0] - x[7]*x[0] + x[0]*x[1] - x[0];
        p[9]           = x[8];
}

/** 
  update px matrix (epidote)
*/
void px_ig_ep(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[1] - x[0] + 1.0;
        p[1]           = 2.0*x[1];
        p[2]           = - x[1] + x[0];
}

/** 
  update px matrix (fluid)
*/
void px_ig_fl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0;
        p[1]           = x[1];
        p[2]           = x[0];
        p[3]           = x[2];
        p[4]           = x[3];
        p[5]           = x[4];
        p[6]           = x[5];
        p[7]           = x[6];
        p[8]           = x[7];
        p[9]           = x[8];
        p[10]           = x[9];
}


/** 
  update px matrix (garnet)
*/
void px_ig_g(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1]*x[0] - x[1] - x[3] - 4.0*x[4] - x[0] + 1.0;
        p[1]           = - x[1]*x[0] + x[0];
        p[2]           = x[1] - x[2];
        p[3]           = x[2];
        p[4]           = x[3];
        p[5]           = 4.0*x[4];
}

/** 
  update px matrix (hornblende)
*/
void px_ig_hb(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -0.5*x[3] + x[5] - x[6] - x[7] - x[1] + x[2];
        p[1]           = -0.5*x[3] + x[6] + x[1] - x[2];
        p[2]           = - x[3]*x[4] + x[3];
        p[3]           = - x[6] + x[2];
        p[4]           = -1.5*x[8] + x[9]*x[6] + x[9]*x[7] + x[9]*x[1] - x[9] + x[5]*x[0] - x[5] + x[0]*x[2] - x[0] - x[2] + 1.0;
        p[5]           = -2.5*x[8] + 2.0*x[9]*x[6] + 2.0*x[9]*x[7] + 2.0*x[9]*x[1] - 2.0*x[9] + x[5]*x[0] - x[6]*x[0] - x[7]*x[0] - x[0]*x[1] + x[0]*x[2] + x[0];
        p[6]           = 2.5*x[8] - x[9]*x[6] - x[9]*x[7] - x[9]*x[1] + x[9] - x[5]*x[0] - x[0]*x[2];
        p[7]           = 1.5*x[8] - 2.0*x[9]*x[6] - 2.0*x[9]*x[7] - 2.0*x[9]*x[1] + 2.0*x[9] - x[5]*x[0] + x[6]*x[0] + x[7]*x[0] + x[0]*x[1] - x[0]*x[2];
        p[8]           = x[6];
        p[9]           = x[3]*x[4];
        p[10]           = x[7];
}

/**
    Endmember fraction of ilm
*/
void px_ig_ilm(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[2];
        p[1]           = - x[0]*x[1] + x[0] - x[2];
        p[2]           = 1.0 - x[0];
        p[3]           = - x[2] + x[3];
        p[4]           = x[0]*x[1] + x[2] - x[3];
}

    
/**
    Endmember fraction of liqHw
*/
void px_ig_liq(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[6] - x[3] - x[2] - x[10] - x[5] - x[4] - x[8] - x[1] - x[7] - x[0] + 0.25*x[9]*(-3.0*x[6] - 3.0*x[3] - 3.0*x[2] - 3.0*x[10] - 3.0*x[5] - 3.0*x[4] - 3.0*x[8] - 3.0*x[1] - 3.0*x[7] - 3.0*x[0] + 4.0) + 1.0;
        p[1]           = 0.75*x[1]*x[9] + x[1] - x[9];
        p[2]           = 0.75*x[0]*x[9] + x[0] - x[9];
        p[3]           = 0.75*x[2]*x[9] + x[2];
        p[4]           = 0.75*x[3]*x[9] + x[3];
        p[5]           = 0.75*x[4]*x[9] + x[4];
        p[6]           = 0.75*x[5]*x[9] + x[5];
        p[7]           = 0.75*x[6]*x[9] + x[6];
        p[8]           = 0.75*x[7]*x[9] + x[7];
        p[9]           = 0.75*x[8]*x[9] + x[8];
        p[10]           = x[9];
        p[11]           = 0.75*x[10]*x[9] + x[10];
}
/** 
  update px matrix (muscovite)
*/
void px_ig_mu(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[4] - x[2] - x[3] + x[1];
        p[1]           = x[0]*x[1] - x[0] - x[1] + 1.0;
        p[2]           = - x[0]*x[1] + x[0];
        p[3]           = x[3];
        p[4]           = x[4];
        p[5]           = x[2];
}

/** 
  update px matrix (olivine)
*/
void px_ig_ol(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1];
        p[1]           = - x[2] + x[0];
        p[2]           = - x[2] + x[1]*x[0] - x[1] - x[0] + 1.0;
        p[3]           = 2.0*x[2] - x[1]*x[0];
}

/** 
  update px matrix (orthopyroxene)
*/
void px_ig_opx(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[3]*x[7] + x[3]*x[5] - x[3]*x[1] + x[3] + x[2]*x[0] - x[2] + x[7]*x[0] - x[7] - x[0] - x[1] + 1.0;
        p[1]           = - x[3]*x[7] + x[3]*x[5] - x[3]*x[1] + x[3] - x[7]*x[0] + x[5]*x[0] - x[0]*x[1] + x[0];
        p[2]           = 2.0*x[3]*x[7] - 2.0*x[3]*x[5] + 2.0*x[3]*x[1] - 2.0*x[3] - x[2]*x[0] - x[5]*x[0] + x[0]*x[1];
        p[3]           = x[2];
        p[4]           = - x[6] - x[4] - 2.0*x[5] + x[1];
        p[5]           = x[6];
        p[6]           = 2.0*x[5];
        p[7]           = x[4];
        p[8]           = x[7];
}

/** 
  update px matrix (plagioclase 4T)
*/
void px_ig_fsp(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = - x[0] - x[1] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}

/** 
  update px matrix (spinel)
*/
void px_ig_spn(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -1./3.*x[0]*x[3] - 1./3.*x[0] -x[2] + 1./3.*x[3] + 2./3.*x[4] + 1./3.;
        p[1]           = -2./3.*x[0]*x[3] - 2./3.*x[0] + 2./3.*x[3] - 2./3.*x[4] + 2./3.;
        p[2]           = 1./3.*x[0]*x[3] + 1./3.*x[0] + 1./3.*x[1]*x[2] + 1./3.*x[1]*x[3] - 1./3.*x[1] -x[3] + 2./3.*x[5] + 2./3.*x[6];
        p[3]           = 2./3.*x[0]*x[3] + 2./3.*x[0] + 2./3.*x[1]*x[2] + 2./3.*x[1]*x[3] - 2./3.*x[1] -x[3] - 2./3.*x[5] - 2./3.*x[6];
        p[4]           = -1./3.*x[1]*x[2] - 1./3.*x[1]*x[3] + 1./3.*x[1] - 2./3.*x[6];
        p[5]           = -2./3.*x[1]*x[2] - 2./3.*x[1]*x[3] + 2./3.*x[1] + 2./3.*x[6];
        p[6]           = x[2];
        p[7]           = x[3];
}

/**
    Endmember fraction of ma
*/
void px_ig_ma(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[1] - 1.0*x[2] - 1.0*x[3] - 1.0*x[4];
        p[1]           = x[0]*x[1] - 1.0*x[0] - 1.0*x[1] + 1.0;
        p[2]           = -1.0*x[0]*x[1] + x[0];
        p[3]           = x[3];
        p[4]           = x[4];
        p[5]           = x[2];
}

  /**
    Endmember fraction of chl
*/
void px_ig_chl(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -1.0*x[0]*x[1] - 1.0*x[0]*x[2] - 1.0*x[0]*x[3] + 0.25*x[1]*x[4] + 1.25*x[1]*x[5] + 1.25*x[2]*x[5] - 0.25*x[3]*x[4] + 1.25*x[3]*x[5] + 2.0*x[3] - 0.25*x[4] - 1.25*x[5];
        p[1]           = 3.0*x[0]*x[1] + 2.0*x[0]*x[2] + x[0]*x[3] - 2.0*x[0] - 1.25*x[1]*x[4] - 2.25*x[1]*x[5] - 1.0*x[1] - 2.25*x[2]*x[5] - 1.0*x[2] + 1.25*x[3]*x[4] - 2.25*x[3]*x[5] - 1.0*x[3] + 1.25*x[4] + 2.25*x[5] + 1.0;
        p[2]           = x[1] - 1.0*x[3];
        p[3]           = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - 0.25*x[1]*x[4] - 1.25*x[1]*x[5] - 1.25*x[2]*x[5] + 0.25*x[3]*x[4] - 1.25*x[3]*x[5] + 0.25*x[4] + 1.25*x[5];
        p[4]           = -1.0*x[0]*x[1] - 1.0*x[0]*x[2] - 1.0*x[0]*x[3] + x[0] + x[1]*x[5] + x[2]*x[5] + x[3]*x[5] - 1.0*x[5];
        p[5]           = -2.0*x[0]*x[1] - 1.0*x[0]*x[2] + x[0] + 1.25*x[1]*x[4] + 1.25*x[1]*x[5] + 1.25*x[2]*x[5] - 1.25*x[3]*x[4] + 1.25*x[3]*x[5] - 1.25*x[4] - 1.25*x[5];
        p[6]           = x[2];
}

    
/**
    Endmember fraction of ctd
*/
void px_ig_ctd(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -x[0] - x[1] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}

    
/**
    Endmember fraction of car
*/
void px_ig_car(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = -1.0*x[0] - 1.0*x[1] + 1.0;
        p[1]           = x[0];
        p[2]           = x[1];
}

    
/**
    Endmember fraction of ta
*/
void px_ig_ta(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = x[0]*x[1] - 1.0*x[0] + x[1]*x[3] - 2.0*x[1] + x[2] - 1.0*x[3] + 1.0;
        p[1]           = -1.0*x[0]*x[2] + x[0] + 0.5*x[1]*x[3] - 0.5*x[3];
        p[2]           = -1.0*x[0]*x[1] + x[0]*x[2] - 1.5*x[1]*x[3] + 1.5*x[3];
        p[3]           = x[2];
        p[4]           = 2.0*x[1] - 2.0*x[2];
}

    
/**
    Endmember fraction of zoi
*/
void px_ig_zoi(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p = d->p;
        p[0]           = 1.0 - 1.0*x[0];
        p[1]           = x[0];
}




 
/**
    Objective function of fper_S11
*/
double obj_ig_fper(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_ig_fper(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = 1.0*x[0];
    sf[1]          = 1.0 - x[0];
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[1])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0])) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_fper(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

/** 
  objective function of biotite
*/
double obj_ig_bi(unsigned  n, const double *x, double *grad, void *SS_ref_db) {
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_bi(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0]*x[1] + x[0]*x[2] + x[0]*x[3] - x[0] - x[1] - x[2] - x[3] - 2.0/3.0*x[4] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[2] - x[0]*x[3] + x[0] + 2.0/3.0*x[4];
    sf[2]          = x[2];
    sf[3]          = x[3];
    sf[4]          = x[1];
    sf[5]          = -x[0] + 1.0/3.0*x[4] + 1.0;
    sf[6]          = x[0] - 1.0/3.0*x[4];
    sf[7]          = -0.5*x[1] - 0.5*x[2] + 0.5;
    sf[8]          = 0.5*x[1] + 0.5*x[2] + 0.5;
    sf[9]          = 1.0 - x[3];
    sf[10]          = x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(4.0*sf[0]*cpow(sf[5], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(4.0*sf[1]*cpow(sf[6], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(4.0*sf[1]*cpow(sf[5], 2.0)*sf[7]*sf[8]*cpow(sf[9], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[4]*cpow(sf[5], 2.0)*cpow(sf[8], 2.0)*cpow(sf[9], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(4.0*cpow(sf[10], 2.0)*sf[3]*cpow(sf[5], 2.0)*sf[7]*sf[8])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[2]*cpow(sf[5], 2.0)*cpow(sf[8], 2.0)*cpow(sf[9], 2.0) + d_em[5])) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_bi(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
};

/** 
  objective function of cordierite
*/
double obj_ig_cd(unsigned  n, const double *x, double *grad, void *SS_ref_db) {

	SS_ref *d  = (SS_ref *) SS_ref_db;


	int n_em   = d->n_em;
	double P   = d->P;
	double T   = d->T;
	double R   = d->R;

	double *gb     = d->gb_lvl;
	double *mu_Gex = d->mu_Gex;
	double *sf     = d->sf;
	double *mu     = d->mu;

	px_ig_cd(SS_ref_db,x);

	for (int i = 0; i < d->n_em; i++){
		mu_Gex[i] = 0.0;
		int it = 0;
		for (int j = 0; j < d->n_xeos; j++){
			for (int k = j+1; k < d->n_em; k++){
				mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
				it += 1;
			}
		}
	}
	
    sf[0]           = x[0];
    sf[1]           = 1.0 - x[0];
    sf[2]           = x[1];
    sf[3]           = 1.0 - x[1];
    
	mu[0]            = R*T*creal(clog( pow(sf[1], 2.0)*sf[3])) + gb[0]  + mu_Gex[0];
	mu[1]            = R*T*creal(clog( pow(sf[0], 2.0)*sf[3])) + gb[1]  + mu_Gex[1];
	mu[2]            = R*T*creal(clog( pow(sf[1], 2.0)*sf[2])) + gb[2]  + mu_Gex[2];

	d->sum_apep = 0.0;
	for (int i = 0; i < n_em; i++){
	   d->sum_apep += d->ape[i]*d->p[i];
	}
	d->factor = d->fbc/d->sum_apep;

	d->df_raw = 0.0;
	for (int i = 0; i < d->n_em; i++){
		d->df_raw += mu[i]*d->p[i];
	}
	d->df = d->df_raw * d->factor;
	
	if (grad){
	double *dfx    = d->dfx;
	double **dp_dx = d->dp_dx;
		dpdx_ig_cd(SS_ref_db,x);
		for (int i = 0; i < (d->n_xeos); i++){
		   dfx[i] = 0.0;
		   for (int j = 0; j < n_em; j++){
			   dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
		   }
		   grad[i] = creal(dfx[i]);
		}
	}

	return d->df;
};

/** 
  objective function of clinopyroxene
*/
double obj_ig_cpx(unsigned n, const double *x, double *grad, void *SS_ref_db) {
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_cpx(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0]*x[1] + x[0]*x[3] - x[0]*x[7] + x[0]*x[8] - x[0] + x[1]*x[4] - x[1] + x[3]*x[4] - x[3] - x[4]*x[7] + x[4]*x[8] - x[4] + x[7] - x[8] + 1.0;
    sf[1]          = -x[0]*x[1] - x[0]*x[3] + x[0]*x[7] - x[0]*x[8] + x[0] - x[1]*x[4] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
    sf[2]          = x[1] + x[3] - x[5] - x[6] - 2.0*x[7] + x[8];
    sf[3]          = x[5];
    sf[4]          = x[6];
    sf[5]          = x[7];
    sf[6]          = -x[0]*x[2] - x[1]*x[4] + x[2] - x[3]*x[4] + x[4]*x[7] - x[4]*x[8] + x[4];
    sf[7]          = x[0]*x[2] + x[1]*x[4] + x[3]*x[4] - x[4]*x[7] + x[4]*x[8] - x[4];
    sf[8]          = -x[2] - x[3] - x[8] + 1.0;
    sf[9]          = x[3];
    sf[10]          = x[8];
    sf[11]          = 1.0 - 0.5*x[1];
    sf[12]          = 0.5*x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*csqrt(sf[11])*sf[8])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(csqrt(sf[11])*sf[1]*sf[7])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(1.4142*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*sf[2]*sf[8])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(1.4142*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*sf[4]*sf[8] + d_em[3])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(1.4142*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*sf[3]*sf[8] + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(2.8284*csqrt(sf[0])*cpow(sf[11], 0.25)*cpow(sf[12], 0.25)*csqrt(sf[5])*sf[8])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(csqrt(sf[11])*sf[2]*sf[9])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(sf[0]*csqrt(sf[11])*sf[6])) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(sf[0]*csqrt(sf[11])*sf[7])) + mu_Gex[8];
    mu[9]          = gb[9] + R*T*creal(clog(sf[10]*csqrt(sf[11])*sf[2])) + mu_Gex[9];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_cpx(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

/** 
  objective function of epidote
*/
double obj_ig_ep(unsigned  n, const double *x, double *grad, void *SS_ref_db) {
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_ep(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = x[0] - x[1];
    sf[1]          = -x[0] + x[1] + 1.0;
    sf[2]          = x[0] + x[1];
    sf[3]          = -x[0] - x[1] + 1.0;
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[1]*sf[3])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[1]*sf[2] + d_em[1])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[2] + d_em[2])) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_ep(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
};

/** 
  objective function of fluid
*/
double obj_ig_fl(unsigned  n, const double *x, double *grad, void *SS_ref_db) {
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_fl(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = -x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] + 1.0;
    sf[1]          = x[1];
    sf[2]          = x[0];
    sf[3]          = x[2];
    sf[4]          = x[3];
    sf[5]          = x[4];
    sf[6]          = x[5];
    sf[7]          = x[6];
    sf[8]          = x[7];
    sf[9]          = x[8];
    sf[10]          = x[9];
    sf[11]          = 1.0 - x[9];
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[11])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[11]*sf[1])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[11]*sf[2])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[11]*sf[3])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[11]*sf[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[11]*sf[5])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(sf[11]*sf[6]+d_em[6])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(sf[11]*sf[7]+d_em[7])) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(sf[11]*sf[8])) + mu_Gex[8];
    mu[9]          = gb[9] + R*T*creal(clog(sf[11]*sf[9])) + mu_Gex[9];
    mu[10]          = gb[10] + R*T*creal(clog(cpow(sf[10], 2.0))) + mu_Gex[10];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_fl(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

/** 
  objective function of garnet
*/
double obj_ig_g(unsigned   n, const double *x, double *grad, void *SS_ref_db) {
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_g(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[1]          = -x[0]*x[1] + x[0];
    sf[2]          = x[1];
    sf[3]          = -x[2] - x[3] - 2.0*x[4] + 1.0;
    sf[4]          = x[3];
    sf[5]          = x[2];
    sf[6]          = x[4];
    sf[7]          = x[4];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(cpow(sf[0], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(cpow(sf[1], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[2], 3.0)*cpow(sf[3], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(cpow(sf[2], 3.0)*cpow(sf[5], 2.0) + d_em[3])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(cpow(sf[0], 3.0)*cpow(sf[4], 2.0) + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(8.0*cpow(sf[0], 3.0)*sf[3]*csqrt(sf[6])*csqrt(sf[7]))) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_g(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

/** 
  objective function of hornblende
*/
double obj_ig_hb(unsigned  n, const double *x, double *grad, void *SS_ref_db) {
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_hb(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = 1.0 - x[3];
    sf[1]          = -x[3]*x[4] + x[3];
    sf[2]          = x[3]*x[4];
    sf[3]          = -x[0] + x[8] + 1.0;
    sf[4]          = x[0] - x[8];
    sf[5]          = x[0]*x[1] + x[0]*x[6] + x[0]*x[7] - x[0] - x[1]*x[9] - x[1] - x[6]*x[9] - x[6] - x[7]*x[9] - x[7] + x[9] + 1.0;
    sf[6]          = -x[0]*x[1] - x[0]*x[6] - x[0]*x[7] + x[0] + x[1]*x[9] + x[6]*x[9] + x[7]*x[9] - x[9];
    sf[7]          = x[1];
    sf[8]          = x[6];
    sf[9]          = x[7];
    sf[10]          = x[5];
    sf[11]          = x[0]*x[2] + x[0]*x[5] - x[0] + x[1]*x[9] - x[2] - x[5] + x[6]*x[9] + x[7]*x[9] - 1.5*x[8] - x[9] + 1.0;
    sf[12]          = -x[0]*x[2] - x[0]*x[5] + x[0] - x[1]*x[9] - x[6]*x[9] - x[7]*x[9] + 1.5*x[8] + x[9];
    sf[13]          = x[2];
    sf[14]          = -0.5*x[1] + 0.5*x[2] - 0.25*x[3] - 0.5*x[6] - 0.5*x[7] + 1.0;
    sf[15]          = 0.5*x[1] - 0.5*x[2] + 0.25*x[3] + 0.5*x[6] + 0.5*x[7];
    sf[16]          = 1.0 - x[7];
    sf[17]          = x[7];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*cpow(sf[10], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[0]*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[7], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(8.0*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*sf[1]*cpow(sf[3], 3.0)*sf[5]*sf[7])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*cpow(sf[13], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[7], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[0]*cpow(sf[11], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[4], 3.0)*cpow(sf[6], 2.0))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[6], 2.0))) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(sf[0]*cpow(sf[12], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[4], 3.0)*cpow(sf[5], 2.0))) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(sf[0]*cpow(sf[13], 2.0)*sf[14]*cpow(sf[16], 2.0)*cpow(sf[3], 3.0)*cpow(sf[8], 2.0) + d_em[8])) + mu_Gex[8];
    mu[9]          = gb[9] + R*T*creal(clog(8.0*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[16], 2.0)*sf[2]*cpow(sf[3], 3.0)*sf[5]*sf[7])) + mu_Gex[9];
    mu[10]         = gb[10] + R*T*creal(clog(2.0*sf[0]*cpow(sf[10], 2.0)*csqrt(sf[14])*csqrt(sf[15])*cpow(sf[17], 2.0)*cpow(sf[3], 3.0)*cpow(sf[9], 2.0))) + mu_Gex[10];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_hb(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

   
/**
    Objective function of ilm
*/
double obj_ig_ilm(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_ilm(SS_ref_db,x);

    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->p[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }   
  
    sf[0]          = -0.5*x[0]*x[1] + 0.5*x[0] + 0.5*x[2];
    sf[1]          = 0.5*x[0] - 0.5*x[3];
    sf[2]          = 1.0 - x[0];
    sf[3]          = 0.5*x[0]*x[1] - 0.5*x[2] + 0.5*x[3];
    sf[4]          = -0.5*x[0]*x[1] + 0.5*x[0] - 0.5*x[2];
    sf[5]          = 0.5*x[0] + 0.5*x[3];
    sf[6]          = 1.0 - x[0];
    sf[7]          = 0.5*x[0]*x[1] + 0.5*x[2] - 0.5*x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(csqrt(sf[0])*csqrt(sf[5]))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*cpow(sf[0], 0.25)*cpow(sf[1], 0.25)*cpow(sf[4], 0.25)*cpow(sf[5], 0.25))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(csqrt(sf[2])*csqrt(sf[6]) + d_em[2])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(csqrt(sf[3])*csqrt(sf[5]))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(2.0*cpow(sf[1], 0.25)*cpow(sf[3], 0.25)*cpow(sf[5], 0.25)*cpow(sf[7], 0.25))) + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_ilm(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    

   
/**
    Objective function of liqHw
*/
double obj_ig_liq(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_liq(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = - x[6] - x[3] - x[2] - x[10] - x[5] - x[4] - x[8] - x[1] - x[7] - x[0] + 0.25*x[9]*(-3.0*x[6] - 3.0*x[3] - 3.0*x[2] - 3.0*x[10] - 3.0*x[5] - 3.0*x[4] - 3.0*x[8] - 3.0*x[1] - 3.0*x[7] - 3.0*x[0] + 4.0) + 1.0;
    sf[1]          = 0.75*x[1]*x[9] + x[1] - x[9];
    sf[2]          = 0.75*x[0]*x[9] + x[0] - x[9];
    sf[3]          = 0.75*x[4]*x[9] + x[4];
    sf[4]          = 0.75*x[5]*x[9] + x[5];
    sf[5]          = 0.75*x[6]*x[9] + x[6];
    sf[6]          = 0.75*x[7]*x[9] + x[7];
    sf[7]          = 0.75*x[8]*x[9] + x[8];
    sf[8]          = x[9];
    sf[9]          = x[3] + x[2] + 0.75*x[9]*(x[3] + x[2]);
    sf[10]          = -0.75*x[10]*x[9] - x[10] + 1.0;
    sf[11]          = 4.0*x[2]*(0.75*x[9] + 1.0);
    sf[12]          = 4.0*x[3]*(0.75*x[9] + 1.0);
    sf[13]          = x[0]*(0.75*x[9] + 1.0) - x[9];
    sf[14]          = x[1]*(0.75*x[9] + 1.0) - x[9];
    sf[15]          = -2.0*x[9] + (0.75*x[9] + 1.0)*(4.0*x[3] + 4.0*x[2] + x[1] + x[0]);
    sf[16]          = x[10]*(0.75*x[9] + 1.0);
    sf[17]          = -0.75*x[10]*x[9] - x[10] + 1.0;
    
    
    mu[0]          = R*T*creal(clog(sf[0]*1.0/sf[10]*cpow(sf[17], 2.0))) + gb[0] + mu_Gex[0];
    mu[1]          = R*T*creal(clog(sf[14]*sf[1]*1.0/sf[15]*1.0/sf[10]*cpow(sf[17], 2.0))) + gb[1] + mu_Gex[1];
    mu[2]          = R*T*creal(clog(sf[13]*sf[2]*1.0/sf[15]*1.0/sf[10]*cpow(sf[17], 2.0))) + gb[2] + mu_Gex[2];
    mu[3]          = R*T*creal(clog(cpow(sf[11], 4.0)*sf[9]*cpow(sf[15], -4.0)*1.0/sf[10]*cpow(sf[17], 2.0))) + gb[3] + mu_Gex[3];
    mu[4]          = R*T*creal(clog(cpow(sf[12], 4.0)*sf[9]*cpow(sf[15], -4.0)*1.0/sf[10]*cpow(sf[17], 2.0))) + gb[4] + mu_Gex[4];
    mu[5]          = R*T*creal(clog(sf[3]*1.0/sf[10]*cpow(sf[17], 2.0))) + gb[5] + mu_Gex[5];
    mu[6]          = R*T*creal(clog(sf[4]*1.0/sf[10]*cpow(sf[17], 2.0) + d_em[6])) + gb[6] + mu_Gex[6];
    mu[7]          = R*T*creal(clog(sf[5]*1.0/sf[10]*cpow(sf[17], 2.0) + d_em[7])) + gb[7] + mu_Gex[7];
    mu[8]          = R*T*creal(clog(sf[6]*1.0/sf[10]*cpow(sf[17], 2.0))) + gb[8] + mu_Gex[8];
    mu[9]          = R*T*creal(clog(sf[7]*1.0/sf[10]*cpow(sf[17], 2.0))) + gb[9] + mu_Gex[9];
    mu[10]          = R*T*creal(clog(sf[8]*1.0/sf[10]*cpow(sf[17], 2.0))) + gb[10] + mu_Gex[10];
    mu[11]          = R*T*creal(clog(cpow(sf[16], 2.0) +  d_em[11])) + gb[11] + mu_Gex[11];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_liq(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}   


/** 
  objective function of muscovite
*/
double obj_ig_mu(unsigned  n, const double *x, double *grad, void *SS_ref_db) {

	SS_ref *d  = (SS_ref *) SS_ref_db;


	int n_em   = d->n_em;
	double P   = d->P;
	double T   = d->T;
	double R   = d->R;

	double *gb     = d->gb_lvl;
	double *mat_phi= d->mat_phi;
	double *mu_Gex = d->mu_Gex;
	double *sf     = d->sf;
	double *mu     = d->mu;

	px_ig_mu(SS_ref_db,x);

	d->sum_v = 0.0;
	for (int i = 0; i < d->n_em; i++){
		d->sum_v += d->p[i]*d->v[i];
	}
	for (int i = 0; i < d->n_em; i++){
		d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
	}

	for (int i = 0; i < d->n_em; i++){
		mu_Gex[i] = 0.0;
		int it = 0;
		for (int j = 0; j < d->n_xeos; j++){
			for (int k = j+1; k < d->n_em; k++){
				mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
				it += 1;
			}
		}
	}
	
    sf[0]           = -x[4] - x[3] + 1.0;
    sf[1]           = x[3];
    sf[2]           = x[4];
    sf[3]           = x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[4]           = -x[0]*x[1] + x[0];
    sf[5]           = x[1];
    sf[6]           = 1.0 - x[2];
    sf[7]           = x[2];
    sf[8]           = -0.5*x[4] - 0.5*x[1] + 1.0;
    sf[9]           = 0.5*x[4] + 0.5*x[1];
	
	mu[0]          = R*T*creal(clog(4.0*sf[0]*sf[5]*sf[6]*sf[8]*sf[9]))  + gb[0] + mu_Gex[0];
	mu[1]          = R*T*creal(clog(sf[0]*sf[3]*sf[6]*cpow(sf[8], 2.0))) + gb[1] + mu_Gex[1];
	mu[2]          = R*T*creal(clog(sf[0]*sf[4]*sf[6]*cpow(sf[8], 2.0))) + gb[2] + mu_Gex[2];
	mu[3]          = R*T*creal(clog(4.0*sf[1]*sf[5]*sf[6]*sf[8]*sf[9]))  + gb[3] + mu_Gex[3];
	mu[4]          = R*T*creal(clog(sf[2]*sf[5]*sf[6]*cpow(sf[9], 2.0))) + gb[4] + mu_Gex[4];
	mu[5]          = R*T*creal(clog(4.0*sf[0]*sf[5]*sf[7]*sf[8]*sf[9]))  + gb[5] + mu_Gex[5];

	d->sum_apep = 0.0;
	for (int i = 0; i < n_em; i++){
	   d->sum_apep += d->ape[i]*d->p[i];
	}
	d->factor = d->fbc/d->sum_apep;

	d->df_raw = 0.0;
	for (int i = 0; i < d->n_em; i++){
		d->df_raw += mu[i]*d->p[i];
	}
	d->df = d->df_raw * d->factor;
	
	if (grad){
	double *dfx    = d->dfx;
	double **dp_dx = d->dp_dx;
		dpdx_ig_mu(SS_ref_db,x);
		for (int i = 0; i < (d->n_xeos); i++){
		   dfx[i] = 0.0;
		   for (int j = 0; j < n_em; j++){
			   dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
		   }
		   grad[i] = creal(dfx[i]);
		}
	}

	return d->df;
};

/** 
  objective function of olivine
*/
double obj_ig_ol(unsigned  n, const double *x, double *grad, void *SS_ref_db) {

	SS_ref *d  = (SS_ref *) SS_ref_db;


	int n_em   = d->n_em;
	double P   = d->P;
	double T   = d->T;
	double R   = d->R;

	double *gb     = d->gb_lvl;
	double *mat_phi= d->mat_phi;
	double *mu_Gex = d->mu_Gex;
	double *sf     = d->sf;
	double *mu     = d->mu;

	px_ig_ol(SS_ref_db,x);

	for (int i = 0; i < d->n_em; i++){
		mu_Gex[i] = 0.0;
		int it = 0;
		for (int j = 0; j < d->n_xeos; j++){
			for (int k = j+1; k < d->n_em; k++){
				mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
				it += 1;
			}
		}
	}

    sf[0]          =  x[2] - x[0] + 1.0;
    sf[1]          = -x[2] + x[0];
    sf[2]          =  x[1]*x[0] - x[1] - x[2] - x[0] + 1.0;
    sf[3]          = -x[1]*x[0] + x[2] + x[0];
    sf[4]          =  x[1];
    
	mu[0]          = R*T*creal(clog(sf[0]*sf[4])) + gb[0] + mu_Gex[0];
	mu[1]          = R*T*creal(clog(sf[1]*sf[3])) + gb[1] + mu_Gex[1];
	mu[2]          = R*T*creal(clog(sf[0]*sf[2])) + gb[2] + mu_Gex[2];
	mu[3]          = R*T*creal(clog(sf[0]*sf[3])) + gb[3] + mu_Gex[3];

	d->sum_apep = 0.0;
	for (int i = 0; i < n_em; i++){
	   d->sum_apep += d->ape[i]*d->p[i];
	}
	d->factor = d->fbc/d->sum_apep;

	d->df_raw = 0.0;
	for (int i = 0; i < d->n_em; i++){
		d->df_raw += mu[i]*d->p[i];
	}
	d->df = d->df_raw * d->factor;
	
	if (grad){
	double *dfx    = d->dfx;
	double **dp_dx = d->dp_dx;
		dpdx_ig_ol(SS_ref_db,x);
		for (int i = 0; i < (d->n_xeos); i++){
		   dfx[i] = 0.0;
		   for (int j = 0; j < n_em; j++){
			   dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
		   }
		   grad[i] = creal(dfx[i]);
		}
	}

	return d->df;
};

/** 
  objective function of orthopyroxene
*/
double obj_ig_opx(unsigned n, const double *x, double *grad, void *SS_ref_db) {
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_opx(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = x[0]*x[1] - x[0]*x[5] + x[0]*x[7] - x[0] + x[1]*x[3] - x[1] - x[3]*x[5] + x[3]*x[7] - x[3] + x[5] - x[7] + 1.0;
    sf[1]          = -x[0]*x[1] + x[0]*x[5] - x[0]*x[7] + x[0] - x[1]*x[3] + x[3]*x[5] - x[3]*x[7] + x[3];
    sf[2]          = x[1] - x[4] - 2.0*x[5] - x[6] + x[7];
    sf[3]          = x[4];
    sf[4]          = x[6];
    sf[5]          = x[5];
    sf[6]          = x[0]*x[2] + x[0]*x[7] - x[0] - x[1]*x[3] - x[2] + x[3]*x[5] - x[3]*x[7] + x[3] - x[7] + 1.0;
    sf[7]          = -x[0]*x[2] - x[0]*x[7] + x[0] + x[1]*x[3] - x[3]*x[5] + x[3]*x[7] - x[3];
    sf[8]          = x[2];
    sf[9]          = x[7];
    sf[10]          = 1.0 - 0.5*x[1];
    sf[11]          = 0.5*x[1];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*csqrt(sf[10])*sf[6])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(csqrt(sf[10])*sf[1]*sf[7])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*csqrt(sf[10])*sf[7])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*csqrt(sf[10])*sf[8])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(1.4142*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*sf[2]*sf[6])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(1.4142*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*sf[4]*sf[6] + d_em[5])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(2.8284*csqrt(sf[0])*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*csqrt(sf[5])*sf[6])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(1.4142*cpow(sf[10], 0.25)*cpow(sf[11], 0.25)*sf[3]*sf[6] + d_em[7])) + mu_Gex[7];
    mu[8]          = gb[8] + R*T*creal(clog(csqrt(sf[10])*sf[2]*sf[9])) + mu_Gex[8];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_opx(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

/** 
  objective function of plagioclase 4T
*/
double obj_ig_fsp(unsigned  n, const double *x, double *grad, void *SS_ref_db) {

	SS_ref *d  = (SS_ref *) SS_ref_db;


	int n_em   = d->n_em;
	double P   = d->P;
	double T   = d->T;
	double R   = d->R;

	double *gb     = d->gb_lvl;
	double *mat_phi= d->mat_phi;
	double *mu_Gex = d->mu_Gex;
	double *sf     = d->sf;
	double *mu     = d->mu;

	px_ig_fsp(SS_ref_db,x);

	d->sum_v = 0.0;
	for (int i = 0; i < d->n_em; i++){
		d->sum_v += d->p[i]*d->v[i];
	}
	for (int i = 0; i < d->n_em; i++){
		d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
	}

	for (int i = 0; i < d->n_em; i++){
		mu_Gex[i] = 0.0;
		int it = 0;
		for (int j = 0; j < d->n_xeos; j++){
			for (int k = j+1; k < d->n_em; k++){
				mu_Gex[i] -= (d->eye[i][j] - d->mat_phi[j])*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
				it += 1;
			}
		}
	}
	
    sf[0]           = -x[0] - x[1] + 1.0;
    sf[1]           = x[0];
    sf[2]           = x[1];
    sf[3]           = 0.25*x[0] + 0.25;
    sf[4]           = 0.75 - 0.25*x[0];

	mu[0]          = R*T*creal(clog(1.7548*sf[0]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) 	+ gb[0] + mu_Gex[0];
	mu[1]          = R*T*creal(clog(2.0*sf[1]*csqrt(sf[3])*csqrt(sf[4]))) 				+ gb[1] + mu_Gex[1];
	mu[2]          = R*T*creal(clog(1.7548*sf[2]*cpow(sf[3], 0.25)*cpow(sf[4], 0.75))) 	+ gb[2] + mu_Gex[2];

	d->sum_apep = 0.0;
	for (int i = 0; i < n_em; i++){
	   d->sum_apep += d->ape[i]*d->p[i];
	}
	d->factor = d->fbc/d->sum_apep;

	d->df_raw = 0.0;
	for (int i = 0; i < d->n_em; i++){
		d->df_raw += mu[i]*d->p[i];
	}
	d->df = d->df_raw * d->factor;
	
	if (grad){
	double *dfx    = d->dfx;
	double **dp_dx = d->dp_dx;
		dpdx_ig_fsp(SS_ref_db,x);
		for (int i = 0; i < (d->n_xeos); i++){
		   dfx[i] = 0.0;
		   for (int j = 0; j < n_em; j++){
			   dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
		   }
		   grad[i] = creal(dfx[i]);
		}
	}

	return d->df;
};

/** 
  objective function of spinel
*/
double obj_ig_spn(unsigned n, const double *x, double *grad, void *SS_ref_db) {
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    double *d_em      = d->d_em;
    px_ig_spn(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < d->n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < d->n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -1.0/3.0*x[0]*x[3] - 1.0/3.0*x[0] + 1.0/3.0*x[3] + 2.0/3.0*x[4] + 1.0/3.0;
    sf[1]          = 1.0/3.0*x[0]*x[3] + 1.0/3.0*x[0] + 2.0/3.0*x[5];
    sf[2]          = 2.0/3.0*x[1]*x[2] + 2.0/3.0*x[1]*x[3] - 2.0/3.0*x[1] - 1.0/3.0*x[3] - 2.0/3.0*x[4] - 2.0/3.0*x[5] - 2.0/3.0*x[6] + 2.0/3.0;
    sf[3]          = -2.0/3.0*x[1]*x[2] - 2.0/3.0*x[1]*x[3] + 2.0/3.0*x[1] + 2.0/3.0*x[6];
    sf[4]          = -1.0/3.0*x[0]*x[3] - 1.0/3.0*x[0] + 1.0/3.0*x[3] - 1.0/3.0*x[4] + 1.0/3.0;
    sf[5]          = 1.0/3.0*x[0]*x[3] + 1.0/3.0*x[0] - 1.0/3.0*x[5];
    sf[6]          = 2.0/3.0*x[1]*x[2] + 2.0/3.0*x[1]*x[3] - 2.0/3.0*x[1] - x[2] - 5.0/6.0*x[3] + 1.0/3.0*x[4] + 1.0/3.0*x[5] + 1.0/3.0*x[6] + 2.0/3.0;
    sf[7]          = -2.0/3.0*x[1]*x[2] - 2.0/3.0*x[1]*x[3] + 2.0/3.0*x[1] - 1.0/3.0*x[6];
    sf[8]          = x[2];
    sf[9]          = 0.5*x[3];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[6])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(2.0*sf[2]*csqrt(sf[4])*csqrt(sf[6]))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[1]*sf[6])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(2.0*sf[2]*csqrt(sf[5])*csqrt(sf[6]))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[1]*sf[7] + d_em[4])) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(2.0*sf[3]*csqrt(sf[5])*csqrt(sf[7]) + d_em[5])) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(sf[0]*sf[8] + d_em[6])) + mu_Gex[6];
    mu[7]          = gb[7] + R*T*creal(clog(2.0*sf[1]*csqrt(sf[5])*csqrt(sf[9]))) + mu_Gex[7];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_spn(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}


    
/**
    Objective function of ma
*/
double obj_ig_ma(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mat_phi   = d->mat_phi;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_ig_ma(SS_ref_db,x);

    d->sum_v = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_v += d->p[i]*d->v[i];
    }
    for (int i = 0; i < n_em; i++){
        d->mat_phi[i] = (d->p[i]*d->v[i])/d->sum_v;
    }
    
    double tmp = 0.0;
    double Gex = 0.0;
    for (int i = 0; i < n_em; i++){
        Gex = 0.0;
        int it = 0;
        for (int j = 0; j < d->n_xeos; j++){
            tmp = (d->eye[i][j] - d->mat_phi[j]);
            for (int k = j+1; k < n_em; k++){
                Gex -= tmp*(d->eye[i][k] - d->mat_phi[k])*(d->W[it]*2.0*d->v[i]/(d->v[j]+d->v[k]));
                it += 1;
            }
        }
        mu_Gex[i] = Gex;
    }
    
    sf[0]          = -x[3] - x[4] + 1.0;
    sf[1]          = 1.0*x[3];
    sf[2]          = 1.0*x[4];
    sf[3]          = 1.0*x[0]*x[1] - x[0] - x[1] + 1.0;
    sf[4]          = -x[0]*x[1] + 1.0*x[0];
    sf[5]          = 1.0*x[1];
    sf[6]          = 1.0 - x[2];
    sf[7]          = 1.0*x[2];
    sf[8]          = -0.5*x[1] - 0.5*x[4] + 1.0;
    sf[9]          = 0.5*x[1] + 0.5*x[4];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(4.0*sf[0]*sf[5]*sf[6]*sf[8]*sf[9])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*sf[3]*sf[6]*cpow(sf[8], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[0]*sf[4]*sf[6]*cpow(sf[8], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(4.0*sf[1]*sf[5]*sf[6]*sf[8]*sf[9])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[2]*sf[5]*sf[6]*cpow(sf[9], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(4.0*sf[0]*sf[5]*sf[7]*sf[8]*sf[9])) + mu_Gex[5];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_ma(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of chl
*/
double obj_ig_chl(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_ig_chl(SS_ref_db,x);

	for (int i = 0; i < n_em; i++){
		mu_Gex[i] = 0.0;
		int it = 0;
		for (int j = 0; j < d->n_xeos; j++){
			for (int k = j+1; k < n_em; k++){
				mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
				it += 1;
			}
		}
	}
    
    sf[0]          = 1.0*x[0]*x[1] - x[0]*x[3] - x[0] - x[1]*x[4] - x[1] + 1.0*x[3]*x[4] + 1.0*x[3] + 1.0*x[4] + 1.0;
    sf[1]          = -x[0]*x[1] + 1.0*x[0]*x[3] + 1.0*x[0] + 1.0*x[1]*x[4] - x[3]*x[4] - x[4];
    sf[2]          = 1.0*x[1] - x[3];
    sf[3]          = -x[0] + 0.25*x[1]*x[4] + 0.25*x[1]*x[5] + 0.25*x[2]*x[5] - 0.25*x[3]*x[4] + 0.25*x[3]*x[5] - 0.25*x[4] - 0.25*x[5] + 1.0;
    sf[4]          = 1.0*x[0] - 0.25*x[1]*x[4] - 0.25*x[1]*x[5] - 0.25*x[2]*x[5] + 0.25*x[3]*x[4] - 0.25*x[3]*x[5] + 0.25*x[4] + 0.25*x[5];
    sf[5]          = 1.0*x[0]*x[1] + 1.0*x[0]*x[2] + 1.0*x[0]*x[3] - x[0] - x[1]*x[5] - x[1] - x[2]*x[5] - x[2] - x[3]*x[5] - x[3] + 1.0*x[5] + 1.0;
    sf[6]          = -x[0]*x[1] - x[0]*x[2] - x[0]*x[3] + 1.0*x[0] + 1.0*x[1]*x[5] + 1.0*x[2]*x[5] + 1.0*x[3]*x[5] - x[5];
    sf[7]          = 1.0*x[2];
    sf[8]          = 1.0*x[1] + 1.0*x[3];
    sf[9]          = -x[1] - 0.5*x[2] + 1.0;
    sf[10]          = 1.0*x[1] + 0.5*x[2];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(4.0*sf[0]*sf[10]*cpow(sf[3], 4.0)*sf[8]*sf[9])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*cpow(sf[3], 4.0)*sf[5]*cpow(sf[9], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(cpow(sf[10], 2.0)*sf[2]*cpow(sf[3], 4.0)*sf[8])) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(4.0*sf[10]*sf[1]*cpow(sf[4], 4.0)*sf[8]*sf[9])) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(sf[0]*cpow(sf[4], 4.0)*sf[6]*cpow(sf[9], 2.0))) + mu_Gex[4];
    mu[5]          = gb[5] + R*T*creal(clog(sf[1]*cpow(sf[3], 4.0)*sf[5]*cpow(sf[9], 2.0))) + mu_Gex[5];
    mu[6]          = gb[6] + R*T*creal(clog(4.0*sf[0]*sf[10]*cpow(sf[3], 4.0)*sf[7]*sf[9])) + mu_Gex[6];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_chl(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}

    
/**
    Objective function of ctd
*/
double obj_ig_ctd(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_ig_ctd(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = 1.0 - x[1];
    sf[1]          = x[1];
    sf[2]          = 1.0 - x[0];
    sf[3]          = x[0];
    
    mu[0]          = gb[0] + R*T*creal(clog(csqrt(sf[0])*sf[2])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(csqrt(sf[0])*sf[3])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(csqrt(sf[1])*sf[2])) + mu_Gex[2];
 
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_ctd(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of car
*/
double obj_ig_car(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_ig_car(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = 1.0 - x[1];
    sf[1]          = 1.0*x[1];
    sf[2]          = 1.0 - x[0];
    sf[3]          = 1.0*x[0];
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[0]*sf[2])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0]*sf[3])) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[1]*sf[2])) + mu_Gex[2];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_car(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of ta
*/
double obj_ig_ta(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_ig_ta(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = 1.0*x[2];
    sf[1]          = 1.0*x[0]*x[2] - x[0] - 0.5*x[1]*x[3] - x[2] + 0.5*x[3] + 1.0;
    sf[2]          = -x[0]*x[2] + 1.0*x[0] + 0.5*x[1]*x[3] - 0.5*x[3];
    sf[3]          = 1.0*x[0]*x[1] - x[0] + 1.0*x[1]*x[3] - x[1] - x[3] + 1.0;
    sf[4]          = -x[0]*x[1] + 1.0*x[0] - x[1]*x[3] + 1.0*x[3];
    sf[5]          = 1.0*x[1];
    sf[6]          = -x[1] + 1.0*x[2] + 1.0;
    sf[7]          = 1.0*x[1] - x[2];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[1]*cpow(sf[3], 2.0)*cpow(sf[6], 2.0))) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[2]*cpow(sf[4], 2.0)*cpow(sf[6], 2.0))) + mu_Gex[1];
    mu[2]          = gb[2] + R*T*creal(clog(sf[1]*cpow(sf[4], 2.0)*cpow(sf[6], 2.0))) + mu_Gex[2];
    mu[3]          = gb[3] + R*T*creal(clog(sf[0]*cpow(sf[5], 2.0)*cpow(sf[6], 2.0))) + mu_Gex[3];
    mu[4]          = gb[4] + R*T*creal(clog(16.0*sf[1]*sf[3]*sf[5]*sf[6]*sf[7])) + mu_Gex[4];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_ta(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}
    
/**
    Objective function of zoi
*/
double obj_ig_zoi(unsigned n, const double *x, double *grad, void *SS_ref_db){
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *mu_Gex    = d->mu_Gex;
    double *sf        = d->sf;
    double *mu        = d->mu;
    px_ig_zoi(SS_ref_db,x);

    for (int i = 0; i < n_em; i++){
        mu_Gex[i] = 0.0;
        int it    = 0;
        for (int j = 0; j < d->n_xeos; j++){
            for (int k = j+1; k < n_em; k++){
                mu_Gex[i] -= (d->eye[i][j] - d->p[j])*(d->eye[i][k] - d->p[k])*(d->W[it]);
                it += 1;
            }
        }
    }
    
    sf[0]          = 1.0*x[0];
    sf[1]          = 1.0 - x[0];
    
    
    mu[0]          = gb[0] + R*T*creal(clog(sf[1])) + mu_Gex[0];
    mu[1]          = gb[1] + R*T*creal(clog(sf[0])) + mu_Gex[1];
    
    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*d->p[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*d->p[i];
    }
    d->df = d->df_raw * d->factor;

    if (grad){
        double *dfx    = d->dfx;
        double **dp_dx = d->dp_dx;
        dpdx_ig_zoi(SS_ref_db,x);
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i] = 0.0;
            for (int j = 0; j < n_em; j++){
                dfx[i] += (mu[j] - (d->ape[j]/d->sum_apep)*d->df_raw)*d->factor*dp_dx[j][i];
            }
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}




/** 
  objective function for aqueous species
*/
double DebyeHuckel( double* A,
                    double* B,
                    double* azero,
                    double* bgamma,
                    double  TK,
                    double  Pbar,
                    double  charge,
                    double  II,
                    double  density,
                    double  g,
                    double  epsilon,
                    double  xiw       ){
    
    *A     =  1.824829238e6 * sqrt(density)/pow((TK*epsilon),1.5);
    *B     =  50.29158649   * sqrt(density)/sqrt(TK*epsilon);
                    
    // azero in the Debye-Huckel (P-T dependent because g is P-T dependent)
    double nc     =  1.0;
    double na     =  1.0; 
    double ni     =  2.0;
    double zc     =  1.0;
    double za     = -1.0;
    double ac     =  3.72; // Common ion size parameter - NaCl

    double c      =  2.0/ni * (nc * fabs(zc) + na * fabs(za));
    *azero         = ac + c*g;

    /** bgamma in the Debye-Huckel (P-T dependent)
        Calculation - Taken from GEMS line 525 - 589
        units are cal, kg, K, mol, bar */
    double a1     =  0.030056;
    double a2     = -202.55;
    double a3     = -2.9092;
    double a4     =  20302.0;
    double a5     = -0.206;
    double c1     = -1.50;
    double c2     =  53300.0;
    double omg    =  178650.0;
    double bg     = -174.623;
    double bs     =  2.164;
    double rc     =  0.97; // rc - radius of cation at 298 K/1 bar
    double ra     =  1.81; // ra - radius of anion at 298 K/1 bar

    double omgpt  = 1.66027e5*(1.0/(0.94+rc+g)+1.0/(ra+g));

    double nbg    = - ni*bg/2.0+ni*bs*(TK-298.15)/2.0 - c1*(TK*log(TK/298.15)-TK+298.15) + a1*(Pbar-1.0) + a2*log((2600.0+Pbar)/(2600.0+1.0)) - c2*((1.0/(TK-228)-1.0/(298.15-228.0))*(228.0-TK)/228.0-TK/(228.0*228.0) *log((298.15*(TK-228.0))/(TK*(298.15-228.0))))+ 1.0/(TK-228.0)*(a3*(Pbar-1.0) + a4*log((2600.0+Pbar)/(2600.0+1.0))) + a5*(omgpt*(1.0/epsilon-1.0) - omg*(1.0/78.24513-1)-5.80e-5*omg*(TK-298.15));
    *bgamma       = nbg/(2.0*log(10.0)*1.98721*TK);

    double loggamma = - ((*A) * charge*charge * sqrt(II)) / (1.0 + (*azero) * (*B) * sqrt(II)) + ((*bgamma) * II) +  log10(xiw);

    return loggamma;
}

double OsmoticCoeff(double *A,
                    double *B,
                    double *azero,
                    double *bgamma,
                    double  T,
                    double  P,
                    double  charge,
                    double  II,
                    double  density,
                    double  g,
                    double  epsilon,
                    double  xiw,
                    double  m_charge,
                    double  m_all       ){


    double loggamma = DebyeHuckel(  A,
                                    B,
                                    azero,
                                    bgamma,

                                    T,
                                    P,
                                    charge,              //charge of species
                                    II,
                                    density,            //density of water
                                    g,  
                                    epsilon,
                                    xiw                );  //fraction of water

    // Equation 187 of Helgeson et al. (1981)
    double gamma = -log10(1.0 + 0.0180153 * m_all);
    double Lambda = 1.0 + (*azero) * (*B) * sqrt(II);

    // sigmaterm here is short for = sigma * (azero*bgamma*csqrt(I))
    double sigmaterm = (3.0/(pow((*azero),3.0) * pow((*B),3.0) * pow(II,(3.0/2.0)))) * (Lambda - 1.0/Lambda - 2.0*log(Lambda));

    // printf("sigmaterm: %g\n",sigmaterm);
    double Phi = -log10(m_charge/m_all) * (( pow(charge,2.0) * (*A) * sqrt(II) * sigmaterm)/3.0 + (1.0 * gamma)/(0.0180153*2.0*II) - ((*bgamma) * II) / 2.0);
    double logawater = -(Phi*m_all)/55.508435;

    return logawater;
}
void px_aq17(void *SS_ref_db, const double *x){
    SS_ref *d  = (SS_ref *) SS_ref_db;
    double *p   = d->p;
    int n_em    = d->n_em;

    for (int i = 0; i < n_em; i++){
        p[i] = x[i];
    }
}


double obj_aq17(unsigned n, const double *x, double *grad, void *SS_ref_db) {
    SS_ref *d         = (SS_ref *) SS_ref_db;

    int n_em          = d->n_em;
    int len_ox        = d->len_ox;
    double P          = d->P;
    double T          = d->T;
    double R          = d->R;

    double *gb        = d->gb_lvl;
    double *ElH       = d->ElEntropy;
    double **Comp     = d->Comp;
    double *mu        = d->mu;
    double *charge    = d->mat_phi;

    /* calculate chemical potential of fluid species, exept water */
    double m_all       = 0.0;
    double m_charge    = 0.0;
    double A           = 0.0;
    double B           = 0.0;
    double azero       = 0.0;
    double bgamma      = 0.0;
    double xiw         = x[0];
    double Xw          = 0.0;  
    for (int i = 0; i < n_em; i++){
        Xw += x[i];
    } 
  
    double II = 0.0;

    for (int i = 1; i < n_em; i++){
        II += 55.508435*(x[i]/xiw)*pow(charge[i],2.0);
    }
    II *= 0.5;

    double loggamma,cor;
    for (int i = 1; i < n_em; i++){
        loggamma = DebyeHuckel( &A,
                                &B,
                                &azero,
                                &bgamma,
                                T,
                                P*1000.0,
                                charge[i],              //charge of species
                                II,
                                d->densityW,            //density of water
                                d->g,  
                                d->epsilon,
                                xiw                );  //fraction of water
        // cor          = HSC_to_SUPCRT(ElH, Comp[i], len_ox);
        mu[i]        = gb[i]  + (log(pow(10.0,loggamma)) + log(1000.0/18.0153) + log(x[i]/Xw) - log(xiw/Xw) - xiw/Xw + 1.0 )/1000.0;
        m_all       += x[i];
        if (charge[i] != 0.0){
            m_charge += x[i];
        }
    }
    

    m_all       /= xiw;
    m_charge    /= xiw;

    double logawater = OsmoticCoeff(   &A,
                                       &B,
                                       &azero,
                                       &bgamma,
        
                                        T,
                                        P*1000.0,
                                        charge[0],
                                        II,
                                        d->densityW,
                                        d->g,
                                        d->epsilon,
                                        xiw,
                                        m_charge,
                                        m_all       );

    /* set chemical potential of water */
    // cor          = HSC_to_SUPCRT(ElH, Comp[0], len_ox);
    mu[0] = gb[0]  + ( log(logawater) + log(xiw/Xw) - Xw/xiw - xiw/Xw + 2.0)/1000.0;

    px_aq17(SS_ref_db,x);

    d->sum_apep = 0.0;
    for (int i = 0; i < n_em; i++){
        d->sum_apep += d->ape[i]*x[i];
    }
    d->factor = d->fbc/d->sum_apep;

    d->df_raw = 0.0;
    for (int i = 0; i < n_em; i++){
        d->df_raw += mu[i]*x[i];
    }
    d->df = d->df_raw * d->factor;


    printf("gb0:\n");
    for (int i = 0; i < n_em; i++){
        printf(" %+12.6f",gb[i]);
    }
    printf("\n");
    printf("x:\n");
    for (int i = 0; i < n_em; i++){
        printf(" %g",x[i]);
    }
    printf("\n");
    printf("mu:\n");
    for (int i = 0; i < n_em; i++){
        printf(" %+12.6f",mu[i]);
    }
    printf("\nFLUID: dfraw -> %+10f df -> %10f\n",d->df_raw,d->df);

	// printf("\n\n");

    if (grad){
        double *dfx    = d->dfx;
        for (int i = 0; i < (d->n_xeos); i++){
            dfx[i]  = (mu[i] - (d->ape[i]/d->sum_apep)*d->df_raw);
            grad[i] = creal(dfx[i]);
        }
    }

    return d->df;
}


SS_ref P2X(					global_variable 	 gv,
							SS_ref 				 SS_ref_db, 
							bulk_info 			 z_b,
							char    			*name				){

	double eps = gv.bnd_val;

	/* Associate the right solid-solution data */
     if(gv.EM_database == 0){
		if 	(strcmp( name, "liq") == 0 ){
			p2x_mp_liq(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "fsp") == 0){
			p2x_mp_fsp(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "bi") == 0){
			p2x_mp_bi(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "g") == 0){
			p2x_mp_g(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "ep") == 0){
			p2x_mp_ep(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "ma") == 0){
			p2x_mp_ma(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "mu") == 0){
			p2x_mp_mu(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "opx") == 0){
			p2x_mp_opx(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "sa") == 0){
			p2x_mp_sa(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "cd") == 0){
			p2x_mp_cd(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "st") == 0){
			p2x_mp_st(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "chl") == 0){
			p2x_mp_chl(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "ctd") == 0){
			p2x_mp_ctd(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "sp") == 0){
			p2x_mp_sp(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "ilm") == 0){
			p2x_mp_ilm(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "ilmm") == 0){
			p2x_mp_ilmm(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "mt") == 0){
			p2x_mp_mt(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "aq17") == 0){
			p2x_aq17(&SS_ref_db, eps);	
		}
		else{
			printf("\nsolid solution '%s' is not in the database\n",name);		
		}	
     }
     else if (gv.EM_database == 1){
      if (strcmp( name, "liq") == 0 ){
         p2x_mb_liq(&SS_ref_db, eps);
      }
      else if (strcmp( name, "hb") == 0 ){
         p2x_mb_hb(&SS_ref_db, eps);
      }
      else if (strcmp( name, "aug") == 0 ){
         p2x_mb_aug(&SS_ref_db, eps);
      }
      else if (strcmp( name, "dio") == 0 ){
         p2x_mb_dio(&SS_ref_db, eps);
      }
      else if (strcmp( name, "opx") == 0 ){
         p2x_mb_opx(&SS_ref_db, eps);
      }
      else if (strcmp( name, "g") == 0 ){
         p2x_mb_g(&SS_ref_db, eps);
      }
      else if (strcmp( name, "ol") == 0 ){
         p2x_mb_ol(&SS_ref_db, eps);
      }
      else if (strcmp( name, "fsp") == 0 ){
         p2x_mb_fsp(&SS_ref_db, eps);
      }
      else if (strcmp( name, "abc") == 0 ){
         p2x_mb_abc(&SS_ref_db, eps);
      }
      else if (strcmp( name, "k4tr") == 0 ){
         p2x_mb_k4tr(&SS_ref_db, eps);
      }
      else if (strcmp( name, "sp") == 0 ){
         p2x_mb_sp(&SS_ref_db, eps);
      }
      else if (strcmp( name, "ilm") == 0 ){
         p2x_mb_ilm(&SS_ref_db, eps);
      }
      else if (strcmp( name, "ilmm") == 0 ){
         p2x_mb_ilmm(&SS_ref_db, eps);
      }
      else if (strcmp( name, "ep") == 0 ){
         p2x_mb_ep(&SS_ref_db, eps);
      }
      else if (strcmp( name, "bi") == 0 ){
         p2x_mb_bi(&SS_ref_db, eps);
      }
      else if (strcmp( name, "mu") == 0 ){
         p2x_mb_mu(&SS_ref_db, eps);
      }
      else if (strcmp( name, "chl") == 0 ){
         p2x_mb_chl(&SS_ref_db, eps);
      }
      else{
         printf("\nsolid solution '%s' is not in the database\n",name);
      }
   }
	else if(gv.EM_database == 2 || gv.EM_database == 5){
		if 	(strcmp( name, "bi") == 0 ){
			p2x_ig_bi(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "fper")  == 0){
			p2x_ig_fper(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "cd")  == 0){
			p2x_ig_cd(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "cpx") == 0){
			p2x_ig_cpx(&SS_ref_db, eps);
		}	
		else if (strcmp( name, "ep")  == 0){
			p2x_ig_ep(&SS_ref_db, eps);
		}
		else if (strcmp( name, "fl")  == 0){
			p2x_ig_fl(&SS_ref_db, eps);
		}		
		else if (strcmp( name, "g")   == 0){
			p2x_ig_g(&SS_ref_db, eps);
		}
		else if (strcmp( name, "hb")  == 0){
			p2x_ig_hb(&SS_ref_db, eps);
		}	
		else if (strcmp( name, "ilm") == 0){
			p2x_ig_ilm(&SS_ref_db, eps);
		}
		else if (strcmp( name, "liq") == 0){
			p2x_ig_liq(&SS_ref_db, eps);
		}
		else if (strcmp( name, "mu")  == 0){
			p2x_ig_mu(&SS_ref_db, eps);	
		}	
		else if (strcmp( name, "ol")  == 0){
			p2x_ig_ol(&SS_ref_db, eps);
		}
		else if (strcmp( name, "opx") == 0){
			p2x_ig_opx(&SS_ref_db, eps);
		}
		else if (strcmp( name, "fsp")  == 0){
			p2x_ig_fsp(&SS_ref_db, eps);
		}	
		else if (strcmp( name, "spn") == 0){
			p2x_ig_spn(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "ma")  == 0){
			p2x_ig_ma(&SS_ref_db, eps);
		}	
		else if (strcmp( name, "chl") == 0){
			p2x_ig_chl(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "ctd")  == 0){
			p2x_ig_ctd(&SS_ref_db, eps);
		}	
		else if (strcmp( name, "car") == 0){
			p2x_ig_car(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "ta")  == 0){
			p2x_ig_ta(&SS_ref_db, eps);
		}	
		else if (strcmp( name, "zoi") == 0){
			p2x_ig_zoi(&SS_ref_db, eps);	
		}
		else{
			printf("\nsolid solution '%s' is not in the database\n",name);		
		}	

	}
    else if (gv.EM_database == 3){
        if (strcmp( name, "liq") == 0 ){
            p2x_igd_liq(&SS_ref_db, eps);
        }
		else if (strcmp( name, "fper")  == 0){
			p2x_ig_fper(&SS_ref_db, eps);	
		}
        else if (strcmp( name, "fl") == 0 ){
            p2x_igd_fl(&SS_ref_db, eps);
        }
        else if (strcmp( name, "fsp") == 0 ){
            p2x_igd_fsp(&SS_ref_db, eps);
        }
        else if (strcmp( name, "spn") == 0 ){
            p2x_igd_spn(&SS_ref_db, eps);
        }
        else if (strcmp( name, "g") == 0 ){
            p2x_igd_g(&SS_ref_db, eps);
        }
        else if (strcmp( name, "ol") == 0 ){
            p2x_igd_ol(&SS_ref_db, eps);
        }
        else if (strcmp( name, "opx") == 0 ){
            p2x_igd_opx(&SS_ref_db, eps);
        }
        else if (strcmp( name, "cpx") == 0 ){
            p2x_igd_cpx(&SS_ref_db, eps);
        }
        else if (strcmp( name, "ilm") == 0 ){
            p2x_igd_ilm(&SS_ref_db, eps);
        }
        else if (strcmp( name, "hb") == 0 ){
            p2x_igd_hb(&SS_ref_db, eps);
        }
        else if (strcmp( name, "bi") == 0 ){
            p2x_igd_bi(&SS_ref_db, eps);
        }
        else if (strcmp( name, "ep") == 0 ){
            p2x_igd_ep(&SS_ref_db, eps);
        }
        else if (strcmp( name, "cd") == 0 ){
            p2x_igd_cd(&SS_ref_db, eps);
        }
        else{
            printf("\nsolid solution '%s' is not in the database\n",name);
        }
    }
    else if (gv.EM_database == 6){
        if (strcmp( name, "liq") == 0 ){
            p2x_alk_liq(&SS_ref_db, eps);
        }
        else if (strcmp( name, "fl") == 0 ){
            p2x_alk_fl(&SS_ref_db, eps);
        }
        else if (strcmp( name, "fsp") == 0 ){
            p2x_alk_fsp(&SS_ref_db, eps);
        }
        else if (strcmp( name, "spn") == 0 ){
            p2x_alk_spn(&SS_ref_db, eps);
        }
        else if (strcmp( name, "g") == 0 ){
            p2x_alk_g(&SS_ref_db, eps);
        }
        else if (strcmp( name, "ol") == 0 ){
            p2x_alk_ol(&SS_ref_db, eps);
        }
        else if (strcmp( name, "opx") == 0 ){
            p2x_alk_opx(&SS_ref_db, eps);
        }
        else if (strcmp( name, "cpx") == 0 ){
            p2x_alk_cpx(&SS_ref_db, eps);
        }
        else if (strcmp( name, "ilm") == 0 ){
            p2x_alk_ilm(&SS_ref_db, eps);
        }
        else if (strcmp( name, "ness") == 0 ){
            p2x_alk_ness(&SS_ref_db, eps);
        }
        else if (strcmp( name, "lct") == 0 ){
            p2x_alk_lct(&SS_ref_db, eps);
        }
        else if (strcmp( name, "kals") == 0 ){
            p2x_alk_kals(&SS_ref_db, eps);
        }
        else if (strcmp( name, "mel") == 0 ){
            p2x_alk_mel(&SS_ref_db, eps);
        }
        else if (strcmp( name, "hb") == 0 ){
            p2x_alk_hb(&SS_ref_db, eps);
        }
        else if (strcmp( name, "bi") == 0 ){
            p2x_alk_bi(&SS_ref_db, eps);
        }
        else if (strcmp( name, "ep") == 0 ){
            p2x_alk_ep(&SS_ref_db, eps);
        }
        else if (strcmp( name, "cd") == 0 ){
            p2x_alk_cd(&SS_ref_db, eps);
        }
        else{
            printf("\nsolid solution '%s' is not in the database\n",name);
        }
    }
	else if(gv.EM_database == 4){
		if 	(strcmp( name, "fluid") == 0 ){
			p2x_um_fluid(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "ol")  == 0){
			p2x_um_ol(&SS_ref_db, eps);	
		}
		else if (strcmp( name, "br") == 0){
			p2x_um_br(&SS_ref_db, eps);
		}	
		else if (strcmp( name, "ch")  == 0){
			p2x_um_ch(&SS_ref_db, eps);
		}
		else if (strcmp( name, "atg")  == 0){
			p2x_um_atg(&SS_ref_db, eps);
		}		
		else if (strcmp( name, "g")   == 0){
			p2x_um_g(&SS_ref_db, eps);
		}
		else if (strcmp( name, "ta")  == 0){
			p2x_um_ta(&SS_ref_db, eps);
		}	
		else if (strcmp( name, "chl") == 0){
			p2x_um_chl(&SS_ref_db, eps);
		}
		else if (strcmp( name, "anth") == 0){
			p2x_um_anth(&SS_ref_db, eps);
		}
		else if (strcmp( name, "spi")  == 0){
			p2x_um_spi(&SS_ref_db, eps);	
		}	
		else if (strcmp( name, "opx")  == 0){
			p2x_um_opx(&SS_ref_db, eps);
		}
		else if (strcmp( name, "po") == 0){
			p2x_um_po(&SS_ref_db, eps);
		}
		else{
			printf("\nsolid solution '%s' is not in the database\n",name);		
		}	
	}

	return SS_ref_db;
};

SS_ref PC_function(		global_variable 	 gv,
						SS_ref 				 SS_ref_db, 
						bulk_info 	 		 z_b,
						char    			*name				){

	double G0 = 0.0;

	/* Associate the right solid-solution data */
    if(gv.EM_database == 0){
		if 	(strcmp( name, "liq") == 0 ){
			G0 = obj_mp_liq(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "fsp") == 0){	
			G0 = obj_mp_fsp(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "bi") == 0){	
			G0 = obj_mp_bi(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "g") == 0){	
			G0 = obj_mp_g(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ep") == 0){	
			G0 = obj_mp_ep(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ma") == 0){	
			G0 = obj_mp_ma(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "mu") == 0){	
			G0 = obj_mp_mu(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "opx") == 0){	
			G0 = obj_mp_opx(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "sa") == 0){	
			G0 = obj_mp_sa(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "cd") == 0){	
			G0 = obj_mp_cd(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "st") == 0){	
			G0 = obj_mp_st(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "chl") == 0){	
			G0 = obj_mp_chl(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ctd") == 0){	
			G0 = obj_mp_ctd(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "sp") == 0){	
			G0 = obj_mp_sp(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ilm") == 0){	
			G0 = obj_mp_ilm(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ilmm") == 0){	
			G0 = obj_mp_ilmm(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "mt") == 0){	
			G0 = obj_mp_mt(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "aq17") == 0){	
			G0 = obj_aq17(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else{
			printf("\nsolid solution '%s' is not in the database\n",name);		
		}	
	}
    else if (gv.EM_database == 1){
      if (strcmp( name,"liq") == 0 ){
         G0 = obj_mb_liq(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "hb") == 0 ){
         G0 = obj_mb_hb(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "aug") == 0 ){
         G0 = obj_mb_aug(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "dio") == 0 ){
         G0 = obj_mb_dio(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "opx") == 0 ){
         G0 = obj_mb_opx(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "g") == 0 ){
         G0 = obj_mb_g(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "ol") == 0 ){
         G0 = obj_mb_ol(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "fsp") == 0 ){
         G0 = obj_mb_fsp(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "abc") == 0 ){
         G0 = obj_mb_abc(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "k4tr") == 0 ){
         G0 = obj_mb_k4tr(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "sp") == 0 ){
         G0 = obj_mb_sp(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "ilm") == 0 ){
         G0 = obj_mb_ilm(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "ilmm") == 0 ){
         G0 = obj_mb_ilmm(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "ep") == 0 ){
         G0 = obj_mb_ep(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "bi") == 0 ){
         G0 = obj_mb_bi(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "mu") == 0 ){
         G0 = obj_mb_mu(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else if (strcmp( name, "chl") == 0 ){
         G0 = obj_mb_chl(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
      }
      else{
         printf("\nsolid solution '%s' is not in the database\n",name);
      }
   }
	else if(gv.EM_database == 2 || gv.EM_database == 5){
		if 	(strcmp( name, "bi") == 0 ){
			G0 = obj_ig_bi(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "fper")  == 0){
			G0 = obj_ig_fper(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "cd")  == 0){
			G0 = obj_ig_cd(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "cpx") == 0){	
			G0 = obj_ig_cpx(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
				}	
		else if (strcmp( name, "ep")  == 0){
			G0 = obj_ig_ep(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "fl")  == 0){
			G0 = obj_ig_fl(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}		
		else if (strcmp( name, "g")   == 0){
			G0 = obj_ig_g(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "hb")  == 0){
			G0 = obj_ig_hb(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "ilm") == 0){
			G0 = obj_ig_ilm(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "liq") == 0){
			G0 = obj_ig_liq(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "mu")  == 0){
			G0 = obj_ig_mu(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "ol")  == 0){
			G0 = obj_ig_ol(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "opx") == 0){
			G0 = obj_ig_opx(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "fsp")  == 0){
			G0 = obj_ig_fsp(SS_ref_db.n_xeos, SS_ref_db.iguess,SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "spn") == 0){	
			G0 = obj_ig_spn(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ma")  == 0){
			G0 = obj_ig_ma(SS_ref_db.n_xeos, SS_ref_db.iguess,SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "chl") == 0){	
			G0 = obj_ig_chl(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ctd")  == 0){
			G0 = obj_ig_ctd(SS_ref_db.n_xeos, SS_ref_db.iguess,SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "car") == 0){	
			G0 = obj_ig_car(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ta")  == 0){
			G0 = obj_ig_ta(SS_ref_db.n_xeos, SS_ref_db.iguess,SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "zoi") == 0){	
			G0 = obj_ig_zoi(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else{
			printf("\nsolid solution '%s' is not in the database\n",name);		
		}	
	}
    else if (gv.EM_database == 3){
        if (strcmp( name, "liq") == 0 ){
            G0 = obj_igd_liq(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
		else if (strcmp( name, "fper")  == 0){
			G0 = obj_igd_fper(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
        else if (strcmp( name, "fl") == 0 ){
            G0 = obj_igd_fl(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "fsp") == 0 ){
            G0 = obj_igd_fsp(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "spn") == 0 ){
            G0 = obj_igd_spn(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "g") == 0 ){
            G0 = obj_igd_g(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "ol") == 0 ){
            G0 = obj_igd_ol(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "opx") == 0 ){
            G0 = obj_igd_opx(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "cpx") == 0 ){
            G0 = obj_igd_cpx(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "ilm") == 0 ){
            G0 = obj_igd_ilm(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "hb") == 0 ){
            G0 = obj_igd_hb(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "bi") == 0 ){
            G0 = obj_igd_bi(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "ep") == 0 ){
            G0 = obj_igd_ep(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "cd") == 0 ){
            G0 = obj_igd_cd(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else{
            printf("\nsolid solution '%s' is not in the database\n",name);
        }
    }
    else if (gv.EM_database == 6){
        if (strcmp( name, "liq") == 0 ){
            G0 = obj_alk_liq(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "fl") == 0 ){
            G0 = obj_alk_fl(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "fsp") == 0 ){
            G0 = obj_alk_fsp(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "spn") == 0 ){
            G0 = obj_alk_spn(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "g") == 0 ){
            G0 = obj_alk_g(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "ol") == 0 ){
            G0 = obj_alk_ol(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "opx") == 0 ){
            G0 = obj_alk_opx(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "cpx") == 0 ){
            G0 = obj_alk_cpx(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "ilm") == 0 ){
            G0 = obj_alk_ilm(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "ness") == 0 ){
            G0 = obj_alk_ness(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "lct") == 0 ){
            G0 = obj_alk_lct(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "kals") == 0 ){
            G0 = obj_alk_kals(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "mel") == 0 ){
            G0 = obj_alk_mel(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "hb") == 0 ){
            G0 = obj_alk_hb(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "bi") == 0 ){
            G0 = obj_alk_bi(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "ep") == 0 ){
            G0 = obj_alk_ep(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else if (strcmp( name, "cd") == 0 ){
            G0 = obj_alk_cd(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
        }
        else{
            printf("\nsolid solution '%s' is not in the database\n",name);
        }
    }
	else if(gv.EM_database == 4){
		if 	(strcmp( name, "fluid") == 0 ){
			G0 = obj_um_fluid(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ol")  == 0){
			G0 = obj_um_ol(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "br") == 0){	
			G0 = obj_um_br(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
				}	
		else if (strcmp( name, "ch")  == 0){
			G0 = obj_um_ch(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "atg")  == 0){
			G0 = obj_um_atg(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}		
		else if (strcmp( name, "g")   == 0){
			G0 = obj_um_g(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "ta")  == 0){
			G0 = obj_um_ta(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "chl") == 0){
			G0 = obj_um_chl(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "anth") == 0){
			G0 = obj_um_anth(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "spi")  == 0){
			G0 = obj_um_spi(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}	
		else if (strcmp( name, "opx")  == 0){
			G0 = obj_um_opx(SS_ref_db.n_xeos, SS_ref_db.iguess, 	SS_ref_db.dfx, &SS_ref_db);
		}
		else if (strcmp( name, "po") == 0){
			G0 = obj_um_po(SS_ref_db.n_xeos, SS_ref_db.iguess, SS_ref_db.dfx, &SS_ref_db);
		}

		else{
			printf("\nsolid solution '%s' is not in the database\n",name);		
		}	
	}

    // if (strcmp( name, "aq17")  == 0){
    //     /* correction from SUPCRT to HSC convention */
    //     double cor;
    //     int n_em = SS_ref_db.n_em;
    //     SS_ref_db.df_raw = 0.0;
    //     for (int i = 0; i < n_em; i++){
    //         cor                   = SUPCRT_to_HSC(SS_ref_db.ElEntropy, SS_ref_db.Comp[i], SS_ref_db.len_ox);
    //         SS_ref_db.mu[i]      += cor;
    //         SS_ref_db.df_raw     += SS_ref_db.mu[i]*SS_ref_db.p[i];
    //     }

    //     SS_ref_db.sum_apep = 0.0;
    //     for (int i = 0; i < n_em; i++){
    //         SS_ref_db.sum_apep += SS_ref_db.ape[i]*SS_ref_db.p[i];
    //     }
    //     SS_ref_db.factor = SS_ref_db.fbc/SS_ref_db.sum_apep;

    //     SS_ref_db.df_raw = 0.0;
    //     for (int i = 0; i < n_em; i++){
    //         SS_ref_db.df_raw += SS_ref_db.mu[i]*SS_ref_db.p[i];
    //     }
    //     SS_ref_db.df = SS_ref_db.df_raw * SS_ref_db.factor;
    //     // printf("df aq17: %+12.8f\n",SS_ref_db.df);
    // }
    // else{
	    SS_ref_db.df = G0;
    // }

	
	/** initialize composition */
	for (int j = 0; j < gv.len_ox; j++){
	   SS_ref_db.ss_comp[j] = 0.0;
	}
	
	/* set mu = 0 for absent oxides */
	for (int j = 0; j < SS_ref_db.n_em; j++){
	   SS_ref_db.mu[j] *= SS_ref_db.z_em[j];
	} 
	
	/* find solution phase composition*/
	for (int i = 0; i < SS_ref_db.n_em; i++){
	   for (int j = 0; j < gv.len_ox; j++){
		   SS_ref_db.ss_comp[j] += SS_ref_db.Comp[i][j]*SS_ref_db.p[i]*SS_ref_db.z_em[i];
	   } 
	}
	
	/* check if site fractions are satisfied */
	SS_ref_db.sf_ok = 1;
	for (int i = 0; i < SS_ref_db.n_sf; i++){
		if (SS_ref_db.sf[i] < gv.eps_sf_pc || isnan(SS_ref_db.sf[i]) == 1|| isinf(SS_ref_db.sf[i]) == 1){
			SS_ref_db.sf_ok = 0;	
			break;
		}
	}

	return SS_ref_db;
};

int get_phase_id(		global_variable 	 gv,
						char    			*name				){
	int id = 0;
	for (int i = 0; i < gv.len_ss; i++){
		if 	(strcmp( name, gv.SS_list[i]) == 0 ){
			id = i;
			break;
		}
	}

	return id;
};

