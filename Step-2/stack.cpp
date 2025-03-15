#include "slink.h"
bool check(char *str)
{
  //在这里补全代码
  /****begin*****/
    sqstack S;
    initstack(S);

    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = str[i];

        if (ch == '(' || ch == '[' || ch == '{')
        {
            push(S, ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            char topChar;
            if (!pop(S, topChar))
            {
                return false;
            }

            if ((ch == ')' && topChar != '(') ||
                (ch == ']' && topChar != '[') ||
                (ch == '}' && topChar != '{')) {
                return false;
            }
        }
    }

    return isempty(S);
  
  /****end******/
}
