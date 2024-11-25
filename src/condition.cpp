#include "Condition.h"


bool Condition::apply(const Row &cur_row)
{
    if (get_tokens().empty())
        return true;
    
    return dynamic_cast<const BoolCell&>(*eval(cur_row)).value;

}
