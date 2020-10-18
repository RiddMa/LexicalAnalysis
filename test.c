int main() {
    /*comment
    test*/
    ifstream infile;

    //error test
        9a ; 'c

    infile.open("../test.c");
    if (!infile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    int a=2;
    a*=2; a++;

    return 0;
}
















