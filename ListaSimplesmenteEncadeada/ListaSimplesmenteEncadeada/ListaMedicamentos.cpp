#include <iostream>
#include <locale.h> // setlocale
#include <stdlib.h> // system
#include <string>   // Textos em geral

using namespace std;

// O projeto deverá ser uma lista simplesmente encadeada com 
// os seguintes dados a respeito de remédios: código e nome do medicamento, 
// nome do laboratório, princípio ativo, preço de compra e de venda, ano e mês de validade.
// Estrutura Remedio:
struct Remedio {
	int codigo;
	string nomeLab;
	string pAtivo;
	float precoCompra;
	float precoVenda;
	string nomeRemedio;
	string validade;
	int mes_validade;
};

// Estrutura do Nó - ok
struct No {
	Remedio dados;		// estrutura guardada dentro da lista
	No* proxNo;			// aponta para o próximo Nó da lista
};


// Nó início da lista
struct Lista {
	int qtdNo;
	No* inicio;
};

//prototipacoes
Lista* criarLista();

// Inserir
bool inserirListaInicio(Lista* ptrLista, int codigo, string nomeLab, string pAtivo, float precoCompra, float precoVenda, string nomeRemedio, string validade, int mes_validade);
bool inserirListaFim(Lista* ptrLista, int codigo, string nomeLab, string pAtivo, float precoCompra, float precoVenda, string nomeRemedio, string validade, int mes_validade);
bool inserirListaOrdenada(Lista* ptrLista, int codigo, string nomeLab, string pAtivo, float precoCompra, float precoVenda, string nomeRemedio, string validade, int mes_validade);

// Buscar / Pesquisar
void exibirLista(Lista* ptrLista);

//// Remover
bool removerListaInicio(Lista* ptrLista);
bool removerListaFim(Lista* ptrLista);
bool removerListaOrdenada(Lista* ptrLista, int codigo);

// maior e menor preço
void maiorPreco(Lista* ptrLista);
void menorPreco(Lista* ptrLista);

void vencimentoEm3Meses(Lista* ptrLista);

// pesquisar principio ativo
//No* pesquisarpAtivo(Lista* ptrLista, string pAtivo);
//Lista* pesquisarpAtivo(Lista* ptrLista, string pAtivo);
void pesquisarpAtivo(Lista* ptrLista, string pAtivo);

void liberarLista(Lista* ptrLista);


