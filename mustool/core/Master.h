#ifndef REMUS_MASTER_H
#define REMUS_MASTER_H

#include "mustool/satSolvers/MSHandle.h"
#include "Explorer.h"
#ifndef NOSMT
	#include "mustool/satSolvers/Z3Handle.h"
#endif
#ifndef NOLTL 
	#include "mustool/satSolvers/SpotHandle.h"
	#include "mustool/satSolvers/NuxmvHandle.h"
#endif
#include "types_h.h"
#include <set>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <ctime>
#include <chrono>	
#include <unordered_map>

using namespace std;

class Master{
public:
	int dimension; //the number of constraints
	string algorithm; //MUS enumeration algorithm to be used
	int isValidExecutions;
	bool verbose; //TODO: make it int based 
	string output_file;
	bool validate_mus_c;
	float mus_approx;
	bool get_implies;
	bool criticals_rotation;
	string domain;
	bool useMixedHeuristic;
	int hash;
	int unex_unsat;
	int unex_sat;
	chrono::high_resolution_clock::time_point initial_time;
	vector<MUS> muses;
	Explorer* explorer;
	SatSolver* satSolver; 
	string sat_solver;

	Master(string filename, string alg);
	Master(int numVars, const vector<vector<int> > & clauses, const string& alg);
	~Master();
	bool is_valid(Formula &f, bool core = false, bool grow = false);
	void block_down(Formula f);
	void block_up(MUS& f);
	void mark_MUS(MUS& m, bool block = true);
	MUS& shrink_formula(Formula& f, Formula crits = Formula());
	Formula grow_formula(Formula& f);
	void write_mus_to_file(MUS& f);
	void validate_mus(Formula &f);
	void enumerate();
	void setMucCallback(const MucCallback::Ptr & mucCallback) { if (satSolver) satSolver->mucCallback = mucCallback; }
	
	//reMUS algorithm functions
	int depthMUS;
	float dim_reduction;
	int current_depth;
	void find_all_muses_duality_based_remus(Formula subset, Formula crits, int depth);
	void extend_mus(Formula &top, Formula &mus, int dMUS = 1);

	//TOME algorithm functions
	void find_all_muses_tome();
	pair<Formula, Formula> local_mus(Formula bot, Formula top, int diff);

	//MARCO algorithm functions
	void marco_base();
};
#endif
