#include <stdio.h>

/**
 * print_menu - Displays the calculator menu options.
 *
 * Return: void.
 */
void print_menu(void)
{
	printf("Simple Calculator\n");
	printf("1) Add\n");
	printf("2) Subtract\n");
	printf("3) Multiply\n");
	printf("4) Divide\n");
	printf("0) Quit\n");
}

/**
 * main - Entry point for the simple calculator program with input recovery.
 *
 * Return: Always 0 (Success).
 */
int main(void)
{
	int choice = -1;
	double a, b;

	while (choice != 0)
	{
		print_menu();
		printf("Choice: ");
		
		/* فحص خيار القائمة وتطهير المخزن إذا فشل */
		if (scanf("%d", &choice) != 1)
		{
			printf("Invalid choice\n");
			while (getchar() != '\n')
				;
			continue;
		}

		if (choice < 0 || choice > 4)
		{
			printf("Invalid choice\n");
			continue;
		}

		if (choice == 0)
		{
			printf("Bye!\n");
			break;
		}

		/* فحص واستعادة المدخل الأول A */
		while (1)
		{
			printf("A: ");
			if (scanf("%lf", &a) == 1)
				break;
			printf("Invalid number\n");
			while (getchar() != '\n')
				;
		}

		/* فحص واستعادة المدخل الثاني B */
		while (1)
		{
			printf("B: ");
			if (scanf("%lf", &b) == 1)
				break;
			printf("Invalid number\n");
			while (getchar() != '\n')
				;
		}

		if (choice == 1)
			printf("Result: %g\n", a + b);
		else if (choice == 2)
			printf("Result: %g\n", a - b);
		else if (choice == 3)
			printf("Result: %g\n", a * b);
		else if (choice == 4)
		{
			if (b == 0)
				printf("Error: division by zero\n");
			else
				printf("Result: %g\n", a / b);
		}
	}

	return (0);
}
