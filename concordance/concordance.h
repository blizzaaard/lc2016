#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace yguo {

                             // =================
                             // struct Occurrence
                             // =================

struct Occurrence {

    // INSTANCE DATA
    int              m_count; // the word frequency
    std::vector<int> m_occrs; // sentence numberes in which the word occurs

    // CREATOR
    explicit Occurrence();
        // Create a 'Occurrence' object with 0 word frequency and empty
        // sentence numbers list.

    // PUBLIC METHODS
    void print(std::ostream& stream) const;
        // Dump this object into the specified 'stream' as a human-readable
        // string.
};

                             // =================
                             // class Concordance
                             // =================

class Concordance {

    // PRIVATE TYPES
    typedef std::unordered_map<std::string, Occurrence> Index;

    // INSTANCE DATA
    Index m_index;

    // NOT IMPLEMENTED
    Concordance(const Concordance&);
    Concordance& operator=(const Concordance&);

    // PRIVATE METHODS
    void parseSent(int sentId, const std::string& sent);
        // Parse the sentence in the specified 'sent' with the specified
        // 'sentId'.

    void parsePara(const std::string& para);
        // Parse the paragraph in the specified 'para'.

  public:
    // CREATOR
    explicit Concordance();
        // Create a 'Concordance' object with an empty index.

    // PUBLIC METHODS
    void build(std::istream& stream);
        // Build the index from the content in the specified 'stream'.

    const Index& index() const;
        // Return the non-modifiable reference to the index.

    void print(std::ostream& stream) const;
        // Dump this object into the specified 'stream' as a human-readable
        // string.
};

} // close namespace yguo

// FREE FUNCTIONS
std::ostream& operator<<(std::ostream&           stream,
                         const yguo::Occurrence& occurrence);

std::ostream& operator<<(std::ostream&            stream,
                         const yguo::Concordance& builder);

