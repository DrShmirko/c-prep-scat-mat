
#include <stdio.h>
#include <legacy.h>
#include <dlfcn.h>

int *key, *key_rd, *keyel, *keysub, *keyls, *key_org, *key_fx, 
    *key_grid1, *key_rd1, *kn, *km, *kr, *nratn, *ndp;

float *wl, *rn, *rk, *pomin, *pomax, *xext, *xabs, *xsca, *albedo, 
      *xblr, *xldr;

float *r;//[KRpar];
float *grid,//[KNpar], 
       *sd;//[KNpar];
float *rd;//[KRpar];


float *f11,//[KMpar], 
       *f12,//[KMpar], //
       *f22,//[KMpar], 
       *f33,//[KMpar], //
       *f34,//[KMpar], 
       *f44;//[KMpar];
float *angle;//[KMpar];
int *key_sd, *id, *nmd, *nsd;

float *cm,//[KMD], 
       *sm,//[KMD], 
       *rmm;//[KMD];
float *rrr,//[KNpar], 
       *ar,//[KNpar], 
       *xgrid;//[KNpar];
float *ac;

// Handle of shared library
void *libsp;

int initialize_shared_library(const char *fname){
    libsp = dlopen(fname, RTLD_NOW);

    if(libsp==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_LOAD;
    }

    dls_read_config_ = (void (*)(const char *, int*))dlsym(libsp, "dls_read_config_");
    if (dls_read_config_==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    alloc_dls_array_ = (void (*)(int*, int*, int*))dlsym(libsp, "alloc_dls_array_");
    if (alloc_dls_array_==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    optchar_ = (void (*)(int*))dlsym(libsp, "optchar_");
    if (optchar_==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    sizedisdn_ = (void (*)(int *, int *, int *, int *, float* , float* , float* , float* , float* , float* , float* , float *, int *, int* ))dlsym(libsp, "sizedisdn_");
    if (sizedisdn_==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

 
    set_distname_o = (void (*)(char*))dlsym(libsp, "set_distname_o");
    if (set_distname_o==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    set_distname_f = (void (*)(char*))dlsym(libsp, "set_distname_f");
    if (set_distname_f==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    set_distname_n = (void (*)(char*))dlsym(libsp, "set_distname_n");
    if (set_distname_n==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    set_comm_name = (void (*)(int *, char *))dlsym(libsp, "set_comm_name");
    if (set_distname_o==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }


    wl = get_float_var(libsp, "wl");
    if (wl==0) return IL_FAIL_VAR;
    
    r = get_float_var(libsp, "r");
    if (r==0) return IL_FAIL_VAR;
    
    rrr = get_float_var(libsp, "rrr");
    if (rrr==0) return IL_FAIL_VAR;

    grid = get_float_var(libsp, "grid");
    if (grid==0) return IL_FAIL_VAR;

    kn = get_int_var(libsp, "kn");
    if (kn==0) return IL_FAIL_VAR;

    sd = get_float_var(libsp, "sd");
    if (sd==0) return IL_FAIL_VAR;

    return IL_OK;
}

int deinitialize_shared_library(){
    int eret = dlclose(libsp);
    if(eret!=0){
        perror(dlerror());
        return IL_FAIL_UNLOAD;
    }
    return IL_OK;
}

// get_float_var - возвращает указатель на переменную динамической библиотеки
// libsp - указатель на загруженную динамическую библиотеку
// varname - имя символа в библиотеке к которому мы хотим получить доступ
float * get_float_var(void * libsp, const char *varname){
    float * tmp;
    tmp = (float *)dlsym(libsp, varname);
    if (tmp==0){
        perror("Error loading dll. ");
        return 0;
    }
    return tmp;
}

int* get_int_var(void* libsp, const char* varname){
    int * tmp;
    tmp = (int *)dlsym(libsp, varname);
    if (tmp==0){
        perror("Error loading dll. ");
        return 0;
    }
    return tmp;
}
