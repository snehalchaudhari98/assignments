#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main(int argc, char const *argv[])
{
	int lc=0,count,code;
	char label[10],mnemonic[10],op1[10],op2[10],mnemonic_main[10];
	FILE *input , *output ,*mot ,*symtab ,*littab;


	input=fopen("input.txt","r"); 
	mot=fopen("mot.txt","r");
	output=fopen("output.txt","w");
	symtab=fopen("symtab.txt","w");
	//littab=fopen("littab.txt","w");

	fscanf(input,"%s\t%s\t%s\t%s",label,mnemonic,op1,op2);

	if(strcmp(mnemonic,"START")==0){
		lc=atoi(op1);
		count=lc;		
		fprintf(output, "\t%s\t%s\t%s\t%s\n",label,mnemonic,op1,op2);
	}

fscanf(input,"%s\t%s\t%s\t%s",label,mnemonic,op1,op2);

	while(strcmp(mnemonic,"END")!=0){

		if(strcmp(label,"--")!=0){
			fprintf(symtab, "%s\t%d\n",label,lc );
		}

fprintf(output, "%d",lc );
		rewind(mot);
		fscanf(mot,"%s\t%d",mnemonic_main,&code);
		while(!feof(mot)){
			if(strcmp(mnemonic,mnemonic_main)==0){
				lc+=1;
			}
		fscanf(mot,"%s\t%d",mnemonic_main,&code);
		}

fscanf(input,"%s\t%s\t%s\t%s",label,mnemonic,op1,op2);

	fprintf(output, "\t%s\t%s\t%s\t%s\n",label,mnemonic,op1,op2);

	}

fclose(input);
fclose(output);
fclose(mot);
fclose(symtab);

	return 0;
}



