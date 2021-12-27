#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

struct Matrix {
	int rows;
	int columns;
	float** data;
};



int main()
{
	struct Matrix* firstMatrix, * secondMatrix, * operationMatrix;
	

	while(1)
	{
		operationMatrix = InitMatrix(10, 10);
		int operation = OperationChoice();
		char a;
		
		switch (operation)
		{
		case 1:
			system("cls");
			printf("Dodawanie macierzy\n\n");

			printf("Pierwsza macierz\n");
			firstMatrix = MatrixChoice();

			printf("Druga macierz\n");
			secondMatrix = MatrixChoice();

			operationMatrix = AddMatrix(firstMatrix, secondMatrix, operationMatrix);
			
			free(firstMatrix);
			free(secondMatrix);
			free(operationMatrix);
			printf("Czy chcesz wykonac kolejna operacje(t/n)\n");
			scanf(" %c", &a);
			if (a == 't')
			{
				system("cls");
				break;
			}
			if (a == 'n')
				exit(0);
			else
			{
				break;
			}
			
		case 2:
			system("cls");
			printf("Odejmowanie macierzy\n\n");

			printf("Pierwsza macierz\n");
			firstMatrix = MatrixChoice();

			printf("Druga macierz\n");
			secondMatrix = MatrixChoice();

			operationMatrix = SubMatrix(firstMatrix, secondMatrix, operationMatrix);

			free(firstMatrix);
			free(secondMatrix);
			free(operationMatrix);
			printf("Czy chcesz wykonac kolejna operacje(t/n)\n");
			scanf(" %c", &a);
			if (a == 't')
			{
				system("cls");
				break;
			}
			if (a == 'n')
				exit(0);
			else
			{
				break;
			}

		case 3:
			
			system("cls");
			printf("Mnozenie macierzy przez skalar\n");

			printf("Macierz\n");
			firstMatrix = MatrixChoice();

			printf("Podaj skalar\n");
			int scalar = 0;
			scanf("%d", &scalar);

			operationMatrix = MultiplyMatrixScalar(firstMatrix, scalar, operationMatrix);

			free(firstMatrix);
			free(operationMatrix);
			printf("Czy chcesz wykonac kolejna operacje(t/n)\n");
			scanf(" %c", &a);
			if (a == 't')
			{
				system("cls");
				break;
			}
			if (a == 'n')
				exit(0);
			else
			{
				break;
			}

		case 4:
			system("cls");
			printf("Mnozenie macierzy przez macierz\n");

			printf("Pierwsza macierz\n");
			firstMatrix = MatrixChoice();

			printf("Druga macierz\n");
			secondMatrix = MatrixChoice();

			operationMatrix = MultiplyMatrixMatrix(firstMatrix, secondMatrix, operationMatrix);

			free(firstMatrix);
			free(secondMatrix);
			free(operationMatrix);
			printf("Czy chcesz wykonac kolejna operacje(t/n)\n");
			scanf(" %c", &a);
			if (a == 't')
			{
				system("cls");
				break;
			}
			if (a == 'n')
				exit(0);
			else
			{
				break;
			}

		case 5:
			system("cls");
			printf("Transpozycja macierzy\n");

			printf("Macierz\n");
			firstMatrix = MatrixChoice();

			operationMatrix = MatrixTranspose(firstMatrix, operationMatrix);

			free(firstMatrix);
			free(operationMatrix);
			printf("Czy chcesz wykonac kolejna operacje(t/n)\n");
			scanf(" %c", &a);
			if (a == 't')
			{
				system("cls");
				break;
			}
			if (a == 'n')
				exit(0);
			else
			{
				break;
			}

		case 6:
			free(operationMatrix);
			return 0;
		default:
			system("cls");
			break;
		}
	};
	return 0;
}