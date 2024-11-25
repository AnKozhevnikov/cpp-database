#include <Expression.h>

ExpressionParcer::ExpressionParcer(std::string str)
{
    str.push_back(',');
    int mode = 0; // 0 - searching =  , 1 - searching , or till end
    int opened_quotes = 0;
    int start = 0;
    for (int i = 0; i < str.size(); i++)
    {
        switch (str[i])
        {
        case '\"':
            opened_quotes ^= 1;
            break;
        
        case '=':
        {
            if (mode == 0 && opened_quotes == 0)
            {
                updating.push_back(str.substr(start, i - start));
                start = i + 1;
            }
            break;
        }

        case ',':
        {
            if (mode == 1 && opened_quotes == 0)
            {
                values.emplace_back(str.substr(start, i - start));
                start = i + 1;
            }
            break;
        }

        default:
            break;
        }
    }

    for (std::string& i : updating)
    {
        int left = 0;
        int right = i.size() - 1;
        while (i[left] == ' ')
            left++;
        while (i[right] == ' ')
            right--;
        i = i.substr(left, right - left + 1);
    }

}

std::vector<std::unique_ptr<Cell>> ExpressionParcer::get_values (const Row& cur_row)
{
    std::vector<std::unique_ptr<Cell>> ans;
    ans.reserve(values.size());
    for (auto& i : values)
    {
        ans.push_back(i.eval(cur_row)->clone());
    }
    return ans;
}