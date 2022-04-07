#ifndef WORDLE_H
#define WORDLE_H

#include <QString>
#include <vector>

using namespace std;

class Wordle
{
private:
    unsigned int countWord;
     vector<QString> words;
public:
    QString word;
    int nbLives;


    Wordle(int lives);
    void ShowWord();
    int CompareWords(QString answer);
};

#endif // WORDLE_H
