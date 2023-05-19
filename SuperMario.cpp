#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include <time.h>
// #include "Cell.hpp"
// #include "Champion.hpp"
//#include "NEWMAP.h"

using namespace std;


class Cell
{
private:
	char CellType;
	int x;
	int y;
	char originalCellType;

public:
	Cell()
	{
		this->CellType = '.';
		this->x = 0;
		this->y = 0;
	}
	Cell(char CellType, int x, int y)
	{
		this->CellType = CellType;
		this->x = x;
		this->y = y;
	}
	void setCellType(char x)
	{
		this->CellType = x;
	}
	char getCellType()
	{
		return this->CellType;
	}
	void setOriginalCellType(char x){
        this->originalCellType=x;
	}
	char getOriginalCellType(){
        return this->originalCellType;
	}
};



class Cham : public Cell
{
private:
	int health;
	int x; // which x and y values will be removed the one fomr the Cell or the one from the chamption
	int y;
	char Symbol = (char)234;
	int gems;
	char CellType;
	int x1; // from the cell
	int y2; // from the cell

public:
	Cham() : Cell('C', 0, 0)
	{
		cout << "Constructor champion() is called" << endl;
		this->x = 0;
		this->y = 0;
		this->health = 100;
		this->gems = 0;
		this->setCellType('C');

	}

	// either this or that msh 3aref
	 // but with this method will we have to remove the fucking shit also
	virtual void useAbility(char x ,Cell*** cell)
	{
		cout << "Ability X is called " << endl;
	}
	void setLocationX(int x)
	{
		this->x = x;
	}
	void setLocationY(int y)
	{
		this->y = y;
	}
	int getLocationX()
	{
		return x;
	}
	int getLocationY()
	{
		return y;
	}
	int getGems()
	{
		return gems;
	}
	void setGems(int x)
	{
		gems = x;
	}
	char getSymbol()
	{
		return Symbol;
	}
	void setHealth(int h)
	{
		health = h;
	}
	int getHealth()
	{
		return health;
	}

	void print_champ_info()
	{
		// put here the ability counter inside the champion locations put inside the main method ya amara
		cout << "The champion score: location " << x << ", " << y << "  health " << health << "/100 "<<  endl;// dp it later
	}
	virtual ~Cham() {}
};


class Obstacle : public Cell
{
private:
	int dmg_amount;

public:

	Obstacle() : Cell()
	{

		this->dmg_amount = (1 + rand() % 5);
	}
	virtual void execute(Cham c)
	{
        cout<<"Obstacle Execute called"<<endl;
	}
	friend class Thief;
	friend class Bomb;
};


class Gem : public Cell
{
private:
	int totalPoints;

public:
	Gem() : Cell()
	{
        this->setOriginalCellType('g');
		this->totalPoints = (rand() % 10) + 5;
	}
	virtual void execute(Cham *c) {}
	friend class Coin;
	friend class Potion;
};

class Coin : public Gem
{
public:
	Coin() : Gem()
	{
		this->setCellType('C');
	}
	void execute(Cham* c)
	{
	    cout<<"Coin Execute called"<<endl;
		c->setGems(c->getGems() + this->totalPoints);

		cout << "Coin executed with points = " << this->totalPoints << endl;
	}
};


class Potion : public Gem
{
public:
	Potion() : Gem()
	{
		this->setCellType('P');
	}
	void execute(Cham *c)//champ-poibter not object
	{
	    cout<<"Potion Execute called"<<endl;
		if ((c->getHealth()) < 100)
		{
		    cout<<"points being applied potion"<<endl;
			c->setHealth(c->getHealth() + this->totalPoints);
			if (c->getHealth() >= 100)
				c->setHealth(100);
		}
		cout << "Potion executed with points = " << this->totalPoints << endl;
	}
};

class Thief : public Obstacle
{
public:
	Thief() : Obstacle()
	{
		this->setCellType('T');
	}

	void execute(Cham* c)
	{
	    cout<<"Thief Execute called"<<endl;
		if ((c->getGems() - this->dmg_amount) < 0)
		{
		    cout<<"damage amount being applied thief"<<endl;
			c->setGems(0);
		}
		else{
            cout<<"damage amount being applied thief"<<endl;
			c->setGems(c->getGems() - this->dmg_amount);
			}
			cout << "Thief executed with dmg = " << this->dmg_amount << endl;
	}
};

