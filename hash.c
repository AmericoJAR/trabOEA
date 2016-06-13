/******************************************************************
04/06/2016                      hash                     04/06/2016
-------------------------------------------------------------------
Arquivo...: hash.c
Autor.....: Jos� Am�rico Rodrigues
Finalidade: Opera��es no arquivo da tabela hash
Atualiza��es:
13/06/2016 - Atualizadas algumas rotinas mas ainda com problemas
             na indexa��o (cria��o da tabela hash de dispers�o).
           - Inclu�da precau��o contra CEPs duplicados.
           - Completada a rotina de pesquisa.
           - Criado uma arquivo de log para tentar desvendar o
             problema na cria��o da tabela de dispers�o.
******************************************************************/
#include <stdlib.h>
#include <math.h>
#include "hash.h"
#include "cep.h"
#include "util.h"
<<<<<<< HEAD
=======

>>>>>>> origin/master

/******************************************************************
Fun��o....: criaHash
Finalidade: Cria o arquivo zerado da tabela hash
******************************************************************/
int criaHash() {
	HashTab ht;     					// Estrutura para o registro da tabela
    int i;								// Vari�vel auxiliar
    long marco = trunc(MAXHASH / 50);	// Auxiliar para o marco da barra de progresso

    arqhash = fopen(HASHFILE, "w");							// Cria o arquivo
    arqhash = freopen(HASHFILE, "r+", arqhash);  			// Reabre-o para escrita
	printf("Criando o arquivo inicial de �ndices...   ");	// Exibe mensagem de cria��o
	printf("\n\n0%% ");										// Inicia a barra de progresso
    ht = inicializaHash(0, -1, -1);							// Inicializa os dados dos registros
    // Loop para inclus�o das linhas da tabela
    for (i = 0; i <= MAXHASH; i++) {
        escreveHash(ht, 0, SEEK_END);                		// Adiciona o registro no final do arquivo
        if (i % marco == 0) printf("%c", 187);     	 		// Exibe o andamento do processo
    }
    printf(" 100%%\n\n");   								// Finaliza a barra de progresso
    fechaHash();											// Fecha o arquivo de hash
	return 0;
}

