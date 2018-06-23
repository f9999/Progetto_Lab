#include "function.h"
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
	char tipo[10];
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
	int id_utente,id_artista;
	char scelta[15];
};



bool controllo_data_nascita(struct data b_day){
	time_t rawtime;
 	time (&rawtime);
    struct tm* time;
    time  =  localtime(&rawtime);
    bool risultato = true;
	if(b_day.giorno <= 0 || b_day.giorno>31)
		risultato = false;
	if(b_day.mese <= 0 || b_day.mese>12)
		risultato = false;
	if(!(b_day.anno <= (time->tm_year+1900)-18 && b_day.anno>(time->tm_year+1800)))
		risultato = false;
	if(b_day.anno >= (time->tm_year+1900)-18)
		 if(b_day.mese >= time->tm_mon+1)
		 	if(b_day.giorno>time->tm_mday)
				risultato = false;
	if((b_day.mese == 1 || b_day.mese == 3 || b_day.mese == 5 || b_day.mese == 7 || b_day.mese == 8 || b_day.mese == 10 || b_day.mese == 12) && risultato)
		risultato = true;
	if((b_day.mese == 4 || b_day.mese == 6 || b_day.mese == 9 || b_day.mese == 11) && risultato){
		if(b_day.giorno<31)
			risultato = true;
		else
			risultato = false;
	}
	if((b_day.mese == 2) && risultato){
		if((b_day.anno%4) == 0){
			if(b_day.giorno<30)
				risultato = true;
			else
				risultato = false;
		}
		else{
			if(b_day.giorno<29)
				risultato = true;
			else
				risultato = false;
		}
	}
	return risultato;
}

struct utente input_registrazione(){
	struct utente app;
	int var = -1;
	char string_f[100],*pt;
	bool condizione = true;
	printf("Inserire il nome:");
	fflush(stdin);
	fgets(string_f,40,stdin);
	strcpy(app.nome,strtok(string_f,"\n"));
	printf("Inserire il cognome:");
	fflush(stdin);
	fgets(string_f,40,stdin);
	strcpy(app.cognome,strtok(string_f,"\n"));
	printf("Inserire l'user(senza spazi):");
	do{
		fflush(stdin);
		fgets(string_f,40,stdin);
		strcpy(app.user,strtok(string_f,"\n"));
		pt = strtok(string_f," ");
		if(strcmp(pt,app.user)!= 0){
			printf("Reinserire l'user'(senza spazi):");
			continue;
		}
		var = controllo_nome(app.user,"user.csv");
		if(var == -1)
			printf("User gia' in uso\nReinserire l'user'(senza spazi):");
		else{
			app.id = var+1;
		}
	}while(var == -1);

	do{
		printf("Inserire la password(Minimo 6 caratteri):");
		fflush(stdin);
		fgets(string_f,40,stdin);
		strcpy(app.password,strtok(string_f,"\n"));
	}while(strlen(app.password)<6);

	do{
		app.data_nascita.giorno = 1;
		app.data_nascita.mese = 1;
		app.data_nascita.anno = 1999;
		do{
			printf("Inserire il giorno di nascita(1-31):");
			fflush(stdin);
			fgets(string_f,3,stdin);
			app.data_nascita.giorno = atoi(string_f);
			if(!controllo_data_nascita(app.data_nascita)){
				printf("Reinserisci\n");
				condizione = false;
			}
			else
				condizione = true;
		}while(!condizione);

		do{
			printf("Inserire il mese di nascita(1-12):");
			fflush(stdin);
			fgets(string_f,3,stdin);
			app.data_nascita.mese = atoi(string_f);
			if(!controllo_data_nascita(app.data_nascita)){
				printf("Reinserisci\n");
				condizione = false;
			}
			else
				condizione = true;
		}while(!condizione);
		do{
			printf("Inserire l'anno di nascita(1900-2000):");
			fflush(stdin);
			fgets(string_f,5,stdin);
			app.data_nascita.anno = atoi(string_f);
			if(!controllo_data_nascita(app.data_nascita)){
				printf("Reinserisci\n");
				condizione = false;
			}
			else
				condizione = true;
		}while(!condizione);
	}while(!controllo_data_nascita(app.data_nascita));
	strcpy(app.tipo,"user");
	return app;
}

//funzionante per utenti
bool registrazione(struct utente utente){
	char nome[80],cognome[80],user[80],string_f[200];
	int id = 0,res,app = 0;
	bool condizione = true,risultato;
	id = controllo_nome(utente.user,"user.csv");
	FILE *out;
	out = fopen("user.csv","a");
	time_t rawtime;
 	time (&rawtime);
    struct tm* time;
    time  =  localtime(&rawtime);
	app = fprintf(out,"%d;%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",utente.id,utente.nome,utente.cognome,utente.user,utente.password,utente.tipo,
	utente.data_nascita.giorno,utente.data_nascita.mese,utente.data_nascita.anno,time->tm_mday,time->tm_mon+1,time->tm_year+1900);
	fclose(out);
	if(app>0){
		risultato = true;
	}

	else
		risultato = false;
	return risultato;

}

//funzionante per utenti e admin
struct utente  autenticazione(char *nome,char *password){
	int res = 0,id,i = 0,risultato;
	bool condizione_admin = true;
	struct utente var;
	char nome_f[50],cognome_f[50],user_f[50],password_f[50],appoggio[200],string_f[200];
	FILE *in;
	in = fopen("user.csv","r");
	rewind(in);

	while(condizione_admin && fgets(string_f,200,in)!= NULL){
		var = string_to_struct_utente(string_f);
		if(strcmp(var.user,nome) == 0)
			if(strcmp(var.password,password) == 0){
				condizione_admin = false;
			}

	}
	if(condizione_admin){
		var.id = -1;
	}
	fclose(in);
	return var;
}