int main() {
	setlocale(LC_ALL, "Portuguese");

	Lista* pLista;
	string pAtivo;

	// CRIAR lista - ok
	pLista = criarLista();

	// Insira, via programação, 10 medicamentos a uma lista. 
	// O ano de vencimento dos produtos deve ser todos 2020 e os meses deverão variar entre junho e dezembro.

	//--------------------------------------------------------
	// Inserção no INÍCIO
	//--------------------------------------------------------
	// Inserimos o Nó

	inserirListaInicio(pLista, 1, "Ache", "AAS", 2.55, 9.50, "Aspirina", "12/12/2020", 12);
	inserirListaInicio(pLista, 2, "Bayer", "Metamizol", 3.70, 11.50, "Dipirona", "11/11/2020", 11);
	inserirListaInicio(pLista, 3, "Pfizer", "ibuprofeno", 3.55, 14.50, "Advil", "10/10/2020", 10);


	//--------------------------------------------------------
	// Inserção no FINAL
	//--------------------------------------------------------
	inserirListaFim(pLista, 4, "Biosintetica", "nimesulida", 5.55, 20.50, "Allegra", "09/09/2020", 9);
	inserirListaFim(pLista, 5, "Eurofarma", "amoxicilina tri-hidratada", 10.55, 35.50, "Amoxicilina", "08/08/2020", 8);
	inserirListaFim(pLista, 6, "Biolab", "ondansetrona", 9.55, 25.50, "Vonau Flash", "07/07/2020", 7);


	//--------------------------------------------------------
	// Inserção  ORDENADO
	//--------------------------------------------------------
	inserirListaOrdenada(pLista, 10, "Altapharma", "Biotina", 1.55, 5.30, "hairUp", "06/06/2020", 6);
	inserirListaOrdenada(pLista, 8, "Ache", "gestodeno e etinilestradiol", 15.55, 35.50, "Alestra 20", "11/09/2020", 9);
	inserirListaOrdenada(pLista, 9, "Cimed", "Loratadina", 4.05, 12.50, "Loratamed", "23/08/2020", 8);
	inserirListaOrdenada(pLista, 7, "Cimed", "maleato de clorfeniramina + paracetamol", 10.55, 50.50, "Cimegripe", "09/12/2020", 12);
	//add de 2 medicamentos sem principio ativo
	inserirListaOrdenada(pLista, 11, "Ache", "", 10.55, 50.50, "Neosaldina", "21/6/2020", 6);
	inserirListaOrdenada(pLista, 12, "Cimed", "", 30.55, 50.50, "Doralgina", "21/7/2020", 7);

	exibirLista(pLista);

	//Para verificar a remoçao, descomentar o código

	//removerListaInicio(pLista);
	//removerListaFim(pLista);
	//removerListaOrdenada(pLista, 8);

	//cout << endl << endl << "---------------------------------" << endl;
	//cout << "----------Após remoção-----------" << endl;
	//exibirLista(pLista);

	// maior e menor preco
	maiorPreco(pLista);
	menorPreco(pLista);

	// vencimento em 3 meses
	cout << endl << endl << "-------------------------------------------------------------------" << endl;
	cout << "----------medicamentos com validade nos proximos 3 meses-----------" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	vencimentoEm3Meses(pLista);

	// medicamentos com principio ativo
	exibirLista(pLista);
	cout << endl << endl << "-------------------------------------------------------------------" << endl;
	cout << "----------------medicamentos com principio ativo-------------------" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	pesquisarpAtivo(pLista, pAtivo);


	liberarLista(pLista);

	system("pause");
	return 0;
}


//--------------------------------------------------------
// CRIAR LISTA - ok
//--------------------------------------------------------
Lista* criarLista() {
	Lista* ptrLista;

	ptrLista = new Lista;

	// Se a lista NÃO pode ser criada
	if (ptrLista == NULL) {
		cout << "Não foi possível criar a lista!" << endl;
		return NULL;
	}

	// Como a lista está vazia, o INÍCIO aponta para NULL	
	ptrLista->qtdNo = 0;
	ptrLista->inicio = NULL;

	return ptrLista;
}

//--------------------------------------------------------
// LIBERAR LISTA - ok
//--------------------------------------------------------
void liberarLista(Lista* ptrLista) {
	No* ptrNoAtual;

	//Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}

	// Exclui cada Nó da lista
	while (ptrLista->inicio != NULL)
	{
		ptrNoAtual = ptrLista->inicio;

		ptrLista->inicio = ptrNoAtual->proxNo;

		delete  ptrNoAtual;
	}

	delete ptrLista;
}

//--------------------------------------------------------
// INSERIR NO INÍCIO DA LISTA - ok
//--------------------------------------------------------
bool inserirListaInicio(Lista* ptrLista, int codigo, string nomeLab, string pAtivo, float precoCompra, float precoVenda, string nomeRemedio, string validade, int mes_validade) {
	No* ptrNoNovo;

	//Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return false;
	}

	//---------------------------------------------------------------
	//	Cria o novo nó
	//---------------------------------------------------------------
	ptrNoNovo = new No;

	if (ptrNoNovo == NULL) {
		cout << "Memória insulficiente!" << endl;
		return false;
	}

	ptrNoNovo->dados.codigo = codigo;
	ptrNoNovo->dados.nomeLab = nomeLab;
	ptrNoNovo->dados.pAtivo = pAtivo;
	ptrNoNovo->dados.precoCompra = precoCompra;
	ptrNoNovo->dados.precoVenda = precoVenda;
	ptrNoNovo->dados.nomeRemedio = nomeRemedio;
	ptrNoNovo->dados.validade = validade;
	ptrNoNovo->dados.mes_validade = mes_validade;

	ptrNoNovo->proxNo = ptrLista->inicio;

	ptrLista->inicio = ptrNoNovo;

	// Incrementa o quantidade de Nós
	ptrLista->qtdNo++;

	return true;
}

