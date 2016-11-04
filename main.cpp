/********************************************************
Copyright (c) <2016> <Bloodknight Studios>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*********************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

string setCase(const std::string & s, int Case){
    string ret(s.size(), char());
    for(unsigned int i = 0; i < s.size(); ++i){
        if (Case == 0)
            ret[i] = (s[i] <= 'z' && s[i] >= 'a') ? s[i]-32 : s[i];
        if (Case == 1)
            ret[i] = (s[i] <= 'Z' && s[i] >= 'A') ? s[i]+32 : s[i];
    }
    return ret;
}

int main ()
{
    // Input file has 3 enries, name hex and vec3 rgb
    string colname, colhex, colrgb;
    string scolr, scolg, scolb;

    double colr, colg, colb;
    ifstream infile ("namedcolours.txt");
    ofstream outfile ("colours.h");

    outfile << "#ifndef COLOURS_H_INCLUDED\n";
    outfile << "#define COLOURS_H_INCLUDED\n\n";
    outfile << "\/\/ Named colours for use with opengl r, g, b system\n\n";

    if (infile.is_open()) {
        while ( !infile.eof() ) {
            // read each line
            getline (infile, colname, '\t');
            getline (infile, colhex, '\t');
            getline (infile, scolr, ',');
            getline (infile, scolg, ',');
            getline (infile, scolb, '\n');

            // convert string data to integer
            colr = atof(scolr.c_str());
            colg = atof(scolg.c_str());
            colb = atof(scolb.c_str());

            string colnameupper, colnamelower;
            colnameupper = setCase(colname, 0);
            colnamelower = setCase(colname, 1);
            outfile.precision(2);
            outfile <<fixed << "GLfloat " << colnameupper<<"[] = {" << colr/256 << "f, " << colg/256 << "f, " << colb/256 <<"f };"<<endl;
            //printf("#define %s %f.2, %f.2, %f.2", toupper(), float() )

        }
        infile.close();
    outfile << "\n\n#endif // COLOURS_H_INCLUDED/n";

    }

    else cout << "Unable to open file";

    return 0;
}
