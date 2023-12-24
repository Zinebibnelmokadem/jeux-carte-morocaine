#ifndef MACLASSE_H
#define MACLASSE_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MaClasse; }
QT_END_NAMESPACE



class mouselable : public QLabel
{
    Q_OBJECT

signals:

    void clicked();


public:
    mouselable(QWidget *parent = nullptr);
   void startAnimation(const QPoint &startPos, const QPoint &endPos);




protected:
    void mousePressEvent(QMouseEvent *event) override;



private:
    bool isDragging;
    QPoint offset;


};





class MaClasse : public QMainWindow
{
    Q_OBJECT

public:
    MaClasse(QWidget *parent = nullptr);
    ~MaClasse();




private slots:
    void melange();
    void startGame();
    void Help();
    void createCircularMask();




private:
    int cartesDeplaceesCounter;

    Ui::MaClasse *ui;
    QStringList cardNames;

    QList<QString> imagePaths;
    QList<int> shuffledIndices;

    QLabel *titleLabel;
    QLabel *imageLabel1;
    QLabel *imageLabel2;
    QLabel *imageLabel3;
    QLabel *imageLabel4;
    QPushButton *startButton;
    QPushButton *playButton;
    QPushButton *recommence;
    QList<mouselable *>cartesObtenuesParOrdinateur;
     QList<mouselable *>cartesDeplaceesParJoueur;










 private:

    void distribuerCartesJoueur(const QList<int> &indicesJoueur, int endX, int endY);
    void distribuerCartesOrdinateur(const QList<int> &indicesOrdinateur, int endX, int endY);
    void carteJoueurClicked();
    void deplacerCartes();
    QString generateRandomFaceImagePath();
    void deplacer();
    void diminuerCarte();
    void supprimerCarteAleatoire();






};
#endif // MACLASSE_H
