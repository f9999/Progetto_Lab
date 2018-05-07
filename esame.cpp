#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAX 10

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
void visualizza_elenco(char tipologia,char *txt);

int main(){
	char nome[80],password[80],utente_file[80],cognome[80], *txt_admin="admin.csv",*txt_utente="user.csv",*txt_artisti="artisti.csv";
	struct utente utenti[MAX],utente_registrato;
	struct artista artisti[MAX],artista;
	struct preferenza prefereza_utenti[MAX];
	int risposta,risposta_aut;
	int giorno,mese,anno;
	bool condizione=true,app=NULL,admin=false,user=false;
	
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
					if(scelta_1==1){
						printf("desideri visualizzare l'elenco degli artisti iscritti?[0/1]\n");
						scanf("%d",&scelta_3);
						if(scelta_3==1){
							visualizza_elenco('a',txt_artisti);
						}
						
						
					}
					else{
						
					}
					
					
					break;
				case 3:
					break;
				case 4:
					condizione_sw=false;
					break;
				default:
					printf("SEI UN COGLIONE.\n");
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
			return false;
		}
		else{
			if(tipologia=='l')
				printf("Login non effettuato.\n");
			if(tipologia=='r')
				printf("Registrazione non effettuata.\n");	
			return true;
		}
}


void visualizza_elenco(char tipologia,char *txt){

	FILE *in;
	in=fopen(txt,"r");
	char string_f[300];
	
	fgets(string_f,300,in);
	printf("ID NOME GENERE PRODUTTORE NAZIONE ANNO INIZIO\n");
	do{
		printf("%d %s %s %s %s %d\n",atoi(strtok(string_f,";")),strtok(NULL,";"),strtok(NULL,";"),strtok(NULL,";"),strtok(NULL,";"),atoi(string_f));	
	}while(fgets(string_f,300,in)!=NULL);
	
	fclose(in);
	
	
}















