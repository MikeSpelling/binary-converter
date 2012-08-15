//////////////////////////////////////////
//	Created by Michael Spelling 10/2009 //
//  v5							//
//////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <conio.h>
using namespace std;

class convert
{
	int decimal;
	string y;	

	void ten();
	void hundred();
	void thousand();
	void tenThousand();
	void hundredThousand();
	void million();
	void tenMillion();
	void hundredMillion();
	void billion();
	void tenBillion();
public:

	// Function to convert decimal to string
	string convertIntStr(string z);
	// Function to convert decimal to binary
	int convertDecBin(string z);
	// Function to convert binary to decimal
	int convertBinDec(string z);
};

int main()
{	
	char c, d;
	string Number;
	convert converter;

	while(1)
	{
		cout << "Convert from [B]inary, [D]ecimal or [Q]uit: ";
		c = getch();
		cout << c;
		if(c == 81 || c == 113){cout << "\n";return 0;}
		cout << "\nConvert to [B]inary, [D]ecimal, Decimal [S]tring or [Q]uit: ";
		d = getch();
		cout << d;
		if(d == 81 || d == 113){cout << "\n";return 0;}

		switch(c)
		{
		// [B]
		case 66:
		case 98:
			{
				switch(d)
				{
				// [B]
				case 66:
				case 98:
					{
						cout << "\n\nError> Converting between same formats\n\n";
						break;
					}
				// [D]
				case 68:
				case 100:
					{
						cout << "\nEnter number to convert: ";
						cin >> Number;
						int x = converter.convertBinDec(Number);
						if(x == -1) {
							cout << "\nError> Conversion impossible: Number entered was not in binary\n\n";
							break;
						}

						cout << "\nNumber: " << x << "\n\n";
						break;
					}
				// [S]
				case 83:
				case 115:
					{
						stringstream tempString;
						cout << "\nEnter number to convert: ";
						cin >> Number;
						int x = converter.convertBinDec(Number);
						if(x == -1) {
							cout << "\nError> Conversion impossible: Number entered was not in binary\n\n";
							break;
						}
						tempString << x;
						cout << "\nNumber: " << converter.convertIntStr(tempString.str()) << "\n\n";
						break;
					}
				}
				break;
			}
		// [D]
		case 68:
		case 100:
			{
				switch(d)
				{
				// [B]
				case 66:
				case 98:
					{
						cout << "\nEnter number to convert: ";
						cin >> Number;
						int x = converter.convertDecBin(Number);
						if(x == -1) {
							cout << "\nError> Overflow: Number went out of range\n\n";
							break;
						}
						cout << "\nNumber: " << x << "\n\n";
						break;
					}
				// [D]
				case 68:
				case 100:
					{
						cout << "\n\nError> Converting between same formats\n\n";
						break;
					}
				// [S]
				case 83:
				case 115:
					{
						cout << "\nEnter number to convert: ";
						cin >> Number;
						cout << "\nNumber: " << converter.convertIntStr(Number) << "\n\n";
						break;
					}
				}
				break;
			}
		}
	}

	cout << "\n\n";
	return 0;
}

int convert::convertDecBin(string z)
{
	int v;
	decimal = 0;
	int w = z.size() - 1;
	for(int x = 0; x < z.size(); x++) {		
		v = pow(10, w);
		decimal = decimal + (v * (z[x]-48));
		w--;
	}

	int binary = 0;
	if(decimal < 0) return(-1);

	if(decimal >=1024)
		return(-1);
	if(decimal >= 512)
	{
		binary += 1000000000;
		decimal -= 512;
	}
	if(decimal >= 256)
	{
		binary += 100000000;
		decimal -= 256;
	}
	if(decimal >= 128)
	{
		binary += 10000000;
		decimal -= 128;
	}
	if(decimal >= 64)
	{
		binary += 1000000;
		decimal -= 64;
	}
	if(decimal >= 32)
	{
		binary += 100000;
		decimal -= 32;
	}
	if(decimal >= 16)
	{
		binary += 10000;
		decimal -= 16;
	}
	if(decimal >= 8)
	{
		binary += 1000;
		decimal -= 8;
	}
	if(decimal >= 4)
	{
		binary += 100;
		decimal -= 4;
	}
	if(decimal >= 2)
	{
		binary += 10;
		decimal -= 2;
	}
	if(decimal >= 1)
		binary += 1;
	return(binary);
}

int convert::convertBinDec(string z)
{
	int v;
	int decimal = 0;
	int w = z.size() - 1;
	for(int x = 0; x < z.size(); x++) {
		if(z[x] == '0' || z[x] == '1') {			
			v = pow(2, w);
			decimal = decimal + (v * (z[x]-48));
			w--;
		}
		else
			return(-1);
	}
	return(decimal);
}

