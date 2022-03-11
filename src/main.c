#include <stdio.h>
#include <legacy.h>
#include <dlfcn.h>

enum {RET_OK, RET_DLLFAILS, RET_FAILSFCN, RET_FAILSVAR};


int main(int argc, char **argv){


    if(initialize_shared_library("../lib/libspheroid.so")!=IL_OK){
        return -1;
    }
    
    int len = 18;
    dls_read_config_("./input_sphrds.dat", &len);
    printf("Wavelength: %9.3f\n", *wl);

    printf("[\n");
    for(int i=0; i< *kn; i++){
        printf("%7.2f, %7.2f\n", grid[i], sd[i]);
    }
    printf("\b\b] ");
    
    deinitialize_shared_library();
    return RET_OK;
}

