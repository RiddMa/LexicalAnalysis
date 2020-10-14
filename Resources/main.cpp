#include "../Headers/main.h"
#include "../Headers/analysis.h"
#include "../Headers/err.h"
#include "../Headers/util.h"

/*
第一类：标识符   letter(letter | digit)*  无穷集
第二类：常数    (digit)+  无穷集
第三类：保留字(32)
auto       break    case     char        const      continue
default    do       double   else        enum       extern
float      for      goto     if          int        long
register   return   short    signed      sizeof     static
struct     switch   typedef  union       unsigned   void
volatile    while

第四类：界符  ‘/*’、‘//’、 () { } [ ] " "  '
第五类：运算符 <、<=、>、>=、=、+、-、*、/、^、
 */
std::vector<std::string> reserveWord;
std::vector<std::string> buf;

int main() {
    ifstream infile;
    infile.open("../test.c");

    if (!infile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    file2Buf(infile, buf);

    for (auto & i : buf) {
        analysisLine(i);
    }

    return 0;
}