string convert::convertIntStr(string z)
{
	bool isMinus = 0;
	int startPos = 0;
	if(z.at(0) == '-') {
		isMinus = 1;
		startPos = 1;;
	}
	decimal = 0;
	int w = z.size() - 1 - startPos;

	// Convert string to number
	for(int x = startPos; x < z.size(); x++) {	
		decimal = decimal + (pow(10, w) * (z[x]-48));
		w--;
	}

	// Control negative or zero cases
	if(decimal == 0) return("Zero");
	y.erase(0, y.length());
	if(isMinus)	y = "Minus ";

	// Control cases up to 2 Billion
	if(decimal > 2000000000 || decimal < -2000000000) return("Overflow");
	else {
		if(decimal == 2000000000) y = y + "Two Billion";
		if(decimal < 2000000000 && decimal >= 1000000000)
			tenBillion();
		if(decimal < 1000000000 && decimal >= 100000000)
			billion();
		if(decimal < 100000000 && decimal >= 20000000)
			hundredMillion();
		if(decimal < 20000000 && decimal >= 1000000)
			tenMillion();
		if(decimal < 1000000 && decimal >= 100000)
			million();
		if(decimal < 100000 && decimal >= 20000)
			hundredThousand();
		if(decimal < 20000 && decimal >= 1000)
			tenThousand();
		if(decimal < 1000 && decimal >= 100)
			thousand();
		if(decimal < 100 && decimal >= 20)
			hundred();
		if(decimal < 20)
			ten();
	}

	return(y);
}

void convert::ten()
{
	if(decimal == 1)
		y = y + "One";
	else if(decimal == 2)
		y = y + "Two";
	else if(decimal == 3)
		y = y + "Three";
	else if(decimal == 4)
		y = y + "Four";
	else if(decimal == 5)
		y = y + "Five";
	else if(decimal == 6)
		y = y + "Six";
	else if(decimal == 7)
		y = y + "Seven";
	else if(decimal == 8)
		y = y + "Eight";
	else if(decimal == 9)
		y = y + "Nine";
	else if(decimal == 10)
		y = y + "Ten";
	else if(decimal == 11)
		y = y + "Eleven";
	else if(decimal == 12)
		y = y + "Twelve";
	else if(decimal == 13)
		y = y + "Thirteen";
	else if(decimal == 14)
		y = y + "Fourteen";
	else if(decimal == 15)
		y = y + "Fifteen";
	else if(decimal == 16)
		y = y + "Sixteen";
	else if(decimal == 17)
		y = y + "Seventeen";
	else if(decimal == 18)
		y = y + "Eighteen";
	else if(decimal == 19)
		y = y + "Nineteen";
	return;
}

void convert::hundred()
{
	if(decimal < 30)
	{
		y = y + "Twenty";
		decimal -= 20;
		if(decimal > 0) y = y + " ";
	}
	else if(decimal < 40)
	{
		y = y + "Thirty";
		decimal -= 30;
		if(decimal > 0) y = y + " ";
	}
	else if(decimal < 50)
	{
		y = y + "Fourty";
		decimal -= 40;
		if(decimal > 0) y = y + " ";
	}
	else if(decimal < 60)
	{
		y = y + "Fifty";
		decimal -= 50;
		if(decimal > 0) y = y + " ";
	}
	else if(decimal < 70)
	{
		y = y + "Sixty";
		decimal -= 60;
		if(decimal > 0) y = y + " ";
	}
	else if(decimal < 80)
	{
		y = y + "Seventy";
		decimal -= 70;
		if(decimal > 0) y = y + " ";
	}
	else if(decimal < 90)
	{
		y = y + "Eighty";
		decimal -= 80;
		if(decimal > 0) y = y + " ";
	}
	else if(decimal < 100)
	{
		y = y + "Ninety";
		decimal -= 90;
		if(decimal > 0) y = y + " ";
	}
	return;
}

void convert::thousand()
{
	if(decimal < 200)
	{
		y = y + "One Hundred";
		decimal -= 100;
		if(decimal > 0) y = y + " and ";
	}
	else if(decimal < 300)
	{
		y = y + "Two Hundred";
		decimal -= 200;
		if(decimal > 0) y = y + " and ";
	}
	else if(decimal < 400)
	{
		y = y + "Three Hundred";
		decimal -= 300;
		if(decimal > 0) y = y + " and ";
	}
	else if(decimal < 500)
	{
		y = y + "Four Hundred";
		decimal -= 400;
		if(decimal > 0) y = y + " and ";
	}
	else if(decimal < 600)
	{
		y = y + "Five Hundred";
		decimal -= 500;
		if(decimal > 0) y = y + " and ";
	}
	else if(decimal < 700)
	{
		y = y + "Six Hundred";
		decimal -= 600;
		if(decimal > 0) y = y + " and ";
	}
	else if(decimal < 800)
	{
		y = y + "Seven Hundred";
		decimal -= 700;
		if(decimal > 0) y = y + " and ";
	}
	else if(decimal < 900)
	{
		y = y + "Eight Hundred";
		decimal -= 800;
		if(decimal > 0) y = y + " and ";
	}
	else if(decimal < 1000)
	{
		y = y + "Nine Hundred";
		decimal -= 900;
		if(decimal > 0) y = y + " and ";
	}
	return;
}

