#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
using namespace std;

class Database {
    private:
        Database() {}
        static Database* instance;
        static vector<string> imdb_id;
        static vector<string> title;
        static vector<string> plot_synopsis;
        static vector<string> tags;
        static vector<string> split;
        static vector<string> synopsis_source;
    public:
        static Database* getInstance();
        static void initialize();
        static vector<string>& getImdbId(){return imdb_id;}
        static vector<string>& getTitle(){return title;}
        static vector<string>& getPlotSynopsis(){return plot_synopsis;}
        static vector<string>& getTags(){return tags;}
        static vector<string>& getSplit(){return split;}
        static vector<string>& getSynopsisSource(){return synopsis_source;}
};

#endif // DATABASE_H