class Bomb : public Obstacle
{
public:
	Bomb() : Obstacle()
	{
		this->setCellType('B');
	}
	void execute(Cham* c)
	{
		if (((c->getHealth()) - this->dmg_amount) < 0)
		{
		    cout<<"damage amount being applied Bomb"<<endl;
			c->setHealth(0);
		}
		else{
			c->setHealth(c->getHealth() - this->dmg_amount);
			cout<<"damage amount being applied bomb"<<endl;
		}
		cout << "Bomb executed with dmg = " + this->dmg_amount << endl;
	}
};

class Luigi : public Cham
{
private:
public:
	Luigi() : Cham() {
		this->setCellType('L');
		this->setOriginalCellType('L');
	}
	void useAbility(char n,Cell *** cell){
		if (n == '8' || n == 'w')
		{
			for (int i = this->getLocationY(); i < 10; i++)
			{
				if (cell[i][this->getLocationX()]->getCellType() == 'B' ||cell[i][this->getLocationX()]->getCellType() == 'T')
				{
					cell[i][this->getLocationX()]->setCellType('.');
				}
			}
		}
		else if (n == '6' || n == 'd')
		{
			for (int i = this->getLocationX(); i < 10; i++)
			{
				if (cell[this->getLocationY()][i]->getCellType() == 'B' || cell[this->getLocationY()][i]->getCellType() == 'T')
					cell[this->getLocationY()][i]->setCellType('.');
			}
		}
		else if (n == '5' || n == 's')
		{
			for (int i = this->getLocationY(); i >= 0; i--)
			{
				if (cell[i][this->getLocationX()]->getCellType() == 'B' || cell[i][this->getLocationX()]->getCellType() == 'T')
				{
					cell[i][this->getLocationX()]->setCellType('.');
				}
			}
		}
		else if (n == '4' || n == 'a')
		{
			for (int i = this->getLocationY(); i >= 0; i--)
			{
				if (cell[this->getLocationY()][i]->getCellType() == 'B' || cell[this->getLocationY()][i]->getCellType() == 'T')
					cell[this->getLocationY()][i]->setCellType('.');
			}
		}
	}
};
class Mario : public Cham
{

public:
	Mario() : Cham()
	{
	    this->setOriginalCellType('M');
		this->setCellType('M');
	}
	void useAbility(char x,Cell*** cell)
	{
		cout<<"Ability Mario is called "<<endl;
					int targetX = this->getLocationX();
		int targetY = this->getLocationY();
		if (x == '8' || x == 'w')
			targetY += 2;
		else if (x == '6' || x == 'd')
			targetX += 2;
		else if (x == '5' || x == 's')
			targetY -= 2;
		else if (x == '4' || x == 'a')
			targetX -= 2;
		else
			cout << "enter a valid direction" << endl;
		{
		}
		if (targetX < 0 || targetX > 9 || targetY < 0 || targetY > 9)
		{
			cout << "Target bara" << endl;
		}
		else
		{
			if (cell[targetY][targetX]->getCellType() == 'B')
			{
				((Bomb *)(cell[targetY][targetX]))->execute(this); // not quite sure about this one
			}
			else if (cell[targetY][targetX]->getCellType() == 'T')
			{
				((Thief *)(cell[targetY][targetX]))->execute(this);
			}
			else if (cell[targetY][targetX]->getCellType() == 'C')
			{
				((Coin *)(cell[targetY][targetX]))->execute(this);
			}
			else if (cell[targetY][targetX]->getCellType() == 'P')
			{
				((Potion *)(cell[targetY][targetX]))->execute(this);
			}
			cell[targetY][targetX]->setCellType(this->getCellType());
			cell[this->getLocationY()][this->getLocationX()]->setCellType('.');
			this->setLocationX(targetX);
			this->setLocationY(targetY);
		}
	}


};


class Map
{
private:
	Cell ***base;

public:
	int gems_c = 0;
	Cham* champ;

	Map(Cham* c)
	{
		cout << "Constructor map() is called" << endl;
        base = new Cell**[10];

		for (int i = 0; i <10 ; i++)
		{
		    base [i] = new Cell*[10];
			for (int j = 0; j < 10; j++)
			{
				base[i][j] = new Cell();
			}
		}

		this->champ = c;
	}

	~Map()
	{
		free(base);
		delete champ;
	}


	char getGems()
	{
		return gems_c;
	}