/******************************************************************
Fun��o....: indexaHash
Finalidade: Indexa o arquivo da tabela hash atrav�s do arquivo de CEPs
******************************************************************/
int indexaHash() {
<<<<<<< HEAD
	Endereco e;                 // Estrutura para guardar um registro
=======
	Endereco e;     // Estrutura para guardar um registro
>>>>>>> origin/master
    HashTab ht, htaux, htant;   // Auxiliares para adicionar registros na tabela
    long h = 0;					// Posi��o na tabela hash
    long registro = -1;			// Posi��o atual do registro de CEPs
    long posicaofinal = 0;		// Final do arquivo de �ndices (hash)
<<<<<<< HEAD
=======
//    long posicaoarqanterior;    // Posi��o anterior no arquivo (hash)
//    long posicaoanterior;       // Posi�ao anterior no arquivo
>>>>>>> origin/master
    long marco;					// Auxiliar para o marco da barra de progresso

	marco = trunc(ultregCep()/50);		// Calcula o marco para desenho da barra
    arqhash = fopen(HASHFILE, "r+");	// Abre o �ndice hash zerado
<<<<<<< HEAD
    arqlog = fopen(LOGFILE, "w");	    // Abre o arquivo de log
    abreCep();							// Abre o arquivo de CEPs
	printf("Indexando o arquivo de CEPs (hash)...     ");
	printf("\n\n0%% ");
    registro++;
    e = leCep(registro);   //L� o registro do arquivo de CEps
    fprintf(LOGFILE, "IN�CIO DO LOG\n\nLido do arquivo de CEPs - Posi��o: %ld - CEP: %s", registro, e.cep);
    // Loop para circular pelos registros de CEPs
	while(strlen(e.cep) > 0) {
        h = calculaHash(atol(e.cep));  // Calcula a posi��o para a indexa��o
        fprintf(LOGFILE, "\nPosi��o calculada no hash: %ld - CEP: %s % 900001", h, e.cep);
        // Vai at� a linha calculada da tabela e guarda as informa��es contidas
        ht = leHash(h);
        fprintf(LOGFILE, "\n(LEITURA) Posi��o: %ld - CEP: %ld - ", h, ht.CEP);
        fprintf(LOGFILE, "PosArq: %ld - ", ht.PosArq);
        fprintf(LOGFILE, "Prox: %ld", ht.Proximo);
=======
    abreCep();							// Abre o arquivo de CEPs
	printf("Indexando o arquivo de CEPs (hash)...     ");
	printf("\n\n0%% ");
    // Loop para circular pelos registros de CEPs
	//while (strlen(e.cep) > 0) {
    registro++;
    e = leCep(registro);   //L� o registro do arquivo de CEps
printf("\n\nLido do arquivo de CEPs - Posi��o: %ld - CEP: %s", registro, e.cep);
	while(strlen(e.cep) > 0) {
        h = calculaHash(atol(e.cep));  // Calcula a posi��o para a indexa��o
printf("\nPosi��o calculada no hash: %ld - CEP: %ld % 900001", h, atol(e.cep));
        // Vai at� a linha calculada da tabela e guarda as informa��es contidas
        ht = leHash(h);
printf("\n(LEITURA) Posi��o: %ld - CEP: %ld - ", h, ht.CEP);
printf("PosArq: %ld - ", ht.PosArq);
printf("Prox: %ld", ht.Proximo);
>>>>>>> origin/master
        // Guarda as informa��es na vari�vel auxiliar
        htaux = inicializaHash(atol(e.cep), registro, -1);    // Novo CEP
        // Se n�o houver um CEP na linha...
        if ((ht.CEP == 0) || (ht.PosArq == -1)) {
            escreveHash(htaux, h, SEEK_SET);    // Guarda o CEP no arquivo hash
<<<<<<< HEAD
            fprintf(LOGFILE, "\n\nSEM COLIS�O\n(GRAVA��O) Posi��o: %ld - CEP: %ld - ", h, htaux.CEP);
            fprintf(LOGFILE, "PosArq: %ld - ", htaux.PosArq);
            fprintf(LOGFILE, "Prox: %ld", htaux.Proximo);
       }
=======
        }
>>>>>>> origin/master
        // H� colis�o...
        else {
            // Se n�o for um CEP repetido...
            if (ht.CEP != atol(e.cep)) {
	            // 1� colis�o
	            if (ht.Proximo == -1) {
                	escreveHash(htaux, 0, SEEK_END);    // Adiciona o CEP no final do arquivo
<<<<<<< HEAD
                    // Guarda a posi��o da nova linha para sobrescrever o campo
                	// Proximo da linha onde houve a colis�o
                	posicaofinal = ultregHash() - 1;
                	fprintf(LOGFILE, "\n\n1 COLIS�O\n(ADI��O) Posi��o: %ld - CEP: %ld - ", posicaofinal, htaux.CEP);
                    fprintf(LOGFILE, "PosArq: %ld - ", htaux.PosArq);
                    fprintf(LOGFILE, "Prox: %ld", htaux.Proximo);
                	// Guarda a nova informa��o do arquivo de CEPs
                	htaux=inicializaHash(ht.CEP, ht.PosArq, posicaofinal);
                	escreveHash(htaux, h, SEEK_SET);
                    fprintf(LOGFILE, "\n(GRAVA��O) Posi��o anterior: %ld - CEP: %ld - ", h, htaux.CEP);
                    fprintf(LOGFILE, "PosArq: %ld - ", htaux.PosArq);
                    fprintf(LOGFILE, "Prox: %ld", htaux.Proximo);
	            }
	            // H� v�rias colis�es
	            else {
                    fprintf(LOGFILE, "\n\nV�RIAS COLIS�ES");
                    // Loop para circular por todas as colis�es encontradas
	                while (ht.Proximo != -1) {
						htant = leHash(ht.Proximo);
                        fprintf(LOGFILE, "\n(LEITURA-LOOP) Posi��o: %ld - CEP: %ld - ", ht.Proximo, htant.CEP);
                        fprintf(LOGFILE, "PosArq: %ld - ", htant.PosArq);
                        fprintf(LOGFILE, "Prox: %ld", htant.Proximo);
	                }
	                escreveHash(htaux, 0, SEEK_END);    // Adiciona o CEP no final do arquivo
	                // Guarda a posi��o da nova linha para sobrescrever o campo
	                // Proximo da linha onde houve a colis�o
	                posicaofinal = ultregHash() - 1;
                    fprintf(LOGFILE, "\n(ADI��O) Posi��o: %ld - CEP: %ld - ", posicaofinal, htaux.CEP);
                    fprintf(LOGFILE, "PosArq: %ld - ", htaux.PosArq);
                    fprintf(LOGFILE, "Prox: %ld", htaux.Proximo);
	                // Grava a nova informa��o do arquivo de CEPs
	                htaux = inicializaHash(atol(e.cep), htant.Proximo, posicaofinal);
	                escreveHash(htaux, htant.Proximo, SEEK_SET);
                    fprintf(LOGFILE, "\n(GRAVA��O) Posi��o anterior: %ld - CEP: %ld - ", htant.Proximo, htaux.CEP);
                    fprintf(LOGFILE, "PosArq: %ld - ", htaux.PosArq);
                    fprintf(LOGFILE, "Prox: %ld", htaux.Proximo);
                    pausa();
	            }
            }
        }
        //if ((registro % 50 ==0) && (registro > 0)) pausa();
        if (registro % marco == 0) printf("%c", 187);	// Exibe o andamento do processo
        registro++;
        e = leCep(registro);   //L� os registros do arquivo de CEps
        fprintf(LOGFILE, "\n\nPR�XIMO\n\nLido do arquivo de CEPs - Posi��o: %ld - CEP: %s", registro, e.cep);
=======
                	// Guarda a posi��o da nova linha para sobrescrever o campo
                	// Proximo da linha onde houve a colis�o
                	posicaofinal = ultregHash() - 1;
                	// Guarda a nova informa��o do arquivo de CEPs
                	htaux=inicializaHash(ht.CEP, ht.PosArq, posicaofinal);
                	escreveHash(htaux, h, SEEK_SET);
	            }
	            // H� v�rias colis�es
	            else {
//                htant = ht;
                //posicaoarqanterior = ht.PosArq;
//                posicaoanterior = ht.Proximo;
                // Loop para circular por todas as colis�es encontradas
printf("***V�rias colis�es***");
	                while (ht.Proximo != -1) {
						htant = leHash(ht.Proximo);
printf("\n(LEITURA-LOOP) Posi��o: %ld - CEP: %ld - ", ht.Proximo, htant.CEP);
printf("PosArq: %ld - ", htant.PosArq);
printf("Prox: %ld", htant.Proximo);
						if (htant.Proximo != -1) {
                        //posicaoarqanterior = ht.PosArq;
//                        posicaoanterior = ht.Proximo;
//                        htant = ht;
	                    }
	                }
	                escreveHash(htaux, 0, SEEK_END);    // Adiciona o CEP no final do arquivo
	                // Guarda-se a posi��o da nova linha para sobrescrever o campo
	                // Proximo da linha onde houve a colis�o
	                posicaofinal = ultregHash() - 1;
printf("\n(ADI��O) Posi��o: %ld - CEP: %ld - ", posicaofinal, htaux.CEP);
printf("PosArq: %ld - ", htaux.PosArq);
printf("Prox: %ld", htaux.Proximo);
	                // Grava a nova informa��o do arquivo de CEPs
	                htaux = inicializaHash(strtol(e.cep, NULL, 10), htant.Proximo, posicaofinal);
	                escreveHash(htaux, htant.Proximo, SEEK_SET);
printf("\n(GRAVA��O) Posi��o anterior: %ld - CEP: %ld - ", htant.Proximo, htaux.CEP);
printf("PosArq: %ld - ", htaux.PosArq);
printf("Prox: %ld", htaux.Proximo);
pausa();
	            }
            }
        }