bool aggiungi_artista(struct artista artista){
	FILE *in;
	in = fopen("artisti.csv","r");
	char nome[80],genere[80],produttore[80],nazionalita[80],string_f[200];
	int id = 0,res,app = 0;
	bool condizione = true,risultato = false;
	id = controllo_nome(artista.nome,"artisti.csv");
	if(id == -1)
		condizione = false;
	if(condizione){
		FILE *out;
		out = fopen("artisti.csv","a");
		if(artista.numero_generi == 1)
			app = fprintf(out,"%d;%s;%d;%s;%s;%s;%d",id+1,strtok(artista.nome,"\n"),artista.numero_generi,strtok(artista.genere[0],"\n"),
			strtok(artista.produttore,"\n"),strtok(artista.nazione,"\n"),artista.anno_inizio);
		else{
			app = fprintf(out,"%d;%s;%d;",id+1,strtok(artista.nome,"\n"),artista.numero_generi);
			for(int i = 0;i<artista.numero_generi;i++){
				fprintf(out,"%s",strtok(artista.genere[i],"\n"));
				if(i!= artista.numero_generi-1)
					fprintf(out,",");
			}
			fprintf(out,";%s;%s;%d\n",strtok(artista.produttore,"\n"),strtok(artista.nazione,"\n"),artista.anno_inizio);
		}
		fclose(out);
	}
	if(app>0)
		risultato = true;
	else
		risultato = false;
	return risultato;

}

bool controllo_funzioni(bool app,char tipologia){
	if(app){
			if(tipologia == 'l')
				printf("Login effettuato con successo.\n");
			if(tipologia == 'r')
				printf("Registrazione effettuata con successo.\n");
			if(tipologia == 'm')
				printf("Modifica effettuata con successo.\n");
			if(tipologia == 'e')
				printf("Cancellazzione effettuata con successo.\n");
			if(tipologia == 'a')
				printf("Ascolto effettuato con successo.\n");
			if(tipologia == 'i')
				printf("Like salvato con successo.\n");
			if(tipologia == 'd')
				printf("Dislike salvato con successo.\n");
			return false;
		}
		else{
			if(tipologia == 'l')
				printf("Login non effettuato.\n");
			if(tipologia == 'r')
				printf("Registrazione non effettuata.\n");
			if(tipologia == 'm')
				printf("Modifica non effettuata.\n");
			if(tipologia == 'e')
				printf("Cancellazzione non effettuata.\n");
			if(tipologia == 'a')
				printf("Ascolto non effettuato. \n");
			if(tipologia == 'i')
				printf("Like non salvato.\n");
			if(tipologia == 'd')
				printf("Dislike non salvato.\n");
			return true;
		}
}

bool visualizza_elenco(char tipologia,char *txt){
	FILE *in;
	in = fopen(txt,"r");
	char string_f[300];
	fgets(string_f,300,in);
	struct artista cipolla;
	struct utente origano;
	if(tipologia ==  'a')
		printf("ID             NOME      PRODUTTORE         NAZIONE ANNO INIZIO       GENERE/I\n");
	if(tipologia ==  'u' || tipologia ==  's')
		printf("ID            NOME          COGNOME           USER        PASSWORD  DATA DI NASCITA\n");

	do{
		if(tipologia == 'a'){
			cipolla = string_to_struct_artista(string_f);
			stampa_struct_artista(cipolla);
		}
		if(tipologia ==  'u'){
			origano = string_to_struct_utente(string_f);
			if(strcmp(origano.tipo,"user") == 0)
				stampa_struct_utente(origano);
		}
		if(tipologia ==  's'){
			origano = string_to_struct_utente(string_f);
			if(strcmp(origano.tipo,"admin") == 0)
				stampa_struct_utente(origano);
		}
	}while(fgets(string_f,300,in)!= NULL);
	fclose(in);
}

char *  visualizza_dati_id(int id, char *txt,char tipologia,char* string){
	FILE *in;
	in = fopen(txt,"r");
	char string_f[200],app[200];
	bool condizione = false;
	struct artista cipolla;
	struct utente origano;
	while(fgets(string_f,200,in)!= NULL && !condizione){
		strcpy(app,string_f);
		strcpy(string,app);
		cipolla.id = -1;
		origano.id = -1;
		if(tipologia == 'u' || tipologia == 's')
			origano = string_to_struct_utente(string_f);
		if(tipologia == 'a')
			cipolla = string_to_struct_artista(string_f);
		if((tipologia == 'u' || tipologia == 's') && origano.id == id){
			if(strcmp(txt,"user.csv") == 0 && tipologia == 'u' && strcmp(origano.tipo,"user") == 0){
				condizione = true;
				printf("ID            NOME         COGNOME            USER        PASSWORD  DATA DI NASCITA\n");
				stampa_struct_utente(origano);
				continue;
			}
			else if(strcmp(txt,"user.csv") == 0 && tipologia == 's' && strcmp(origano.tipo,"admin") == 0){
				condizione = true;
				printf("ID            NOME         COGNOME            USER        PASSWORD  DATA DI NASCITA\n");
				stampa_struct_utente(origano);
				continue;
			}
		}
		if(tipologia == 'a' && cipolla.id == id){
			if(strcmp(txt,"artisti.csv") == 0){
				condizione = true;
				printf("ID            NOME          GENERE      PRODUTTORE         NAZIONE ANNO INIZIO\n");
				stampa_struct_artista(cipolla);
				continue;
			}
		}
	}
	fclose(in);
	if(!condizione)
		strcpy(string,"Errore");

}

struct artista string_to_struct_artista(char *string){
	char app[100];
	struct artista cipolla;
	cipolla.id = atoi(strtok(string,";"));
	strcpy(cipolla.nome,strtok(NULL,";"));
	cipolla.numero_generi = atoi(strtok(NULL,";"));
	if(cipolla.numero_generi>1){
		strcpy(app,strtok(NULL,";"));
		strcpy(cipolla.produttore,strtok(NULL,";"));
		strcpy(cipolla.nazione,strtok(NULL,";"));
		cipolla.anno_inizio = atoi(strtok(NULL,";"));
		strcpy(cipolla.genere[0],strtok(app,","));
		for(int i = 1;i<cipolla.numero_generi;i++){
			strcpy(cipolla.genere[i],strtok(NULL,","));
		}
	}
	else{
		strcpy(cipolla.genere[0],strtok(NULL,";"));
		strcpy(cipolla.produttore,strtok(NULL,";"));
		strcpy(cipolla.nazione,strtok(NULL,";"));
		cipolla.anno_inizio = atoi(strtok(NULL,";"));
	}

	return cipolla;
}

