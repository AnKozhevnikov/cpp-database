#include <string>
#include <map>
#include <vector>
#include "FlexLexer.h"
enum FuncTokenTypes
{
    open_par,
    close_par,
    open_sqr,
    close_sqr,
    open_brace,
    close_brace,
    create,
    on,
    update,
    mdelete,
    mselect,
    where,
    from,
    separator,
    eq,
    by,
    mset,
    mindex,
    join,
    mend,
    mnext,
    other
};
std::vector<FuncToken> mbuffer;


using FT=FuncTokenTypes;
#define Q(x) #x
#define GLUE(b) FT::b
#define f_pair(x) {std::string(Q(x)), GLUE(x)}
#define fm_pair(x) {std::string(Q(x)), GLUE(m ## x)}


static std::map<std::string, FuncTokenTypes> words_to_func  = {f_pair(create), f_pair(update),
fm_pair(select), f_pair(where), f_pair(from), f_pair(by), fm_pair(set), fm_pair(index), f_pair(join), f_pair(on), fm_pair(delete)};
class mParser : public yyFlexLexer
{
    
public:
    mParser();
    void parse(std::string a);
private:
    std::vector<FuncToken> tokens;
};

class FuncToken
{
    public:
        FuncTokenTypes type;
        std::string val;
        FuncToken(std::string tmp_v) :val(tmp_v) {
            if (tmp_v == "(")
            {   
                type = FT::open_par;
            } 
            else if (tmp_v == ")")
            {
                type = FT::close_par;
            }
            else if (tmp_v == "{")
            {
                type = FT::open_brace;
            }
            else if (tmp_v == "}")
            {
                type = FT::close_brace;
            }
            else if (tmp_v == "[")
            {
                type = FT::open_sqr;
            }
            else if (tmp_v == "]")
            {
                type = FT::close_sqr;
            }
            else if (tmp_v == "=")
            {
                type = FT::eq;
            }
            else if (tmp_v == ":")
            {
                type = FT::separator;
            }
            else if (tmp_v == "\0")
            {
                type = FT::mend;
            }
            else if (tmp_v == ",")
            {
                type = FT::mnext;
            }
            else if (words_to_func.find(tmp_v) != words_to_func.end())
            {
                type = words_to_func[tmp_v];
            }
            else
            {
                type = FT::other;
            }
        }
};





class FinetStateM
{
    public:
        FinetStateM(std::vector<FuncToken>& v) : Tokens(v), pos(3) {}
        
        std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::string>, int> next_col();
        int pars_atr();
        std::shared_ptr<ValueType> pars_type();
        int pos;
    private:
        std::vector<FuncToken>& Tokens;
        
};