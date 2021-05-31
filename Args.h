
#ifndef ARGS_H
#define ARGS_H

#include <string>

using namespace std;

class Args {
private:
    string filepath;
    string c;
    string filename;
    string b;
    int bloom_size;
    int levels;    
public:        
//getters and setters 
    Args(int argc, char * argv[]);
    
    string GetB() const {
        return b;
    }

    int GetBloom_size() const {
        return bloom_size;
    }

    string GetC() const {
        return c;
    }

    string GetFilename() const {
        return filename;
    }

    string GetFilepath() const {
        return filepath;
    }

    int GetLevels() const {
        return levels;
    }

};
#endif /* ARGS_H */