struct utente string_to_struct_utente(char *string){
	struct utente origano;
	origano.id = atoi(strtok(string,";"));
	strcpy(origano.nome,strtok(NULL,";"));
	strcpy(origano.cognome,strtok(NULL,";"));
	strcpy(origano.user,strtok(NULL,";"));
	strcpy(origano.password,strtok(NULL,";"));
	strcpy(origano.tipo,strtok(NULL,";"));
	origano.data_nascita.giorno = atoi(strtok(NULL,";"));
	origano.data_nascita.mese = atoi(strtok(NULL,";"));
	origano.data_nascita.anno = atoi(strtok(NULL,";"));
	origano.data_iscrizione.giorno = atoi(strtok(NULL,";"));
	origano.data_iscrizione.mese = atoi(strtok(NULL,";"));
	origano.data_iscrizione.anno = atoi(strtok(NULL,";"));
	return origano;
}

void stampa_struct_artista(struct artista to_print){
	printf("%2d  %15s %15s %15s %11d ",to_print.id,to_print.nome,to_print.produttore,to_print.nazione,to_print.anno_inizio);
	for(int i = 0;i<to_print.numero_generi;i++){
		printf("%15s ",to_print.genere[i]);
	}
	printf("\n");
}

void stampa_struct_utente(struct utente to_print){
	printf("%2d %15s %15s %15s %15s       %2d/%2d/%4d\n",to_print.id,to_print.nome,to_print.cognome,to_print.user,to_print.password,
	to_print.data_nascita.giorno,to_print.data_nascita.mese,to_print.data_nascita.anno);
}


struct artista modifica_dati_struct(struct artista to_modify){
	char scelta[20],scelta_genere[20],app[20],franco;
	bool condizione = true,condizione_do_while;
	int num_genere;
	do {
		condizione = true;
		printf("Che dati vuole modificare?<nome><genere><produttore><nazione><anno>)\n");
		fflush(stdin);
		fgets(scelta,20,stdin);
		strtok(scelta,"\n");
		if(strcmp(scelta,"nome") == 0){
			printf("Inserire il nuovo nome:");
			fflush(stdin);
			fgets(to_modify.nome,100,stdin);
			strtok(to_modify.nome,"\n");
			condizione = false;
		}
		if(strcmp(scelta,"genere") == 0 && condizione){
			if(to_modify.numero_generi == 0){
				printf("Aggiungi genere\n");
				strcpy(scelta_genere,"aggiungi");
			}
			else{
				printf("Vuoi eliminare o aggiungere un genere?[elimina/aggiungi]\n");
				fflush(stdin);
				fgets(scelta_genere,20,stdin);
				strtok(scelta_genere,"\n");
			}
			if(strcmp(scelta_genere,"aggiungi") == 0){
				printf("inserire il nuovo genere:");
				fflush(stdin);
				fgets(to_modify.genere[to_modify.numero_generi],100,stdin);
				strtok(to_modify.genere[to_modify.numero_generi],"\n");
				to_modify.numero_generi++;
				condizione = false;
			}
			if(strcmp(scelta_genere,"elimina") == 0){
				printf("Che genere vuoi eliminare?\n");
				for(int i = 0;i<to_modify.numero_generi;i++){
					printf("NUM %d :%s\n",i+1,to_modify.genere[i]);
				}
				fflush(stdin);
				fgets(app,3,stdin);
				num_genere = atoi(app);
				for(int i = num_genere-1;i<to_modify.numero_generi-1;i++){
					strcpy(to_modify.genere[i],to_modify.genere[i+1]);
				}
				to_modify.numero_generi--;
				condizione = false;
			}

		}
		if(strcmp(scelta,"produttore") == 0 && condizione){
			printf("Inserire il nuovo produttore:");
			fflush(stdin);
			fgets(to_modify.produttore,100,stdin);
			strtok(to_modify.produttore,"\n");
			condizione = false;
		}
		if(strcmp(scelta,"nazione") == 0 && condizione){
			printf("Inserire la nuova nazione:");
			fflush(stdin);
			fgets(to_modify.nazione,100,stdin);
			strtok(to_modify.nazione,"\n");
			condizione = false;
		}
		if(strcmp(scelta,"anno") == 0 && condizione){
			do{
				printf("inserire il nuovo anno:");
				fflush(stdin);
				fgets(app,5,stdin);
				to_modify.anno_inizio = atoi(app);
				condizione = false;
				time_t rawtime;
			 	time (&rawtime);
			    struct tm* time;
			    time  =  localtime(&rawtime);
				if(to_modify.anno_inizio>time->tm_year+1900 || to_modify.anno_inizio == 0)
					condizione_do_while = true;
			}while(condizione_do_while);
		}
		if(condizione){
			printf("Renserisci.\n");
			continue;
			}
		do{
			printf("Desideri modificare altri campi?<si><no>\n");
			fflush(stdin);
			fgets(app,3,stdin);
			franco = controllo_risposta(app,'q');
		}while(franco == 'r');
	}while(franco == 's');
	return to_modify;
}

struct utente modifica_dati_struct_utente(struct utente to_modify){
	char scelta[10],var[20],franco;
	bool condizione = true,app = true;
	int valore_ritorno;
	char hold[100];

