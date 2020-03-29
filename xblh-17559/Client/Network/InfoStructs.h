#include "include.h"

using namespace std;

//Main clientinfo struct
struct clientInfo
{
	int			sock_id;
	char*		ip;
	int			user_id;
	bool		user_loggedIn;
};
typedef std::list<clientInfo*> client_list;

//Main admininfo struct
struct adminInfo
{
	int			sock_id;
	char*			ip;
	int			admin_id;
	bool		admin_loggedIn;
};
typedef std::list<adminInfo*> admin_list;

extern client_list		clientList;
extern admin_list		adminList;