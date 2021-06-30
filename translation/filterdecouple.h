//#define BOOST_SPIRIT_DEBUG
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include "custom_fold_directive.hpp"
//#include <regex>
//#include <sstream>
#include <stack>
#include <tuple>
//#include <bits/stdc++.h>
#include <map> 

namespace qi = boost::spirit::qi;
using namespace std;


// DEFINING TYPES
struct op_not {};
struct op_bound {};
struct op_or {};
struct op_and {};
struct op_xor {};
struct op_eq {};
struct op_ne {};
struct op_add {};
struct op_subtract {};
struct op_multiply {};
struct op_divide {};

struct op_gte {};
struct op_gt {};
struct op_lte {};
struct op_lt {};

set<string> set_bound_var;

namespace Expression{

typedef std::string var;
template <typename tag> struct binop;
template <typename tag> struct unop;
template <typename tag> struct bound;

typedef boost::variant<
    int,
    double,
    var,
    boost::recursive_wrapper<unop <op_not> >,
    boost::recursive_wrapper<binop<op_eq> >,
    boost::recursive_wrapper<binop<op_gte> >,
    boost::recursive_wrapper<binop<op_gt> >,    
    boost::recursive_wrapper<binop<op_lte> >,
    boost::recursive_wrapper<binop<op_lt> >,    
    boost::recursive_wrapper<binop<op_ne> >,
    boost::recursive_wrapper<binop<op_and> >,
    boost::recursive_wrapper<binop<op_xor> >,
    boost::recursive_wrapper<binop<op_or> >,
    boost::recursive_wrapper<binop<op_subtract> >,
    boost::recursive_wrapper<binop<op_add> >,
    boost::recursive_wrapper<binop<op_multiply> >,
    boost::recursive_wrapper<bound <op_bound> >,    
    boost::recursive_wrapper<binop<op_divide> >
> expressionContainer;

/*
template<typename T>
bool is_number(T x){
    std::string s;
    std::regex e ("^-?\\d*\\.?\\d+");
    std::stringstream ss; 
    ss << x;
    ss >>s;
    if (std::regex_match (s,e)) return true;
    else return false;}
*/

std::stack<std::string> filter_stack;
int int_tmp_key;

std::string str_tmp_1, str_tmp_2, str_tmp_3;
map<std::string, std::tuple< std::string, std::string, std::string >> tmp_map;
std::tuple< std::string, std::string, std::string > tmp_tuple;


template <typename tag> struct binop
{
    explicit binop(const expressionContainer& l
        , const expressionContainer& r)
        : oper1(l), oper2(r) { }
    expressionContainer oper1, oper2;

    friend std::ostream& operator<<(std::ostream& os, const binop& val)
    {
        //os << "(" << typeid(tag).name() << " " << val.oper1 << ", "<< val.oper2 << ")";
	  
        
        
        //boost::get<var>(val.oper1)
        
	

       // os << "(" << val.oper1 << " \'" << typeid(tag).name() << "\' " << val.oper2 << ")";
        
	
	std::string tmp_symbol="";
	
	
	
        os << "(" ;
        filter_stack.push("(");
        
        os << val.oper1;

	switch(val.oper1.which())
	{
		case 0:
			filter_stack.push(std::to_string(boost::get<int>(val.oper1)));
			break;
		case 1:
			filter_stack.push(std::to_string(boost::get<double>(val.oper1)));
			break;
		case 2:
			if (boost::get<var>(val.oper1).find('%') != std::string::npos)
				tmp_symbol = "%" + boost::get<var>(val.oper1);
			//if (boost::get<var>(val.oper1).find('?') != std::string::npos)
			//	tmp_symbol = "?" + boost::get<var>(val.oper1);	
			
			else if (boost::get<var>(val.oper1).find('>') != std::string::npos)
				tmp_symbol = "<http" + boost::get<var>(val.oper1);			
		
			else if (boost::get<var>(val.oper1).find('-') != std::string::npos || boost::get<var>(val.oper1).find(':') != std::string::npos)
				tmp_symbol =  boost::get<var>(val.oper1) ;			
			else if (boost::get<var>(val.oper1).find('\"') != std::string::npos)
				tmp_symbol = "\"" + boost::get<var>(val.oper1);			
			
			else
				tmp_symbol = "?" + boost::get<var>(val.oper1);			

			filter_stack.push(tmp_symbol);
			break;
	}
		
        
        os << "\'" << typeid(tag).name() << "\' ";
        filter_stack.push(typeid(tag).name());
        
        os << val.oper2 << "\n";

        	switch(val.oper2.which())
	{
		case 0:
			filter_stack.push(std::to_string(boost::get<int>(val.oper2)));
			break;
		case 1:
			filter_stack.push(std::to_string(boost::get<double>(val.oper2)));
			break;
		case 2:
			if (boost::get<var>(val.oper2).find('%') != std::string::npos)
				tmp_symbol = "%" + boost::get<var>(val.oper2);
			//if (boost::get<var>(val.oper2).find('?') != std::string::npos)
			//	tmp_symbol = "?" + boost::get<var>(val.oper2);

			else if (boost::get<var>(val.oper2).find('>') != std::string::npos)
				tmp_symbol = "<http" + boost::get<var>(val.oper2);			
						
			else if (boost::get<var>(val.oper2).find('-') != std::string::npos || boost::get<var>(val.oper2).find(':') != std::string::npos) 
				tmp_symbol =  boost::get<var>(val.oper2) ;			
			else if (boost::get<var>(val.oper2).find('\"') != std::string::npos)
				tmp_symbol = "\"" + boost::get<var>(val.oper2);
			else
				tmp_symbol = "?" + boost::get<var>(val.oper2);			
			
			filter_stack.push(tmp_symbol);
			break;
	}

        
         os << ")";
        filter_stack.push(")");
	//os << "-------------\n";
	
	
	
	
		filter_stack.pop(); // ')'
        	
		str_tmp_1 = filter_stack.top();
        	filter_stack.pop();
        	
		str_tmp_2 = filter_stack.top();
        	filter_stack.pop();
        	
		str_tmp_3 = filter_stack.top();
        	filter_stack.pop();

        	tmp_tuple = std::make_tuple(str_tmp_3, str_tmp_2, str_tmp_1);
        	

		filter_stack.pop(); // ')'
		
		if (int_tmp_key < 9) 
		tmp_map.emplace( ("key_0"+std::to_string(++int_tmp_key)) , tmp_tuple );
		else
		tmp_map.emplace( ("key_"+std::to_string(++int_tmp_key)) , tmp_tuple );

		if (int_tmp_key < 9) 
		filter_stack.push(("key_0"+std::to_string(int_tmp_key)));
		else
		filter_stack.push(("key_"+std::to_string(int_tmp_key)));		

	
        return os;
    }
};

template <typename tag> struct unop
{
    explicit unop(const expressionContainer& o) : oper1(o) { }
    expressionContainer oper1;

    friend std::ostream& operator<<(std::ostream& os, const unop& val)
    {
    
        os << "(" ;
        filter_stack.push("(");
        
        os << val.oper1 ;

        //set_bound_var.insert(("?" + boost::get<var>(val.oper1)));
        


        //filter_stack.push(std::to_string(val.oper1.which()));
        
        //cout << "\n\n TYPE:  " << std::to_string(val.oper1.which()) <<"\n";

        os << "\'" << typeid(tag).name() << "\' ";
        filter_stack.push(typeid(tag).name());
        
        
        os << ")";
        filter_stack.push(")");
	//os << "-------------\n";
			
		filter_stack.pop(); // ')'
        	
		str_tmp_1 = filter_stack.top();
        	filter_stack.pop();
        	
		str_tmp_2 = filter_stack.top();
        	filter_stack.pop();
        	
		str_tmp_3 = "";

        	tmp_tuple = std::make_tuple(str_tmp_2, str_tmp_1, str_tmp_3);
        	

		filter_stack.pop(); // ')'

		if (int_tmp_key < 9) 
		tmp_map.emplace( ("key_0"+std::to_string(++int_tmp_key)) , tmp_tuple );
		else
		tmp_map.emplace( ("key_"+std::to_string(++int_tmp_key)) , tmp_tuple );


		if (int_tmp_key < 9) 
		filter_stack.push(("key_0"+std::to_string(int_tmp_key)));
		else
		filter_stack.push(("key_"+std::to_string(int_tmp_key)));		


	
        return os;
    }
};


template <typename tag> struct bound
{
    explicit bound(const expressionContainer& o) : oper1(o) { }
    expressionContainer oper1;

    friend std::ostream& operator<<(std::ostream& os, const bound& val)
    {
    
        os << "(" ;
        filter_stack.push("(");
        
        os << val.oper1 ;

        //set_bound_var.insert(("?" + boost::get<var>(val.oper1)));
        
        filter_stack.push(("?"+ boost::get<var>(val.oper1)));
        
        //cout << "\n\n TYPE:  " << std::to_string(val.oper1.which()) <<"\n";

        os << "\'" << typeid(tag).name() << "\' ";
        filter_stack.push(typeid(tag).name());
        
        
        os << ")";
        filter_stack.push(")");
	//os << "-------------\n";
			
		filter_stack.pop(); // ')'
        	
		str_tmp_1 = filter_stack.top();
        	filter_stack.pop();
        	
		str_tmp_2 = filter_stack.top();
        	filter_stack.pop();
        	
		str_tmp_3 = "";

        	tmp_tuple = std::make_tuple(str_tmp_2, str_tmp_1, str_tmp_3);
        	

		filter_stack.pop(); // ')'

		if (int_tmp_key < 9) 
		tmp_map.emplace( ("key_0"+std::to_string(++int_tmp_key)) , tmp_tuple );
		else
		tmp_map.emplace( ("key_"+std::to_string(++int_tmp_key)) , tmp_tuple );


		if (int_tmp_key < 9) 
		filter_stack.push(("key_0"+std::to_string(int_tmp_key)));
		else
		filter_stack.push(("key_"+std::to_string(int_tmp_key)));		


	
        return os;
    }
};




}

    // EXPRESSION PARSER
