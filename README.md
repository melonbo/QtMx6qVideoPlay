# QtMx6qVideoPlay
imx6q硬件解码视频，在qt界面显示

```
:QtMx6qDemo
	CDecThread(i, this);
	connect(thread[i],SIGNAL(SignalYuvNotify(const unsigned char *, int,int,int,int)), this, SLOT(YuvDataNotify(const unsigned char *, int,int,int,int )));
	thread[i]->start();
	

CDecThread
	fin =  fopen("/home/stream.h264", "rb");//打开文件
	DecContxt decContxt;//初始化decContxt，包括yuv回调、h264读回调等
	run()；
		decode_stream (&decContxt);
			pBitstream=(unsigned char*)malloc(nUnitDataSize);//alloc bitstream buffer
			memset(&memInfo,0,sizeof(VpuMemInfo));//clear vpu内存
			memset(&decMemInfo,0,sizeof(DecMemInfo));//clear 解码内存
			ret=VPU_DecLoad();//load vpu
			ret=VPU_DecGetVersionInfo(&ver);//version info
			ret=VPU_DecGetWrapperVersionInfo(&w_ver);//wrapper version info
			ret=VPU_DecQueryMem(&memInfo);//query memory
			MallocMemBlock(&memInfo,&decMemInfo)//malloc memory for vpu wrapper
			ConvertCodecFormat(pDecContxt->nCodec, &decOpenParam.CodecFormat))；//set open params，包括//for H264//unit test: using stream mode
			VPU_DecGetCapability((VpuDecHandle)NULL, VPU_DEC_CAP_FILEMODE, &capability);//check capabilities
			VPU_DecGetCapability((VpuDecHandle)NULL, VPU_DEC_CAP_TILE, &capability);//check capabilities
			ret=VPU_DecOpen(&handle, &decOpenParam, &memInfo);//open vpu
			
			DecodeLoop(handle, pDecContxt, pBitstream,&decMemInfo,&fbHandle);//decoding loop
				VPU_DecGetCapability(handle, VPU_DEC_CAP_FRAMESIZE, &capability);//frame size supported
				VpuDecConfig config;//vpn解码配置
				ConvertSkipMode(pDecContxt->nSkipMode,&config,&param)；//config skip type
				ret=VPU_DecConfig(handle, config, &param);//vpn解码配置
														//config skip type
														//config delay buffer size
														//config input type: normal
				while()//main loop for playing
					//avoid dead loop : can not write data into decoder
					readbytes=ReadBitstream(pDecContxt, pBitstream,unitDataSize);//read new data into bitstream buf
					ret=VPU_DecDecodeBuf(handle, &InData,&bufRetCode);//decode bitstream buf//配置InData类型
					//check input buff	
					//check init info
					//check resolution change
					//check frame size
					ret=VPU_DecGetOutputFrame(handle, &frameInfo);//check output buff
					OutputFrame(pDecContxt,&frameInfo,InitInfo.nPicWidth,InitInfo.nPicHeight,*pFbHandle,dispFrameNum);//输出一帧图像
						ret=VPU_DecGetMem(&vpuMem);//获取输出数据
						fwrite()//写文件保存
						ConvertDataFromTileToLinear()；//把碎片数据排成线性
						pDecContxt->foutcallback()；//YuvDataCallBack()调用yuv回调函数
							emit pthread->SignalYuvNotify(pPacketBuffer, nPacketSize, width,height,pthread->decContxt.index);
							QtMx6qDemo::YuvDataNotify();
								ipu_yuv420p_to_rgb24();
								QImage tmpImg()；
								QPainter.drawImage();绘图
								
						//display 
						//ConvertCodecFormat(pDecContxt->nCodec, &codecFormat);
						
					ret=VPU_DecOutFrameDisplayed(handle,frameInfo.pDisplayFrameBuf);//clear frame display flag
					//check whether some frames are skipped by vpu
					//check other options when no err
					
				
				
			VPU_DecReset(handle);
```			
		
