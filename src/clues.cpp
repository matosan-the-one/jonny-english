#include <iostream>
#include <string>
#include <cmath>


class Clue{
		std::string hint;
		bool collected, truth;
		int x, y;
		public:
		Clue(int k, int g) {
				collected=false;
				std::cout << "vpis hint\n";
				std::getline(std::cin, hint);
				std::cout << "answer 1/0";
				std::cin >> truth;
				x=k;
				y=g;
		}
		void found(){
				collected=true;
		}
		bool isFound(){
            // get question
            // if (ans==true)
				return collected;
		}
		std::string check(int k, int g){
				std::string not_f="0";
				if(250<sqrt((k-x)*(k-x)+(g-y)*(g-y))) {
						(*this).found();
						return hint;
				}
				return not_f;
		}

};

