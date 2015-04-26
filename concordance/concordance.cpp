#include "concordance.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <map>
#include <regex>

namespace yguo {

namespace {

static const char REGEX_WORD[] = "(\\b[^\\s]+\\b)";
    // Split sentence to words according to whitespaces.

static const char REGEX_SENT[] = "(\\S.+?[.!?])";
    // Sentence starts with a non-white space charactor and ends with either
    // '.', '!' or '?'.

}; // close unnamed namespace

                             // =================
                             // struct Occurrence
                             // =================

// CREATORS
Occurrence::Occurrence()
: m_count(0)
{
}

// PUBLIC METHODS
void Occurrence::print(std::ostream& stream) const
{
    stream << '{';
    stream << m_count;
    stream << ':';
    bool first = true;
    for (std::vector<int>::const_iterator it  = m_occrs.begin();
                                          it != m_occrs.end();
                                        ++it)
    {
        if (!first) {
            stream << ',';
        } else {
            first = false;
        }
        stream << *it;
    }
    std::cout << '}';
}

                             // =================
                             // class Concordance
                             // =================

// PRIVATE METHODS
void Concordance::parseSent(int sentId, const std::string& sent)
{
    std::regex regex(REGEX_WORD);

    for (std::sregex_iterator
             it  = std::sregex_iterator(sent.begin(), sent.end(), regex);
             it != std::sregex_iterator();
           ++it)
    {
        // Convert each char in the word to be lower case

        std::string word = it->str();
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Increment the count and add the sentence id into the list

        std::pair<Index::iterator, bool> ret =
                m_index.insert(std::make_pair(word, Occurrence()));

        ++ret.first->second.m_count;
        ret.first->second.m_occrs.push_back(sentId);
    }
}

void Concordance::parsePara(const std::string& para)
{
    int        sentId = 0;
    std::regex regex(REGEX_SENT);

    for (std::sregex_iterator
            it  = std::sregex_iterator(para.begin(), para.end(), regex);
            it != std::sregex_iterator();
          ++it)
    {
        parseSent(++sentId, it->str());
    }
}

// CREATOR
Concordance::Concordance()
{
}

// PUBLIC METHODS
void Concordance::build(std::istream& stream)
{
    m_index.clear();

    std::string para;
    while (std::getline(stream, para)) {
        parsePara(para);
    }
}

const Concordance::Index& Concordance::index() const
{
    return m_index;
}

void Concordance::print(std::ostream& stream) const
{
    // Sort the unordered dictionary using a ordered map

    typedef std::map<std::string, Index::const_iterator> OrderedDict;

    OrderedDict orderedDict;

    for (Index::const_iterator it  = m_index.begin();
                               it != m_index.end();
                             ++it)
    {
        orderedDict.insert(std::make_pair(it->first, it));
    }

    // Dump the ordered dictionary into stream.

    for (OrderedDict::const_iterator it  = orderedDict.begin();
                                     it != orderedDict.end();
                                   ++it)
    {
        stream << std::setw(25)
               << std::left
               << it->first
               << it->second->second
               << std::endl;
    }
}

} // close namespace yguo

// FREE FUNCTIONS
std::ostream& operator<<(std::ostream&           stream,
                         const yguo::Occurrence& occurrence)
{
    occurrence.print(stream);
    return stream;
}

std::ostream& operator<<(std::ostream&            stream,
                         const yguo::Concordance& builder)
{
    builder.print(stream);
    return stream;
}
