#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <algorithm>
//#include <array>

//----------- INTEGER Input filtrers -------------------------------
int Get_Int_SA();				// String-analysis вариант фильтра INTEGER
int Get_Int_Positive();			// String-Analysis вариант проверки ввода INTEGER_POSITIVE		
int Get_Int_PG();				// peek&get вариант проверки ввода INTEGER	
//----------- DOUBLE Input filtrers --------------------------------
double Get_Dbl_SA();		// String-analysis вариант фильтра DOUBLE.
double Get_Dbl_Positive();	// String-analysis вариант фильтра DOUBLE_POSITIVE
double Get_Dbl_PG();		// peek&get вариант проверки ввода DOUBLE	
//----------- Service functions ------------------------------------
int Get_Random(int Range_min, int Range_max);
double Get_Random(double Range_min, double Range_max);
template <typename ANY> void Fill_Array_with_Random(ANY arr[], int Size, ANY Range_min, ANY Range_max);
template <typename ANY> void Array_Console_Out(ANY arr[], int Size);

// Homework 19 -----------------------------------------------------

//Task 1
template <typename ANY> ANY Max_Common_Divider(ANY num1, ANY num2)
{
	for (ANY i = num1; i >= 0; i--)
	{
		if (num1 % i == 0 && num2 % i == 0)
		{
			return i;
		}
	}
	return -1;
}
void Max_Common_Divider_demo()
{
	std::cout << "\n"<<"Max_Common_Divider(10, 15) = " << Max_Common_Divider(10, 15);
	std::cout << "\n" << "Max_Common_Divider(8, 48) = " << Max_Common_Divider(8, 48);
	std::cout << "\n" << "Max_Common_Divider(184, 2056) = " << Max_Common_Divider(184, 2056);
	std::cout << "\n" << "Max_Common_Divider(10LL, 15LL) = " << Max_Common_Divider(10LL, 15LL);
	//std::cout << "\n" << "Max_Common_Divider(10.0, 15.0) = " << Max_Common_Divider(10.0, 15.0); //couldn't be compiled
	//std::cout << "\n" << "Max_Common_Divider(10.0F, 15.0F) = " << Max_Common_Divider(10.0F, 15.0F); //couldn't be compiled
	char a = 10, b = 15;
	std::cout << "\n" << "Max_Common_Divider(char a=10, char b=15) = " << int(Max_Common_Divider(a, b));
}

//Task 2
template <typename ANY> ANY What_Digit_in_Position(ANY Number, int position)
{
	return (Number % int(pow(10, position))) / int(pow(10, position - 1));
}
template <typename ANY> ANY mirror_number(ANY num)
{
	ANY reversed_number = 0;
	int num_digit=1;
	while (num % long(pow(10, num_digit)) != num)
	{
		num_digit++;
	}
	int step=0;
	do
	{
		step++;
		reversed_number += What_Digit_in_Position(num, step) * (pow(10, num_digit - step));

	} while (num % long(pow(10, step)) != num);

	return reversed_number;
}
void mirror_number_demo()
{
	std::cout << "\n" << "mirror_number(1234) = " << mirror_number(1234);
	std::cout << "\n" << "mirror_number(95) = " << mirror_number(95);
	std::cout << "\n" << "mirror_number(140) = " << mirror_number(140);
	std::cout << "\n" << "mirror_number(5) = " << mirror_number(5);	
	std::cout << "\n" << "mirror_number(1234LL) = " << mirror_number(1234LL);
	std::cout << "\n" << "mirror_number(95LL) = " << mirror_number(95LL);
	std::cout << "\n" << "mirror_number(short(140) = " << mirror_number(short(140));
	std::cout << "\n" << "mirror_number(char(5)) = " << mirror_number(char(5));
	//std::cout << "\n" << "mirror_number(1234.0) = " << mirror_number(1234.0);
}