	void print_map()
	{

		cout << "Print map() us called" << endl;
		for (int i = 9; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++)
			{

                        cout << base[i][j]->getCellType() << " ";
			}
			cout << endl;
		}
	}

	void randomize_map()
	{
		gems_c = 0;
		 for (int i = 9; i >= 0; i--)
		 {
		 	for (int j = 0; j < 10; j++)
		 	{

			base[i][j]->setCellType('.');
            }
		}
		int r1, r2;
		int thief_c = 0;
		int bomb_c = 0;
		int Coins_counter = 0;
		int mapss = 0;

		while (gems_c != 20)
		{
			r1 = (rand() % 10) + 0;
			r2 = (rand() % 10) + 0;
			if (base[r1][r2]->getCellType() == '.')
			{
				base[r1][r2] = new Potion();
				gems_c++;
			}
		}
		while (Coins_counter != 20)
		{

			r1 = (rand() % 10) + 0;
			r2 = (rand() % 10) + 0;
			if (base[r1][r2]->getCellType() == '.')
			{
				base[r1][r2] = new Coin();
				Coins_counter++;
			}
		}
		while (thief_c != 10)
		{ // put theif
			r1 = (rand() % 10) + 0;
			r2 = (rand() % 10) + 0;
			if (base[r1][r2]->getCellType() == '.')
			{
				base[r1][r2] = new Thief ();
				thief_c++;
			}
		}
		while (bomb_c != 10)
		{ // put bombs
			r1 = (rand() % 10) + 0;
			r2 = (rand() % 10) + 0;
			if (base[r1][r2]->getCellType() == '.')
			{
				base[r1][r2] = new Bomb();
				bomb_c++;
			}
		}

		base[0][0]->setCellType(champ->getCellType());
	}
	void moveChamp(char n)
	{
		int targetX = champ->getLocationX();
		int targetY = champ->getLocationY();

		if (n == '8' || n == 'w')
		{
			targetY += 1;
		}
		else if (n == '6' || n == 'd')
		{
			targetX += 1;
		}
		else if (n == '5' || n == 's')
		{
			targetY -= 1;
		}
		else if (n == '4' || n == 'a')
		{
			targetX -= 1;
		}
		else
			cout << "enter a valid direction" << endl;

		if (targetX < 0 || targetX > 9 || targetY < 0 || targetY > 9)
		{

			cout << "Target bara" << endl;
		}
		else
		{
			if (base[targetY][targetX]->getCellType() == 'B')
			{
			    cout<<"ana hena Bomb"<<endl;
				((Bomb*)(base[targetY][targetX]))->execute(champ); // not quite sure about this one
			}
			else if (base[targetY][targetX]->getCellType() == 'T')
			{
			    cout<<"ana hena theif"<<endl;
				((Thief*) (base[targetY][targetX]))->execute(champ);
			}
			else if (base[targetY][targetX]->getCellType() == 'C')
			{
			    cout<<"ana hena coin"<<endl;
				((Coin*)(base[targetY][targetX]))->execute(champ);
			}
			else if (base[targetY][targetX]->getCellType() == 'P')
			{
			    cout<<"ana hena potion"<<endl;
				((Potion*)(base[targetY][targetX]))->execute(champ);
			}

			base[targetY][targetX] = champ;
			cout<<"champ successfully moved"<<endl;
			base[champ->getLocationY()][champ->getLocationX()] =  new Cell('.',champ->getLocationY(),champ->getLocationX());
			champ->setLocationX(targetX);
			champ->setLocationY(targetY);
		}
	}

		Cell *** getMap(){
			return base;
		}
// void  MarioAbility(char x)
// {
// 	int targetX = champ->getLocationX();
// 	int targetY = champ->getLocationY();
// 	if (x == '8' || x == 'w')
// 		targetY += 2;
// 	else if (x == '6' || x == 'd')
// 		targetX += 2;
// 	else if (x == '5' || x == 's')
// 		targetY -= 2;
// 	else if (x == '4' || x == 'a')
// 		targetX -= 2;
// 	else
// 		cout << "enter a valid direction" << endl;
// 	{
// 	}
// 	if (targetX < 0 || targetX > 9 || targetY < 0 || targetY > 9)
// 	{
// 		cout << "Target bara" << endl;
// 	}
// 	else
// 	{
// 		if (base[targetY][targetX]->getCellType() == 'B')
// 			{
// 				((Obstacle*) (base[targetY][targetX]))->execute(*champ); // not quite sure about this one
// 			}
// 			else if (base[targetY][targetX]->getCellType() == 'T')
// 			{
// 				((Thief*)(base[targetY][targetX]))->execute(*champ);
// 			}
// 			else if (base[targetY][targetX]->getCellType() == 'C')
// 			{
// 				((Coin*)(base[targetY][targetX]))->execute(*champ);
// 			}
// 			else if (base[targetY][targetX]->getCellType() == 'P')
// 			{
// 				((Potion*)(base[targetY][targetX]))->execute(*champ);
// 			}
// 			base[targetY][targetX]->setCellType(champ->getCellType()) ;
// 			base[champ->getLocationY()][champ->getLocationX()]->setCellType('.');
// 			champ->setLocationX(targetX);
// 			champ->setLocationY(targetY);