//--------------------------------------------------------
// INSERIR NO FINAL DA LISTA - ok
//--------------------------------------------------------
bool inserirListaFim(Lista* ptrLista, int codigo, string nomeLab, string pAtivo, float precoCompra, float precoVenda, string nomeRemedio, string validade, int mes_validade) {
	No* ptrNoNovo;
	No* ptrNoAtual;

	//Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return false;
	}

	//---------------------------------------------------------------
	//	Cria o novo nó
	//---------------------------------------------------------------
	ptrNoNovo = new No;

	if (ptrNoNovo == NULL) {
		cout << "Memória insulficiente!" << endl;
		return false;
	}

	ptrNoNovo->dados.codigo = codigo;
	ptrNoNovo->dados.nomeLab = nomeLab;
	ptrNoNovo->dados.pAtivo = pAtivo;
	ptrNoNovo->dados.precoCompra = precoCompra;
	ptrNoNovo->dados.precoVenda = precoVenda;
	ptrNoNovo->dados.nomeRemedio = nomeRemedio;
	ptrNoNovo->dados.validade = validade;
	ptrNoNovo->dados.mes_validade = mes_validade;

	ptrNoNovo->proxNo = NULL;

	ptrNoAtual = ptrLista->inicio;

	// Se não houver nenhum nó na lista
	if (ptrNoAtual == NULL) {
		ptrLista->inicio = ptrNoNovo;
	}
	else {
		// Localiza o último nó
		while (ptrNoAtual->proxNo != NULL) {
			ptrNoAtual = ptrNoAtual->proxNo;
		}
		ptrNoAtual->proxNo = ptrNoNovo;
	}

	// Incrementa o quantidade de Nós
	ptrLista->qtdNo++;

	return true;
}

//--------------------------------------------------------
// INSERIR EM LISTA ORDENADA - ok
//--------------------------------------------------------
bool inserirListaOrdenada(Lista* ptrLista, int codigo, string nomeLab, string pAtivo, float precoCompra, float precoVenda, string nomeRemedio, string validade, int mes_validade) {
	No* ptrNoNovo;
	No* ptrNoAnterior;
	No* ptrNoAtual;

	//---------------------------------------------------------------
	//	Cria o novo nó
	//---------------------------------------------------------------
	ptrNoNovo = new No;

	if (ptrNoNovo == NULL) {
		cout << "Memória insulficiente!" << endl;
		return false;
	}

	ptrNoNovo->dados.codigo = codigo;
	ptrNoNovo->dados.nomeLab = nomeLab;
	ptrNoNovo->dados.pAtivo = pAtivo;
	ptrNoNovo->dados.precoCompra = precoCompra;
	ptrNoNovo->dados.precoVenda = precoVenda;
	ptrNoNovo->dados.nomeRemedio = nomeRemedio;
	ptrNoNovo->dados.validade = validade;
	ptrNoNovo->dados.mes_validade = mes_validade;

	ptrNoNovo->proxNo = NULL;

	//Se a lista estiver vazia
	if (ptrLista->inicio == NULL) {
		ptrLista->inicio = ptrNoNovo;
	}
	else
	{
		ptrNoAnterior = NULL;
		ptrNoAtual = ptrLista->inicio;

		// Localiza a posição de inserção
		while (ptrNoAtual != NULL && ptrNoAtual->dados.codigo < codigo) {
			ptrNoAnterior = ptrNoAtual;
			ptrNoAtual = ptrNoAtual->proxNo;
		}

		// Insere no INÍCIO da lista
		if (ptrNoAtual == ptrLista->inicio) {
			ptrNoNovo->proxNo = ptrLista->inicio;
			ptrLista->inicio = ptrNoNovo;
		}
		else { // Insere no MEIO ou no FIM da lista

			ptrNoNovo->proxNo = ptrNoAnterior->proxNo;
			ptrNoAnterior->proxNo = ptrNoNovo;
		}
	}

	// Incrementa o quantidade de Nós
	ptrLista->qtdNo++;

	return true;
}