//if ((registro % 50 ==0) && (registro > 0)) pausa();
        if (registro % marco == 0) printf("%c", 187);	// Exibe o andamento do processo
        registro++;
        e = leCep(registro);   //L� os registros do arquivo de CEps
printf("\n\nLido do arquivo de CEPs - Posi��o: %ld - CEP: %s", registro, e.cep);
>>>>>>> origin/master
    }
    printf(" 100%%\n\n");
    fechaCep();							// Abre o arquivo de CEPs
	return 0;
}

/******************************************************************
Fun��o....: pesquisaHash
Finalidade: Consultar um elemento atrav�s da tabela de hash
******************************************************************/
int pesquisaHash() {
	Endereco e;     // Estrutura para guardar um registro
<<<<<<< HEAD
    HashTab ht;     // Auxiliares para adicionar registros na tabela
	char cep[9];    // Guarda o nome a ser pesquisado
	long h;         // Guarda o n�mero do registro
	int flag = 0;   // Se encontrado = 1 sen�o = 0
=======
    HashTab ht;   // Auxiliares para adicionar registros na tabela
	char cep[9];  // Guarda o nome a ser pesquisado
	long h;  // Guarda o n�mero do registro
>>>>>>> origin/master

    // Leitura via teclado do CEP a ser pesuisado
    printf("CEP a ser pesquisado: "); scanf("%s", cep);
 	printf("Procurando o CEP [%s]\n", cep);
    // Calcula a posi��o para pesquisar
    abreCep();							// Abre o arquivo de CEPs
    h = atol(cep) % MAXHASH;
    // Vai at� a linha calculada da tabela e guarda as informa��es contidas
    ht = leHash(h);
    if (atol(cep) == ht.CEP) {
        // CEP encontrado de primeira... Pegando informa��es do arquivo de CEPs
        flag = 1;
    }
    // CEP houve colis�o ou n�o foi encontrado
    else {
        while (ht.Proximo != -1) {
            ht = leHash(ht.Proximo);
        }
        // CEP encontrado... Pegando informa��es do arquivo de CEPs
        if (atol(cep) == ht.CEP) {
            flag = 1;
        }
    }
    if (flag == 1) {
        e = leCep(ht.PosArq);
        printf("CEP %s encontrado!", cep);
        imprimeCep(ht.PosArq, e);
    }
    else {
        printf("CEP n�o encontrado!");
    }
	pausa();
    fechaCep();							// Abre o arquivo de CEPs
	return 0;
}

