
	#include "header.h"
    #include "wavFile.h"

	// function prototype
	int wavInfoHandler(char *);
	int wavEncoderHandler(char *,char *, char *);
	int wavDecoderHandler(char *, char *);

	int main(int argc,char *argv[]) {

		try {
			const char *f1 = argv[1];

			switch(argc)
			{
				case 1:				//single argument...
				case 2:
					cout << "usage : " << endl;
					cout<<"wav -options "<<endl;
					cout<<"Options:"<<endl;
					cout<<"-i    : detailed help informations"<<endl;
					cout<<"-e    : hide into wav file"<<endl;
					cout<<"-d    : unhide from wav file"<<endl;
					cout<<"example: "<<endl;
					cout<<"wav -i file.wav"<<endl;
					cout<<"wav -d input.wav output.txt"<<endl;
					cout<<"wav -e input.wav input.txt output.wav"<<endl;
					exit(0);
					break;

				case 3:
					if ( strcmp(f1, "-i") == 0 ) {
						wavInfoHandler(argv[2]);
					} else {
						cout<<"example: "<<endl;
						cout<<"wav -i file.wav"<<endl;
						exit(0);
					}
					break;

				case 4:
					if ( strcmp(f1, "-d") == 0 ) {
						wavDecoderHandler(argv[2],argv[3]);
					} else {
						cout<<"example: "<<endl;
						cout<<"wav -d input.wav output.txt"<<endl;
						exit(0);
					}
					break;
				case 5:
					if ( strcmp(f1, "-e") == 0 ) {
						wavEncoderHandler(argv[2],argv[3],argv[4]);
					} else {
						cout<<"example: "<<endl;
						cout<<"wav -e input.wav input.txt output.wav"<<endl;
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

	//function definition
	int wavInfoHandler(char *parentFile)
	{
		WavFile wa(parentFile);
		wa.printFileInfo();
		return 0;
	};

	int wavEncoderHandler(char *parentfile, char *childfile, char *outfile)
	{
		WavFile wa(parentfile);
		if(wa.hide(parentfile, childfile, outfile) == -1)
			return -1;

		cout<<"encoding done"<<endl;
		return 0;
	};

	int wavDecoderHandler(char *parentfile, char *outfile)
	{
		WavFile wa(parentfile);
		if(wa.unhide(parentfile,outfile)==-1)
			return -1;
		cout<<"decoding done"<<endl;
		return 0;
	};
