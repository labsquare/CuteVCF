#include <string>
#include <stdlib.h>
#include <sys/stat.h>
#include "htslib/bgzf.h"
#include "htslib/tbx.h"
#include "htslib/kseq.h"
#include <iostream>
#include <cstring>
#include <vector>


#include <QtCore>
#include <QDebug>

using namespace std;

class Tabix {

    htsFile* fn;
    tbx_t* tbx;
    kstring_t str;
    hts_itr_t* iter;
    const tbx_conf_t *idxconf;
    int tid, beg, end;
    string firstline;
    bool has_jumped;
    vector<string>::iterator current_chrom;

public:

    string filename;
    vector<string> chroms;

    Tabix(void);
    ~Tabix(void);

    void getHeader(string& header);
    bool setRegion(const string& region);
    bool getNextLine(string& line);
    void setFilename(string& file);

};
