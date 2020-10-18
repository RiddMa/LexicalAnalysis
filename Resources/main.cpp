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
std::vector<std::string> buf;
int state(0);
bool read(false);
tool cnt{};

int main() {
    ifstream infile;
    infile.open("../test.c");

    if (!infile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    file2Buf(infile, buf);

    char inChar;
    std::string token;
    cnt.clear();
    for (int i = 0; i < buf.size(); i++) {
        for (int j = 0; j < buf[i].length();) {
            if (state == 14) {// remain of this line is comment
                state = 0;
                break;
            } else {
                if (!read) {
                    inChar = buf[i][j];
                    j++;
                    cnt.charCount++;
                }
                analysisChar(token, inChar);
            }

        }
        cnt.rowCount++;
    }
    if (state != 0) {
        state = -1;
        analysisChar(token, inChar);
    }

    std::cout << "Char count: " << cnt.charCount << " \tRow count: " << cnt.rowCount << std::endl;
    std::cout << "Keyword count: " << cnt.keywordCount << "\tIdentifier count: " << cnt.idCount;
    std::cout << "\tOperator count: " << cnt.opCount << "\tConstant count: " << cnt.constCount<< std::endl;
    std::cout << "Delimiter count: " << cnt.othersCount << "\tError count: " << cnt.errCount ;
    std::cout << "\t\tTotal count: " << cnt.getTotalCount() << std::endl;
    infile.close();
    return 0;
}