	do {
		condizione = true;
		printf("Che dati vuole modificare?(nome,cognome,user,password,data)\n");
		fflush(stdin);
		fgets(scelta,80,stdin);
		strtok(scelta,"\n");
		if(strcmp(scelta,"nome") == 0){
			printf("Inserire il nuovo nome:");
			fflush(stdin);
			fgets(hold,80,stdin);
			strcpy(to_modify.nome,strtok(hold,"\n"));
			condizione = false;
		}
		if(strcmp(scelta,"cognome") == 0 && condizione){
			printf("Inserire il nuovo cognome:");
			fflush(stdin);
			fgets(hold,80,stdin);
			strcpy(to_modify.cognome,strtok(hold,"\n"));
			condizione = false;
		}
		if(strcmp(scelta,"user") == 0 && condizione){
			printf("Inserire il nuovo user(sono validi solo user senza spazi): ");
			do{
				fflush(stdin);
				fgets(to_modify.user,80,stdin);
				strtok(to_modify.user,"\n");
				condizione = false;
				valore_ritorno = controllo_nome(to_modify.user,"user.csv");
				if(valore_ritorno == -1)
					printf("Reinseire l'user:");
			}while(valore_ritorno == -1);
		}
		if(strcmp(scelta,"password") == 0 && condizione){
			printf("Inserire la nuova password(almeno 6 caratteri): ");
			do{
				fflush(stdin);
				fgets(to_modify.password,80,stdin);
				strtok(to_modify.password,"\n");
				condizione = false;
				if(strlen(to_modify.password)<6)
					printf("Reinserire la password");
			}while(strlen(to_modify.password)<6);

		}
		if(strcmp(scelta,"data") == 0 && condizione){
			char string_f[10];
			do{
				to_modify.data_nascita.giorno = 1;
				to_modify.data_nascita.mese = 1;
				to_modify.data_nascita.anno = 1999;
				do{
					printf("Inserire il giorno di nascita(1-31):");
					fflush(stdin);
					fgets(string_f,3,stdin);
					to_modify.data_nascita.giorno = atoi(string_f);
					if(!controllo_data_nascita(to_modify.data_nascita)){
						printf("Reinserisci\n");
						condizione = false;
					}
					else
						condizione = true;
				}while(!condizione);

				do{
					printf("Inserire il mese di nascita(1-12):");
					fflush(stdin);
					fgets(string_f,3,stdin);
					to_modify.data_nascita.mese = atoi(string_f);
					if(!controllo_data_nascita(to_modify.data_nascita)){
						printf("Reinserisci\n");
						condizione = false;
					}
					else
						condizione = true;
				}while(!condizione);
				do{
					printf("Inserire l'anno di nascita(1900-2000):");
					fflush(stdin);
					fgets(string_f,5,stdin);
					to_modify.data_nascita.anno = atoi(string_f);
					if(!controllo_data_nascita(to_modify.data_nascita)){
						printf("Reinserisci\n");
						condizione = false;
					}
					else
						condizione = true;
				}while(!condizione);
				condizione = false;
			}while(!controllo_data_nascita(to_modify.data_nascita));
		}
		if(condizione){
			printf("Reinserire il campo da modificare!\n");
			continue;
		}
		do{
			printf("Vuoi modificare altri dati?[si/no]\n");
			fflush(stdin);
			fgets(var,10,stdin);
			franco = controllo_risposta(var,'q');
		}while(franco == 'r');
	}while(franco == 's');
	return to_modify;

}


bool modifica_file_artisti(struct artista modificato,char tipologia){
	FILE *in,*out;
	in = fopen("artisti.csv","r");
	int id,app,dio = 0,k = 0,lol = 0,rosmarino,rosa,n = 0;
	struct artista artisti[MAX];
	bool condizione = true,risultato = false,condizione_id = false;
	char string_f[200],gesu[200];
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){
		n++;
		artisti[i] = string_to_struct_artista(string_f);
		if(artisti[i].id == modificato.id){
			condizione_id = true;
			if(tipologia == 'm'){
				artisti[i] = modificato;
			}
			if(tipologia == 'e'){
				i--;
				n--;
			}
		}
	}
	fclose(in);
	if(condizione_id){
		out = fopen("artisti.csv","w");
		for(int i = 0;i<n;i++){
			if(artisti[i].numero_generi == 1)
				app = fprintf(out,"%d;%s;%d;%s;%s;%s;%d\n",artisti[i].id,artisti[i].nome,artisti[i].numero_generi,artisti[i].genere[0],artisti[i].produttore,artisti[i].nazione,artisti[i].anno_inizio);
			else{
				fprintf(out,"%d;%s;%d;",artisti[i].id,artisti[i].nome,artisti[i].numero_generi);
				for(int j = 0;j<artisti[i].numero_generi;j++){
					fprintf(out,"%s",artisti[i].genere[j]);
					if(j!= artisti[i].numero_generi-1)
						fprintf(out,",");
				}
				app = fprintf(out,";%s;%s;%d\n",artisti[i].produttore,artisti[i].nazione,artisti[i].anno_inizio);
			}
			if(app>0){
				app = 0;
				k++;
			}
		}
		if(n == k)
			risultato = true;
		else
			risultato = false;
		if(condizione_id)
			risultato = true;
		fclose(out);
	}

	return risultato;

}

bool modifica_file_utenti(struct utente modificato,char tipologia,char tipologia2){
	FILE *in;

	in = fopen("user.csv","r");
	int n = 0,k = 0,app = 0;
	char string_f[200];
	bool risultato = false,condizione_id = false;
	struct utente utenti[MAX];
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){
		n++;
		utenti[i] = string_to_struct_utente(string_f);
		if(utenti[i].id == modificato.id){
			condizione_id = true;
			if(tipologia == 'm' && tipologia2 == 'u' && strcmp(utenti[i].tipo,"user") == 0){
				utenti[i] = modificato;
			}
			if(tipologia == 'm' && tipologia2 == 'a' && strcmp(utenti[i].tipo,"admin") == 0){
				utenti[i] = modificato;
			}
			if(tipologia == 'e' && tipologia2 == 'u' && strcmp(utenti[i].tipo,"user") == 0){
				i--;
				n--;
			}
			if(tipologia == 'e' && tipologia2 == 'a' && strcmp(utenti[i].tipo,"admin") == 0){
				i--;
				n--;
			}
		}
	}
	fclose(in);
	FILE *out;
	if(condizione_id){
		out = fopen("user.csv","w");
		for(int i = 0;i<n;i++){
			app = fprintf(out,"%d;%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",utenti[i].id,utenti[i].nome,utenti[i].cognome,utenti[i].user,utenti[i].password,
			utenti[i].tipo,utenti[i].data_nascita.giorno,utenti[i].data_nascita.mese,utenti[i].data_nascita.anno,
			utenti[i].data_iscrizione.giorno,utenti[i].data_iscrizione.mese,utenti[i].data_iscrizione.anno);
			if(app>0){
				app = 0;
				k++;
			}
		}
		if(n == k)
			risultato = true;
		else
			risultato = false;
		if(condizione_id)
			risultato = true;
		fclose(out);
	}

	return risultato;
}

