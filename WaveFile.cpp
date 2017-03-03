// WaveFile.cpp: implementation of the CWaveFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavSZ.h"
#include "WaveFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWaveFile::CWaveFile()
{
	pbuf=NULL;len=0;

}

CWaveFile::~CWaveFile()
{
	if(pbuf!=NULL) {free(pbuf); pbuf=NULL;len=0;}

}

int CWaveFile::ReadWavFile(LPSTR filename, WORD *pnchn, WORD *pbitpersmp, DWORD *psmprate)
{
	int nError=0;
	if ((nError=OpenWavFile(filename,pnchn, pbitpersmp,psmprate))!=0)
		return nError;
	if(pbuf!=NULL) {free(pbuf); pbuf=NULL;}
	if(len<=0)
	{
		len=0;
		pbuf=NULL;
		nError=ER_EMPTYFILE;
		return nError;
	}
	pbuf=(unsigned char*)malloc(len);
	nError=WaveDataRead(&len,pbuf);
	CloseReadFile();
	return nError;
}

int CWaveFile::WriteWavFile(LPSTR filename,unsigned char* databuf,
		              DWORD datalen, WORD nchn,
					  WORD bitpersmp, DWORD smprate)
{
	int nError=0;
	MMIOINFO mmioinfoOut;

	wfxInfo.nChannels=nchn;
	wfxInfo.wBitsPerSample=bitpersmp;
	wfxInfo.nSamplesPerSec=smprate;
	wfxInfo.wFormatTag=WAVE_FORMAT_PCM;
	wfxInfo.nAvgBytesPerSec=smprate*bitpersmp*nchn/8;
	wfxInfo.nBlockAlign=bitpersmp/8;
	wfxInfo.cbSize=0;
	DWORD numsmp=datalen/wfxInfo.nBlockAlign;

	if ((nError=WaveCreateFile(filename)) != 0) 
		return ERROR_SAVING;
	if ((nError = WaveStartDataWrite(&mmioinfoOut)) != 0) 
		return ERROR_SAVING;
	if ((nError = WaveWriteFile(datalen,databuf,&mmioinfoOut)) != 0)
		return ERROR_SAVING;
	if ((nError = WaveCloseWriteFile(&mmioinfoOut,numsmp)) != 0) 
		return ERROR_SAVING;
	return 0;
}




