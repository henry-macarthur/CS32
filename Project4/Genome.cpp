#include "provided.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <istream>

using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    static bool properInput(char input);
    string m_name;
    string m_sequence;
    
    //Genome* g;
};

bool GenomeImpl::properInput(char a)
{
    return (toupper(a) == 'A' || toupper(a) == 'G' || toupper(a) == 'T' || toupper(a) == 'C' || toupper(a) == 'N');
}
GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    
    
    char c;
    string dnaSequence;
    while(genomeSource.get(c))
    {
        dnaSequence += c;
    }

    if(dnaSequence[0] != '>')
        return false;
    
    int i = 0;
    string currentName;
    string currentSequence;
    while(i < dnaSequence.size())
    {
        
        if(dnaSequence[i] == '>')
        {
            
            size_t indexOfNewLine = dnaSequence.size();
            indexOfNewLine = dnaSequence.find('\n', i); //look for new line
            currentName = "";

            if(indexOfNewLine < dnaSequence.size())
            {
                for(int j = i+1; j < indexOfNewLine; j++)
                    currentName += dnaSequence[j];
            }
            else
                return false;
            i = indexOfNewLine + 1;
            
        }
        
        while (dnaSequence[i] != '>' && i < dnaSequence.size())
        {
            if (!properInput(dnaSequence[i]) && dnaSequence[i] != '\n')
            {
                return false;
            }
            else if (properInput(dnaSequence[i]))
            {
                currentSequence += toupper(dnaSequence[i]);
            }
            i++;
        }
        if (currentName.size() != 0 || currentSequence.size() != 0)
        {
            genomes.push_back(Genome(currentName, currentSequence)); //should i clear the vector if i return false
            currentName = "";
            currentSequence = "";
        }
        else
        {
            return false;
        }
    }
    
    
    return true;
    // This compiles, but may not be correct
}

int GenomeImpl::length() const
{
    return m_sequence.size();  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
    return m_name;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if(length <= 0 || (position + length) > m_sequence.size()) //should it be less than 0?
        return false;  // This compiles, but may not be correct
    
    
    fragment = m_sequence.substr(position, length);

    
    return true;
    
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}

//int main()
//{
//    //string filename = "Ferroplasma_acidarmanus.txt";
//    string filename = "Halobacterium_jilantaiense.txt";
//    ifstream strm(filename);
//    
//    if(!strm)
//    {
//        cout << "Cannot open " << filename << endl;
//        return 0;
//    }
//    
//    vector<Genome> vg;
//    bool success = Genome::load(strm, vg);
//    
//    if(success)
//    {
//        for(int k = 0; k < vg.size(); k++)
//            cout << vg[k].name() << endl;
//    }
//    
////    Genome g("oryx", "GCTCGGNACACATCCGCCGCGGACGGGACGGGATTCGGGCTGTCGATTGTCTCACAGATCGTCGACGTACATGACTGGGA");
////    string f1, f2, f3;
////    bool result1 = g.extract(0, 5, f1);     //    result1    =    true,    f1    =    “GCTCG”;
////    bool result2 = g.extract(74, 6, f2); //    result2 =    true,    f2 =    “CTGGGA”;
////    bool result3 = g.extract(74, 7, f3); //    result3 =    false,    f3 is    unchanged
////
////    cout << f1 << endl;
////    cout << f2 << endl;
////    cout << f3 << " " << result3 << endl;
//    
////    GenomeMatcher m(3);
////    m.addGenome(Genome("Genome 1", "ACTG"));
////    m.addGenome(Genome("Genome 2", "TCGACT"));
////    m.addGenome(Genome("Genome 3", "TCTCG"));
//    
//    GenomeMatcher m1(4);
//    m1.addGenome(Genome("Genome 1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
//    m1.addGenome(Genome("Genome 2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
//    m1.addGenome(Genome("Genome 3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
//    
//    vector<DNAMatch> matches;
//    
//    bool result;
//    result = m1.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG", 12, false, matches);
//        
//    
//}

