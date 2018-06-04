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
	char genere[80][20];
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
bool aggiungi_artista(struct artista artista);
bool controllo_funzioni(bool app,char tipologia);
bool visualizza_elenco(char tipologia,char *txt);
char * visualizza_dati_id(int id, char *txt);
struct artista string_to_struct_artista(char *string);
struct utente string_to_struct_utente(char *string);
struct artista modifica_dati_struct(struct artista to_modify);
struct utente modifica_dati_struct_utente(struct utente to_modify,char tipologia);
bool modifica_file_artisti(struct artista modificato,char tipologia);
bool modifica_file_utenti(struct utente modificato,char tipologia,char *txt);
void stampa_struct_artista(struct artista to_print);
void stampa_struct_utente(struct utente to_print);
bool controllo_input(char *string);
bool ricerca_artisti(char *string,char tipo,int id_utente);
int algoritmo_ricerca(char *text,char *pattern);
int controllo_nome(char *txt,char *nome);
bool controllo_data_nascita(struct data b_day);
bool preferenze_utente(char *txt);
bool inserimento_ascolti_e_preferenze(int id_artista,int id_utente,char tipologia);
bool controllo_file_preferenze(char * string);
bool aggiungi_admin(struct utente admin);



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
	struct utente admin_to_add;
	if(admin){
		do{
			printf("[1] per aggiungere, modificare o eliminare degli artisti \n");
			printf("[2] per aggiungere, modificare o eliminare degli utenti \n");
			printf("[3] per aggiungere admin\n");
			printf("[4] esci.\n");
			scanf("%d",&scelta_1);
			//system("cls");
			if(scelta_1==1)
				strcpy(string,"artista");
			if(scelta_1==2)
				strcpy(string,"utente");
			if(scelta_1==3)
				strcpy(string,"admin");
			if(scelta_1==4){
				condizione_sw=false;
				continue;
			}
			if(scelta_1<0 || scelta_1>4){
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
							fflush(stdin);
							printf("Inserire il nome:");
							fgets(artista.nome,80,stdin);
							printf("Inserire numero di generi:");
							scanf("%d",&artista.numero_generi);
							for(int i=0;i<artista.numero_generi;i++){
								fflush(stdin);
								printf("Inserire il genere n.%d:",i+1);
								fgets(artista.genere[i],80,stdin);
							}
							fflush(stdin);
							printf("Inserire il produttore:");
							fgets(artista.produttore,80,stdin);
							fflush(stdin);
							printf("Inserire la nazionalita':");
							fgets(artista.nazione,80,stdin);
							fflush(stdin);
							printf("Inserire la data di inizio attivita':");
							scanf("%d",&artista.anno_inizio);
							app=aggiungi_artista(artista);
							controllo_funzioni(app,'r');
							printf("desidera aggiungere altri artisti?[si/no]\n");
							scanf("%s",scelta_3);
							//system("cls");
						}while(controllo_input(scelta_3));
					}
					else if(scelta_1==2){ 
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
					else if(scelta_1==3){
						do{			
							fflush(stdin);
							printf("Inserire il nome:");
							fgets(admin_to_add.nome,80,stdin);
							printf("Inserire il cognome:");
							fflush(stdin);
							fgets(admin_to_add.cognome,80,stdin);
							fflush(stdin);
							printf("Inserire il user:");
							fgets(admin_to_add.user,80,stdin);
							fflush(stdin);
							printf("Inserire la password':");
							fgets(admin_to_add.password,80,stdin);
							fflush(stdin);
							printf("Inserire la data di nascita [gg mm aa]:");
							scanf("%2d %2d %4d",&admin_to_add.data_nascita.giorno,&admin_to_add.data_nascita.mese,&admin_to_add.data_nascita.anno);
							app=aggiungi_admin(admin_to_add);
							controllo_funzioni(app,'r');
							printf("desidera aggiungere altri admin?[si/no]\n");
							scanf("%s",scelta_3);
							//system("cls");
						}while(controllo_input(scelta_3));
					} 	
					break;
				case 2:
					char continua[80],*string_da_modificare,app2[200];
					struct utente admin_modificato;
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
					
					else if(scelta_1==2) {
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
							utente_modificato=modifica_dati_struct_utente(utente_da_modificare,'u');
							app=modifica_file_utenti(utente_modificato,'m',txt_utente);
							controllo_funzioni(app,'m');
							printf("desideri continuare a modificare altre informazioni?[si/no]\n");
							scanf("%s", continua);
						}while(controllo_input(continua));
					}
					else if(scelta_1==3){
						do{
							char *string_da_modificare;
							struct utente admin_da_modificare;
							printf("---Modifica admin--- \n");
							printf("desideri visualizzare l'elenco degli admin iscritti?[si/no]\n");
							scanf("%2s",scelta_3);
							fflush(stdin);
							if(controllo_input(scelta_3)){
								visualizza_elenco('u',txt_admin);
							}
							printf("inserisci ID dell'utente da modificare\n");
							scanf("%d",&numero);
							string_da_modificare=visualizza_dati_id(numero,txt_admin);
							if(strcmp(string_da_modificare,"Errore")==0){
								printf("ritenta.\n");
								continue;
							}
							admin_da_modificare=string_to_struct_utente(string_da_modificare);
							admin_modificato=modifica_dati_struct_utente(admin_da_modificare,'a');			
							app=modifica_file_utenti(admin_modificato,'m',txt_admin);
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
							app=modifica_file_utenti(appoggio,'e',txt_utente);
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
		char risposta_user[10],*string_id,scelta_modifica_dati[10],continua[10];
		int scelta;
		struct utente dati_utente_log,utente_modificato;
		printf("[1] Ricerca artista per ascolto o preferenza \n");
		printf("[2] Ordinamento \n");
		printf("[3] Profilo utente \n");//implementare la ricerca.
		printf("[4] Esci\n");
		do{
			printf("risposta: ");
			scanf("%d",&scelta);	
		switch(scelta){
			case 1://ricerca approssimata
				bool condizione,app;
				char risposta[20],scelta_to_continue[20];
				
				do{
					condizione=true;
					do{
						fflush(stdin);
						printf("inserisci il campo di ricerca[nome][genere][produttore][nazione][anno]\n");
						
						fgets(risposta,80,stdin);						
						if(strcmp(strtok(risposta,"\n"),"nome")==0){
							condizione=false;
							printf("inserisci nome artista\n");
							scanf("%s",risposta);
							app=ricerca_artisti(risposta,'n',id_lol);
						}
						if(strcmp(strtok(risposta,"\n"),"genere")==0){
							printf("inserisci un genere musicale\n");
							condizione=false;
							scanf("%s",risposta);
							app=ricerca_artisti(risposta,'g',id_lol);
						}
						if(strcmp(strtok(risposta,"\n"),"produttore")==0){
							printf("inserisci un produttore\n");
							condizione=false;
							scanf("%s",risposta);
							app=ricerca_artisti(risposta,'p',id_lol);
						}
						if(strcmp(strtok(risposta,"\n"),"nazione")==0){
							printf("inserisci una nazione\n");
							condizione=false;
							scanf("%s",risposta);
							app=ricerca_artisti(risposta,'h',id_lol);
						}
						if(strcmp(strtok(risposta,"\n"),"anno")==0){
							printf("inserisci anno di inizio attivita'\n");
							condizione=false;
							scanf("%s",risposta);
							app=ricerca_artisti(risposta,'a',id_lol);
						}
					}while(condizione);
					printf("Desideri effettuare un'altra ricerca?[si/no]\n");
					scanf("%2s",scelta_to_continue);
				}while(controllo_input(scelta_to_continue));
				break;
			case 2://ordinamento
				printf("vuoi visualizzare la top 10 ascoltati?[][][]");//no Xd
				break;
			case 3://visualizzazione profilo
				printf("Desideri visualizzare il tuo profilo?[si/no]\n");
				scanf("%s",risposta_user);
				if(controllo_input(risposta_user)){
					string_id=visualizza_dati_id(id_lol,txt_utente);
					dati_utente_log=string_to_struct_utente(string_id);
				}
				printf("Vuoi modificare i tuoi dati?[si/no]\n");
				scanf("%s",scelta_modifica_dati);
				if(controllo_input(scelta_modifica_dati)){
						utente_modificato=modifica_dati_struct_utente(dati_utente_log,'u');
						app=modifica_file_utenti(utente_modificato,'m',txt_utente);
						controllo_funzioni(app,'m');
				}
				//stampa_struct_utente(dati_utente_log);
				
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
	bool condizione=true,risultato=false;
	
	id=controllo_nome("user.csv",utente.user);
	if(id==-1)
		condizione=false;
	app=controllo_data_nascita(utente.data_nascita);
	if(!app)
		condizione=false;
	if(condizione){
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

bool aggiungi_artista(struct artista artista){
FILE *in;
	in=fopen("artisti.csv","r");
	char nome[80],genere[80],produttore[80],nazionalita[80],string_f[200];
	int id=0,res,app=0;
	bool condizione=true,risultato=false;
	
	id=controllo_nome("artisti.csv",artista.nome);
	if(id==-1)
		condizione=false;
	if(condizione){
		FILE *out;
		out=fopen("artisti.csv","a");
		if(artista.numero_generi==1)
			app=fprintf(out,"%d;%s;%d;%s;%s;%s;%d",id,strtok(artista.nome,"\n"),artista.numero_generi,strtok(artista.genere[0],"\n"),
			strtok(artista.produttore,"\n"),strtok(artista.nazione,"\n"),artista.anno_inizio);
		else{
			app=fprintf(out,"%d;%s;%d;",id,strtok(artista.nome,"\n"),artista.numero_generi);
			for(int i=0;i<artista.numero_generi;i++){
				fprintf(out,"%s",strtok(artista.genere[i],"\n"));
				if(i!=artista.numero_generi-1)
					fprintf(out,",");
			}
			fprintf(out,";%s;%s;%d\n",strtok(artista.produttore,"\n"),strtok(artista.nazione,"\n"),artista.anno_inizio);
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
			if(tipologia=='a')
				printf("Ascolto effettuato con successo.\n");
			if(tipologia=='i')
				printf("Like salvato con successo.\n");
			if(tipologia=='d')
				printf("Dislike salvato con successo.\n");
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
			if(tipologia=='a')
				printf("Ascolto non effettuato. \n");
			if(tipologia=='i')
				printf("Like non salvato.\n");
			if(tipologia=='d')
				printf("Dislike non salvato.\n");	
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
	char string_f[200],app[200];
	char app2[200];
	bool condizione=false;
	struct artista cipolla;
	struct utente origano;
	while(fgets(string_f,200,in)!=NULL && !condizione){
		strcpy(app,string_f);
		if((atoi(strtok(string_f,";")))==id){
			condizione=true;		
			strcpy(app2,app);
			if(strcmp(txt,"user.csv")==0 || strcmp(txt,"admin.csv")==0){	
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
	char app[100];
	struct artista cipolla;
	cipolla.id=atoi(strtok(string,";"));
	strcpy(cipolla.nome,strtok(NULL,";"));
	cipolla.numero_generi=atoi(strtok(NULL,";"));
	if(cipolla.numero_generi>1){
		strcpy(app,strtok(NULL,";"));
		strcpy(cipolla.produttore,strtok(NULL,";"));
		strcpy(cipolla.nazione,strtok(NULL,";"));
		cipolla.anno_inizio=atoi(strtok(NULL,";"));
		strcpy(cipolla.genere[0],strtok(app,","));	
		for(int i=1;i<cipolla.numero_generi;i++){	
			strcpy(cipolla.genere[i],strtok(NULL,","));				
		}	
	}
	else{
		strcpy(cipolla.genere[0],strtok(NULL,";"));
		strcpy(cipolla.produttore,strtok(NULL,";"));
		strcpy(cipolla.nazione,strtok(NULL,";"));
		cipolla.anno_inizio=atoi(strtok(NULL,";"));	
	}		
	
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
	printf("%2d  %15s %15s %15s %11d ",to_print.id,to_print.nome,to_print.produttore,to_print.nazione,to_print.anno_inizio);
	for(int i=0;i<to_print.numero_generi;i++){		
		printf("%15s",to_print.genere[i]);
	}
	printf("\n");
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
	char scelta[20],scelta_genere[20];
	bool condizione=true,condizione_do_while;
	int num_genere;
	do {
		printf("Che dati vuole modificare?(nome,genere,produttore,nazione,anno)\n");
		scanf("%s",scelta);
		if(strcmp(scelta,"nome")==0){
			printf("inserire il nuovo nome:");
			fflush(stdin);
			fgets(to_modify.nome,100,stdin);
			condizione=false;
		}
		if(strcmp(scelta,"genere")==0 && condizione){
			if(to_modify.numero_generi==0)
				printf("Vuoi aggiungere un genere?[aggiungi]\n");
			else
				printf("Vuoi eliminare o aggiungere un genere?[elimina/aggiungi]\n");
			scanf("%s",scelta_genere);
			if(to_modify.numero_generi==0 && strcmp(scelta_genere,"elimina")==0){
				printf("Giovan8 :'( ");
				continue;
			}
			if(strcmp(scelta_genere,"aggiungi")==0){
				printf("inserire il nuovo genere:");
				fflush(stdin);
				fgets(to_modify.genere[to_modify.numero_generi],100,stdin);
				strtok(to_modify.genere[to_modify.numero_generi],"\n");
				to_modify.numero_generi++;
				condizione=false;
			}
			if(strcmp(scelta_genere,"elimina")==0){
				printf("Che genere vuoi eliminare?\n");
				for(int i=0;i<to_modify.numero_generi;i++){
					printf("NUM %d :%s\n",i+1,to_modify.genere[i]);
				}
				scanf("%d",&num_genere);
				for(int i=num_genere-1;i<to_modify.numero_generi-1;i++){
					strcpy(to_modify.genere[i],to_modify.genere[i+1]);
				}
				to_modify.numero_generi--;
				condizione=false;	
			}

		}
		if(strcmp(scelta,"produttore")==0 && condizione){
			printf("inserire il nuovo produttore:");
			fflush(stdin);
			fgets(to_modify.produttore,100,stdin);
			condizione=false;
		}
		if(strcmp(scelta,"nazione")==0 && condizione){
			printf("inserire la nuova nazione:");
			fflush(stdin);
			fgets(to_modify.nazione,100,stdin);
			condizione=false;
		}
		if(strcmp(scelta,"anno")==0 && condizione){
			do{
				printf("inserire il nuovo anno:");
				scanf("%d",&to_modify.anno_inizio);
				condizione=false;
				time_t rawtime;
			 	time (&rawtime);
			    struct tm* time;
			    time = localtime(&rawtime);
				if(to_modify.anno_inizio>time->tm_year+1900)
					condizione_do_while=true;
			}while(condizione_do_while);	
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

//inserire controllo sulla data di nascita & controllo se l'user è già in USO
struct utente modifica_dati_struct_utente(struct utente to_modify,char tipologia){
	char scelta[10];
	bool condizione=true,app=true;
	int valore_ritorno;
	char hold[100];
	
	do {
		printf("Che dati vuole modificare?(nome,cognome,user,password,data)\n");
		fflush(stdin);
		fgets(scelta,80,stdin);
		strtok(scelta,"\n");
		if(strcmp(scelta,"nome")==0){
			printf("inserire il nuovo nome:");
			fflush(stdin);
			fgets(hold,80,stdin);
			strcpy(to_modify.nome,strtok(hold,"\n"));
			condizione=false;
		}
		if(strcmp(scelta,"cognome")==0 && condizione){
			printf("inserire il nuovo cognome:");
			fflush(stdin);
			fgets(hold,80,stdin);
			strcpy(to_modify.cognome,strtok(hold,"\n"));
			condizione=false;
		}
		if(strcmp(scelta,"user")==0 && condizione){
			do{
				printf("inserire il nuovo user(sono validi solo user senza spazi): ");
				scanf("%s",to_modify.user);
				fflush(stdin);
				condizione=false;
				if(tipologia=='u'){
					valore_ritorno=controllo_nome("utente.txt",to_modify.user);	
				}
				else
					valore_ritorno=controllo_nome("admin.txt",to_modify.user);		
				
			}while(valore_ritorno==-1);
		}
		if(strcmp(scelta,"password")==0 && condizione){
			printf("inserire la nuova password(sono valide solo password senza spazi): ");
			scanf("%s",to_modify.password);
			fflush(stdin);
			condizione=false;
		}
		if(strcmp(scelta,"data")==0 && condizione){
			do{
				printf("inserire una nuova data di nascita[gg mm aa]:");
				scanf("%d %d %d",&to_modify.data_nascita.giorno,&to_modify.data_nascita.mese,&to_modify.data_nascita.anno);
				condizione=false;
				app=controllo_data_nascita(to_modify.data_nascita);
			}while(!app);
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
			if(artisti[i].numero_generi==1)
				app=fprintf(out,"%d;%s;%d;%s;%s;%s;%d\n",artisti[i].id,artisti[i].nome,artisti[i].numero_generi,artisti[i].genere[0],artisti[i].produttore,artisti[i].nazione,artisti[i].anno_inizio);
			else{
				fprintf(out,"%d;%s;%d;",artisti[i].id,artisti[i].nome,artisti[i].numero_generi);
				for(int j=0;j<artisti[i].numero_generi;j++){
					fprintf(out,"%s",artisti[i].genere[j]);
					if(j!=artisti[i].numero_generi-1)
						fprintf(out,",");
				}
				app=fprintf(out,";%s;%s;%d\n",artisti[i].produttore,artisti[i].nazione,artisti[i].anno_inizio);
			}
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

bool modifica_file_utenti(struct utente modificato,char tipologia,char *txt){
	FILE *in,*out;
	in=fopen(txt,"r");
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
		out=fopen(txt,"w");
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

//inserire ricerca per anno grz;;
bool ricerca_artisti(char *string,char tipo,int id_utente){
	struct artista array[MAX];
	struct punti{
		struct artista array;
		int punti;
	};
	FILE *in;
	struct punti classifica[MAX],app;
	char string_f[200],string_ricerca[50],risposta[100];
	int n=0,punteggio_finale[MAX],max,min,punteggio_generi;
	int lung_string_ricerca,differenza_lunghezze=0,m,lung_pattern,punteggio_parziale[MAX];
	int posizione_vettore,id_artista,vettore_posizioni[MAX]={-1};
	int pt,h=0;
	bool match_positivo=false,condizione_secondo_ciclo=true,condizione_generi=false;
	bool risultato,condizione=true,var=false;
	bool citronella=true;
	in=fopen("artisti.csv","r");
	for(int i=0;fgets(string_f,200,in)!=NULL;i++){
		classifica[i].array=string_to_struct_artista(string_f);
		n++;
	}
	fclose(in);
	for(int i=0;i<n;i++){
		if(tipo=='n'){
			strcpy(string_ricerca,classifica[i].array.nome);
			var=true;			
		}
		if(tipo=='g'){
			condizione_generi=true;
			var=true;			
		}
		if(tipo=='p'){
			strcpy(string_ricerca,classifica[i].array.produttore);
			var=true;			
		}
		if(tipo=='h'){
			strcpy(string_ricerca,classifica[i].array.nazione);
			var=true;			
		}
		if(tipo=='a'){
			condizione_secondo_ciclo=false;
			if(classifica[i].array.anno_inizio==atoi(string)){
				printf("anno trovato\n");
				printf("ID             NOME      PRODUTTORE         NAZIONE ANNO INIZIO       GENERE/I\n");
				stampa_struct_artista(classifica[i].array);
				var=true;
				continue;
			}
		}
				
		lung_string_ricerca=strlen(string_ricerca);
		lung_pattern=strlen(string);
		differenza_lunghezze=lung_string_ricerca-lung_pattern;
		
		if(condizione_generi){
			for(int h=0;h<classifica[i].array.numero_generi;h++){
				strcpy(string_ricerca,classifica[i].array.genere[h]);
				punteggio_generi=0;
				lung_string_ricerca=strlen(string_ricerca);
				lung_pattern=strlen(string);
				differenza_lunghezze=lung_string_ricerca-lung_pattern;
				
				punteggio_generi=algoritmo_ricerca(string_ricerca,string);
				
				if(punteggio_generi==lung_pattern && lung_pattern==lung_string_ricerca){
					if(condizione_secondo_ciclo){
						printf("Genere trovato \n");	
						printf("ID             NOME       PRODUTTORE         NAZIONE ANNO INIZIO       GENERE/I\n");
					}					
					h=classifica[i].array.numero_generi;
					stampa_struct_artista(classifica[i].array);
					condizione_secondo_ciclo=false;
					continue;
				}
				if(h==0)
					punteggio_finale[i]=punteggio_generi;
				if(punteggio_generi>punteggio_finale[i]  && h>0)
					punteggio_finale[i]=punteggio_generi;
							
			}
			classifica[i].punti=punteggio_finale[i];
		}
		else{
			punteggio_finale[i]=algoritmo_ricerca(string_ricerca,string);
			if(punteggio_finale[i]==lung_pattern && lung_pattern==lung_string_ricerca){
				printf("Artista trovato\n");
				printf("ID             NOME      PRODUTTORE          NAZIONE ANNO INIZIO       GENERE/I\n");
				stampa_struct_artista(classifica[i].array);
				posizione_vettore=i;
				id_artista=classifica[i].array.id;
				condizione_secondo_ciclo=false;
				continue;
			}
			classifica[i].punti=punteggio_finale[i];
		}
		classifica[i].punti=punteggio_finale[i];
	}
	
	if(condizione_secondo_ciclo){
		for(int i=0;i<n-1;i++){//ordinamento per punteggio crescente
			min=i;
			for(int j=i+1;j<n;j++){
				if(classifica[j].punti<classifica[min].punti){
					min=j;
				}
			}
			app=classifica[min];
			classifica[min]=classifica[i];
			classifica[i]=app;
		}
		
		max=classifica[n-1].punti;
		printf("Forse cercavi:\n");
		printf("pt. ID             NOME      PRODUTTORE         NAZIONE ANNO INIZIO        GENERE/I\n");
		for(int i=n-1;i>=0 && condizione_secondo_ciclo;i--){
			if(classifica[i].punti==max || (max-classifica[i].punti)==1){//regole di visualizzazione
				printf("[%d] ",h);
				stampa_struct_artista(classifica[i].array);
				h++;
			}	
		}	
	}
	if(!var)
		printf("artista non trovato\n");
	
	if(condizione_secondo_ciclo){
		do{
			printf("Che artista andavi cercando?(inserisci pt.)\n");
			scanf("%d",&pt);
		}while(pt>h-1 || pt<0);
		do{
			printf("Vuoi ascoltare o lasciare una preferenza?[ascolto/preferenza]\n");
			fflush(stdin);
			fgets(risposta,100,stdin);
			if(strcmp(strtok(risposta,"\n"),"ascolto")==0)
				citronella=false;
			else if (strcmp(strtok(risposta,"\n"),"preferenza")==0 && citronella)
				citronella=false;		
		}while(citronella);
		if(strcmp(strtok(risposta,"\n"),"ascolto")==0){
			printf("Hai appena ascoltato:%s\n",classifica[n-(1+pt)].array.nome);
			risultato=inserimento_ascolti_e_preferenze(classifica[n-(1+pt)].array.id,id_utente,'a');
			controllo_funzioni(risultato,'a');
		}
				
		if(strcmp(strtok(risposta,"\n"),"preferenza")==0){
			do{
				printf("Like o dislike?[like/dislike]\n");
				fflush(stdin);
				fgets(risposta,100,stdin);
				if(strcmp(strtok(risposta,"\n"),"like")==0){
					risultato=inserimento_ascolti_e_preferenze(classifica[n-(1+pt)].array.id,id_utente,'l');
					condizione=false;
					controllo_funzioni(risultato,'i');					
				}
				else if(strcmp(strtok(risposta,"\n"),"dislike")==0){
					risultato=inserimento_ascolti_e_preferenze(classifica[n-(1+pt)].array.id,id_utente,'d');
					condizione=false;
					controllo_funzioni(risultato,'d');
					}
			}while(condizione);
		}
	}
	if(!condizione_secondo_ciclo && var){
		do{
			citronella=true;
			printf("Vuoi ascoltare o lasciare una preferenza?[ascolto/preferenza]\n");
			fflush(stdin);
			fgets(risposta,100,stdin);		
			if(strcmp(strtok(risposta,"\n"),"ascolto")==0)
				citronella=false;
			else if (strcmp(strtok(risposta,"\n"),"preferenza")==0 && citronella)
				citronella=false;
		}while(citronella);

		if(strcmp(strtok(risposta,"\n"),"ascolto")==0){
			printf("Hai appena ascoltato:%s\n",classifica[posizione_vettore].array.nome);
			risultato=inserimento_ascolti_e_preferenze(id_artista,id_utente,'a');
			controllo_funzioni(risultato,'a');
		}
		if(strcmp(strtok(risposta,"\n"),"preferenza")==0){
			do{
				printf("Like o dislike?[like/dislike]\n");
				fflush(stdin);
				fgets(risposta,100,stdin);
				if(strcmp(strtok(risposta,"\n"),"like")==0){
					risultato=inserimento_ascolti_e_preferenze(id_artista,id_utente,'l');
					condizione=false;
					controllo_funzioni(risultato,'i');					
				}
				else if(strcmp(strtok(risposta,"\n"),"dislike")==0){
					risultato=inserimento_ascolti_e_preferenze(id_artista,id_utente,'d');
					condizione=false;
					controllo_funzioni(risultato,'d');
					}
			}while(condizione);	
		}
	}

}

int algoritmo_ricerca(char *text,char *pattern){
	int lung_string_ricerca,lung_pattern,differenza_lunghezze;
	int m,punteggio_parziale,punteggio_finale;
	lung_string_ricerca=strlen(text);
	lung_pattern=strlen(pattern);
	differenza_lunghezze=lung_string_ricerca-lung_pattern;
	for(int j=0;j<=differenza_lunghezze;j++){
		m=0;
		punteggio_parziale=0;
		for(int l=j;m<lung_pattern;l++){ 
			if(text[l]==pattern[m]){
				punteggio_parziale++;
			}	
			m++;
		}
		if(lung_string_ricerca==lung_pattern && punteggio_parziale==lung_pattern){
			punteggio_finale=punteggio_parziale;
			continue;
		}
		if(punteggio_parziale==lung_pattern){
			punteggio_finale=punteggio_parziale;
			continue;
		}
		if(j==0)
			punteggio_finale=punteggio_parziale;
		if(punteggio_parziale>punteggio_finale  && j>0)
			punteggio_finale=punteggio_parziale;
	}
	return punteggio_finale;
}


int controllo_nome(char *nome,char *txt){
	FILE *in;
	in=fopen(txt,"r");
	struct utente app;
	struct artista app2;
	int risultato=0;
	char string_f[200];
	while(fgets(string_f,200,in)!=NULL && risultato!=-1){
		if(strcmp(txt,"user.csv")==0 || strcmp(txt,"admin.csv")==0){
			app.id=atoi(strtok(string_f,";"));
			strcpy(app.nome,strtok(NULL,";"));
			strcpy(app.cognome,strtok(NULL,";"));
			strcpy(app.user,strtok(NULL,";"));
			risultato=app.id;
			if(strcmp(app.user,nome)==0)
				risultato=-1;		
		}
		if(strcmp(txt,"artisti.csv")==0){
			app2.id=atoi(strtok(string_f,";"));
			strcpy(app2.nome,strtok(NULL,";"));
			risultato=app2.id;
			if(strcmp(app2.nome,nome)==0)
				risultato=-1;
		}
	}
	return risultato;
}

bool controllo_data_nascita(struct data b_day){
	time_t rawtime;
 	time (&rawtime);
    struct tm* time;
    time = localtime(&rawtime);
    bool risultato=true;
	if(b_day.giorno<0 || b_day.giorno>31)
		risultato=false;
	if(b_day.mese<0 || b_day.mese>12)
		risultato=false;
	if(b_day.anno<(time->tm_year+1900)-18 || b_day.anno<(time->tm_year+1900) || b_day.anno<(time->tm_year+1850))
		risultato=false;
	if(b_day.mese==1 || b_day.mese==3 || b_day.mese==5 || b_day.mese==7 || b_day.mese==8 || b_day.mese==10 || b_day.mese==12)
		risultato=true;
	if(b_day.mese==4 || b_day.mese==6 || b_day.mese==9 || b_day.mese==11){
		if(b_day.giorno<31)
			risultato=true;
		else
			risultato=false;
	}
	if(b_day.mese==2){
		if((b_day.anno%4)==0){
			if(b_day.giorno<30)
				risultato=true;
			else
				risultato=false;
		}
		else{
			if(b_day.giorno<29)
				risultato=true;
			else
				risultato=false;
		}
	}
	return risultato;
}


bool inserimento_ascolti_e_preferenze(int id_artista,int id_utente,char tipologia){
	FILE *out;
	int app;
	bool risultato,controllo;
	char string_f[200];
	out=fopen("preferenze_ascolto.csv","a");
	if(tipologia=='a')
		sprintf(string_f,"%d;%d;ascoltato\n",id_utente,id_artista);
	if(tipologia=='l')
		sprintf(string_f,"%d;%d;like\n",id_utente,id_artista);
	if(tipologia=='d')
		sprintf(string_f,"%d;%d;dislike\n",id_utente,id_artista);
	controllo=controllo_file_preferenze(string_f);
	if(controllo)
		app=fprintf(out,string_f);	
	if(app>0)
		risultato=true;
	else
		risultato=false;
	fclose(out);
	return risultato;
}

bool controllo_file_preferenze(char * string){
	FILE *in;
	in=fopen("preferenze_ascolto.csv","r");
	bool risultato=true;
	char string_f[200];
	while(fgets(string_f,200,in)!=NULL && risultato){
		if(strcmp(strtok(string,"\n"),string_f)==0)
			risultato=false;
	}
	return risultato;
}

bool aggiungi_admin(struct utente admin){
	bool condizione,var1=false,app2=true;
	int app,risultato;
	condizione=true;
	FILE *in;
	app=controllo_nome("admin.csv",strtok(admin.user,"\n"));
	app2=controllo_data_nascita(admin.data_nascita);
	if(app==-1 && !app2)
		condizione=false;
	if(condizione){
		in=fopen("admin.csv","a");
		time_t rawtime;
	 	time (&rawtime);
	    struct tm* time;
	    time = localtime(&rawtime);
		risultato=fprintf(in,"%d;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",app+1,strtok(admin.nome,"\n"),strtok(admin.cognome,"\n"),admin.user,strtok(admin.password,"\n"),
		admin.data_nascita.giorno,admin.data_nascita.mese,admin.data_nascita.anno,time->tm_mday,time->tm_mon,time->tm_year+1900);
		if(risultato>0)
			var1=true;
	}
	return var1;
}




















