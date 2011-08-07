	//This is the wavFile format reading class implementation...

	#include "header.h"
	#include "wavFile.h"

	#ifndef __WavFile
	#define __WavFile
	#endif

	//checks for existence of file, returns 0 if ok, returns -1 on error
	int WavFile::isFileExist(char *filename)
	{
		FILE *wavFilename;
		wavFilename = fopen(filename,"rb");
		if (wavFilename == NULL) {
			throw("File doesn't exits or wrong Filename...\n");
			exit(1);
			return (-1);
		}
		fclose(wavFilename);
		return 0;
	}

	int WavFile::readHeader(char *filename)
	{

		if (isFileExist(filename)==0) {
			FILE *wavFilename = fopen(filename,"rb");

			fread((LONG *)&waRiffId,4,1,wavFilename);

			fread((LONG *)&waRiffChunk,4,1,wavFilename);

			fread((LONG *)&waWaveId,4,1,wavFilename);

			fread((LONG *)&waFmtId,4,1,wavFilename);

			fread((LONG *)&waFmtChunk,4,1,wavFilename);

			fread((unsigned short int *)&waMonoStereo,2,1,wavFilename);

			fread((unsigned short int *)&waChannel,2,1,wavFilename);

			fread((LONG *)&waSampleRate,4,1,wavFilename);

			fread((LONG *)&waBytesPerSec,4,1,wavFilename);

			fread((WORD *)&waBytesPerSample,2,1,wavFilename);

			fread((WORD *)&waBitsPer,2,1,wavFilename);

			fread((LONG *)&waDataChunk,4,1,wavFilename);

			fread((LONG *)&waLengthOfChunk,4,1,wavFilename);

			fclose(wavFilename);
			return 0;
		}
		return -1;
	}

	//class contructor
	WavFile::WavFile(char *filename)
	{
		if(isFileExist(filename)==0)
		{
			readHeader(filename);
		}
	}

	int WavFile::printFileInfo ()
	{
		cout<<"RIFF             : "<<waRiffId<<endl;
		cout<<"Riff Chuck       : "<<waRiffChunk<<endl;
		cout<<"Wave             : "<<waWaveId<<endl;
		cout<<"Fmt              : "<<waFmtId<<endl;
		cout<<"Fmt chunk        : "<<waFmtChunk<<endl;
		cout<<"Mono Or Stero    : "<<waMonoStereo<<endl;
		cout<<"Channel          : "<<waChannel<<endl;
		cout<<"Sample Rate      : "<<waSampleRate<<endl;
		cout<<"Bytes per sec    : "<<waBytesPerSec<<endl;
		cout<<"Bytes Per Sample : "<<waBytesPerSample<<endl;
		cout<<"Bits per sample  : "<<waBitsPer<<endl;
		cout<<"Data chuck       : "<<waDataChunk<<endl;
		cout<<"Length of chunk  : "<<waLengthOfChunk<<endl;

		return 0;
	}

	int WavFile::checkFilesForHiding(char *parentfile, char *childfile)
	{
		FILE *tfile, *pfile;
		unsigned long t=0, p=0;

		// check and Initialize files...
		// read txt file and read wav file length...
		if(isFileExist(parentfile) == -1)
		{
			throw("WAV file doesn't exist");
			return -1;
		}

		if(isFileExist(childfile)== -1)
		{
			throw("txt file doesn't exist");
			return -1;
		}

		tfile = fopen(childfile,"rb");
		while(!feof(tfile))					// read the length of txt file...
		{
			fgetc(tfile);
			t++;
		}

		pfile = fopen(parentfile,"rb");
		while(!feof(pfile))					// read the length of wav file...
		{
			fgetc(pfile);
			p++;
		}

        readHeader(parentfile);				// read wav header info...

		wavFileSize = p-54;
		if(t > wavFileSize)
		{
			throw "TXT filesize is greater than WAVE file...";
			return -1;
		}

		//if(waChannel != 1)
//		{
//			throw ("Only mono WAVE files can be used...");
//			return -1;
//		}

		return 0;
	}

	int WavFile::hide (char *parentfile, char *childfile, char *outputfile)
	{
		FILE *wfile, *tfile, *ofile;
		unsigned char header[54];
		char wavbuffer, txtbuffer;
		int i;
		char txtTerminatorIndicator = '*';

		// check and Initialize parent & txt files...
		if(checkFilesForHiding(parentfile, childfile) == -1)
		{
			throw ("error!, initialization failed...");
			return -1;
		}

		wfile = fopen(parentfile, "rb");
		tfile = fopen(childfile, "rb");
		ofile = fopen(outputfile, "w+b");

		fread(header, 54, 1, wfile);		// read WAV header
		fwrite(header, 54, 1, ofile);		// write WAV header

		// main hiding/encoding process
		while( ! feof(tfile) )
		{
			txtbuffer = fgetc(tfile);
			for(i = 0; i<8; i++)
			{
				wavbuffer = fgetc(wfile);
				wavbuffer &= 0xFE;				//FE, to make sure LSB is always zero
				wavbuffer |= (char)((txtbuffer >> i) & 1);
				fputc(wavbuffer,ofile);

				wavFileSize--;
			}
		}

		// stuffing txt terminator indicator.
		for(i = 0; i < 8; i++)
		{
			wavbuffer = fgetc(wfile);
			wavbuffer &= 0xFE;
			wavbuffer |= (char)((txtTerminatorIndicator >> i) & 1);
			fputc(wavbuffer,ofile);
			wavFileSize--;
		}

		// write remaing wav bytes into the new file.
		if(wavFileSize != 0)
		{
			while(!feof(wfile)) {
				fputc(fgetc(wfile), ofile);
            }
		}

		// close all file handlers
		fclose(wfile);
		fclose(tfile);
		fclose(ofile);

		return 0;
	}

	int WavFile::unhide(char *parentfile, char *txtfile)
	{
		if (readHeader(parentfile) == -1) {
			return -1;
		}

		FILE *bfile, *tfile;
		char ch, bmpBuffer[8];
		int i;
		bfile = fopen(parentfile,"rb");
		tfile = fopen(txtfile,"w+b");

		fseek(bfile, 54, SEEK_SET);				//skip the BMP header part
		ch = 0;

		while(!feof(bfile))
		{
			// read the last bit from BMP file
			ch = 0;
			for (i=0; i<=7; i++) {
				bmpBuffer[i] = fgetc(bfile);
			}

			for (i=7; i>=0; i--) {
				ch += (bmpBuffer[i] & 1);
				if(i != 0)
					ch <<= 1;
			}

			if(ch == EOF || ch == '*') {
				break;
			} else {
				fputc(ch,tfile);
			}
		}

		fclose(bfile);
		fclose(tfile);
		return 0;
	}