bool ricerca_artisti(char *string,char tipo,int id_utente){
	struct artista array[MAX];
	struct punti{
		struct artista array;
		int punti;
	};
	FILE *in;
	struct punti classifica[MAX],app;
	char string_f[200],string_ricerca[50],risposta[100],franco,mista[20];
	int n = 0,punteggio_finale[MAX],max,min,punteggio_generi,xd = 0;
	int lung_string_ricerca,differenza_lunghezze = 0,m,lung_pattern,punteggio_parziale[MAX];
	int posizione_vettore,id_artista,vettore_posizioni[MAX] = {-1};
	int pt = 0,h = -1,var1,l = 0;
	bool match_positivo = false,condizione_secondo_ciclo = true,condizione_generi = false;
	bool risultato,condizione = true,var = false;
	bool citronella = true;
	in = fopen("artisti.csv","r");
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){
		classifica[i].array = string_to_struct_artista(string_f);
		n++;
	}
	fclose(in);
	for(int i = 0;i<n;i++){
		if(tipo == 'n'){
			strcpy(string_ricerca,classifica[i].array.nome);
			var = true;
		}
		if(tipo == 'g'){
			condizione_generi = true;
			var = true;
		}
		if(tipo == 'p'){
			strcpy(string_ricerca,classifica[i].array.produttore);
			var = true;
		}
		if(tipo == 'h'){
			strcpy(string_ricerca,classifica[i].array.nazione);
			var = true;
		}
		if(tipo == 'a'){
			condizione_secondo_ciclo = false;
			if(classifica[i].array.anno_inizio == atoi(string)){
				if(!var){
					printf("Anno trovato\n");
					printf("ID             NOME      PRODUTTORE         NAZIONE ANNO INIZIO       GENERE/I\n");
				}
				stampa_struct_artista(classifica[i].array);
				vettore_posizioni[xd] = i;
				xd++;
				var = true;
				continue;
			}
		}

		lung_string_ricerca = strlen(string_ricerca);
		lung_pattern = strlen(string);
		differenza_lunghezze = lung_string_ricerca-lung_pattern;

		if(condizione_generi){//blocco per ricerca generi
			for(int h = 0;h<classifica[i].array.numero_generi;h++){
				strcpy(string_ricerca,classifica[i].array.genere[h]);
				punteggio_generi = 0;
				lung_string_ricerca = strlen(string_ricerca);
				lung_pattern = strlen(string);
				differenza_lunghezze = lung_string_ricerca-lung_pattern;

				punteggio_generi = algoritmo_ricerca(string_ricerca,string);
				pt = 0;
				if(punteggio_generi == lung_pattern && lung_pattern == lung_string_ricerca){
					if(condizione_secondo_ciclo){
						printf("Genere trovato \n");
						printf("ID             NOME       PRODUTTORE         NAZIONE ANNO INIZIO       GENERE/I\n");
					}
					h = classifica[i].array.numero_generi;
					posizione_vettore = i;
					vettore_posizioni[xd] = i;
					xd++;
					stampa_struct_artista(classifica[i].array);
					condizione_secondo_ciclo = false;
					continue;
				}
				if(h == 0)
					punteggio_finale[i] = punteggio_generi;
				if(punteggio_generi>punteggio_finale[i]  && h>0)
					punteggio_finale[i] = punteggio_generi;

			}
			classifica[i].punti = punteggio_finale[i];
		}

		else{
			punteggio_finale[i] = algoritmo_ricerca(string_ricerca,string);
			if(punteggio_finale[i] == lung_pattern && lung_pattern == lung_string_ricerca){
				if(condizione_secondo_ciclo){
					printf("Artista trovato\n");
					printf("ID             NOME      PRODUTTORE          NAZIONE ANNO INIZIO       GENERE/I\n");
				}
				stampa_struct_artista(classifica[i].array);
				vettore_posizioni[xd] = i;
				xd++;
				posizione_vettore = i;
				id_artista = classifica[i].array.id;
				condizione_secondo_ciclo = false;
				continue;
			}
			classifica[i].punti = punteggio_finale[i];
		}
		classifica[i].punti = punteggio_finale[i];
	}

	if(condizione_secondo_ciclo){
		for(int i = 0;i<n-1;i++){//ordinamento per punteggio crescente
			min = i;
			for(int j = i+1;j<n;j++){
				if(classifica[j].punti<classifica[min].punti){
					min = j;
				}
			}
			app = classifica[min];
			classifica[min] = classifica[i];
			classifica[i] = app;
		}

		max = classifica[n-1].punti;
		h = 0;
		int j = 0;
		if(max >= 3){
			printf("Forse cercavi:\n");
			printf("ID             NOME      PRODUTTORE         NAZIONE ANNO INIZIO        GENERE/I\n");
			var = true;
			h = 1;

			for(int i = n-1;i >= 0 && condizione_secondo_ciclo;i--){
				if((classifica[i].punti == max || (max-classifica[i].punti) == 1) && classifica[i].punti >= 3){//regole di visualizzazione
					stampa_struct_artista(classifica[i].array);
					vettore_posizioni[xd] = i;
					xd++;
					posizione_vettore = i;
					var1 = true;
					condizione_generi = false;
				}
				j++;
			}
			if(xd == 1)
				condizione_secondo_ciclo = false;
		}
	}
	if(h == 0){
		condizione_secondo_ciclo = false;
		var = false;
	}

	if(!var){
		printf("Artista non trovato\n");
	}

	int i = 0;
	bool condizione_caratteri;
	if((condizione_secondo_ciclo || condizione_generi || tipo == 'p' || tipo == 'h' || tipo == 'a') && var && xd!= 1){
		do{
			var1 = true;
			do{
				condizione_caratteri = false;
				printf("Quale artista stai cercando?<ID>\n");
				fflush(stdin);
				fgets(mista,3,stdin);
			}while(alfanumerico(mista));
			pt = atoi(mista);
			for(i = 0;i<xd && var1;i++){
				if(pt == classifica[vettore_posizioni[i]].array.id){
					var1 = false;
					continue;
				}
			}
		}while(var1);
		if(pt!= -1)
			ascolti_or_preferenze(id_utente,pt,classifica[vettore_posizioni[i-1]].array.nome);

		}
	if((!condizione_secondo_ciclo && var)&& (!condizione_generi || xd == 1) && var1){
		ascolti_or_preferenze(id_utente,classifica[posizione_vettore].array.id,classifica[posizione_vettore].array.nome);
	}

}

