#include <iostream>
#include <cstdio>

class String
{
    public:

        char* str;

        String(char* str)
        {
            this->str = str;
        }

        int length()
        {
            int len = 0;

            while (str[len] != '\0') 
            {
                len += 1;
            }

            return len;
        }
        
        int countChar(char symbol)
        {
            int count = 0;
            int i = 0;

            while (str[i] != '\0')
            {   
                if (str[i] == symbol)
                {
                    count += 1;
                } 

                i += 1;       
            }
            return count;
        }

        int findFirstOf(char symbol)
        {
            int i = 0;

            while (str[i] != '\0')
            {
                if (str[i] == symbol)
                {
                    return i;
                }
                else
                {
                    i += 1;
                }
                 
            }
        }

        String operator+ (String S)
        {
            int len = length() + S.length() + 1;
            char* str = new char[len];
            
            for (int i = 0; i < length(); ++i)
            {
                str[i] = this->str[i];
            }


            for (int i = length(); i < len; ++i)
            {
                str[i] = S.str[i - length()];
            }

            str[len - 1] = '\0';

            String string = {str};

            return string;
        }

        String* split(char symbol)
        {
            
            for (int i = 0; i < length(); ++i)
            {

            }
        }

    private:
        
        int length(char* str)
        {
            String string = {str};
            // int len = 0;

            // while ([len] != '\0') 
            // {
            //     len += 1;
            // }

            return string.length();
        }
        
};