/******************************************************************
Fun��o....: estatisticasHash
Finalidade: Estat�sticas gerais do arquivo de Hash
******************************************************************/
int estatisticasHash() {
	Endereco e;     // Estrutura para guardar um registro
	int *colisoes;
	long h;
    long registro = -1;
    long tamarqCep;   // Guarda o tamanho do arquivo
    long marco; 	// Auxiliar para o marco da barra de progresso
	long resultado[MAXCOLISOES + 2];
	long i;
	long somacolisoes = 0;
	long totalregCep;

    colisoes = malloc (MAXHASH * sizeof (int));
    if (colisoes == NULL) {
        printf ("Erro! Nao foi poss�vel alocar mem�ria para o vetor.\n");
        exit (EXIT_FAILURE);
    }
	marco = trunc(MAXHASH / 30);
    limpaTela();
 	printf("Zerando vetor...        0%% ");
    for (i = 0; i <= MAXHASH; i++) {
        if (i < MAXCOLISOES + 2) resultado[i] = 0;
        colisoes[i] = 0;
        if (i % marco == 0) printf("%c", 187);	// Exibe o andamento do processo
    }
    printf(" 100%%\n");
	marco = trunc(ultregCep()/30);		// Calcula o marco para desenho da barra
    arqhash = fopen(HASHFILE, "r+");	// Abre o �ndice hash zerado
    abreCep();							// Abre o arquivo de CEPs
  	printf("Lendo �ndices...        0%% ");
    registro++;
    e = leCep(registro);
	while(strlen(e.cep) > 0) {
        h = calculaHash(atol(e.cep));
        colisoes[h]++;
        if (registro % marco == 0) printf("%c", 187);	// Exibe o andamento do processo
        registro++;
        e = leCep(registro);
    }
    tamarqCep = ftell(arqcep);
<<<<<<< HEAD
    totalregCep = tamarqCep / sizeof(Endereco);
    fechaCep();							// Fecha o arquivo de CEPs
    printf(" 100%%\n");
=======
    printf(" 100%%\n");
    fechaCep();							// Abre o arquivo de CEPs
>>>>>>> origin/master
 	marco = trunc(MAXHASH / 30);
  	printf("Gerando estatisticas... 0%% ");
    for (i = 0; i <= MAXHASH; i++) {
        resultado[colisoes[i]]++;
        if (i % marco == 0) printf("%c", 187);	// Exibe o andamento do processo
    }
    printf(" 100%%\n\n");
    limpaTela();
<<<<<<< HEAD
 	// Exibe informa��es estat�sticas
=======
>>>>>>> origin/master
    for (i = 0; i < MAXCOLISOES + 2; i++){
        if (i == 0) {
            printf("registros n�o ocupados: %d de %ld\n", resultado[0], MAXHASH);
        } else if (i == 1) {
            printf("Nenhuma colis�o.......: %d\n", resultado[1]);
        } else if (i == 2) {
            printf(" 1 colis�o............: %d\n", resultado[i]);
        } else if (i > 2 && i < 11){
            printf(" %ld colis�es...........: %d\n", (i - 1), resultado[i]);
        } else {
            printf("%ld colis�es...........: %d\n", (i - 1), resultado[i]);
        }
        if (i > 1) somacolisoes = somacolisoes + resultado[i];
<<<<<<< HEAD
    }
    printf("Somat�rio de colis�es: %ld\n", somacolisoes);
    printf("Ocupa��o: %ld\n", resultado[1]);
    printf("Hashs: %ld\n", MAXHASH);
    printf("totalregCep: %ld\n", totalregCep);
    printf("Taxa de ocupa��o: %.2f%%\n", (resultado[1] / MAXHASH));
    printf("Taxa de colis�es: %.2f%%\n", (somacolisoes / totalregCep));
=======
   }

 	// Exibe informa��es estat�sticas
    totalregCep = tamarqCep / sizeof(Endereco);

   printf("Somat�rio de colis�es: %ld\n", somacolisoes);
   printf("Ocupa��o: %ld\n", resultado[1]);
   printf("Hashs: %ld\n", MAXHASH);
   printf("totalregCep: %ld\n", totalregCep);

    printf("Taxa de ocupa��o: %2.2f%%\n", (resultado[1] / MAXHASH));
    printf("Taxa de colis�es: %2.2f%%\n", (somacolisoes / totalregCep));