// 	}
// }
// void LuigiAbility(char n)
// {
// 	if (n == '8' || n == 'w')
// 	{
// 		for (int i = champ->getLocationY(); i < 10; i++)
// 		{
// 			if (base[i][champ->getLocationX()]->getCellType() == 'B' || base[i][champ->getLocationX()]->getCellType() == 'T')
// 			{
// 				base[i][champ->getLocationX()]->setCellType('.');
// 			}
// 		}
// 	}
// 	else if (n == '6' || n == 'd')
// 	{
// 		for (int i = champ->getLocationX(); i < 10; i++)
// 		{
// 			if (base[champ->getLocationY()][i]->getCellType() == 'B' || base[champ->getLocationY()][i]->getCellType() == 'T')
// 				base[champ->getLocationY()][i]->setCellType('.');
// 		}
// 	}
// 	else if (n == '5' || n == 's')
// 	{
// 		for (int i = champ->getLocationY(); i >= 0; i--)
// 		{
// 			if (base[i][champ->getLocationX()]->getCellType() == 'B' || base[i][champ->getLocationX()]->getCellType() == 'T')
// 			{
// 				base[i][champ->getLocationX()]->setCellType('.');
// 			}
// 		}
// 	}
// 	else if (n == '4' || n == 'a')
// 	{
// 		for (int i = champ->getLocationY(); i >= 0; i--)
// 		{
// 			if (base[champ->getLocationY()][i]->getCellType() == 'B' || base[champ->getLocationY()][i]->getCellType() == 'T')
// 				base[champ->getLocationY()][i]->setCellType('.');
// 		}
// 	}
// }

void infolol()
{

	champ->print_champ_info();
	cout << " gem score " << champ->getGems() << "/" << gems_c  << endl;
}
bool isOver(){
    for(int i =0;i<10;i++){
        for(int j=0;j<10;j++){
            if(base[i][j]->getCellType()=='C')
                return false;
        }
    }
    return true;
}
//friend class Game;u
};









int main()
{
	cout << "Please choose your player: " << endl;
	cout<<"1 for Luigi"<< endl;
	cout << "2 for Mario" << endl;
	char Player;
	Player=(char)getch();
	Map *p;
	if (Player == '1')
	{ // luigi

		Luigi *l = new Luigi();
		p = new Map(l);
	}
	else if (Player == '2')
	{ // mario

		Mario *m = new Mario();
		p = new Map(m);
	}

	char num;
	// add the champoiobn ability counter next to the champinfo here (put om il method hona ya 7mar)
	do
	{
	    system("CLS");
	    cout<<"want to randomize before calling randomize"<<endl;
		p->randomize_map();
		cout<<"want to randomize"<<endl;
		p->print_map();
		cout << "enter 2 to randomize  map, enter 1 to proceed: ";
		num = (char)getch();
	} while (num == '2');
	char x;
    int ability_counter=2;
	if (num == '1')
	{
		while (p->champ->getHealth() > 0 && p->isOver()==false)
		{
			system("CLS");
			p->print_map();
			p->infolol();
			cout<<"Ability  counter: "<< ability_counter<<endl;
			cout << "to move press: Use the WASD key or 8 to move up, 5 to move down, 4 to move left, 6 move right";
			x = (char)getch();
			if (x == 'x')
			{   if(ability_counter!=0){
				cout << "Enter a direction for ur specific ability" << endl;
				x=(char)getch();
				p->champ->useAbility(x,p->getMap());
				ability_counter--;
				}  else
                        cout<<"You have already used all ur abilities"<<endl;// help
			}
			p->moveChamp(x);
		}
	}
	else
		cout << "Please enter either 1 or 2" << endl;
	cout << endl;
	cout << endl;

	cout << endl;


	if (p->isOver()== true)
	{
		system("CLS");
		p->print_map();
		cout << "GG, you won" << endl;
	}
	else if(p->champ->getHealth() ==0)
	{
		system("CLS");
		p->print_map();
		cout << "U Lost" << endl;
	}
	delete p;


}