template <typename It, typename Skipper = boost::spirit::standard_wide::space_type>
struct parserExpression : qi::grammar<It, Expression::expressionContainer(), Skipper>
{
    parserExpression() : parserExpression::base_type(expr_)
    {
        using namespace qi;
        using namespace Expression;
        using custom::fold;

        expr_ = or_.alias();

        // Logical Operators
        or_ = fold<binop<op_or> >(xor_.alias())[orOperator_ >> xor_];
        xor_ = fold<binop<op_xor> >(and_.alias())[xorOperator_ >> and_];
        and_ = fold<binop<op_and> >(equal_.alias())[andOperator_ >> equal_];
        equal_ = fold<binop<op_eq> >(unequal_.alias())[equalOperator_ >> unequal_]; 
        unequal_ = fold<binop<op_ne> >(gte_.alias())[unequalOperator_ >> gte_];
        gte_     = fold<binop<op_gte> >(gt_.alias())[gteOperator_ >> gt_];
        gt_      = fold<binop<op_gt> >(lte_.alias())[gtOperator_ >> lte_];
	lte_     = fold<binop<op_lte> >(lt_.alias())[lteOperator_ >> lt_];
	lt_     = fold<binop<op_lt> >(sum_.alias())[ltOperator_ >> sum_];
	
        // Numerical Operators
        sum_ = fold<binop<op_add> >(difference_.alias())[sumOperator_ >> difference_];
        difference_ = fold<binop<op_subtract> >(factor_.alias())[differenceOperator_ >> factor_];
        factor_ = fold<binop<op_multiply> >(division_.alias())[factorOperator_ >> division_]; 
        division_ = fold<binop<op_divide> >(bound_.alias())[divisionOperator_ >> bound_];        




        // UNARY OPERATIONS
        bound_ = (  no_case ["bound"] > not_ ) [_val = boost::phoenix::construct<Expression::bound <op_bound>>(qi::_1)]    | not_ [_val = qi::_1];
        not_   = (notOperator_ > (simple | bound_)) [_val = boost::phoenix::construct<Expression::unop <op_not>>(qi::_1)]    | simple [_val = qi::_1];
        
        

        simple = (('(' > expr_ > ')') | var_ | num_);
        //var_ = qi::lexeme[+alnum];
        //var_ = qi::lexeme[ ('?' >> +alnum) ]  | qi::lexeme[ ('%' >> +(alnum | char_('%')) )] | qi::lexeme[ ('\"' >>  +(alnum | char_('-') | char_(':') | char_('\"') )  ) ];
         var_ = qi::lexeme[ ('?' >> +alnum) ]  | qi::lexeme[ ('%' >> +(alnum | char_('%')) )] | qi::lexeme[ ('\"' >>  +(alnum | char_('-') | char_(':') | char_('\"') )  ) ]
        | qi::lexeme[ (no_case ["<http"] >>  +(alnum | char_('-') | char_('.') | char_(':') | char_('_') | char_('#') | char_('/') | "//" | char_('>') )  ) ];

        

        
        
        num_ = real_parser<double,strict_real_policies<double>>() | int_;

        notOperator_        = qi::char_('!');
        andOperator_        = qi::string("&&");
        orOperator_         = qi::string("||");
        xorOperator_        = qi::char_("^");
        equalOperator_      = qi::string("=");
        unequalOperator_    = qi::string("!=");
        sumOperator_        = qi::char_("+");
        differenceOperator_ = qi::char_("-");
        factorOperator_     = qi::char_("*");
        divisionOperator_   = qi::char_("/");
        gteOperator_        = qi::string(">=");
        gtOperator_         = qi::char_(">");
        lteOperator_        = qi::string("<=");
        ltOperator_         = qi::char_("<");
        
        BOOST_SPIRIT_DEBUG_NODES((expr_)(or_)(xor_)(and_)(equal_)(unequal_)(gte_)(gt_)(lte_)(lt_)(sum_)(difference_)(factor_)(division_)(simple)(notOperator_)
                                 (andOperator_)(orOperator_)(xorOperator_)(equalOperator_)(unequalOperator_)(sumOperator_)(differenceOperator_)(factorOperator_)(divisionOperator_));

    }

private:

