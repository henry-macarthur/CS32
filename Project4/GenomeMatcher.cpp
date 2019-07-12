#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    //static bool compareItems(const GenomeMatch& lhs, const GenomeMatch& rhs);
    struct trieContents
    {
        int position;
        int m_index;
    };
    int m_minSearch;
    //unordered_map<string, int> mapIndexes;
    vector<Genome> m_genomeList;
    Trie<trieContents> m_genomeTrie;
    static bool compareItems(const GenomeMatch& lhs, const GenomeMatch& rhs);
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearch = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genomeList.push_back(genome);
    //mapIndexes[genome.name()] = m_genomeList.size() - 1;
    
    for(int i = 0; i < genome.length(); i++)
    {
        string current;
        if(genome.extract(i, this->minimumSearchLength(), current))
        {
            trieContents t;
            t.position = i;
            t.m_index = m_genomeList.size() - 1;
            
//            DNAMatch dna;
//            dna.genomeName = genome.name();
//            dna.length = this->minimumSearchLength();
//            dna.position = i;
            m_genomeTrie.insert(current, t);
            
        }
        else
            break;
    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearch;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    
    if(minimumLength < minimumSearchLength() || fragment.length() < minimumLength)
        return false;
    
    string findS = fragment.substr(0, this->minimumSearchLength());
    
    //cout << findS << " " << this->minimumSearchLength() << endl;
    unordered_map<string, int> mapGenomeToVectorIndex;
    vector<trieContents> v =  m_genomeTrie.find(findS, exactMatchOnly); //is this ok?
    
    if(v.size() == 0)
        return false;
    
    for(int i = 0; i < v.size(); i++)
    {
        bool canKeepLooking = !exactMatchOnly;
        string s;

        int index = v[i].m_index;

        Genome curr = m_genomeList[index];
        
        m_genomeList[index].extract(v[i].position, fragment.length(), s);
        
        int currentLength = 0;
        int k = 0;

        for(;(v[i].position + k) < curr.length() && k < s.size(); k++)
        {
            if(fragment[k] !=  s[k])
            {
                
                if(canKeepLooking)
                {
                    canKeepLooking = false;
                }
                else
                {
                    break;
                }
            }
            
            currentLength++;
        }
        //do i have to right length here
        if(currentLength >= minimumLength)
        {
            DNAMatch addition;
            addition.genomeName = m_genomeList[index].name();//v[i].genomeName;
            addition.position = v[i].position;
            addition.length = currentLength;
            auto p = mapGenomeToVectorIndex.find(addition.genomeName);
            
            if(p == mapGenomeToVectorIndex.end())
            {
                
                matches.push_back(addition);
                mapGenomeToVectorIndex[addition.genomeName] = matches.size()-1;
            }
            else
            {
                if(matches[p->second].length < currentLength)
                {
                    matches[p->second] = addition;
                    mapGenomeToVectorIndex[addition.genomeName] = matches.size()-1;
                }
            }
        }
    }
    return true;
}

//inline
bool GenomeMatcherImpl::compareItems(const GenomeMatch& lhs, const GenomeMatch& rhs)
{
    if (lhs.percentMatch > rhs.percentMatch)
        return true;
    if (lhs.percentMatch < rhs.percentMatch)
        return false;
    return lhs.genomeName < rhs.genomeName;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    unordered_map<string, int> genomeToMatch;
    //cout << query.length() << endl;
    int totalMatches = query.length()/fragmentMatchLength;
    
    for(int i = 0; i*fragmentMatchLength < query.length(); i++)
    {
        string s;
        query.extract(i*fragmentMatchLength, fragmentMatchLength, s);
        
        vector<DNAMatch> m;
        bool isFound = findGenomesWithThisDNA(s, fragmentMatchLength, exactMatchOnly, m);
        
        if(isFound)
        {
            for(int j = 0; j < m.size(); j++)
            {
                
                if(m[j].length >= fragmentMatchLength)
                {
                    auto it = genomeToMatch.find(m[j].genomeName);
                    if(it != genomeToMatch.end())
                    {
                        genomeToMatch[m[j].genomeName]++;
                        //it->second += 1;
                    }
                    else
                    {
                        
                        genomeToMatch[m[j].genomeName] = 1;
                        //it->second = 1;
                    }
                    
                }
            }
        }

    }
    
    bool matchAdded = false;
    //vector<GenomeMatch> properMatches;
    
    for(auto it = genomeToMatch.begin(); it != genomeToMatch.end(); it++)
    {
        
        double percentFound = static_cast<double>((it->second))/(totalMatches);
        
        //should be *100?
        int p = percentFound*100;
        
        if(p >= matchPercentThreshold) //it is a match
        {
            matchAdded = true;
            GenomeMatch g;
            g.genomeName = it->first;
            g.percentMatch = p;
            
            results.push_back(g);
        }
    }
    
    sort(results.begin(), results.end(), compareItems);
    
    return matchAdded;
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}