int CWaveFile::OpenWavFile(LPSTR filename, WORD *pnchn, WORD *pbitpersmp, DWORD *psmprate)
{
	int nError=0;
	
	hmmio=mmioOpen(filename,NULL,MMIO_ALLOCBUF|MMIO_READ);
	if(hmmio==NULL) 
	{
		nError=ER_CANNOTOPEN;
		return nError;
	}
	if((nError=(int)mmioDescend(hmmio,&ckInRIFF,NULL,0))!=0)
	{ 
		return nError;
	}
	if((ckInRIFF.ckid!=FOURCC_RIFF)||(ckInRIFF.fccType!=mmioFOURCC('W','A','V','E')))
	{
		nError=ER_NOTWAVEFILE;
		return nError;
	}
	ckIn.ckid=mmioFOURCC('f','m','t',' ');
	if((nError=(int)mmioDescend(hmmio,&ckIn,&ckInRIFF,MMIO_FINDCHUNK))!=0)
	{
		return nError;
	}
	if(ckIn.cksize<(long)sizeof(PCMWAVEFORMAT))
	{
		nError=ER_NOTWAVEFILE;
		return nError;
	}
	/* Read the 'fmt ' chunk into <pcmWaveFormat>.*/ 
	if(mmioRead(hmmio,(HPSTR)&pcmWaveFormat,
		(long)sizeof(pcmWaveFormat))!=(long)sizeof(pcmWaveFormat))
	{ 
		nError=ER_CANNOTREAD;
		return nError;
	}
	
	// Ok, allocate the waveformatex, but if its not pcm 
	// format, read the next word, and thats how many extra 
	// bytes to allocate. 
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM) 
		cbExtraAlloc = 0;
	else 
	{ 
		// Read in length of extra bytes.
		if (mmioRead(hmmio,(LPSTR)&cbExtraAlloc,
			(long)sizeof(cbExtraAlloc))!=(long)sizeof(cbExtraAlloc))
		{
			nError=ER_CANNOTREAD;
			return nError;
		}
	}

	// Copy the bytes from the pcm structure to the waveformatex structure 
	memcpy(&wfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
	wfxInfo.cbSize=cbExtraAlloc; 
	
	// Now, read those extra bytes into the structure,	if cbExtraAlloc != 0. 
	if (cbExtraAlloc!=0) 
	{ 
		if (mmioRead(hmmio,(LPSTR)(((BYTE*)&(wfxInfo.cbSize))+sizeof(cbExtraAlloc)),
			(long)(cbExtraAlloc))!=(long) (cbExtraAlloc)) 
		{ 
			nError=ER_NOTWAVEFILE; 
			return nError;
		}
	}
	/* Ascend the input file out of the 'fmt ' chunk. */
	if ((nError=mmioAscend(hmmio, &ckIn, 0))!= 0)
	{
		return nError;
	}

	// Do a nice little seek... 
	if ((nError=mmioSeek(hmmio,
		ckInRIFF.dwDataOffset+sizeof(FOURCC),SEEK_SET))==-1)
	{ 
		return nError;
	}  

//      Search the input file for for the 'data' chunk.
	ckIn.ckid=mmioFOURCC('d','a','t','a'); 
	if ((nError=mmioDescend(hmmio,&ckIn,&ckInRIFF,MMIO_FINDCHUNK))!=0)
	{ 
		return nError;
	}

	MMIOINFO mmioinfoIn;
	if (nError=mmioGetInfo(hmmio,&mmioinfoIn,0)!=0)
	{ 
		return nError;
	}
	IOBufLen=mmioinfoIn.cchBuffer;
	len=ckIn.cksize;
	bpos=0;

	*pnchn=pcmWaveFormat.wf.nChannels;
	*pbitpersmp=pcmWaveFormat.wBitsPerSample;
	*psmprate=pcmWaveFormat.wf.nSamplesPerSec;
	return nError;

}


int CWaveFile::WaveDataRead(DWORD*preadlen, unsigned char* OutBuf)
{
	int nError;  
	nError = 0;
	DWORD cT,readlen=*preadlen;
	if (pcmWaveFormat.wBitsPerSample==16)
		memset(OutBuf,0,readlen);
	else
		memset(OutBuf,128,readlen);

	MMIOINFO mmioinfoIn;

	if (nError=mmioGetInfo(hmmio,&mmioinfoIn,0)!=0)
	{ 
		*preadlen=0;bpos+=*preadlen;
		return nError;
	}
	for (cT=0;cT<readlen;cT++)
	{
		/* Copy the bytes from the io to the buffer. */ 
		if (mmioinfoIn.pchNext==mmioinfoIn.pchEndRead) 
		{     
			*preadlen=readlen;
			if ((nError=mmioAdvance(hmmio,&mmioinfoIn,MMIO_READ))!=0)
			{ 
				*preadlen=cT;bpos+=*preadlen;
				return nError; 
			}
			if (mmioinfoIn.pchNext==mmioinfoIn.pchEndRead)
			{ 
				nError=ER_CORRUPTWAVEFILE;
				*preadlen=len-bpos;bpos+=*preadlen;
				return nError;
			}
		}  
		// Actual copy.
		*((BYTE*)OutBuf+cT)=*((BYTE*)mmioinfoIn.pchNext);
		(BYTE*)mmioinfoIn.pchNext++;
	}
	if ((nError=mmioSetInfo(hmmio,&mmioinfoIn,0))!=0) 
	{ 
		*preadlen=0;bpos+=*preadlen;
		return nError;
	} 
	*preadlen=cT;bpos+=*preadlen;
	return nError; 

}


