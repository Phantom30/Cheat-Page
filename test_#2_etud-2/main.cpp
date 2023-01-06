/**
 * @date : 28 nov 2022
 * @author A. Casali
 * @synopisis : construction de la spirale de ULAM en coordonées carétsiennes : https://fr.wikipedia.org/wiki/Spirale_d%27Ulam
 **/
#include <iostream>
#include <vector>
#include <cmath> //sqrt ()
#include <cassert> // assert
#include <algorithm> //binary_search ()
#include <fstream> //ofstream, ifstream, ...
using namespace std;

/**
 * @brief generePremierPlusPetitQue
 * @param n : plus grand entier pour lequel on doit trouver des nombres premiers plus petit en utilisant le modulo
 * @return liste des nombres preimers plus petits que n
 */
vector<size_t> generePremierPlusPetitQue (const size_t & n) {
    //voir les spec du programmme
    if (n < 2 ) exit (-1);
    //on geneère tous les nombres entre [2; n)
    vector<size_t> vectNbPremier (n-2);
    for (size_t i (0); i < vectNbPremier.size(); ++i)
        vectNbPremier[i] = i + 2;
    //pour chaque nombre possible
    for (size_t i (0); i < vectNbPremier.size(); ++i){
        //on teste son modulo avec ceux qui sont plus petit que lui
        for (size_t j (0); j < i; ++j){
            //si on a déjà un 0, on ne fait rien
            if (vectNbPremier[j] ==0) continue;
            //est-ce qu'on a un nombre premier ?
            if (vectNbPremier [i] % vectNbPremier[j] ==0){
                vectNbPremier [i] = 0;
                break;
            }
        }
    }
    //on supprime tous les 0 -- tassement // ne pas utiliser .erase()
    size_t posAInserer (0);
    for (size_t i (0); i < vectNbPremier.size(); ++i){
        if (vectNbPremier [i] == 0) continue;
        vectNbPremier [posAInserer++] = vectNbPremier [i];
    }
    vectNbPremier.resize(posAInserer);
    return vectNbPremier;
}

/**
 * @brief generePremierPlusPetitQueV2
 * @param n : plus grand entier pour lequel on doit trouver des nombres premiers plus petit en utilisant le crible d'Erathosthène
 * @return liste des nombres preimers plus petits que n
 */
vector<size_t> generePremierPlusPetitQueV2 (const size_t & n) {
    //voir les spec du programmme
    if (n < 2 ) exit (-1);
    //on geneère tous les nombres entre [2; n)
    //on mets tous les nombres dans le tableau vectNbPremier
    vector<size_t> vectNbPremier (n-2);
    for (size_t i (0); i < vectNbPremier.size(); ++i)
        vectNbPremier[i] = i + 2;
    //pour chaque nombre possible
    for (size_t i (0); i < vectNbPremier.size(); ++i){
        //on supprime tous les multiples de i
        if (0 == vectNbPremier[i]) continue;
        for (size_t j (vectNbPremier[i] * vectNbPremier[i] -2); j < vectNbPremier.size(); j+=vectNbPremier[i]){
            vectNbPremier[j] = 0;
        }
    }
    //on supprime tous les 0 -- tassement // ne pas utiliser .erase()
    size_t posAInserer (0);
    for (size_t i (0); i < vectNbPremier.size(); ++i){
        if (vectNbPremier [i] == 0) continue;
        vectNbPremier [posAInserer++] = vectNbPremier [i];
    }
    vectNbPremier.resize(posAInserer);
    return vectNbPremier;
}


/**
 * @brief affichVecteur
 * @param [in] vect : le tableau a affcher
 */
template <typename unType>
void affichVecteur (const vector<unType> & vect){
    for (const auto & cell : vect)
        cout << cell << '\t';
    cout << endl;
}

/**
 * @brief CMat : definition d'une matrice (2D), le type de la cellule est un unsigned
 */
typedef vector<vector<unsigned>> CMat;


/**
 * @brief affichMat
 * @param[in] mat : la matrice a afficher
 */
void affichMat (const CMat & mat){
    for (const auto & uneLigne : mat){
        for (const auto & val : uneLigne)
            cout << val << '\t';
        cout << endl;
    }
}


/**
 * @brief initMat
 * @param[out] mat : la matice
 * @param[in] taille : taille de la matrice, intialisée qu'avec des 0
 */
void initMat (CMat & mat, const size_t & taille) {
    mat.resize(taille);
    for (auto & uneLigne : mat)
        uneLigne.resize(taille);
}

/**
 * @brief genereMatricEscargot
 * @param mat[out] une matrice en forme d'esacrgot
 */
void genereMatricEscargot (CMat & mat){
    size_t numLigne (mat.size()/2), numCol (mat.size()/2);
    unsigned numerTour (1), nombreAInserer (1);
    mat[numLigne][numCol++] = nombreAInserer++;
    for (;nombreAInserer < mat.size() * mat.size();){
        //haut
        for (unsigned i (0); i < 2*numerTour; ++i){
            mat[numLigne][numCol] = nombreAInserer++;
            --numLigne;
        }
        ++numLigne;
        --numCol;
        //gauche
        for (unsigned i (0); i < 2*numerTour; ++i){
            mat[numLigne][numCol] = nombreAInserer++;
            --numCol;
        }
        ++numLigne;
        ++numCol;
        //bas
        for (unsigned i (0); i < 2*numerTour; ++i){
            mat[numLigne][numCol] = nombreAInserer++;
            ++numLigne;
        }
        --numLigne;
        ++numCol;
        //droite
        for (unsigned i (0); i < 2*numerTour; ++i){
            mat[numLigne][numCol] = nombreAInserer++;
            ++numCol;
        }
        ++numerTour;
    }
}


