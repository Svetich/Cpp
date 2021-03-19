#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include <algorithm>

using namespace std;

unsigned int RSHash(const char* str, unsigned int length) 
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}

unsigned int JSHash(const char* str, unsigned int length) // 1
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          =
                      (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash = 0;
   unsigned int test = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << OneEighth) + (*str);

      if ((test = hash & HighBits) != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << 4) + (*str);

      if ((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }

      hash &= ~x;
   }

   return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
   unsigned int hash = length;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }

   return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}

void random_string(char *randomStr, size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    generate_n(randomStr, length, randchar);
}

int main()
{
    default_random_engine gen;
    uniform_int_distribution<int> dist(3,10);
    vector<unordered_set<int>> v(9); // вектор из 9 unordered_set
    // каждый из unordered_set для соответствующей хэш-функции
    array<int, 9> collisions; // массив из 9 элементов для подсчета коллизий
    collisions.fill(0); // заполнение массива нулями
    char *randomStr;
    int length;
    int N = 20000; // N можно выбрать любое
    for (int i = 0; i<N; i++)
    {
      length = dist(gen);
      randomStr = new char[length];
      random_string(randomStr, length);
      array <int, 9> hash = {RSHash(randomStr, length), JSHash(randomStr, length), PJWHash(randomStr, length),
                            ELFHash(randomStr, length), BKDRHash(randomStr, length), SDBMHash(randomStr, length), 
                            DJBHash(randomStr, length), DEKHash(randomStr, length), APHash(randomStr, length)};

      for (int i = 0; i < 9; i++)
      {
         if (v[i].find(hash[i]) == v[i].end())
         {
            v[i].insert(hash[i]);
         }
         else
         {
            collisions[i] += 1;
         }
      }
        /* TODO: вычислить 9 хешей от randomStr с помощью соответствующих хэш-функций
                 добавить хеши в соответствующие unordered_set
                 если хэш уже есть в unordered_set, увеличить соответствующий счетчик коллизий на единицу
        */
    }
   for (int i = 0; i < 9; i++)
   {
      cout << collisions[i] << endl;
   }   
   // TODO: вывести на экран количество коллизий для каждой из хэш-функций
   /* вывод
   17
   71
   264
   264
   17
   17
   81
   79
   17 */
   return 0;
}