int CWaveFile::WaveCreateFile(LPSTR filename)
{
	int nError;            // Return value.
	DWORD dwFactChunk;     // Contains the actual fact chunk. Garbage until WaveCloseWriteFile. 
	MMCKINFO  ckOut1;
	dwFactChunk = (DWORD)-1;
	nError = 0;
	hmmio = mmioOpen(filename, NULL, MMIO_ALLOCBUF|MMIO_READWRITE|MMIO_CREATE);
	if (hmmio == NULL)
	{ 
		nError = ER_CANNOTWRITE;
		goto ERROR_CANNOT_WRITE;    // cannot save WAVE file
	}      
	
	/* Create the output file RIFF chunk of form type 'WAVE'.      */

	ckInRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	ckInRIFF.cksize = 0;
	if ((nError = mmioCreateChunk(hmmio, &ckInRIFF, MMIO_CREATERIFF)) != 0)
	{ 
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably 
	} 
	
	/* We are now descended into the 'RIFF' chunk we just created.
	* Now create the 'fmt ' chunk. Since we know the size of this chunk,
	* specify it in the MMCKINFO structure so MMIO doesn't have to seek
	* back and set the chunk size after ascending from the chunk.      */

	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	ckIn.cksize = sizeof(PCMWAVEFORMAT);   // we know the size of this ck.

	if ((nError = mmioCreateChunk(hmmio, &ckIn, 0)) != 0)
	{ 
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably 
	}      
	/* Write the PCMWAVEFORMAT structure to the 'fmt ' chunk if its that type.
	*/
	if (wfxInfo.wFormatTag == WAVE_FORMAT_PCM) 
	{     
		if (mmioWrite(hmmio, (HPSTR) &wfxInfo, sizeof(PCMWAVEFORMAT)) != sizeof(PCMWAVEFORMAT))
		{ 
			nError = ER_CANNOTWRITE; 
			goto ERROR_CANNOT_WRITE;    // cannot write file, probably 
		} 
	}
	else  
	{ 
		// Write the variable length size. 
		if ((UINT)mmioWrite(hmmio, (HPSTR) &wfxInfo, sizeof(wfxInfo)+wfxInfo.cbSize) != (sizeof(wfxInfo)+wfxInfo.cbSize)) 
		{ 
			nError = ER_CANNOTWRITE;
			goto ERROR_CANNOT_WRITE;    // cannot write file, probably 
		}   
	}

	/* Ascend out of the 'fmt ' chunk, 
	back into the 'RIFF' chunk.      */
	
	if ((nError = mmioAscend(hmmio, &ckIn, 0)) != 0) 
	{ 
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably 
	}  
	
	// Now create the fact chunk, not required for PCM but nice to have.  This is filled 
	// in when the close routine is called.
	
	ckOut1.ckid = mmioFOURCC('f', 'a', 'c', 't'); 
	ckOut1.cksize = 0;
	if ((nError = mmioCreateChunk(hmmio, &ckOut1, 0)) != 0)
	{ 
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably 
	}  
	if (mmioWrite(hmmio, (HPSTR)&dwFactChunk, sizeof(dwFactChunk)) != sizeof(dwFactChunk)) 
	{ 
		nError = ER_CANNOTWRITE; 
		goto ERROR_CANNOT_WRITE; 
	}  
	// Now ascend out of the fact chunk...
	if ((nError = mmioAscend(hmmio, &ckOut1, 0)) != 0) 
	{ 
		nError = ER_CANNOTWRITE;        // cannot write file, probably 
		goto ERROR_CANNOT_WRITE; 
	}        
	goto DONE_CREATE;
ERROR_CANNOT_WRITE: 
	// Maybe delete the half-written file?  Ah forget it for now, its good to leave the 
	// file there for debugging...  
DONE_CREATE: 
	return(nError); 

}

