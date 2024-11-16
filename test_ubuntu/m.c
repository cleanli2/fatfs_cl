#include "ff.h"
#include <stdio.h>
/*------------------------------------------------------------/
/ Open or create a file in append mode
/ (This function was sperseded by FA_OPEN_APPEND flag at FatFs R0.12a)
/------------------------------------------------------------*/


#include <execinfo.h>

#define BACKTRACE_SIZ   64
void do_backtrace()
{
    void    *array[BACKTRACE_SIZ];
    size_t   size, i;
    char   **strings;

    size = backtrace(array, BACKTRACE_SIZ);
    strings = backtrace_symbols(array, size);

    for (i = 0; i < size; i++) {
        printf("%p : %s\n", array[i], strings[i]);
    }

    free(strings);  // malloced by backtrace_symbols
}

FRESULT open_append (
    FIL* fp,            /* [OUT] File object to create */
    const char* path    /* [IN]  File name to be opened */
)
{
    FRESULT fr;

    /* Opens an existing file. If not exist, creates a new file. */
    fr = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS);
    if (fr == FR_OK) {
        /* Seek to end of the file to append data */
        fr = f_lseek(fp, f_size(fp));
        if (fr != FR_OK)
            f_close(fp);
    }
    return fr;
}


//v disk
#define V_DISK_N 100
int v_secs_list[V_DISK_N]={0};
char v_secs_data[V_DISK_N][512]={0};
int vnp=0;

void v_init()
{
    for(int i=0;i<V_DISK_N;i++){
        v_secs_list[i]=-1;
    }
}

void v_r_sec(int n, char*buf)
{
    for(int i=0;i<vnp;i++){
        if(v_secs_list[i]==n){
            memcpy(buf, v_secs_data[i], 512);
            printf("data found\n");
            return;
        }
    }
    printf("no data\n");
    memset(buf, 0, 512);
}

void v_w_sec(int n, char*buf)
{
    for(int i=0;i<vnp;i++){
        if(v_secs_list[i]==n){
            memcpy(v_secs_data[i], buf, 512);
            printf("w data found\n");
            return;
        }
    }
    printf("no data, %d used\n");
    v_secs_list[vnp]=n;
    memcpy(v_secs_data[vnp], buf, 512);
    vnp++;
}


// end of v disk


int main (void)
{
    FRESULT fr;
    FATFS fs;
    FIL fil;

    /* Open or create a log file and ready to append */
    f_mount(&fs, "", 0);
    fr = open_append(&fil, "logfile.txt");
    if (fr != FR_OK) return 1;

    /* Append a line */
    f_printf(&fil, "%02u/%02u/%u, %2u:%02u\n", 3, 4, 2022, 12, 39);

    /* Close the file */
    f_close(&fil);

    return 0;
}

