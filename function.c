/**
 * @file    function.c
 * @author  Dimiccoli Davide & Fuccilli Francesco
 * @version 1.0
 */

#include "function.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#define MAX 80
#define MAX_GENERI 10
#define MAX_NUM_INPUT 5

struct data{
	int giorno,mese,anno;
};
struct utente {
	int id;
	char nome[MAX];
	char cognome[MAX];
	char user[MAX];
	char password[MAX];
	char tipo[10];
	struct data data_nascita;
	struct data data_iscrizione;
};
struct artista {
	int id;
	char nome[MAX];
	int numero_generi;
	char genere[MAX][MAX_GENERI];
	char produttore[MAX];
	char nazione[MAX];
	int anno_inizio;
};
struct preferenza{
	int id_utente,id_artista;
	char scelta[15];
};


/**
 * La funzione controlla se la data inserita è valida.
 * Viene controllato il giorno, il mese e l'anno, se essi sono validi,
 * se si hanno piu di 18 anni, se si anno più di 100 anni
 * @param struct data b_day Struttura contenente la data
 * @return True se la data è corretta, False se è errata (minorenne o maggiore di 100 anni, etc).
 */
bool controllo_data_nascita(struct data b_day){
	time_t rawtime;
 	time (&rawtime);
    struct tm* time;
    time  =  localtime(&rawtime);				//legge il tempo del sistema
    bool risultato = true;
	if(b_day.giorno <= 0 || b_day.giorno>31)	//programmazione difensiva per l'inserimento del giorno di nascita
		risultato = false;
	if(b_day.mese <= 0 || b_day.mese>12)		//programmazione difensiva per l'inserimento del mese di nascita
		risultato = false;
	if(!(b_day.anno <= (time->tm_year+1900)-18 && b_day.anno>(time->tm_year+1800))) //gli utenti minorenni o ultracentenari non possono iscriversi
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
		if((b_day.anno%4) == 0){				//se l'utente ha inserito in input 29 febbraio controlla se l'anno e' bisestile
			if(b_day.giorno<30)
				risultato = true;
			else
				risultato = false;
		}
		else{
			if(b_day.giorno<29)					//controllo per la data inserita
				risultato = true;
			else
				risultato = false;
		}
	}
	return risultato;
}

/**
 * La funzione chiede in input all'utente i vari campi per registrarsi e controlla se il campo user,
 * password,data di nascita sono corretti.
 * La password deve contenere minimo 6 caratteri
 * L'user deve essere unico
 * La data di nascita deve essere corretta e l'utente deve essere maggiorenne
 * @return Struct utente contenente i dati inseriti correttamente.
 */
struct utente input_registrazione(){
	struct utente app;						//stampa dei vari campi richiesti per la registrazione
	int var = -1;
	char string_f[100],*pt;
	bool condizione = true;
	printf("Inserire il nome:");
	fflush(stdin);
	fgets(string_f,MAX,stdin);
	strcpy(app.nome,strtok(string_f,"\n"));
	printf("Inserire il cognome:");
	fflush(stdin);
	fgets(string_f,MAX,stdin);
	strcpy(app.cognome,strtok(string_f,"\n"));
	printf("Inserire l'user(senza spazi):");
	do{
		fflush(stdin);
		fgets(string_f,MAX,stdin);
		strcpy(app.user,strtok(string_f,"\n"));
		pt = strtok(string_f," ");
		if(strcmp(pt,app.user)!= 0){
			printf("Reinserire l'user'(senza spazi):");
			continue;
		}
		var = controllo_nome(app.user,"user.csv");
		if(var == -1)													// se l'user e' gia' in uso il programma chiede di inserirne uno nuovo
			printf("User gia' in uso\nReinserire l'user'(senza spazi):");
		else{
			app.id = var+1;
		}
	}while(var == -1);

	do{
		printf("Inserire la password(Minimo 6 caratteri):");			// richiede una password che sia lunga almeno 6 caratteri altrimenti ripete
		fflush(stdin);
		fgets(string_f,MAX,stdin);
		strcpy(app.password,strtok(string_f,"\n"));
	}while(strlen(app.password)<6);