//Task 3
template <typename ANY> int  Sort_Array_from_N(ANY arr[], int Size, ANY NUM)
{
	for (int i = 0; i < Size; i++)
	{
		if (arr[i] == NUM)
		{
			std::sort(arr + i+1, arr + Size);
			std::cout << "\nN = " << NUM << " is on " << i << " position. Array is sorted after this position.\n";
			return i;
		}
	}
	std::cout <<"\nThere is no mathes with " << NUM <<" in array "<<'\n';
	return  -1;
}
void Sort_Array_from_N_demo()
{
	int const Size = 15;
	int Random_Array[Size];
	srand(time(NULL));
	int N = Get_Random(0, 14); //???first call of function somehow is very stable (exampl 9, 9, 9, 9...),second and further are random
	N = Get_Random(0, 15);
	std::cout << "\nRandom Array INTEGER [-999...999]:\n";
	Fill_Array_with_Random(Random_Array, Size, -999, 999);
	Array_Console_Out(Random_Array, Size);
	Sort_Array_from_N(Random_Array, Size, Random_Array[N]);
	Array_Console_Out(Random_Array, Size);

	float Random_Array_float[Size];
	N = Get_Random(0, 15);
	std::cout << "\nRandom Array FLOAT [-999...999]:\n";
	Fill_Array_with_Random(Random_Array_float, Size, -999.0F, 999.0F);
	Array_Console_Out(Random_Array_float, Size);
	Sort_Array_from_N(Random_Array_float, Size, Random_Array_float[N]);
	Array_Console_Out(Random_Array_float, Size);

	std::cout << "\n\nWish to enter N? [0..14] - number of element of array\n";
	N = Get_Int_SA();
	Sort_Array_from_N(Random_Array, Size, Random_Array[N]);
	Array_Console_Out(Random_Array, Size);
	Sort_Array_from_N(Random_Array_float, Size, Random_Array_float[N]);
	Array_Console_Out(Random_Array_float, Size);
}

//Task 4
template <typename ANY> ANY Search_First_Ordinary_in_Array(ANY arr[], int Size)
{
	for (int i = 0; i < Size; i++)
	{
		int Divider_Counter = 0;
		for (int k = 1; k <= arr[i]; k++)
			if (arr[i] % k == 0) Divider_Counter++;
		if (Divider_Counter == 2) return arr[i];
	}
	std::cout << "\nThere are no ordinary numbers in array\n";
	return 0;
}
template <typename ANY> int Search_Position_First_Ordinary_in_Array(ANY arr[], int Size)
{
	for (int i = 0; i < Size; i++)
	{
		int Divider_Counter = 0;
		for (int k = 1; k <= arr[i]; k++)
			if (arr[i] % k == 0) Divider_Counter++;
		if (Divider_Counter == 2) return i;
	}
	return -1;
}
void Search_First_Ordinary_in_Array_demo()
{
	int const Size = 15;
	int Random_Array[Size];
	srand(time(NULL));
	std::cout << "\nRandom_Array [-999...999]:\n";
	Fill_Array_with_Random(Random_Array, Size, -999, 999);
	Array_Console_Out(Random_Array, Size);
	if (Search_First_Ordinary_in_Array(Random_Array, Size))
	{
		std::cout << "\nFirst ordinary number in array -> " << Search_First_Ordinary_in_Array(Random_Array, Size);
		std::cout << "\nPosition -> " << Search_Position_First_Ordinary_in_Array(Random_Array, Size);
	}
}

// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	setlocale(LC_CTYPE, "Russian");
	system("mode con cols=110 lines=40"); // ??? текст основного меню не входит в окно консоли по умолчанию. При небольшом увеличении окна (lines < 85) пропадает полоса прокрутки, что не здорово. Как ee оставить и не делать (lines > 85)?
	std::string Name_of_Work = { "Home Work 19: More functions" };
	std::string Menu_Element_1 = { "Max_Common_Divider(num1, num2): Maximum common divider of two numbers" };
	std::string Menu_Element_2 = { "mirror_number(num): Mirror a number " };
	std::string Menu_Element_3 = { "Sort_Array_from_N(arr[], Size, N): Search first encaunter of N in array, then sort from this position" };
	std::string Menu_Element_4 = { "Search_First_Ordinary_in_Array(arr[], Size): Returns first ordinary number in an array" };

	do {		
		system("cls");
		std::cout << "\n\t***\t***\t" << Name_of_Work << "\t***\t***\n\n\t\n\nChoose an opion: \n";
		std::cout << "\n 1. " << Menu_Element_1;
		std::cout << "\n 2. " << Menu_Element_2;
		std::cout << "\n 3. " << Menu_Element_3;
		std::cout << "\n 4. " << Menu_Element_4;
		std::cout << "\n\n 0. Exit\n";
		int choice = 0;
		std::cout << "\nYour choice: ";
		choice = Get_Int_Positive();		
		std::cout << "\n";
		// Обработка выбора пользователя
		if (choice == 0) { std::cout << "\nGood By"; for (int j = 0; j < 50; j++) { Sleep(50 - j); std::cout << "y"; } std::cout << "e!"; Sleep(850);  return 0; }
		else if (choice == 1) Max_Common_Divider_demo();
		else if (choice == 2) mirror_number_demo();
		else if (choice == 3) Sort_Array_from_N_demo();
		else if (choice == 4) Search_First_Ordinary_in_Array_demo();
			
		else { std::cout << "\nSuch choice does not exist yet\n"; Sleep(1000); }
		std::cout << "\n\n";
		system("pause");
		} while (true);
		
	//system("pause");
	return 0;
}

