
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct node
{
	char mat[MAX];
	char nome[MAX];
	char sobrenome[MAX];
	char email[MAX];
	char tel[MAX];
	char salario[MAX];
	struct node *ant, *prox;
}NODE;


typedef struct tree {

	char mat[MAX];
	char nome[MAX];
	char sobrenome[MAX];
	char email[MAX];
	char tel[MAX];
	char salario[MAX];
	int height;
	struct tree *left, *right;
	
} Tree;

int opcao (NODE **Lista,Tree **ptr, int opc, int *tipo, FILE *arq,char arquivo[]);
/////////////////////////////////////////////////
void CriaLista (NODE **Lista, FILE *arq);
int VaziaLista (NODE *Lista);
NODE *alocaLista ();
void CriaNoLista (NODE **Lista, FILE *arq);
void InsereNoLista (NODE **Lista, NODE *novo, int *taNaLista); // insere o noh na lista de forma ordenada //
void InsereContato (NODE *novo,  char *tok, int *cont); // insere os dados da string no repectivo noh //
void ExibeLista (NODE *Lista);
void BuscaNomeLista (NODE *Lista, int *achei, char *nome, char *sobre);
int BuscaMatLista (NODE *Lista, char *mat);
void RemoveMatLista (NODE **Lista, char *mat, int *achei);
void apagaLista(NODE **Lista);
/////////////////////////////////////////////////
int max(int a, int b);
int alt(Tree *ptr);
Tree *rightRotate (Tree* ptr);
Tree *leftRotate (Tree *ptr);
int fator(Tree *N);
Tree *checkBalance(Tree *ptr);
Tree *maxLeft(Tree *ptr);
Tree *CriaTree(Tree **ptr, FILE *arq);
void insertTree(Tree **ptr,Tree *novo, int *taNaTree);
void apagaTree(Tree **ptr);
Tree* CriaNoTree (Tree **root, FILE *arq);
void InsereContatoTree (Tree *novo,  char *tok, int *cont);
Tree *removeTree(Tree *ptr, char v[], int *achei);
void ExibeTree (Tree *ptr);
void BuscaNomeTree(Tree *ptr,int *achei, char n[], char s[]);
void BuscaMatTree(Tree *ptr, char m[], int *achei);
Tree* alocaTree();

