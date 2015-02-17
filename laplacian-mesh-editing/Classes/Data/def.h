#pragma once
#include <vector>
#include <gl/glut.h>
#define TRIANGLE 't'
#define POLYGON 'p'
#define ISEQUAL(a,b) (strcmp(a,b)==0)
#define CAI_SYNTHESIZE(varType, var, Var)\
	public: varType var; \
	public: const varType get##Var(){return var;} \
	void set##Var(varType v){var = v;}
using namespace std;