// Вспомагательные функции -----------------------------------------
int Get_Int_SA() {
	std::string a;
	std::cin.sync(); // заклинание средней силы против неудачного чтения getline
	std::cin.clear(); // заклинание малой силы против неудачного чтения getline
	getline(std::cin, a);
	//std::cout << "\nFunction: working with " << a << "\n"; для отладки
	if (a != "")
	{

		if ((a.find_first_not_of("-0123456789") == -1))
		{
			for (int i = 1; i < a.size(); i++) // определяем есть ли минусы кроме первого символа
			{
				if (a[i] == '-') 
				{
					std::cout << "Input Error: Minus misstanding\n";
					return Get_Int_SA();
				}
			}
			try
			{
				return stoi(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow\n";
				return Get_Int_SA();
			}


		}
		else
		{
			std::cout << "Input Error: Incorrect symbol\n";
			return Get_Int_SA();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input\n";
		return Get_Int_SA();
	}
}
int Get_Int_Positive()
{
	std::string a;
	std::cin.sync();
	std::cin.clear();
	//std::cin.ignore(1024, '\n');
	getline(std::cin, a);
	if (a != "") // оказывается getline считывает пустую строку которую stoi уже не берет
	{

		if ((a.find_first_not_of("0123456789") == -1))
		{
			try{
				return stoi(a);
			}
			catch (std::out_of_range){
				std::cout << "Incorrect input: INTEGER overflow. Decrease input\n";
			}
		}
		else
		{
			std::cout << "Incorrect symbols: positive INTEGER expected. Try again...\n";
			return Get_Int_Positive();
		}
		//return Get_Int_Positive();
	}
	else
		std::cout << "Input Error: NULL input\n";
	return Get_Int_Positive();
}
int Get_Int_PG()
{
	int a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! Repeat please...\n";
	}
	return a;
}
double Get_Dbl_SA(){
	std::string a;
	std::cin.sync();
	getline(std::cin, a);
	if (a == "") { std::cout << "\nInput Error : NULL input\n"; return Get_Dbl_SA(); }
	if ((a.find_first_not_of("-.0123456789") == -1))
	{
		for (int i = 1; i < a.size(); i++) // Проверяем отсутсвие лишних минусов
		{
			if (a[i] == '-')
			{
				std::cout << "\nInput Error: Minus misstanding\n";
				return Get_Dbl_SA();
			}

		}
		bool Dot_Flag = 0;
		for (int i = 0; i < a.size(); i++) // проверяем отсутсвие лишних точек
		{
			if (a[i] == '.')
			{
				if (Dot_Flag == 1)
				{
					std::cout << "\nInput Error: Dot misstandig\n";
					return Get_Dbl_SA();
				}
				Dot_Flag = 1;
			}

		}		 	
				try{
					return stod(a);
				}
				catch (std::out_of_range) {
					std::cout << "Data type overflow\n";
					return Get_Dbl_SA();					
				}						
	}
	else {		
		std::cout << "Incorrect symbols: REAL expected.\nUse dot instead of coma. Example 50.64\n";
		return Get_Dbl_SA();
	}
}
double Get_Dbl_Positive(){
	std::string a, dot = "."; // = "";
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "")
	{
		if ((a.find_first_not_of(".0123456789") == -1))
		{
			bool One_Dot_already = false;
			for (int i = 0; i < a.size(); i++)
			{
				//std::cout << "\na[" << i << "] ->" << a[i]<< " == " <<dot[0];
				//std::cout << "\nflag -> " << One_Dot_already;
				if (a[i] == dot[0] && One_Dot_already == true) //проверяем количество разделителей
				{
					std::cout << "dot placement error\n";
					return Get_Dbl_Positive();
				}
				if (a[i] == dot[0])	One_Dot_already = true;
			}
			try
			{
				//std::cout << "trying stod: " << a;
				//system("pause");
				return stod(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Incorrect input: Data type [DOUBLE] overflow. Decrease input\n";
				return Get_Dbl_Positive();
			}
		}
		else
		{
			//std::cout << "Incorrect symbols: positive REAL expected.\nUse coma instead of dot. Example 50,64\n"; // да точно говорю вот даже сообщение такое было, а теперь наоборот wtf*2?!
			std::cout << "Incorrect symbols: positive REAL expected.\nUse dot instead of coma. Example 50.64\n";
			return Get_Dbl_Positive();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input\n";
		return Get_Dbl_Positive();
	}
	return Get_Dbl_Positive();
}
double Get_Dbl_PG()
{
	double a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! Repeat please...\n";
	}
	return a;
}
int Get_Random(int Range_min=-999, int Range_max=999)
{
	if (Range_min > Range_max) 
	{ 
		std::cout << "\nError: Range_min > Range_max. New range: [Range_max..Range_min]\n";
		std::swap(Range_min, Range_max);
	}
	//return (Range_min + rand() % (Range_max - Range_min + 1));
	double K_random = double((rand() % RAND_MAX)) / RAND_MAX;
	int random = Range_min + ((Range_max - Range_min) * K_random);
	//return Range_min + (Range_max - Range_min) * (rand() % RAND_MAX) / RAND_MAX;
	return random;
}
double Get_Random(double Range_min=-9999.0, double Range_max=9999.0)
{
	if (Range_min > Range_max)
	{
		std::cout << "\nError: Range_min > Range_max. New range: [Range_max..Range_min]\n";
		std::swap(Range_min, Range_max);
	}
	return 	Range_min + (Range_max - Range_min) * double(rand() % RAND_MAX) / RAND_MAX;	
}
template <typename ANY> void Array_Console_Out(ANY arr[], int Size)
{
	std::cout << "\n[";
	for (int i = 0; i < Size; i++)
		std::cout << arr[i] << ", ";
	std::cout << "\b\b]\n";
}
template <typename ANY> void Fill_Array_with_Random(ANY arr[], int Size, ANY Range_min, ANY Range_max)
{
	for (int i = 0; i < Size; i++)
	{
		arr[i] = Get_Random(Range_min, Range_max);		
	}
}
