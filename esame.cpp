#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAX 50



struct data{
	int giorno,mese,anno;
};
struct utente {
	int id;
	char nome[80];
	char cognome[80];
	char user[80];
	char password[80];
	struct data data_nascita;
	struct data data_iscrizione;
	
};




struct artista {
	int id;
	char nome[80];
	char genere[80];
	char produttore[80];
	char nazione[80];
	int anno_inizio;
};

struct preferenza{
	int id_utente;
	char nome_artista[80];
	bool preferenza;
};

bool autenticazione(char *nome,char *password,char *txt);
bool registrazione(struct utente utente);
bool aggiungi_artista(struct artista artista);
bool controllo_funzioni(bool app,char tipologia);
bool visualizza_elenco(char tipologia,char *txt);
char * visualizza_dati_id(int id, char *txt);
struct artista string_to_struct_artista(char *string);
struct utente string_to_struct_utente(char *string);
struct artista modifica_dati_struct(struct artista to_modify);
bool modifica_file(struct artista modificato);
//void leggi();

int main(){
	char nome[80],password[80],utente_file[80],cognome[80], *txt_admin="admin.csv",*txt_utente="user.csv",*txt_artisti="artisti.csv";
	struct utente utenti[MAX],utente_registrato;
	struct artista artisti[MAX],artista;
	struct preferenza prefereza_utenti[MAX];
	int risposta,risposta_aut,numero;
	int giorno,mese,anno;
	bool condizione=true,app=NULL,admin=false,user=false;
//	leggi();
	printf("utente o admin? [0/1]\n");
	int (scanf("%d",&risposta));
	//system("cls");
	
	do{
		
		if(risposta==1){
			printf("inserisci utente e password\n");
			scanf("%s %s", nome,password);
			//system("cls");
			app=autenticazione(nome,password,txt_admin);
			condizione=controllo_funzioni(app,'l');
			if(app)
				admin=true;
		}
		if(risposta==0){
			printf("Registrazione o login[0,1]\n");
			scanf("%d",&risposta_aut);
			//system("cls");
			if(risposta_aut==1){
				printf("inserisci utente e password\n");
				scanf("%s %s", nome,password);
				//system("cls");
				app=autenticazione(nome,password,txt_utente);
				condizione=controllo_funzioni(app,'l');
				user=true;
				}
			if(risposta_aut==0){
				printf("Inserire il nome,cognome,user,password e data di nascita[<nome> <cognome> <user> <password> <gg/mm/aa>]\n");
				scanf("%s %s %s %s %d %d %d",utente_registrato.nome,utente_registrato.cognome,utente_registrato.user,utente_registrato.password,
				&utente_registrato.data_nascita.giorno,&utente_registrato.data_nascita.mese,&utente_registrato.data_nascita.anno);
				//system("cls");
				app=registrazione(utente_registrato);
				condizione=controllo_funzioni(app,'r');
				}
		}
		
		
			
		
	}
	while(condizione);
	int scelta_1,scelta_2,scelta_3;
	bool condizione_sw=true;
	char string[20];
	struct artista artista_da_modificare,artista_modificato;
	if(admin){
		do{
			printf("Per aggiungere, modificare o eliminare degli artisti premi 1.\n");
			printf("Per aggiungere, modificare o eliminare degli utenti premi 2.\n");
			printf("Esci. 3\n");
			scanf("%d",&scelta_1);
			//system("cls");
			if(scelta_1==1)
				strcpy(string,"artista");
			if(scelta_1==2)
				strcpy(string,"utente");
			if(scelta_1==3){
				condizione_sw=false;
				continue;
			}
			if(scelta_1<0 || scelta_1>3){
				printf("Scelta non valida. Riprovare.\n");
				continue;
			}
				
			printf("Per aggiungere un %s premi 1.\n",string);
			printf("Per modificare un %s premi 2.\n",string);
			printf("Per eliminare un %s premi 3.\n",string);
			printf("Per uscire premi 4.\n");
			scanf("%d",&scelta_2);
			//system("cls");
			switch(scelta_2){
				case 1:
					if(scelta_1==1){
						do{
							printf("Inserire il nome, genere, produttore, nazionalita', data di inizio attivita'[<nome> <genere> <produttore> <nazionalita'> <aa>]\n");
							scanf("%s %s %s %s %d", artista.nome,artista.genere,artista.produttore,artista.nazione,&artista.anno_inizio);
							app=aggiungi_artista(artista);
							controllo_funzioni(app,'r');
							printf("desidera aggiungere altri artisti?[0/1]\n");
							scanf("%d",&scelta_3);
							//system("cls");
						}while(scelta_3==1);
					}
					else{ 
						do{
							printf("Inserire il nome,cognome,user,password e data di nascita[<nome> <cognome> <user> <password> <gg/mm/aa>]\n");
							scanf("%s %s %s %s %d %d %d",utente_registrato.nome,utente_registrato.cognome,utente_registrato.user,utente_registrato.password,
							&utente_registrato.data_nascita.giorno,&utente_registrato.data_nascita.mese,&utente_registrato.data_nascita.anno);
							app=registrazione(utente_registrato);
							controllo_funzioni(app,'r');
							printf("desidera aggiungere altri utenti?[0/1]\n");
							scanf("%d",&scelta_3);
							//system("cls");
						}while(scelta_3==1); 
					} 	
					break;
				case 2:
					char continua[80],*string_da_modificare,app2[200];
					strcpy(continua,"1");
					if(scelta_1==1){
						printf("---Modifica artisti--- \n");
						do{
							
							printf("desideri visualizzare l'elenco degli artisti iscritti?[0/1]\n");
							scanf("%d",&scelta_3);
							if(scelta_3==1){
								visualizza_elenco('a',txt_artisti);
							}
							printf("inserisci ID dell'artista da modificare\n");
							scanf("%d",&numero);
							string_da_modificare=visualizza_dati_id(numero,txt_artisti);
							printf("%s",string_da_modificare);
							strcpy(app2,string_da_modificare);							
							if(strcmp(app2,"Errore")==0){
								printf("Sei un coglione\n");
								printf("---Modifica artisti--- \n");
								continue;
							}
							printf("ci sono QUASI\n");
							artista_da_modificare=string_to_struct_artista(app2);
							printf("Ci sono xd\n");
							artista_modificato=modifica_dati_struct(artista_da_modificare);
							app=modifica_file(artista_modificato);
							controllo_funzioni(app,'m');
							printf("desideri continuare a modificare altre informazioni?[1/altro]\n");
							scanf("%s", continua);
						}while(strcmp(continua,"1")==0);
					}
					
					else{
						struct utente utente_da_modificare;
						char *string_da_modificare;
						printf("desideri visualizzare l'elenco degli artisti iscritti?[0/1]\n");
						scanf("%d",&scelta_3);
						if(scelta_3==1){
							visualizza_elenco('u',txt_utente);
						}
						printf("inserisci ID dell'artista da modificare\n");
						scanf("%d",&numero);
						string_da_modificare=visualizza_dati_id(numero,txt_utente);
						utente_da_modificare=string_to_struct_utente(string_da_modificare);
						
					}
					
					
					break;
				case 3:
					break;
				case 4:
					condizione_sw=false;
					break;
				default:
					printf("RIPROVA.\n");
					break;
			}
		}while(condizione_sw);	
	}
		
	return 0;
	
	
	
	
}

