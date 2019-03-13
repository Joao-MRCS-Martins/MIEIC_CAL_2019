/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conteúdo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conteúdo actual (só para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}



/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve()
{
	return solve(0,0);
}



bool Sudoku::solve(int i, int j) {

	if(isComplete() || i > 8 || j>8)
		return true;

	pair<int,int> sqr;

	//verificar quando está preenchido
	if(numbers[i][j] !=0) {
		if(i ==8 && j ==8) {
			return true;
		}
		//continuar para a proxima casa
		sqr = nextSquare(i,j);
		return solve(sqr.first,sqr.second);
	}

	//tentar preencher o quadrado com um numero 1..9
	for(int n =1; n<=9;n++) {
		//verificar as condicoes de jogo
		if(block3x3HasNumber[i/3][j/3][n] || columnHasNumber[j][n] || lineHasNumber[i][n])
			continue;
		else {
			//preencher o quadrado
			fillSqr(i,j,n);

			//continuar para a proxima casa
			sqr = nextSquare(i,j);

			//verificar se o puzzle se resolve com este numero nesta casa
			if(solve(sqr.first,sqr.second))
				return true;
			//senao apagar o numero e tentar com outro
			else {
				unFillSqr(i,j,n);
				continue;
			}

		}
	}
	return false;
}

void Sudoku::fillSqr(int i, int j, int n) {
	numbers[i][j] = n;
	block3x3HasNumber[i/3][j/3][n] = true;
	columnHasNumber[j][n] = true;
	lineHasNumber[i][n]=true;
	countFilled++;
}

pair<int, int> Sudoku::nextSquare(int i, int j) {
	if(i == 8) {
		return make_pair(0,j+1);
	}
	else {
		return make_pair(i+1,j);
	}
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}

void Sudoku::unFillSqr(int i, int j, int n) {
	numbers[i][j] =0;
	block3x3HasNumber[i/3][j/3][n] = false;
	columnHasNumber[j][n] = false;
	lineHasNumber[i][n]=false;
	countFilled--;
}