>>>>>>> origin/master
 	// Exibe informa��es do arquivo de CEPs
	printf("Total de CEPs no arquivo: %ld\n", totalregCep);
	printf("Tamanho dos Registros...: %d bytes\n", sizeof(Endereco));
	printf("Tamanho do Arquivo......: %ld bytes", tamarqCep);
    free(colisoes);
    pausa();
	return 0;
}

/******************************************************************
Fun��o....: listaHash
Finalidade: Lista a tabela Hash
******************************************************************/
int listaHash() {
    HashTab ht;   // Auxiliares para adicionar registros na tabela
    long registro = -1;

    limpaTela();
	printf("Listando o arquivo de �ndices...\n\n");
    registro++;
    ht = leHash(registro);
    while(ht.CEP != "") {
        printf("\nRegistro: %ld - ", registro);
        printf("CEP: %ld - ", ht.CEP);
        printf("Posi��o: %ld - ", ht.PosArq);
        printf("Pr�ximo: %ld", ht.Proximo);
        registro++;
        ht = leHash(registro);
    }
	pausa();
	return 1;
}

/******************************************************************
Fun��o....: abreHash
Finalidade: Abre o arquivo da tabela hash
******************************************************************/
int abreHash() {
    // Verifica a exist�ncia do arquivo de hash e o abre. Caso n�o exista, o cria.
	arqhash = fopen(HASHFILE, "r");
	if(!arqhash) {
        fclose(arqhash);
    	limpaTela();   		// Limpa a tela
		criaHash();			// Cria o arquivo de hash
		indexaHash();		// Indexa atrav�s do arquivo de CEPs
	}
    return 0;
}

