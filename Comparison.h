#ifndef COMPARISON_H
#define COMPARISON_H
#include <iostream>
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include <fstream>

typedef struct {
	int attNo;
	Type attType;
} myAtt;

typedef struct
{
	int attNo;
	Type attType;
} attNoAndType;


// This stores an individual comparison that is part of a CNF
class Comparison {

	friend class ComparisonEngine;
	friend class CNF;

	Target operand1;
	int whichAtt1;
	Target operand2;
	int whichAtt2;

	Type attType;

	CompOperator op;

public:

	Comparison();

	//copy constructor
	Comparison(const Comparison &copyMe);

	// print to the screen
	void Print ();
};


class Schema;
class Record;
class OrderMaker;

// This structure stores a CNF expression that is to be evaluated
// during query execution

class CNF {

	friend class ComparisonEngine;

	Comparison orList[MAX_ANDS][MAX_ORS];
	
	int orLens[MAX_ANDS];
	int numAnds;

public:

	// this returns an instance of the OrderMaker class that
	// allows the CNF to be implemented using a sort-based
	// algorithm such as a sort-merge join.  Returns a 0 if and
	// only if it is impossible to determine an acceptable ordering
	// for the given comparison
	int GetSortOrders (OrderMaker &left, OrderMaker &right);

	// print the comparison structure to the screen
	void Print ();

        // this takes a parse tree for a CNF and converts it into a 2-D
        // matrix storing the same CNF expression.  This function is applicable
        // specifically to the case where there are two relations involved
        void GrowFromParseTree (struct AndList *parseTree, Schema *leftSchema, 
		Schema *rightSchema, Record &literal);

        // version of the same function, except that it is used in the case of
        // a relational selection over a single relation so only one schema is used
        void GrowFromParseTree (struct AndList *parseTree, Schema *mySchema, 
		Record &literal);

		int queryOrderMaker(const OrderMaker & actual, OrderMaker & binSearch_order, OrderMaker & literal_order);

};



// This structure encapsulates a sort order for records
class OrderMaker {

	friend class ComparisonEngine;
	friend class CNF;

	int numAtts;

	int whichAtts[MAX_ANDS];
	Type whichTypes[MAX_ANDS];

public:

	void queryOrderMaker(OrderMaker &sortOrder, CNF &query, OrderMaker &queryorder, OrderMaker & cnforder);

	int findAttrIn(int att, CNF &query);

	void initOrderMaker(int numAtts, attNoAndType * myAtts);

	// creates an empty OrdermMaker
	OrderMaker();

	// create an OrderMaker that can be used to sort records
	// based upon ALL of their attributes
	OrderMaker(Schema *schema);

	// print to the screen
	void Print();
	void FilePrint(std::ofstream &fileout);
	void makeordermaker(std::ifstream & ifs);
	void GetAttsList(int AttsList[]);
	int Add(int attIndex, Type attType);
	int ADDSortingAtt(SortedAttList *satts, Schema *s);
	//int ADDSortingAtt(NameList * satts, Schema * s);
	//int ADDSortingAtt(NameList satts, Schema s);
	int GetNumAtts()
	{
		return numAtts;
	}
};


#endif
