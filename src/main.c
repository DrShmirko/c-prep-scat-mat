#include <stdio.h>
#include <legacy.h>
#include <dlfcn.h>
#include <config.h>
#include <string.h>


enum {RET_OK, RET_DLLFAILS, RET_FAILSFCN, RET_FAILSVAR};

int main(int argc, char **argv){

    static legacy_t *hdlr;
    hdlr = get_handler();

    read_config_file(hdlr, CONFIG_SPHEROIDS);
    print_config(hdlr);
    allocate_arrays(hdlr);

    calculate(hdlr);
    const float *f11 = get_f11(hdlr);
    const float *angle = get_angle(hdlr);

    if(f11==NULL){
        fprintf(stderr, "f11 is NULL\n");
        return 0;
    }

    if(angle==NULL){
        fprintf(stderr,"angle is NULL\n");
        return 0;
    }

    for(size_t i=0; i<5; i++){
        printf("%f\t%f\n", angle[i], f11[i]);
    }

    const float *ar=get_ar(hdlr);
    const float *xgrid=get_xgrid(hdlr);
    const float *sd=get_sd(hdlr);
    const float *grid=get_xgrid(hdlr);

    for(size_t i=0; i<*hdlr->kn; i++){
        printf("%f\t%f\t%f\t%f\n", ar[i], xgrid[i], sd[i], grid[i]);
    }

    deallocate_arrays(hdlr);
    deinitialize_shared_library();
    return RET_OK;
}

