// --------------------------------------------------------------------------
// All or portions of this software are copyrighted by D-IMAGE.
// Copyright 2010-2011 D-IMAGE Corporation.  
// Company proprietary.
// --------------------------------------------------------------------------
//******************************************************************************
/**
 *  \file           DICAMAPI.h
 *  \brief          Defines the API for the D-IMAGE USB2.0 CAMERA DLL application
 *  \author         Mike 
 *  \version        \$ Revision: 0.1 \$         
 *  \arg            first implemetation    
 *  \date           2010/07/26 10:52:00     
 */
#ifndef _DICAMAPI_H_
#define _DICAMAPI_H_
#include "stdafx.h"
#include "DIDefine.h"
// DECLDIR will perform an export for us

#ifdef DLL_EXPORT
	#define DI_API extern "C" __declspec(dllexport) 
#else
	#define DI_API extern "C" __declspec(dllimport) 
#endif


/*==============================================================
Name:	CameraGetCameraNum
Desc:  Get the numeber of MultiCamera that connected to the PC.

Param:	*CamAllNum      Camera numeber connected to the PC
        *pResolution    the resolution of the previous work 
		*pCapResolution  the resolution of capture
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
  --------------------------------------------------------------*/

DI_API DI_CAMERA_STATUS _stdcall CameraGetMultiCameraNumber(BYTE *CamAllNum, BYTE *pResolution, BYTE *pCapResolution);

/*==============================================================
Name:	CameraSetMessage
Desc:   .
Param:  MsHWND  control handle which get message
        MessageID Message ID

Return: Call returns a STATUS_OK on success,otherwise returns an error code
  Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetMessage(HWND MsHWND,UINT MessageID);


/*==============================================================
Name:	CameraInit
Desc:   Initialize video equipment

Param:   pCallbackFunction  Callback fuction pointer,called by SDK,users can add the image analysis in callback fuction.	
		uiResolution  Resolution index
        hWndDisplay	  Video display control handle(Set it to NULL,when don't need to display an image )
		CamNum        One in MultiCamera
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
  --------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall  CameraInit(DI_SNAP_PROC pCallbackFunction,
								   IN DI_RESOLUTION uiResolution, 
								   IN HWND hWndDisplay, 
								   BYTE CamNum,
								   LPVOID lpContext
								   );
/*==============================================================
Name:	CameraUnInit
Desc:	Anti-initialization equipment
Param:   
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   It must call when exit the program for releasing the memory allocation space.
  --------------------------------------------------------------*/