void convert::tenThousand()
{
	if(decimal < 2000)
	{
		y = y + "One Thousand";
		decimal -= 1000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
		
	}
	else if(decimal < 3000)
	{
		y = y + "Two Thousand";
		decimal -= 2000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 4000)
	{
		y = y + "Three Thousand";
		decimal -= 3000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 5000)
	{
		y = y + "Four Thousand";
		decimal -= 4000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 6000)
	{
		y = y + "Five Thousand";
		decimal -= 5000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 7000)
	{
		y = y + "Six Thousand";
		decimal -= 6000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 8000)
	{
		y = y + "Seven Thousand";
		decimal -= 7000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 9000)
	{
		y = y + "Eight Thousand";
		decimal -= 8000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 10000)
	{
		y = y + "Nine Thousand";
		decimal -= 9000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 11000)
	{
		y = y + "Ten Thousand";
		decimal -= 10000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 12000)
	{
		y = y + "Eleven Thousand";
		decimal -= 11000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 13000)
	{
		y = y + "Twelve Thousand";
		decimal -= 12000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 14000)
	{
		y = y + "Thirteen Thousand";
		decimal -= 13000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 15000)
	{
		y = y + "Fourteen Thousand";
		decimal -= 14000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 16000)
	{
		y = y + "Fifteen Thousand";
		decimal -= 15000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 17000)
	{
		y = y + "Sixteen Thousand";
		decimal -= 16000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 18000)
	{
		y = y + "Seventeen Thousand";
		decimal -= 17000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 19000)
	{
		y = y + "Eighteen Thousand";
		decimal -= 18000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 200000)
	{
		y = y + "Nineteen Thousand";
		decimal -= 19000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	return;
}

void convert::hundredThousand()
{
	if(decimal < 30000)
	{
		decimal -= 20000;
		y = y + "Twenty ";
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";		
	}
	else if(decimal < 40000)
	{
		y = y + "Thirty ";
		decimal -= 30000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
	}
	else if(decimal < 50000)
	{
		y = y + "Fourty ";
		decimal -= 40000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
	}
	else if(decimal < 60000)
	{
		y = y + "Fifty ";
		decimal -= 50000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
	}
	else if(decimal < 70000)
	{
		y = y + "Sixty ";
		decimal -= 60000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
	}
	else if(decimal < 80000)
	{
		y = y + "Seventy ";
		decimal -= 70000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
	}
	else if(decimal < 90000)
	{
		y = y + "Eighty ";
		decimal -= 80000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
	}
	else if(decimal < 100000)
	{
		y = y + "Ninety ";
		decimal -= 90000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
	}
	return;
}

void convert::million()
{
	if(decimal < 200000)
	{
		y = y + "One Hundred ";
		decimal -= 100000;

		if(decimal == 0){ y = y + "Thousand"; return;} 
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
		else if(decimal < 100000) y = y + "and ";
	}
	else if(decimal < 300000)
	{
		y = y + "Two Hundred ";
		decimal -= 200000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
		else if(decimal < 100000) y = y + "and ";
	}
	else if(decimal < 400000)
	{
		y = y + "Three Hundred ";
		decimal -= 300000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
		else if(decimal < 100000) y = y + "and ";
	}
	else if(decimal < 500000)
	{
		y = y + "Four Hundred ";
		decimal -= 400000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
		else if(decimal < 100000) y = y + "and ";
	}
	else if(decimal < 600000)
	{
		y = y + "Five Hundred ";
		decimal -= 500000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
		else if(decimal < 100000) y = y + "and ";
	}
	else if(decimal < 700000)
	{
		y = y + "Six Hundred ";
		decimal -= 600000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
		else if(decimal < 100000) y = y + "and ";
	}
	else if(decimal < 800000)
	{
		y = y + "Seven Hundred ";
		decimal -= 700000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
		else if(decimal < 100000) y = y + "and ";
	}
	else if(decimal < 900000)
	{
		y = y + "Eight Hundred ";
		decimal -= 800000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
		else if(decimal < 100000) y = y + "and ";
	}
	else if(decimal < 1000000)
	{
		y = y + "Nine Hundred ";
		decimal -= 900000;
		
		if(decimal == 0){ y = y + "Thousand"; return;}
		else if(decimal < 100) y = y + "Thousand and ";
		else if(decimal < 1000) y = y + "Thousand ";
		else if(decimal < 100000) y = y + "and ";
	}
	return;
}

void convert::tenMillion()
{
	if(decimal < 2000000)
	{
		y = y + "One Million";
		decimal -= 1000000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
		
	}
	else if(decimal < 3000000)
	{
		y = y + "Two Million";
		decimal -= 2000000;

		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
		
	}
	else if(decimal < 4000000)
	{
		y = y + "Three Million";
		decimal -= 3000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 5000000)
	{
		y = y + "Four Million";
		decimal -= 4000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 6000000)
	{
		y = y + "Five Million";
		decimal -= 5000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 7000000)
	{
		y = y + "Six Million";
		decimal -= 6000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 8000000)
	{
		y = y + "Seven Million";
		decimal -= 7000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 9000000)
	{
		y = y + "Eight Million";
		decimal -= 8000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 10000000)
	{
		y = y + "Nine Million";
		decimal -= 9000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 11000000)
	{
		y = y + "Ten Million";
		decimal -= 10000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 12000000)
	{
		y = y + "Eleven Million";
		decimal -= 11000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 13000000)
	{
		y = y + "Twelve Million";
		decimal -= 12000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 14000000)
	{
		y = y + "Thirteen Million";
		decimal -= 13000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 15000000)
	{
		y = y + "Fourteen Million";
		decimal -= 14000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 16000000)
	{
		y = y + "Fifteen Million";
		decimal -= 15000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 17000000)
	{
		y = y + "Sixteen Million";
		decimal -= 16000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 18000000)
	{
		y = y + "Seventeen Million";
		decimal -= 17000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 19000000)
	{
		y = y + "Eighteen Million";
		decimal -= 18000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	else if(decimal < 20000000)
	{
		y = y + "Nineteen Million";
		decimal -= 19000000;
		
		if(decimal == 0) return;
		else if(decimal < 100) y = y + " and ";
		else y = y + " ";
	}
	return;
}

void convert::hundredMillion()
{
	if(decimal < 30000000)
	{
		y = y + "Twenty";
		decimal -= 20000000;

		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " ";
	}
	else if(decimal < 40000000)
	{
		y = y + "Thirty";
		decimal -= 30000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " ";
	}
	else if(decimal < 50000000)
	{
		y = y + "Fourty";
		decimal -= 40000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " ";
	}
	else if(decimal < 60000000)
	{
		y = y + "Fifty";
		decimal -= 50000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " ";
	}
	else if(decimal < 70000000)
	{
		y = y + "Sixty";
		decimal -= 60000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " ";
	}
	else if(decimal < 80000000)
	{
		y = y + "Seventy";
		decimal -= 70000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " ";
	}
	else if(decimal < 90000000)
	{
		y = y + "Eighty";
		decimal -= 80000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " ";
	}
	else if(decimal < 100000000)
	{
		y = y + "Ninety";
		decimal -= 90000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " ";
	}
	return;
}

void convert::billion()
{
	if(decimal < 200000000)
	{
		y = y + "One Hundred";
		decimal -= 100000000;

		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " and ";
	}
	else if(decimal < 300000000)
	{
		y = y + "Two Hundred";
		decimal -= 200000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " and ";
	}
	else if(decimal < 400000000)
	{
		y = y + "Three Hundred";
		decimal -= 300000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " and ";
	}
	else if(decimal < 500000000)
	{
		y = y + "Four Hundred";
		decimal -= 400000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " and ";
	}
	else if(decimal < 600000000)
	{
		y = y + "Five Hundred";
		decimal -= 500000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " and ";
	}
	else if(decimal < 700000000)
	{
		y = y + "Six Hundred";
		decimal -= 600000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " and ";
	}
	else if(decimal < 800000000)
	{
		y = y + "Seven Hundred";
		decimal -= 700000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " and ";
	}
	else if(decimal < 900000000)
	{
		y = y + "Eight Hundred";
		decimal -= 800000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " and ";
	}
	else if(decimal < 1000000000)
	{
		y = y + "Nine Hundred";
		decimal -= 900000000;
		
		if(decimal == 0){ y = y + " Million"; return;}
		else if(decimal < 100) y = y + " Million and ";
		else if(decimal < 1000000) y = y + " Million ";
		else y = y + " and ";
	}
	return;
}

void convert::tenBillion()
{
	y = y + "One Billion";
	decimal -= 1000000000;

	if(decimal == 0) return;
	else if(decimal < 100) y = y + " and ";
	else y = y + " ";

	return;
}
