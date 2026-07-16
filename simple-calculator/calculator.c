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
 * main - Entry point for the simple calculator program.
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
		if (scanf("%d", &choice) != 1)
		{
			/* Handle non-numeric input gracefully to prevent infinite loops */
			printf("Invalid choice\n\n");
			while (getchar() != '\n')
				;
			continue;
		}

		if (choice < 0 || choice > 4)
		{
			printf("Invalid choice\n\n");
			continue;
		}

		if (choice == 0)
		{
			printf("Bye!\n");
			break;
		}

		printf("A: ");
		scanf("%lf", &a);
		printf("B: ");
		scanf("%lf", &b);

		if (choice == 1)
			printf("Result: %g\n\n", a + b);
		else if (choice == 2)
			printf("Result: %g\n\n", a - b);
		else if (choice == 3)
			printf("Result: %g\n\n", a * b);
		else if (choice == 4)
		{
			if (b == 0)
				printf("Error: division by zero\n\n");
			else
				printf("Result: %g\n\n", a / b);
		}
	}

	return (0);
}
