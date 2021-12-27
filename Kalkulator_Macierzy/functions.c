#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Matrix {
	int rows;
	int columns;
	float** data;
};
typedef struct Matrix Matrix;


int OperationChoice();
int CreateOrLoad();
Matrix* LoadMatrix();
Matrix* InitMatrix(int rows, int cols);
Matrix* CreateMatrix(int rows, int cols);
void SaveMatrix(Matrix* matrix);
void PrintMatrix(Matrix* matrix);
Matrix* MatrixChoice();
Matrix* AddMatrix(Matrix* firstMatrix, Matrix* secondMatrix, Matrix* operationMatrix);
Matrix* SubMatrix(Matrix* firstMatrix, Matrix* secondMatrix, Matrix* operationMatrix);
Matrix* MultiplyMatrixScalar(Matrix* firstMatrix, int scalar, Matrix* operationMatrix);
Matrix* MultiplyMatrixMatrix(Matrix* firstMatrix, Matrix* secondMatrix, Matrix* operationMatrix);
void ClearBuffer();


int OperationChoice()
{
	system("cls");
	int n;
	printf("Dostepne operacje:\n1. Dodawanie macierzy\n2. Odejmowanie macierzy\n3. Mnozenie macierzy przez skalar\n4. Mnozenie macierzy przez macierz\n5. Transpozycja macierzy\n6. Wyjdz\n\n");
	printf("Wybierz operacje: ");
	scanf_s("%d", &n);
	ClearBuffer();
	if (n < 0 && n>6) {
		n = OperationChoice();
	}
	return n;
}

int CreateOrLoad()
{
	int n;
	printf("\t1. Wczytaj macierz\n\t2. Stworz nowa macierz\n");
	printf("\t>>> ");
	scanf_s("%d", &n);
	ClearBuffer();
	if (n < 0 && n>1) {
		n = CreateOrLoad();
	}
	return n;
}

Matrix* LoadMatrix()
{
	Matrix* matrix = InitMatrix(10, 10);
	FILE *filepointer = NULL;
	char filename[20], c;
	int txt = 1;
	int iter = 0;
	printf("Wybierz macierz (wprowadz nazwe wraz z rozszerzeniem .txt):\n");
	system("dir /b *.txt");
	while(1)
	{
		printf(">>>");
		scanf("%s", filename);
		if (CheckTxt(filename) == 0)
		{
			filepointer = fopen(filename, "r");
			break;
		}
	}
	
	if (filepointer == NULL) {
		printf("Nie znaleziono pliku\n\n");
		free(matrix);
		return LoadMatrix();
	}
	c = fgetc(filepointer);
	int i = 0;
	int	j = 0;
	int n = 0;
	int rows = 0;
	int columns = 0;
	while (c != EOF)
	{
		if (c == ',')
		{
			if(n == 1)
			{
				matrix->data[i][j] = -matrix->data[i][j];
				n = 0;
			}
			j += 1;
		}
		if (c == '\n')
		{
			if (n == 1)
			{
				matrix->data[i][j] = -matrix->data[i][j];
				n = 0;
			}
			i += 1;
			j = 0;
		}
		if (c == '-')
		{
			n = 1;
		}
		if(c != ',' && c != '\n' && c != '-') matrix->data[i][j] = matrix->data[i][j] * 10 + (int)c - 48;
		c = fgetc(filepointer);
		if (i > rows) rows = i;
		if (j > columns) columns = j;
	}
	if (n == 1)
	{
		matrix->data[i][j] = -matrix->data[i][j];
		n = 0;
	}
	matrix->rows = rows + 1;
	matrix->columns = columns + 1;
	PrintMatrix(matrix);
	printf("\n");
	fclose(filepointer);
	return matrix;
}

Matrix* InitMatrix(int rows, int cols)
{
	struct Matrix* matrix = malloc(sizeof(Matrix));
	matrix->rows = rows;
	matrix->columns = cols;
	int** data = malloc(sizeof(float*) * rows);
	for (int x = 0; x < rows; x++)
	{
		data[x] = calloc(cols, sizeof(float));
	}
	matrix->data = data;

	return matrix;
}

Matrix* CreateMatrix(int rows, int cols)
{
	Matrix* matrix = InitMatrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("Wprowadz liczbe do pozycji [%d,%d]: ", i + 1, j + 1);
			scanf_s("%f", &matrix->data[i][j]);
			ClearBuffer();
		}
	}
	PrintMatrix(matrix);
	return matrix;
}

void SaveMatrix(Matrix* matrix)
{
	char a;
	
	printf("Czy chcesz zapisac wynik (t/n):\n");
	scanf(" %c", &a);
	ClearBuffer();
	system("cls");
	if (a == 't') 
	{
		FILE* filepointer;
		char filename[20];
		char coma = ',';
		char nl = '\n';

		printf("Wprowadz nazwe dla macierzy (wraz z rozszerzeniem .txt):\n");
		while (1)
		{
			printf(">>>");
			scanf("%s", filename);
			if (CheckTxt(filename) == 0)
			{
				filepointer = fopen(filename, "w");
				break;
			}
		}

		if (filepointer != NULL) {
			for (int i = 0; i < matrix->rows; i++)
			{
				for (int j = 0; j < matrix->columns; j++) 
				{
					fprintf(filepointer, "%f", matrix->data[i][j]);
					if(j != matrix->columns - 1)
						fprintf(filepointer, "%c", coma);
				}
				if(i != matrix->rows - 1)
					fprintf(filepointer, "%c", nl);
			}
			fclose(filepointer);
		}

		printf("Zapisano macierz\n");
		PrintMatrix(matrix);

	}

}