int main(int argc, char *argv[])
{
	int opc = 1;
	NODE *Lista = NULL;
	NODE **l = &Lista;
	Tree *root = NULL;
	Tree **r = &root;

	char arquivo[MAX];

	FILE *arq = NULL;

	system ("cls");

	if(argc > 1) {
		strcpy(arquivo,argv[1]);
		arq = fopen (arquivo, "r");
	}

	while(!arq) {

		puts ("Digite o nome do arquivo:");
		scanf ("%s", arquivo);
		arq = fopen (arquivo, "r");
		if (!arq) {
			printf("Arquivo nao encontrado!\n");
		} 
	}

	int tipo = 0; // tipo = 0 -> vazio, tipo = 1 -> lista, tipo = 2 -> árvore
	int *pTipo = &tipo;

	do
	{
		system ("cls");

			printf("Arquivo Atual %s\n",arquivo);
			if(tipo == 0)
				puts("Carregado como: NADA");
			else if(tipo == 1)
				puts("Carregado como: LISTA");
			else 
				puts("Carregado como: ARVORE");
			puts ("\n**********Escolha uma opcao abaixo:**********\n");
			puts("1 - Carregar arquivo como lista encadeada;");
			puts("2 - Carregar arquivo como arvore;");
			puts ("3 - Exibir registros por ordem de matricula;");
			puts ("4 - Buscar registro por nome;");
			puts ("5 - Buscar registro por matricula;");
			puts ("6 - Inserir registro;");
			puts ("7 - Remover registro.");
			puts ("0 - Encerrar programa");
			scanf ("%d", &opc);

		
		opcao (l, r, opc, pTipo,arq,arquivo);
		system ("pause");
	}while (opc);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int opcao (NODE **Lista, Tree **root, int opc, int *tipo, FILE *arq, char arquivo[])
{
	printf("\n");
	NODE *tmp;
	Tree *aux;
	char nome [MAX], mat[MAX],sobre[MAX];	
	char ch;
	
	switch (opc)
	{
		case 1:
		;

		clock_t start_t1, end_t1, total_t1; 
		arq = fopen (arquivo, "r");

		if(*tipo == 1)
			apagaLista(Lista);
		else if(*tipo == 2) {
			apagaTree(root);
			*root = NULL;
		}
		*tipo = 1;
		
		start_t1 = clock();
		CriaLista(Lista, arq);

		end_t1 = clock();
		printf("\nTempo para carregamento da lista: %f (s)\n", (double)(end_t1 - start_t1) / CLOCKS_PER_SEC );
		
		break;

		case 2: ;

		clock_t start_t2, end_t2, total_t2; 
		arq = fopen (arquivo, "r");

		if(*tipo == 1)
			apagaLista(Lista);
		else if(*tipo == 2) {
			apagaTree(root);
			*root = NULL;
		}
		*tipo = 2;
			
		start_t2 = clock();
		*root = CriaNoTree(root,arq);

		end_t2 = clock();
		printf("\nTempo para carregamento da arvore: %f (s)\n", (double)(end_t2 - start_t2) / CLOCKS_PER_SEC );
	
		break;

		case 3: ;

		if(*tipo == 0) {
			puts("Opcao Invalida, arquivo ainda nao foi carregado!");
			break;
		}

		clock_t start_t3, end_t3, total_t3; 
		start_t3 = clock();		
		
		if (*tipo == 1)
			ExibeLista (*Lista);
		else if (*tipo == 2) {
			ExibeTree (*root);
		}

		end_t3 = clock();
		printf("\nTempo para exibicao: %f (s)\n", (double)(end_t3 - start_t3) / CLOCKS_PER_SEC );
		
		break;

		case 4: ;

		if(*tipo == 0) {
			puts("Opcao Invalida, arquivo ainda nao foi carregado!");
			break;
		}
		
		printf ("Digite o nome que deseja buscar:\n");
		scanf (" %s", nome);
		printf ("Digite o sobrenome do nome que deseja buscar:\n");
		scanf(" %s", sobre);
		puts("");
		int achei = 0;

		clock_t start_t4, end_t4, total_t4; 
		start_t4 = clock();

		if(*tipo == 1) {
			BuscaNomeLista (*Lista, &achei, nome, sobre);
			if (!achei)
				printf("Nome nao encontrado!\n");
		} else if(*tipo == 2) {
			aux = NULL;
			BuscaNomeTree(*root,&achei,nome,sobre);
			if(!achei) {
				printf("Nome nao encontrado!\n");
			}
		}
		
		end_t4 = clock();
		printf("\nTempo para busca: %f (s)\n", (double)(end_t4 - start_t4)/CLOCKS_PER_SEC);

		break;

		case 5: ;

		if(*tipo == 0) {
			puts("Opcao Invalida, arquivo ainda nao foi carregado!");
			break;
		}
		
		printf ("Digite a matricula que deseja buscar:\n");
		scanf (" %s", mat);
		printf("\n");

		clock_t start_t5, end_t5, total_t5; 
		start_t5 = clock();

		if(*tipo == 1) {

			if (!BuscaMatLista (*Lista, mat))
				printf("Matricula nao encontrada!\n");

		} else if (*tipo == 2) {
			int achei = 0;
			BuscaMatTree(*root, mat,&achei);
			if(!achei)
				printf("Matricula nao encontrada!\n");

		}

		end_t5 = clock();
		printf("\nTempo para busca: %f (s)\n", (double)(end_t5 - start_t5) / CLOCKS_PER_SEC );

		break;

		case 6: ;

		if(*tipo == 0) {
			puts("Opcao Invalida, arquivo ainda nao foi carregado!");
			break;
		}

		printf("Digite uma matricula para o novo funcionario:\n");
		scanf(" %s", mat);
		
		clock_t start_t6, end_t6, total_t6; 
		

		if(*tipo == 1) {

			NODE *novo = alocaLista();

			int taNaLista = 0;

			if(novo) {
				strcpy (novo -> mat, mat);
				printf("Digite o nome do novo funcionario:\n");
				scanf(" %s", novo -> nome);
				printf ("Sobrenome:\n");
				scanf(" %s", novo -> sobrenome);
				printf ("Email:\n");
				scanf(" %s", novo -> email);
				printf ("Telefone:\n");
				scanf(" %s", novo -> tel);
				printf ("Salario:\n");
				scanf(" %s",novo -> salario);

				start_t6 = clock();
				InsereNoLista (Lista, novo,&taNaLista);
				if(taNaLista) {
					puts("Registro nao adicionado. Matricula ja estava presente na lista.");
					free(novo);
				}
				end_t6 = clock();
			}

		} else if(*tipo == 2) {

			Tree *novo = alocaTree();
			int taNaTree = 0;

			if(novo) {
				strcpy (novo -> mat, mat);
				printf("Digite o nome do novo funcionario:\n");
				scanf(" %s", novo -> nome);
				printf ("Sobrenome:\n");
				scanf(" %s", novo -> sobrenome);
				printf ("Email:\n");
				scanf(" %s", novo -> email);
				printf ("Telefone:\n");
				scanf(" %s", novo -> tel);
				printf ("Salario:\n");
				scanf(" %s",novo -> salario);

				start_t6 = clock();
				insertTree(root,novo,&taNaTree);
				if(taNaTree) {
					puts("Registro nao adicionado. Matricula ja estava presente na arvore.");
					free(novo);
				}
				end_t6 = clock();
			}
		}
		
		printf("\nTempo para insercao: %f (s)\n", (double)(end_t6 - start_t6) / CLOCKS_PER_SEC );

		break;

		case 7: ;

		if(*tipo == 0) {
			puts("Opcao Invalida, arquivo ainda nao foi carregado!");
			break;
		}

		printf ("Digite a matricula do funcionario a ser removido:\n");
		scanf (" %s", mat);
	
		clock_t start_t7, end_t7, total_t7; 
		start_t7 = clock();

		if(*tipo == 1) {

			int achei = 1;

			RemoveMatLista (Lista, mat,&achei);

			if (achei)
				puts("Matricula removida com sucesso");
			else 
				printf("Matricula nao encontrada!\n");
			

		} else if(*tipo == 2) {

			int achei = 1;

			*root = removeTree(*root,mat, &achei);

			if(achei) 
				puts("Matricula removida com sucesso");
			else 
				printf("Matricula nao encontrada!\n");

		}
		end_t7 = clock();
		printf("\nTempo para delecao: %f (s)\n", (double)(end_t7 - start_t7) / CLOCKS_PER_SEC );

		break;

		case 0:

		break;

		default:
		puts ("Opcao Invalida");

	}
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
////////////////////// 												   ////////////////////
//								ALGORITMOS DE LISTA
////////////////////// 												   ////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void CriaLista (NODE **Lista, FILE *arq)
{
	CriaNoLista (Lista, arq);
}

int VaziaLista (NODE *Lista)
{
	return (Lista == NULL);
}

void CriaNoLista (NODE **Lista, FILE *arq) 
{
	char *tok;

	char str[150];
	NODE *novo;
	int i = 0;
	int cont = 0;
	while (fgets(str, sizeof(str), arq) != NULL)
	{
		i++;
		
		if (i > 2)
		{
			
			tok = strtok(str,",");

			NODE *tmp;
			NODE *novo = alocaLista();

			while (tok != NULL)
			{
				//printf("%s\n",tok);
				cont++;
				InsereContato (novo, tok, &cont);
				tok = strtok(NULL,",");
	
			}
			int taNaLista = 0;
			//printf("%s\n",novo->mat);
			InsereNoLista(Lista, novo,&taNaLista);
			if(taNaLista)
				free(novo);

		}
		
	}
	printf("Operacao Concuida!\n%d Contatos foram importados\n",i-2);

	fclose (arq);
}

NODE *alocaLista()
{
	NODE *novo = (NODE*)malloc(sizeof(NODE));
	if (!novo)
	{
		printf("Sem memoria!\n");
		return NULL;
	}
	novo -> prox = NULL;
	novo -> ant = NULL;
	return novo;
}

void InsereNoLista (NODE **Lista, NODE *novo, int *taNaLista)
{
	if(VaziaLista(*Lista)) {
		novo->prox = novo->ant = NULL;
		*Lista = novo;
		return;
	}

	NODE *q = *Lista, *antes = NULL;

	while(q != NULL && atoi(q->mat) < atoi(novo->mat)) {
		antes = q,q = q->prox;
	}

	if(q == NULL) { //esta inserindo no final
		antes->prox = novo;
		novo->ant = antes, novo->prox = NULL;
		return;
	} 
	
	if(strcmp(q->mat, novo->mat) == 0) {
		*taNaLista = 1;
		return;
	}
	
	if(antes == NULL) { // inserindo no inicio
		novo->prox = *Lista,novo->ant = NULL;
		(*Lista)->ant = novo;
		*Lista = novo;
		return;
	}

	antes->prox = novo;
	novo->prox = q,novo->ant = antes;
	q->ant = novo;

}

void InsereContato (NODE *novo,  char *tok, int *cont)
{
	switch (*cont)
	{
		case 1:
		strcpy (novo -> mat, tok);
		break;

		case 2:
		strcpy (novo -> nome, tok);
		break;

		case 3:
		strcpy (novo -> sobrenome, tok);
		break;

		case 4:
		strcpy (novo -> email, tok);
		break;

		case 5:
		strcpy (novo -> tel, tok);
		break;

		default:
		strcpy (novo -> salario, tok);
		*cont = 0;
	}

}

void ExibeLista (NODE *Lista)
{

	if (VaziaLista (Lista))
	{
		printf("Lista vazia!\n");
		return;
	}
	
	NODE *tmp = Lista;
	
	while (tmp != NULL)
	{
		printf("\nMatricula: %s\n", tmp -> mat);
		printf("Nome: %s\n", tmp -> nome);
		printf("Sobrenome: %s\n", tmp -> sobrenome);
		printf("E-mail: %s\n", tmp -> email);
		printf("Telefone: %s\n", tmp -> tel);
		printf("Salario: %s\n", tmp -> salario);
		tmp = tmp ->prox;
	}
}

void BuscaNomeLista (NODE *Lista, int *achei, char *nome, char *sobre)
{
	NODE *tmp = Lista;

	while (tmp != NULL)
	{
		if ((strcmp (nome, tmp -> nome)) == 0 && (strcmp (sobre, tmp -> sobrenome)) == 0) {
			*achei = 1;
			printf("Matricula: %s\n", tmp -> mat);
			printf("Nome: %s\n", tmp -> nome);
			printf("Sobrenome: %s\n", tmp -> sobrenome);
			printf("E-mail: %s\n", tmp -> email);
			printf("Telefone: %s\n", tmp -> tel);
			printf("Salario: %s\n\n", tmp -> salario);
		}
		tmp = tmp -> prox;
	}
}

int BuscaMatLista (NODE *Lista, char *mat)
{
	NODE *tmp = Lista;

	while (tmp != NULL)
	{
		if ((strcmp (mat, tmp -> mat)) == 0) {
			printf("Matricula: %s\n", tmp -> mat);
			printf("Nome: %s\n", tmp -> nome);
			printf("Sobrenome: %s\n", tmp -> sobrenome);
			printf("E-mail: %s\n", tmp -> email);
			printf("Telefone: %s\n", tmp -> tel);
			printf("Salario: %s\n\n", tmp -> salario);
			return 1;
		} 
		tmp = tmp -> prox;
	} 
	return 0;
}

void RemoveMatLista (NODE **Lista, char *mat, int *achei)
{

	if(VaziaLista(*Lista)) {
		puts("A sua agenda esta vazia");
		*achei = -1;
		return;
	}

	NODE *tmp,*q = *Lista;

	while(q != NULL && strcmp(q->mat,mat) != 0)
		q = q->prox;

	if (q == NULL) { //nao achou o elemento
		*achei = 0;
		return;
	}


	if(q->ant == NULL) { // deleta o primeiro
		tmp = *Lista;
		*Lista = (*Lista)->prox;
		if(*Lista)
			(*Lista)->ant = NULL;
		free(tmp);
		return;
	}

	if(q->prox == NULL) { // deleta o ultimo
		(q->ant)->prox = NULL;
		free(q);
		return;
	}
	
	(q->ant)->prox = q->prox;
	(q->prox)->ant = q->ant;
	free(q);	

}

void apagaLista(NODE **Lista) {

	NODE **tmp = Lista;
	*Lista = NULL;
	NODE *next;
	while(*tmp != NULL) {
		next = (*tmp)->prox;
		free(*tmp);
		*tmp = NULL;
		*tmp = next;
	}
	
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
////////////////////// 												   ////////////////////
//								ALGORITMOS DE ÁRVORE
////////////////////// 												   ////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void IniciaTree(Tree *root) {

	root->left = root->right = NULL;
}


Tree *alocaTree()
{
	Tree *novo = (Tree*)malloc(sizeof(Tree));
	if (!novo)
	{
		printf("Sem memoria!\n");
		return NULL;
	}
	novo->left = NULL;
	novo->right = NULL;
	novo->height = 1;
	return novo;
}

int max(int a,int b) {
	if(a>b)
		return a;
	return b;
}

int alt(Tree *ptr) {
	if(ptr == NULL)
		return 0;
	//printf("ptr->height %d\n",ptr->height);
	return ptr->height;
}

Tree *rightRotate (Tree* ptr) {

	Tree *x, *y;
	x = ptr->left;
	y = x->right;

	x->right = ptr;
	ptr->left = y;

	ptr->height = max(alt(ptr->left),alt(ptr->right))+1;
	x->height = max(alt(x->left),alt(x->right))+1;

	return x;

}

Tree *leftRotate (Tree *ptr) {

	Tree *x, *y;
	x = ptr->right;
	y = x->left;

	x->left = ptr;
	ptr->right = y;

	ptr->height = max(alt(ptr->left),alt(ptr->right)) + 1;
	x->height = max(alt(x->left),alt(x->right)) + 1;

	return x;

}

int fator(Tree *N)
{

    if (N == NULL)
        return 0;

    //printf("ptr->left = %p, ptr->right = %p\n",N->left,N->right);
    //printf("ptr->left = %d, ptr->right = %d\n",N->left,N->right);

    return alt(N->left) - alt(N->right);
}


Tree* checkBalance(Tree *ptr) {

	//puts("cb1"); 

	// fator de balanceamento
	int fat = fator(ptr);
	//printf("fator = %d\n", fat);

	//puts("cb2");

	//Quatro casos a analisar

	//Se a árvore estiver desbalanceada para a esquerda e a sua subárvore da esquerda
	//estiver com altura da esquerda maior ou igual à da direita, entao rot p/ direita
	if (fat > 1 && fator(ptr->left) >= 0) {
        return rightRotate(ptr);
	}
	//puts("cb3");
 
 	//Se a árvore estiver desbalanceada para a esquerda e a sua subárvore da esquerda
	//estiver com altura da esquerda menor à da direita, entao rot p/ esquerda e direita
    if (fat > 1 && fator(ptr->left) < 0)
    {
        ptr->left =  leftRotate(ptr->left);
        return rightRotate(ptr);
    }
    //puts("cb4");
 
 	//Se a árvore estiver desbalanceada para a direita e a sua subárvore da direita
	//estiver com altura da direita maior ou igual à da esquerda, entao rot p/ esquerda
    if (fat < -1 && fator(ptr->right) <= 0)
        return leftRotate(ptr);
    //puts("cb5");
 
 	//Se a árvore estiver desbalanceada para a direita e a sua subárvore da direita
	//estiver com altura da direita menor à da esquerda, entao rot p/ direita e esquerda
    if (fat < -1 && fator(ptr->right) > 0)
    {
        ptr->right = rightRotate(ptr->right);
        return leftRotate(ptr);
    }
    //puts("cb6");

    // nao precisa rotacionar
    return ptr;

}

Tree* CriaNoTree (Tree **root, FILE *arq)
{
	char *tok;

	char str[150];
	int i = 0;
	int cont = 0;

	while (fgets(str, sizeof(str), arq) != NULL)
	{
				
		i++;
		
		if (i > 2)
		{
			tok = strtok(str,",");

			Tree *novo = alocaTree();

			while (tok != NULL)
			{
				//printf("%s\n",tok);
				cont++;

				InsereContatoTree(novo,tok,&cont);
					
				tok = strtok(NULL,",");
	
			}
			int taNaTree = 0;

			insertTree(root, novo, &taNaTree);
			if(taNaTree)
				free(novo);

		}
		
	}
	
	printf("Operacao Concuida!\n%d Contatos foram importados\n",i-2);

	fclose (arq);
	return *root;
}

void InsereContatoTree (Tree *novo,  char *tok, int *cont)
{
	switch (*cont)
	{
		case 1:
		strcpy (novo -> mat, tok);
		break;

		case 2:
		strcpy (novo -> nome, tok);
		break;

		case 3:
		strcpy (novo -> sobrenome, tok);
		break;

		case 4:
		strcpy (novo -> email, tok);
		break;

		case 5:
		strcpy (novo -> tel, tok);
		break;

		default:
		strcpy (novo -> salario, tok);
		*cont = 0;
	}

}

void insertTree(Tree **ptr,Tree *novo, int *taNaTree) {

	if(*ptr == NULL) {
		*ptr = novo;
		return;
	}

	if(atoi(novo->mat) > atoi((*ptr)->mat)) {
		insertTree(&((*ptr)->right),novo, taNaTree);
	} else if(atoi(novo->mat) < atoi((*ptr)->mat))
		insertTree(&((*ptr)->left),novo,taNaTree);
	else {
		*taNaTree = 1;
	} 

	(*ptr)->height = 1 + max(alt((*ptr)->left),alt((*ptr)->right));

	*ptr = checkBalance(*ptr);
}

void ExibeTree (Tree *ptr)
{

	if(ptr == NULL)
		return;

	ExibeTree(ptr->left);

	printf("\nMatricula: %s\n", ptr -> mat);
	printf("Nome: %s\n", ptr -> nome);
	printf("Sobrenome: %s\n", ptr -> sobrenome);
	printf("E-mail: %s\n", ptr -> email);
	printf("Telefone: %s\n", ptr -> tel);
	printf("Salario: %s\n", ptr -> salario);
	
	ExibeTree(ptr->right);
}

Tree *maxLeft(Tree *ptr) {
	if(ptr->right == NULL)
		return ptr;
	return maxLeft(ptr->right);
}

Tree *removeTree(Tree *ptr, char v[], int *achei) {

	if(ptr == NULL) {
		*achei = 0;
		return NULL;
	}

	if(atoi(v) > atoi(ptr->mat)) {
		ptr->right = removeTree(ptr->right,v,achei);
	} else if(atoi(v) < atoi(ptr->mat))
		ptr->left = removeTree(ptr->left,v,achei);
	else {

		if(ptr->left == NULL || ptr->right == NULL) {

			Tree *temp;
			if(ptr->left != NULL) {
				temp = ptr->left;	
				free(ptr);
				ptr = temp;			
			} else if(ptr->right != NULL) {
				temp = ptr->right;	
				free(ptr);
				ptr = temp;
			} else {
				// nao tem filhos
				free(ptr);
				return NULL;
			}

		} else {

			Tree *temp = maxLeft(ptr->left);
			strcpy(ptr->mat,temp->mat);
			strcpy(ptr->nome,temp->nome);
			strcpy(ptr->sobrenome,temp->sobrenome);
			strcpy(ptr->email,temp->email);
			strcpy(ptr->tel,temp->tel);
			strcpy(ptr->salario,temp->salario);
			ptr->left = removeTree(ptr->left,temp->mat,achei);
		}
	}

	ptr->height = 1 + max(alt(ptr->left),alt(ptr->right));

	ptr = checkBalance(ptr);
	
	return ptr;	
} 

void apagaTree(Tree **ptr) {

	if(*ptr == NULL)
		return;

	apagaTree(&((*ptr)->left));
	apagaTree(&((*ptr)->right));
	Tree **tmp = ptr;
	free(*tmp);
	*tmp = NULL;
}

void BuscaNomeTree(Tree *ptr,int *achei, char n[], char s[]) {

	if(ptr == NULL)
		return;

	if(strcmp((ptr)->nome,n) == 0 && strcmp((ptr)->sobrenome,s) == 0) {
		*achei = 1;
		printf("Matricula: %s\n", ptr -> mat);
		printf("Nome: %s\n", ptr -> nome);
		printf("Sobrenome: %s\n", ptr -> sobrenome);
		printf("E-mail: %s\n", ptr -> email);
		printf("Telefone: %s\n", ptr -> tel);
		printf("Salario: %s\n\n", ptr -> salario);
	}
	BuscaNomeTree(ptr->left,achei,n,s);
	BuscaNomeTree(ptr->right,achei,n,s);
}

void BuscaMatTree(Tree *ptr, char m[], int *achei) {

	if(ptr == NULL) 
		return;

	if(atoi(ptr->mat) == atoi(m)) {
		printf("Matricula: %s\n", ptr -> mat);
		printf("Nome: %s\n", ptr -> nome);
		printf("Sobrenome: %s\n", ptr -> sobrenome);
		printf("E-mail: %s\n", ptr -> email);
		printf("Telefone: %s\n", ptr -> tel);
		printf("Salario: %s\n\n", ptr -> salario);
		*achei = 1;
	} else if(atoi(m) > atoi(ptr->mat)) {
		BuscaMatTree(ptr->right,m,achei);
	} else 
		BuscaMatTree(ptr->left,m,achei); 
}