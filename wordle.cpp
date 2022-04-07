#include "wordle.h"
#include "mainwindow.h"
#include <iostream>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

using std::ifstream;

Wordle::Wordle(int lives)
{

    MainWindow::Instance->Print("You are going to play wordle now,\nYou have to write a word and then click on the validate button to check if it is the good word"
                                "\nEvery time you fail you lose a life");
    MainWindow::Instance->Print("Let's find the world !!");    
    nbLives = lives;

    countWord = 0;


    QString filename(QCoreApplication::applicationDirPath() +"/../words.txt");
//    MainWindow::Instance->Print(filename);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        MainWindow::Instance->Print("Impossible to read the file");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        words.push_back(line);
    }

    file.close();

    word = words[countWord];

    ShowWord();
}

void Wordle::ShowWord()
{
    QString hideWord = "";

    for (int i = 0; i < word.length(); i++)
    {
        hideWord += "_ ";
    }

    MainWindow::Instance->Print(hideWord);
}


int Wordle::CompareWords(QString answer)
{
    answer = answer.toLower();

    if (word.length() != answer.length())
    {
        MainWindow::Instance->Print("This word is not valid") ;
        return -1;
    }

    if (word == answer)
    {
        MainWindow::Instance->Print(word);
        MainWindow::Instance->Print("You find the word !");
        countWord++;
        if (countWord == words.size())
        {
            MainWindow::Instance->Print("You find all the words");
            return 2;
        }
        else
        {
            word = words[countWord];
            ShowWord();
             return 0;
        }

    }

    QString indications = "";
    for (int i = 0; i < answer.length(); i++)
    {
        if (answer[i] == word[i])
        {
            indications += answer[i];
            indications += " ";
        }
        else
        {
            indications += "_ ";
        }
    }
    MainWindow::Instance->Print(answer + '\n' + indications);
    return 1;
}
