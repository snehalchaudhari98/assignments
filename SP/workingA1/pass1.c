#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Littab{
int sr;
char literal[10];
int address;
}Littab;



typedef struct Symtab{
int sr;
char symbol[10];
int size;
int address;
}Symtab;



int findReg(char *a){
	if(strcmp(a,"AREG")==0)
	return 1;
	else if(strcmp(a,"BREG")==0)
	return 2;
	else if(strcmp(a,"CREG")==0)
	return 3;
	else if(strcmp(a,"DREG")==0)
	return 4;
	else if(strcmp(a,"--")==0)
	return 5;
	else
		return 99;
}
/*
int findType(char *a){
	if(strcmp(a,"IS")==0)
	return 1;
	else if(strcmp(a,"DL")==0)
	return 2;
	else if(strcmp(a,"AD")==0)
	return 3;
	else
		return 99;
}
*/

int main(int argc, char const *argv[])
{
	int lc=0,count,code,size,syscount=0,litcount=0,poolcount=0,flag,o1,o2,i=0,re_lit,re_lit2,j=0;
	char label[10],mnemonic[10],op1[10],op2[10],mnemonic_main[10],m_type[3];
	FILE *input , *output ,*mot ,*symtab ,*littab;
	Littab LITTAB[10];
	Symtab SYMTAB[10];


	input=fopen("input.txt","r"); 
	if(input!=NULL){
		printf("Input file opened\n");
	}else{
		printf("can1t open Input file\n");
	}


	mot=fopen("mot.txt","r");
	if(mot!=NULL){
		printf("Input file opened\n");
	}else{
		printf("can1t open Input file\n");
		exit(0);
	}


	output=fopen("output.txt","w");
		if(output!=NULL){
		printf("output file opened\n");
	}else{
		printf("can1t open output file\n");
		exit(0);
	}


	symtab=fopen("symtab.txt","w");
	if(symtab!=NULL){
		printf("symtab file opened\n");
	}else{
		printf("can1t open symtab file\n");
		exit(0);
	}

/*littab=fopen("littab.txt","r+");
	if(symtab!=NULL){
		printf("littab file opened\n");
	}else{
		printf("can`t open littab file\n");
		exit(0);
	}*/

	//littab=fopen("littab.txt","w");

	fscanf(input,"%s\t%s\t%s\t%s",label,mnemonic,op1,op2);

	//printf("From INPUT.TXT =%s\t%s\t%s\t%s\n",label,mnemonic,op1,op2);
	if(strcmp(mnemonic,"START")==0){
		lc=atoi(op1);
		count=lc;		
		fprintf(output, "%d\t(AD,01)\t(C,%s)\n",lc,op1);
		printf("printing to OUTPUT.TXT =%d\t%s\n",lc,mnemonic);

	}

fscanf(input,"%s\t%s\t%s\t%s",label,mnemonic,op1,op2);
//printf("From INPUT.TXT =%s\t%s\t%s\t%s\n",label,mnemonic,op1,op2);

	while(strcmp(mnemonic,"END")!=0){

		if(strcmp(label,"--")!=0){
			SYMTAB[syscount].sr=syscount+1;
			strcpy(SYMTAB[syscount].symbol,label);
			SYMTAB[syscount].size=0;		// change the size 
			SYMTAB[syscount].address=lc;
			syscount+=1;
			fprintf(symtab, "%d\t%s\t%d\n",syscount,label,lc );

			printf("printing to SYMTAB.TXT =%d\t%s\t%d\n",syscount,label,lc);
		}

	    fprintf(output, "%d\t",lc );
		rewind(mot);
		fscanf(mot,"%s\t%d\t%s\t%d\n",mnemonic_main,&code,m_type,&size);
		//printf("From MOT.TXT =%s\t%d\t%s\t%d\n",mnemonic_main,code,m_type,size);

		while(!feof(mot)){

			if(strcmp(mnemonic,mnemonic_main)==0){
				lc+=1;
				printf("%s Mnemonic FOUND\n",mnemonic_main);
				goto label1;
			}

		fscanf(mot,"%s\t%d\t%s\t%d\n",mnemonic_main,&code,m_type,&size);
		//printf("From MOT.TXT =%s\t%d\t%s\t%d\n",mnemonic_main,code,m_type,size);
		}

label1:

			 o1=findReg(op1);
			 o2=findReg(op2);

			 if(o2==99){

			 	if(op2[0]=='=')
					{
					printf("\nYEEHHH we found Literal\n");		
						//fprintf(littab,"%d\t%s\t",);
							LITTAB[litcount].sr=litcount+1;
							strcpy(LITTAB[litcount].literal,op2);
							LITTAB[litcount].address=0;
							litcount+=1;
					}
			 }

		/*if(strcmp(label,"--")!=0){*/

			fprintf(output, "(%s,%d)",m_type,code);
			if(o1==99){
				for(i=0;i<syscount;i++){

					if(strcmp(SYMTAB[i].symbol,op1)==0){
						re_lit=i;
						break;
					}
				}
					if(i!=syscount){
						fprintf(output, "\t(S,%d)",i);
					}else{
						SYMTAB[syscount].sr=syscount+1;
						strcpy(SYMTAB[syscount].symbol,op1);
						SYMTAB[syscount].size=0;		// change the size 
				//		SYMTAB[syscount].address=lc;  LC is assigned later on
						syscount+=1;
						fprintf(symtab, "%d\t%s\t%d\n",syscount,label,lc );
						//printf("printing to SYMTAB.TXT =%d\t%s\t%d\n",syscount,label,lc);
							fprintf(output, "\t(S,%d)",i+1);
					}
				
			}else{
				fprintf(output, "(R,%d)",o1);
			}
			
			if(o2==99){
				printf("finding OP2 in symtab tab \n");
				for(i=0;i<syscount;i++){

					if(strcmp(SYMTAB[i].symbol,op2)==0){
						re_lit=i;
						break;
					}
				}

				if(i==syscount){
					printf("finding OP2 in literal tab \n");
					for(j=0;j<litcount;j++){

						if(strcmp(LITTAB[j].literal,op2)==0){
							re_lit2=j;
							break;
						}
				    }

				    if(j!=litcount){
				    	fprintf(output, "\t(L,%d)",j);
				    }else{
					printf("writing pre-defined OP2 in sysmtab tab \n");
						SYMTAB[syscount].sr=syscount+1;
						strcpy(SYMTAB[syscount].symbol,op1);
						SYMTAB[syscount].size=0;		// change the size 
				//		SYMTAB[syscount].address=lc;  LC is assigned later on
						syscount+=1;
						fprintf(symtab, "%d\t%s\t%d\n",syscount,label,lc );
						//printf("printing to SYMTAB.TXT =%d\t%s\t%d\n",syscount,label,lc);
						fprintf(output, "(S,%d)",i+1);
					}

				}else{
					fprintf(output, "\t(S,%d)",i);
				}


			/*	if(i==syscount && j==litcount){
					printf("writing pre-defined OP2 in sysmtab tab \n");
						SYMTAB[syscount].sr=syscount+1;
						strcpy(SYMTAB[syscount].symbol,op1);
						SYMTAB[syscount].size=0;		// change the size 
				//		SYMTAB[syscount].address=lc;  LC is assigned later on
						syscount+=1;
						fprintf(symtab, "%d\t%s\t%d\n",syscount,label,lc );
						//printf("printing to SYMTAB.TXT =%d\t%s\t%d\n",syscount,label,lc);
						fprintf(output, "(S,%d)",i+1);
					}*/

			}else{
				fprintf(output, "(R,%d)",o2);
			}	




			/*fprintf(output, "(%s,%d)\t(R,%d)",m_type,code,o1);
				if(o2!=5)
				fprintf(output, "(%s,%d)\n",op2,o2);
				else
					fprintf(output, "\n");
			//fprintf(output, "\t%s\t%s\t%s\t%s\n",label,mnemonic,op1,op2);
			printf("printing to OUTPUT.TXT =%d\t%s\t%s\t%s\t%s\n",(lc-1),label,mnemonic,op1,op2);*/

		/*}else{
		fprintf(output, "\t%s\t%s\t%s\t%s\n",label,mnemonic,op1,op2);
			printf("printing to OUTPUT.TXT =%d\t%s\t%s\t%s\t%s\n",(lc-1),label,mnemonic,op1,op2);
		}*/


	fprintf(output, "\n");
	fscanf(input,"%s\t%s\t%s\t%s",label,mnemonic,op1,op2);
		//printf("From INPUT.TXT =%s\t%s\t%s\t%s\n",label,mnemonic,op1,op2);
	}

printf("SYMTAB is as follows:: and syscount =%d\n\n\n",syscount);
for(i=0;i<syscount;i++){
printf("%d\t%s\t%d\t%d\n",SYMTAB[i].sr,SYMTAB[i].symbol,SYMTAB[i].size,SYMTAB[i].address);
}



printf("LITTAB is as follows::and litcount =%d\n\n",litcount);
for(i=0;i<litcount;i++){
printf("%d\t%s\t%d\n",LITTAB[i].sr,LITTAB[i].literal,LITTAB[i].address);
}


fclose(input);
fclose(output);
fclose(mot);
fclose(symtab);

	return 0;
}