void PrintMatrix(Matrix* matrix)
{
	printf("\n");
	for (int x = 0; x < matrix->rows; x++) {
		for (int y = 0; y < matrix->columns; y++) {
			printf("%.2f ", matrix->data[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

Matrix* MatrixChoice()
{

	int col = 0;
	while (col != 1 && col != 2)
	{
		col = CreateOrLoad();
	}
	if (col == 1)
	{
		Matrix* matrix = LoadMatrix();
		return matrix;
	}
	else
	{
		int rows = 0;
		int cols = 0;
		while (rows <= 0 || rows > 10)
		{
			printf("Podaj liczbe wierszy (od 1 do 10): ");
			scanf_s("%d", &rows);
			ClearBuffer();
		}
		printf("\n");
		while (cols <= 0 || cols > 10)
		{
			printf("Podaj liczbe kolumn (od 1 do 10): ");
			scanf_s("%d", &cols);
			ClearBuffer();
		}
		printf("\n");
		Matrix* matrix = CreateMatrix(rows, cols);
		return matrix;
	}


	
}

Matrix* AddMatrix(Matrix* firstMatrix, Matrix* secondMatrix, Matrix* operationMatrix)
{

	if (firstMatrix->rows != secondMatrix->rows || firstMatrix->columns != secondMatrix->columns)
	{
		printf("Liczba wierszy lub liczba kolumn macierzy nie sa jednakowe\n\n");
		
		return operationMatrix;
	}
	else
	{
		operationMatrix->rows = secondMatrix->rows;
		operationMatrix->columns = firstMatrix->columns;
		for (int i = 0; i < firstMatrix->rows; i++)
		{
			for (int j = 0; j < firstMatrix->columns; j++)
			{
				operationMatrix->data[i][j] = firstMatrix->data[i][j] + secondMatrix->data[i][j];
			}
		}
		printf("Wynik operacji to:\n");
		PrintMatrix(operationMatrix);
		SaveMatrix(operationMatrix);
		return operationMatrix;
	}
}

Matrix* SubMatrix(Matrix* firstMatrix, Matrix* secondMatrix, Matrix* operationMatrix)
{
	if (firstMatrix->rows != secondMatrix->rows || firstMatrix->columns != secondMatrix->columns)
	{
		printf("Liczba wierszy lub liczba kolumn macierzy nie sa jednakowe\n\n");

		return operationMatrix;
	}
	else
	{
		operationMatrix->rows = secondMatrix->rows;
		operationMatrix->columns = firstMatrix->columns;
		for (int i = 0; i < firstMatrix->rows; i++)
		{
			for (int j = 0; j < firstMatrix->columns; j++)
			{
				operationMatrix->data[i][j] = firstMatrix->data[i][j] - secondMatrix->data[i][j];
			}
		}
		printf("Wynik operacji to:\n");
		PrintMatrix(operationMatrix);
		SaveMatrix(operationMatrix);
		return operationMatrix;
	}
}

Matrix* MultiplyMatrixScalar(Matrix* firstMatrix, int scalar, Matrix* operationMatrix)
{
		operationMatrix->rows = firstMatrix->rows;
		operationMatrix->columns = firstMatrix->columns;
		for (int i = 0; i < firstMatrix->rows; i++)
		{
			for (int j = 0; j < firstMatrix->columns; j++)
			{
				operationMatrix->data[i][j] = firstMatrix->data[i][j] * scalar;
			}
		}
		printf("Wynik operacji to:\n");
		PrintMatrix(operationMatrix);
		SaveMatrix(operationMatrix);
		return operationMatrix;
}

Matrix* MultiplyMatrixMatrix(Matrix* firstMatrix, Matrix* secondMatrix, Matrix* operationMatrix)
{
	if (firstMatrix->columns != secondMatrix->rows)
	{
		printf("Liczba kolumn pierwszej macierzy nie jest rowna liczbie wierszy drugiej macierzy\n\n");

		return operationMatrix;
	}
	else
	{
		operationMatrix->rows = secondMatrix->columns;
		operationMatrix->columns = firstMatrix->rows;
		for (int i = 0; i < firstMatrix->rows; i++)
		{
			for (int j = 0; j < secondMatrix->columns; j++)
			{
				operationMatrix->data[i][j] = 0;
				for (int k = 0; k < firstMatrix->columns; k++) 
				{
					operationMatrix->data[i][j] += firstMatrix->data[i][k] * secondMatrix->data[k][j];
				}
			}
		}
		printf("Wynik operacji to:\n");
		PrintMatrix(operationMatrix);
		SaveMatrix(operationMatrix);
		return operationMatrix;
	}


}

Matrix* MatrixTranspose(Matrix* firstMatrix, Matrix* operationMatrix)
{
	operationMatrix->rows = firstMatrix->columns;
	operationMatrix->columns = firstMatrix->rows;
	for (int i = 0; i < firstMatrix->columns; i++)
	{
		for (int j = 0; j < firstMatrix->rows; j++)
		{
			operationMatrix->data[i][j] = firstMatrix->data[j][i];
		}
	}
	printf("Wynik operacji to:\n");
	PrintMatrix(operationMatrix);
	SaveMatrix(operationMatrix);
	return operationMatrix;
}

void ClearBuffer()
{
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

int CheckTxt(char* filename)
{
	int i = 0;
	for (i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '.')
		{
			break;
		}
	}
	if (i == strlen(filename))
	{
		printf("Nie podano rozszerzenia .txt\n");
		return 1;
	}
	if (filename[i + 1] == 't')
	{
		if (filename[i + 2] == 'x')
		{
			if (filename[i + 3] == 't')
			{
				if (filename[i + 4] == '\0')
				{
					return 0;
				}
			}
		}
	}
	printf("Nie podano rozszerzenia .txt\n");
	return 1;
}