/**
 * Conway's Game if Life
 */

// birth
// live
// depopulation
// congestion


#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

#define GRID (25)
#define ROW (8)
#define COLUMN (8)

using namespace std;


class Game{
	public:
		Game():all_score(0){ cout << "Create New Game" << endl; }
		void initialise();
		void show();
		void run();

	private:
		typedef struct{
			int score;
			int state;
			int generation;
		} cell_t;

		cell_t stage[COLUMN][ROW];
		int all_score;

		void setZero();
		void setPos();
		void calcScore();
		void updateState();

};


void Game::setZero(){
	for(int i=0;i<COLUMN;i++){
		for(int j=0;j<ROW;j++){
			stage[i][j].score = 0;
			stage[i][j].state = 0;
			stage[i][j].generation = 0;
		}
	}
}

void Game::setPos(){
#if 0
int pos[COLUMN][ROW] = {
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0}};
#endif

#if 1
int pos[COLUMN][ROW] = {
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 1, 0, 0, 1, 0, 0},
						{0, 1, 0, 1, 1, 0, 1, 0},
						{0, 0, 1, 0, 0, 1, 0, 0},
						{0, 0, 1, 0, 0, 1, 0, 0},
						{0, 1, 0, 1, 1, 0, 1, 0},
						{0, 0, 1, 0, 0, 1, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0}};
#endif
#if 0
int pos[COLUMN][ROW] = {
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}};
#endif
	for(int i=0;i<COLUMN;i++){
		for(int j=0;j<ROW;j++){
			stage[i][j].state = pos[i][j];
		}
	}

}

void Game::calcScore(){
	int
		r_max = 0, r_min = 0,
		c_max = 0, c_min = 0;

	all_score = 0;

	for(int col=0;col<COLUMN;col++){
		for(int row=0;row<ROW;row++){
			if(row == 0){
				r_max = row+1;
				r_min = row;
			}else if(row == ROW-1){
				r_max = row;
				r_min = row-1;
			}else{
				r_max = row+1;
				r_min = row-1;
			}

			if(col == 0){
				c_max = col+1;
				c_min = col;
			}else if(col == COLUMN-1){
				c_max = col;
				c_min = col-1;
			}else{
				c_max = col+1;
				c_min = col-1;
			}

			for(int i=c_min;i<=c_max;i++){
				for(int j=r_min;j<=r_max;j++){
					if(i == col && j == row){}
					else
						if(stage[i][j].state == 1) stage[col][row].score++;
				}
			}

			all_score += stage[col][row].score;
		}
	}

}

void Game::updateState(){
	for(int i=0;i<COLUMN;i++){
		for(int j=0;j<ROW;j++){
			if(stage[i][j].state == 0){
				if(stage[i][j].score == 3) stage[i][j].state = 1;
			}else if(stage[i][j].state == 1){
				if(stage[i][j].score == 2 || stage[i][j].score == 3) stage[i][j].state = 1;
				else if(stage[i][j].score <= 1) stage[i][j].state = 0;
				else if(stage[i][j].score >= 4) stage[i][j].state = 0;
			}

			stage[i][j].score = 0;
		}
	}
}

void Game::initialise(){
	setZero();
	setPos();
	all_score = 1;
}

void Game::show(){
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::system("clear");
	for(int i=0;i<COLUMN;i++){
		for(int j=0;j<ROW;j++){
//			cout << stage[i][j].state;
			if(stage[i][j].state) cout << "@";
			else cout << "#";
		}
		cout << endl;
	}
}

void Game::run(){
	cout << "--- setup ---" << endl;
	initialise();
	show();

	for(int i=0;i<60;i++){
		if(all_score == 0) break;
		cout << "--- " << i+1 << " ---" << endl;
		calcScore();
		updateState();
		show();
	}

}


int main(){

	Game g;
	g.run();

return 0;
}