	do{
		app.data_nascita.giorno = 1;
		app.data_nascita.mese = 1;
		app.data_nascita.anno = 1999;
		do{
			printf("Inserire il giorno di nascita(1-31):");
			fflush(stdin);
			fgets(string_f,MAX_NUM_INPUT,stdin);
			app.data_nascita.giorno = atoi(string_f);
			if(!controllo_data_nascita(app.data_nascita)){				//programmazione difensiva per evitare errori di battitura
				printf("Reinserisci\n");
				condizione = false;
			}
			else
				condizione = true;
		}while(!condizione);

		do{
			printf("Inserire il mese di nascita(1-12):");
			fflush(stdin);
			fgets(string_f,MAX_NUM_INPUT,stdin);
			app.data_nascita.mese = atoi(string_f);
			if(!controllo_data_nascita(app.data_nascita)){				//programmazione difensiva per evitare errori di battitura
				printf("Reinserisci\n");
				condizione = false;
			}
			else
				condizione = true;
		}while(!condizione);
		do{
			printf("Inserire l'anno di nascita(1900-2000):");
			fflush(stdin);
			fgets(string_f,MAX_NUM_INPUT,stdin);
			app.data_nascita.anno = atoi(string_f);
			if(!controllo_data_nascita(app.data_nascita)){				//e' possibile iscriversi solo se si e' maggiorenni e non si e' ultracentenari
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

/**
 * La funzione inserisce in coda al file i dati dell'utente che vuole registrarsi
 * @param struct utente utente La struttura contenente i dati
 * @return True se la funzione ha inserito correttamente i dati sul file, False se non ha
 * inserito i dati sul file.
 */
bool registrazione(struct utente utente){
	int app = 0,id = 0;
	bool risultato;
	id = controllo_nome(utente.user,"user.csv");
	FILE *out;
	out = fopen("user.csv","a");
	time_t rawtime;
 	time (&rawtime);
    struct tm* time;
    time  =  localtime(&rawtime);
	app = fprintf(out,"%d;%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",utente.id,utente.nome,utente.cognome,utente.user,utente.password,utente.tipo,
	utente.data_nascita.giorno,utente.data_nascita.mese,utente.data_nascita.anno,time->tm_mday,time->tm_mon+1,time->tm_year+1900); //stampa e memorizza sul file user.csv i dati inseriti dall'utente
	fclose(out);
	if(app>0){
		risultato = true;
	}

	else
		risultato = false;
	return risultato;

}

/**
 * La funzione controlla se la password inserita dall'utente appartiene al nome inserito dall'utente.
 * La funzione restituisce la struct utente contenete i dati di quest'ultimo oppure una struct utente
 * con il campo id impostato a "-1" in caso di errore
 * @param char* nome Stringa contenente il nome dell'utente
 * @param char* password Stringa contenente la password dell'utente
 * @return struct utente con i suoi dati oppure struct utente con il campo id impostato a "-1"
 */
struct utente  autenticazione(char *nome,char *password){
	bool condizione_admin = true;
	struct utente var;
	char string_f[200];
	FILE *in;
	in = fopen("user.csv","r");
	rewind(in);
	while(condizione_admin && fgets(string_f,200,in)!= NULL){  //la funzione legge il file e controlla se i campi inseriti dall'utente corrisposndo a quelli presenti nel file per potersi autenticare
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


/**
 * La funzione inserisce in coda al file i dati dell'artista,
 * vengono effettuati i controlli sul nome che deve essere univoco ed
 * anche sulla data di inizio attività
 * @param struct artista artista La struttura contenente i dati dell'artista
 * @return True se la funzione ha inserito correttamente i dati sul file, False se non ha
 * inserito i dati sul file.
 */
bool aggiungi_artista(struct artista artista){
	int id = 0,app = 0;
	bool condizione = true,risultato = false;
	id = controllo_nome(artista.nome,"artisti.csv");
	if(id == -1)
		condizione = false;
	if(condizione){
		FILE *out;
		out = fopen("artisti.csv","a");
		if(artista.numero_generi == 1)
			app = fprintf(out,"%d;%s;%d;%s;%s;%s;%d",id+1,strtok(artista.nome,"\n"),artista.numero_generi,strtok(artista.genere[0],"\n"),
			strtok(artista.produttore,"\n"),strtok(artista.nazione,"\n"),artista.anno_inizio); // stampa e memorizzazione dei vari campi dell'artista su file
		else{
			app = fprintf(out,"%d;%s;%d;",id+1,strtok(artista.nome,"\n"),artista.numero_generi); //ciclo per inserire i vari generi dell'artista se sono piu' di uno
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


/**
 * La funzione mostra a video delle stringhe che indicano se delle funzioni precedentemente
 * chiamate anno avuto esito positivo o negativo
 * @param bool app Valore booleano che indica se un particolare tipo di funzione è stata eseguita correttamente
 * o meno
 * @param char tipologia Tipo di controllo('l'->login 'r'->registrazione 'm'->modifica
 * 'e'->cancellazzione 'a'->ascolto 'i'->like salvato 'd'->dislike salvato
 *
 */
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

/**
 * La funzione mostra a video l'elenco degli artisti o degli admin o degli user.
 * @param char tipologia Tipo di elenco da visualizzare.
 * @param char* txt Nome del file da cui leggere l'elenco.
 */
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
	}while(fgets(string_f,300,in)!= NULL); 			// prende in input dal file i dati necessari fin quando non lo termina
	fclose(in);
}

/**
 * La funzione mostra a video l'artista o l'admin o l'user corrispondenti all'id
 * @param int id Id da visualizzare
 * @param char* txt Nome del file da cui leggere i dati dell'id.
 * @param char tipologia Tipo di id da leggere ('a'->artisti 'u'->user 's'->admin)
 * @param char* string Stringa su cui viene effettuato il return.
 * @return La funzione restituisce una stringa contenente i dati dell'id mostrato a video oppure
 * la stringa "Errore"
 */
char *  visualizza_dati_id(int id, char *txt,char tipologia,char* string){
	FILE *in;
	in = fopen(txt,"r");
	char string_f[200],app[200];
	bool condizione = false;
	struct artista cipolla;
	struct utente origano;
	while(fgets(string_f,200,in)!= NULL && !condizione){				//preleva da file i dati relativi ad ogni utente o artista e si inerrompe quando viene mostrato il profilo cercato
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

/**
 * La funzione divide in token la stringa e inseirsce i vari token negli
 * appositi campi della struct artista
 * @param char* string Stringa in input da dividere in token.
 * @return struct artista Contenente i dati della stringa in input inseriti nei vari campi.
 */
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

/**
 * La funzione divide in token la stringa e inseirsce i vari token negli
 * appositi campi della struct utente
 * @param char* string Stringa in input da dividere in token.
 * @return struct utente Contenente i dati della stringa in input inseriti nei vari campi.
 */
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

/**
 * La funzione manda a video la struct artista.
 * @param struct artista to_print Struttura contenente i dati da visualizzare.
 */
void stampa_struct_artista(struct artista to_print){
	printf("%2d  %15s %15s %15s %11d ",to_print.id,to_print.nome,to_print.produttore,to_print.nazione,to_print.anno_inizio);
	for(int i = 0;i<to_print.numero_generi;i++){
		printf("%15s ",to_print.genere[i]);
	}
	printf("\n");
}

/**
 * La funzione manda a video la struct utente.
 * Attenzione viene stampata anche la password.
 * @param struct utente to_print Struttura contenente i dati da visualizzare.
 */
void stampa_struct_utente(struct utente to_print){
	printf("%2d %15s %15s %15s %15s       %2d/%2d/%4d\n",to_print.id,to_print.nome,to_print.cognome,to_print.user,to_print.password,
	to_print.data_nascita.giorno,to_print.data_nascita.mese,to_print.data_nascita.anno);
}

/**
 * La funzione permette all'admin di modificare i vari campi dell'artista
 * e controlla che il nome sia univoco e la data corretta.
 * @param struct artista to_modify Struttura dati da modificare.
 * @return struct artista Contenente i dati dell'artista modificati.
 */
struct artista modifica_dati_struct(struct artista to_modify){
	char scelta[20],scelta_genere[20],app[20],franco;
	bool condizione = true,condizione_do_while;
	int num_genere;
	do {
		condizione = true;
		printf("Che dati vuole modificare?<nome><genere><produttore><nazione><anno>)\n"); //chiede in input uno dei campi da modificare
		fflush(stdin);
		fgets(scelta,MAX,stdin);
		strtok(scelta,"\n");
		if(strcmp(scelta,"nome") == 0){
			printf("Inserire il nuovo nome:");
			fflush(stdin);
			fgets(to_modify.nome,MAX,stdin);
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
				fgets(scelta_genere,MAX,stdin);
				strtok(scelta_genere,"\n");
			}
			if(strcmp(scelta_genere,"aggiungi") == 0){
				printf("inserire il nuovo genere:");
				fflush(stdin);
				fgets(to_modify.genere[to_modify.numero_generi],MAX,stdin);
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
				fgets(app,MAX_NUM_INPUT,stdin);
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
			fgets(to_modify.produttore,MAX,stdin);
			strtok(to_modify.produttore,"\n");
			condizione = false;
		}
		if(strcmp(scelta,"nazione") == 0 && condizione){
			printf("Inserire la nuova nazione:");
			fflush(stdin);
			fgets(to_modify.nazione,MAX,stdin);
			strtok(to_modify.nazione,"\n");
			condizione = false;
		}
		if(strcmp(scelta,"anno") == 0 && condizione){
			do{
				printf("inserire il nuovo anno:");
				fflush(stdin);
				fgets(app,MAX_NUM_INPUT,stdin);
				to_modify.anno_inizio = atoi(app);
				condizione = false;
				time_t rawtime;
			 	time (&rawtime);
			    struct tm* time;
			    time  =  localtime(&rawtime);
				if(to_modify.anno_inizio>time->tm_year+1900 || to_modify.anno_inizio == 0)
					condizione_do_while = true;
			}while(condizione_do_while);							// programmazione difensva per evitare errori di battitura
		}
		if(condizione){
			printf("Renserisci.\n");
			continue;
			}
		do{
			printf("Desideri modificare altri campi?<si><no>\n");	// se risposta affermativamente continua con la modifica dei vari campi dell'artista
			fflush(stdin);
			fgets(app,MAX_NUM_INPUT,stdin);
			franco = controllo_risposta(app,'q');
		}while(franco == 'r');
	}while(franco == 's' || condizione);
	return to_modify;
}

/**
 * La funzione permette all'admin di modificare i vari campi dell'artista
 * e controlla che il nome sia univoco e la data corretta e la password di almeno 6 caratteri.
 * @param struct utente to_modify Struttura dati da modificare.
 * @return struct utente Contenente i dati dell'artista modificati.
 */
struct utente modifica_dati_struct_utente(struct utente to_modify){
	char scelta[10],var[20],franco;
	bool condizione = true;
	int valore_ritorno;
	char hold[100];

	do {
		condizione = true;
		printf("Che dati vuole modificare?(nome,cognome,user,password,data)\n");
		fflush(stdin);
		fgets(scelta,MAX,stdin);
		strtok(scelta,"\n");
		if(strcmp(scelta,"nome") == 0){
			printf("Inserire il nuovo nome:");
			fflush(stdin);
			fgets(hold,MAX,stdin);
			strcpy(to_modify.nome,strtok(hold,"\n"));
			condizione = false;
		}
		if(strcmp(scelta,"cognome") == 0 && condizione){
			printf("Inserire il nuovo cognome:");
			fflush(stdin);
			fgets(hold,MAX,stdin);
			strcpy(to_modify.cognome,strtok(hold,"\n"));
			condizione = false;
		}
		if(strcmp(scelta,"user") == 0 && condizione){
			printf("Inserire il nuovo user(sono validi solo user senza spazi): ");
			do{
				fflush(stdin);
				fgets(to_modify.user,MAX,stdin);
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
				fgets(to_modify.password,MAX,stdin);
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
					fgets(string_f,MAX_NUM_INPUT,stdin);
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
					fgets(string_f,MAX_NUM_INPUT,stdin);
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
					fgets(string_f,MAX_NUM_INPUT,stdin);
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
			fgets(var,MAX_NUM_INPUT,stdin);
			franco = controllo_risposta(var,'q');
		}while(franco == 'r');
	}while(franco == 's' || condizione);
	return to_modify;

}

/**
 * La funzione modifica il file dell'artista in base alla tipologia inviata
 * ('e'->elimina 'm'->modifica)
 * @param struct artista modificato struttura modificata dall'admin da inserire nel file
 * @param char tipologia Tipo di modifica del file(cancellazzione o sostituzione).
 * @return True se la modifica del file è avvenuta  correttamente oppure False se si è verificato un
 * errore.
 */
bool modifica_file_artisti(struct artista modificato,char tipologia){
	FILE *in,*out;
	in = fopen("artisti.csv","r");
	int app,k = 0,n = 0;
	struct artista artisti[MAX];
	bool risultato = false,condizione_id = false;
	char string_f[200];
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){			//prende in input da file le informazioni relative all'artista inviato dal parametro
		n++;
		artisti[i] = string_to_struct_artista(string_f);
		if(artisti[i].id == modificato.id){
			condizione_id = true;
			if(tipologia == 'm'){
				artisti[i] = modificato;
			}
			if(tipologia == 'e'){								// elimina la riga in cui c'era l'artista inviato dal parametro e copia le informazioni dal file
				i--;
				n--;
			}
		}
	}
	fclose(in);
	if(condizione_id){
		out = fopen("artisti.csv","w");
		for(int i = 0;i<n;i++){									// sovrascrive il file artisti attraverso la struct creata precedentemente
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

/**
 * La funzione modifica il file dell'utente in base alla tipologia inviata
 * ('e'->elimina 'm'->modifica)
 * @param struct artista modificato struttura modificata dall'admin da inserire nel file
 * @param char tipologia Tipo di modifica del file(cancellazzione o sostituzione).
 * @param char tipologia2 Tipo di utente da modificare('u'->user 's'->admin)
 * @return True se la modifica del file è avvenuta correttamente oppure False se si è verificato un
 * errore.
 */
bool modifica_file_utenti(struct utente modificato,char tipologia,char tipologia2){
	FILE *in;
	in = fopen("user.csv","r");
	int n = 0,k = 0,app = 0;
	char string_f[200];
	bool risultato = false,condizione_id = false;
	struct utente utenti[MAX];
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){		//prende in input da file i dati degli utenti e degli admin
		n++;
		utenti[i] = string_to_struct_utente(string_f);
		if(utenti[i].id == modificato.id){
			condizione_id = true;
			if(tipologia == 'm' && tipologia2 == 'u' && strcmp(utenti[i].tipo,"user") == 0){		//modifica utenti
				utenti[i] = modificato;
			}
			if(tipologia == 'm' && tipologia2 == 'a' && strcmp(utenti[i].tipo,"admin") == 0){		//modifica admin
				utenti[i] = modificato;
			}
			if(tipologia == 'e' && tipologia2 == 'u' && strcmp(utenti[i].tipo,"user") == 0){		//elimina user
				i--;
				n--;
			}
			if(tipologia == 'e' && tipologia2 == 'a' && strcmp(utenti[i].tipo,"admin") == 0){		//elimina admin
				i--;
				n--;
			}
		}
	}
	fclose(in);
	FILE *out;
	if(condizione_id){
		out = fopen("user.csv","w");
		for(int i = 0;i<n;i++){			// ciclo per stampare e memorizzare su file le relative modifiche o cancellazioni effettuate
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

/**
 * La funzione in base alla tipologia ricevuta('n'->nome 'g'->genere 'a'->anno 'p'->produttore
 * 'h'->nazione) ricerca degli artisti attraverso un algoritmo e dopo la ricerca è possibile ascoltare o inserire
 * una preferenza per essi.
 * @param char* string stringa su cui viene effettuata la ricerca
 * @param char tipo Tipologia di dato su cui effettuare la ricerca.
 * @param int id_utente Id dell'utente.
 * @return True se la funzione viene eseguita senza errori oppure false.
 */
bool ricerca_artisti(char *string,char tipo,int id_utente){
	struct punti{
		struct artista array;
		int punti;
	};
	FILE *in;
	struct punti classifica[MAX],app;
	char string_f[200],string_ricerca[50],mista[20];
	int n = 0,punteggio_finale[MAX],max,min,punteggio_generi,xd = 0;
	int lung_string_ricerca,lung_pattern,differenza_lunghezze = 0;
	int posizione_vettore,id_artista,vettore_posizioni[MAX] = {-1};
	int pt = 0,h = -1,var1;
	bool condizione_secondo_ciclo = true,condizione_generi = false;
	bool var = false;
	in = fopen("artisti.csv","r");
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){			//prende in input da file i dati di ogni artista
		classifica[i].array = string_to_struct_artista(string_f);
		n++;
	}
	fclose(in);
	for(int i = 0;i<n;i++){										//ciclo che copia in string_ricerca il campo di ricerca passato per parametro
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
		if(tipo == 'a'){										//e' possibile ricercare l'anno solo se e' presente nella struct artista
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

		lung_string_ricerca = strlen(string_ricerca); 			//copia la lunghezza della stringa inserita in input per la ricerca
		lung_pattern = strlen(string);							//copia la lunghezza della stringa su cui viene effettuato il confronto
		differenza_lunghezze = lung_string_ricerca-lung_pattern;//tiene conto della differenza di lunghezza tra la stringa di ricerca e quella da file

		if(condizione_generi){//blocco per ricerca generi
			for(int h = 0;h<classifica[i].array.numero_generi;h++){ //ciclo per la ricerca dei generi
				strcpy(string_ricerca,classifica[i].array.genere[h]);
				punteggio_generi = 0;
				lung_string_ricerca = strlen(string_ricerca);
				lung_pattern = strlen(string);
				differenza_lunghezze = lung_string_ricerca-lung_pattern;

				punteggio_generi = algoritmo_ricerca(string_ricerca,string);// esegue la ricerca e ritorna il risultato
				pt = 0;
				if(punteggio_generi == lung_pattern && lung_pattern == lung_string_ricerca){
					if(condizione_secondo_ciclo){
						printf("Genere trovato \n");
						printf("ID             NOME       PRODUTTORE         NAZIONE ANNO INIZIO       GENERE/I\n"); //stampa il rislutato ottenuto dalla ricerca
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
					printf("ID             NOME      PRODUTTORE          NAZIONE ANNO INIZIO       GENERE/I\n");// stampa l'artista corrispondente al campo di ricerca inserito
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
		for(int i = 0;i<n-1;i++){//ordinamento selection sort
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
		if(max >= 3){				//ricerca approssimativa che stampa gli artisti che hanno ricevuto un punteggio maggiore in confronto alla stringa di ricerca inserita
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
	if((condizione_secondo_ciclo || condizione_generi || tipo == 'p' || tipo == 'h' || tipo == 'a') && var && xd!= 1){//in caso di risultati approssimati chiede l'ID dell'utente da inserire
		do{
			var1 = true;
			do{
				condizione_caratteri = false;
				printf("Quale artista stai cercando?<ID>\n");
				fflush(stdin);
				fgets(mista,MAX_NUM_INPUT,stdin);
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

/**
 * La funzione si occupa di chiedere all'utente se vuole ascoltare o lasciare una preferenza
 * @param int id_utente Id dell'utente
 * @param int id_artista Id dell'artista
 * @param char *nome_artista Nome dell'artista
 * @return True se la funzione viene eseguita senza errori oppure false.
 */
bool ascolti_or_preferenze(int id_utente,int id_artista,char *nome_artista){
	bool citronella,risultato,condizione;
	char risposta[20],string[100];
	do{
		citronella = true;
		printf("Vuoi ascoltare o lasciare una preferenza?[ascolto/preferenza]\n"); //richiesta per immetttere un ascolto o una preferenza
		fflush(stdin);
		fgets(risposta,MAX,stdin);
		if(strcmp(strtok(risposta,"\n"),"ascolto") == 0)
			citronella = false;
		else if (strcmp(strtok(risposta,"\n"),"preferenza") == 0 && citronella)
			citronella = false;
	}while(citronella);

	if(strcmp(strtok(risposta,"\n"),"ascolto") == 0){
		risultato = inserimento_ascolti_e_preferenze(id_artista,id_utente,'a');
		if(risultato)
			printf("Hai appena ascoltato:%s\n",nome_artista);					//stampa l'ascolto effettuato
		else
			printf("Hai gia' ascoltato questo artista.\n");						//messaggio di errore in caso l'artista e' stato gia' ascoltato
		controllo_funzioni(risultato,'a');
	}
	if(strcmp(strtok(risposta,"\n"),"preferenza") == 0){						//controlla se vi sono presenti preferenze all'artista inserito e rimanda alla funzione inserimento_ascolti_preferenze
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
			printf("Like o dislike?<like><dislike>\n");							//se non vi sono preferenze chiede di inserirne una
			fflush(stdin);
			fgets(risposta,MAX,stdin);
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

/**
 * La funzione calcola un punteggio in base alla stringa di ricerca inserita e quella presente da file
 * @param char *text Testo su cui effettuare la ricerca
 * @param char *pattern Testo con cui si effettua la ricerca
 * @return Un punteggio relativo ai risultati di ricerca
 */
int algoritmo_ricerca(char *text,char *pattern){			//ricerca approssimativa
	int lung_string_ricerca,lung_pattern,differenza_lunghezze;
	int m,punteggio_parziale,punteggio_finale;
	lung_string_ricerca = strlen(text);						//text e' la variabile che deve essere confrontata con il pattern
	lung_pattern = strlen(pattern);							//il pattern e' la stringa inserita dall'utente
	if(lung_string_ricerca >= lung_pattern)					//se text ha lunghezza minore del pattern la differenza e' data da pattern-text
		differenza_lunghezze = lung_string_ricerca-lung_pattern;
	else
		differenza_lunghezze = lung_pattern-lung_string_ricerca; //altrimeti text-pattern
	for(int j = 0;j <= differenza_lunghezze;j++){				//ciclo che si ripete per il numero della lunghezza della differenza delle stringhe
		m = 0;
		punteggio_parziale = 0;
		for(int l = j;m<lung_pattern;l++){
			if(tolower(text[l]) == tolower(pattern[m])){		//programmazione difensiva che converte le stringhe in stamaptello in minuscolo
				punteggio_parziale++;
			}
			m++;
		}
		if(lung_string_ricerca == lung_pattern && punteggio_parziale == lung_pattern){
			punteggio_finale = punteggio_parziale;				//assegnazione del punteggio finale nel caso in cui la stringa inserita e' equivalente a quella del file
			continue;
		}
		if(punteggio_parziale == lung_pattern){					//assegnazione del punteggio finale nel caso in cui la stringa inserica e' equivalente a una parte della stringa da file
			punteggio_finale = punteggio_parziale;
			continue;
		}
		if(j == 0)												//al primo ciclo il primo punteggio parziale trovato viene assegnato in quello finale
			punteggio_finale = punteggio_parziale;
		if(punteggio_parziale>punteggio_finale  && j>0)			//in quelli successivi scambia il punteggio finale se ne viene trovato uno parziale maggiore
			punteggio_finale = punteggio_parziale;
	}
	return punteggio_finale;
}

/**
 * La funzione controlla se c'è gia un determinato nome per gli artisti
 *  o un determinato user per gli utenti.
 * @param char* nome Nome da controllare.
 * @param *txt Nome del file su cui effetture il controllo.
 * @return l'id dell'ultimo artista o utente controllato oppure -1 in caso di nome già presente.
 */
int controllo_nome(char *nome,char *txt){
	FILE *in;
	in = fopen(txt,"r"); //prende in input il file da aprire
	struct utente app;
	struct artista app2;
	int risultato = 0;
	char string_f[200];
	while(fgets(string_f,200,in)!= NULL && risultato!= -1){	//legge da file le informazioni relative alla nome inserito
		if(strcmp(txt,"user.csv") == 0){
			app.id = atoi(strtok(string_f,";"));
			strcpy(app.nome,strtok(NULL,";"));
			strcpy(app.cognome,strtok(NULL,";"));
			strcpy(app.user,strtok(NULL,";"));
			risultato = app.id;
			if(strcmp(app.user,strtok(nome,"\n")) == 0)		//ritorna -1 se gia' presente
				risultato = -1;
		}
		if(strcmp(txt,"artisti.csv") == 0){
			app2.id = atoi(strtok(string_f,";"));
			strcpy(app2.nome,strtok(NULL,";"));
			risultato = app2.id;
			if(strcmp(app2.nome,strtok(nome,"\n")) == 0)	//ritorna -1 se gia' presente
				risultato = -1;
		}
	}
	fclose(in);
	return risultato;
}


/**
 * La funzione inserisce in coda al file "preferenze_ascolto.csv"  l'ascolto o la preferenza espressa
 * dall'utente, se essa è già presente chiede se essa deve essere scambiata o eliminata.
 * Oppure essa scambia o elimina una determinata preferenza attraverso il campo tipologia('a'->ascolto
 * 'l'->like 'd'->dislike)
 * @param int id_artista Id dell'artista.
 * @param int id_utente Id dell'utente.
 * @param char tipologia tipologia .
 * @return True se la funzione viene eseguita senza errori oppure false.
 */
bool inserimento_ascolti_e_preferenze(int id_artista,int id_utente,char tipologia){
	FILE *out;
	int app = -1; //variabile di appoggio utilizzata per il controllo
	bool risultato,controllo = false,controllo_l = false,controllo_d = false;
	char string_f[200],string_l[200],string_d[200],risposta[20],var;

	if(tipologia == 'a'){
		sprintf(string_f,"%d;%d;ascoltato\n",id_utente,id_artista);
		controllo = controllo_file_preferenze(string_f);			//la funzione controllo_file_preferenze controlla se vi e' gia' stato un ascolto di questo artista su file
	}
	if(tipologia == 'l' || tipologia == 'd'){
		sprintf(string_l,"%d;%d;like\n",id_utente,id_artista);		//la funzione controllo_file_preferenze controlla se vi e' gia' stata inserita una preferenza a questo artista su file
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
				printf("Hai già inserito un dislike per questo artista\n"); //se vi e' gia' inserito un like una stampa chiede se si vuole scambiare la preferenze o eliminarla
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
				printf("Hai già inserito un like per questo artista\n");	//se vi e' gia' inserito un dislike una stampa chiede se si vuole scambiare la preferenze o eliminarla
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
	if(app>0 || risultato)			//controlla se l'operazione e' andata a buon fine
		risultato = true;
	else
		risultato = false;
	fclose(out);
	return risultato;
}

/**
 * La funzione controlla sul file "preferenze_ascolto.csv" se è presente una determinato ascolto,
 * like o dislike
 * @param char * string Stringa contenente l'id dell'utente,l'id dell'artista,"ascolto"/"like"/"preferenza"
 * "id_utente;id_artista;like/dislike/ascolto)
 * @return True se non ci sono stringhe uguali nel file altrimenti false.
 */
bool controllo_file_preferenze(char * string){
	FILE *in;
	in = fopen("preferenze_ascolto.csv","r");
	bool risultato = true;
	char string_f[200];
	while(fgets(string_f,200,in)!= NULL && risultato){		//legge dal file "preferenze_ascolto.csv" se vi e' gia' un ascolto o una preferenza inserita
		if(strcmp(strtok(string,"\n"),strtok(string_f,"\n")) == 0)
			risultato = false;
	}
	fclose(in);
	return risultato;
}

/**
 * La funzione inserisce in coda al file i dati dell'admin
 * @param struct utente admin La struttura contenente i dati
 * @return True se la funzione ha inserito correttamente i dati sul file, False se non ha
 * inserito i dati sul file.
 */
bool aggiungi_admin(struct utente admin){
	bool condizione,var1 = false,app2 = true;
	int app,risultato;		//variabili di appoggio
	condizione = true;
	FILE *in;
	app = controllo_nome("admin.csv",strtok(admin.user,"\n"));  //rimanda alla funzione che controlla se l'user dell'admin immesso e' gia' presente
	app2 = controllo_data_nascita(admin.data_nascita);			//rimanda alla funzione che esegue controlli sulla data di nascita
	if(app == -1 && !app2)
		condizione = false;
	if(condizione){
		in = fopen("admin.csv","a");
		time_t rawtime;
	 	time (&rawtime);
	    struct tm* time;
	    time  =  localtime(&rawtime);
		risultato = fprintf(in,"%d;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",app+1,strtok(admin.nome,"\n"),strtok(admin.cognome,"\n"),admin.user,strtok(admin.password,"\n"),
		admin.data_nascita.giorno,admin.data_nascita.mese,admin.data_nascita.anno,time->tm_mday,time->tm_mon,time->tm_year+1900);		//stampa su file tutti i dati della struct admin
		if(risultato>0)
			var1 = true;		//torna vero se la scrittura e' avvenuta
	}
	return var1;
}

/**
 * La funzione ordina gli artisti in un determinato modo ('a'->ascolti 'p'->like),
 * creando una top 10,
 * dopo l'ordinamento è possibile ascoltare o lasciare una preferenza per un determinato artista.
 * @param char tipologia tipologia di ordinamento
 * @param int id_utente ID dell'utente.
 * @return True se la funzione viene eseguita senza errori oppure false.
 */
bool ordinamento_artisti(char tipologia,int id_utente){
	FILE *in;
	char app1[20];
	in = fopen("preferenze_ascolto.csv","r");
	struct preferenza var[100];
	struct pd{					//contiene la struct artisti e un intero se vi e' un ascolto o un like
		int num_roba;
		struct artista art;
	};
	char string_f[200],var1[15],var2;
	int n_pr = 0,n_art = 0,risposta = 0;
	struct pd cipolla[100],app;	//dichiarazione di array di struct			
	bool condizione,controllo;
	if(tipologia == 'a')		//in base alla tipologia mandata per parametro esegue l'ordimaneto necessario
		strcpy(var1,"ascoltato"); //per ascolti	
	if(tipologia == 'p')
		strcpy(var1,"like");	//o per like
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){	//prende in input dal file preferenze_ascolto.csv i dati 
		var[i] = string_to_struct_preferenza(string_f);
		n_pr++;
	}
	fclose(in);
	in = fopen("artisti.csv","r");
	for(int i = 0;fgets(string_f,200,in)!= NULL;i++){	//prende in input dal file artisti.csv i dati
		cipolla[i].art = string_to_struct_artista(string_f);
		cipolla[i].num_roba = 0;
		n_art++;
	}
	fclose(in);
	for(int i = 0;i<n_pr;i++){
		condizione = true;
		if(strcmp(strtok(var[i].scelta,"\n"),var1) == 0){
			for(int j = 0;j<n_art && condizione;j++){
				if(cipolla[j].art.id == var[i].id_artista){//assegna punteggio ad ogni artista in base agli ascolti o i like
					condizione = false;
					cipolla[j].num_roba++;
				}
			}
		}
	}
	for(int i = 0;i<n_art;i++){
		for(int j = 0;j<n_art-1;j++){
			if(cipolla[j].num_roba>cipolla[j+1].num_roba){// ordinamento bubble sort
				app = cipolla[j];
				cipolla[j] = cipolla[j+1];
				cipolla[j+1] = app;
			}
		}
	}

	if(strcmp(var1,"ascoltato") == 0)
			strcpy(var1,"ascolti");
	for(int i = n_art-1;i>0;i--){
		printf("[%2d]%-20s numero %-10s-->%3d\n",(n_art-i),cipolla[i].art.nome,var1,cipolla[i].num_roba); //stampa della classifica ordinata
	}
	printf("\n");
	do{
			printf("Selezionare un'artista per ascoltare o mettere una preferenza [inserisci una posizione da 1 a 10 (-1 per uscire)]<ID><-1>\n");
			fflush(stdin);
			fgets(app1,MAX_NUM_INPUT,stdin);
			risposta = atoi(app1);
	}while((risposta<1 || risposta>10) && risposta!= -1);
	if(risposta!= -1)
		controllo = ascolti_or_preferenze(id_utente,cipolla[(n_art-1)-(risposta-1)].art.id,cipolla[(n_art-1)-(risposta-1)].art.nome);//rimanda ad ascolti_or_preferenze


	return true;


}

/**
 * La funzione riceve in input una stringa e una tipologia in base alla tipologia ritorna un
 * determinato carattere.
 * @param char risposta[20] variabile contenente una stringa inserita dall'utente.
 * @param char tipologia tipo di controllo da effettuare.
 * @return Uno specifico carattere.
 */
char controllo_risposta(char risposta[20],char tipologia){
	char condizione = 'r';		//in caso di errore viene restituito r
	strtok(risposta,"\n");
	to_minuscolo(risposta);
	switch (tipologia){ //switch che esegue varie strcmp in base alla tipologia ricevuta 
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

/**
 * La funzione riceve in input un puntatore ad una stringa e la rende minuscola
 * @param char* string Stringa da convertire in minuscolo
 * @return La stringa convertita in minuscolo e presente sulla variabile utilizzata come primo parametro.
 */
char* to_minuscolo(char *string){
	int i, s = 0;
	s  =  strlen(string);
	strcpy(string,strtok(string,"\n"));
	for(i  = 0;i<s-1;i++){				//ciclo for che itera da 0 fino alla lunghezza della stringa in input
		string[i] = tolower(string[i]);
	}
	return string;
}

/**
 * La funzione divide in token la stringa e inseirsce i vari token negli
 * appositi campi della struct preferenza
 * @param char* string Stringa in input da dividere in token.
 * @return struct preferenza Contenente i dati della stringa in input inseriti nei vari campi.
 */
struct preferenza string_to_struct_preferenza(char *string){
	struct preferenza var;
	var.id_utente = atoi(strtok(string,";"));
	var.id_artista = atoi(strtok(NULL,";"));
	strcpy(var.scelta,strtok(NULL,";"));
	strcpy(var.scelta,strtok(var.scelta,"\n"));
	return var;					//ritorna la struct 
}

/**
 * La funzione mostra a video le preferenze e gli ascolti dell'utente e permette all'utente di
 * modificare o eliminare gli ascolti o le preferenze
 * @param int id_utente Id dell'utente che ha richiamato la funzione
 * @param char *tipo Tipologia di preferenza o ascolto da mostrare
 * @return True se la funzione viene eseguita senza errori oppure false.
 */
bool preferenze_e_ascolti_utente(int id_utente,char *tipo){
	FILE *in;
	in = fopen("preferenze_ascolto.csv","r");
	struct preferenza array[100],app;		//array di struct
	struct artista array_art[MAX];
	int i = 0,n_art = 0,vettore_posizioni[MAX] = {-1},n_pr = 0,posizione;
	char string_f[200],string[20],franco;
	while(fgets(string_f,50,in)!= NULL){	//prende in input i dati dal file preferenze_ascolto.csv
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
			printf("Hai messo %s a questi artisti:\n",tipo);//%s stampa like o dislike
		int l = 0;
		for(int j = 0;j<i;j++){
			for(int k = 0;k<n_art;k++){
				if(array[j].id_artista == array_art[k].id){
					if(i>1){
						printf("[%d] ",l+1);				//stampa numero degli artisti con cui si ha avuto una interazione
					}
					else
						posizione = k;
					printf("%s\n",array_art[k].nome);		//stampa il nome degli artisti
					vettore_posizioni[l] = k;
					l++;
				}

			}
		}
		if(strcmp(tipo,"ascoltato")!= 0){
			do{
				printf("Vuoi modificare i tuoi %s?<si><no>\n",tipo);	//stampa per poter ascambiare o eliminare le propire preferenze
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
			printf("Non hai ancora ascoltato nessun artista.\n");	//stampa se non ha ascoltato nessuno
		else
			printf("Non hai ancora messo %s a nessun artista.\n",tipo);	//stampa se non si e' messo like o dislike a nessun artista
	}


	return true;
}

/**
 * La funzione elimina le preferenza di un'artista o un'utente quando uno di essi viene eliminato
 * @param int id Id dell'utente o dell'artista
 * @param char tipologia Tipo di id a cui la funzione fa riferimento('a'->artisti 'u'->utenti)
 * @return True se la funzione viene eseguita senza errori oppure false.
 */
bool elimina_preferenze(int id,char tipologia){
	char string_f[100];
	struct preferenza array[200],app;		//array di struct
	int n = 0,k = 0,var = 0;
	bool risultato = false;
	FILE *in,*out;
	in = fopen("preferenze_ascolto.csv","r");
	for(int i = 0;fgets(string_f,MAX,in)!= NULL;i++){	//prende in input dal file preferenze_ascolto
		app = string_to_struct_preferenza(string_f);
		if(tipologia == 'a'){
			if(app.id_artista == id){					// elimina la riga in cui vi e' la corrispondenza tra l'artista da eliminare e l'artista da file
				i--;
				n--;
			}
			else
				array[i] = app;
		}
		if(tipologia == 'u'){							// elimina la riga in cui vi e' la corrispondenza tra l'utente da eliminare e l'utente da file
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
		var = fprintf(out,"%d;%d;%s\n",array[i].id_utente,array[i].id_artista,array[i].scelta); //nuova stampa su file dei dati aggiornati
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

/**
 * La funzione permette di modificare o eliminare una determinata preferenza
 * @param int id_artista ID dell'artista
 * @param int id_utente Id dell'utente
 * @param char tipologia Tipologia ('e'->elimina 'm'->'modifica)
 * @return True se la funzione viene eseguita senza errori oppure false.
 */
bool modifica_preferenza(int id_artista,int id_utente,char tipologia){
	char string_f[100];
	FILE *in,*out;
	in = fopen("preferenze_ascolto.csv","r");
	struct preferenza array[100];
	int n = 0,var = 0,k = 0;
	bool risultato = true,app=true;
	for(int i = 0;fgets(string_f,100,in)!= NULL && app;i++){	//prende in input i dati dal file preferenze_ascolto
		array[i] = string_to_struct_preferenza(string_f);
		n++;
		if(array[i].id_artista == id_artista && array[i].id_utente == id_utente){		//vari controlli per eseguire lo scambio di preferenza
			if(strcmp(strtok(array[i].scelta,"\n"),"like") == 0 && tipologia!= 'e'){
				printf("Cambio like con dislike...\n");
				strcpy(array[i].scelta,"dislike");
				app=false;
			}
			else if(strcmp(strtok(array[i].scelta,"\n"),"dislike") == 0 && tipologia!= 'e'){	//vari controlli per eseguire lo scambio di preferenza
				printf("Cambio dislike con like...\n");
				strcpy(array[i].scelta,"like");
				app=false;
			}
			else if(tipologia == 'e'){					//elimina la preferenza
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
		var = fprintf(out,"%d;%d;%s\n",array[i].id_utente,array[i].id_artista,array[i].scelta);		//stampa su file i dati aggiornati
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


/**
 * La funzione controlla che nella stringa non siano presenti caratteri alfabetici o spazi
 * @param char* string Stringa da controllare
 * @return True se la stringa contien un carattere alfabetico o uno spazio oppure False se è composta
 * da soli numeri.
 */
bool alfanumerico(char *string){
	strtok(string,"\n");
	bool condizione_alphanum = false;
	for(int i = 0;i<strlen(string) && !condizione_alphanum;i++){	//ciclo che itera da 0 fino alla lunghezza della stringa in input
		if(isalpha(string[i])>0 || isspace(string[i])>0){			//controlla che la stringa contiene caratteri alfabetici o spazi
			condizione_alphanum = true;
		}
	}
	return condizione_alphanum;				//ritorna vero se vi sono caratteri alfabetici o spazi
}