/**
 * @brief genereMatricUlam
 * @param [out] mat : une matrice dans laquelle on supprime tous les nombres
 * appartenant au tableau "nombresPremiers"
 * @param [in] nombresPremiers : tableau des nombre premiers, ce tableau est supposé trié
 */
template <typename T>
void genereMatricUlam (CMat & mat,
                       const vector <T> & nombresPremiers){

    for (auto & uneLigne : mat){
        for (unsigned & val : uneLigne){
            if (!binary_search (nombresPremiers.begin(), nombresPremiers.end(),
                      val))
                val = 0;
        }
    }
}

/**
 * @brief affichMatUlam
 * @param [in] mat : matrice à afficher : 0 si le nombre n'est pas premier, son nombre
 * sinon
 */
void affichMatUlam (const CMat & mat){
    for (const auto & uneLigne : mat){
        for (const auto & val : uneLigne)
           cout << (val == 0? '-' : 'X') ;
        cout << endl;
    }
}
/**
 * @brief UlamVersPPM, dans  cette version, on ecrit le "pixel" en utilisant les string
 * @param [in] mat : matrice à afficher
 * @param [in] nomFichiersortie : nom du fichier image dans lequel on souhaite écrire
 */
void UlamVersPPM(const CMat & mat,
                 const string & nomFichiersortie ){
    ofstream ofs (nomFichiersortie);
    ofs << "P3" << '\n';
    ofs << mat.size() << ' ' << mat.size() << '\n';
    ofs << "255" << '\n';
    const string pixel1_noir ("0 0 0 ");
    const string pixel2_blanc ("255 255 255 ");
    for (const vector<unsigned> & uneLigne : mat){
        for (const unsigned & val : uneLigne)
           ofs << (val == 0? pixel2_blanc : pixel1_noir) ;
        ofs << '\n';
    }
}



/**
 * @brief UlamVersPPM - dans  cette version, on ecrit le "pixel" en utilisant les entiers
 * naturels
 * @param [in] mat : matrice à afficher
 * @param [in] nomFichiersortie : nom du fichier image dans lequel on souhaite écrire
 */
void UlamVersPPMV2(const CMat & mat,
                 const string & nomFichiersortie ){
    ofstream ofs (nomFichiersortie);
    ofs << "P3" << '\n';
    ofs << mat.size() << ' ' << mat.size() << '\n';
    ofs << "255" << '\n';
    const unsigned niveauPixel1Rouge (0);
    const unsigned niveauPixel1Vert (0);
    const unsigned niveauPixel1Bleu (0);
    const unsigned niveauPixel2Rouge (255);
    const unsigned niveauPixel2Vert (255);
    const unsigned niveauPixel2Bleu (255);
    for (const vector<unsigned> & uneLigne : mat){
        for (const unsigned & val : uneLigne){
            //si val n'est pas un premier => on affiche les niveaux RGB pour pixel1
            if (0 != val){
                ofs << niveauPixel1Rouge << ' '
                    << niveauPixel1Vert  << ' '
                    << niveauPixel1Bleu  << ' ';
            }
            else { //val est pas un premier => on affiche les niveaux RGB pour pixel2
                ofs << niveauPixel2Rouge << ' '
                    << niveauPixel2Vert  << ' '
                    << niveauPixel2Bleu  << ' ';
            }
        }
        ofs << '\n';
    }
}

/**
 * @brief main - fonction principale
 * @return 0 si pas de boulette, 1 si la taille de la matrice est imapaire
 * @param [in] argv[1] : taille de la matrice
 */
int main(int argc, char* argv[])
{
    if (3 != argc){
        cerr << "usage : nom_pgm mat_size nom_fichier_sortie" << endl;
        exit (2);
    }
    vector<size_t> v, v1;
    unsigned max (stoul (argv[1]));
    if (0 == (max % 2)) {
        cerr << " la taille de la matrice doit êrte impaire" << endl;
        exit (1);
    }
    v  = generePremierPlusPetitQueV2 (max * max);
    //pour être sûr, une petite assertion ^^
    //v1 = generePremierPlusPetitQue(max * max);
    //v1 = generePremierPlusPetitQue((max - 1) * (max -1));
    //assert (v == v1);
    //affichVecteur(v);
    //on declare la matrice
    CMat uneMatrice;
    //on dimensionne la matrice
    initMat (uneMatrice, max);
    //on remplit la matrice en escargot
    genereMatricEscargot (uneMatrice);
    //Trool, les esacargots, c'est bon ^^
    //on supprime les nombres non premiers
    genereMatricUlam (uneMatrice, v);
    //on affiche en "mode standard"
    //affichMat(uneMatrice);
    //on affiche en "selon les specifications"
    affichMatUlam (uneMatrice);
    //on ecrit la matrice dans un fichier au format PPM
    UlamVersPPM   (uneMatrice, string(argv[2] + string("1")));
    UlamVersPPMV2 (uneMatrice, string(argv[2] + string("2")));
    return 0;
}