//--------------------------------------------------------
// EXIBIR A LISTA - ok
//--------------------------------------------------------
void exibirLista(Lista* ptrLista) {
	No* ptrNoAtual;

	//Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}

	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return;
	}

	ptrNoAtual = ptrLista->inicio;

	cout << "--------------------------------- " << endl;
	cout << "--------LISTA MEDICAMENTOS------- " << endl;
	cout << "--------------------------------- " << endl;
	while (ptrNoAtual != NULL) {

		cout << "Codigo do Medicamento: " << ptrNoAtual->dados.codigo << endl;
		cout << "Laboratorio de Fabricaçao: " << ptrNoAtual->dados.nomeLab << endl;
		cout << "Principio Ativo: " << ptrNoAtual->dados.pAtivo << endl;
		cout << "Preço de Compra: " << ptrNoAtual->dados.precoCompra << endl;
		cout << "Preço de Venda: " << ptrNoAtual->dados.precoVenda << endl;
		cout << "Nome do medicamento: " << ptrNoAtual->dados.nomeRemedio << endl;
		cout << "Data de Validade: " << ptrNoAtual->dados.validade << endl << endl << endl;

		ptrNoAtual = ptrNoAtual->proxNo;

		//ptrNoAtual == NULL;
	}

	cout << endl;
}

//--------------------------------------------------------
// REMOVER DO INÍCIO DA LISTA - ok
//--------------------------------------------------------
bool removerListaInicio(Lista* ptrLista) {
	No* ptrNoAtual;

	// Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return false;
	}

	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return false;
	}

	// Ajusta o INÍCIO
	ptrNoAtual = ptrLista->inicio;
	ptrLista->inicio = ptrNoAtual->proxNo;

	// Exclui o primeiro nó
	delete ptrNoAtual;

	// Decrementa o quantidade de Nós
	ptrLista->qtdNo--;

	return true;
}

////--------------------------------------------------------
//// REMOVER DO FIM DA LISTA - ok
////--------------------------------------------------------
bool removerListaFim(Lista* ptrLista) {
	No* ptrNoAnterior;
	No* ptrNoAtual;

	// Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return false;
	}

	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return false;
	}

	ptrNoAnterior = NULL;
	ptrNoAtual = ptrLista->inicio;

	// Localiza o nó final da lista
	while (ptrNoAtual->proxNo != NULL) {
		ptrNoAnterior = ptrNoAtual;
		ptrNoAtual = ptrNoAtual->proxNo;
	}


	// Se for o primeiro nó da lista
	if (ptrNoAtual == ptrLista->inicio) {
		ptrLista->inicio = NULL;
	}
	else {
		ptrNoAnterior->proxNo = NULL;
	}

	// Exclui o primeiro nó
	delete ptrNoAtual;

	// Decrementa o quantidade de Nós
	ptrLista->qtdNo--;

	return true;
}

////--------------------------------------------------------
//// REMOVER DO MEIO DA LISTA - ok
////--------------------------------------------------------
bool removerListaOrdenada(Lista* ptrLista, int codigo) {
	No* ptrNoAnterior;
	No* ptrNoAtual;

	// Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return false;
	}

	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return false;
	}

	ptrNoAnterior = NULL;
	ptrNoAtual = ptrLista->inicio;

	// Localizao nó que será excluído
	while (ptrNoAtual != NULL && ptrNoAtual->dados.codigo != codigo) {
		ptrNoAnterior = ptrNoAtual;
		ptrNoAtual = ptrNoAtual->proxNo;
	}

	if (ptrNoAtual == NULL) {
		cout << "O codigo  " << codigo << " não foi encontrado!" << endl;
		return false;
	}


	// Se for o primeiro nó da lista
	if (ptrNoAtual == ptrLista->inicio) {
		ptrLista->inicio = ptrNoAtual->proxNo;
	}
	else {
		ptrNoAnterior->proxNo = ptrNoAtual->proxNo;
	}

	// Exclui o nó atual
	delete ptrNoAtual;

	// Decrementa o quantidade de Nós
	ptrLista->qtdNo--;

	return true;
}

