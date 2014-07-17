#ifndef __PLAYEREXCEPTION__
#define __PLAYEREXCEPTION__

#include <exception>
#include <map>
using namespace std;

namespace server_model_exp{
	
	class PlayerExp : public exception{
		public:
			~PlayerExp(void);
			PlayerExp(int error);
			const char* what() throw(); 
		private:
			int idError;
			map<int, string> mError;
	};
}

#endif /*__PLAYEREXCEPTION__*/
