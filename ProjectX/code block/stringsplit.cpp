std::string temp = "30,40";
int index = temp.find_first_of(",");

std::string front = temp.substr(0, index);
std::string behand = temp.substr(index + 1, temp.length());
	
int f,b;
std::stringstream ff(front);
ff>>f;
std::stringstream bb(behand);
bb>>b;

log("f===>%d", f);
log("b===>%d", b);