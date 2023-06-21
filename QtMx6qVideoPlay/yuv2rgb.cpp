#include <stdio.h>
#include "yuv2rgb.h"
#include "bmp_utils.h"
#include <string.h>



#define _IPU_FMT_
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/mxcfb.h>
#include <linux/ipu.h>

#ifdef _IPU_FMT_
struct ipu_task task;
unsigned int fmt_to_bpp(unsigned int pixelformat)
{
	unsigned int bpp;

        switch (pixelformat)
        {
                case IPU_PIX_FMT_RGB565:
               /*interleaved 422*/
                case IPU_PIX_FMT_YUYV:
                case IPU_PIX_FMT_UYVY:
                /*non-interleaved 422*/
                case IPU_PIX_FMT_YUV422P:
                case IPU_PIX_FMT_YVU422P:
                        bpp = 16;
                        break;
                case IPU_PIX_FMT_BGR24:
                case IPU_PIX_FMT_RGB24:
                case IPU_PIX_FMT_YUV444:
                        bpp = 24;
                        break;
                case IPU_PIX_FMT_BGR32:
                case IPU_PIX_FMT_BGRA32:
                case IPU_PIX_FMT_RGB32:
                case IPU_PIX_FMT_RGBA32:
                case IPU_PIX_FMT_ABGR32:
                        bpp = 32;
                        break;
                /*non-interleaved 420*/
                case IPU_PIX_FMT_YUV420P:
                case IPU_PIX_FMT_YVU420P:
                case IPU_PIX_FMT_YUV420P2:
                case IPU_PIX_FMT_NV12:
    case IPU_PIX_FMT_TILED_NV12:
                        bpp = 12;
                        break;
                default:
                        bpp = 8;
                        break;
        }
        return bpp;
}
int ipu_yuv420p_to_rgb24(const unsigned char* yuvbuffer,unsigned char* rgbbuffer, int sour_width,int sour_height, int obj_width,int obj_height)
{
	// Clear &task
		memset(&task, 0, sizeof(task));

		// Input image size and format
		task.input.width    = sour_width;
		task.input.height   = sour_height;
		task.input.format   = IPU_PIX_FMT_YUV420P;

		// Output image size and format
		task.output.width   = obj_width;
		task.output.height  = obj_height;
        task.output.format  = V4L2_PIX_FMT_RGB24;//V4L2_PIX_FMT_BGR24;
		task.output.rotate = 0;

		int fd_ipu = 0;   // IPU file descriptor
		int isize = 0;    // input size
		int osize = 0;    // output size

		void *inbuf = NULL;
		void *outbuf = NULL;

		int ret = 0;

		// Open IPU device
		fd_ipu = open("/dev/mxc_ipu", O_RDWR, 0);
		if (fd_ipu < 0) {
			printf("open ipu dev fail\n");
			ret = -1;
			goto done;
		}

		// Calculate input size from image dimensions and bits-per-pixel
		// according to format
		isize = task.input.paddr =
			task.input.width * task.input.height
			* fmt_to_bpp(task.input.format)/8;

		// Allocate contingous physical memory for input image
		// input.paddr contains the amount needed
		// this value will be replaced with physical address on success
		ret = ioctl(fd_ipu, IPU_ALLOC, &task.input.paddr);
		if (ret < 0) {
			printf("ioctl IPU_ALLOC fail: (errno = %d)\n", errno);
			goto done;
		}

		// Create memory map and obtain the allocated memory virtual address
		inbuf = mmap(0, isize, PROT_READ | PROT_WRITE,
		MAP_SHARED, fd_ipu, task.input.paddr);
		if (!inbuf) {
			printf("mmap fail\n");
			ret = -1;
			goto done;
		}

		// Allocate memory for output image
		osize = task.output.paddr =
			task.output.width * task.output.height
			* fmt_to_bpp(task.output.format)/8;
		ret = ioctl(fd_ipu, IPU_ALLOC, &task.output.paddr);
		if (ret < 0) {
			printf("ioctl IPU_ALLOC fail\n");
			goto done;
		}

		// Create memory map for output image
		outbuf = mmap(0, osize, PROT_READ | PROT_WRITE,
		MAP_SHARED, fd_ipu, task.output.paddr);
		if (!outbuf) {
			printf("mmap fail\n");
			ret = -1;
			goto done;
		}

//		// Open output file for writing
//		if ((file_out = fopen("output_file.raw", "wb")) < 0) {
//			printf("Cannot open output file");
//			ret = -1;
//			goto done;
//		}

		// Read input image
		memcpy(inbuf,yuvbuffer,isize);
//		ret = fread(inbuf, 1, isize, file_in);
//		if (ret < isize) {
//			ret = 0;
//			printf("Cannot read enough data from input file\n");
//			goto done;
//		}


		// Perform the rotation
		ret = ioctl(fd_ipu, IPU_QUEUE_TASK, &task);
		if (ret < 0) {
			printf("ioct IPU_QUEUE_TASK fail\n");
			goto done;
		}
		memcpy(rgbbuffer,outbuf,osize);

	done:

		if (outbuf)
			munmap(outbuf, osize);
		if (task.output.paddr)
			ioctl(fd_ipu, IPU_FREE, &task.output.paddr);
		if (inbuf)
			munmap(inbuf, isize);
		if (task.input.paddr)
			ioctl(fd_ipu, IPU_FREE, &task.input.paddr);
		if (fd_ipu)
			close(fd_ipu);
    return obj_width*obj_height*3;
}

#endif