/******************************************************************
Fun��o....: leHash
Finalidade: Le um registro da tabela de Hash
******************************************************************/
HashTab leHash(long pos) {
    HashTab reg;	// Vari�vel para a guarda de um registro de hash

    fseek(arqhash, pos * sizeof(HashTab), SEEK_SET);	// Posiciona o ponteiro na posi��o desejada
    memset(&reg, 0, sizeof(HashTab));    				// Zera a vari�vel para guardar o hash
//    fread(&reg, sizeof(HashTab), 1, arqhash);			// L� o registro
    fread(&reg.CEP, 1, sizeof(long), arqhash);
    fread(&reg.PosArq, 1, sizeof(long), arqhash);
    fread(&reg.Proximo, 1,  sizeof(long), arqhash);
    return reg;
}

/******************************************************************
Fun��o....: escreveHash
Finalidade: Grava um registro no arquivo da tabela de Hash
Par�metros: reg - Registro a ser gravado
            pos - Deslocamento do registro em rela��o ao in�cio do
                  arquivo de hash
            rel - a pesquisa � relativa ao in�cio do arquivo, � po-
                  si��o corrente ou ao fim do arquivo?
******************************************************************/
int escreveHash(HashTab reg, long pos, int rel) {
    fseek(arqhash, pos * sizeof(HashTab), rel);		// Posiciona o ponteiro na posi��o desejada
    fwrite(&reg, sizeof(HashTab), 1, arqhash);		// Grava o registro no arquivo
    return 1;
}

/******************************************************************
Fun��o....: fechaHash
Finalidade: Fecha o arquivo da tabela hash
******************************************************************/
int fechaHash() {
	fclose(arqhash);     // Fecha o arquivo de ordena��o (hash)
    return 1;
}

/******************************************************************
Fun��o....: ultregHash
Finalidade: Retorna a �ltima posi��o do arquivo de hash
******************************************************************/
long ultregHash() {
    return (ftell(arqhash) / sizeof(HashTab));
}

/******************************************************************
Fun��o....: calculaHash
Finalidade: Retorna o c�lculo para a tabela de dispers�o
******************************************************************/
long calculaHash(long valor) {
	return (valor % MAXHASH);
}

/******************************************************************
Fun��o....: inicializaHash
Finalidade: Incializa um registro da tabela de Hash
******************************************************************/
HashTab inicializaHash(long cep, long posarq, long proximo) {
    HashTab reg;	// Vari�vel para a guarda de um registro de hash

	memset(&reg, 0, sizeof(HashTab));    						// Zera a vari�vel para guardar o hash
    reg.CEP = cep; reg.PosArq = posarq; reg.Proximo = proximo;	// Inicializa os dados dos registros
	return reg;
}
<<<<<<< HEAD
=======

>>>>>>> origin/master
