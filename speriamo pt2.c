/*
 ============================================================================
 Name        : speriamo.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


/**
 * @file    main.c
 * @author  Dimiccoli Davide & Fuccilli Francesco
 * @version 1.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "function.h"
/**
 * @brief Costante per definire la lunghezza massima delle stringhe in input
 */
#define MAX 80
/**
 * @brief Costante per definire il numero massimo di generi
 */
#define MAX_GENERI 10
/**
 * @brief Costante per definire il numero di caratteri da leggere in caso di un input intero compreso tra
 * -9999 e 9999 oppure per stringhe aventi massimo 4 caratteri
 */
#define MAX_NUM_INPUT 5

/**
 * @brief Struttura dati utilizzata per contenere una determinata data
 */
struct data{
	int giorno,mese,anno;
};
/**
 * @brief Struttura dati utilizzata per contenere i dati dell'utente e dell'admin
 * utente e admin sono differenziati l'uno dall'altro attraverso il parametro tipo[10]
 */
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
/**
 * @brief Struttura dati utilizzata per contenere i dati dell'artista
 * il campo genere puo' contenere piu' stringhe
 */
struct artista {
	int id;
	char nome[MAX];
	int numero_generi;
	char genere[MAX][MAX_GENERI];
	char produttore[MAX];
	char nazione[MAX];
	int anno_inizio;
};
/**
 * @brief Struttura dati utilizzata per contenere i dati della preferenza
 */
struct preferenza{
	int id_utente,id_artista;
	char scelta[15];
};


/**
 * Il main contiene il menu' relativo all'admin e all'utente e le relative chiamate di funzione.
 */