//funzionante per utenti
bool registrazione(struct utente utente){
	FILE *in;
	in=fopen("user.csv","r");
	char nome[80],cognome[80],user[80],string_f[200];
	int id=0,res,app=0;
	bool condizione=true,condizione_id=false,condizione_user=false,risultato=false;
	if(fgets(string_f,200,in)==NULL){
		id=-1;
		condizione_id=true;
		condizione_user=true;
	}
	else{
		do{
			id=atoi(strtok(string_f,";"));
			strcpy(nome,strtok(NULL,";"));
			strcpy(cognome,strtok(NULL,";"));
			strcpy(user,strtok(NULL,";"));
			if(strcmp(user,utente.user)==0){
				condizione=false;
				condizione_user=false;
			}
			else{
				condizione_user=true;
			}
		}while((fgets(string_f,200,in)!=NULL && condizione));
	}
	id++;
	condizione_id=true;
	fclose(in);
	if(condizione_id && condizione_user){
		FILE *out;
		out=fopen("user.csv","a");
		time_t rawtime;
	 	time (&rawtime);
	    struct tm* time;
	    time = localtime(&rawtime);
		app=fprintf(out,"\n%d;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d",id,utente.nome,utente.cognome,utente.user,utente.password,
		utente.data_nascita.giorno,utente.data_nascita.mese,utente.data_nascita.anno,time->tm_mday,time->tm_mon,time->tm_year+1900);
		fclose(out);
	}
	if(app>0)
		risultato=true;
	else
		risultato=false;
	return risultato;
	
}
	
