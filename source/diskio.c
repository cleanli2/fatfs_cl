/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "m.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result=0;
    printf("%s:pdrv=%d\n", __func__, pdrv);
    //do_backtrace();
    return result;

#if 0
	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_status();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
#endif
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result=0;
    printf("%s:pdrv=%d\n", __func__, pdrv);
    //do_backtrace();
    return result;

#if 0
	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_initialize();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
#endif
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result=0;
    memset(buff, 0, 512);
#if 0
    if(sector==0){
#if 0
1C0: 21 00 0B FE FF FF 20 00-00 00 00 6F 47 07 00 00  !_____ ____oG___
1D0: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ________________
1E0: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ________________
1F0: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 55 AA  ______________U_
#endif
        buff[0x1c0]=0x21;
        buff[0x1c2]=0x0b;
        buff[0x1c3]=0xfe;
        buff[0x1c4]=0xff;
        buff[0x1c5]=0xff;
        buff[0x1c6]=0x20;
        buff[0x1cb]=0x6f;
        buff[0x1cc]=0x47;
        buff[0x1cd]=0x07;
        buff[0x1fe]=0x55;
        buff[0x1ff]=0xaa;
    }
#endif
    printf("%s:pdrv=%d sec=%d n=%d\n", __func__, pdrv, sector, count);
    //printf("level 0 addr %p \n", __builtin_return_address(0));
    //printf("level 1 addr %p \n", __builtin_return_address(1));
    //do_backtrace();
    v_r_sec(sector, buff);
    return result;

#if 0
	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
#endif
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result=0;
    printf("%s:pdrv=%d sec=%d count=%d\n", __func__, pdrv, sector, count);
    //do_backtrace();
    v_w_sec(sector, buff);
    return result;

#if 0
	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
#endif
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
    DWORD sz_drv=2048, lba, lba2, sz_eblk=1, sz_sec=512, pns = 1;
	DRESULT res;
	int result=0;
    printf("%s:pdrv=%d cmd=%d\n", __func__, pdrv, cmd);
    switch(cmd){
        case GET_SECTOR_SIZE:
            memcpy(buff, &sz_sec, sizeof(DWORD));
            break;
        case GET_BLOCK_SIZE:
            memcpy(buff, &sz_eblk, sizeof(DWORD));
            break;
        case GET_SECTOR_COUNT:
            memcpy(buff, &sz_drv, sizeof(DWORD));
            break;
        case CTRL_SYNC:
            break;
        default:
            printf("unknown cmd %d\n", cmd);
            break;
    }
    return result;

#if 0
	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
#endif
}