int main(){

	char nome[80],password[80],*txt_utente="user.csv",*txt_artisti="artisti.csv";
	struct utente utente_registrato,var;
	struct artista artista;
	int numero;
	int varr=0;
	bool condizione=true,app;
	char risposta_primaria[100],var12;
	printf("---------------------SPOTIFY---------------------\n");
	do{
	printf("Registrazione o login? <registrazione>/<login>\n");
		fflush(stdin);
		fgets(risposta_primaria,100,stdin);
		to_minuscolo(risposta_primaria);
		var12=controllo_risposta(risposta_primaria,'z');
	}while(var12=='r');
	system("cls");
	do{
		if(var12=='y'){
			printf("---------------------LOGIN---------------------\n");
			printf("Inserisci user:");
			fflush(stdin);
			fgets(nome,MAX,stdin);
			printf("Inserisci password:");
			fflush(stdin);
			fgets(password,MAX,stdin);
			strtok(password,"\n");
			strtok(nome,"\n");
			var=autenticazione(nome,password);
			if(var.id!=-1){
				controllo_funzioni(true,'l');
				printf("Benvenuto %s\n",var.nome);
				condizione=false;
				system("pause");
			}
		}
		if(var12=='x'){
			printf("---------------------REGISTRAZIONE---------------------\n");
			utente_registrato=input_registrazione();
			app=registrazione(utente_registrato);
			if(app){
				var=utente_registrato;
				condizione=false;
			}
			controllo_funzioni(app,'r');

		}
	}while(condizione);
	system("cls");
	int scelta_1,scelta_2;
	char scelta_3[20],mista[20];
	bool condizione_sw=true,condizione_while;
	char string[20],franco;
	struct artista artista_da_modificare,artista_modificato;
	struct utente admin_to_add;
	char continua[80],string_da_modificare[20];
	if(strcmp(var.tipo,"admin")==0){
		do{
			printf("---------------------MENU'---------------------\n");
			printf("[1] Per aggiungere, modificare o eliminare degli artisti \n");
			printf("[2] Per aggiungere, modificare o eliminare degli utenti \n");
			printf("[3] Per aggiungere, modificare o eliminare admin\n");
			printf("[4] TERMINA.\n");
			fflush(stdin);
			fgets(mista,MAX_NUM_INPUT,stdin);
			scelta_1=atoi(mista);
			//system("cls");
			if(scelta_1==1)
				strcpy(string,"ARTISTA");
			if(scelta_1==2)
				strcpy(string,"UTENTE");
			if(scelta_1==3)
				strcpy(string,"ADMIN");
			if(scelta_1==4){
				condizione_sw=false;
				continue;
			}
			if(scelta_1<=0 || scelta_1>4){
				printf("Scelta non valida. Riprovare.\n");
				continue;
			}
			printf("\n");
			printf("---------------------MENU' %s---------------------\n",string);
			printf("[1] Per aggiungere un %s\n",string);
			printf("[2] Per modificare un %s\n",string);
			printf("[3] Per eliminare un %s\n",string);
			printf("[4] Per tornare indietro \n");
			fflush(stdin);
			fgets(mista,MAX_NUM_INPUT,stdin);
			scelta_2=atoi(mista);
			//system("cls");
			switch(scelta_2){
				case 1:
					if(scelta_1==1){
						printf("---------------------AGGIUNTA %s---------------------\n",string);
						do{
							fflush(stdin);
							printf("Inserire il nome:");
							fgets(artista.nome,MAX,stdin);
							do{
								printf("Inserire numero di generi:");
								fflush(stdin);
								fgets(mista,MAX_NUM_INPUT,stdin);
								artista.numero_generi=atoi(mista);
							}while(alfanumerico(mista) || artista.numero_generi<=0 || artista.numero_generi>MAX_GENERI);
							for(int i=0;i<artista.numero_generi;i++){
								fflush(stdin);
								printf("Inserire il genere n.%d:",i+1);
								fgets(artista.genere[i],MAX,stdin);
							}
							fflush(stdin);
							printf("Inserire il produttore:");
							fgets(artista.produttore,MAX,stdin);
							fflush(stdin);
							printf("Inserire la nazionalita':");
							fgets(artista.nazione,MAX,stdin);
							fflush(stdin);
							do{
								printf("Inserire la data di inizio attivita':");
								fflush(stdin);
								fgets(mista,5,stdin);
								artista.anno_inizio=atoi(mista);
							}while(artista.anno_inizio==0);
							app =aggiungi_artista(artista);
							controllo_funzioni(app,'r');
							do{
								printf("Desideri aggiungere altri artisti?<si><no>\n");
								fflush(stdin);
								fgets(scelta_3,MAX_NUM_INPUT,stdin);
								franco=controllo_risposta(scelta_3,'q');
							}while(franco=='r');
						}while(franco=='s');
					}
					else if(scelta_1==2){
						printf("---------------------AGGIUNTA %s---------------------\n",string);
						do{
							utente_registrato=input_registrazione();
							varr=registrazione(utente_registrato);
							controllo_funzioni(varr,'r');
							do{
								printf("Desideri aggiungere altri utenti?<si><no>\n");
								fflush(stdin);
								fgets(scelta_3,MAX_NUM_INPUT,stdin);
								franco=controllo_risposta(scelta_3,'q');
							}while(franco=='r');
						}while(franco=='s');
					}
					else if(scelta_1==3){
						//aggiunta ADMIN
						printf("---------------------AGGIUNTA %s---------------------\n",string);
						do{
							admin_to_add=input_registrazione();
							strcpy(admin_to_add.tipo,"admin");
							app=registrazione(admin_to_add);
							controllo_funzioni(app,'r');
							do{
								printf("Desideri aggiungere altri admin?<si><no>\n");
								fflush(stdin);
								fgets(scelta_3,MAX_NUM_INPUT,stdin);
								franco=controllo_risposta(scelta_3,'q');
							}while(franco=='r');
						}while(franco=='s');
					}
					system("cls");
					break;
				case 2:
					strcpy(continua,"1");
					if(scelta_1==1){
						printf("---------------------MODIFICA ARTISTI--------------------- \n");
						do{
							printf("Desideri visualizzare l'elenco degli artisti iscritti?<si><no>\n");
							fflush(stdin);
							fgets(scelta_3,MAX_NUM_INPUT,stdin);
							if(controllo_risposta(scelta_3,'q')=='s'){
								visualizza_elenco('a',txt_artisti);
							}
							do{
								condizione_while=false;
								do{
									printf("Inserisci l'ID dell'artista da modificare<ID>\n");
									fflush(stdin);
									fgets(mista,MAX_NUM_INPUT,stdin);
									numero=atoi(mista);
								}while(alfanumerico(mista) || numero<0 );
								visualizza_dati_id(numero,txt_artisti,'a',string_da_modificare);
								if(strcmp(string_da_modificare,"Errore")==0){
									printf("Reniserisci.\n");
									condizione_while=true;
									continue;
								}
							}while(condizione_while);
							artista_da_modificare=string_to_struct_artista(string_da_modificare);
							artista_modificato=modifica_dati_struct(artista_da_modificare);
							app=modifica_file_artisti(artista_modificato,'m');
							controllo_funzioni(app,'m');
							do{
								printf("Desideri continuare a modificare altre informazioni?<si><no>\n");
								fflush(stdin);
								fgets(continua,MAX_NUM_INPUT,stdin);
								franco=controllo_risposta(continua,'q');
							}while(franco=='r');

						}while(franco=='s');
					}

					else if(scelta_1==2) {
						struct utente utente_da_modificare,utente_modificato;
						char string_da_modificare[200];
						printf("---------------------MODIFICA UTENTI---------------------\n");
						do{
							condizione=false;
							do{
								printf("Desideri visualizzare l'elenco degli utenti iscritti?<si><no>\n");
								fflush(stdin);
								fgets(continua,MAX_NUM_INPUT,stdin);
								franco=controllo_risposta(continua,'q');
							}while(franco=='r');
							if(franco=='s')
								visualizza_elenco('u',txt_utente);
							do{
								condizione_while=false;
								do{
									printf("Inserisci l'ID dell'utente da modificare\n");
									fflush(stdin);
									fgets(mista,MAX_NUM_INPUT,stdin);
									numero=atoi(mista);
								}while(alfanumerico(mista) || numero<0);
								visualizza_dati_id(numero,txt_utente,'u',string_da_modificare);
								if(strcmp(string_da_modificare,"Errore")==0){
									printf("Reinserisci.\n");
									condizione_while=true;
									continue;
								}
							}while(condizione_while);
							utente_da_modificare=string_to_struct_utente(string_da_modificare);
							utente_modificato=modifica_dati_struct_utente(utente_da_modificare);
							app=modifica_file_utenti(utente_modificato,'m','u');
							controllo_funzioni(app,'m');
							do{
								printf("Desideri continuare a modificare altre informazioni?<si><no>\n");
								fflush(stdin);
								fgets(continua,MAX_NUM_INPUT,stdin);
								franco=controllo_risposta(continua,'q');
							}while(franco=='r');
						}while(franco=='s' || condizione);
					}
					else if(scelta_1==3){
						do{
							char string_da_modificare[200];
							struct utente admin_da_modificare,admin_modificato;
							printf("---------------------MODIFICA ADMIN--------------------- \n");
							do{
								printf("Desideri visualizzare l'elenco degli admin iscritti?<si><no>\n");
								fflush(stdin);
								fgets(scelta_3,MAX_NUM_INPUT,stdin);
							}while(controllo_risposta(scelta_3,'q')=='r');
							if(controllo_risposta(scelta_3,'q')=='s'){
								visualizza_elenco('s',txt_utente);
							}

							do{
								do{
									condizione_while=false;
									do{
										printf("Inserire l'ID dell'admin da modificare:\n");
										fflush(stdin);
										fgets(mista,MAX_NUM_INPUT,stdin);
										fflush(stdin);
										numero=atoi(mista);
									}while(alfanumerico(mista) || numero<0);
									visualizza_dati_id(numero,txt_utente,'s',string_da_modificare);
									if(strcmp(string_da_modificare,"Errore")==0){
										printf("Ritenta.\n");
										condizione_while=true;
										continue;
									}
								}while(condizione_while);
								admin_da_modificare=string_to_struct_utente(string_da_modificare);
								admin_modificato=modifica_dati_struct_utente(admin_da_modificare);
								app=modifica_file_utenti(admin_modificato,'m','a');

							}while(!app);
							controllo_funzioni(app,'m');
							do{
							printf("Desideri continuare a modificare altre informazioni?<si><no>\n");
								fflush(stdin);
								fgets(continua,MAX_NUM_INPUT,stdin);
							}while(controllo_risposta(continua,'q')=='r');
						}while(controllo_risposta(continua,'q')=='s');
					}
					system("cls");
					break;
				case 3:
					printf("---------------------ELIMINA %s---------------------\n",string);
					char scelta_elenco[3],scelta_to_continue[3];

					int id_to_delete;
					if(scelta_1==1){
						//elimina ARTISTI
						struct artista appoggio;
						do{
							printf("Desideri visualizzare l'elenco degli artisti?<si><no> \n");
							fflush(stdin);
							fgets(scelta_elenco,MAX_NUM_INPUT,stdin);
						}while(controllo_risposta(scelta_elenco,'q')=='r');
						if(controllo_risposta(scelta_elenco,'q')=='s'){
							visualizza_elenco('a',txt_artisti);
						}
						do{
							do{
								condizione_while=false;
								do{
									printf("Inserire l'ID dell'artista da eliminare:\n");
									fflush(stdin);
									fgets(mista,MAX_NUM_INPUT,stdin);
									id_to_delete=atoi(mista);
									appoggio.id=id_to_delete;
								}while(alfanumerico(mista) || numero<0);
								visualizza_dati_id(id_to_delete,txt_artisti,'a',string_da_modificare);
								if(strcmp(string_da_modificare,"Errore")==0){
									printf("Ritenta.\n");
									condizione_while=true;
									continue;
								}
							}while(condizione_while);
							app=modifica_file_artisti(appoggio,'e');
							if(app)
								app=elimina_preferenze(id_to_delete,'a');
						}while(!app);
						controllo_funzioni(app,'e');
						do{
							do{
								printf("Desideri eliminare altri artisti?<si><no>\n");
								fflush(stdin);
								fgets(scelta_to_continue,MAX_NUM_INPUT,stdin);
							}while(controllo_risposta(scelta_to_continue,'q')=='r');
						}while(controllo_risposta(scelta_to_continue,'q')=='s');
					}

					else if(scelta_1==2){
						struct utente appoggio;
						do{
							do{
								printf("Desideri visualizzare l'elenco degli utenti?<si><no>\n");
								fflush(stdin);
								fgets(scelta_to_continue,MAX_NUM_INPUT,stdin);
							}while(controllo_risposta(scelta_to_continue,'q')=='r');
							if(controllo_risposta(scelta_to_continue,'q')=='s'){
								visualizza_elenco('u',txt_utente);
							}
							do{
								do{
									condizione_while=false;
									do{
										printf("Inserire l'ID dell'user da eliminare:\n");
										fflush(stdin);
										fgets(mista,MAX_NUM_INPUT,stdin);
										id_to_delete=atoi(mista);
										appoggio.id=id_to_delete;
									}while(alfanumerico(mista) || numero<0);
									visualizza_dati_id(id_to_delete,txt_utente,'u',string_da_modificare);
									if(strcmp(string_da_modificare,"Errore")==0){
										printf("Ritenta.\n");
										condizione_while=true;
										continue;
									}
								}while(condizione_while);
								app=modifica_file_utenti(appoggio,'e','u');
								if(app)
									app=elimina_preferenze(id_to_delete,'u');
								controllo_funzioni(app,'e');
							}while(!app);
							do{
								printf("Desideri eliminare altri utenti?<si><no>\n");
								fflush(stdin);
								fgets(scelta_to_continue,MAX_NUM_INPUT,stdin);
							}while(controllo_risposta(scelta_to_continue,'q')=='r');
						}while(controllo_risposta(scelta_to_continue,'q')=='s');
					}
					else if(scelta_1==3){
						struct utente appoggio;
						do{
							do{
								printf("Desideri visualizzare l'elenco degli admin?<si><no>\n");
								fflush(stdin);
								fgets(scelta_to_continue,MAX_NUM_INPUT,stdin);
							}while(controllo_risposta(scelta_to_continue,'q')=='r');
							if(controllo_risposta(scelta_to_continue,'q')=='s'){
								visualizza_elenco('s',txt_utente);
							}
							do{
								do{
									condizione_while=false;
									do{
										printf("Inserire l'ID dell'admin da eliminare:\n");
										fflush(stdin);
										fgets(mista,MAX_NUM_INPUT,stdin);
										id_to_delete=atoi(mista);
										appoggio.id=id_to_delete;
									}while(alfanumerico(mista) || numero<0);
									if(id_to_delete==var.id){
										printf("Non puoi eliminare te stesso!\n");
										condizione_while=true;
										continue;
									}
									else{
										visualizza_dati_id(id_to_delete,txt_utente,'s',string_da_modificare);
									}
									app=modifica_file_utenti(appoggio,'e','a');
									controllo_funzioni(app,'e');
									if(strcmp(string_da_modificare,"Errore")==0){
										printf("Ritenta.\n");
										condizione_while=true;
										continue;
									}
								}while(condizione_while);

							}while(!app);

							do{
								printf("Desideri eliminare altri admin?<si><no>\n");
								fflush(stdin);
								fgets(scelta_to_continue,MAX_NUM_INPUT,stdin);
							}while(controllo_risposta(scelta_to_continue,'q')=='r');
						}while(controllo_risposta(scelta_to_continue,'q')=='s');
					}
					system("cls");
					break;
				case 4:
					break;

				default:
					printf("Riprova.\n");
					break;
			}
		}while(condizione_sw);
	}
	if(strcmp(var.tipo,"user")==0){
		char string_id[200],var5;
		int scelta;
		struct utente utente_modificato;
		bool condizione_do=false,condizione_profilo=false;
		do{
			printf("---------------------MENU'---------------------\n");
			printf("[1] Ricerca artista per ascolto o preferenza \n");
			printf("[2] TOP 10 \n");
			printf("[3] Profilo utente \n");
			printf("[4] Logout\n");
			printf("risposta: ");
			fflush(stdin);
			fgets(mista,MAX_NUM_INPUT,stdin);
			scelta=atoi(mista);
			system("cls");
		switch(scelta){
			case 1://ricerca approssimata
				printf("---------------------RICERCA---------------------\n");
				bool condizione,app,condizione_caratteri;
				char risposta[20];
				do{
					condizione=true;
					do{
						fflush(stdin);
						printf("Inserisci il campo di ricerca<nome><genere><produttore><nazione><anno>\n");

						fgets(risposta,MAX,stdin);
						to_minuscolo(risposta);
						if(strcmp(strtok(risposta,"\n"),"nome")==0){
							condizione=false;
							printf("Inserisci nome artista\n");
							fflush(stdin);
							fgets(risposta,MAX,stdin);
							strtok(risposta,"\n");
							app=ricerca_artisti(risposta,'n',var.id);
						}
						if(strcmp(strtok(risposta,"\n"),"genere")==0){
							printf("Inserisci un genere musicale\n");
							condizione=false;
							fflush(stdin);
							fgets(risposta,MAX,stdin);
							strtok(risposta,"\n");
							app=ricerca_artisti(risposta,'g',var.id);
						}
						if(strcmp(strtok(risposta,"\n"),"produttore")==0){
							printf("Inserisci un produttore\n");
							condizione=false;
							fflush(stdin);
							fgets(risposta,MAX,stdin);
							strtok(risposta,"\n");
							app=ricerca_artisti(risposta,'p',var.id);
						}
						if(strcmp(strtok(risposta,"\n"),"nazione")==0){
							printf("Inserisci una nazione\n");
							condizione=false;
							fflush(stdin);
							fgets(risposta,MAX,stdin);
							strtok(risposta,"\n");
							app=ricerca_artisti(risposta,'h',var.id);
						}
						if(strcmp(strtok(risposta,"\n"),"anno")==0){
							do{
								condizione_caratteri=false;
								printf("Inserisci anno di inizio attivita'\n");
								condizione=false;
								fflush(stdin);
								fgets(risposta,MAX,stdin);
								strtok(risposta,"\n");
								for(int i=0;i<strlen(risposta);i++){
									if(isalpha(risposta[i])>0 || isspace(risposta[i])>0)
										condizione_caratteri=true;
								}

							}while(condizione_caratteri);
							app=ricerca_artisti(risposta,'a',var.id);
						}
					}while(condizione);
					do{
						printf("Desideri effettuare un'altra ricerca?<si><no>\n");
						fflush(stdin);
						fgets(scelta_3,MAX_NUM_INPUT,stdin);
						franco=controllo_risposta(scelta_3,'q');
					}while(franco=='r');
				}while(franco=='s');
				system("cls");
				break;
			case 2://ordinamento
				printf("---------------------TOP 10---------------------\n");
				do{
					printf("Vuoi visualizzare la top 10 ascoltati o piaciuti?<ascoltati><piaciuti>\n");
					fflush(stdin);
					fgets(risposta,MAX,stdin);
				}while((var5=controllo_risposta(risposta,'a'))=='r');
				ordinamento_artisti(var5,var.id);
				system("cls");
				break;
			case 3://visualizzazione profilo
				do{
					printf("---------------------PROFILO---------------------\n");
					printf("[1] Visualizza il tuo profilo \n");
					printf("[2] Visualizza preferenze e ascolti\n");
					printf("[3] Elimina profilo\n");//implementare la ricerca.
					printf("[4] Torna indietro\n");
					printf("risposta: ");
					fflush(stdin);
					fgets(mista,MAX_NUM_INPUT,stdin);
					scelta=atoi(mista);
					system("cls");
					condizione_profilo=false;
					switch(scelta){
						case 1:
							printf("---------------------IL TUO PROFILO---------------------\n");
							visualizza_dati_id(var.id,txt_utente,'u',string_id);

							printf("Vuoi modificare i tuoi dati?[si/no]\n");
							do{
								fflush(stdin);
								fgets(scelta_3,MAX_NUM_INPUT,stdin);
								franco=controllo_risposta(scelta_3,'q');
							}while(franco=='r');
							if(franco=='s'){
								utente_modificato=modifica_dati_struct_utente(var);
								app=modifica_file_utenti(utente_modificato,'m','u');
								controllo_funzioni(app,'m');
							}
							system("cls");
						break;
						case 2:
							printf("---------------------LE TUE PREFERENZE---------------------\n");
							preferenze_e_ascolti_utente(var.id,"ascoltato");
							preferenze_e_ascolti_utente(var.id,"like");
							preferenze_e_ascolti_utente(var.id,"dislike");
							system("pause");
							system("cls");
						break;
						case 3:
							printf("---------------------ELINIMAZIONE---------------------\n");
							do{
								printf("Sei sicuro di voler eliminare il tuo profilo?<si><no>\n");
								fflush(stdin);
								fgets(risposta,MAX_NUM_INPUT,stdin);
								franco=controllo_risposta(risposta,'q');
							}while(franco=='r');
							if(franco=='s'){
								app=modifica_file_utenti(var,'e','u');
								if(app)
									app=elimina_preferenze(var.id,'u');
								controllo_funzioni(app,'e');
								condizione_profilo=condizione_do=true;
								system("pause");
								continue;
							}
							system("cls");
						break;
						case 4:
							condizione_profilo=true;
						break;
						default:
							printf("Riprova\n");
						break;

					}
				}while(!condizione_profilo);
				system("cls");
				break;
			case 4:
				condizione_do=true;
				break;
			default:
				printf("Riprova!\n");
			break;
			}

		}while(!condizione_do);




		}


		return 0;

	}

