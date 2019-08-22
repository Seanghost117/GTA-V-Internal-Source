//this is our features namespace call it by Features::(Feature name)
namespace Features {
	void UpdateLoop();
  	int main();
	extern bool userHotkey;
  //example
	//self
 	extern bool sixstars_bool;
	void sixstars(bool toggle);
	//never wanted
	extern bool Neverwanted;
	void neverwanted(bool toggle);
	//editing the wanted level
	extern int PlyrWntLevel;
	void ChangeWanted(int level);
	int GetWanted(Player player);
	//super jumping
	extern bool sjump_bool;
	void sjump(bool toggle);
  
}
