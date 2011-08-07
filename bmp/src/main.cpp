
	#include "header.h"
	#include "bmpFile.h"

	// function prototype
	int bmpEncoderHandler(char *,char *,char *);
	int bmpDecoderHandler(char *, char *);
	int bmpInfoHandler(char *);

	// main function
	int main (int argc,char *argv[]) {
		try {
			const char *f1 = argv[1];

			switch(argc)
			{
				case 1:				//single argument...
				case 2:
					cout<<"usage"<<endl;
					cout<<"bmp -option "<<endl;
					cout<<"Options:"<<endl;
					cout<<"-e    : encode into a bmp file"<<endl;
					cout<<"-d    : decode from bmp file"<<endl;
					cout<<"-i    : bmp file informations..."<<endl;
					cout<<"example: "<<endl;
					cout<<"bmp -i file.bmp"<<endl;
					cout<<"bmp -d input.bmp output.txt"<<endl;
					cout<<"bmp -e input.bmp input.txt output.bmp"<<endl;
					exit(0);
					break;

				case 3:
					if (strcmp(f1,"-i") == 0)
					{
						bmpInfoHandler(argv[2]);
					}
					else
					{
						cout<<"example: "<<endl;
						cout<<"bmp -i [BMP file]"<<endl;
						cout<<"bmp -i file.bmp"<<endl;
						exit(0);
					}
					break;

				case 4:
					if (strcmp(f1,"-d") == 0)
					{
						bmpDecoderHandler(argv[2],argv[3]);
					}
					else
					{
						cout<<"example: "<<endl;
						cout<<"bmp -d [BMP file] [Txt file]"<<endl;
						cout<<"bmp -d input.bmp output.txt"<<endl;
						exit(0);
					}

					break;

				case 5:
					if(strcmp(f1,"-e")==0)
					{
						bmpEncoderHandler(argv[2],argv[3],argv[4]);
					}
					else
					{
						cout<<"example: "<<endl;
						cout<<"bmp -e [BMP file] [Txt file] [Output Bmp file]"<<endl;
						cout<<"bmp -e input.bmp input.txt output.bmp"<<endl;
						exit(0);
					}
					break;
			}
		}
		catch(char *err)
		{
			cout<<"Err : "<<err<<endl;
			exit(1);
		}

		return 0;
	}

	// Encode into bmp file
	int bmpEncoderHandler (char *parentFile, char *childFile, char *outputFile)
	{
		BmpFile bm(parentFile);

		if( bm.hide(parentFile, childFile, outputFile) == 0 )
		{
			printf("Hidding done.\n");
		}
		else
		{
			printf("Error!");
			return -1;
		}

		return 0;
	};

	// Decode from bmp file
	int bmpDecoderHandler(char *parentFile, char *outputFile)
	{
		BmpFile bm(parentFile);

		if ( bm.unhide(parentFile, outputFile) == 0 )
		{
			printf("Unhidding done.\n");
		}
		else
		{
			printf("Error!");
			return -1;
		}

		return 0;
	};

	// Read bmp header
	int bmpInfoHandler(char *parentFile)
	{
		BmpFile bm(parentFile);
		bm.printFileInfo();
		return 0;
	};
