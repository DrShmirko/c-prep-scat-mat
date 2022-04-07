#include <stdio.h>
#include <legacy.h>
#include <dlfcn.h>
#include <config.h>
#include <stdlib.h>
#include <string.h>

// Macroses for accesing variables in shared library
#define GET_VAR(hdlr, type, name) ({ \
                                    type *tmp; \
                                    tmp = (type *)dlsym(hdlr->libsp, name);\
                                    if(tmp==NULL){\
                                        fprintf(stderr, "error on line %d problem with loading dll variable %s.", __LINE__, name);\
                                        return IL_FAIL_VAR;\
                                    }\
                                    tmp;\
                                })

// Macro for int and float types
#define GET_INT_VAR(hdlr, name) GET_VAR(hdlr, int, name)
#define GET_FLT_VAR(hdlr, name) GET_VAR(hdlr, float, name)


// Handle of shared library structure
static legacy_t *hdlr=NULL;

// get_handler - returns handler to static struct
legacy_t *get_handler(){
    if(hdlr==NULL){
        int ret;
        if((ret = initialize_shared_library())!=IL_OK){
            perror("Error loading dll library");
            return NULL;
        }
    }
    return hdlr;
}

//
int initialize_shared_library(){
    hdlr = (legacy_t*)malloc(sizeof(legacy_t));
    if(hdlr==NULL){
        perror("Error alocating memory");
        return IL_FAIL_LOAD;
    }

    hdlr->libsp = dlopen(LIBRARY_PATH, RTLD_NOW);

    if(hdlr->libsp==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_LOAD;
    }

    dls_read_config_ = (void (*)(const char *, int*))dlsym(hdlr->libsp, "dls_read_config_");
    if (dls_read_config_==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    alloc_dls_array_ = (void (*)(int*, int*, int*))dlsym(hdlr->libsp, "alloc_dls_array_");
    if (alloc_dls_array_==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    optchar_ = (void (*)(int*))dlsym(hdlr->libsp, "optchar_");
    if (optchar_==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    sizedisdn_ = (void (*)(int *, int *, int *, int *, float* , float* , float* , float* , float* , float* , float* , float *, int *, int* ))dlsym(hdlr->libsp, "sizedisdn_");
    if (sizedisdn_==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }
 
    set_distname_o = (void (*)(char*))dlsym(hdlr->libsp, "set_distname_o");
    if (set_distname_o==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    set_distname_f = (void (*)(char*))dlsym(hdlr->libsp, "set_distname_f");
    if (set_distname_f==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    set_distname_n = (void (*)(char*))dlsym(hdlr->libsp, "set_distname_n");
    if (set_distname_n==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    set_comm_name = (void (*)(int *, char *))dlsym(hdlr->libsp, "set_comm_name");
    if (set_distname_o==NULL){
        perror("Error loading dll. ");
        return IL_FAIL_FUNCT;
    }

    hdlr->key = GET_INT_VAR(hdlr, "key");
    hdlr->key_rd = GET_INT_VAR(hdlr, "key_rd");
    hdlr->keyel = GET_INT_VAR(hdlr, "keyel");
    hdlr->keysub = GET_INT_VAR(hdlr, "keysub");
    hdlr->keyls = GET_INT_VAR(hdlr, "keyls");
    hdlr->key_org = GET_INT_VAR(hdlr, "key_org");
    hdlr->key_fx = GET_INT_VAR(hdlr, "key_fx");
    hdlr->key_grid1 = GET_INT_VAR(hdlr, "key_grid1");
    hdlr->key_rd1 = GET_INT_VAR(hdlr, "key_rd1");
    hdlr->km = GET_INT_VAR(hdlr, "km");
    hdlr->kr = GET_INT_VAR(hdlr, "kr");
    hdlr->nratn = GET_INT_VAR(hdlr, "nratn");
    hdlr->ndp = GET_INT_VAR(hdlr, "ndp");
    hdlr->xext = GET_FLT_VAR(hdlr, "xext");
    hdlr->xabs = GET_FLT_VAR(hdlr, "xabs");
    hdlr->xsca = GET_FLT_VAR(hdlr, "xsca");
    hdlr->albedo = GET_FLT_VAR(hdlr, "albedo");
    hdlr->xblr = GET_FLT_VAR(hdlr, "xblr");
    hdlr->xldr = GET_FLT_VAR(hdlr, "xldr");
    hdlr->rn = GET_FLT_VAR(hdlr, "rn");
    hdlr->rk = GET_FLT_VAR(hdlr, "rk");
    hdlr->wl = GET_FLT_VAR(hdlr, "wl");
    hdlr->r = GET_FLT_VAR(hdlr, "r");
    hdlr->rrr = GET_FLT_VAR(hdlr, "rrr");
    hdlr->grid = GET_FLT_VAR(hdlr, "grid");
    hdlr->kn = GET_INT_VAR(hdlr, "kn");
    hdlr->sd = GET_FLT_VAR(hdlr, "sd");
    hdlr->rd = GET_FLT_VAR(hdlr, "rd");
    hdlr->f11 = GET_FLT_VAR(hdlr, "f11");
    hdlr->f12 = GET_FLT_VAR(hdlr, "f12");
    hdlr->f22 = GET_FLT_VAR(hdlr, "f22");
    hdlr->f33 = GET_FLT_VAR(hdlr, "f33");
    hdlr->f34 = GET_FLT_VAR(hdlr, "f34");
    hdlr->f44 = GET_FLT_VAR(hdlr, "f44");
    hdlr->angle = GET_FLT_VAR(hdlr, "angle");
    hdlr->key_sd = GET_INT_VAR(hdlr, "key_sd");
    hdlr->id = GET_INT_VAR(hdlr, "id");
    hdlr->nmd = GET_INT_VAR(hdlr, "nmd");
    hdlr->nsd = GET_INT_VAR(hdlr, "nsd");
    hdlr->cm = GET_FLT_VAR(hdlr, "cm");
    hdlr->sm = GET_FLT_VAR(hdlr, "sm");
    hdlr->rmm = GET_FLT_VAR(hdlr, "rmm");
    hdlr->rrr = GET_FLT_VAR(hdlr, "rrr");
    hdlr->ar = GET_FLT_VAR(hdlr, "ar");
    hdlr->xgrid = GET_FLT_VAR(hdlr, "xgrid");
    hdlr->ac = GET_FLT_VAR(hdlr, "ac");
    hdlr->is_allocated = false;
    return IL_OK;
}

// deinitialize_shared_library - закрывает ьиьлиотеку и освобождает ресурсы
int deinitialize_shared_library(){
    if(hdlr==0 || hdlr->libsp==0){
        perror("dll is not initialized");
        return IL_FAIL_UNLOAD;
    }

    int eret = dlclose(hdlr->libsp);
    if(eret!=0){
        perror(dlerror());
        return IL_FAIL_UNLOAD;
    }
    hdlr->libsp = NULL;
    free(hdlr);
    hdlr=NULL;
    return IL_OK;
}

// print_config вывод на экран некоторых настроек расчтета.
void print_config(legacy_t *hdlr){
    if(hdlr->libsp==NULL){
        perror("Library didn't loaded.");
        return;
    }

    //print wavelength
    printf("Wavelen: %7.2f um.\n", *hdlr->wl);
    // Print sizedistr
    printf("[\n");
    printf("%s |%s","R, um,","dVdlnr\n");
    for(int i=0; i<*hdlr->kn; i++){
        printf("%7.2f %7.4f\n", hdlr->grid[i], hdlr->sd[i]);
    }
    printf("\b\b]\n");

    printf("[\n");
    printf("R, um, |rd\n");
    for(int i=0; i<*hdlr->kr; i++){
        printf("%7.2f %7.4f\n", hdlr->r[i], hdlr->rd[i]);
    }
    printf("\b\b]\n");
}   

// read_config_file читает файл с настройками
void read_config_file(legacy_t *hdlr, const char* fname){
    int len = strlen(fname);
    dls_read_config_(fname, &len);
}

void allocate_arrays(legacy_t *hdlr){
    if(!hdlr->is_allocated){
        int32_t val = 1;
        alloc_dls_array_(hdlr->key, hdlr->keyel, &val);
        hdlr->is_allocated=true;
    }
}

void deallocate_arrays(legacy_t *hdlr){
    if (hdlr->is_allocated){
        int32_t val = 2;
        alloc_dls_array_(hdlr->key, hdlr->keyel, &val);
        hdlr->is_allocated=false;
    }
}

uint8_t is_loaded(legacy_t *hldr){
    return hldr->libsp!=NULL;
}

uint8_t is_allocated(legacy_t *hldr){
    return hldr->is_allocated;
}

const float * get_f11(legacy_t *hldr){
    if((hldr->libsp!=NULL)&&(hldr->is_allocated==1)){
        return hldr->f11;
    }
    return NULL;
}

const float * get_f12(legacy_t *hldr){
    if((hldr->libsp!=NULL)&&(hldr->is_allocated==1)){
        return hldr->f12;
    }
    return NULL;
}

const float * get_f22(legacy_t *hldr){
    if((hldr->libsp!=NULL)&&(hldr->is_allocated==1)){
        return hldr->f22;
    }
    return NULL;
}

const float * get_f33(legacy_t *hldr){
    if((hldr->libsp!=NULL)&&(hldr->is_allocated==1)){
        return hldr->f33;
    }
    return NULL;
}

const float * get_f34(legacy_t *hldr){
    if((hldr->libsp!=NULL)&&(hldr->is_allocated==1)){
        return hldr->f34;
    }
    return NULL;
}

const float * get_f44(legacy_t *hldr){
    if((hldr->libsp!=NULL)&&(hldr->is_allocated==1)){
        return hldr->f44;
    }
    return NULL;
}

const float* get_angle(legacy_t *hldr){
    if((hldr->libsp!=NULL)&&(hldr->is_allocated==1)){
        return hldr->angle;
    }
    return NULL;
}

const float * get_rrr(legacy_t *hdlr){
    if((hdlr->libsp!=NULL)&&(hdlr->is_allocated==1)){
        return hdlr->rrr;
    }
    return NULL;
}

void calculate(legacy_t *hdlr){
    if((hdlr->libsp!=NULL)&&(hdlr->is_allocated==1)){
        optchar_(hdlr->ndp);
    }
}

const float * get_ar(legacy_t *hldr){
    if((hdlr->libsp!=NULL)&&(hdlr->is_allocated==1)){
        return hdlr->ar;
    }
    return NULL;
}

const float * get_xgrid(legacy_t *hldr){
    if((hdlr->libsp!=NULL)&&(hdlr->is_allocated==1)){
        return hdlr->xgrid;
    }
    return NULL;
}

const float * get_grid(legacy_t *hldr){
    if((hdlr->libsp!=NULL)&&(hdlr->is_allocated==1)){
        return hdlr->grid;
    }
    return NULL;
}

const float * get_sd(legacy_t *hldr){
    if((hdlr->libsp!=NULL)&&(hdlr->is_allocated==1)){
        return hdlr->sd;
    }
    return NULL;
}