#include "ff.h"
#include "m.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
            mem_print(buf, n*512, 512);
            return;
        }
    }
    printf("no data\n");
    memset(buf, 0, 512);
}

void v_w_sec(int n, char*buf)
{
    mem_print(buf, n*512, 512);
    for(int i=0;i<vnp;i++){
        if(v_secs_list[i]==n){
            memcpy(v_secs_data[i], buf, 512);
            printf("w data found\n");
            return;
        }
    }
    printf("no data, %d used\n", vnp);
    v_secs_list[vnp]=n;
    memcpy(v_secs_data[vnp], buf, 512);
    vnp++;
}


void mem_print(const char*buf, uint32_t ct_start, uint32_t len)
{
    const char*line_stt = buf;
    uint32_t left=len, line_len;

    printf("\nMemShow Start:");
    while(left){
        int j, li;
        line_len = left>16?16:left;
        li=line_len;
        printf("\n%08x: ", ct_start);
        j=0;
        while(li--){
            printf("%02x",line_stt[j]&0xff);
            printf(j == 7 ? "-":" ");
            j++;
        }
        li=line_len;
        j=0;
        printf(" ");
        while(li--){
            if(line_stt[j]>=0x20 && line_stt[j]<0x7f){
                printf("%c", line_stt[j]);
            }
            else{
                printf("_");
            }
            j++;
        }
        left-=line_len;
        line_stt+=line_len;
        ct_start+=line_len;
    }
    printf("\nMemShow End:\n");
}

// end of v disk


int main (void)
{
    FRESULT fr;
    FATFS fs;
    FIL fil;
    FRESULT res;        /* API result code */
    BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
    UINT rn;

    v_init();

    /* Format the default drive with default parameters */
    printf("======mkfs======\n");
    res = f_mkfs("", 0, work, sizeof work);
    if (res){
        printf("fmkfs fail %d\n", res);
        return -1;
    }
    else{
        printf("fmkfs done OK\n");
    }
    printf("======mkfs done======\n");

    /* Open or create a log file and ready to append */
    printf("======mount======\n");
    f_mount(&fs, "", 0);
    printf("======mount done======\n");
    printf("======openappend======\n");
    fr = open_append(&fil, "logfile.txt");
    if (fr != FR_OK) return 1;
    printf("======openappend done======\n");

    /* Append a line */
    printf("======fprint======\n");
    f_printf(&fil, "%02u/%02u/%u, %2u:%02u\n", 3, 4, 2022, 12, 39);
    printf("======fprint done======\n");

    /* Close the file */
    printf("======fclose======\n");
    f_close(&fil);
    printf("======fclose done======\n");

    printf("======rename======\n");
    f_rename("logfile.txt", "mylog.txt");
    printf("======rename done======\n");

    fr = f_open(&fil, "mylog.txt", FA_READ | FA_OPEN_ALWAYS);
    if (fr) return 1;
    f_read(&fil, work, 100, &rn);
    printf("rn=%d:%s\n", rn, work);
    f_close(&fil);

    return 0;
}

