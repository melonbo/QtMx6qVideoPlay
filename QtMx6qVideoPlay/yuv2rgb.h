/**
 * @file   yuv2rgb.h
 * @author Late Lee
 * @date   2012.01.20
 * 
 * @brief  
 *         YUV422P/YUV420P/YUV422SP转RGB24实现代码
 *
 * @note
 *         1、在Windows编译测试
 *         2、代码中使用的YUV420P、YUV422P是平面(planar)格式，不是打包(packed)格式
 *
 *         3、qcif: 176*144
              cif: 352*288
 * @todo  确定好RGB排序到底是什么
 *
 * @log   2013-10-26 参考422p函数，实现422sp转换422p格式函数。将初始化接口隐藏，不对外公开
 *        2014-02-10 封装统一一个函数。
 *
 * 笔记：
            每个Y、U、V、R、G、B均占用1个字节
            YUV422P平面格式
            Y、U、V分开存储，Y占w*h，U、V分别占w*h/2。每行Y有w个，U、V各w/2个。
            两个Y共用一个U和V，两个像素有Y分量2个，U、V分量各一个，共4字节，因此一个像素占2字节。

            内存分布如下：
                    w
            +--------------------+
            |Y0Y1Y2Y3...         |
            |...                 |   h
            |...                 |
            |                    |
            +--------------------+
            |U0U1      |
            |...       |   h
            |...       |
            |          |
            +----------+
            |V0V1      |
            |...       |  h
            |...       |
            |          |
            +----------+
                w/2

            第一个像素：Y0 U0 V0
            第二个像素：Y1 U0 V0
            第三个像素：Y2 U1 V1
            第四个像素：Y3 U1 V1

			每种格式分布见转换函数处
 */

#ifndef _YUV2RGB_H_
#define _YUV2RGB_H_

int ipu_yuv420p_to_rgb24(const unsigned char* yuvbuffer,unsigned char* rgbbuffer, int sour_width,int sour_height, int obj_width,int obj_height);
#endif /* _YUV2RGB_H_ */