//funzionante per utenti e admin
bool autenticazione(char *nome,char *password,char *txt){
	int res=0,id;
	bool condizione_admin=true,risultato;
	char user_f[80],password_f[80],nome_f[80],cognome_f[80],app_f[80],string_f[200];
	FILE *in;
	in=fopen(txt,"r");
	rewind(in);
	
	while(condizione_admin && fgets(string_f,200,in)!=NULL){
		id=atoi(strtok(string_f,";"));
		strcpy(nome_f,strtok(NULL,";"));
		strcpy(cognome_f,strtok(NULL,";"));
		strcpy(user_f,strtok(NULL,";"));
		strcpy(password_f,strtok(NULL,";"));
		if(strcmp(user_f,nome)==0)
			if(strcmp(password_f,password)==0)
				condizione_admin=false;
	}
	fclose(in);	
	if(fgets(string_f,200,in)==NULL && condizione_admin)
		risultato=false;
	else if(!condizione_admin)
		risultato=true;
	return risultato;			
}

bool aggiungi_artista(struct artista artista){
FILE *in;
	in=fopen("artisti.csv","r");
	char nome[80],genere[80],produttore[80],nazionalita[80],string_f[200];
	int id=0,res,app=0;
	bool condizione=true,condizione_id=false,condizione_user=false,risultato=false;
	if(fgets(string_f,200,in)==NULL){
		id=-1;
		condizione_id=true;
		condizione_user=true;
	}
	else{
		do{
			id=atoi(strtok(string_f,";"));
			strcpy(nome,strtok(NULL,";"));
			if(strcmp(nome,artista.nome)==0){
				condizione=false;
				condizione_user=false;
			}
			else{
				condizione_user=true;
			}
		}while((fgets(string_f,200,in)!=NULL && condizione));
	}
	id++;
	condizione_id=true;
	fclose(in);
	if(condizione_id && condizione_user){
		FILE *out;
		out=fopen("artisti.csv","a");
		app=fprintf(out,"\n%d;%s;%s;%s;%s;%d",id,artista.nome,artista.genere,artista.produttore,artista.nazione,artista.anno_inizio);
		fclose(out);
	}
	if(app>0)
		risultato=true;
	else
		risultato=false;
	return risultato;

}

bool controllo_funzioni(bool app,char tipologia){
	if(app){
			if(tipologia=='l')
				printf("Login effettuato con successo.\n");
			if(tipologia=='r')
				printf("Registrazione effettuata con successo.\n");
			if(tipologia=='m')
				printf("Modifica effettuata con successo.\n");
			return false;
		}
		else{
			if(tipologia=='l')
				printf("Login non effettuato.\n");
			if(tipologia=='r')
				printf("Registrazione non effettuata.\n");
			if(tipologia=='m')
				printf("Modifica non effettuata.\n");	
			return true;
		}
}


bool visualizza_elenco(char tipologia,char *txt){
	FILE *in;
	in=fopen(txt,"r");
	char string_f[300];
	fgets(string_f,300,in);
	struct artista cipolla;
	struct utente origano;
	if(tipologia== 'a')
		printf("ID            NOME          GENERE      PRODUTTORE         NAZIONE ANNO INIZIO\n");
	if(tipologia== 'u')
		printf("ID     NOME    COGNOME    USER     PASSWORD     DATA DI NASCITA\n");
	do{
		if(tipologia=='a'){
			cipolla=string_to_struct_artista(string_f);
			printf("%2d %15s %15s %15s %15s %11d\n",cipolla.id,cipolla.nome,cipolla.genere,cipolla.produttore,cipolla.nazione,cipolla.anno_inizio);
		}
		if(tipologia== 'u'){
			origano=string_to_struct_utente(string_f);	
			printf("%2d %15s %15s %15s %15s %2d/%2d/%4d\n",origano.id,origano.nome,origano.cognome,origano.user,origano.password,
			origano.data_nascita.giorno,origano.data_nascita.mese,origano.data_nascita.anno);
		}
	}while(fgets(string_f,300,in)!=NULL);
	fclose(in);
}
 
/*void leggi(){
	FILE *in;
	in=fopen("user.csv","r+");
	char string[200];
	fgets(string,200,in);
	printf("%s\n",string);
	fseek(in,1000,SEEK_SET);
	fputs("25",in);
	fclose(in);
}
*/