DI_API DI_CAMERA_STATUS _stdcall  CameraUnInit(void);
/*==============================================================
Name:	CameraPlay
Desc:	Open the video stream
Param: 
Return: Call returns a STATUS_OK on success,otherwise returns an error code 
Note:   
  --------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall  CameraPlay();

/*==============================================================
Name:	CameraPlay
Desc:	Stop the video stream
Param:   
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
  --------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall  CameraStop(void);


/*==============================================================
Name:	CameraSaveCurrentImage
Desc:	Save current image.
Param:   strFileName  file name(include directory path)
        FileType     File type,specific definition refer FILE_TYPE 
Return: Call returns a STATUS_OK on success,otherwise returns an error code    
Note:   The last image will be saved when the video stream stops , .
  --------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall  CameraSaveCurrentImage(LPCTSTR strFileName, BYTE FileType,IN BYTE Quality);

/*==============================================================
Name:	CameraCaptureFile
Desc:	Capture an image to a file, the file format will change according to FileType
Param:   strFileName  file name(include directory path)
        FileType     File type,specific definition refer FILE_TYPE
		Quality      JEPG compression parameters£¬range£º1 - 100£¬value larger£¬image quality better£¬file memory bigger.
		uiCapResolution resolution£¬ refer DI_RESOLUTION definition
Return: Call returns a STATUS_OK on success,otherwise returns an error code  
Note:  
  --------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall  CameraCaptureFile(IN LPCTSTR strFileName, IN BYTE FileType, IN BYTE Quality,
										  IN DI_RESOLUTION uiCapResolution);
/*==============================================================
Name:	CameraCaptureToBuf
Desc:	Capture image data to buffer
Param:   

Return: Call returns a STATUS_OK on success,otherwise returns an error code  
Note:  
  --------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraCaptureToBuf(BYTE* pBuffer, DI_DATA_TYPE Type, IN DI_RESOLUTION uiCapResolution);

/*==============================================================
Name:	CameraGetImageSize
Desc:	Read current image size
Param:   *pWidth image width pointer
		*pHeight image height pointer
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall  CameraGetImageSize(int *pWidth, int *pHeight);
/*==============================================================
Name:	CameraSetAeState
Desc:	Set AE mode
Param:   bState - TRUE automatic exposure
               - FALSE manual exposure
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall  CameraSetAeState(IN BOOL bState);
/*==============================================================
Name:	CameraGetAeState
Desc:	Read AE mode
Param:   *pAeState save state pointer
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall  CameraGetAeState(BOOL *pAeState);
/*==============================================================
Name:	CameraSetAWBState
Desc:   Set white balance mode
Prame:   bAWBState - TRUE automatic white balance
                  - FALSE mu manual white balance
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetAWBState(BOOL bAWBState);
/*==============================================================
Name:	CameraGetAWBState
Desc:   Read white balance mode
Param:   *pAWBState save state pointer
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetAWBState(BOOL *pAWBState);
/*==============================================================
Name:	CameraSetAeTarget
Desc:   Set AE target
Param:   uiAeTarget -AE target
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetAeTarget(IN BYTE uiAeTarget);
/*==============================================================
Name:	CameraGetAeTarget
Desc:   Read AE target
Param:   *pAeTarget -save AE target pointer
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetAeTarget(IN OUT BYTE *pAeTarget);
/*==============================================================
Name:	CameraSetExposureTime
Desc:   Set exposure time
Param:   uiExposureTime -exposure time
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetExposureTime(IN int uiExposureTime);
/*==============================================================
Name:	CameraGetExposureTime
Desc:   Read exposure time
Param:   *pExposureTime -save exposure time pointer
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetExposureTime(IN int *pExposureTime);
DI_API DI_CAMERA_STATUS _stdcall CameraGetMaxExposureTime(IN USHORT *pMaxExposureTime);
/*==============================================================
Name:	CameraSetAnalogGain
Desc:   Set gain
Param:   usAnalogGain gain
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetAnalogGain(IN USHORT usAnalogGain);
/*==============================================================
Name:	CameraGetAnalogGain
Desc:   Set gain
Param:   *pAnalogGain save the gain pointer
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetAnalogGain(IN USHORT *pAnalogGain);
/*==============================================================
Name:	CameraSetGain
Desc:   Set each color channel gain
Param:   RGain red channel gain
		GGain green channel gain
		BGain blue channel gain
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetGain(IN USHORT RGain, USHORT GGain, USHORT BGain);
/*==============================================================
Name:	CameraGetGain
Desc:   Read each color channel gain 
Param:   *pRGain save red channel gain pointer
		*pGGain save green channel gain pointer
		*pBGain save blue channel gain pointer
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetGain(IN int *pRGain, int *pGGain, int *pBGain);
/*==============================================================
Name:	CameraSetGamma
Desc:   set GAMMA
Param:   uiGamma 
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetGamma(IN BYTE uiGamma);
/*==============================================================
Name:	CameraGetGamma
Desc:   Read GAMMA
Param:   *pGamma save the GAMMA pointer
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetGamma(IN BYTE *pGamma);
/*==============================================================
Name:	CameraSetColorEnhancement
Desc:   Color enhancement
Param:   bEnable - TRUE enable 
                - FALSE 
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetColorEnhancement(IN BOOL bEnable);
/*==============================================================
Name:	CameraGetColorEnhancement
Desc:   
Param:    
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetColorEnhancement(IN BOOL *pEnable);
/*==============================================================
Name:	CameraSetSaturation
Desc:   Set saturation
Param:   uiSaturation 
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetSaturation(IN BYTE uiSaturation);
/*==============================================================
Name:	CameraGetSaturation
Desc:   Read saturation
Param:   *pSaturation save the saturation pointer
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetSaturation(IN BYTE *pSaturation);
/*==============================================================
Name:	CameraSetContrast
Desc:   Set contrast
Param:   uiContrast 
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetContrast(IN BYTE uiContrast);
/*==============================================================
Name:	CameraGetContrast
Desc:   Read contrast
Param:   *pContrast 
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetContrast(IN BYTE *pContrast);
/*==============================================================
Name:	CameraSetMirror
Desc:   Set image mirror
Parem:   uiDir direction specified,refer DI_MIRROR_DIRECTION definition,
        bEnable - TRUE mirror
		        - FALSE cancel mirror
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetMirror(IN DI_MIRROR_DIRECTION uiDir, IN BOOL bEnable);
/*==============================================================
Name:	CameraGetMirror
Desc:   Set image mirror
Param:   uiDir direction specified,refer DI_MIRROR_DIRECTION definition,
        *bEnable - return information
		        
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetMirror(IN DI_MIRROR_DIRECTION uiDir, IN BOOL *bEnable);
/*==============================================================
Name:	CameraSetMonochrome
Desc:   Set monochrome
Param:   bEnable - TRUE monochrome
                - FALSE cancel monochrome
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/

DI_API DI_CAMERA_STATUS _stdcall CameraSetMonochrome(IN BOOL bEnable);
/*==============================================================
Name:	CameraGetMonochrome
Desc:   Read color settings
Param:   *pEnable save the state pointer
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetMonochrome(IN BOOL *pEnable);
/*==============================================================
Name:	CameraSetFrameSpeed
Desc:   Set frame speed
Param:   FrameSpeed index,Specific definitions refer DI_FRAME_SPEED
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetFrameSpeed(IN DI_FRAME_SPEED FrameSpeed);
/*==============================================================
Name:	CameraGetFrameSpeed
Desc:   Set frame speed
Param:   FrameSpeed index,Specific definitions refer DI_FRAME_SPEED
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetFrameSpeed(IN BYTE *pFrameSpeed);

/*==============================================================
Name:	CameraSetLightFrquency
Desc:   Set light frquency
Param:   
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   It is effective in automatic expoture.
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetLightFrquency(IN DI_LIGHT_FREQUENCY LightFrequency );
DI_API DI_CAMERA_STATUS _stdcall CameraGetLightFrquency(IN BYTE *pLightFrequency );
/*==============================================================
Name:	CameraSaveParameter
Desc:   Save parameters to team ?
Param:   Team -team
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSaveParameter(IN DI_PARAMETER_TEAM Team);
DI_API DI_CAMERA_STATUS _stdcall CameraReadParameter(IN DI_PARAMETER_TEAM Team);
/*==============================================================
Name:	CameraGetCurrentParameterTeam
Desc:   Read current parameter team
Param:   
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetCurrentParameterTeam(IN BYTE *pTeam);
/*==============================================================
Name:	CameraSetGpio
Desc:   Configure the input and output of GPIO
Param:   bValue £­£­bit0 to IO3
               £­£­bit1 to IO2
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   input is 0£¬output is 1£»
        such as£ºCameraSetGpio(0x01)--configure IO3 as output£¬IO2 as input.
        
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetGpio(IN BYTE Value);
/*==============================================================
Name:	CameraSetGpio
Desc:   Read GPIO
Param:   bValue £­£­bit0 to IO3
               £­£­bit1 to IO2
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   Configure the appropriate IO port as output before read.
        
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraReadGpio(IN BYTE *pbValue);
/*==============================================================
Name:	CameraSetGpio
Desc:   Write GPIO
Param:   bValue £­£­bit0 to IO3
               £­£­bit1 to IO2
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note:   Configure the appropriate IO port as output before read.
        
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraWriteGpio(IN BYTE Value);
/*==============================================================
Name:	CameraGetRowTime
Desc:   Read the line cycle at current
Param:   
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note: Get the current setting line time,units is microseconds(us);
      Can be used to count exposure time.
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraGetRowTime(UINT *pRowTime);

/*==============================================================
Name:	CameraSetROI
Desc:   Set ROI area
Param:   HOff Line offset
        VOff Offset
		Width area width
		Height area height
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note: 
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetROI(USHORT HOff, USHORT VOff, USHORT Width, USHORT Height);
DI_API DI_CAMERA_STATUS _stdcall CameraGetROI(USHORT *pHOff, USHORT *pVOff, USHORT *pWidth, USHORT *pHeight);
/*==============================================================
Name:	CameraSetWBWindow
Desc:   Set white balance window
Param:   HOff Line offset
        VOff Offset
		Width  area width
		Height area height
		
Return:Call returns a STATUS_OK on success,otherwise returns an error code
Note: Default regional is center,a quarter of full-screen.
Notice£ºThe function is effective when call CameraInit£¨£©.
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetWBWindow(USHORT HOff, USHORT VOff, USHORT Width, USHORT Height);
/*==============================================================
Name:	CameraSetDisplayWindow
Desc:   Set display window
Param:   HOff Line offset
        VOff Offset
		Width area width
		Height area height
		
Return: Call returns a STATUS_OK on success,otherwise returns an error code
Note: full resolution£»
Notice£ºThe function is effective when call CameraInit£¨£©.
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetDisplayWindow(USHORT HOff, USHORT VOff, USHORT Width, USHORT Height);

/*==============================================================
Name:	CameraEnableDeadPixelCorrection
Desc:   initializatize dead pixel correction.
Param:   no

  Return: Call returns a STATUS_OK on success,otherwise returns an error code
  Note:   When need to dead pixel correction,first cover the lens with shade cap,turn off auto-exposure ,set the exposure time and gain to appropriate value.
  And then call the fuction to initialize,the program willautomatically find and record the position of dead pixel.
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraEnableDeadPixelCorrection(void);

/*==============================================================
Name:	CameraSetB2RGBMode
Desc:   Set the transfer mode from BAYER to RGB24.
Param:   Mode --B2RGB_MODE_LAROCHE  base on  Gradient and color interpolation
			--B2RGB_MODE_HAMILTON  Adaptive interpolation
			--B2RGB_MODE_LINE  Linear interpolation
  Return: Call returns a STATUS_OK on success,otherwise returns an error code
  Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraSetB2RGBMode(DI_B2RGB_MODE Mode);
DI_API DI_CAMERA_STATUS _stdcall CameraGetB2RGBMode(byte *pMode);

/*==============================================================
Name:	CameraWriteSN
Desc:   Write product number.
Param:   

  Return: Call returns a STATUS_OK on success,otherwise returns an error code
  Note: make sure eeprom is writeable
        the SNCnt max value is 32  
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraWriteSN(char *pSN, BYTE SNCnt);
/*==============================================================
Name:	CameraReadSN
Desc:   read product number
Param:   

Return: Call returns a STATUS_OK on success,otherwise returns an error code
  Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraReadSN(char *pSN, BYTE SNCnt);

/*==============================================================
Name:	CameraLoadDefault
Desc:   load default camera setting
Param:   

Return: Call returns a STATUS_OK on success,otherwise returns an error code
  Note:   
--------------------------------------------------------------*/
DI_API DI_CAMERA_STATUS _stdcall CameraLoadDefault(void);



DI_API DI_CAMERA_STATUS _stdcall CameraReadBN(USHORT *pYear, BYTE *pMonth, BYTE *pDay);
DI_API DI_CAMERA_STATUS _stdcall CameraGetFPS(float* fps);

DI_API DI_CAMERA_STATUS _stdcall SaveBmpFile(CString sfilename, BYTE *pBuffer, UINT width, UINT height);
DI_API DI_CAMERA_STATUS _stdcall SetVideoFilePathName(CString  csFileName);

DI_API DI_CAMERA_STATUS _stdcall RecordAviStart(void);
DI_API DI_CAMERA_STATUS _stdcall RecordAviStop(void);
#endif