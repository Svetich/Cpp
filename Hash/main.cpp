#include "iostream"
#include "Hash.cpp"


std::vector <std::string> createBuffer(char* name)
{
    std::vector <std::string> buffer;
    std::string line;

    std::ifstream in(name);
    if (in.is_open())
        {
            while (getline(in, line, ' ' ))
            {
                if (line != std::string())
                {
                    if (line.find('\n') != std::string::npos) 
                    {
                        line.pop_back();
                    }

                    if ((line.find('.') != std::string::npos) || (line.find(',') != std::string::npos) || (line.find('!') != std::string::npos) || 
                    (line.find('?') != std::string::npos) || (line.find(':') != std::string::npos) || (line.find(';') != std::string::npos))
                    {
                        line.pop_back();
                    }

                    buffer.push_back(line);                
                }
            }
        }
        in.close();

        return buffer;
}


void createCollisionFile(std::vector < std::list <std::string> > hash_table)
{
    std::ofstream collision;          
    collision.open("collision.txt"); 
    if (collision.is_open())
    {
        for (int i = 0; i <= hash_table.size(); i++)
        {
            collision << hash_table[i].size() << std::endl;
        }        
    }
}


int main()
{
    std::vector <std::string> buffer = createBuffer("hamlet.txt");  

    std::vector < std::list <std::string> > hash_table(1000); 

    for (int i = 0; i <= buffer.size(); i++)
    {
        if (buffer[i] != std::string())
        {
            hashFunctions key = {buffer[i]};
            int hash = key.hashFunction5();

            hash_table[hash % 1000].push_back(buffer[i]);
        }
    }
    
    createCollisionFile(hash_table);

    return 0;
}