// A primeira deve receber, também, o nome do princípio ativo, 
// encontrar e imprimir todos os medicamentos que tenham o princípio ativo informado.
//--------------------------------------------------------
// Medicamentos com principio ativo informado - ok
//--------------------------------------------------------
void pesquisarpAtivo(Lista* ptrLista, string pAtivo) {
	No* ptrNoAtual;
	int verifica = 0;

	// Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}

	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return;
	}

	ptrNoAtual = ptrLista->inicio;

	// Localiza a posição do Nó pesquisado
	while (ptrNoAtual != NULL) {
		if (ptrNoAtual->dados.pAtivo != "") {
			cout << "Codigo do Medicamento: " << ptrNoAtual->dados.codigo << endl;
			cout << "Laboratorio de Fabricaçao: " << ptrNoAtual->dados.nomeLab << endl;
			cout << "Preço de Compra: " << ptrNoAtual->dados.precoCompra << endl;
			cout << "Preço de Venda: " << ptrNoAtual->dados.precoVenda << endl;
			cout << "Nome do medicamento: " << ptrNoAtual->dados.nomeRemedio << endl;
			cout << "Data de Validade: " << ptrNoAtual->dados.validade << endl << endl << endl;
			verifica++;
		}
		ptrNoAtual = ptrNoAtual->proxNo;
	}
	if (verifica == 0)
		cout << "O medicamento nao apresenta principio ativo descrito" << endl;

}

// A segunda deve encontrar e imprimir o medicamento mais barato e o mais caro da lista.
//--------------------------------------------------------
// Encontrando maior e menos preco - ok
//--------------------------------------------------------
void maiorPreco(Lista* ptrLista) {
	No* ptrNoAtual;

	// Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}

	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return;
	}

	float maiorPreco = -1;

	ptrNoAtual = ptrLista->inicio;

	// Passa por todos os nós da lista
	while (ptrNoAtual != NULL) {

		if (ptrNoAtual->dados.precoVenda > maiorPreco) {
			maiorPreco = ptrNoAtual->dados.precoVenda;
		}

		ptrNoAtual = ptrNoAtual->proxNo;
	}
	cout << "---------------------" << endl;
	cout << "O maior preco é: " << maiorPreco << endl;
}

void menorPreco(Lista* ptrLista) {
	No* ptrNoAtual;

	// Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}

	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return;
	}

	float menorPreco = 100;

	ptrNoAtual = ptrLista->inicio;

	// Passa por todos os nós da lista
	while (ptrNoAtual != NULL) {

		if (ptrNoAtual->dados.precoVenda < menorPreco) {
			menorPreco = ptrNoAtual->dados.precoVenda;
		}

		ptrNoAtual = ptrNoAtual->proxNo;
	}

	cout << "O menor preço é: " << menorPreco << endl;
	cout << "---------------------" << endl;

}

// A terceira deve receber, também, o mês de vencimento do produto. 
// Deverá ser listado todos os medicamentos que terão a data de validade vencida nos próximos 3 meses.
//--------------------------------------------------------
// Validade nos proximos 3 meses - ok
//--------------------------------------------------------
void vencimentoEm3Meses(Lista* ptrLista) {
	No* ptrNoAtual;

	// Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}

	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return;
	}
	ptrNoAtual = ptrLista->inicio;

	while (ptrNoAtual != NULL) {
		if (ptrNoAtual->dados.mes_validade < 9) {
			cout << "Codigo do Medicamento: " << ptrNoAtual->dados.codigo << endl;
			cout << "Laboratorio de Fabricaçao: " << ptrNoAtual->dados.nomeLab << endl;
			cout << "Preço de Compra: " << ptrNoAtual->dados.precoCompra << endl;
			cout << "Preço de Venda: " << ptrNoAtual->dados.precoVenda << endl;
			cout << "Nome do medicamento: " << ptrNoAtual->dados.nomeRemedio << endl;
			cout << "Data de Validade: " << ptrNoAtual->dados.validade << endl << endl << endl;
		}
		ptrNoAtual = ptrNoAtual->proxNo;
	}
}