bool ascolti_or_preferenze(int id_utente,int id_artista,char *nome_artista){
	bool citronella,risultato,condizione;
	char risposta[20],string[100];
	do{
		citronella = true;
		printf("Vuoi ascoltare o lasciare una preferenza?[ascolto/preferenza]\n");
		fflush(stdin);
		fgets(risposta,100,stdin);
		if(strcmp(strtok(risposta,"\n"),"ascolto") == 0)
			citronella = false;
		else if (strcmp(strtok(risposta,"\n"),"preferenza") == 0 && citronella)
			citronella = false;
	}while(citronella);

	if(strcmp(strtok(risposta,"\n"),"ascolto") == 0){
		risultato = inserimento_ascolti_e_preferenze(id_artista,id_utente,'a');
		if(risultato)
			printf("Hai appena ascoltato:%s\n",nome_artista);
		else
			printf("Hai gia' ascoltato questo artista.\n");
		controllo_funzioni(risultato,'a');
	}
	if(strcmp(strtok(risposta,"\n"),"preferenza") == 0){
		do{
			sprintf(string,"%d;%d;like\n",id_utente,id_artista);
			if(controllo_file_preferenze(string)){
				sprintf(string,"%d;%d;dislike\n",id_utente,id_artista);
				if(controllo_file_preferenze(string))
					risultato = true;
				else{
					inserimento_ascolti_e_preferenze(id_artista,id_utente,'l');
					condizione = false;
					continue;
				}

			}
			else{
				inserimento_ascolti_e_preferenze(id_artista,id_utente,'d');
				condizione = false;
				continue;
			}




			printf("Like o dislike?<like><dislike>\n");
			fflush(stdin);
			fgets(risposta,100,stdin);
			if(strcmp(strtok(risposta,"\n"),"like") == 0){
				risultato = inserimento_ascolti_e_preferenze(id_artista,id_utente,'l');
				condizione = false;
				controllo_funzioni(risultato,'i');
			}
			else if(strcmp(strtok(risposta,"\n"),"dislike") == 0){
				risultato = inserimento_ascolti_e_preferenze(id_artista,id_utente,'d');
				condizione = false;
				controllo_funzioni(risultato,'d');
			}
		}while(condizione);
	}
}

int algoritmo_ricerca(char *text,char *pattern){
	int lung_string_ricerca,lung_pattern,differenza_lunghezze;
	int m,punteggio_parziale,punteggio_finale;
	lung_string_ricerca = strlen(text);
	lung_pattern = strlen(pattern);
	if(lung_string_ricerca >= lung_pattern)
		differenza_lunghezze = lung_string_ricerca-lung_pattern;
	else
		differenza_lunghezze = lung_pattern-lung_string_ricerca;
	for(int j = 0;j <= differenza_lunghezze;j++){
		m = 0;
		punteggio_parziale = 0;
		for(int l = j;m<lung_pattern;l++){
			if(tolower(text[l]) == tolower(pattern[m])){
				punteggio_parziale++;
			}
			m++;
		}
		if(lung_string_ricerca == lung_pattern && punteggio_parziale == lung_pattern){
			punteggio_finale = punteggio_parziale;
			continue;
		}
		if(punteggio_parziale == lung_pattern){
			punteggio_finale = punteggio_parziale;
			continue;
		}
		if(j == 0)
			punteggio_finale = punteggio_parziale;
		if(punteggio_parziale>punteggio_finale  && j>0)
			punteggio_finale = punteggio_parziale;
	}
	return punteggio_finale;
}

int controllo_nome(char *nome,char *txt){
	FILE *in;
	in = fopen(txt,"r");
	struct utente app;
	struct artista app2;
	int risultato = 0;
	char string_f[200];
	while(fgets(string_f,200,in)!= NULL && risultato!= -1){
		if(strcmp(txt,"user.csv") == 0){
			app.id = atoi(strtok(string_f,";"));
			strcpy(app.nome,strtok(NULL,";"));
			strcpy(app.cognome,strtok(NULL,";"));
			strcpy(app.user,strtok(NULL,";"));
			risultato = app.id;
			if(strcmp(app.user,strtok(nome,"\n")) == 0)
				risultato = -1;
		}
		if(strcmp(txt,"artisti.csv") == 0){
			app2.id = atoi(strtok(string_f,";"));
			strcpy(app2.nome,strtok(NULL,";"));
			risultato = app2.id;
			if(strcmp(app2.nome,strtok(nome,"\n")) == 0)
				risultato = -1;
		}
	}
	fclose(in);
	return risultato;
}



bool inserimento_ascolti_e_preferenze(int id_artista,int id_utente,char tipologia){
	FILE *out;
	int app = -1;
	bool risultato,controllo = false,controllo_l = false,controllo_d = false;
	char string_f[200],string_l[200],string_d[200],risposta[20],var;

	if(tipologia == 'a'){
		sprintf(string_f,"%d;%d;ascoltato\n",id_utente,id_artista);
		controllo = controllo_file_preferenze(string_f);
	}
	if(tipologia == 'l' || tipologia == 'd'){
		sprintf(string_l,"%d;%d;like\n",id_utente,id_artista);
		controllo_l = controllo_file_preferenze(string_l);
		if(controllo_l){
			sprintf(string_d,"%d;%d;dislike\n",id_utente,id_artista);
			controllo_d = controllo_file_preferenze(string_d);
			if(controllo_l && controllo_d){
				controllo = true;
				if(tipologia == 'l')
					strcpy(string_f,string_l);
				if(tipologia == 'd')
					strcpy(string_f,string_d);
			}
			else if(tipologia == 'l' && !controllo_d){
				printf("Hai già inserito un dislike per questo artista\n");
				printf("Vuoi inserire una preferenza opposta o eliminare?<scambia><elimina>\n");
				fflush(stdin);
				fgets(risposta,20,stdin);
				if((var = controllo_risposta(risposta,'w')) == 's')
					risultato = modifica_preferenza(id_artista,id_utente,'h');
				if(var == 'e')
					risultato = modifica_preferenza(id_artista,id_utente,'e');
			}
		}
		else if(tipologia == 'd' && !controllo_l){
			do{
				printf("Hai già inserito un like per questo artista\n");
				printf("Vuoi inserire una preferenza opposta o eliminare?<scambia><elimina>\n");
				fflush(stdin);
				fgets(risposta,20,stdin);
			}while(controllo_risposta(risposta,'w') == 'r');
			if(controllo_risposta(risposta,'w') == 's'){
				if(controllo_risposta(risposta,'w') == 'e')
					risultato = modifica_preferenza(id_artista,id_utente,'h');
			}
			else if(controllo_risposta(risposta,'w') == 'e'){
					risultato = modifica_preferenza(id_artista,id_utente,'e');
			}
		}
	}
	out = fopen("preferenze_ascolto.csv","a");
	strcat(string_f,"\n");
	if(controllo)
		app = fprintf(out,string_f);
	if(app>0 || risultato)
		risultato = true;
	else
		risultato = false;
	fclose(out);
	return risultato;
}

