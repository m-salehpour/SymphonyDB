// #define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <map>
namespace qi    = boost::spirit::qi;


std::map < int, std::pair<int, std::string> > map_modifiers;
int map_key = 0;




struct SelectStatement
{
    std::vector<std::string> order_by_, offset_, limit_; 

};

BOOST_FUSION_ADAPT_STRUCT(SelectStatement, 
        (std::vector<std::string>, order_by_)
        (std::vector<std::string>, offset_)
        (std::vector<std::string>, limit_)        

       )

 struct asc_cnt
    {
        void operator()(std::string const& i, qi::unused_type, qi::unused_type) const
        {
            map_modifiers.emplace(map_key++, std::make_pair(0, ("?"+i)) );
        }
    };

 struct desc_cnt
    {
        void operator()(std::string const& i, qi::unused_type, qi::unused_type) const
        {
            map_modifiers.emplace(map_key++, std::make_pair(1, ("?"+i)) );
        }
    };
    
    
 struct offset_cnt
    {
        void operator()(int const& i, qi::unused_type, qi::unused_type) const
        {

            map_modifiers.emplace(map_key++, std::make_pair(2, std::to_string(i)) );

        }
    };

 struct limit_cnt
    {
        void operator()(int const& i, qi::unused_type, qi::unused_type) const
        {
            map_modifiers.emplace(map_key++, std::make_pair(3, std::to_string(i)) );
        }
    };

    
template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, SelectStatement(), Skipper>
{
    parser() : parser::base_type(start)
    {
        using namespace qi;
	namespace lambda = boost::lambda;
        using lambda::_1;

        sparql_sqlident_var = lexeme [ ("?" >> +alnum) ]; // table or column name
        desc_ = ( no_case [ "desc" ] >> '(' >> sparql_sqlident_var >> ')');
        asc_  = ( no_case [ "asc" ] >> '(' >> sparql_sqlident_var >> ')');
        
        order_by_  = no_case [ "order" ] >> no_case [ "by" ] >> *( sparql_sqlident_var[asc_cnt()] |  ('(' >> sparql_sqlident_var >> ')') [asc_cnt()] | desc_[desc_cnt()] | asc_[asc_cnt()] );
        
        offset_    = no_case [ "offset" ]   >> int_ [offset_cnt()];
        
        limit_     = no_case [ "limit" ]   >> int_  [limit_cnt()];

        start    = *order_by_ >> *offset_  >> *limit_  >> *char_('.');

        BOOST_SPIRIT_DEBUG_NODE(start);
        BOOST_SPIRIT_DEBUG_NODE(sparql_sqlident_var);
        BOOST_SPIRIT_DEBUG_NODE(order_by_);
        BOOST_SPIRIT_DEBUG_NODE(offset_);
    }

  private:
    qi::rule<It, std::string()             , Skipper> sparql_sqlident_var, desc_, asc_;
    qi::rule<It, std::vector<std::string>(), Skipper> order_by_, offset_, limit_;
    qi::rule<It, SelectStatement()         , Skipper> start;
};

template <typename C, typename Skipper>
    std::map < int, std::pair<int, std::string> > get_modifiers(const C& input, const Skipper& skipper) //string, space
{


    map_modifiers.clear();
    auto f(std::begin(input)), l(std::end(input));

    parser<decltype(f), Skipper> p;
    SelectStatement query;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,skipper,query);
        if (ok)   
        {
		/*
		std::map < int, std::pair<int, std::string> >::iterator it = map_modifiers.begin();
		while (it != map_modifiers.end())
		{


            	switch ( std::get<0>(it->second) )
		{            	
            	case (0):
            		std::cout << "ASC: " << std::get<1>(it->second) << "\n";
            		break;
            	case (1):
            		std::cout << "DESC: " << std::get<1>(it->second) << "\n";
            		break;
            	case (2):
            		std::cout << "OFFSET: " << std::get<1>(it->second) << "\n";
            		break;
            	case (3):
            		std::cout << "LIMIT: " << std::get<1>(it->second) << "\n";
            		break;
            		
            	}
            	
            	it++;
            	}
            	*/	
            
     
            

        }
        else      std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

        if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
        
        return map_modifiers;
        
    } catch(const qi::expectation_failure<decltype(f)>& e)
    {
        std::string frag(e.first, e.last);
        std::cerr << e.what() << "'" << frag << "'\n";
    }

	return map_modifiers;
}