    qi::rule<It, Expression::var(), Skipper> var_;
    qi::rule<It, Expression::expressionContainer(), Skipper>
    	  not_
    	, bound_
        , and_
        , xor_
        , or_
        , equal_
        , unequal_
        , gte_
        , gt_
        , lte_
        , lt_
        , sum_
        , difference_
        , factor_
        , division_
        , simple
        , expr_
        , num_
        ;
    qi::rule<It, Skipper> notOperator_
        , andOperator_
        , orOperator_
        , xorOperator_
        , equalOperator_
        , unequalOperator_
        , sumOperator_
        , differenceOperator_
        , factorOperator_
        , divisionOperator_
        , gteOperator_
        , gtOperator_        
        , lteOperator_
        , ltOperator_        
        ;
};




map<std::string, std::tuple< std::string, std::string, std::string >> parse_filter_to_AST_map(const std::string str)
{

	Expression::tmp_map.clear();
    map<std::string, std::tuple< std::string, std::string, std::string >>::iterator filter_it =  Expression::tmp_map.begin();

		/*
		while (filter_it != Expression::tmp_map.end())
		{
			Expression::tmp_map.erase (filter_it);
			filter_it++;
		}
		Expression::tmp_map.clear();
		*/
		

    std::string::const_iterator iter = str.begin(), end = str.end();



    parserExpression<std::string::const_iterator,qi::space_type> parser;
    Expression::expressionContainer expr;
    

    bool result = qi::phrase_parse(iter,end,parser,qi::space, expr);


    if(result && iter==end)
    {
        std::cout << "Success." << std::endl;
        std::cout << str << " => " << expr << std::endl;
        
    }
    else
    {
        std::cout << "Failure." << std::endl;
    }
   



    //parse_filter_to_AST_map("?var1 <= (!(?var2 + %p1%)) || ?var1 >= (!(?var2 - 170)) ");
 
	std::map<std::string, std::tuple< std::string, std::string, std::string >>::iterator it =
Expression::tmp_map.begin();
 
	// Iterate over the map using Iterator till end.
	while (it != Expression::tmp_map.end())
	{
		// Accessing KEY from element pointed by it.
		std::string word = it->first;
 
		// Accessing VALUE from element pointed by it.
		//int count = it->second;
 
		std::cout << word << " :: \n" <<	
		"  0: " << std::get< 0 >( it->second ) <<
		"  1: " << std::get< 1 >( it->second ) <<
		"  2: " << std::get< 2 >( it->second ) << std::endl;
 
		// Increment the Iterator to point to next entry
		it++;
	}



			//for (string const& pre_opt : set_bound_var)
			//	cout << "   \n BOUND  :" << pre_opt << endl;

    

    return Expression::tmp_map;

}

    
 
    
    

