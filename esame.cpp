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

int main(){
	char nome[80],password[80],utente_file[80],cognome[80], *txt_admin="admin.csv",*txt_utente="user.csv";
	struct utente utenti[MAX],utente_registrato;
	struct artista artisti[MAX];
	struct preferenza prefereza_utenti[MAX];
	int risposta,risposta_aut;
	int giorno,mese,anno;
	bool condizione=true,app=NULL,admin=false,user=false;
	
	printf("utente o admin? [0/1]\n");
	int (scanf("%d",&risposta));
	do{
		
		if(risposta==1){
			printf("inserisci utente e password\n");
			scanf("%s %s", nome,password);
			app=autenticazione(nome,password,txt_admin);
			admin=true;
		}
		if(risposta==0){
			printf("Registrazione o login[0,1]\n");
			scanf("%d",&risposta_aut);
			 
			if(risposta_aut==1){
				printf("inserisci utente e password\n");
				scanf("%s %s", nome,password);
				app=autenticazione(nome,password,txt_utente);
				user=true;
				}
			if(risposta_aut==0){
				printf("Inserire il nome,cognome,user,password e data di nascita[<nome> <cognome> <user> <password> <gg/mm/aa>]\n");
				scanf("%s %s %s %s %d %d %d",utente_registrato.nome,utente_registrato.cognome,utente_registrato.user,utente_registrato.password,
				&utente_registrato.data_nascita.giorno,&utente_registrato.data_nascita.mese,&utente_registrato.data_nascita.anno);
				app=registrazione(utente_registrato);
				}
		}
		
		if(app){
			if(risposta==1 || (risposta==0 && risposta_aut==1)){
				printf("Login effettuato con successo.\n");
				condizione=false;
			}
			if(risposta==0 && risposta_aut==0){
				printf("Registrazione effettuata con successo.\n");
				condizione=false;
			}
		}
		else{
			if(risposta==1 || (risposta==0 && risposta_aut==1))
				printf("Login non effettuato.\n");
			if(risposta==0 && risposta_aut==0)
				printf("Registrazione non effettuata.\n");	
		}
			
		
	}
	while(condizione);
	int scelta_1,scelta_2;
	bool condizione_sw;
	char string[20];
	if(admin){
		do{
			printf("Per aggiungere, modificare o eliminare degli artisti premi 1.\n");
			printf("Per aggiungere, modificare o eliminare degli utenti premi 2.\n");
			printf("Esci. 3\n");
			scanf("%d",&scelta_1);
			if(scelta_1==1)
				strcpy(string,"artista");
			if(scelta_1==2)
				strcpy(string,"utente");
			if(scelta_1==3){
				condizione_sw=false;
				continue;
			}
			printf("Per aggiungere un %s premi 1.\n",string);
			printf("Per modificare un %s premi 2.\n",string);
			printf("Per eliminare un %s premi 3.\n",string);
			printf("Per uscire premi 4.\n");
			scanf("%d",&scelta_2);
			
			switch(scelta_2){
				case 1:
						
					break;
				case 2:
					break;
				case 3:
					condizione_sw=false;
					break;
				default:
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




















