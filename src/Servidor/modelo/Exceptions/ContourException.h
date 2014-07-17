
#ifndef __CONTOUREXCEPTION__
#define __CONTOUREXCEPTION__

#include <exception>
#include <map>
using namespace std;

namespace server_model_exp{
	
	class ContourExp : public exception{
		public:
			~ContourExp(void);
			ContourExp(int error);
			const char* what() throw(); 
		private:
			int idError;
			map<int, string> mError;
	};
}

#endif /*__CONTOUREXCEPTION__*/