bool controllo_file_preferenze(char * string){
	FILE *in;
	in = fopen("preferenze_ascolto.csv","r");
	bool risultato = true;
	char string_f[200];
	while(fgets(string_f,200,in)!= NULL && risultato){
		if(strcmp(strtok(string,"\n"),strtok(string_f,"\n")) == 0)
			risultato = false;
	}
	fclose(in);
	return risultato;
}

bool aggiungi_admin(struct utente admin){
	bool condizione,var1 = false,app2 = true;
	int app,risultato;
	condizione = true;
	FILE *in;
	app = controllo_nome("admin.csv",strtok(admin.user,"\n"));
	app2 = controllo_data_nascita(admin.data_nascita);
	if(app == -1 && !app2)
		condizione = false;
	if(condizione){
		in = fopen("admin.csv","a");
		time_t rawtime;
	 	time (&rawtime);
	    struct tm* time;
	    time  =  localtime(&rawtime);
		risultato = fprintf(in,"%d;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",app+1,strtok(admin.nome,"\n"),strtok(admin.cognome,"\n"),admin.user,strtok(admin.password,"\n"),
		admin.data_nascita.giorno,admin.data_nascita.mese,admin.data_nascita.anno,time->tm_mday,time->tm_mon,time->tm_year+1900);
		if(risultato>0)
			var1 = true;
	}
	return var1;
}

bool ordinamento_artisti(char tipologia,int id_utente){
	FILE *in;
	char app1[20];
	in = fopen("preferenze_ascolto.csv","r");
	struct preferenza var[100];
	struct pd{
		int num_roba;
		struct artista art;
	};
	char string_f[200],var1[15],variabile,var2;
	int n_pr = 0,n_art = 0,risposta = 0;
	struct pd cipolla[100],app;
	bool condizione,controllo;
	if(tipologia == 'a')
		strcpy(var1,"ascoltato");
	if(tipologia == 'p')
		strcpy(var1,"like");
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){
		var[i] = string_to_struct_preferenza(string_f);
		n_pr++;
	}
	fclose(in);
	in = fopen("artisti.csv","r");
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){
		cipolla[i].art = string_to_struct_artista(string_f);
		cipolla[i].num_roba = 0;
		n_art++;
	}
	fclose(in);
	for(int i = 0;i<n_pr;i++){
		condizione = true;
		if(strcmp(strtok(var[i].scelta,"\n"),var1) == 0){
			for(int j = 0;j<n_art && condizione;j++){
				if(cipolla[j].art.id == var[i].id_artista){
					condizione = false;
					cipolla[j].num_roba++;
				}
			}
		}
	}
	for(int i = 0;i<n_art;i++){
		for(int j = 0;j<n_art-1;j++){
			if(cipolla[j].num_roba>cipolla[j+1].num_roba){
				app = cipolla[j];
				cipolla[j] = cipolla[j+1];
				cipolla[j+1] = app;
			}
		}
	}

	if(strcmp(var1,"ascoltato") == 0)
			strcpy(var1,"ascolti");
	for(int i = n_art-1;i>0;i--){
		printf("[%2d]%-20s numero %-10s-->%3d\n",(n_art-i),cipolla[i].art.nome,var1,cipolla[i].num_roba);
	}
	printf("\n");
	do{
			printf("Selezionare un'artista [inserisci una posizione da 1 a 10 (-1 per uscire)]<ID><-1>\n");
			fflush(stdin);
			fgets(app1,3,stdin);
			risposta = atoi(app1);
	}while((risposta<1 || risposta>10) && risposta!= -1);
	if(risposta!= -1)
		controllo = ascolti_or_preferenze(id_utente,cipolla[(n_art-1)-(risposta-1)].art.id,cipolla[(n_art-1)-(risposta-1)].art.nome);


	return true;


}

char controllo_risposta(char risposta[20],char tipologia){
	char condizione = 'r';
	strtok(risposta,"\n");
	to_minuscolo(risposta);
	switch (tipologia){
		case 'a':
			if(strcmp(risposta,"ascoltati") == 0){
			condizione = 'a';
			}
			else if (strcmp(risposta,"piaciuti") == 0){
					condizione = 'p';
			}
		break;
		case 'd':
			if(strcmp(risposta,"like") == 0)
				condizione = 'l';
			if(strcmp(risposta,"dislike") == 0)
				condizione = 'd';
		break;
		case 'o':
			if(strcmp(risposta,"no") == 0)
				condizione = 'n';
			if(strcmp(risposta,"ascolto") == 0)
				condizione = 'a';
			if(strcmp(risposta,"preferenza") == 0)
				condizione = 'p';
		break;
		case 'q':
			if(strcmp(risposta,"si") == 0)
				condizione = 's';
			if(strcmp(risposta,"no") == 0)
				condizione = 'n';
			break;
		case 'w':
			if(strcmp(risposta,"scambia") == 0)
				condizione = 's';
			if(strcmp(risposta,"elimina") == 0)
				condizione = 'e';
		break;
		case 'z':
			if(strcmp(risposta,"registrazione") == 0){
				condizione = 'x';
			}
			else if (strcmp(risposta,"login") == 0){
				condizione = 'y';
			}
		break;

	}
 return condizione;
}

