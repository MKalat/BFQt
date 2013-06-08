#ifndef FILM_FTBL_CLASS_H
#define FILM_FTBL_CLASS_H

#endif // FILM_FTBL_CLASS_H
class Ftbl
{
public:
    static struct Film film_tbl;
    static struct Film2 film2_ftbl;
    static struct DB_paths pths;
    static bool sort; // oznacza czy form. Film jest sortowany.


};

struct DB_paths
{

    wchar_t BF_PDB[550];
    wchar_t BF_PDB2[550];
    wchar_t BF_OC[550];
    wchar_t BF_OB[550];
    wchar_t BF_PRP[550];
    wchar_t BF_PRD[550];
    wchar_t BF_LZ[550];
    wchar_t BF_WI[550];
    wchar_t BF_WO[550];
    wchar_t BF_COVERS[550];
    wchar_t BF_MCF[550];
    wchar_t db_path[550];
    wchar_t cur_db_path[550];

};
