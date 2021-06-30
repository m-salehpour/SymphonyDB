namespace custom
{
    namespace tag
    {
        struct fold { BOOST_SPIRIT_IS_TAG() };
    }

    template <typename Exposed, typename Expr>
    boost::spirit::stateful_tag_type<Expr, tag::fold, Exposed>
    fold(Expr const& expr)
    {
        return boost::spirit::stateful_tag_type<Expr, tag::fold, Exposed>(expr);
    }

}

namespace boost { namespace spirit 
{
    template <typename Expr, typename Exposed>
    struct use_directive<qi::domain
          , tag::stateful_tag<Expr, custom::tag::fold, Exposed> >
      : mpl::true_ {};
}}

namespace custom
{
    template <typename Exposed, typename InitialParser, typename RepeatingParser>
    struct fold_directive
    {
        fold_directive(InitialParser const& initial, RepeatingParser const& repeating):initial(initial),repeating(repeating){}

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename boost::spirit::traits::attribute_of<InitialParser,Context,Iterator>::type type;
        };

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper, Attribute& attr_) const
        {
            Iterator start = first;

            typename boost::spirit::traits::attribute_of<InitialParser,Context,Iterator>::type initial_attr;


            if (!initial.parse(first, last, context, skipper, initial_attr))
            {
                first=start;
                return false;
            }

            typename boost::spirit::traits::attribute_of<RepeatingParser,Context,Iterator>::type repeating_attr;

            if(!repeating.parse(first, last, context, skipper, repeating_attr))
            {
                boost::spirit::traits::assign_to(initial_attr, attr_);
                return true;
            }
            Exposed current_attr(initial_attr,repeating_attr);

            while(repeating.parse(first, last, context, skipper, repeating_attr))
            {
                boost::spirit::traits::assign_to(Exposed(current_attr,repeating_attr),current_attr);
            }
            boost::spirit::traits::assign_to(current_attr,attr_);
            return true;
        }

        template <typename Context>
        boost::spirit::info what(Context& context) const
        {
            return boost::spirit::info("fold");
        }

        InitialParser initial;
        RepeatingParser repeating;
    };
}

namespace boost { namespace spirit { namespace qi
{
    template <typename Expr, typename Exposed, typename Subject, typename Modifiers>
    struct make_directive<
        tag::stateful_tag<Expr, custom::tag::fold, Exposed>, Subject, Modifiers>
    {
        typedef custom::fold_directive<Exposed, Expr, Subject> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject, Modifiers const&) const
        {
            typedef tag::stateful_tag<
                Expr, custom::tag::fold, Exposed> tag_type;
            using spirit::detail::get_stateful_data;

            return result_type(get_stateful_data<tag_type>::call(term),subject);
        }
    };
}}}