int CWaveFile::WaveStartDataWrite(MMIOINFO *pmmioinfoOut)
{
	int nError;
	nError = 0;
	
	/* Create the 'data' chunk that holds the waveform samples.  */
	
	ckIn.ckid = mmioFOURCC('d', 'a', 't', 'a'); 
	ckIn.cksize = 0;
	if ((nError = mmioCreateChunk(hmmio, &ckIn, 0)) != 0) 
	{ 
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably 
	}  
	if ((nError = mmioGetInfo(hmmio, pmmioinfoOut, 0)) != 0) 
	{ 
		goto ERROR_CANNOT_WRITE; 
	}  
	goto CLEANUP; 
ERROR_CANNOT_WRITE:
CLEANUP:
	return(nError);

}

int CWaveFile::WaveWriteFile(DWORD datalen, unsigned char *databuf, MMIOINFO *pmmioinfo)
{
	int nError;
	UINT cT;
	nError = 0;

	for (cT=0; cT < datalen; cT++) 
	{
        if (pmmioinfo->pchNext == pmmioinfo->pchEndWrite)
		{ 
			pmmioinfo->dwFlags |= MMIO_DIRTY;
			if ((nError = mmioAdvance(hmmio, pmmioinfo, MMIO_WRITE)) != 0)
			{
				goto ERROR_CANNOT_WRITE; 
			} 
		} 
		*((BYTE*)pmmioinfo->pchNext) = *((BYTE*)databuf+cT);
		(BYTE*)pmmioinfo->pchNext++;
	}   
ERROR_CANNOT_WRITE: 
	// What to do here?  Well, for now, nothing, just return that error.  
	//(maybe delete the file later?  
	return(nError);

}

int CWaveFile::WaveCloseWriteFile(MMIOINFO *pmmioinfoOut, DWORD numsmp)
{
	int nError;
	nError = 0;
	if (hmmio == NULL) 
		return(0);
	pmmioinfoOut->dwFlags |= MMIO_DIRTY;
	if ((nError = mmioSetInfo(hmmio, pmmioinfoOut, 0)) != 0) 
	{
		// cannot flush, probably... 
		goto ERROR_CANNOT_WRITE;
	}   
	/* Ascend the output file out of the 'data' chunk -- this will cause 
	* the chunk size of the 'data' chunk to be written.      */
	if ((nError = mmioAscend(hmmio, &ckIn, 0)) != 0)
		goto ERROR_CANNOT_WRITE;	// cannot write file, probably   
	
	// Do this here instead... 
	if ((nError = mmioAscend(hmmio, &ckInRIFF, 0)) != 0) 
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably   
	
	nError = mmioSeek(hmmio, 0, SEEK_SET); 
	
	if ((nError = (int)mmioDescend(hmmio, &ckInRIFF, NULL, 0)) != 0)
		goto ERROR_CANNOT_WRITE;

	nError = 0; 
	ckIn.ckid = mmioFOURCC('f', 'a', 'c', 't'); 
	if ((nError = mmioDescend(hmmio, &ckIn, &ckInRIFF, MMIO_FINDCHUNK)) == 0) 
	{ 
		// If it didn't fail, write the fact chunk out, if it failed, not critical, just 
		// assert (below).     
		nError = mmioWrite(hmmio, (HPSTR)&numsmp, sizeof(DWORD)); 
		nError = mmioAscend(hmmio, &ckIn, 0);  
		nError = 0; 
	} 
	else  
	{ 
		nError = 0;
//		Assert(FALSE); 
	}  // CANTWRITEFACT:     

	/* Ascend the output file out of the 'RIFF' chunk -- this will cause      
	* the chunk size of the 'RIFF' chunk to be written.      */
	
	if ((nError = mmioAscend(hmmio, &ckInRIFF, 0)) != 0) 
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably    

ERROR_CANNOT_WRITE: 
	if (hmmio != NULL) 
	{ 
		mmioClose(hmmio, 0); 
		hmmio = NULL;
	}  
	return(nError); 

}

int CWaveFile::CloseReadFile()
{
	if (hmmio!=NULL)
	{mmioClose(hmmio, 0);hmmio = NULL;}
	return 0;
}
