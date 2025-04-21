#include <string>

class Clue{
		std::string hint;
		bool collected;
		int x, y;
		public:
		Clue(int k, int g);	
		void found();
		bool isFound();
		bool check(int k, int g);
};