char *  visualizza_dati_id(int id, char *txt){
	FILE *in;
	in=fopen(txt,"r");
	char string_f[200],app[200],app2[200];
	bool condizione=false;
	struct artista cipolla;
	struct utente origano;
	while(fgets(string_f,200,in)!=NULL && !condizione){
		strcpy(app,string_f);
		if((atoi(strtok(string_f,";")))==id){
			if(strcmp(txt,"utenti.csv")==0){
				printf("ID     NOME    COGNOME    USER     PASSWORD     DATA DI NASCITA\n");
				origano=string_to_struct_utente(app);
				printf("%2d %15s %15s %15s %15s %2d/%2d/%4d\n",origano.id,origano.nome,origano.cognome,origano.user,origano.password,
				origano.data_nascita.giorno,origano.data_nascita.mese,origano.data_nascita.anno);
				condizione=true;
			}
			else{
				strcpy(app2,app);
				cipolla=string_to_struct_artista(app);
				printf("ID            NOME          GENERE      PRODUTTORE         NAZIONE ANNO INIZIO\n");
				printf("%2d %15s %15s %15s %15s %11d\n",cipolla.id,cipolla.nome,cipolla.genere,cipolla.produttore,cipolla.nazione,cipolla.anno_inizio);	
				condizione=true;	
			}
			
		}
	}
		
	fclose(in);
	if(!condizione)
		strcpy(app2,"Errore");
	return app2;
		
}


struct artista string_to_struct_artista(char *string){
	struct artista cipolla;
	cipolla.id=atoi(strtok(string,";"));
	strcpy(cipolla.nome,strtok(NULL,";"));
	strcpy(cipolla.genere,strtok(NULL,";"));
	strcpy(cipolla.produttore,strtok(NULL,";"));
	strcpy(cipolla.nazione,strtok(NULL,";"));
	cipolla.anno_inizio=atoi(strtok(NULL,";"));	
	return cipolla;	
}

struct utente string_to_struct_utente(char *string){
	struct utente origano;
	origano.id=atoi(strtok(string,";"));
	strcpy(origano.nome,strtok(NULL,";"));
	strcpy(origano.cognome,strtok(NULL,";"));
	strcpy(origano.user,strtok(NULL,";"));
	strcpy(origano.password,strtok(NULL,";"));
	origano.data_nascita.giorno=atoi(strtok(NULL,";"));
	origano.data_nascita.mese=atoi(strtok(NULL,";"));
	origano.data_nascita.anno=atoi(strtok(NULL,";"));
	return origano;
}



struct artista modifica_dati_struct(struct artista to_modify){
	char scelta[10];
	bool condizione=true;
	do {
		printf("Che dati vuole modificare?(nome,genere,produttore,nazione,anno)\n");
		scanf("%s",scelta);
		if(strcmp(scelta,"nome")==0){
			printf("inserire il nuovo nome:");
			scanf("%s",to_modify.nome);
			condizione=false;
		}
		if(strcmp(scelta,"genere")==0 && condizione){
			printf("inserire il nuovo genere:");
			scanf("%s",to_modify.genere);
			condizione=false;
		}
		if(strcmp(scelta,"produttore")==0 && condizione){
			printf("inserire il nuovo produttore:");
			scanf("%s",to_modify.produttore);
			condizione=false;
		}
		if(strcmp(scelta,"nazione")==0 && condizione){
			printf("inserire la nuova nazione:");
			scanf("%s",to_modify.nazione);
			condizione=false;
		}
		if(strcmp(scelta,"anno")==0 && condizione){
			printf("inserire il nuovo anno:");
			scanf("%d",&to_modify.anno_inizio);
			condizione=false;
		}
		printf("Giovan8 ");
	}while(condizione);
	return to_modify;
}

bool modifica_file(struct artista modificato){
	FILE *in,*out;
	in=fopen("artisti.csv","r");
	int id,lengh,app,dio=0,k=0,lol=0,rosmarino,rosa,n=0;
	struct artista artisti[MAX];
	bool condizione=true,risultato;;
	char string_f[200],gesu[200];
	for(int i=0;fgets(string_f,200,in)!=NULL;i++){
		n++;
		artisti[i]=string_to_struct_artista(string_f);
		if(artisti[i].id==modificato.id){
			artisti[i]=modificato;
		}
		
	}
	fclose(in);
	out=fopen("artisti.csv","w");
	for(int i=0;i<n;i++){
		app=fprintf(out,"%d;%s;%s;%s;%s;%d\n",artisti[i].id,artisti[i].nome,artisti[i].genere,artisti[i].produttore,artisti[i].nazione,artisti[i].anno_inizio);
		if(app>0){
			app=0;
			k++;
		}
	}
		
	
		
	
	if(n==k){
		printf("risultato=true\n");
		risultato=true;
	}else{
	
		printf("risultato=false chiusura file\n");
		risultato=false;}
	fclose(out);
	return risultato;
}





