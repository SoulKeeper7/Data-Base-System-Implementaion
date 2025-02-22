
#ifndef ParseFunc
#define ParseFunc

// these are the types of operands that can appear in a CNF expression
#define DOUBLE 1
#define INT 2
#define NAME 3
#define STRING 4
#define LESS_THAN 5
#define GREATER_THAN 6
#define EQUALS 7

// used in computational (funcional) expressions
struct FuncOperand {

	// this tells us the type of the operand: FLOAT, INT, STRING...
	int code;

	// this is the actual operand
	char *value;
};

struct FuncOperator {

	// this tells us which operator to use: '+', '-', ...
	int code;

	// these are the operators on the left and on the right
	struct FuncOperator *leftOperator;
	struct FuncOperand *leftOperand;
	struct FuncOperator *right;	

};

struct TableList {

	// this is the original table name
	char *tableName;

	// this is the value it is aliased to
	char *aliasAs;

	// and this the next alias
	struct TableList *next;
};

struct NameList {

	// this is the name
	char *name;

	// and this is the next name in the list
	struct NameList *next;
};

// used in boolean expressions... there's no reason to have both this
// and FuncOperand, but both are here for legacy reasons!!
struct Operand {

        // this tells us the type of the operand: FLOAT, INT, STRING...
        int code;

        // this is the actual operand
        char *value;
};

struct ComparisonOp {

        // this corresponds to one of the codes describing what type
        // of literal value we have in this nodes: LESS_THAN, EQUALS...
        int code;

        // these are the operands on the left and on the right
        struct Operand *left;
        struct Operand *right;
};

struct OrList {

        // this is the comparison to the left of the OR
        struct ComparisonOp *left;

        // this is the OrList to the right of the OR; again,
        // this might be NULL if the right is a simple comparison
        struct OrList *rightOr;
};

struct AndList {

        // this is the disjunction to the left of the AND
        struct OrList *left;

        // this is the AndList to the right of the AND
        // note that this can be NULL if the right is a disjunction
        struct AndList *rightAnd;

};

struct SchemaList {

	// this is the original attribute name
	char *attName;

	// this is the type
	char *type;

	// and this the next alias
	struct SchemaList *next;
};
struct SortedAttList
{
	char *name;
	struct SortedAttList *next;

};


struct CreateTableType {
	char* heapOrSorted; // "HEAP": create the database as a heap dbfile
						// "SORTED": create the database as a sorted dbfile
	struct SortedAttList *sortedAttList; // the set of attributes in CREATE TABLE that we are sorting on (if sorted file;
								 // if heap, this is NULL)
};



#endif