char* to_minuscolo(char *string){
	int i, s = 0;
	s  =  strlen(string);
	strcpy(string,strtok(string,"\n"));
	for(i  = 0;i<s-1;i++){
		string[i] = tolower(string[i]);
	}
	return string;
}

struct preferenza string_to_struct_preferenza(char *string){
	struct preferenza var;
	var.id_utente = atoi(strtok(string,";"));
	var.id_artista = atoi(strtok(NULL,";"));
	strcpy(var.scelta,strtok(NULL,";"));
	strcpy(var.scelta,strtok(var.scelta,"\n"));
	return var;
}

bool preferenze_e_ascolti_utente(int id_utente,char *tipo){
	FILE *in;
	in = fopen("preferenze_ascolto.csv","r");
	struct preferenza array[100],app;
	struct artista array_art[MAX];
	int i = 0,n_art = 0,vettore_posizioni[MAX] = {-1},n_pr = 0,posizione;
	char string_f[200],string[20],franco;
	while(fgets(string_f,50,in)!= NULL){
		app = string_to_struct_preferenza(string_f);
		if(strcmp(app.scelta,tipo) == 0 && id_utente == app.id_utente){
			array[i] = app;
			i++;
		}
	}
	if(i!= 0){
		fclose(in);
		in = fopen("artisti.csv","r");
		for(int j = 0;fgets(string_f,200,in);j++){
			array_art[j] = string_to_struct_artista(string_f);
			n_art++;
		}

		fclose(in);

		if(strcmp(tipo,"ascoltato") == 0)
			printf("Hai ascoltato questi artisti:\n");
		else
			printf("Hai messo %s a questi artisti:\n",tipo);
		int l = 0;
		for(int j = 0;j<i;j++){
			for(int k = 0;k<n_art;k++){
				if(array[j].id_artista == array_art[k].id){
					if(i>1){
						printf("[%d] ",l+1);
					}
					else
						posizione = k;
					printf("%s\n",array_art[k].nome);
					vettore_posizioni[l] = k;
					l++;
				}

			}
		}
		if(strcmp(tipo,"ascoltato")!= 0){
			do{
				printf("Vuoi modificare i tuoi %s?<si><no>\n",tipo);
				fflush(stdin);
				fgets(string,10,stdin);
				franco = controllo_risposta(string,'q');
			}while(franco == 'r');
			if(franco == 's'){
				if(i>1){
					do{
						printf("Inserisci numero della preferenza da modificare:");
						fflush(stdin);
						fgets(string,10,stdin);
						n_pr = atoi(string);
					}while(n_pr<1 && n_pr>l);
					posizione = vettore_posizioni[n_pr-1];
				}
				do{
					printf("Vuoi scambiare o eliminare?<scambia><elimina>\n");
					fflush(stdin);
					fgets(string,15,stdin);
					franco = controllo_risposta(string,'w');
				}while(franco == 'r');
				modifica_preferenza(array_art[posizione].id,id_utente,franco);
			}
		}
	}
	else{
		if(strcmp(tipo,"ascoltato") == 0)
			printf("Non hai ancora ascoltato nessun artista.\n");
		else
			printf("Non hai ancora messo %s a nessun artista.\n",tipo);
	}


	return true;
}

bool elimina_preferenze(int id,char tipologia){
	char string_f[100];
	struct preferenza array[200],app;
	int n = 0,k = 0,var = 0;
	bool risultato = false;
	FILE *in,*out;
	in = fopen("preferenze_ascolto.csv","r");
	for(int i = 0;fgets(string_f,99,in)!= NULL;i++){
		app = string_to_struct_preferenza(string_f);
		if(tipologia == 'a'){
			if(app.id_artista == id){
				i--;
				n--;
			}
			else
				array[i] = app;
		}
		if(tipologia == 'u'){
			if(app.id_utente == id){
				i--;
				n--;
			}
			else
				array[i]  =  app;
		}
		n++;

	}

	fclose(in);
	out = fopen("preferenze_ascolto.csv","w");
	for(int i = 0;i<n;i++){
		var = fprintf(out,"%d;%d;%s\n",array[i].id_utente,array[i].id_artista,array[i].scelta);
		if(var>0){
			var = 0;
			k++;
		}
	}
	if(k == n)
		risultato = true;
	else
		risultato = false;
	fclose(out);
	return risultato;
}


bool modifica_preferenza(int id_artista,int id_utente,char tipologia){
	char condizione = 'r',string_f[100];
	FILE *in,*out;
	in = fopen("preferenze_ascolto.csv","r");
	struct preferenza array[100];
	int n = 0,var = 0,k = 0;
	bool risultato = true,app=true;
	for(int i = 0;fgets(string_f,100,in)!= NULL && app;i++){
		array[i] = string_to_struct_preferenza(string_f);
		n++;
		if(array[i].id_artista == id_artista && array[i].id_utente == id_utente){
			if(strcmp(strtok(array[i].scelta,"\n"),"like") == 0 && tipologia!= 'e'){
				printf("Cambio like con dislike...\n");
				strcpy(array[i].scelta,"dislike");
				app=false;
			}
			else if(strcmp(strtok(array[i].scelta,"\n"),"dislike") == 0 && tipologia!= 'e'){
				printf("Cambio dislike con like...\n");
				strcpy(array[i].scelta,"like");
				app=false;
			}
			else if(tipologia == 'e'){
				i--;
				n--;
				printf("La preferenza e' stata eliminata.\n");
				app=false;
			}

		}
	}
	fclose(in);
	out = fopen("preferenze_ascolto.csv","w");
	for(int i = 0;i<n;i++){
		var = fprintf(out,"%d;%d;%s\n",array[i].id_utente,array[i].id_artista,array[i].scelta);
		if(var>0){
			var = 0;
			k++;
		}
	}
	if(k == n)
		risultato = true;
	else
		risultato = false;
	fclose(out);
	return risultato;
}



bool alfanumerico(char *string){
	strtok(string,"\n");
	bool condizione_alphanum = false;
	for(int i = 0;i<strlen(string) && !condizione_alphanum;i++){
		if(isalpha(string[i])>0 || isspace(string[i])>0){
			condizione_alphanum = true;
		}
	}
	return condizione_alphanum;
}
