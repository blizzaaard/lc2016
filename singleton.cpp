#include <atomic>
#include <mutex>

using namespace std;

class Singleton {

    static atomic<Singleton *> s_pInstance;
    static mutex               s_mutex;

    // NOT IMPLEMENTED
    Singleton(const Singleton&);
    const Singleton& operator=(const Singleton&);

  public:
    explicit Singleton()
    {
    }

    static Singleton* instance()
    {
        if (!s_pInstance) {
            lock_guard<mutex> guard(s_mutex);
            if (!s_pInstance) s_pInstance = new Singleton();
        }
        return s_pInstance;
    }
};

int main()
{
    return 0;
}
