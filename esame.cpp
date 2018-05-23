#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
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
	int numero_generi;
	char *genere[80];
	char produttore[80];
	char nazione[80];
	int anno_inizio;
};

struct preferenza{
	int id_utente;
	char nome_artista[80];
	bool preferenza;
};

int autenticazione(char *nome,char *password,char *txt);
bool registrazione(struct utente utente);
bool aggiungi_artista(struct artista artista,int numero_generi);
bool controllo_funzioni(bool app,char tipologia);
bool visualizza_elenco(char tipologia,char *txt);
char * visualizza_dati_id(int id, char *txt);
struct artista string_to_struct_artista(char *string);
struct utente string_to_struct_utente(char *string);
struct artista modifica_dati_struct(struct artista to_modify);
struct utente modifica_dati_struct_utente(struct utente to_modify);
bool modifica_file_artisti(struct artista modificato,char tipologia);
bool modifica_file_utenti(struct utente modificato,char tipologia);
void stampa_struct_artista(struct artista to_print);
void stampa_struct_utente(struct utente to_print);
bool controllo_input(char *string);

int main(){
	char nome[80],password[80],utente_file[80],cognome[80], *txt_admin="admin.csv",*txt_utente="user.csv",*txt_artisti="artisti.csv";
	struct utente utenti[MAX],utente_registrato,admin_loggato;
	struct artista artisti[MAX],artista;
	struct preferenza prefereza_utenti[MAX];
	int risposta,risposta_aut,numero;
	int giorno,mese,anno,id_lol;
	bool condizione=true,app=NULL,admin=false,user=false;
	char *string_pd,dio[200],appogio[200];
	struct utente utente_log;
	do{
		printf("Utente o admin? [0/1]\n");
		scanf("%d",&risposta);	
	}while( risposta<0 || risposta>1 );
	//system("cls");
	
	do{
		
		if(risposta==1){
			printf("inserisci utente e password\n");
			scanf("%s %s", nome,password);
			//system("cls");
			id_lol=autenticazione(nome,password,txt_admin);
			//condizione=controllo_funzioni(app,'l');
			if(id_lol==-1){
				continue;
			}
			if(id_lol>=0){
				admin=true;
				condizione=false;
			}
				
		}
		if(risposta==0){
			printf("Registrazione o login[0,1]\n");
			scanf("%d",&risposta_aut);
			//system("cls");
			if(risposta_aut==1){
				do{
					printf("inserisci utente e password\n");
					scanf("%s %s", nome,password);
					//system("cls");
					id_lol=autenticazione(nome,password,txt_utente);
					if(id_lol==-1){
						continue;
					}
					else {
					//strcpy(appogio,string_pd);
					//utente_log=string_to_struct_utente(appogio);
						user=true;
						condizione=false;
					}
				}while(condizione);
				//printf("Benvenuto %s %s\n",utente_log.nome,utente_log.cognome);
				//condizione=controllo_funzioni(app,'l');
			}
			if(risposta_aut==0){
				printf("Inserire il nome,cognome,user,password e data di nascita[<nome> <cognome> <user> <password> <gg mm aa>]\n");
				scanf("%s %s %s %s %d %d %d",utente_registrato.nome,utente_registrato.cognome,utente_registrato.user,utente_registrato.password,
				&utente_registrato.data_nascita.giorno,&utente_registrato.data_nascita.mese,&utente_registrato.data_nascita.anno);
				//system("cls");
				app=registrazione(utente_registrato);
				condizione=controllo_funzioni(app,'r');
			}
		}
		
		
			
		
	}while(condizione);
	
	int scelta_1,scelta_2,n;
	char scelta_3[20];
	bool condizione_sw=true;
	char string[20];
	struct artista artista_da_modificare,artista_modificato;
	if(admin){
		do{
			printf("[1] per aggiungere, modificare o eliminare degli artisti \n");
			printf("[2] per aggiungere, modificare o eliminare degli utenti \n");
			printf("[3] esci.\n");
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
				
			printf("[1] per aggiungere un %s\n",string);
			printf("[2] per modificare un %s\n",string);
			printf("[3] per eliminare un %s\n",string);
			printf("[4] per uscire \n");
			scanf("%d",&scelta_2);
			//system("cls");
			switch(scelta_2){
				case 1:
					if(scelta_1==1){
						do{
							printf("Inserire il nome:");
							system("pause");
							fgets(artista.nome,80,stdin);
							printf("Inserire numero di generi:");
							scanf("%d",&artista.numero_generi);
							for(int i=0;i<artista.numero_generi;i++){
								printf("Inserire il genere n.%d:",i+1);
								
								fgets(artista.genere[i],80,stdin);
							}
							printf("Inserire il produttore:");
							fgets(artista.produttore,80,stdin);
							printf("Inserire la nazionalita':");
							fgets(artista.nazione,80,stdin);
							printf("Inserire la data di inizio attivita':");
							scanf("%d",&artista.anno_inizio);
							app=aggiungi_artista(artista,n);
							controllo_funzioni(app,'r');
							printf("desidera aggiungere altri artisti?[si/no]\n");
							scanf("%s",scelta_3);
							//system("cls");
						}while(controllo_input(scelta_3));
					}
					else{ 
						do{
							printf("Inserire il nome,cognome,user,password e data di nascita[<nome> <cognome> <user> <password> <gg mm aa>]\n");
							scanf("%s %s %s %s %d %d %d",utente_registrato.nome,utente_registrato.cognome,utente_registrato.user,utente_registrato.password,
							&utente_registrato.data_nascita.giorno,&utente_registrato.data_nascita.mese,&utente_registrato.data_nascita.anno);
							app=registrazione(utente_registrato);
							controllo_funzioni(app,'r');
							printf("desidera aggiungere altri utenti?[si/no]\n");
							scanf("%s",scelta_3);
							//system("cls");
						}while(controllo_input(scelta_3)); 
					} 	
					break;
				case 2:
					char continua[80],*string_da_modificare,app2[200];
					strcpy(continua,"1");
					if(scelta_1==1){
						printf("---Modifica artisti--- \n");
						do{
							
							printf("desideri visualizzare l'elenco degli artisti iscritti?[si/no]\n");
							scanf("%s",scelta_3);
							if(controllo_input(scelta_3)){
								visualizza_elenco('a',txt_artisti);
							}
							printf("inserisci ID dell'artista da modificare\n");
							scanf("%d",&numero);
							string_da_modificare=visualizza_dati_id(numero,txt_artisti);							
							if(strcmp(string_da_modificare,"Errore")==0){
								printf("Sei un coglione\n");
								printf("---Modifica artisti--- \n");
								continue;
							}							
							artista_da_modificare=string_to_struct_artista(string_da_modificare);
							artista_modificato=modifica_dati_struct(artista_da_modificare);
							app=modifica_file_artisti(artista_modificato,'m');
							controllo_funzioni(app,'m');
							printf("desideri continuare a modificare altre informazioni?[1/cud ca vu]\n");
							scanf("%s", continua);
						}while(strcmp(continua,"1")==0);
					}
					
					else{
						struct utente utente_da_modificare,utente_modificato;
						char *string_da_modificare;
						printf("---Modifica utenti--- \n");
						do{
							printf("desideri visualizzare l'elenco degli utenti iscritti?[si/no]\n");
							scanf("%s",scelta_3);
							if(controllo_input(scelta_3)){
								visualizza_elenco('u',txt_utente);
							}
							printf("inserisci ID dell'utente da modificare\n");
							scanf("%d",&numero);
							string_da_modificare=visualizza_dati_id(numero,txt_utente);
							if(strcmp(string_da_modificare,"Errore")==0){
								printf("ritenta.\n");
								continue;
							}
							utente_da_modificare=string_to_struct_utente(string_da_modificare);
							utente_modificato=modifica_dati_struct_utente(utente_da_modificare);
							app=modifica_file_utenti(utente_modificato,'m');
							controllo_funzioni(app,'m');
							printf("desideri continuare a modificare altre informazioni?[si/no]\n");
							scanf("%s", continua);
						}while(controllo_input(continua));
					}
					
					
					break;
				case 3:
					char scelta_elenco[3],scelta_to_continue[3];
					
					int id_to_delete;
					if(scelta_1==1){
						struct artista appoggio;
						do{
							printf("Desideri visualizzare l'elenco degli artisti?[si/no] \n");
							scanf("%s",scelta_elenco);
							if(controllo_input(scelta_elenco)){
								visualizza_elenco('a',txt_artisti);
							}
							printf("Inserire l'ID dell'artista da eliminare:\n");
							scanf("%d",&id_to_delete);
							appoggio.id=id_to_delete;
							app=modifica_file_artisti(appoggio,'e');
							controllo_funzioni(app,'e');
							printf("Desideri eliminare altri artisti?[si/no]\n");
							scanf("%s",scelta_to_continue);
						}while(controllo_input(scelta_to_continue));		
					}
					
					else{
						struct utente appoggio;
						do{
							printf("Desideri visualizzare l'elenco degli utenti?[si/no]\n");
							scanf("%s",scelta_elenco);
							if(controllo_input(scelta_elenco)){
								visualizza_elenco('u',txt_utente);
							}
							printf("Inserire l'ID dell'artista da eliminare:\n");
							scanf("%d",&id_to_delete);
							appoggio.id=id_to_delete;
							app=modifica_file_utenti(appoggio,'e');
							controllo_funzioni(app,'e');
							printf("Desideri eliminare altri utenti?[si/no]\n");
							scanf("%s",scelta_to_continue);
						}while(controllo_input(scelta_to_continue));
					}
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
	if(user){
		char risposta_user[10],*string_id;
		int scelta;
		struct utente dati_utente_log;
		printf("[1] Ricerca \n");
		printf("[2] Ordinamento \n");
		printf("[3] Profilo utente \n");
		printf("[4] Esci\n");
		do{
		scanf("%d",&scelta);	
		switch(scelta){
			case 1:
				break;
			case 2:
				printf("vuoi visualizzare la top 10 ascoltati?[][][]");
				break;
			case 3:
				printf("Desideri visualizzare il tuo profilo?[si/no]\n");
				scanf("%s",risposta_user);
				if(controllo_input(risposta_user)){
					string_id=visualizza_dati_id(id_lol,txt_utente);
					dati_utente_log=string_to_struct_utente(string_id);
				}
				printf("vuoi visualizzare i dati di altri utenti?[si/no]\n");
				scanf("%s",risposta_user);
				if(controllo_input(risposta_user)){
					
				}
				//stampa_struct_utente(dati_utente_log);
				
				break;
			case 4:
				break;
			default:
				printf("memt\n");
			}
		}while(scelta<0 || scelta>4);	
		
		
		
		
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
		app=fprintf(out,"%d;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",id,utente.nome,utente.cognome,utente.user,utente.password,
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
int  autenticazione(char *nome,char *password,char *txt){
	int res=0,id,i=0,risultato;
	bool condizione_admin=true;
	char nome_f[50],cognome_f[50],user_f[50],password_f[50],appoggio[200],string_f[200];
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
			if(strcmp(password_f,password)==0){
				condizione_admin=false;
				risultato=id;
			}
				
	}	
	if(condizione_admin){
		risultato=-1;
	}
	fclose(in);
	return risultato;			
}

bool aggiungi_artista(struct artista artista,int numero_generi){
FILE *in;
	in=fopen("artisti.csv","r");
	char nome[80],genere[80],produttore[80],nazionalita[80],string_f[200];
	int id=0,res,app=0;
	bool condizione=true,condizione_id=false,condizione_user=false,risultato=false;
	//creare funzione per il riutilizzo di id cancellati
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
		if(numero_generi==1)
			app=fprintf(out,"\n%d;%s;%d;%s;%s;%s;%d",id,artista.nome,artista.numero_generi,artista.genere,artista.produttore,artista.nazione,artista.anno_inizio);
		else{
			app=fprintf(out,"\n%d;%s;%d;",id,artista.nome,artista.numero_generi);
			for(int i=0;i<artista.numero_generi;i++){
				fprintf(out,"%s,",artista.genere[i]);
			}
			fprintf(out,";%s;%s;%d",artista.produttore,artista.nazione,artista.anno_inizio);
		}
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
			if(tipologia=='e')
				printf("Cancellazzione effettuata con successo.\n");
			return false;
		}
		else{
			if(tipologia=='l')
				printf("Login non effettuato.\n");
			if(tipologia=='r')
				printf("Registrazione non effettuata.\n");
			if(tipologia=='m')
				printf("Modifica non effettuata.\n");
			if(tipologia=='e')
				printf("Cancellazzione non effettuata.\n");	
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
		printf("ID            NOME          COGNOME           USER        PASSWORD  DATA DI NASCITA\n");
	do{
		if(tipologia=='a'){
			cipolla=string_to_struct_artista(string_f);
			stampa_struct_artista(cipolla);
		}
		if(tipologia== 'u'){
			origano=string_to_struct_utente(string_f);	
			stampa_struct_utente(origano);
		}
	}while(fgets(string_f,300,in)!=NULL);
	fclose(in);
}

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
			condizione=true;
			strcpy(app2,app);	
			if(strcmp(txt,"user.csv")==0){	
				origano=string_to_struct_utente(app);
				printf("ID            NOME         COGNOME            USER        PASSWORD  DATA DI NASCITA\n");
				stampa_struct_utente(origano);
			}
			else{
				cipolla=string_to_struct_artista(app);
				printf("ID            NOME          GENERE      PRODUTTORE         NAZIONE ANNO INIZIO\n");
				stampa_struct_artista(cipolla);	
			}	
		}
	}
	
	fclose(in);
	if(!condizione)
		strcpy(app2,"Errore");
	return app2;
		
}

struct artista string_to_struct_artista(char *string){
	char *carattere,*app;
	strcpy(carattere,",");
	struct artista cipolla;
	cipolla.id=atoi(strtok(string,";"));
	printf("mi offendo qua 1\n");
	strcpy(cipolla.nome,strtok(NULL,";"));
	printf("mi offendo qua 2\n");
	cipolla.numero_generi=atoi(strtok(NULL,";"));
	printf("mi offendo qua 3\n");
	strcpy(app,strtok(NULL,";"));
	for(int i=0;i<cipolla.numero_generi;i++){
		if(i!=cipolla.numero_generi-1){
			printf("almeno ci provo\n");
			strcpy(carattere,",");}
		strcpy(cipolla.genere[i],strtok(app,carattere));
	}
		
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
	origano.data_iscrizione.giorno=atoi(strtok(NULL,";"));
	origano.data_iscrizione.mese=atoi(strtok(NULL,";"));
	origano.data_iscrizione.anno=atoi(strtok(NULL,";"));
	return origano;
}

void stampa_struct_artista(struct artista to_print){
	printf("%2d %15s",to_print.id,to_print.nome);
	for(int i=0;i<to_print.numero_generi;i++)
		printf(" %s ",to_print.genere[i]);
	printf(" %15s %15s %11d\n",to_print.produttore,to_print.nazione,to_print.anno_inizio);	
}

void stampa_struct_utente(struct utente to_print){
	printf("%2d %15s %15s %15s %15s       %2d/%2d/%4d\n",to_print.id,to_print.nome,to_print.cognome,to_print.user,to_print.password,
	to_print.data_nascita.giorno,to_print.data_nascita.mese,to_print.data_nascita.anno);
}

bool controllo_input(char *string){
	bool risultato;
	for(int i=0;i<2;i++)
		string[i]=tolower(string[i]);
	if(strcmp(string,"si")==0)
		risultato=true;
	else
		risultato=false;
	return risultato;
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
		if(condizione){
			printf("Giovan8 ripeti!\n");
			continue;
			}
		printf("Vuoi modificare altri dati?[si/no]\n");
		scanf("%s",scelta);
		if(strcmp(scelta,"si")==0){
			condizione=true;
			stampa_struct_artista(to_modify);
		}
			
	}while(condizione);
	return to_modify;
}

struct utente modifica_dati_struct_utente(struct utente to_modify){
	char scelta[10];
	bool condizione=true;
	do {
		printf("Che dati vuole modificare?(nome,cognome,user,password,data)\n");
		scanf("%s",scelta);
		if(strcmp(scelta,"nome")==0){
			printf("inserire il nuovo nome:");
			scanf("%s",to_modify.nome);
			condizione=false;
		}
		if(strcmp(scelta,"cognome")==0 && condizione){
			printf("inserire il nuovo cognome:");
			scanf("%s",to_modify.cognome);
			condizione=false;
		}
		if(strcmp(scelta,"user")==0 && condizione){
			printf("inserire il nuovo user:");
			scanf("%s",to_modify.user);
			condizione=false;
		}
		if(strcmp(scelta,"password")==0 && condizione){
			printf("inserire la nuova password:");
			scanf("%s",to_modify.password);
			condizione=false;
		}
		if(strcmp(scelta,"data")==0 && condizione){
			printf("inserire una nuova data di nascita[gg mm aa]:");
			scanf("%d %d %d",&to_modify.data_nascita.giorno,&to_modify.data_nascita.mese,&to_modify.data_nascita.anno);
			condizione=false;
		}
		if(condizione){
			printf("Giovan8 ripeti!\n");
			continue;
			}
		printf("Vuoi modificare altri dati?[si/no]\n");
		scanf("%s",scelta);
		if(strcmp(scelta,"si")==0){
			condizione=true;
			stampa_struct_utente(to_modify);
		}		
	}while(condizione);
	return to_modify;
	
}

bool modifica_file_artisti(struct artista modificato,char tipologia){
	FILE *in,*out;
	in=fopen("artisti.csv","r");
	int id,app,dio=0,k=0,lol=0,rosmarino,rosa,n=0;
	struct artista artisti[MAX];
	bool condizione=true,risultato=false,condizione_id=false;
	char string_f[200],gesu[200];
	for(int i=0;fgets(string_f,200,in)!=NULL;i++){
		n++;
		artisti[i]=string_to_struct_artista(string_f);
		if(artisti[i].id==modificato.id){
			condizione_id=true;
			if(tipologia=='m'){
				artisti[i]=modificato;
			}
			if(tipologia=='e'){
				i--;
				n--;	
			}
		}	
	}
	fclose(in);
	if(condizione_id){
		out=fopen("artisti.csv","w");
		for(int i=0;i<n;i++){
			app=fprintf(out,"%d;%s;%s;%s;%s;%d\n",artisti[i].id,artisti[i].nome,artisti[i].genere,artisti[i].produttore,artisti[i].nazione,artisti[i].anno_inizio);
			if(app>0){
				app=0;
				k++;
			}
		}	
		if(n==k)
			risultato=true;
		else
			risultato=false;
		if(condizione_id)
			risultato=true;
		fclose(out);			
	}
	
	return risultato;

}

bool modifica_file_utenti(struct utente modificato,char tipologia){
	FILE *in,*out;
	in=fopen("user.csv","r");
	int n,k=0,app=0;
	char string_f[200];
	bool risultato=false,condizione_id=false;
	struct utente utenti[MAX];
	for(int i=0;fgets(string_f,200,in)!=NULL;i++){
		n++;
		utenti[i]=string_to_struct_utente(string_f);
		if(utenti[i].id==modificato.id){
			condizione_id=true;
			if(tipologia=='m'){
				utenti[i]=modificato;
			}
			if(tipologia=='e'){
				i--;
				n--;	
			}
		}	
	}
	fclose(in);
	if(condizione_id){
		out=fopen("user.csv","w");
		for(int i=0;i<n;i++){
			app=fprintf(out,"%d;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",utenti[i].id,utenti[i].nome,utenti[i].cognome,utenti[i].user,utenti[i].password,
			utenti[i].data_nascita.giorno,utenti[i].data_nascita.mese,utenti[i].data_nascita.anno,utenti[i].data_iscrizione.giorno,
			utenti[i].data_iscrizione.mese,utenti[i].data_iscrizione.anno);
			if(app>0){
				app=0;
				k++;
			}
		}
		if(n==k)
			risultato=true;
		else	
			risultato=false;
		if(condizione_id)
			risultato=true;
		fclose(out);	
	}
	
	return risultato;	
}

